#include "Tree.h"
#include "LL1.h"
#include "LispEnvironment.h"
#include "procedure.h"
#include <cstdlib>

#include <iostream>
using namespace std;


p_AstNode add( vector<p_AstNode> &ValueList )
{
    LispEnvironment env = LispEnvironment::getRunTimeEnv();
        
    vector<p_AstNode>::iterator it;
    p_AstNode   element;
    Number  sum(0);
    
    it = ValueList.begin();
    for( ; it != ValueList.end(); it++ )
    {
        element = (*it);
        sum = sum + interpreter( element )->getNumber();
    }
    return new ASTNode( sum );
}

p_AstNode sub( vector<p_AstNode> &ValueList )
{
    LispEnvironment env = LispEnvironment::getRunTimeEnv();
        
    vector<p_AstNode>::iterator it;
    
    p_AstNode   element;
    Number  result;
    
    it = ValueList.begin();
    result = (*it)->getNumber();

    for( ++it; it != ValueList.end(); it++ )
    {
        element = (*it);
        result = result - interpreter( element )->getNumber();
    }

    return new ASTNode( result );

}

p_AstNode multiply( vector<p_AstNode> &ValueList )
{
    LispEnvironment env = LispEnvironment::getRunTimeEnv();
        
    vector<p_AstNode>::iterator it;
    p_AstNode   element;
    Number  product(1);
    
    it = ValueList.begin();
    for( ; it != ValueList.end(); it++ )
    {
        element = (*it);
        product = product * interpreter( element )->getNumber();
    }
    return new ASTNode( product );
}


p_AstNode divide( vector<p_AstNode> &ValueList )
{
    LispEnvironment env = LispEnvironment::getRunTimeEnv();
        
    vector<p_AstNode>::iterator it;
    
    p_AstNode   element;
    Number  result;
    
    it = ValueList.begin();
    result = (*it)->getNumber();

    for( ++it; it != ValueList.end(); it++ )
    {
        element = (*it);
        result = result / interpreter( element )->getNumber();
    }

    return new ASTNode( result );

}

p_AstNode interpreter( p_AstNode root )
{
    string rootName = root->getName();
    vector<p_AstNode> &childList = root->getChild();
    
    LispEnvironment env = LispEnvironment::getRunTimeEnv();

    p_AstNode   result;

    switch( root->getTokenType() )
    {
    case ID:
        result = env.getSymbol( rootName );
        if( !result )
        {
            cerr << "undefined symbol: " << rootName << endl;
            exit(0);
        }
        //delete root;
        break;

    case NUM:
        result = root;
        break;

    case ARITH_OP:
        if( rootName == "+" )
        {
            result = add( childList );
        }
        else if( rootName == "-" )
        {
            result = sub( childList );
        }
        else if( rootName == "*" )
        {
            result = multiply( childList );
        }
        else if( rootName == "/" )
        {
            result = divide( childList );
        }

        for(int i=0; i<childList.size(); i++ )
            delete childList[i];
        childList.clear();

        break;
    case BOOL_OP:
        if( rootName == "<" )
        {

        }
        else if( rootName == "<=" )
        {

        }
        else if( rootName == ">" )
        {

        }
        else if( rootName == ">=" )
        {

        }
        else if( rootName == "=" )
        {
            
        }
        break;
    case PROC:
        break;
    }

    return result;
}
