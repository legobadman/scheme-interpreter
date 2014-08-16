#include "Tree.h"
#include "LL1.h"
#include "Token.h"
#include "Number.h"
#include <string>
#include <vector>


p_AstNode CalculateAST( p_AstNode ast_root )
{
    //all the children of ast_root is a single value

    Token token = ast_root->getToken();
    TokenType type = token.getTokenType();
    
    std::string proc = token.getStrval();

    p_AstNode   resultNode;
    Number      x(0), numobj;

    if( type== OPERATOR )
    {
        if( proc=="+" )
        {   
            std::vector<p_AstNode> child = ast_root->getChild();
            x = child[0]->getToken().getNumber();
            for( int i=1; i<child.size(); i++ )
            {
                numobj = child[i]->getToken().getNumber();
                x = x + numobj;
            }

        }
        else if( proc=="-" )
        {
            std::vector<p_AstNode> child = ast_root->getChild();
            x = child[0]->getToken().getNumber();
            for( int i=1; i<child.size(); i++ )
            {
                numobj = child[i]->getToken().getNumber();
                x = x - numobj;
            }

        }
        else if( proc=="*" )
        {
            std::vector<p_AstNode> child = ast_root->getChild();
            x = 1;
            for( int i=0; i<child.size(); i++ )
            {
                numobj = child[i]->getToken().getNumber();
                x = x * numobj;
            }

        }
        else if( proc=="/" )
        {   
            std::vector<p_AstNode> child = ast_root->getChild();
            x = child[0]->getToken().getNumber();
            for( int i=1; i<child.size(); i++ )
            {
                numobj = child[i]->getToken().getNumber();
                x = x / numobj;
            }

        }
        resultNode = new ASTNode( Token(x) );
    }
    
    else if( type==ROP )
    {
        int leftValue = ast_root->getChild()[0]->getToken().getNumber().getInteger();
        int rightValue = ast_root->getChild()[1]->getToken().getNumber().getInteger();
        
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

        resultNode = new ASTNode( Token(boolvalue) );

    }        

    else if( type==ID )
    {
        int boolvalue;
        if( proc=="and" )
        {   
            std::vector<p_AstNode> child = ast_root->getChild();
            boolvalue = 1;
            for( int i=0; i<child.size(); i++ )
            {
                int bvalue = child[i]->getToken().getNumber().getInteger();
                boolvalue = boolvalue && bvalue;
            }
        }
        else if( proc=="or" )
        {
            std::vector<p_AstNode> child = ast_root->getChild();
            boolvalue = 0;
            for( int i=0; i<child.size(); i++ )
            {
                int bvalue = child[i]->getToken().getNumber().getInteger();
                boolvalue = boolvalue || bvalue;
            }

        }
        else if( proc=="not" )
        {
            std::vector<p_AstNode> child = ast_root->getChild();
            boolvalue = !child[0]->getToken().getNumber().getInteger(); 
            
        }

        resultNode = new ASTNode( Token(boolvalue) );
    }

    return resultNode;
}
