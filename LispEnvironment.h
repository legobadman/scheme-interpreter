#ifndef _LISP_ENV_H_
#define _LISP_ENV_H_

#include <cstdlib>
#include <map>
//#include <pair>
#include "Tree.h"

class LispEnvironment
{
public:
    static LispEnvironment &getRunTimeEnv()
    {
        if( prisoner == NULL )
        {
            cout << "init env...." << endl;
            prisoner = new LispEnvironment();
        }
        return *prisoner;
    }
    void TurnOnCalculation(){
        prisoner -> is_directly_calculating = 1;
    }
    void TurnOffCalculation()
    {
        prisoner -> is_directly_calculating = 0;
    }
    int  isAllowdCalculating()
    {
        return prisoner -> is_directly_calculating;
    }
    p_AstNode SearchSymbol( string idName )
    {
        map<string, p_AstNode>::iterator it;
        it = prisoner -> SymbolTable.find( idName );

        if( it != SymbolTable.end() )
        {
            return it->second;
        }
        else
        {
            return NULL;
        }
    }
    void InsertID( string idName, p_AstNode defNode )
    {
        map< string, p_AstNode >::iterator it;

        it = prisoner -> SymbolTable.find( idName );

        if( it != prisoner->SymbolTable.end() )
        {
            prisoner -> SymbolTable.erase( it );
        }
        prisoner -> SymbolTable.insert( pair<string,p_AstNode>( idName, defNode ));
    }

    map<string,p_AstNode> getSymbolTable()
    {
        return prisoner->SymbolTable;
    }
    void getAddress()
    {
        cout << prisoner << endl;
    }
    p_AstNode ReadOut( p_AstNode );


private:
    static LispEnvironment *prisoner;
    LispEnvironment(){}

    /* in order to distinguish whether to execute the 
     * calculation without generating a parsed Tree.
     * 1 means that we can work out such as (+ a b) 
     * directly.
     
     * otherwise, for example, defining a
     * function like (f x y) (+ x y), can not calculate
     * because it's not a expression for calculating, we
     * will generate a parsed tree as a function model
     */
    int is_directly_calculating; 

    /* symbol table for the whole runtime */
    map<string, p_AstNode> SymbolTable;
};




#endif
