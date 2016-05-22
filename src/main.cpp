/*
 * main.cpp
 *
 *  Created on: 2011-3-6
 *      Author: uraplutonium
 */

#include <iostream>
#include <string.h>
#include "Word.h"
using namespace std;

bool menu(Wordlist *wl)
{
	bool ret = true;
	int select;
	cout <<"================ Ebbinghaus Word List Generator ================" <<endl;
	cout <<"                                                   by Felix.Ting" <<endl;
	cout <<"Please select:" <<endl;
	cout <<"1.Generate 100w wordlist;" <<endl;
	cout <<"2.Record the recited words;" <<endl;
	cout <<"3.Add new words;" <<endl;
	cout <<"4.Generate custom wordlist;" <<endl;
	cout <<"5.Display word data;" <<endl;
	cout <<"6.Quit Ebbinghaus." <<endl;

	cin >>select;
	switch(select)
	{
		case 1:
		{
			cout <<"generating wordlist..." <<endl;
			wl->generatelist();
			cout <<"wordlist.wls has been generated." <<endl <<endl;
			break;
		}
		case 2:
		{
			cout <<"reading files..." <<endl;
			wl->recite();
			cout <<"words data has been updated." <<endl;
			break;
		}
		case 3:
		{
			cout <<"reading files..." <<endl;
			wl->add();
			cout <<"words data has been updated." <<endl;
			break;
		}
		case 4:
		{
			cout <<"How many words do you want to export?" <<endl;
			int num;
			cin >>num;
			cout <<"generating wordlist..." <<endl;
			wl->generatelist(num);
			cout <<"wordlist.wls has been generated." <<endl <<endl;
			break;
		}
		case 5:
		{
			cout <<"################ ebbinghaus.info ################" <<endl;
			wl->display();
			cout <<"#################################################" <<endl;
			break;
		}
		case 6:
		{
			cout <<"exiting Ebbinghaus..." <<endl;
			ret = false;
			break;
		}
		default:
		{
			cout <<"unexpected character." <<endl;
		}
	}
	return ret;
}

int main(int argc, char* argv[])
{
	bool repeat;
	int len, i;

	len = strlen(argv[0]);
	len -= 10;
	char *path = new char[len];
	for(i = 0 ; i < len ; i++)
		path[i] = argv[0][i];

	Wordlist *wl = new Wordlist(path, len);

	do
	{
		repeat = menu(wl);
	}
	while(repeat);

	return 0;
}
