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


treenode exp()
{
    Token token = TokenStream[currentIndex];
    string str = token.getStrval();

    if ( token.getStrval() == "(" )
    {
        match("(");
        /* special procedure */
        token = TokenStream[currentIndex];
        if ( token.getStrval() == "cond" )
            COND();
        else if ( token.getStrval() == "if" )
            IF();
        else if ( token.getStrval() == "let" )
            LET();
        else
            procedure();

        exp_();
        match(")");
    }
    else if (token.getStrval()=="\"" || 
            token.getTokenType()==NUM || token.getTokenType()==ID )
    {
        Value();
    }
    else
    {
        error("exp()");
    }
}

treenode Value()
{
    Token token = TokenStream[currentIndex];
    if ( token.getStrval() == "\"" )
        match("\"");
    else if ( token.getTokenType() == ID )
        match( ID );
    else if ( token.getTokenType() == NUM )
        match( NUM );
    else 
        error("Value()");

}

treenode procedure()
{
    Token token = TokenStream[currentIndex];

    string str = token.getStrval();

    if ( str=="+" || str=="-" || str=="*" || str=="/" )
        Operator();
    else if ( str=="<" || str=="<=" || str==">" || str==">=" || str=="=" )
        Rop();
    else if ( str=="and" || str=="or" || str=="not" )
        Boolop();
    else if ( str=="(" )
    {
        if( TokenStream[currentIndex+1].getStrval() == "lambda" )
            LAMB();
        else
            exp();
    }
    else if ( token.getTokenType() ==ID )
    {
        match(ID);
    }
    else
        error("procedure()");
}

treenode Operator()
{
    string str = TokenStream[currentIndex].getStrval();
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

}

treenode Rop()
{
    string str = TokenStream[currentIndex].getStrval();
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
}

treenode Boolop()
{
    string str = TokenStream[currentIndex].getStrval();
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
}

treenode LAMB()
{
    match( "(" );
    match( "lambda" );
    match( "(" );
    ArguRefList();
    match( ")" );
    exp();
    match( ")" );

}

treenode exp_()
{
    Token token = TokenStream[currentIndex];

    if ( token.getStrval()=="(" || token.getStrval()=="\"" || 
            token.getTokenType()==ID || token.getTokenType()==NUM )
    {
        exp();
        exp_();
    }
    else if ( token.getStrval()==")" )
        return treenode();
    else
        error("exp_()");

}

/* the function try to match (<p1> <e1>) (<p2> <e2>) ... */
treenode ConditionList()
{
    Token token = TokenStream[currentIndex];
    if ( token.getStrval() == ")" )
        return treenode();
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

treenode ArguRefList()
{
    Token token = TokenStream[currentIndex];
    if ( token.getTokenType() == ID )
    {
        match(ID);
        ArguRefList();
    }
    else if ( token.getStrval() == ")" )
    {
        return treenode();
    }
    else
        error("ArguRefList()");
}

/* DEF -> ( define DEFOBJ DEFBODY )
 */
treenode DEF()
{
    match("(");    
    match("define");
    DEFOBJ();
    DEFBODY();
    match(")");
}

/* DEFOBJ -> ID | ( ID Argulist )
 */
treenode DEFOBJ()
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
treenode DEFBODY()
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
        return treenode();
    }
    else if ( token.getTokenType()==ID )
    {
        match(ID);
    }
    else
        error("DEFBODY()");

}

treenode IF()
{
    /* the '(' before if has been matched in exp() */
    match("if");
    exp();
    // then-part
    exp();
    // else-part
    exp();
}

treenode COND()
{
    match("cond");
    ConditionList();
}

treenode LocalVariablePairs()
{
    Token token = TokenStream[currentIndex];
    if ( token.getStrval() == ")" )
    {
        return treenode();
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

treenode LET()
{
    match("let");
    match("(");

    LocalVariablePairs();

    match(")");

    exp();
}


int main()
{
    string sourceCode = getSourceCodeFromStream( cin ); 
    getTokenStream( TokenStream, sourceCode );
//    outputtest( TokenStream );
    exp();
}
