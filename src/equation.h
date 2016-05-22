/*
 * equation.h
 *
 *  Created on: 2011-3-7
 *      Author: uraplutonium
 */

#ifndef EQUATION_H_
#define EQUATION_H_

#endif /* EQUATION_H_ */

#include "matrix.h"

class Equation
{
private:
	int order;
	long double *coefficient;
	long double *b;
	long double cofactor;

	bool getdeterminant(pMatrix &pm, int y);

public:
	Equation();
	Equation(int n, long double array[]);

	void display();
	long double getx(int n);
};
