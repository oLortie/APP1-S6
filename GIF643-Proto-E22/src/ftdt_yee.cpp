#include <vector>
#include <iostream>

using namespace std;
using V4D = vector<vector<vector<vector<float>>>>;

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


V4D curl_E(V4D E)
{
    V4D curlE(100, vector<vector<vector<float>>>(100, vector<vector<float>>(100, vector<float>(3, 0))));

    //V4D v1(E[0][1][0][2], E[99][99][99][2]);


    //showV4D(v1);

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

    //curl_E();
}
