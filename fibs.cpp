#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#define MAX 100
#define NIL -1
using namespace std;

/*********************************************************
** Author: James Meehan
** Descriptin: Various differnt algorithms to obtain the
** nth fibonacci number.  Iterative, full recursive (no 
** memoization), and recursive with memoization.
***********************************************************/

//iterative fibonacci (theta(n))
int fib(int n) {
	int arr[n];
	arr[0] = 0;
	arr[1] = 1;
	for (int i = 2; i <= n; i++)
		arr[i] = arr[i-1] + arr[i-2];

	return arr[n];
}


//dynamic programming: array memo is used to store previously calculated
//fibs so repeat work is not done (theta(n)). 
/*
int memo[MAX];

void _initialize()
{
	int i;
	for (i = 0; i < MAX; i++)
		memo[i] = NIL;
}


int fib(int n) {

	_initialize();
	int f;
	if (memo[n] != NIL) {
		return memo[n];
	}
	else if (n <= 1) {
		f = n;
	}
	else
		f = fib(n-1) + fib(n-2);
	
	memo[n] = f;

	return f;
}*/

//full recursive fib (exponential time.. theta(golden ratio^n time)
/*int fib(int n) {
	if (n == 0 || n == 1)
		return n;
	else {
		return fib(n-1) + fib(n-2);
	}
}*/



int main()
{
	for (int i = 0; i < 10; i++)
	{
	cout << fib(i) << endl;
	}
}