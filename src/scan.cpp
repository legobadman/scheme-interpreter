#include "Token.h"
#include "lex.yy.h"
#include <fstream>
#include <vector>
#include <cctype>

using namespace std;
 
extern void set_functions_for_allfunctions();
extern int (*ptr[ numOfRegex ])( const char* );
extern int (*ptr_action[ numOfRegex ])( const char *);

void scan( vector<Token> &Q, istream &in )
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


main()
{
    ifstream inFile("f.scm");
    vector<Token> Q;
    scan( Q, cin );
    //scan(inFile);
}
