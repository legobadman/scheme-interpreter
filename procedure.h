#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_


p_AstNode add( vector<p_AstNode> &dataSeq );

p_AstNode sub( vector<p_AstNode> &dataSeq );

p_AstNode multiply( vector<p_AstNode> &dataSeq );

p_AstNode divide( vector<p_AstNode> &dataSeq );

p_AstNode greater_than( vector<p_AstNode>& );

p_AstNode greater_or_equal_than( vector<p_AstNode>& );

p_AstNode less_than( vector<p_AstNode>& );

p_AstNode less_or_equal_than( vector<p_AstNode>& );

p_AstNode is_equal( vector<p_AstNode>& ); 



p_AstNode define( p_AstNode defObj, p_AstNode defBody );



#endif
