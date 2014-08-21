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


void printProcTree( p_AstNode root, string tabs )
{
    if( root->getChild().size()==0 )
    {
        cout << tabs << root->getName() << endl;
    }
    else
    {
        cout << tabs << root->getName() << endl;
        for( int i=0; i<root->getChild().size(); i++ )
        {
            printProcTree( root->getChild()[i], tabs+"\t" );
        }
    }

}

p_AstNode   deepCopy( const p_AstNode pt_source )
{
    p_AstNode newNode;
    vector<p_AstNode> child = pt_source->getChild();

    newNode = new ASTNode( pt_source->getName() );
    newNode->setTokenType ( pt_source->getTokenType() );
    newNode->setNumber( pt_source->getNumber() );

    for( int i=0; i < child.size(); i++ )
        newNode->addChild( deepCopy( child[i] ) );

    return newNode;

}


ostream &operator<< ( std::ostream &out, p_AstNode pt)
{
    vector<p_AstNode> arguList;
    switch(pt->nodeType)
    {
    case CONS: 
        out << "(" << pt->child[0]->getNumber()
            << " . " << pt->child[1]->getNumber()
            << ")";
        break;

    case LIST:
        out << "(";
        for( int i=0; i<pt->child.size(); i++ )
            out << pt->child[i]->getNumber() <<" ";
        out << ")" << endl;
        break;
        
    case NUM:
        out << pt->number;
        break;

    case ARGUMENT:
        out << pt->name;
        break;
        
    case PROC:
        out << "procdure "<< pt->getName() << "( "; 
        arguList = pt->getOneChild(0)->getChild();
        for( int i=0; i<arguList.size(); i++ )
            cout << arguList[i]->getName() << " ";
        cout << ")" << endl;
        printProcTree( pt->getOneChild(1),"\t" );
        break;

    case CAR:
            

    default:
        out << pt->getNumber();
        break;
    }
    return out;
}


