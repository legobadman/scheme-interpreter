#include "Tree.h"
#include "tokenType.h"
#include "LL1.h"
#include "Token.h"
#include "Number.h"
#include <string>
#include <vector>


p_AstNode CalculateAST( p_AstNode ast_root )
{
    //all the children of ast_root is a single value

    
    std::string proc = ast_root -> getName();

    p_AstNode   resultNode;
    Number      x(0), numobj;

    TokenType type = ast_root->getTokenType();
    

    if( type == ARITH_OP )
    {
        if( proc=="+" )
        {   
            std::vector<p_AstNode> child = ast_root->getChild();
            x = child[0]->getNumber();
            for( int i=1; i<child.size(); i++ )
            {
                numobj = child[i]->getNumber();
                x = x + numobj;
            }

        }
        else if( proc=="-" )
        {
            std::vector<p_AstNode> child = ast_root->getChild();
            x = child[0] -> getNumber();
            for( int i=1; i<child.size(); i++ )
            {
                numobj = child[i]->getNumber();
                x = x - numobj;
            }

        }
        else if( proc=="*" )
        {
            std::vector<p_AstNode> child = ast_root->getChild();
            x = 1;
            for( int i=0; i<child.size(); i++ )
            {
                numobj = child[i] -> getNumber();
                x = x * numobj;
            }

        }
        else if( proc=="/" )
        {   
            std::vector<p_AstNode> child = ast_root->getChild();
            x = child[0]->getNumber();
            for( int i=1; i<child.size(); i++ )
            {
                numobj = child[i]->getNumber();
                x = x / numobj;
            }

        }
        resultNode = new ASTNode( x );
    }
    
    else if( type == BOOL_OP )
    {
        Number leftValue = ast_root->getChild()[0]->getNumber();
        Number rightValue = ast_root->getChild()[1]->getNumber();
        
        int boolvalue;
        //  Do not set the boolean type, which means
        //  the "true" can be represented by 1. 
        if( proc=="<" )
            boolvalue = (leftValue < rightValue);

        else if( proc=="<=" )
            boolvalue = (leftValue <= rightValue);

        else if( proc=="=" )
            boolvalue = (leftValue == rightValue);

        else if( proc==">" )
            boolvalue = (leftValue > rightValue);
            
        else if( proc==">=" )
            boolvalue = (leftValue >= rightValue);

        resultNode = new ASTNode( Number(boolvalue) );

    }        


    return resultNode;
}
