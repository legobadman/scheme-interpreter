#include "LispEnvironment.h"


LispEnvironment* LispEnvironment::prisoner = NULL;


p_AstNode LispEnvironment::ReadOut(p_AstNode p)
{
    p_AstNode idNode, bodyNode, finalNode;

    switch( p->getTokenType() )
    {
    case DEFINE:
        idNode = p->getOneChild(0);
        bodyNode = p->getOneChild(1);
        if( idNode->getChild().size() == 0 )
        {
            // 单个标识符
            finalNode = bodyNode;
        }
        else
        {
            // 函数
        }
    default:
        break;
    }

    return finalNode;
}


void LispEnvironment::pushArgumentInStack(vector<p_AstNode> &arguList)const
{
    vector<p_AstNode>::iterator it;
 
    vector<SymbolTable>::reverse_iterator T = prisoner->runTimeStack.rbegin();

    for( it = arguList.begin(); it != arguList.end(); it++ )
    {
        (*T).insertID( (*it)->getName(), (*it) );
    }
}


p_AstNode LispEnvironment::getSymbol( string idName )
{
    vector<SymbolTable>::reverse_iterator it = prisoner->runTimeStack.rbegin();

    return (*it).getSymbol( idName );
}

void LispEnvironment::InsertID( string idName, p_AstNode defNode )
{
    vector<SymbolTable>::reverse_iterator it;
    it = prisoner->runTimeStack.rbegin();
        
    (*it).insertID( idName, defNode );
}

