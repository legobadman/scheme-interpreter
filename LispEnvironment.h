#ifndef _LISP_ENV_H_
#define _LISP_ENV_H_

#include <cstdlib>
#include <map>
#include "Tree.h"

class LispEnvironment
{
public:
    static LispEnvironment &getRunTimeEnv()
    {
        if( prisoner == NULL )
            prisoner = new LispEnvironment();
        return *prisoner;
    }
    void TurnOnCalculation(){
        is_directly_calculating = 1;
    }
    int  isAllowdCalculating()
    {
        return is_directly_calculating;
    }
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
