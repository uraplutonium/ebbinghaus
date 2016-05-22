/*
 * matrix.cpp
 *
 *  Created on: 2011-3-6
 *      Author: uraplutonium
 */

#include "matrix.h"
#include <iostream>
using namespace std;

Matrix::Matrix()
{
	m = NULL;
}

Matrix::Matrix(int n, long double array[])
{
	int i, j;

	order = n;
	m = new long double*[order];

	for(i = 0 ; i < order ; i++)
		m[i] = new long double[order];

	for(i = 0 ; i < order ; i++)
		for(j = 0 ; j < order ; j++)
			m[i][j] = array[i*order+j];
}

bool Matrix::getsubmatrix(pMatrix &pm, int x, int y)
{
	bool legal;
	if(x >= 0 && x < order && y >= 0 && y < order)
		legal = true;
	else
		legal = false;

	if(legal)
	{
		long double buf[(order-1)*(order-1)];
		int i, j, k;
		for(i = 0, k = 0 ; i < order ; i++)
		{
			if(i != x)
			{
				for(j = 0 ; j < order ; j++)
				{
					if(j != y)
					{
						buf[k] = m[i][j];
						k++;
					}
				}
			}
		}

		pm = new Matrix(order-1, buf);
	}

	return legal;
}

void Matrix::display()
{
	if(m != NULL)
	{
		int i, j;
		for(i = 0 ; i < order ; i++)
		{
			for(j= 0 ; j < order ; j++)
			{
				cout <<m[i][j] <<'\t';
			}
			cout <<endl;
		}
	}
}

long double Matrix::getcofactor()
{
	long double cofactor;

	if(order == 1)
		cofactor = m[0][0];
	else
	{
		pMatrix sm[order];
		int i;
		long double c;
		for(i = 0 ; i < order ; i++)
			getsubmatrix(sm[i], 0, i);

		cofactor = 0;
		for(i = 0 ; i < order ; i++)
		{
			c = m[0][i] * (sm[i]->getcofactor());
			if(i%2 != 0)
				c *= (-1);
			cofactor += c;
		}
	}

	return cofactor;
}
