#pragma once
#include <iostream>
#include <cassert>
#include <sstream>
#include <cstdio>
#include <stdio.h>

class BigInt
{
	char sign_;
	size_t size_;
	char* data_;

	friend bool operator==(const BigInt&, const BigInt&);
	friend bool operator!=(const BigInt&, const BigInt&);
	friend bool operator<=(const BigInt&, const BigInt&);
	friend bool operator<(const BigInt&, const BigInt&);
	friend bool operator>(const BigInt&, const BigInt&);
	friend bool operator>=(const BigInt&, const BigInt&);
	friend BigInt BigIntAdd(const BigInt&, const BigInt&);
	friend BigInt BigIntSub(const BigInt&, const BigInt&);
	friend BigInt operator+(const BigInt&, const BigInt&);
	friend BigInt operator-(const BigInt&, const BigInt&);
	friend std::ostream& operator<<(std::ostream&, const BigInt&);
public:
	BigInt(const long long int& val = 0);
	BigInt(const BigInt&);
	BigInt(char*, char, size_t);
	BigInt(BigInt&&);
	~BigInt();
	BigInt& operator=(const BigInt&);
	BigInt& operator=(BigInt&&);
	BigInt operator-() const;
};

bool operator==(const BigInt&, const BigInt&);
bool operator!=(const BigInt&, const BigInt&);
bool operator<=(const BigInt&, const BigInt&);
bool operator<(const BigInt&, const BigInt&);
bool operator>(const BigInt&, const BigInt&);
bool operator>=(const BigInt&, const BigInt&);
BigInt BigIntAdd(const BigInt&, const BigInt&);
BigInt BigIntSub(const BigInt&, const BigInt&);
BigInt operator+(const BigInt&, const BigInt&);
BigInt operator-(const BigInt&, const BigInt&);
std::ostream& operator<<(std::ostream&, const BigInt&);
