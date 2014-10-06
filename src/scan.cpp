#include "Token.h"
#include "lex.yy.h"
#include <fstream>
#include <vector>
#include <cctype>

using namespace std;
 
extern int (*ptr[ numOfRegex ])( const char* );
extern int (*ptr_action[ numOfRegex ])( const char *);

void set_functions_for_allfunctions();

void scanByWord( vector<Token> &Q, istream &in )
{
    int i;
    string word;
    TokenType type;

    set_functions_for_allfunctions();

    while( in>>word )
    {
        for( i=0; i<numOfRegex; i++ )
        {
            /* recognize? */
            if( ((*ptr[i])(word.c_str())) == 1 )
            {
                type = (TokenType)(*ptr_action[i])( word.c_str() );
                // given tokentype and word, construct token obj;
                Q.push_back( Token( type, word) ); 
                break;
            }
        }
    }
    // Q now is a token stream.
}

void outputtest( vector<Token> &Q )
{
    for( int i=0; i<Q.size(); i++ )
    {
        cout << Q[i] << endl;
    }

}

string getSourceCodeFromStream( istream &in )
{
    char c;
    /* the num of brack in the program */
    int     leftBracket, rightBracket;
    /* some code appear in the command line mode */
    string  sourceCode;

    leftBracket = rightBracket = 0;
    
    cout << endl;
    cout << ">>>  ";
    while( c = cin.get() )
    {
        if( c!='\n' && c!=' ' && c!='\t' )
            break;
        if( c=='\n' )
            cout << ">>>  ";

    }
    cin.putback(c);
    //cout << ">>> ";

    while( c = cin.get() )
    {
        leftBracket += (c=='(')? 1 : 0;
        rightBracket += (c==')')? 1 : 0;
        sourceCode += c;

        if( leftBracket==rightBracket ) break;
    }
    cin.sync();

    cin.get();
    //cin.get();
    
    return sourceCode; 
}

void getTokenStream( vector<Token> &Q, string sourceCode )
{
    set_functions_for_allfunctions();
    int startpos = 0;
    while ( startpos < sourceCode.size() )
    {
        char currchar = sourceCode[startpos];
        if ( currchar == ' ' or currchar=='\n' or currchar=='\t' )
        {
            startpos++;
            continue;
        }

        /* max-match principle */
        int match[numOfRegex];
        
        int MatchLength( const string, int (*)(const char *) );
        const string getpiece( string, int );
        
        string piece = getpiece( sourceCode, startpos );
        
        int maxindex = -1, maxValue = 0;
        for( int i=0; i<numOfRegex; i++ )
        {
            //cout << piece << endl;
            match[i] = MatchLength( piece, ptr[i] );
            if ( match[i] > maxValue )
            {
                maxValue = match[i];
                maxindex = i;
            }
        }

        /* now, we get the matched code: Code[ startpos : startpos+maxValue ] */
        if( maxValue > 0 )
        {
            const string word = sourceCode.substr( startpos, maxValue );
            TokenType type = (TokenType)((*ptr_action[maxindex])( word.c_str() ));
            Q.push_back( Token( type, word.c_str() ) );
        }else{
            cerr << "match Error!" << endl;
        }

        startpos += maxValue;
        
    }
}

/* str = getpiece(str,startpos): a string can be regard as a sequence of pieces 
 *                      splited by space,\t or \n 
 */

const string getpiece( string s, int startpos )
{
    int i;
    for ( i=startpos; i<s.size()&&(s[i]!=' ')&&(s[i]!='\n')&&(s[i]!='\t'); i++ );

    return s.substr( startpos, i-startpos );
}

int MatchLength (const string piece, int (*p)(const char *))
{
    for( int i=piece.size(); i>0; i-- )
        if( (*p)( piece.substr(0,i).c_str() ) == 1 )
            return i;

    return 0;
}


void commandLine()
{
    while(1)
    {
        vector<Token> Q;
        string sourceCode = getSourceCodeFromStream( cin );
        getTokenStream( Q, sourceCode );
        outputtest( Q );
    }
}


int main2()
{
    commandLine();

    return 0;
}
