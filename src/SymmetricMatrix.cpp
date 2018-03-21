#include "SymmetricMatrix.h"
#include<math.h>

SymmetricMatrix::SymmetricMatrix() : m_size(0)
{
}

SymmetricMatrix::SymmetricMatrix(size_t mat_size) : m_size(mat_size), m_mat(new double[(mat_size - 1) * mat_size / 2 + mat_size])
{
}

SymmetricMatrix::~SymmetricMatrix()
{
    delete m_mat;
}

SymmetricMatrix::SymmetricMatrix(const SymmetricMatrix& other)
{
    // TODO
}

SymmetricMatrix::Row SymmetricMatrix::operator[](size_t row)
{
    return Row(*this, row);
}

double& SymmetricMatrix::Row::operator[](size_t col)
{
    size_t r = max(m_row, col);
    size_t c = min(m_row, col);
    return m_mat.m_mat[(r + 1) * r / 2 + c];
}
