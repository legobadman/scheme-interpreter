#ifndef _SYMBOL_TABLE_
#define _SYMBOL_TABLE_

#include <map>
#include "Tree.h"
#include "tokenType.h"
#include "macro.h"
#include <iostream>

class SymbolTable
{
public:
    /* insert the node, coresponding to the name */
    void insertID( string idName, p_AstNode node );
    void deleteID( string idName );
    void insertMacro (string name, Macro m);
    Macro searchMacro(string name); 
    void deleteMacro (string name);
    
    ~SymbolTable();

    p_AstNode getSymbol( string idName );
    
    void outputTable();

private:
    map<std::string,p_AstNode> T;
    map<std::string,Macro> T1;
};


#endif
