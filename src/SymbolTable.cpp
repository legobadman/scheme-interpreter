#include "SymbolTable.h"

void SymbolTable::insertID( string idName, p_AstNode node )
{
    //对于已有的建，尝试覆盖
    T.insert( pair<std::string,p_AstNode>( idName, node ));
}

void SymbolTable::deleteID( string idName )
{
    T.erase(idName);
}

p_AstNode SymbolTable::getSymbol( string idName )
{
    map<std::string, p_AstNode>::iterator it;
    it = T.find( idName );

    if( it != T.end() )
    {
        return it->second;
    }
    else
    {
        return NULL;
    }
}

void SymbolTable::outputTable()
{
    map<std::string,p_AstNode>::iterator it;
    
    for(it = T.begin(); it != T.end(); it++ )
    {
        cout << "[" << it->first << "]:  " << it->second << endl;
    }

}


SymbolTable::~SymbolTable()
{
    map<std::string,p_AstNode>::iterator it;

    //cout << "SymbolTable :: ~SymbolTable()" << endl;

    for(it = T.begin(); it != T.end(); it++ )
    {
    }
}






