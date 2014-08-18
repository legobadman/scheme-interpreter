#ifndef _LISP_ENV_H_
#define _LISP_ENV_H_

#include <cstdlib>
#include <map>
#include <stack>
#include "Tree.h"
#include "SymbolTable.h"

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

    void TurnOnCalculation()
    {
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

    p_AstNode getSymbol( string idName );

    void InsertID( string idName, p_AstNode defNode );

    map<string,p_AstNode> getCurrentSymbolTable()
    {

    }

    void getAddress()
    {
        cout << prisoner << endl;
    }

    p_AstNode ReadOut( p_AstNode );

    void pushArgumentInStack( vector<p_AstNode> & )const;

    
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


    /* when calling define procdure, there should be
       s runTimeStack recording the argument
     */
    
    vector<SymbolTable> runTimeStack;

};




#endif
