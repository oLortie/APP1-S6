#include <vector>
#include <iostream>
#include "eigen-3.4.0/Eigen/Dense"

using namespace std;

void printVector(vector<float> v)
{
    for(int i = 0; i < v.size() / 3; i++)
    {
        if(true/*v[i] <= 20100 && v[i] >= 19800*/)
        {
            cout << i << ": " << v[i] << " " << v[i + 1000000] << " " << v[i + 2000000] << endl;
        }
    }
}

std::vector<float> sliceCurl(std::vector<float> const &v, int m, int n)
{
    // m et n inclusivement
    auto first = v.cbegin() + m;
    auto last = v.cbegin() + n + 1;
 
    std::vector<float> vec(first, last);
    return vec;
}

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

    return vec;
}

vector<float> curl_E(vector<float> const &E)
{
    vector<float> curlE(3000000, 0);

    // !! mettre la dimension 2 (de 2m à 3m) dans le E
    auto E1 = sliceCurl(E, 2000000, 2999999);
    auto v1 = slice(E1, true, 1);
    auto v2 = slice(E1, false, 1);

    // !! mettre la dimension 0 (de 0m à 1m) dans le E
    auto E6 = sliceCurl(E, 0, 999999);
    auto v11 = slice(E6, true, 1);
    auto v12 = slice(E6, false, 1);

    int j = 0;
    int k = 0;

    for(int i = 0; i < 1000000; i++)
    {
        curlE[i] += v1[i - k] - v2[i - k];
        curlE[i + 2000000] += v11[i - k] - v12[i - k];

        if(j == 98)
        {
            k++;
            i++;
            j = 0;
        }
        else
        {
            j++;
        }
    }

    // !! mettre la dimension 1 (de 1m à 2m) dans le E
    auto E2 = sliceCurl(E, 1000000, 1999999);
    auto v3 = slice(E2, true, 2);
    auto v4 = slice(E2, false, 2);

    // !! mettre la dimension 0 (de 0m à 1m) dans le E
    auto E3 = sliceCurl(E, 0, 999999);
    auto v5 = slice(E3, true, 2);
    auto v6 = slice(E3, false, 2);

    j = 0;
    k = 0;

    for(int i = 0; i < 1000000; i++)
    {
        curlE[i] -= v3[i - k] - v4[i - k];
        curlE[i + 1000000] += v5[i - k] - v6[i - k];

        if(j == 9899)
        {
            k += 100;
            i += 100;
            j = 0;
        }
        else
        {
            j++;
        }
    }

    // !! mettre la dimension 2 (de 2m à 3m) dans le E
    auto E4 = sliceCurl(E, 2000000, 2999999);
    auto v7 = slice(E4, true, 2);
    auto v8 = slice(E4, false, 2);

    // !! mettre la dimension 1 (de 1m à 2m) dans le E
    auto E5 = sliceCurl(E, 1000000, 1999999);
    auto v9 = slice(E5, true, 0);
    auto v10 = slice(E5, false, 0);

    for(int i = 0; i < 990000; i++)
    {
        curlE[i + 1000000] += v7[i] - v8[i];
        curlE[i + 2000000] += v9[i] - v10[i];
    }

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
    
    for(int i = 0; i < 3000000; i++)
    {
        curlE.push_back(i);
    }

    printVector(curl_E(curlE));
}
