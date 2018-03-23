#include <iostream>
#include <fstream>
#include "SymmetricMatrix.h"

using namespace std;


int main(int argc, char** argv)
{
    string line;
    int size;

    // Input stream
    string fName = argc >= 2 ? argv[1] : "-";
    istream* input;
    if (fName != "-")
    {
        ifstream* file = new ifstream(fName);
        input = file;
    }
    else
    {
        input = &cin;
    }

    // Inputting matrix
    if (!(*input >> size))
    {
        cerr << "Empty input!" << endl;
        return 1;
    }
    SymmetricMatrix mat(size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            if (!(*input >> mat[i][j]))
            {
                cerr << "Incomplete input!" << endl;
                return 1;
            }
        }
    }

    eigen* e = mat.calculateEigens(1e-10);
    for (int i = 0; i < size; i++)
    {
        cout << "\n  eigen-value " << (i + 1) << ":\n";
        cout << e[i].value << endl;
        cout << "  eigen-vector " << (i + 1) << ":\n";
        for (int j = 0; j < size; j++)
        {
            cout << e[i].vector[j] << endl;
        }
    }

    if (fName == "-")
        ((ifstream*) input)->close();
}
