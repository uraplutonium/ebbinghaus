/*
 * matrix.h
 *
 *  Created on: 2011-3-6
 *      Author: uraplutonium
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#endif /* MATRIX_H_ */

typedef class Matrix* pMatrix;

class Matrix
{
private:
	int order;
	long double **m;

	bool getsubmatrix(pMatrix &pm, int x, int y);

public:
	Matrix();
	Matrix(int n, long double array[]);

	void display();
	long double getcofactor();
};
