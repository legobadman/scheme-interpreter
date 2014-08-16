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
    
    std::string op = token.getStrval();

    p_AstNode   resultNode, leftValue, rightValue;
    Number      x(0), numobj;

    if( type== OPERATOR )
    {
        if( op=="+" )
        {   
            x = 0;
            std::vector<p_AstNode> child = ast_root->getChild();
            for( int i=0; i<child.size(); i++ )
            {
                numobj = child[i]->getToken().getNumber();
                x = x + numobj;
            }

        }
        else if( op=="-" )
        {
            std::vector<p_AstNode> child = ast_root->getChild();
            x = child[0]->getToken().getNumber();
            for( int i=1; i<child.size(); i++ )
            {
                numobj = child[i]->getToken().getNumber();
                x = x - numobj;
            }

        }
        else if( op=="*" )
        {
            std::vector<p_AstNode> child = ast_root->getChild();
            x = 1;
            for( int i=0; i<child.size(); i++ )
            {
                numobj = child[i]->getToken().getNumber();
                x = x * numobj;
            }

        }
        else if( op=="/" )
        {   
            std::vector<p_AstNode> child = ast_root->getChild();
            for( int i=0; i<child.size(); i++ )
            {
                numobj = child[i]->getToken().getNumber();
                x = x / numobj;
            }

        }
        resultNode = new ASTNode( Token(x) );
    }
    
    else if( type==ROP )
    {
        leftValue = ast_root->getChild()[0];
        rightValue = ast_root->getChild()[1];
        bool x;
        if( op=="<" )
        {
            
        }
        else if( op=="<=" )
        {

        }
        else if( op=="=" )
        {

        }
        else if( op==">" )
        {

        }
        else if( op==">=" )
        {

        }
    }        

    else if( type==ID )
    {


    }

    return resultNode;
}
