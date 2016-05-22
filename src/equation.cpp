/*
 * equation.cpp
 *
 *  Created on: 2011-3-7
 *      Author: uraplutonium
 */

#include <iostream>
#include "equation.h"
using namespace std;

Equation::Equation()
{
	order = 0;
	coefficient = NULL;
	b = NULL;
	cofactor = 0;
}

Equation::Equation(int n, long double array[])
{
	order = n;
	coefficient = new long double[n*n];
	b = new long double[order];
	int i;

	for(i = 0 ; i < (n*(n+1)) ; i++)
	{
		if((i+1)%(n+1) == 0)
			b[((i+1)/(n+1)-1)] = array[i];
		else
			coefficient[(i-(i+1)/(n+1))] = array[i];
	}

	Matrix m = Matrix(order, coefficient);
	cofactor = m.getcofactor();
}

bool Equation::getdeterminant(pMatrix &pm, int y)
{
	bool legal;
	if(y >=0 && y < order)
		legal = true;
	else
		legal = false;

	if(legal)
	{
		int i;
		long double buf[order*order];

		for(i = 0 ; i < order*order ; i++)
			buf[i] = coefficient[i];
		for(i = 0 ; i < order ; i++)
			buf[i*order+y] = b[i];

		pm = new Matrix(order, buf);
	}

	return legal;
}

void Equation::display()
{
	int i, j;
	for(i = 0 ; i < order ; i++)
		cout <<b[i] <<'\t';
	cout <<endl <<endl;

	for(i = 0 ; i < order ; i++)
	{
		for(j = 0 ; j < order ; j++)
		{
			cout <<coefficient[i*order+j] <<'\t';
		}
		cout <<endl;
	}
}

long double Equation::getx(int n)
{
	long double x;
	pMatrix m;
	getdeterminant(m, n);
	x = m->getcofactor() / cofactor;
	return x;
}
