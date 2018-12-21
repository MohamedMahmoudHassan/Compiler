#include <bits/stdc++.h>

using namespace std;

#include "analyser.h"

struct node{
    vector<string> v;

    void add(string x){
      v.push_back(x);
    }

};

map<string, vector<node> > mp;
map<string, bool> eps, trm;

string term[] = {"identifier", "const", ";", "assop", "logicop", "compop", "arithop","datatype", "=", "while", "(", ")", "{", "}", "break", "continue", "if", "elseif", "else", "for", "return", "func"};
string line, nonTrm;


void grammer_generator(){

  //identifing terminals
  for(string s : term)
    trm[s] = 1;

  //getting text that contains grammer
  freopen("grammer", "r", stdin);

  while(cin >> nonTrm){
    if(nonTrm == "$")       //end of the file
      break;
    getline(cin, line);
    while(getline(cin, line)){
      if(line == "")        //end of grammer of non-terminal
        break;
      if(line == "eps"){   //if this non-terminal accepts eps
        eps[nonTrm] = 1;
        continue;
      }

      istringstream s(line);
      string word;

      node new_node;      //each node contain one of the rules to this non-terminal
      while(s >> word)
        new_node.add(word);

      mp[nonTrm].push_back(new_node);
    }
  }
}
