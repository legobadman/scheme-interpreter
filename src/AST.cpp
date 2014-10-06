#include "Tree.h"
#include "tokenType.h"
#include "LL1.h"
#include "Token.h"
#include "Number.h"
#include <string>
#include <vector>


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

void output_treenode (string offset, p_AstNode p)
{
    vector<p_AstNode> child;

    child = p->getChild();

    if (p->getTokenType() == NUM)
    {
        cout << offset << p->getNumber() << endl;
    }
    else
    {
        cout << offset << p->getName() << endl;
    }

    if (child.size()==0)
    {
        return;
    }
    for (int i=0; i<child.size(); i++)
    {
        output_treenode(offset+"\t", child[i]);
    }
}


ostream &operator<< ( std::ostream &out, p_AstNode pt)
{
    vector<p_AstNode> arguList;
    p_AstNode procNode;

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

    case LAMBDA:
        procNode = pt->getOneChild(1);
        printProcTree( procNode, "\t" );
        break;

    case PROC:
        procNode = pt->getOneChild(1);
        arguList = pt->getOneChild(0)->getChild();
        
        out << "procdure "<< pt->getName() << "( "; 
        for( int i=0; i<arguList.size(); i++ )
            cout << arguList[i]->getName() << " ";
        cout << ")" << endl;

        printProcTree( procNode, "\t" );
        break;


    case CAR:
            

    default:
        out << pt->getNumber();
        break;
    }
    //output_treenode("", pt); 
    
    return out;
}


