#include "Tree.h"
#include "LL1.h"
#include "LispEnvironment.h"
#include "procedure.h"
#include <cstdlib>

#include <iostream>
using namespace std;


void getTokenStream (vector<Token> &Q, string sourceCode );

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

    p_AstNode   result, temp;
    p_AstNode   childNode, consNode, assigned;
    vector<p_AstNode> valueList;
    Macro       m;
    string      code, content;
    vector<Token>   Q;

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
          result = add( childList );
        
        else if( rootName == "-" )
          result = sub( childList );
        
        else if( rootName == "*" )
          result = multiply( childList );
        
        else if( rootName == "/" )
          result = divide( childList );

        for(int i=0; i<root->getChild().size(); i++ )
            delete root->getOneChild( i );
        
        root->getChild().clear();

        break;

    case BOOL_OP:
        if( rootName == "<" )
          result = less_than( childList );
        
        else if( rootName == "<=" )
          result = less_or_equal_than( childList );
        
        else if( rootName == ">" )
          result = greater_than( childList );
        
        else if( rootName == ">=" )
          result = greater_or_equal_than( childList );
        
        else if( rootName == "=" )
          result = is_equal( childList );

        break;
    
    case ARGUMENT:
        result = root;
        break;

    case CONS:
        result = root;
        break;

    case LIST:
        result = root;
        break;

    case CAR:
            
    case CDR:
        
        consNode = root->getOneChild(0);        
        if( consNode->getTokenType() != LIST &&
            consNode->getTokenType() != CONS )
        {
            cerr << "cdr操作针对错误的类型。" << endl;
            exit(0);
        }
        else
        {
            vector<p_AstNode> valueList = consNode->getChild();
            if( root->getTokenType() == CAR )
            {
                // return the first element.
                result = valueList[0]; 
            }
            else
            {
                result = new ASTNode( LIST, "cons" );
                vector<p_AstNode> subList;
                subList.assign( valueList.begin()+1, valueList.end() );

                result->setChild( subList );
            }
        }
        break;


    case IF:
        /* reguard any positive as true symbol */
        temp = interpreter (root->getOneChild(0));
        if (temp->getNumber() > 0)
          result = interpreter(root->getOneChild(1)); 
        else
          result = interpreter(root->getOneChild(2));
        break;

    case LAMBDA:
        m       = root->getMacro();
        content = m.get_content();
        if (root->getChild().size() == 0)
            result = root;
        else
        {
            code = m.macro_span(root);
            getTokenStream(Q, code);

            result = eval(Q, 0);

        }
 
    break;

    }

    return result;
}



p_AstNode greater_than( vector<p_AstNode> &ValueList )
{
    LispEnvironment env = LispEnvironment::getRunTimeEnv();
        
    vector<p_AstNode>::iterator it;
    
    p_AstNode   last_element, current_element;
    Number  lastNum, currentNum;
    
    it = ValueList.begin();
    lastNum = interpreter( (*it) )->getNumber();

    for( ++it; it != ValueList.end(); it++ )
    {
        current_element = (*it);
        currentNum = interpreter( current_element )->getNumber();
        if( lastNum <= currentNum )
        {
            return new ASTNode( Number(0) );
        }

        lastNum = currentNum;
    }

    return new ASTNode( Number(1) );

}


p_AstNode greater_or_equal_than( vector<p_AstNode> &ValueList )
{
    LispEnvironment env = LispEnvironment::getRunTimeEnv();
        
    vector<p_AstNode>::iterator it;
    
    p_AstNode   last_element, current_element;
    Number  lastNum, currentNum;
    
    it = ValueList.begin();

    lastNum = interpreter( (*it) )->getNumber();
    for( ++it; it != ValueList.end(); it++ )
    {
        current_element = (*it);
        currentNum = interpreter( current_element )->getNumber();
        if( lastNum < currentNum )
            return new ASTNode( Number(0) );

        lastNum = currentNum;
    }

    return new ASTNode( Number(1) );

}


p_AstNode less_than( vector<p_AstNode>& ValueList)
{
    LispEnvironment env = LispEnvironment::getRunTimeEnv();
        
    vector<p_AstNode>::iterator it;
    
    p_AstNode   last_element, current_element;
    Number  lastNum, currentNum;
    
    it = ValueList.begin();

    lastNum = interpreter( (*it) )->getNumber();
    for( ++it; it != ValueList.end(); it++ )
    {
        current_element = (*it);
        currentNum = interpreter( current_element )->getNumber();
        if( lastNum >= currentNum )
        {
            return new ASTNode( Number(0) );
        }

        lastNum = currentNum;
    }

    return new ASTNode( Number(1) );

}

p_AstNode less_or_equal_than( vector<p_AstNode> &ValueList )
{
    LispEnvironment env = LispEnvironment::getRunTimeEnv();
        
    vector<p_AstNode>::iterator it;
    
    p_AstNode   last_element, current_element;
    Number  lastNum, currentNum;
    
    it = ValueList.begin();
    lastNum = interpreter( (*it) )->getNumber();

    for( ++it; it != ValueList.end(); it++ )
    {
        current_element = (*it);
        currentNum = interpreter( current_element )->getNumber();
        if( lastNum > currentNum )
        {
            return new ASTNode( Number(0) );
        }

        lastNum = currentNum;
    }

    return new ASTNode( Number(1) );

}

p_AstNode is_equal( vector<p_AstNode> &ValueList )
{
    LispEnvironment env = LispEnvironment::getRunTimeEnv();
        
    vector<p_AstNode>::iterator it;
    
    p_AstNode   last_element, current_element;
    Number  lastNum, currentNum;
    
    it = ValueList.begin();
    lastNum = interpreter( (*it) )->getNumber();

    for( ++it; it != ValueList.end(); it++ )
    {
        current_element = (*it);
        currentNum = interpreter( current_element )->getNumber();
        if( currentNum != lastNum )
        {
            return new ASTNode( Number(0) );
        }

        lastNum = currentNum;
    }

    return new ASTNode( Number(1) );

}

p_AstNode And( vector<p_AstNode> &ValueList )
{
}

p_AstNode Or( vector<p_AstNode> &ValueList )
{
}

p_AstNode Not( vector<p_AstNode> &ValueList )
{

}





