#include "Token.h"
#include "Tree.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include "LL1.h"

using namespace std;

void scan( vector<Token> &Q, istream &in );
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
    if ( token.getStrval() == "(" )
    {
        match("(");
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
    else if ( str=="(" )
        LAMB();
    else if ( token.getTokenType() ==ID )
        match(ID);
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

int main()
{
    scan( TokenStream, cin ); 
//    outputtest( TokenStream );
    exp();
}