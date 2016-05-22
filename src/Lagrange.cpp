/*
 * Lagrange.cpp
 *
 *  Created on: 2011-3-8
 *      Author: uraplutonium
 */

#include "Lagrange.h"
#include <iostream>
using namespace std;

long double Lagrange::basisfunc(int j, long double x)
{
	long double l = 1;
	int i;

	for(i = 0 ; i < order ; i++)
	{
		if(j != i)
		{
			l = l*(x-X[i]);
			l = l/(X[j]-X[i]);
		}
	}

	return l;
}

Lagrange::Lagrange()
{
	order = 0;
	X = NULL;
	Y = NULL;
}

Lagrange::Lagrange(int n, long double x[], long double y[])
{
	order = n;
	X = new long double[order];
	Y = new long double[order];

	int i;
	for(i = 0 ; i < order ; i++)
	{
		X[i] = x[i];
		Y[i] = y[i];
	}
}

long double Lagrange::L(long double x)
{
	int j;
	long double l = 0;

	for(j = 0 ; j < order ; j++)
	{
		l = l+(Y[j]*basisfunc(j, x));
	}

	return l;
}
