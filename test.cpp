#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<utility>
#include<algorithm>
#include<fstream>
#include "analyser.h"
using namespace std;

int main()
{
	Lexical x("code");
	vector<string> v = x.getTokens();
	for (auto &i : v)
		cout << i << " ";
	cout << "\n\n";

}