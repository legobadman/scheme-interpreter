#include "Token.h"
#include "Tree.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include "LL1.h"

using namespace std;


string getSourceCodeFromStream( istream &in );
void getTokenStream( vector<Token> &Q, string sourceCode );
void outputtest( vector<Token> &Q );

p_AstNode CalculateAST( p_AstNode );

vector<Token> TokenStream;
int currentIndex = 0;

void match( TokenType type )
{
    Token token = TokenStream[currentIndex];
    if ( token.getTokenType() == type )
    {
        currentIndex++;
        cout << "match " << token.getStrval() << endl;
    }
    else
    {
        cout << "Not match " << token.getStrval() << endl;
        exit(0);
    }

}

void match( string s )
{ 
    Token token = TokenStream[currentIndex];
    if ( token.getStrval() == s )
    {
        currentIndex++;
        cout << "match " << token.getStrval() << endl;
    }
    else
    {
        cout << "Not match " << token.getStrval() << endl;
        exit(0);
    }

}

void error( string s )
{
    cerr<<"error happened in "<<s<<endl;
}


p_AstNode exp()
{
    Token token = TokenStream[currentIndex];
    string str = token.getStrval();

    p_AstNode expNode;

    if ( token.getStrval() == "(" )
    {
        match("(");
        /* special procedure */
        token = TokenStream[currentIndex];
        str = token.getStrval();
        if ( str == "cond" )
            expNode = COND();
        else if ( str == "if" )
        {
            expNode = IF();
        }
        else if ( str == "let" )
        {
            LET();
        }
        else if ( str == "cons" )
        {
            expNode = CONS();
        }
        else if ( str == "car" )
        {
            expNode = CAR();
        }
        else if ( str == "cdr" )
        {
            expNode = CDR();
        }
        else if ( str == "list" )
        {
            expNode = LIST();
        }
        else
        {
            p_AstNode procNode = procedure();
            vector<p_AstNode> valueList = exp_();
            procNode -> setChild( valueList );

            /* execute the calculation in the ast
             * and return a single astnode with the
             * final value 
             */
    
            expNode = CalculateAST( procNode );

            delete procNode;
        }
        match(")");
    }
    else if (token.getStrval()=="\"" || 
            token.getTokenType()==NUM || token.getTokenType()==ID )
    {
        expNode = Value();
    }
    else
    {
        error("exp()");
    }
    return expNode;
}

p_AstNode Value()
{
    Token token = TokenStream[currentIndex];

    p_AstNode vnode = new ASTNode(token);

    if ( token.getStrval() == "\"" )
        match("\"");
    else if ( token.getTokenType() == ID )
        match( ID );
    else if ( token.getTokenType() == NUM )
        match( NUM );
    else 
        error("Value()");

    return vnode;

}

p_AstNode procedure()
{
    Token token = TokenStream[currentIndex];

    string str = token.getStrval();

    p_AstNode   procNode;

    if ( str=="+" || str=="-" || str=="*" || str=="/" )
        procNode = Operator();

    else if ( str=="<" || str=="<=" || str==">" || str==">=" || str=="=" )
        procNode = Rop();

    else if ( str=="and" || str=="or" || str=="not" )
        procNode = Boolop();

    else if ( str=="(" )
    {
        if( TokenStream[currentIndex+1].getStrval() == "lambda" )
            procNode = LAMB();
        else
            procNode = exp();
    }

    else if ( token.getTokenType() ==ID )
    {
        match(ID);
    }

    else
        error("procedure()");

    return procNode;
}

p_AstNode Operator()
{
    Token   token = TokenStream[currentIndex];
    string str = token.getStrval();
    p_AstNode newnode = new ASTNode( token );

    if ( str == "+" )
    {
        match("+");
    }
    else if ( str == "-" )
    {
        match("-");
    }
    else if ( str == "*" )
    {
        match("*");
    }
    else if ( str == "/" )
    {
        match("/");
    }
    else
    {
        error("Operator()");
    }
    return newnode;

}

p_AstNode Rop()
{
    Token   token = TokenStream[currentIndex];
    string str = TokenStream[currentIndex].getStrval();
    
    p_AstNode newnode = new ASTNode( token );
    if ( str == "<" )
    {
        match("<");
    }
    else if ( str == "<=" )
    {
        match("<=");
    }
    else if ( str == ">" )
    {
        match(">");
    }
    else if ( str == ">=" )
    {
        match(">=");
    }
    else if ( str=="=" )
    {
        match("=");
    }
    else
    {
        error("ROP()");
    }
    return newnode;
}

p_AstNode Boolop()
{
    Token   token = TokenStream[currentIndex];
    string str = TokenStream[currentIndex].getStrval();
    p_AstNode newnode = new ASTNode( token );
    if ( str == "and" )
    {
        match("and");
    }
    else if ( str == "or" )
    {
        match("or");
    }
    else if ( str == "not" )
    {
        match("not");
    }
    else
    {
        error("Boolop()");
    }
    return newnode;
}

p_AstNode LAMB()
{
    match( "(" );
    match( "lambda" );
    match( "(" );
    ArguRefList();
    match( ")" );
    exp();
    match( ")" );

}

/* 返回引用还是值返回? */
vector<p_AstNode> exp_()
{
    Token token = TokenStream[currentIndex];

    vector<p_AstNode> valueList;

    if ( token.getStrval()=="(" || token.getStrval()=="\"" || 
            token.getTokenType()==ID || token.getTokenType()==NUM )
    {
        p_AstNode newnode = exp();
        valueList = exp_();
        valueList.insert( valueList.begin(), newnode );
    }
    else if ( token.getStrval()==")" )
        return valueList;
    else
        error("exp_()");

    return valueList;
}

/* the function try to match (<p1> <e1>) (<p2> <e2>) ... */
p_AstNode ConditionList()
{
    Token token = TokenStream[currentIndex];

    p_AstNode finalResult;

    if ( token.getStrval() == ")" )
    {
        return p_AstNode();
    }
    else if ( token.getStrval() == "(" )
    {
        match("(");
        token = TokenStream[currentIndex];
        if ( token.getStrval() == "(" )
        {
            /* predicate */
            p_AstNode boolvalue = exp();
            /* expression */
            p_AstNode curr_result = exp();
            match(")");
            p_AstNode next_result = ConditionList();

            if( boolvalue->getToken().getNumber() == 1 )
            {
                finalResult = curr_result;
            }
            else
            {
                finalResult = next_result;
            }
        }
        else if( token.getStrval() == "else" )
        {
            match("else");
            /* expression */
            finalResult = exp();
            match(")");
        }
        else
        {
            error("错误：cond子句中谓词形式不正确");
        }
    }
    else
    {
        error("cond子句形式不正确，应为(p,e)");
    }
    return finalResult;
}

p_AstNode ArguRefList()
{
    Token token = TokenStream[currentIndex];
    if ( token.getTokenType() == ID )
    {
        match(ID);
        ArguRefList();
    }
    else if ( token.getStrval() == ")" )
    {
        return p_AstNode();
    }
    else
        error("ArguRefList()");
}

/* DEF -> ( define DEFOBJ DEFBODY )
 */
p_AstNode DEF()
{
    match("(");    
    match("define");
    DEFOBJ();
    DEFBODY();
    match(")");
}

/* DEFOBJ -> ID | ( ID Argulist )
 */
p_AstNode DEFOBJ()
{
    Token token = TokenStream[currentIndex];
    if ( token.getTokenType() == ID )
        match( ID );
    else if ( token.getStrval() == "(" )
    {   
        match("(");
        match(ID);
        ArguRefList();
        match(")");
    }
    else
        error("DEFOBJ()");
}


/* DEFOBJ -> ID | ( ID Argulist )
 */
p_AstNode DEFBODY()
{
    Token token = TokenStream[currentIndex];
    if ( token.getStrval() == "(" )
    {
        Token next_token = TokenStream[currentIndex+1];
        if ( next_token.getStrval() == "define" )
        {
            DEF();
            DEFBODY();
        }
        else
        {
            exp();
            DEFBODY();
        }
    }
    else if ( token.getStrval()==")" )
    {
        return p_AstNode();
    }
    else if ( token.getTokenType()==ID )
    {
        match(ID);
    }
    else
        error("DEFBODY()");

}

p_AstNode IF()
{
    /* the '(' before if has been matched in exp() */
    p_AstNode boolean, then_result, else_result;

    match("if");
    // judgement
    boolean = exp();
        // then-part
    then_result = exp();
        // else-part
    else_result = exp();

    if( boolean->getToken().getNumber() == 1 )
        return then_result;
    else
        return else_result;
}

p_AstNode COND()
{
    match("cond");
    return ConditionList();
}

p_AstNode LocalVariablePairs()
{
    Token token = TokenStream[currentIndex];
    if ( token.getStrval() == ")" )
    {
        return p_AstNode();
    }
    else
    {
        match("(");
        //locally defined variable
        exp();
        // value to the previous defined variable
        exp();
        match(")");
        LocalVariablePairs();
    }

}

p_AstNode LET()
{
    match("let");
    match("(");

    LocalVariablePairs();

    match(")");

    exp();
}

static vector<p_AstNode> VariableList()
{
    Token token = TokenStream[currentIndex];
    vector<p_AstNode> valueList;

    if( token.getStrval() == ")" )
    {
        // empty list
        return valueList;
    }
    else
    {
        p_AstNode newnode = exp();
        valueList = VariableList();
        // keep the order
        valueList.insert( valueList.begin(), newnode );
    }

    return valueList;
}

p_AstNode CONS()
{
    match("cons");

    p_AstNode consTypeNode = new ASTNode();
    //left part
    p_AstNode leftNode = exp();
    //right part
    p_AstNode rightNode = exp();

    vector<p_AstNode> child;
    child.push_back( leftNode );
    child.push_back( rightNode );
    
    consTypeNode->setChild( child );
    consTypeNode->setNodeType( CONS_NODE );

    return consTypeNode;
}

p_AstNode CAR()
{
    match("car");
    p_AstNode consNode = exp();
    // check whether it has only two childNode
    vector<p_AstNode> Q = consNode->getChild();

    if( consNode->getNodeType() != LIST_NODE && 
        consNode->getNodeType() != CONS_NODE )
    {
        cerr << "car操作针对错误的类型。" << endl;
        exit(0);
    }
    else
    {
        // get the first element in the cons
        return Q[0];
    }
}

p_AstNode CDR()
{
    match("cdr");
    p_AstNode consNode = exp();
    // check whether it has only two childNode
    vector<p_AstNode> Q = consNode->getChild();
    if( Q.size() != 2 )
    {
        cerr << "car操作针对错误的类型。" << endl;
        exit(0);
    }
    else
    {
        // get the first element in the cons
        return Q[1];
    }

}

p_AstNode LIST()
{
    match("list");
    
    p_AstNode listTypeNode = new ASTNode();
    listTypeNode -> setNodeType( LIST_NODE );

    listTypeNode -> setChild( VariableList() );

    return listTypeNode;
}


int main()
{
    string sourceCode = getSourceCodeFromStream( cin ); 
    getTokenStream( TokenStream, sourceCode );
    p_AstNode result = exp();

    cout << result << endl;
}
