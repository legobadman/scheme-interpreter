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

bool LispEnvironment::isSymbolInCurrentStack( string idName )
{
    vector<SymbolTable>::reverse_iterator it = prisoner->runTimeStack.rbegin();
    return (*it).getSymbol( idName );
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


void LispEnvironment::InsertID( string idName, p_AstNode defNode )
{
    vector<SymbolTable>::reverse_iterator it;
    it = prisoner->runTimeStack.rbegin();
        
    (*it).insertID( idName, defNode );
}


void LispEnvironment::InsertMacro (string name, Macro m)
{
    vector<SymbolTable>::reverse_iterator it;
    it = prisoner->runTimeStack.rbegin();

    (*it).insertMacro (name, m);
}

Macro LispEnvironment::SearchMacro (string name)
{
    vector<SymbolTable>::reverse_iterator it = prisoner->runTimeStack.rbegin();
    
    Macro m;
    for( ; it != prisoner->runTimeStack.rend(); it++ )
    {
        m = (*it).searchMacro(name);
        if (!m.isEmpty())
            break;
    }
    return m;
}

void LispEnvironment::DeleteMacro (string name)
{
    vector<SymbolTable>::reverse_iterator it;
    it = prisoner->runTimeStack.rbegin();
    
    (*it).deleteMacro (name);
}


