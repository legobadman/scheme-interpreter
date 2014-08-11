#ifndef _LL1_H_
#define _LL1_H_

#include "Tree.h"


p_AstNode Lisp();

p_AstNode exp();


p_AstNode Value();

p_AstNode procedure();

p_AstNode Operator();

p_AstNode Rop();
p_AstNode Boolop();

p_AstNode IF();
p_AstNode COND();
p_AstNode ConditionList();

p_AstNode LET();

p_AstNode LAMB();

std::vector<p_AstNode> exp_();

p_AstNode ArguRefList();


p_AstNode DEF();

p_AstNode DEFOBJ();

p_AstNode DEFBODY();


p_AstNode CONS();
p_AstNode CAR();
p_AstNode CDR();

p_AstNode LIST();

#endif
