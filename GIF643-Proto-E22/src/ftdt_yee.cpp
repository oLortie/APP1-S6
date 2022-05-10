#include <vector>
#include <iostream>
#include <mutex>
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

void computeCurl_E(vector<float> &v1, vector<float> &v2, vector<float> &v3, vector<float> &v4,
                            vector<float> &v5, vector<float> &v6, vector<float> &v7, vector<float> &v8,
                            vector<float> &v9, vector<float> &v10, vector<float> &v11, vector<float> &v12,
                            int startIndex, int endIndex, vector<float> &curlE)
{
    int iterator1 = 0;
    int iterator2 = 0;
    int iterator3 = 0;
    int iterator4 = 0;
    int iterator5 = 0;
    int iterator6 = 0; 

    for (int i = startIndex; i < endIndex; i++)
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
            curlE[i + 250000] += v5[iterator3] - v6[iterator3];
            iterator3++;
        }
        if (i < 990000)
        {
            curlE[i + 250000] -= v7[iterator4] - v8[iterator4];
            iterator4++;
        }

        // Dimension 2
        if (i < 990000) 
        {
            curlE[i + 500000] += v9[iterator5] - v10[iterator5];
            iterator5++;
        }
        if (i%10000 < 9900)
        {
            curlE[i + 500000] -= v11[iterator6] - v12[iterator6];
            iterator6++;
        }
    }
}

vector<float> curl_E(vector<float> const &E)
{
    vector<float> curlE_1(750000, 0);
    vector<float> curlE_2(750000, 0);
    vector<float> curlE_3(750000, 0);
    vector<float> curlE_4(750000, 0);
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

    thread t1(computeCurl_E, ref(v1), ref(v2), ref(v3), ref(v4), ref(v5), ref(v6), ref(v7), ref(v8), ref(v9), ref(v10), ref(v11), ref(v12), 0, 250000, ref(curlE_1));
    thread t2(computeCurl_E, ref(v1), ref(v2), ref(v3), ref(v4), ref(v5), ref(v6), ref(v7), ref(v8), ref(v9), ref(v10), ref(v11), ref(v12), 250000, 500000, ref(curlE_2));
    thread t3(computeCurl_E, ref(v1), ref(v2), ref(v3), ref(v4), ref(v5), ref(v6), ref(v7), ref(v8), ref(v9), ref(v10), ref(v11), ref(v12), 500000, 750000, ref(curlE_3));
    thread t4(computeCurl_E, ref(v1), ref(v2), ref(v3), ref(v4), ref(v5), ref(v6), ref(v7), ref(v8), ref(v9), ref(v10), ref(v11), ref(v12), 750000, 1000000, ref(curlE_4));

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    vector<float> curlE;
    curlE.insert(curlE.cend(), curlE_1.cbegin(), curlE_1.cbegin() + 250000);
    curlE.insert(curlE.cend(), curlE_2.cbegin(), curlE_2.cbegin() + 250000);
    curlE.insert(curlE.cend(), curlE_3.cbegin(), curlE_3.cbegin() + 250000);
    curlE.insert(curlE.cend(), curlE_4.cbegin(), curlE_4.cbegin() + 250000);
    curlE.insert(curlE.cend(), curlE_1.cbegin() + 250000, curlE_1.cbegin() + 500000);
    curlE.insert(curlE.cend(), curlE_2.cbegin() + 250000, curlE_2.cbegin() + 500000);
    curlE.insert(curlE.cend(), curlE_3.cbegin() + 250000, curlE_3.cbegin() + 500000);
    curlE.insert(curlE.cend(), curlE_4.cbegin() + 250000, curlE_4.cbegin() + 500000);
    curlE.insert(curlE.cend(), curlE_1.cbegin() + 500000, curlE_1.cbegin() + 750000);
    curlE.insert(curlE.cend(), curlE_2.cbegin() + 500000, curlE_2.cbegin() + 750000);
    curlE.insert(curlE.cend(), curlE_3.cbegin() + 500000, curlE_3.cbegin() + 750000);
    curlE.insert(curlE.cend(), curlE_4.cbegin() + 500000, curlE_4.cbegin() + 750000);

    return curlE;
}

/*vector<float> curl_H(vector<float> const &H)
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
}*/

mutex h_mutex;

void computeCurl_H(vector<float> &v1, vector<float> &v2, vector<float> &v3, vector<float> &v4,
                            vector<float> &v5, vector<float> &v6, vector<float> &v7, vector<float> &v8,
                            vector<float> &v9, vector<float> &v10, vector<float> &v11, vector<float> &v12,
                            int startIndex, int endIndex, vector<float> &curlH)
{
    int iterator1 = 0;
    int iterator2 = 0;
    int iterator3 = 0;
    int iterator4 = 0;
    int iterator5 = 0;
    int iterator6 = 0; 

    for (int i = startIndex; i < endIndex; i++)
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
            curlH[i + 250000] += v5[iterator3] - v6[iterator3];
            iterator3++;
        }
        if (i >= 10000)
        {
            curlH[i + 250000] -= v7[iterator4] - v8[iterator4];
            iterator4++;
        }

        // Dimension 2
        if (i >= 10000) 
        {
            curlH[i + 500000] += v9[iterator5] - v10[iterator5];
            iterator5++;
        }
        if (i%10000 >= 100)
        {
            curlH[i + 500000] -= v11[iterator6] - v12[iterator6];
            iterator6++;
        }
    }
}

vector<float> curl_H(vector<float> const &H)
{
    vector<float> curlH_1(750000, 0);
    vector<float> curlH_2(750000, 0);
    vector<float> curlH_3(750000, 0);
    vector<float> curlH_4(750000, 0);
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

    thread t1(computeCurl_H, ref(v1), ref(v2), ref(v3), ref(v4), ref(v5), ref(v6), ref(v7), ref(v8), ref(v9), ref(v10), ref(v11), ref(v12), 0, 250000, ref(curlH_1));
    thread t2(computeCurl_H, ref(v1), ref(v2), ref(v3), ref(v4), ref(v5), ref(v6), ref(v7), ref(v8), ref(v9), ref(v10), ref(v11), ref(v12), 250000, 500000, ref(curlH_2));
    thread t3(computeCurl_H, ref(v1), ref(v2), ref(v3), ref(v4), ref(v5), ref(v6), ref(v7), ref(v8), ref(v9), ref(v10), ref(v11), ref(v12), 500000, 750000, ref(curlH_3));
    thread t4(computeCurl_H, ref(v1), ref(v2), ref(v3), ref(v4), ref(v5), ref(v6), ref(v7), ref(v8), ref(v9), ref(v10), ref(v11), ref(v12), 750000, 1000000, ref(curlH_4));

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    vector<float> curlH;
    curlH.insert(curlH.cend(), curlH_1.cbegin(), curlH_1.cbegin() + 250000);
    curlH.insert(curlH.cend(), curlH_2.cbegin(), curlH_2.cbegin() + 250000);
    curlH.insert(curlH.cend(), curlH_3.cbegin(), curlH_3.cbegin() + 250000);
    curlH.insert(curlH.cend(), curlH_4.cbegin(), curlH_4.cbegin() + 250000);
    curlH.insert(curlH.cend(), curlH_1.cbegin() + 250000, curlH_1.cbegin() + 500000);
    curlH.insert(curlH.cend(), curlH_2.cbegin() + 250000, curlH_2.cbegin() + 500000);
    curlH.insert(curlH.cend(), curlH_3.cbegin() + 250000, curlH_3.cbegin() + 500000);
    curlH.insert(curlH.cend(), curlH_4.cbegin() + 250000, curlH_4.cbegin() + 500000);
    curlH.insert(curlH.cend(), curlH_1.cbegin() + 500000, curlH_1.cbegin() + 750000);
    curlH.insert(curlH.cend(), curlH_2.cbegin() + 500000, curlH_2.cbegin() + 750000);
    curlH.insert(curlH.cend(), curlH_3.cbegin() + 500000, curlH_3.cbegin() + 750000);
    curlH.insert(curlH.cend(), curlH_4.cbegin() + 500000, curlH_4.cbegin() + 750000);

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
    int nb_iterations = 5;

    EH eh;
    eh.E = vector<float>(3000000, 0);
    eh.H = vector<float>(3000000, 0);

    int courantNumber = 0.1;
    int sourcePos = 33*10000+33*100+50;
    int index = 0;
    float sourceVal = 0;

    for (int i = 0; i < nb_iterations; i++)
    {
        sourceVal = 0.1*sin(0.1*index);
        index++;
        eh = timestep(eh.E, eh.H, courantNumber, sourcePos, sourceVal);
        cout << "Iteration " << i << " done!" << endl;
    }

    printVector(eh.E);

}
