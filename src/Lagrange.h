/*
 * Lagrange.h
 *
 *  Created on: 2011-3-8
 *      Author: uraplutonium
 */

#ifndef LAGRANGE_H_
#define LAGRANGE_H_


#endif /* LAGRANGE_H_ */

class Lagrange
{
private:
	int order;
	long double *X;
	long double *Y;

	long double basisfunc(int j, long double x);

public:
	Lagrange();
	Lagrange(int n, long double x[], long double y[]);

	long double L(long double x);

};
