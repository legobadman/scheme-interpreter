#include "LispEnvironment.h"
#include "procedure.h"


LispEnvironment* LispEnvironment::prisoner = NULL;



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
    
    p_AstNode p = NULL;
    for( ; it != prisoner->runTimeStack.rend(); it++ )
    {
        p = (*it).getSymbol( idName );
        if( p!=NULL )
            break;
    }

    return p;
}

void LispEnvironment::InsertID( string idName, p_AstNode defNode )
{
    vector<SymbolTable>::reverse_iterator it;
    it = prisoner->runTimeStack.rbegin();
        
    (*it).insertID( idName, defNode );
}


void LispEnvironment::runTimeStackPush()
{
    prisoner -> runTimeStack.push_back( SymbolTable() );
}

void LispEnvironment::runTimeStackPop()
{
    prisoner -> runTimeStack.pop_back();
}


void LispEnvironment::outputCurrentSymbolTable()
{
    vector<SymbolTable>::reverse_iterator it;
    it = prisoner->runTimeStack.rbegin();

    (*it).outputTable();

}

void LispEnvironment::DeleteID( string idName )
{
    vector<SymbolTable>::reverse_iterator it;
    it = prisoner->runTimeStack.rbegin();
    
    (*it).deleteID( idName );
}



