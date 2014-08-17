#ifndef _TREE_H_
#define _TREE_H_

#include <vector>
#include <iostream>
#include "Number.h"
#include "tokenType.h"

using namespace std;

typedef class ASTNode *p_AstNode;


extern p_AstNode CalculateAST( p_AstNode ast_root );


class ASTNode{
public:
    ASTNode(){}
    ASTNode(const ASTNode& node)
    {

    }
    ASTNode( const string &s ) : name(s) {}
    ASTNode( TokenType type, const string &s ) : nodeType(type), name(s)
    {
        if( type == NUM )
        {
            number = Number(s);        
        }
    }
    ASTNode( Number n ) : number(n), nodeType( NUM )
    {
    }

    ~ASTNode()
    {
        for(int i=0; i<child.size(); i++ )
            delete child[i];
    }

    void addChild( p_AstNode p )
    {
        child.push_back( p );
    }
    
    string getName()
    {
        return name;
    }

    vector<p_AstNode> &getChild()
    {
        return child;
    }

    Number &getNumber()
    {
        return number;
    }

    void setChild(vector<p_AstNode> Q)
    {
        child = Q;
    }

    void setTokenType(TokenType t)
    {
        nodeType = t;
    }

    TokenType getTokenType()const
    {
        return nodeType;
    }

    friend std::ostream &operator<< ( std::ostream &out, p_AstNode pt)
    {
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

        default:
            out << pt->getNumber();
            break;
        }
        return out;
    }

private:

    Number number;

    TokenType nodeType;

    std::vector<p_AstNode> child;

    /* the name for procedure or number */
    /* e.g.  "+" "square" "1" ... */
    string name;
};



#endif
