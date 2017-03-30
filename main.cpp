
#include <cstdlib>
#include <iostream>
#include <cilk/cilk.h>
#include "hwtimer.h"
using namespace std;


void hanoi_cilk(int n, char* src, char* aux, char* dst)
{
	string s;
    s=string(src);
    string a;
	a=string(aux);
	string d;
	d=string(dst);
	
	if (n == 0)
		return;
	else
	{
		cilk_spawn hanoi_cilk(n-1,src,dst,aux);
		//cout << "Move from " << s << " to " << d << endl; //remove comments if you want the printed output
		cilk_spawn hanoi_cilk(n-1,aux,src,dst);
		cilk_sync;
		return;
	}
	
};

void hanoi(int n, char* src, char* aux, char* dst)
{
	string s;
    s=string(src);
    string a;
	a=string(aux);
	string d;
	d=string(dst);
	
	if (n == 0)
		return;
	else
	{
		hanoi(n-1,src,dst,aux);
		//cout << "Move from " << s << " to " << d << endl; //remove comments if you want the printed output
		hanoi(n-1,aux,src,dst);
		return;
	}
	
};

int main(int argc, char* argv[])
{
	
		hwtimer_t timer;
		initTimer(&timer);
	
		int param = atoi(argv[1]);
	
		startTimer(&timer);
		
		string src = "SRC";
		string aux = "AUX";
		string dst = "DST";
		
		//Char* converter due to gcc limitations
		char* s = new char[src.size()+1];
		copy(src.begin(), src.end(), s);
		s[src.size()]='\0';
		char* a = new char[aux.size()+1];
		copy(aux.begin(), aux.end(), a);
		a[aux.size()]='\0';
		char* d = new char[dst.size()+1];
		copy(dst.begin(), dst.end(), d);
		d[dst.size()]='\0';

		
		//hanoi(param,s,a,d);  //Sequential Algorithm
		hanoi_cilk(param,s,a,d); //Parallel Version
		
		stopTimer(&timer);
		long long hanoiTime = getTimerNs(&timer);
	
		cout << "Total time: " << hanoiTime << "ns" << endl;
	
		return 0;
};
