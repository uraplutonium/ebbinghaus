/*
 * Ebbinghaus.h
 *
 *  Created on: 2011-3-8
 *      Author: uraplutonium
 */

#ifndef EBBINGHAUS_H_
#define EBBINGHAUS_H_


#endif /* EBBINGHAUS_H_ */

#include "Lagrange.h"

class Ebbinghaus
{
private:
	long double T[8];
	long double R[8];
	Lagrange *lag;

	double enlarge(double r_start, double *m_start);

public:
	Ebbinghaus();

	// num: the time that you recite, return: getr: the rate that you remember.
	double getr(double num);

	// num: the time that you recite, r_start: the rate when start
	// *m_start: a point which point to the multiple when start
	// return: getr: the rate that you remember
	// *m_start: a point which point to the multiple in current process
	double getr(int num, double r_start, double *m_start);

	// rate: the rate that you remember, r_start: the rate when start
	// *m_start: a point which point to the multiple when start
	// return: gett: the time that you recite
	// *m_start: a point which point to the multiple in current process
	int gett(double rate, double r_start, double *m_start);

	void exportdata(char filename[30], double r_start, double m_start);
};
