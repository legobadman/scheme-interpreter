#ifndef _LL1_H_
#define _LL1_H_

#include "Tree.h"


p_AstNode LL1_Lisp();

p_AstNode LL1_exp();


p_AstNode LL1_Value();

p_AstNode LL1_procedure();

p_AstNode LL1_Operator();

p_AstNode LL1_Rop();
p_AstNode LL1_Boolop();

p_AstNode LL1_IF();
p_AstNode LL1_COND();
p_AstNode LL1_ConditionList();

p_AstNode LL1_LET();

p_AstNode LL1_LAMB();

std::vector<p_AstNode> LL1_exp_();

std::vector<p_AstNode> LL1_ArguRefList();


p_AstNode LL1_DEF();

p_AstNode LL1_DEFOBJ();

p_AstNode LL1_DEFBODY();


p_AstNode LL1_CONS();
p_AstNode LL1_CAR();
std::vector<p_AstNode> LL1_CDR();

p_AstNode LL1_LIST();

#endif
