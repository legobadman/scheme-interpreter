#ifndef _TREE_H_
#define _TREE_H_

#include "Token.h"
#include <vector>

typedef class ASTNode *p_AstNode;

class ASTNode{
public:
    ASTNode()=default;
    ASTNode(const ASTNode& node){

    }
    void addChild( p_AstNode p )
    {
        child.push_back( p );
    }
    ASTNode( Token t ):token(t){}
    friend std::ostream &operator<< ( std::ostream &out, p_AstNode pt)
    {
        out << pt->token;
        return out;
    }
    Token &getToken()
    {
        return token;
    }

    void setChild(std::vector<p_AstNode> Q)
    {
        child = Q;
    }
private:
    Token token;
    std::vector<p_AstNode> child;
};



#endif
