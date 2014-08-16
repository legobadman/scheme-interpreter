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
            COND();
        else if ( str == "if" )
        {
            IF();
        }
        else if ( str == "let" )
        {
            LET();
        }
        else if ( str == "cons" )
        {
            CONS();
        }
        else if ( str == "car" )
        {
            CAR();
        }
        else if ( str == "cdr" )
        {
            CDR();
        }
        else if ( str == "list" )
        {
            LIST();
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

    else if ( str=="car" )
        procNode = CAR();

    else if ( str=="cdr" )
        procNode = CDR();

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
    if ( token.getStrval() == ")" )
        return p_AstNode();
    else if ( token.getStrval() == "(" )
    {
        match("(");
        token = TokenStream[currentIndex];
        if ( token.getStrval() == "(" )
        {
            /* predicate */
            exp();
            /* expression */
            exp();
            match(")");
            ConditionList();
        }
        else if( token.getStrval() == "else" )
        {
            match("else");
            /* expression */
            exp();
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
    match("if");
    exp();
    // then-part
    exp();
    // else-part
    exp();
}

p_AstNode COND()
{
    match("cond");
    ConditionList();
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

static p_AstNode VariableList()
{
    Token token = TokenStream[currentIndex];
    if( token.getStrval() == ")" )
        return p_AstNode();
    else
    {
        exp();
        VariableList();
    }
}

p_AstNode CONS()
{
    match("cons");
    //left part
    exp();
    //right part
    exp();

}

p_AstNode CAR()
{
    match("car");
    exp();
}

p_AstNode CDR()
{
    match("cdr");
    exp();
}

p_AstNode LIST()
{
    match("list");
    VariableList();
}


int main()
{
    string sourceCode = getSourceCodeFromStream( cin ); 
    getTokenStream( TokenStream, sourceCode );
    p_AstNode result = exp();

    cout << result << endl;
}
