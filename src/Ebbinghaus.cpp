/*
 * Ebbinghaus.cpp
 *
 *  Created on: 2011-3-8
 *      Author: uraplutonium
 */

#define MULTIPLE_MAX 1/(1-0.618)

#include "Ebbinghaus.h"
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;

double Ebbinghaus::enlarge(double r_start, double *m_start)
{
	double multiple;
	multiple = pow(2.718281828, (0-pow(6*(r_start-0.618), 2)/2));
	multiple = 1 + multiple * MULTIPLE_MAX * (*m_start);
	*m_start = multiple;

	return multiple;
}

Ebbinghaus::Ebbinghaus()
{
	T[0] = log(0+1.5) / log(1.5);
	T[1] = log(19+1.5) / log(1.5);
	T[2] = log(63+1.5) / log(1.5);
	T[3] = log(525+1.5) / log(1.5);
	T[4] = log(2880+1.5) / log(1.5);
	T[5] = log(8640+1.5) / log(1.5);
	T[6] = log(44640+1.5) / log(1.5);
	T[7] = log(512640+1.5) / log(1.5);

	R[0] = 1;
	R[1] = 0.582;
	R[2] = 0.442;
	R[3] = 0.358;
	R[4] = 0.278;
	R[5] = 0.254;
	R[6] = 0.212;
	R[7] = 0.1;

	lag = new Lagrange(8, T, R);
}

double Ebbinghaus::getr(double num)
{
	double rate;
	long double x;
	if(num < 0)
		rate = -1;
	else
	{
		num += 5;
		x = (long double)log(num) / (long double)log(1.5);
		rate = lag->L(x);
	}

	return rate;
}

double Ebbinghaus::getr(int num, double r_start, double *m_start)
{
	double rate = 0;

	if(r_start >= 0 && r_start <= 1 && m_start != NULL && *m_start >= 1)
	{
		double multiple, n;

		multiple = enlarge(r_start, m_start);
		n = (double)num / multiple;
		rate = getr(n);
	}
	else
		rate = -1;

	return rate;
}

int Ebbinghaus::gett(double rate, double r_start, double *m_start)
{
	int t = -1;
	if(rate > 0 && rate <= 1 && r_start >= 0 && r_start <= 1 && m_start != NULL && *m_start >= 1)
	{
		double multiple, n, r;
		multiple = enlarge(r_start, m_start);

		do
		{
			t++;
			n = (double)t / multiple;
			r = getr(n);
		}
		while(r > rate);
	}
	return t;
}

void Ebbinghaus::exportdata(char filename[30], double r_start, double m_start)
{
	int i;
	double *m = new double;
	double rate;
	ofstream outfile;

	outfile.open(filename, ios::out);
	if(!outfile)
	{
		cout <<"open " <<filename <<" error!" <<endl;
		return;
	}

	cout <<"export starting..." <<endl;
	outfile <<"r_start:" <<r_start <<endl;
	cout <<"r_start:" <<r_start <<endl;
	outfile <<"// the rate that you still remember now" <<endl <<endl;
	cout <<"// the rate that you still remember now" <<endl;
	outfile <<"m_start:" <<m_start <<endl;
	cout <<"m_start:" <<m_start <<endl;
	outfile <<"// the multiple of the previous process, and will effect the multiple of current process" <<endl <<endl;
	cout <<"// the multiple of the previous process, and will effect the multiple of current process" <<endl;

	*m = m_start;
	getr(0, r_start, m);
	outfile <<"m_current" <<*m <<endl;
	cout <<"m_current" <<*m <<endl;
	outfile <<"// the multiple of the current process" <<endl <<endl;
	cout <<"// the multiple of the current process" <<endl;

	cout <<"t exporting..." <<endl;
	outfile <<"################ t ################" <<endl;
	for(i = 0 ; i < 100 ; i++)
		outfile <<i <<endl;
	for(i = 100 ; i < 1000 ; i+=50)
		outfile <<i <<endl;
	for(i = 1000 ; i < 10000 ; i+=500)
		outfile <<i <<endl;
	for(i = 10000 ; i <= 50000 ; i+=5000)
		outfile <<i <<endl;
	outfile <<endl;

	cout <<"r exporting..." <<endl;
	outfile <<"################ r ################" <<endl;
	for(i = 0 ; i < 100 ; i++)
	{
		*m = m_start;
		rate = getr(i, r_start, m);
		outfile <<rate <<endl;
	}
	for(i = 100 ; i < 1000 ; i+=50)
	{
		*m = m_start;
		rate = getr(i, r_start, m);
		outfile <<rate <<endl;
	}
	for(i = 1000 ; i < 10000 ; i+=500)
	{
		*m = m_start;
		rate = getr(i, r_start, m);
		outfile <<rate <<endl;
	}
	for(i = 10000 ; i <= 50000 ; i+=5000)
	{
		*m = m_start;
		rate = getr(i, r_start, m);
		outfile <<rate <<endl;
	}

	cout <<"data exported." <<endl;

	outfile.close();
}
