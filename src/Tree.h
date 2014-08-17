#ifndef _TREE_H_
#define _TREE_H_

#include "Token.h"
#include <vector>

typedef class ASTNode *p_AstNode;

extern p_AstNode CalculateAST( p_AstNode ast_root );

enum NodeType{ BOOLEAN_NODE, NUM_NODE, PROC_NODE, CONS_NODE, LIST_NODE };

class ASTNode{
public:
    ASTNode(){}
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
        switch(pt->type)
        {
        case CONS_NODE: 
            out << "(" << pt->child[0]->getToken().getNumber()
                << " . " << pt->child[1]->getToken().getNumber()
                << ")";
            break;
        default:
            out << pt->getToken().getNumber();
            break;
        }
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

    void setNodeType(NodeType t)
    {
        type = t;
    }

private:
    Token token;

    NodeType type;

    std::vector<p_AstNode> child;
};



#endif
