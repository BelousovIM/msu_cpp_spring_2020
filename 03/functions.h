#pragma once
#include <cstdio>
#include <iostream>


class Row
{
	int* Matrix_row;
	size_t Row_length;

	public:
		Row(size_t, int*);
		const int& operator[](size_t) const;
		int& operator[](size_t);
};

class Matrix
{
	size_t rows;
	size_t columns;
	int** matrix;

	public:

		Matrix(size_t, size_t);
		~Matrix();
		const Row operator[](size_t) const;
		Row operator[](size_t);
		Matrix& operator*=(const int&);
		bool operator==(const Matrix&) const;
		bool operator!=(const Matrix&) const;
		size_t getRows() const;
		size_t getColumns() const;

};
