/*
 * Word.h
 *
 *  Created on: 2011-3-9
 *      Author: uraplutonium
 */

#ifndef WORD_H_
#define WORD_H_


#endif /* WORD_H_ */

struct word
{
	char value[21];
	int time;
	double rate;
	double multiple;
	int delay;
	word *next;
};

class Wordlist
{
private:
	word *HEAD;
	int num;
	char *path;
	int len;

	int getdt(int former, int later);
	int gett_now();
	int effect(word w);
	void save();

public:
	Wordlist(char p[], int l);

	void add();
	void add(char filename[]);

	void recite();
	void recite(char filename[]);

	void generatelist();
	void generatelist(int n);

	void display();
};
