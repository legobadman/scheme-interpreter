#include "LispEnvironment.h"


LispEnvironment* LispEnvironment::prisoner = NULL;


p_AstNode LispEnvironment::ReadOut(p_AstNode p)
{
    p_AstNode idNode, bodyNode, finalNode;

    switch( p->getTokenType() )
    {
    case DEFINE:
        idNode = p->getOneChild(0);
        bodyNode = p->getOneChild(1);
        if( idNode->getChild().size() == 0 )
        {
            // 单个标识符
            finalNode = bodyNode;
        }
        else
        {
            // 函数
        }
    default:
        break;
    }

    return finalNode;
}
