#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<utility>
#include<algorithm>
#include<fstream>
using namespace std;

#include "analyser.h"
#include "grammer_generator.h"

int i = 0;
Lexical text("Test");
vector<string> tokens = text.getTokens();

void missmatch(){
	cout<<"BAD FUDJE\n";
	exit(0);
}


bool match(string u){
	cout<<"IN "<< u << ' ' << mp[u].size() << endl;
	for(node search_node : mp[u]){
			bool ret = 0;
			for(string s : search_node.v){
				if(i == tokens.size())
					missmatch();
				cout<<s<<' '<<tokens[i]<<endl;
				if((trm[s] && (s == tokens[i])) || (!trm[s] && match(s)) )
					i += trm[s], ret = 1;
				else if(!ret)
					break;
				else
					missmatch();

			}
			if(ret)
				return 1;
	}
	return eps[u];
}

int main()
{
	//freopen("txt.out", "w", stdout);
	tokens.push_back("$");
	for(string s : tokens)
		cout << s << ' ';
	puts("");
	grammer_generator();
	match("S");
	if(i + 1 != tokens.size())
		missmatch();
	cout<<"BIG FUDJE\n";
}
