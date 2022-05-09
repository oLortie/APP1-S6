#include <vector>
#include <iostream>
#include "eigen-3.4.0/Eigen/Dense"

using namespace std;
using V4D = vector<vector<vector<vector<float>>>>;
using V3D = vector<vector<vector<float>>>;
using V2D = vector<vector<float>>;
using Eigen::MatrixXf;
using Eigen::Matrix4f;

void showV4D(V4D v)
{
    for(int i = 0; i < 100; i++)
    {
        for(int j = 0; j < 100; j++)
        {
            for(int k = 0; k < 100; k++)
            {
                for(int l = 0; l < 3; l++)
                {
                    cout << v[i][j][k][l];
                }
            }

            cout << endl;
        }

        cout << endl;
    }

    cout << endl;
}

void showV2D(V2D v)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            cout << v[i][j];
        }

        cout << endl;
    }

    cout << endl;
}

void printVector(vector<float> v)
{
    for(int i = 0; i < 10; i++)
    {
        cout << v[i] << endl;
    }
}

template<typename T>
std::vector<T> slice(std::vector<T> const &v, int m, int n)
{
    // m et n inclusivement
    auto first = v.cbegin() + m;
    auto last = v.cbegin() + n + 1;
 
    std::vector<T> vec(first, last);
    return vec;
}

vector<float> curl_E(/*vector<float> E*/)
{
    //V4D curlE(100, vector<vector<vector<float>>>(100, vector<vector<float>>(100, vector<float>(3, 0))));

    //V4D v1(E[0][1][0][2], E[99][99][99][2]);
    //V4D v1 = slice(slice(slice(slice(curlE[0][0], 0, 3), 1, 99), 0, 99), 2, 2);
    
    /*V4D v1 = slice(curlE, 0, 99);
    V3D v2 = slice(v1[0], 0, 3);
    V2D v3 = slice(v2[0][0], 0, 3);
    vector<float> v3 = slice(v3[0][0][0], 0, 3);*/

    //showV2D(v2);

    vector<float> curlE(3000000, 0);

    /*for(int i = 0; i < 1000000; i++)
    {
        curlE[i] += E[i + 2000000] - E[i + 2000000];
    }

    curlE[i] += E[i + 2000000] - E[i + 2000000];*/

    //curlE.insert(curlE.cbegin(), begin(E), begin(E)+1000000);

    //printVector(curlE);










    return curlE;
}

V4D curl_H(V4D H)
{
    V4D curlH(100, vector<vector<vector<float>>>(100, vector<vector<float>>(100, vector<float>(3, 0))));

    return curlH;
}

int timestep(V4D E, V4D H, float courantNumber, int sourcePos, int sourceVal)
{
    return 0;
}

int main(int argc, char** argv)
{
    cout << "allo" << endl;
    //timestep((100,100, 100), 0.1, "wtf");

    curl_E();
}
