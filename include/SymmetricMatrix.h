#ifndef SYMMETRICMATRIX_H
#define SYMMETRICMATRIX_H

#include <iostream>

using namespace std;


class SymmetricMatrix
{
    public:
        SymmetricMatrix();
        SymmetricMatrix(size_t mat_size);
        virtual ~SymmetricMatrix();
        SymmetricMatrix(const SymmetricMatrix& other);

        size_t Getsize() const { return m_size; }

        class Row
        {
            friend class SymmetricMatrix;
            private:
                SymmetricMatrix& m_mat;
                size_t m_row;
                Row(SymmetricMatrix& mat, size_t row) : m_mat(mat), m_row(row) {}
            public:
                double& operator[](size_t index);
        };

        Row operator[](size_t index);

    protected:

    private:
        const size_t m_size;
        double* const m_mat;
};

#endif // SYMMETRICMATRIX_H
