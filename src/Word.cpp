/*
 * Word.cpp
 *
 *  Created on: 2011-3-9
 *      Author: uraplutonium
 */

#include <iostream>
#include <fstream>
#include <time.h>
#include <string.h>
#include "Word.h"
#include "Ebbinghaus.h"
using namespace std;

int Wordlist::getdt(int former, int later)
{
	int dt;
	dt = 0;

	dt += (later%60 - former%60);
	later /= 60;
	former /= 60;
	dt += (later%24 - former%24)*60;
	later /= 24;
	former /= 24;
	dt += (later%365 - former%365)*24*60;
	later /= 365;
	former /= 365;
	dt += (later - former)*356*24*60;

	return dt;
}

int Wordlist::gett_now()
{
	time_t t;
	tm *tp;
	int t_now;
	t = time(NULL);
	tp = localtime(&t);

	t_now = tp->tm_year;
	t_now *= 365;
	t_now += tp->tm_yday;
	t_now *= 24;
	t_now += tp->tm_hour;
	t_now *= 60;
	t_now += tp->tm_min;

	return t_now;
}

int Wordlist::effect(word w)
{
	int dt;
	dt = getdt(w.time, gett_now());

	Ebbinghaus ebh;
	double r_start;
	double *m_start = new double;
	int t_delay;
	*m_start = w.multiple;
	r_start = ebh.getr(dt, w.rate, m_start);
	t_delay = ebh.gett(0.618, r_start, m_start);

	return t_delay;
}

void Wordlist::save()
{
	word *p;
	ofstream outfile;
	char *filename = new char[len+15];
	memset(filename, '\0', len+15);
	strcpy(filename, path);
	strcat(filename, "ebbinghaus.ebh");
	outfile.open(filename, ios::out);

	outfile <<num <<endl;

	p = HEAD;
	while(p->next != NULL)
	{
		p = p->next;
		outfile <<p->value <<'\t';
		outfile <<p->time <<'\t';
		outfile <<p->rate <<'\t';
		outfile <<p->multiple <<endl;
	}
	outfile.close();
}

Wordlist::Wordlist(char p[], int l)
{
	int i;
	len = l;
	path = new char[len];
	for(i = 0 ; i < len ; i++)
		path[i] = p[i];

	ifstream infile;
	char *filename = new char[len+15];
	memset(filename, '\0', len+15);
	strcpy(filename, path);
	strcat(filename, "ebbinghaus.ebh");

	infile.open(filename, ios::in);
	if(!infile)
	{
		cout <<"open ebbinghaus.ebh error!" <<endl;
		return;
	}

	word *newword;

	HEAD = new word;
	memset(HEAD->value, '\0', 21);
	HEAD->time = 0;
	HEAD->rate = 0;
	HEAD->multiple = 1;
	HEAD->next = NULL;

	infile >>num;
	for(i = 0 ; i < num ; i++)
	{
		newword = new word;
		infile >>newword->value;
		infile >>newword->time;
		infile >>newword->rate;
		infile >>newword->multiple;
		newword->next = NULL;
		newword->delay = effect(*newword);

		// insert
		word *p;
		for(p = HEAD ; p->next != NULL && newword->delay < p->next->delay ; p = p->next)
			;
		newword->next = p->next;
		p->next = newword;
	}

	infile.close();
}

void Wordlist::add()
{
	char *filename = new char[len+12];
	memset(filename, '\0', len+12);
	strcpy(filename, path);
	strcat(filename, "newword.wls");
	add(filename);
}

void Wordlist::add(char filename[])
{
	ifstream infile;
	infile.open(filename, ios::in);
	if(!infile)
	{
		cout <<"open " <<filename <<" error!" <<endl;
		return;
	}

	word *p;
	bool exist;
	char buf[21];
	word *newword;

	while(!infile.eof())
	{
		exist = false;
		memset(buf, '\0', 21);
		infile >>buf;
		if(strcmp("", buf) == 0)
		{
			//cout <<"unexpcted character!" <<endl;
			continue;
		}

		p = HEAD;
		while(p->next != NULL)
		{
			p = p->next;
			if(strcmp(buf, p->value) == 0)
			{
				exist = true;
				break;
			}
		}

		if(!exist)
		{
			newword = new word;
			strcpy(newword->value, buf);
			newword->time = gett_now();
			newword->rate = 0;
			newword->multiple = 1;
			newword->next = NULL;
			newword->delay = effect(*newword);

			// insert
			for(p = HEAD ; p->next != NULL && newword->delay < p->next->delay ; p = p->next)
				;
			newword->next = p->next;
			p->next = newword;
		}
	}

	int n;
	p = HEAD;
	n = 0;
	while(p->next != NULL)
	{
		p = p->next;
		n++;
	}
	num = n;

	infile.close();

	save();
}

void Wordlist::recite()
{
	char *filename = new char[len+16];
	memset(filename, '\0', len+16);
	strcpy(filename, path);
	strcat(filename, "recitedword.wls");
	recite(filename);
}

void Wordlist::recite(char filename[])
{
	Ebbinghaus ebh;
	ifstream infile;
	infile.open(filename, ios::in);
	if(!infile)
	{
		cout <<"open " <<filename <<endl;
		return;
	}

	word *p;
	bool exist;
	char buf[21];
	word *newword;

	while(!infile.eof())
	{
		exist = false;
		memset(buf, '\0', 21);
		infile >>buf;
		if(strcmp("", buf) == 0)
		{
			//cout <<"unexpcted character!" <<endl;
			continue;
		}

		p = HEAD;
		while(p->next != NULL)
		{
			p = p->next;
			if(strcmp(buf, p->value) == 0)
			{
				exist = true;
				break;
			}
		}

		if(!exist)
		{
			newword = new word;
			strcpy(newword->value, buf);
			newword->time = gett_now();
			newword->rate = 0;
			newword->multiple = 1;
			newword->next = NULL;
			newword->delay = effect(*newword);

			// insert
			word *p;
			for(p = HEAD ; p->next != NULL && newword->delay < p->next->delay ; p = p->next)
				;
			newword->next = p->next;
			p->next = newword;
		}
		else
		{
			// alter the word node
			int dt;
			double *m = new double;
			*m = p->multiple;
			dt = getdt(p->time, gett_now());
			p->time = gett_now();
			p->rate = ebh.getr(dt, p->rate, m);
			p->multiple = *m;
			p->delay = effect(*p);

			// take out word node
			word *pbuf;
			pbuf = p;
			for(p = HEAD ; p->next != pbuf ; p = p->next)
				;
			p->next = pbuf->next;
			pbuf->next = NULL;

			// insert word node
			for(p = HEAD ; p->next != NULL && pbuf->delay < p->next->delay ; p = p->next)
				;
			pbuf->next = p->next;
			p->next = pbuf;
		}
	}

	infile.close();

	int n;
	p = HEAD;
	n = 0;
	while(p->next != NULL)
	{
		p = p->next;
		n++;
	}
	num = n;

	save();
}

void Wordlist::generatelist()
{
	generatelist(100);
}

void Wordlist::generatelist(int n)
{
	int i, dt;
	double *m = new double;
	Ebbinghaus ebh;
	word *p;
	ofstream outfile;
	char *filename = new char[len+13];
	memset(filename, '\0', len+13);
	strcpy(filename, path);
	strcat(filename, "wordlist.wls");

	outfile.open(filename, ios::out);

	for(p = HEAD, i = 0 ; p->next != NULL && i < n ; i++)
	{
		p = p->next;

		// calculate memory rate
		*m = p->multiple;
		dt = getdt(p->time, gett_now());
		if(ebh.getr(dt, p->rate, m) <= 0.618)
			outfile <<p->value <<endl;
	}

	for(p = HEAD ; p->next != NULL && i < n ; i++)
	{
		p = p->next;

		// calculate memory rate
		*m = p->multiple;
		dt = getdt(p->time, gett_now());
		if(ebh.getr(dt, p->rate, m) > 0.618)
			outfile <<p->value <<endl;
	}

	outfile.close();
}

void Wordlist::display()
{
	word *p;
	p = HEAD;
	cout <<"num: " <<num <<endl <<endl;

	while(p->next != NULL)
	{
		p = p->next;
		cout <<"v: " <<p->value <<endl;
		cout <<"t: " <<p->time <<endl;
		cout <<"r: " <<p->rate <<endl;
		cout <<"m: " <<p->multiple <<endl;
		cout <<"d: " <<p->delay <<endl;
		cout <<endl;
	}
}
