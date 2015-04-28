// MySTL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include"list.h"
using namespace CQ;
using std::cout;
using std::endl;
int _tmain(int argc, _TCHAR* argv[])
{
	list<int> li;
	li.push_back(1);
	list<int>::iterator p = li.end();
	cout << li.empty()<<endl;
	li.push_front(110);	
	list<int>::iterator t = li.begin();
	li.insert(li.begin(), 120);
	li.push_back(130);
	t++;
	li.insert(t, 140);
	for (list<int>::iterator i = li.begin(); i != li.end(); i++)
	{
		cout << *i << endl;
	}
	li.pop_front();
	li.pop_back();
	li.erase(t);
	cout << li.size();
	return 0;
}

