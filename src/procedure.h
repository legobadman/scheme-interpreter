#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#include "Tree.h"


p_AstNode interpreter( p_AstNode );



p_AstNode add( vector<p_AstNode> &);

p_AstNode sub( vector<p_AstNode> &);

p_AstNode multiply( vector<p_AstNode> &);

p_AstNode divide( vector<p_AstNode> &);

p_AstNode greater_than( vector<p_AstNode>& );

p_AstNode greater_or_equal_than( vector<p_AstNode>& );

p_AstNode less_than( vector<p_AstNode>& );

p_AstNode less_or_equal_than( vector<p_AstNode>& );

p_AstNode is_equal( vector<p_AstNode>& ); 


#endif
