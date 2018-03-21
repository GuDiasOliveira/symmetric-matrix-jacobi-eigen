#include <iostream>
#include <random>
#include "SymmetricMatrix.h"

using namespace std;

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int main(int argc, char** argv)
{
    int size, r, c;
    cin >> size;
    SymmetricMatrix mat(size);
    for (int i = 0; i < size * size; i++)
        mat[i / size][i % size] = 0;
    while(cin >> r)
    {
        cin >> c;
        cin >> mat[r][c];
    }
    SymmetricMatrix mat2 = mat;
    mat[0][0] = 77.888;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            cout << "\t" << mat2[i][j];
        cout << endl;
    }
    return 0;
}
