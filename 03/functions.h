#pragma once
#include <cstdio>
#include <stdexcept>
#include <iostream>


class Row
{
	int* Matrix_row;
	size_t Row_length;

	public:
		Row(const size_t&, int*);
		const int& operator[](const size_t&) const;
		int& operator[](const size_t&);
};

class Matrix
{
	size_t rows;
	size_t columns;
	int** matrix;

	public:

		Matrix(const size_t&, const size_t&);
		~Matrix();
		const Row operator[](const size_t&) const;
		Row operator[](const size_t&);
		Matrix& operator*=(const int&);
		bool operator==(const Matrix&) const;
		bool operator!=(const Matrix&) const;
		const size_t& getRows() const;
		const size_t& getColumns() const;

};
