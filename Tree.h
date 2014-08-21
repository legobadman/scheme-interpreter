#ifndef _TREE_H_
#define _TREE_H_

#include <vector>
#include <iostream>
#include "Number.h"
#include "tokenType.h"

using namespace std;

typedef class ASTNode *p_AstNode;


p_AstNode CalculateAST( p_AstNode ast_root );
void printProcTree( p_AstNode, string );

p_AstNode   deepCopy( const p_AstNode );
ostream &operator<< ( std::ostream &out, p_AstNode pt);

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
    p_AstNode getOneChild( int i )
    {
        return child[i];
    }

    Number getNumber()
    {
        return number;
    }

    void setNumber( Number num )
    {
        number = num;    
    }

    void setChild( vector<p_AstNode> Q )
    {
        child = Q;
    }

    void setTokenType( TokenType t )
    {
        nodeType = t;
    }

    TokenType getTokenType()const
    {
        return nodeType;
    }

    friend ostream &operator<< ( std::ostream &out, p_AstNode pt);

private:

    Number number;

    TokenType nodeType;

    std::vector<p_AstNode> child;

    /* the name for procedure or number */
    /* e.g.  "+" "square" "1" ... */
    string name;
};



#endif
