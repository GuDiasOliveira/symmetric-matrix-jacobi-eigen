#include "SymmetricMatrix.h"
#include <cmath>


SymmetricMatrix::SymmetricMatrix() : m_size(0), m_mat(nullptr)
{
}

SymmetricMatrix::SymmetricMatrix(size_t mat_size) : m_size(mat_size), m_mat(new double[(mat_size - 1) * mat_size / 2 + mat_size])
{
}

SymmetricMatrix::~SymmetricMatrix()
{
    delete[] m_mat;
}

SymmetricMatrix::SymmetricMatrix(const SymmetricMatrix& other) : SymmetricMatrix(other.m_size)
{
    size_t arr_size = (m_size - 1) * m_size / 2 + m_size;
    for (size_t i = 0; i < arr_size; i++)
        m_mat[i] = other.m_mat[i];
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

eigen* SymmetricMatrix::calculateEigens(double precision)
{
    precision = abs(precision);
    size_t size = Getsize();

    if (size == 0)
        return nullptr;
    if (size == 1)
    {
        eigen* e = new eigen[1];
        e[0].value = m_mat[0];
        e[0].vector = new double[1];
        e[0].vector[0] = 1;
        return e;
    }

    double* eVects = new double[size * size];
    for (size_t i = 0; i < size; i++)
        for (size_t j = 0; j < size; j++)
            eVects[i * size + j] = i == j ? 1 : 0;

    SymmetricMatrix* matAp = this;
    while(true)
    {
        SymmetricMatrix& matA = *matAp;

        // Computing max Aij -> Apq, p, q
        size_t p = 0, q = 1;
        double Apq = abs(matA[0][1]);
        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < i; j++)
            {
                double Aij = abs(matA[i][j]);
                if (Aij > Apq)
                {
                    Apq = Aij;
                    p = i;
                    q = j;
                }
            }
        }

        if (Apq < precision)
            break;

        double phi = (matA[q][q] - matA[p][p]) / (2 * matA[p][q]);
        double t = phi == 0 ? 1 : (1 / (phi + (phi > 0 ? 1 : -1) * sqrt(phi * phi + 1)));
        double c = 1 / sqrt(1 + t * t);
        double s = t / sqrt(1 + t * t);

        // Computing Jacob rotation
        double* A_ = new double[size * size];
        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < size; j++)
            {
                size_t index = i * size + j;
                if (i == p)
                    A_[index] = matA[p][j] * c - matA[q][j] * s;
                else if (i == q)
                    A_[index] = matA[p][j] * s + matA[q][j] * c;
                else
                    A_[index] = matA[i][j];
            }
        }
        SymmetricMatrix* nextMatA = new SymmetricMatrix(size);
        SymmetricMatrix& A__ = *nextMatA;
        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j <= i; j++)
            {
                if (j == p)
                    A__[i][p] = A_[i * size + p] * c - A_[i * size + q] * s;
                else if (j == q)
                    A__[i][q] = A_[i * size + p] * s + A_[i * size + q] * c;
                else
                    A__[i][j] = A_[i * size + j];
            }
        }

        delete[] A_;
        if (matAp != this)
            delete matAp;

        matAp = nextMatA;

        // Computing eigenvectors
        double* nextEVects = new double[size * size];
        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < size; j++)
            {
                size_t k = i * size + j;
                if (j == p)
                    nextEVects[k] = eVects[i * size + p] * c - eVects[i * size + q] * s;
                else if (j == q)
                    nextEVects[k] = eVects[i * size + p] * s + eVects[i * size + q] * c;
                else
                    nextEVects[k] = eVects[k];
            }
        }
        delete[] eVects;
        eVects = nextEVects;
    }

    eigen* e = new eigen[size];
    for (size_t i = 0; i < size; i++)
    {
        e[i].value = (*matAp)[i][i];
        e[i].vector = new double[size];
        for (size_t j = 0; j < size; j++)
        {
            e[i].vector[j] = eVects[j * size + i];
        }
    }

    if (matAp != this)
        delete matAp;
    delete[] eVects;

    return e;
}
