# Compiler
# First two phases of the compiler 
1- lexical analyser 

2- AST(Abtract Syntax Tree)


***********************************************
Given the language grammar in the "grammar" file (any correct grammar) and test code in the "Test" file 


the Grammar generator will parse it and build a graph using it 


if there is any lexical error  

      "UnValid syntax" will be printed followed by the place where the error was found


then the *match ()* function will try to check if the given code is correct or not


if so 

      "Accepted code" will be printed followed by the AST


if not 


      "Syntax error" will be printed followed the place where the error was found
