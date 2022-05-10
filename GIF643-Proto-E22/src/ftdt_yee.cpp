#include <vector>
#include <iostream>
#include <thread>
#include <math.h>

using namespace std;

void printVector(vector<float> v)
{
    for(int i = 0; i < v.size() / 3; i++)
    {
        if(v[i] != 0 || v[i + 1000000] != 0 || v[i + 2000000] != 0)
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

    /*switch(dimension)
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
    }*/

    // Je pense que y et z sont inversés, il faudrait échanger 1 et 2 dans le case

    switch(dimension)
    {
        case 0: // enlève 10000 donnée par bon de 1000000
            face ? vec.erase(vec.cbegin(), vec.cbegin() + 10000) : vec.erase(vec.cend() - 10000, vec.cend());
            break;
        
        case 1: // enlève 100 donnée par bon de 10000 et itération à l'envers pour pas fuck-up l'ordre du vecteur
            for(int i = 99; i > -1; i--)
            {
                face ? vec.erase(vec.cbegin() + 10000 * i, vec.cbegin() + 100 + 10000 * i) : vec.erase(vec.cbegin() + 9900 + 10000 * i, vec.cbegin() + 10000 + 10000 * i);
            }
            break;

        case 2: // enlève 1 donnée par bon de 100 et itération à l'envers pour pas fuck-up l'ordre du vecteur
            for(int i = 9999; i > -1; i--)
            {
                face ? vec.erase(vec.cbegin() + 100 * i) : vec.erase(vec.cbegin() + 99 + 100 * i);
            }
            break;
    }

    return vec;
}

/*vector<float> curl_E(vector<float> const &E)
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
}*/

vector<float> curl_E(vector<float> const &E)
{
    vector<float> curlE(3000000, 0);
    vector<float> E0 = sliceCurl(E, 0, 999999);
    vector<float> E1 = sliceCurl(E, 1000000, 1999999);
    vector<float> E2 = sliceCurl(E, 2000000, 2999999);

    vector<float> v1 = slice(E2, true, 1);
    vector<float> v2 = slice(E2, false, 1);

    vector<float> v3 = slice(E1, true, 2);
    vector<float> v4 = slice(E1, false, 2);

    vector<float> v5 = slice(E0, true, 2);
    vector<float> v6 = slice(E0, false, 2);

    vector<float> v7 = slice(E2, true, 0);
    vector<float> v8 = slice(E2, false, 0);

    vector<float> v9 = slice(E1, true, 0);
    vector<float> v10 = slice(E1, false, 0);

    vector<float> v11 = slice(E0, true, 1);
    vector<float> v12 = slice(E0, false, 1);

    int iterator1 = 0;
    int iterator2 = 0;
    int iterator3 = 0;
    int iterator4 = 0;
    int iterator5 = 0;
    int iterator6 = 0; 

    for (int i = 0; i < 1000000; i++)
    {
        // Dimension 0
        if (i%10000 < 9900) 
        {
            curlE[i] += v1[iterator1] - v2[iterator1];
            iterator1++;
        }
        if (i%100 != 99)
        {
            curlE[i] -= v3[iterator2] - v4[iterator2];
            iterator2++;
        }

        // Dimension 1
        if (i%100 != 99)
        {
            curlE[i + 1000000] += v5[iterator3] - v6[iterator3];
            iterator3++;
        }
        if (i < 990000)
        {
            curlE[i + 1000000] -= v7[iterator4] - v8[iterator4];
            iterator4++;
        }

        // Dimension 2
        if (i < 990000) 
        {
            curlE[i + 2000000] += v9[iterator5] - v10[iterator5];
            iterator5++;
        }
        if (i%10000 < 9900)
        {
            curlE[i + 2000000] -= v11[iterator6] - v12[iterator6];
            iterator6++;
        }
    }

    return curlE;
}

vector<float> curl_H(vector<float> const &H)
{
    vector<float> curlH(3000000, 0);
    vector<float> H0 = sliceCurl(H, 0, 999999);
    vector<float> H1 = sliceCurl(H, 1000000, 1999999);
    vector<float> H2 = sliceCurl(H, 2000000, 2999999);

    vector<float> v1 = slice(H2, true, 1);
    vector<float> v2 = slice(H2, false, 1);

    vector<float> v3 = slice(H1, true, 2);
    vector<float> v4 = slice(H1, false, 2);

    vector<float> v5 = slice(H0, true, 2);
    vector<float> v6 = slice(H0, false, 2);

    vector<float> v7 = slice(H2, true, 0);
    vector<float> v8 = slice(H2, false, 0);

    vector<float> v9 = slice(H1, true, 0);
    vector<float> v10 = slice(H1, false, 0);

    vector<float> v11 = slice(H0, true, 1);
    vector<float> v12 = slice(H0, false, 1);

    int iterator1 = 0;
    int iterator2 = 0;
    int iterator3 = 0;
    int iterator4 = 0;
    int iterator5 = 0;
    int iterator6 = 0; 

    for (int i = 0; i < 1000000; i++)
    {
        // Dimension 0
        if (i%10000 >= 100) 
        {
            curlH[i] += v1[iterator1] - v2[iterator1];
            iterator1++;
        }
        if (i%100 != 0)
        {
            curlH[i] -= v3[iterator2] - v4[iterator2];
            iterator2++;
        }

        // Dimension 1
        if (i%100 != 0)
        {
            curlH[i + 1000000] += v5[iterator3] - v6[iterator3];
            iterator3++;
        }
        if (i >= 10000)
        {
            curlH[i + 1000000] -= v7[iterator4] - v8[iterator4];
            iterator4++;
        }

        // Dimension 2
        if (i >= 10000) 
        {
            curlH[i + 2000000] += v9[iterator5] - v10[iterator5];
            iterator5++;
        }
        if (i%10000 >= 100)
        {
            curlH[i + 2000000] -= v11[iterator6] - v12[iterator6];
            iterator6++;
        }
    }

    return curlH;
}

struct EH {
    vector<float> E;
    vector<float> H;
};

EH timestep(vector<float> &E, vector<float> &H, float courantNumber, int sourcePos, float sourceVal)
{
    vector<float> curlH = curl_H(H);
    for (int i = 0; i < 3000000; i++)
    {
        E[i] += courantNumber * curlH[i];
    }
    E[sourcePos] += sourceVal;

    vector<float> curlE = curl_E(E);
    for (int i = 0; i < 3000000; i++)
    {
        H[i] -= courantNumber * curlE[i];
    }

    return EH {
        E,
        H
    };
}

int main(int argc, char** argv)
{
    /*vector<float> curlE;
    
    for(int i = 0; i < 3000000; i++)
    {
        curlE.push_back(i);
    }

    printVector(curl_E(curlE));*/
    int nb_iterations = 10;

    EH eh;
    eh.E = vector<float>(3000000, 0);
    eh.H = vector<float>(3000000, 0);

    int courantNumber = 0.1;
    int sourcePos = 33*10000+33*100+33;
    int index = 0;
    float sourceVal = 0;

    for (int i = 0; i < nb_iterations; i++)
    {
        sourceVal = 0.1*sin(0.1*index);
        index++;
        timestep(eh.E, eh.H, courantNumber, sourcePos, sourceVal);
        cout << "Iteration " << i << " done!" << endl;
    }

    printVector(eh.E);

}
