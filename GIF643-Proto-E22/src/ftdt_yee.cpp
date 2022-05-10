#include <vector>
#include <iostream>
#include "eigen-3.4.0/Eigen/Dense"

using namespace std;

void printVector(vector<float> v)
{
    for(int i = 0; i < v.size(); i++)
    {
        if(true/*v[i] <= 20100 && v[i] >= 19800*/)
        {
            cout << v[i] << endl;
        }
    }
}

/*template<typename T>
std::vector<T> slice(std::vector<T> const &v, int m, int n)
{
    // m et n inclusivement
    auto first = v.cbegin() + m;
    auto last = v.cbegin() + n + 1;
 
    std::vector<T> vec(first, last);
    return vec;
}*/

std::vector<float> slice(std::vector<float> const &v, bool face, int dimension)
{
    vector<float> vec = v;

    switch(dimension)
    {
        case 0: // enlève 10000 donnée par bon de 1000000
            face ? vec.erase(vec.cbegin(), vec.cbegin() + 10000) : vec.erase(vec.cend() - 10000, vec.cend());
            break;

        case 1: // enlève 1 donnée par bon de 100 et itération à l'envers pour pas fuck-up l'ordre du vecteur
            for(int i = 9999; i > -1; i--)
            {
                face ? vec.erase(vec.cbegin() + 100 * i) : vec.erase(vec.cbegin() + 99 + 100 * i);
            }
            break;
            
        case 2: // enlève 100 donnée par bon de 10000 et itération à l'envers pour pas fuck-up l'ordre du vecteur
            for(int i = 99; i > -1; i--)
            {
                face ? vec.erase(vec.cbegin() + 10000 * i, vec.cbegin() + 100 + 10000 * i) : vec.erase(vec.cbegin() + 9900 + 10000 * i, vec.cbegin() + 10000 + 10000 * i);
            }
            break;
    }

    //printVector(vec);

    return vec;
}

vector<float> curl_E(vector<float> const &E)
{
    vector<float> curlE(3000000, 0);

    // !! mettre la dimension 2 (de 2m à 3m) dans le E
    auto v1 = slice(E, true, 1);
    auto v2 = slice(E, false, 1);

    for(int i = 0; i < 100; i++)
    {
        for(int j = 0; j < 100; j++)
        {
            
        }
    }




    /*int j = 0;

    for(int i = 1; i <= 100; i++)
    {
        j += 100;

        for(;j < i * 100; j++)
        {
            
        }
    }*/

    return curlE;
}

/*V4D curl_H(V4D H)
{
    V4D curlH(100, vector<vector<vector<float>>>(100, vector<vector<float>>(100, vector<float>(3, 0))));

    return curlH;
}

int timestep(V4D E, V4D H, float courantNumber, int sourcePos, int sourceVal)
{
    return 0;
}*/

int main(int argc, char** argv)
{
    vector<float> curlE;
    
    for(int i = 0; i < 1000000; i++)
    {
        curlE.push_back(i);
    }

    slice(curlE, true, 1);
}
