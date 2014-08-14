#ifndef _TREE_H_
#define _TREE_H_

#include "Token.h"
#include <vector>

typedef class ASTNode *p_AstNode;

extern p_AstNode CalculateAST( p_AstNode ast_root );


class ASTNode{
public:
    ASTNode()=default;
    ASTNode(const ASTNode& node){

    }
    ASTNode( Token t ) : token(t){}

    ~ASTNode()
    {
        for(int i=0; i<child.size(); i++ )
            delete child[i];
    }

    void addChild( p_AstNode p )
    {
        child.push_back( p );
    }
    friend std::ostream &operator<< ( std::ostream &out, p_AstNode pt)
    {
        out << pt->token;
        return out;
    }
    Token &getToken()
    {
        return token;
    }
    std::vector<p_AstNode> &getChild()
    {
        return child;
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
