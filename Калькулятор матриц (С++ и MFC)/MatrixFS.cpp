#pragma once

#include "Matrix.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstring>
using namespace std;
matrix::matrix() 
{ 
	n = 3; 
	m = 3; 
	p = new int*[m]; 
	for (int i = 0; i < m; i++) 
		p[i] = new int[n]; 
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			p[i][j] = 0;
}
matrix::matrix(int m1, int n1)
{
	n = n1; m = m1;
	p = new int*[m];
	for (int i = 0; i < m; i++)
		p[i] = new int[n];
}
matrix::matrix(int m1, int n1, int init)
{
	n = n1; m = m1;
	p = new int*[m];
	for (int i = 0; i < m; i++)
		p[i] = new int[n];
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			p[i][j] = init;
}
matrix::matrix(int m1, int n1, int *init)
{
	n = n1; m = m1;
	int k = 0;
	p = new int*[m];
	for (int i = 0; i < m; i++)
		p[i] = new int[n];
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			p[i][j] = init[k++];
}
matrix::matrix(const matrix& mx)
{
	n = mx.n;
	m = mx.m;
	p = new int*[m];
	for (int i = 0; i < m; i++)
		p[i] = new int[n];
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			p[i][j] = mx.p[i][j];
}
matrix& matrix:: operator = (const matrix& mx)
{
	delete[]p;
	m = mx.m;
	n = mx.n;
	p = new int*[m];
	for (int i = 0; i < m; i++) 
		p[i] = new int[n];
	for (int i = 0; i < mx.m; i++)
		for (int j = 0; j < mx.n; j++)
			this->p[i][j] = mx.p[i][j];
	return *this;
}
// унарные операторы
matrix& matrix::operator += (const matrix& mx)
{
	try
	{
		if (mx.n > n || mx.m > m)
			throw 9;
		if (mx.n <= n && mx.m <= m)
		{
			for (int i = 0; i < mx.m; i++)
				for (int j = 0; j < mx.n; j++)
					p[i][j] += mx.p[i][j];
			return *this;
		}
	}
	catch (int i)
	{
		std::cout << "Bad dimensions!\n";
	}
}
// throw Bad_dimensions
matrix& matrix::operator -= (const matrix& mx) 
{
	try
	{
		if (mx.n > n || mx.m > m)
			throw 9;
		if (mx.n <= n && mx.m <= m)
		{
			for (int i = 0; i < mx.m; i++)
				for (int j = 0; j < mx.n; j++)
					p[i][j] -= mx.p[i][j];
			return *this;
		}
	}
	catch (int i)
	{
		std::cout << "Bad dimensions!\n";
	}
}	// throw Bad_dimensions
matrix& matrix::operator *= (const matrix& mx)
{
	try
	{
		if (mx.m != n)
			throw 9;
		else
		{
			matrix res(m, mx.n, 0);
			for (int i = 0; i < m; i++)
				for (int j = 0; j < mx.n; j++)
					for (int r = 0; r < n; r++)
						res.p[i][j] += p[i][r] * mx.p[r][j];
			*this = res;
			return *this;
		}
	}
	catch (int i)
	{
		std::cout << "Bad dimensions!\n";
	}
}
// throw Bad_dimensions
matrix& matrix::operator *= (const int& d)
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			p[i][j] *=d;
	return *this;
}
// унарные операторы
matrix operator -(const matrix& mx)
{
	for (int i = 0; i < mx.m; i++)
		for (int j = 0; j < mx.n; j++)
			mx.p[i][j] *= (-1);
	return mx;
}
matrix operator +(const matrix& mx)
{
	for (int i = 0; i < mx.m; i++)
		for (int j = 0; j < mx.n; j++)
			if(mx.p[i][j]<0)
				mx.p[i][j] *= (-1);
	return mx;
}
// бинарные операторы
matrix operator * (const int& d, const matrix& mx)
{
	matrix res(mx);
	for (int i = 0; i < res.m; i++)
		for (int j = 0; j < res.n; j++)
			res.p[i][j] *= d;
	return res;
}
matrix operator * (const matrix& mx, const int& d)
{
	matrix res(mx);
	for (int i = 0; i < res.m; i++)
		for (int j = 0; j < res.n; j++)
			res.p[i][j] *= d;
	return res;
}
// следующие бинарные операторы 
// могут выбросить исключение Bad_dimensions
matrix operator + (const matrix& m1, const matrix& m2)
{
	try
	{
		if (m1.n != m2.n || m1.m != m2.m)
			throw 9;
	matrix res(m1.m,m1.n,0);
	for (int i = 0; i < res.m; i++)
		for (int j = 0; j < res.n; j++)
			res.p[i][j]=m1.p[i][j]+m2.p[i][j];
	return res;
	}
	catch (int i)
	{
		std::cout << "Bad dimensions!\n";
	}
}
matrix operator - (const matrix& m1, const matrix& m2)
{
	try
	{
		if (m1.n != m2.n || m1.m != m2.m)
			throw 9;
	matrix res(m1.m, m1.n, 0);
	for (int i = 0; i < res.m; i++)
		for (int j = 0; j < res.n; j++)
			res.p[i][j] = m1.p[i][j] - m2.p[i][j];
	return res;
	}
	catch (int i)
	{
		std::cout << "Bad dimensions!\n";
	}
}
matrix operator * (const matrix& m1, const matrix& m2)
{
	matrix res(m1.m, m2.n, 0);
	try
	{
		if (m2.m != m1.n)
		{
			throw 9;
		}
		for (int i = 0; i < m1.m; i++)
			for (int j = 0; j < m2.n; j++)
				for (int r = 0; r < m1.n; r++)
					res.p[i][j] += m1.p[i][r] * m2.p[r][j];
		
	}
	catch (int i)
	{
		std::cout << "Bad dimensions!\n";
	}
	return res;
}

/*char** matrix:: print()
{
	char *buff;
	int ssize=0;
	char **res = new char*[m];
	for (int i = 0; i < m; i++)
		res[i] = new char[3 * n];
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			buff = itoa(p[i][j], buff, 10);
			res[i][j + ssize] = buff[0];
			if (isdigit(buff[1]) != 0)
			{
				ssize++;
				res[i][j + ssize] = buff[1];
			}
			else
			{
				ssize++;
				res[i][j + ssize] = ' ';
			}
			ssize++;
			res[i][j + ssize] = ' ';
			std::cout << setw(3) << p[i][j] << ((j == n - 1) ? "\n" : " ");
		}
	return res;
}
*/
void matrix::chng_spc()
{
	int i =1,a,b,n,N;
	std::cout << "enter what to do with matrix:\n";
	while (i)
	{
		std::cout << "1. Change one specific\n2. Change N specific\n3. Exit\n";
		cin >> i;
		switch (i)
		{
		case 1:
		{
			std::cout << "enter coordinates:\n";
			cin >> a >> b;
			std::cout << "enter new value:\n";
			cin >> n;
			p[a - 1][b - 1] = n;
			break;
		}
		case 2:
		{
			std::cout << "enter number of changes:\n";
			cin >> N;
			for (int j = 0; j < N; j++)
			{
				std::cout << "enter coordinates:\n";
				cin >> a >> b;
				std::cout << "enter new value:\n";
				cin >> n;
				p[a - 1][b - 1] = n;
			}
			break;
		}
		case 3:
			i = 0;
			break;
		default:
			i = 0;
			break;
		}
	}
}
std::string matrix::out()
{
	char *buff;
	int ssize = 0;
	string res;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			res += p[i][j];
			res += ' ';
			ssize++;
			if (j == n - 1)
				res += "\n";
			std::cout << setw(3) << p[i][j] << ((j == n - 1) ? "\n" : " ");
		}
	}
	return res;
}
void matrix::elsadd(int mtarget, int msource)
{
	for (int i = 0; i < n; i++)
		p[mtarget][i] += p[msource][i];
}
void matrix::elmul(int m1, double value)
{
	for (int i = 0; i < n; i++)
		p[m1][i] *= value;
}
void matrix::swapr(int m1, int m2)
{
	int *buff = new int[n];
	for (int i = 0; i < n; i++)
		buff[i] = p[m1][i];
	for (int i = 0; i < n; i++)
		p[m1][i]=p[m2][i];
	for (int i = 0; i < n; i++)
		p[m2][i]=buff[i];
}
void matrix::swapc(int n1, int n2)
{
	int *buff = new int[n];
	for (int i = 0; i < m; i++)
		buff[i] = p[i][n1];
	for (int i = 0; i < m; i++)
		p[i][n1] = p[i][n2];
	for (int i = 0; i < m; i++)
		p[i][n2] = buff[i];
}
void matrix::print(int k)
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			std::cout << setw(3) << p[i][j] << ((j == n - 1) ? "\n" : " ");
		}
	return;
}
matrix matrix::minor(int x, int y)
{
	int im = 0, jm = 0;
	matrix res(m-1,n-1);
	for (int i = 0; i < res.m; i++)
	{
		if (im == x)
			im++;
		for (int j = 0; j < res.n; j++)
		{
			if (jm == y)
				jm++;
			if(im!=x && jm!=y)
				res.p[i][j] = p[im][jm];
			jm++;
		}
		jm = 0;
		im++;
	}
	return res;
}
int matrix::det(matrix mx, int csize)
{
	int d=0;
	mx.n = csize;
	if (csize == 2)
	{
		d = (mx.p[0][0] * mx.p[1][1] - mx.p[0][1] * mx.p[1][0]);
		return (d);
	}
	if (m == n)
	{
		int i;
		for (i = 0; i < mx.n; i++)
		{
			d += pow(-1, i)*mx.p[i][0] * det(mx.minor(i, 0), csize - 1);
			//std::cout << mx.p[i][0] << endl;
		}
		return d;
	}
	else
	{
		std::cout << " Determinator does not exist!\n";
		return  0;
	}
}
int* matrix::arr()
{
	int *arr = new int[m*n];
	int k = 0;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			arr[k] = p[i][j];
			k++;
		}
	return arr;
}
