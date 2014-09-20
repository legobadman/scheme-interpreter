#ifndef _LL1_H_
#define _LL1_H_

#include "Tree.h"
#include "Token.h"
#include "macro.h"


extern p_AstNode LL1_Lisp (vector<Token>, int &);

extern p_AstNode LL1_exp (vector<Token>, int &);

extern p_AstNode LL1_Value (vector<Token>, int &);

extern p_AstNode LL1_procedure (vector<Token>, int &);

extern p_AstNode LL1_Operator (vector<Token>, int &);

extern p_AstNode LL1_Rop (vector<Token>, int &);

extern p_AstNode LL1_Boolop (vector<Token>, int &);

extern p_AstNode LL1_IF (vector<Token>, int &);

extern p_AstNode LL1_COND (vector<Token>, int &);

extern p_AstNode LL1_ConditionList (vector<Token>, int &);

extern p_AstNode LL1_LET (vector<Token>, int &);

extern p_AstNode LL1_LAMB (vector<Token>, int &);

extern std::vector<p_AstNode> LL1_exp_ (vector<Token>, int &);

extern std::vector<p_AstNode> LL1_ArguRefList (vector<Token>, int &);


extern p_AstNode LL1_DEF (vector<Token>, int &);

extern p_AstNode LL1_DEFOBJ (vector<Token>, int &);

extern std::string LL1_DEFBODY (Macro&, vector<Token>, int &);

extern p_AstNode LL1_CONS (vector<Token>, int &);
extern p_AstNode LL1_CAR (vector<Token>, int &);
extern p_AstNode LL1_CDR (vector<Token>, int &);

extern p_AstNode LL1_LIST(vector<Token>, int &);

#endif
