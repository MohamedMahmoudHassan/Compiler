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
vector<string> parseTree;

void missmatch(){
	cout<<"BAD FUDJE\n";
	exit(0);
}


bool match(string u){
//	cout<<"IN "<< u << ' ' << mp[u].size()<<endl;

	for(node search_node : mp[u]){
			bool ret = 0;
			for(string s : search_node.v){
				if(i == tokens.size()){
						if(!ret)
							break;
						else
							missmatch();
				}
				parseTree.push_back(s);
//				cout<<s<<' '<<tokens[i]<<endl;
				if(trm[s] && (s == tokens[i])){
					i ++, ret = 1;
					parseTree.push_back("->\n");
				}
				else if(!trm[s] && match(s))
					ret = 1;
				else if(!ret){
					parseTree.pop_back();
					break;
				}
				else
					missmatch();
			}
			if(ret)
				return 1;
	}
	if(eps[u]){
		parseTree.push_back("eps");
		parseTree.push_back("->\n");
		return 1;
	}
	return 0;
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
	cout<<"AST***\n ";
	for(string s : parseTree)
		cout << s << ' ';
	puts("");
}
