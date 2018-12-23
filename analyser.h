#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<utility>
#include<algorithm>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include <sstream>      // std::stringstream, std::stringbuf

using namespace std;

#ifndef ANALYSER
#define ANALYSER
/*

make sure that the code returns a vector of string that contains the tokens
or
return a string that contains a single string  "notValid" which means that a syntax error has been found

*/
class Lexical
{
public:
	Lexical(string fileName)
	{
		file.open(fileName.c_str());
		fillStr();
		fillTok();


	}
	void fillTok()
	{
		tok.insert({ "int", "datatype" });
		tok.insert({ "float", "datatype" });
		tok.insert({ "double", "datatype" });
		tok.insert({ "long", "datatype" });
		tok.insert({ "short", "datatype" });
		tok.insert({ "char", "datatype" });
		tok.insert({ "string", "datatype" });
		tok.insert({ "bool", "datatype" });
		tok.insert({ "void", "datatype" });
		tok.insert({ "if", "if" });
		tok.insert({ "do", "do" });
		tok.insert({ "while", "while" });
		tok.insert({ "for" , "for" });
		tok.insert({ "else" , "else" });
		tok.insert({ "elseif" , "elseif" });
		tok.insert({ "=" , "=" });
		tok.insert({ "/=" , "assop" });
		tok.insert({ "-=" , "assop" });
		tok.insert({ "+=" , "assop" });
		tok.insert({ "*=" , "assop" });
		tok.insert({ "%=" , "assop" });
		tok.insert({ "==" , "compop" });
		tok.insert({ "!=" , "compop" });
		tok.insert({ ">" , "compop" });
		tok.insert({ "<" , "compop" });
		tok.insert({ ">=" , "compop" });
		tok.insert({ "<=" , "compop" });
		tok.insert({ "+", "arithop" });
		tok.insert({ "-", "arithop" });
		tok.insert({ "*", "arithop" });
		tok.insert({ "/", "arithop" });
		tok.insert({ "%", "arithop" });
		tok.insert({ "{" , "{" });
		tok.insert({ "}" , "}" });
		tok.insert({ "(" , "(" });
		tok.insert({ ")" , ")" });
		tok.insert({ ";" , ";" });
		tok.insert({ "func" , "func" });
		tok.insert({ "return" , "return" });
		tok.insert({ "-1", "identifier" });
		buildTokens();

	}
	void fillStr()
	{
		getline(this->file, this->allFile, '\0'); // read all  the file and save it in one string
	}
	bool isvalidchar(char x)
	{
		if (x == '_' || x == '.' || x =='"' )
			return 1;
		return ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z') || (x >= '0' && x <= '9'));
	}
	int isconst(string & checker)
	{
		
		bool allDigits = 1 , dotFound = 0;
		for (int i = 0; i < (int) checker.size(); i++)
		{
			if (!((checker[i] >= '0' && checker[i] <= '9') ||  (checker[i] == '.' )  ))
			{
				allDigits = 0;
				break;
			}
			if (checker[i] == '.' && dotFound == 1)
			{
				
				return -1;
			}
			if (checker[i] == '.')
				dotFound = 1;
			
		}
		if (allDigits)
			return 1;
		
		if (checker[0] == '"')
		{
			if (checker[checker.size() - 1] == '"' && checker.size() > 1)
				return 1;
			else return -1;
		}
		return 0;
	}
	void buildTokens()
	{

		
		// function to seperat the input and build the tokens vector
		string seperators = "; !=><}{()+-/*\n\t"; // string that contain all the seperators
		string holder = ""; // tmp string to fill it as we traverse the input file char by char
		string eqseprators = "><=/%+-*/";
		for (int currentChar = 0; currentChar < (int)allFile.size(); currentChar++)
		{


			if (seperators.find(allFile[currentChar]) == string::npos)
			{
				if (isvalidchar(allFile[currentChar]))
					holder += allFile[currentChar];
				else {
					tokens.clear();
					tokens.push_back("notValid");
					return;
				}
			}
			else
			{
				if (tok.find(holder) != tok.end()) // the current string is in my tokens
				{
					tokens.push_back(tok[holder]); // adding the token to the vector of tokens


				}
				else {
					// the current is identifier
					if (holder.size()) {
						if (isconst(holder) == 1)
							tokens.push_back("const");
						else if (isconst(holder) == 0)
							tokens.push_back(tok["-1"]);
						else {
							tokens.clear();
							tokens.push_back("notValid");
							return;
						}

					}
				}
				holder = "";  // clearing the string to be filled again
				
				if (allFile[currentChar] == '!')
				{
					if (currentChar < (int) allFile.size() - 1)
					{
						if (allFile[currentChar + 1] == '=')
						{
							tokens.push_back(tok["!="]);
							currentChar++;
						}
						else
						{

							tokens.clear();
							tokens.push_back("notValid");
							return;
						}

					}
					else {

						tokens.clear();
						tokens.push_back("notValid");
						return;
					}
				}
				else if (eqseprators.find(allFile[currentChar]) != string::npos)
				{
					string x = "";
					x += allFile[currentChar];
					if (currentChar < (int) allFile.size() - 1)
					{

						if (allFile[currentChar + 1] == '=')
						{
							x += "=";
							tokens.push_back(tok[x]);
							currentChar++;
						}
						else tokens.push_back(tok[x]);

					}
					else tokens.push_back(tok[x]);   
				}
				else if (allFile[currentChar] != ' ' &&  allFile[currentChar] != '\n' && allFile[currentChar] != '\t')
				{
					string x = "";
					x += allFile[currentChar];
					tokens.push_back(tok[x]);
				}
			}

		}
		
	}
	vector<string> getTokens()
	{
		return tokens;
	}
private:
	fstream file;
	string allFile;
	map<string, string> tok;
	vector<string> tokens;
	 
};




#endif // !ANALYSER
