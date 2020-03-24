#include "functions.h"

using namespace std;

Row::Row(const size_t& length, int* row)
{
	Row_length = length;
	Matrix_row = row;
}

const int& Row::operator[](const size_t& j) const
{
	if(j >= Row_length)
		throw std::out_of_range("");
	else
		return Matrix_row[j];
}

int& Row::operator[](const size_t& j)
{
	if(j >= Row_length)
		throw std::out_of_range("");
	else
		return Matrix_row[j];
}


Matrix::Matrix(const size_t& rows_arg, const size_t& columns_arg)
{
	rows = rows_arg;
	columns = columns_arg;
	matrix = new int*[rows];
	for(int i = 0; i < rows; ++i) 
		matrix[i] = new int[columns];
}

Matrix::~Matrix()
{
	for(int i = 0; i < rows; ++i) 
		delete[] matrix[i];
}

const Row Matrix::operator[](const size_t& i) const
{
    if(i >= rows)
		throw std::out_of_range("");
    else
		return Row(columns, matrix[i]);
}

Row Matrix::operator[](const size_t& i) 
{
    if(i >= rows)
		throw std::out_of_range("");
    else
		return Row(columns, matrix[i]);
}

Matrix& Matrix::operator*=(const int& coef)
{
	for(int i=0; i<rows; ++i)
		for(int j=0; j<columns; ++j)
			matrix[i][j] *= coef;
	return *this;
}

bool Matrix::operator==(const Matrix& A) const
{
	if (this == &A)
		return true;
		
	if (A.columns != columns or A.rows != rows)
		return false;

    for(int i=0; i<rows; i++)
        for(int j=0; j<columns; j++)
			if((*this)[i][j] != A[i][j])
                return false;

	return true;
}

bool Matrix::operator!=(const Matrix& A) const
{
    return !(*this == A);
}

const size_t& Matrix::getColumns() const
{
    return columns;
}

const size_t& Matrix::getRows() const
{
    return rows;
}

