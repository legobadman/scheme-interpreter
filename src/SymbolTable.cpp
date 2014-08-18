#include "SymbolTable.h"

void SymbolTable::insertID( string idName, p_AstNode node )
{
    //对于已有的建，尝试覆盖
    T.insert( pair<std::string,p_AstNode>( idName, node ));
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
