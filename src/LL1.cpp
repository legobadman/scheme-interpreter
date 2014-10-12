#include "Token.h"
#include "tokenType.h"
#include "Tree.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <map>
#include <list>
#include "LL1.h"
#include "LispEnvironment.h"
#include <stdlib.h>
#include "procedure.h"
#include "code_gen.h"
#include <stack>

using namespace std;


stack<string> idStack;
stack<string> procStack;

string bytecode_id = "a";

string getSourceCodeFromStream( istream &in );
string getSourceCodeFromStream2( istream &in );
void getTokenStream (vector<Token> &Q, string sourceCode );
void constructTokenStream (vector<Token> &Q, list<string> codelist);
void outputtest( vector<Token> &Q );


p_AstNode CalculateAST (p_AstNode);


/* the main SymbolTable for the running stack */

void match (TokenType type, vector<Token>TokenStream, int &currentIndex)
{
    Token token = TokenStream[currentIndex];
    if ( token.getTokenType() == type )
    {
        currentIndex++;
        //cout << "match " << token.getStrval() << endl;
    }
    else
    {
        cout << "Not match " << token.getStrval() << endl;
        exit(0);
    }
}

void match (string s, vector<Token>TokenStream, int &currentIndex)
{ 
    Token token = TokenStream[currentIndex];
    if (token.getStrval() == s)
    {
        currentIndex++;
        //cout << "match " << token.getStrval() << endl;
    }
    else
    {
        cout << "Not match " << token.getStrval() << endl;
        exit(0);
    }

}

string contentInBracket (vector<Token>TokenStream, int &currentIndex)
{
    int leftBracket(0), rightBracket(0);
    Token   currentToken;
    string  content, token_str;

    currentToken = TokenStream[currentIndex];
    token_str = currentToken.getStrval();

    if (token_str != "(")
    {
        currentIndex++;
        return "";
    }
    

    content += "(";
    leftBracket++;
    currentIndex++;
    while (leftBracket != rightBracket)
    {
         token_str = TokenStream[currentIndex].getStrval();
         if (token_str == "(") leftBracket++;
         if (token_str == ")") rightBracket++;
         content += " " + token_str;
         currentIndex++;
    }
    currentIndex--;
    return content;

}

void error( string s )
{
    cerr<<"error happened in "<<s<<endl;
}

p_AstNode eval (vector<Token>TokenStream, int currentIndex)
{
    p_AstNode p, result;
    p = LL1_Lisp (TokenStream, currentIndex);
    if (p)
    {
        result = interpreter(p);
        return result;
    }
    else
        return NULL;
}

p_AstNode LL1_Lisp (vector<Token>TokenStream, int &currentIndex)
{
    Token token = TokenStream[currentIndex];
 
    p_AstNode root;
    if (token.getStrval() == "(")
    {
        Token nextToken = TokenStream[currentIndex+1]; 
        if (nextToken.getStrval() == "define")
        {
            LL1_DEF (TokenStream, currentIndex);
            return NULL;
        }
        else
            root = LL1_exp (TokenStream, currentIndex);
    }
    else
    {
        // TODO:直接输入34, 只出现3
        root = LL1_exp (TokenStream, currentIndex);
    }
    return root;
}


/*   
 *   calculate each expression from inside to outside, for instance:
 *
 *   (+ 2 (+ 3 4))   <=>     (+ 2 7)   <=>   9
 *   
 *   >>> (define (f x) (+ x 2))
 *   >>> (f (+ 1 2))
 *
 *   first, calculate (+ 1 2), and return 3 as the argument of the macro "f"
 *   (f 3)
 *   span the macro like this:    (+ 3 2)
 */



p_AstNode LL1_exp (vector<Token>TokenStream, int &currentIndex)
{
    Token token = TokenStream[currentIndex];
    string str = token.getStrval();

    LispEnvironment env = LispEnvironment::getRunTimeEnv();
    /* open the calculation */
    //env.TurnOnCalculation();

    p_AstNode expNode;

    if ( token.getStrval() == "(" )
    {
        match ("(", TokenStream, currentIndex);
        /* special procedure */
        token = TokenStream[currentIndex];
        str = token.getStrval();

        if (str == "if")
        {
            expNode = LL1_IF(TokenStream, currentIndex);
        }
        else
        {
            
            p_AstNode procNode = LL1_procedure(TokenStream, currentIndex);
//            cout << "mov "<<bytecode_id<<", " << valueList[0]->getByteCodeID() << endl;
            
            vector<p_AstNode> valueList = LL1_exp_(TokenStream, currentIndex);

            procNode -> setChild (valueList);
            expNode = procNode;

            Macro   macro = env.SearchMacro(expNode->getName());
            if (!macro.isEmpty())
            {
                string code;
                vector<string> predefList = macro.get_Pre_Def_List();
                vector<string>::const_iterator it = predefList.begin();
                vector<Token> Q;
                
                /* push stack */
                for (; it != predefList.end(); it++)
                {
                    code = (*it);
                    getTokenStream (Q, code);
                    eval(Q, 0);
                    Q.clear();
                }
                code = macro.macro_span(procNode);
                getTokenStream (Q, code );
                expNode = eval(Q, 0);
                /* pop */
            }
            else
            {
                expNode = interpreter(procNode);
            }
        }
        match(")", TokenStream, currentIndex);
    }
    else if (token.getStrval()=="\"" || 
            token.getTokenType()==NUM || token.getTokenType()==ID )
    {
        expNode = LL1_Value(TokenStream, currentIndex);
    }
    else
    {
        error("LL1_exp()");
    }
    return expNode;
}

vector<p_AstNode> LL1_exp_(vector<Token>TokenStream, int &currentIndex)
{
    Token token = TokenStream[currentIndex];
    p_AstNode   newnode;

    vector<p_AstNode> valueList;

    string str = token.getStrval();
    string id, previous_id;
    string op_in;
    TokenType   tt = token.getTokenType();

    if (str=="(" || str=="\"" || tt==ID || tt==NUM)
    {
        op_in = procStack.top();
        if (str == "(")
        {
            bytecode_id = next_id(bytecode_id);
            idStack.push(bytecode_id);
            newnode = LL1_exp(TokenStream, currentIndex);
            previous_id = idStack.top();
            idStack.pop();
            id = idStack.top();
            cout << op_in << " " << id <<", " << previous_id << endl; 
        }
        else
        {
            id = idStack.top();
            newnode = LL1_exp(TokenStream, currentIndex);
            cout << op_in << " " << id <<", " << newnode->getByteCodeID() << endl; 

        }
        
        valueList = LL1_exp_(TokenStream, currentIndex);
        valueList.insert (valueList.begin(), newnode);
    }
    else if ( token.getStrval()==")" )
        return valueList;
    else
        error("LL1_exp()");

    return valueList;
}


p_AstNode LL1_Value(vector<Token>TokenStream, int &currentIndex)
{
    Token token = TokenStream[currentIndex];
    
    string      token_string = token.getStrval();
    TokenType   token_type = token.getTokenType();

    LispEnvironment env = LispEnvironment::getRunTimeEnv();

    p_AstNode returnNode;

    if ( token_string == "\"" )
    {
        match("\"", TokenStream, currentIndex);

    }
    else if (token_type == ID)
    {
        match (ID, TokenStream, currentIndex);
        Macro macro = env.SearchMacro(token_string);
        
        if (!macro.isEmpty() && !macro.is_Procedure_Macro())
        {
            string  code = macro.macro_span();

            vector<Token> Q;
            getTokenStream (Q, code );

            returnNode = eval(Q,0);
        }
        else
        {
            returnNode = new ASTNode (ID, token_string);
            return returnNode;
        }

    }

    else if (token_type == NUM)
    {
        returnNode = new ASTNode (NUM, token_string);
        match (NUM , TokenStream, currentIndex);
    }
    else if (token_type == ARGUMENT)
    {
    }

    else 
        error("LL1_Value()");

    return returnNode;

}

p_AstNode LL1_procedure(vector<Token>TokenStream, int &currentIndex)
{
    Token token = TokenStream[currentIndex];

    string str = token.getStrval();

    p_AstNode   procNode;

    if (str == "(")
    {
        procNode = LL1_exp(TokenStream, currentIndex);
    }

    else if (str == "lambda")
    {
        procNode = LL1_LAMB(TokenStream, currentIndex);
    }
    else if (str == "if")
    {
        
    }
    else
    {
        match(str, TokenStream, currentIndex);

        map<string, TokenType>::iterator it;
        it = tokenTypeHash.find(str);

        if (it == tokenTypeHash.end())
            procNode = new ASTNode (PROC, str);
        else
            procNode = new ASTNode (it->second, str);

        switch (it->second)
        {
        case ARITH_OP:
            if (str == "+")
            {
                cout << "mov "<<bytecode_id<<", " << 0 << endl;
                procStack.push("add");             
            }else if (str == "-")
            {
                cout << "mov "<<bytecode_id<<", " << 0 << endl;
                procStack.push("sub");
            }else if (str == "*")
            {
                cout << "mov "<<bytecode_id<<", " << 1 << endl;
                procStack.push("mul");
            }else if (str == "/")
            {
                cout << "mov "<<bytecode_id<<", " << 1 << endl;
                procStack.push("div");
            }
            break;
        }

    }

    return procNode;
}


p_AstNode   LL1_IF(vector<Token>TokenStream, int &currentIndex)
{
    p_AstNode root, judgeNode, result;
    Token   token;

    match ("if", TokenStream, currentIndex);
    root = new ASTNode(IF, "if");
    judgeNode = LL1_exp(TokenStream, currentIndex);

    if (judgeNode->getNumber() > 0)
    {
        root->appendChild(new ASTNode(1));

        p_AstNode thenNode = LL1_exp(TokenStream, currentIndex);
        root->appendChild(thenNode);

        /* just scan the else part */
        Token token = TokenStream[currentIndex];
        contentInBracket(TokenStream, currentIndex);
 
        root->appendChild(new ASTNode());
    }
    else
    {
        // falseNode
        root->appendChild(new ASTNode(Number(0)));
        root->appendChild(new ASTNode());
        contentInBracket(TokenStream, currentIndex);
        p_AstNode elseNode = LL1_exp(TokenStream, currentIndex);
        root->appendChild(elseNode);

    }
    //match(")", TokenStream, currentIndex);
    /* free judgeNode */

    return root;

}


/* lambda structure (tree-like):
    
    ______
   | LAMB |
　　——————
      |       ____________
      -----> | formalArgu |
      |       ————————————
      |           |       ___________
      |           |--->  | argument1 |
      |           |      |___________|
      |           |      ___________
      |           |---> | argument2 |
      |           | .   |___________|
      |             .
      |             
      |       ______       
      -----> | body |
      |       ——————
      |          |       ____________
      |          |----> | parsedTree |
      |                 |____________|
      |
      |       __________
      -----> | realArgu |
             |__________|
                 |       ____________
                 |----> |   argu1    |
                 |      |____________|
                 |       ____________
                 |----> |   argu2    |
                 |      |____________|
                    ...
 */
p_AstNode LL1_LAMB(vector<Token>TokenStream, int &currentIndex)
{
    LispEnvironment env = LispEnvironment::getRunTimeEnv();
    match ("lambda", TokenStream, currentIndex);
    match ("(", TokenStream, currentIndex);

    vector<p_AstNode> arguments = LL1_ArguRefList(TokenStream, currentIndex);

    match (")", TokenStream, currentIndex );

    Macro m;
    m.put_arguments(arguments);
    
    string content = contentInBracket(TokenStream, currentIndex);
    m.set_content(content);

    p_AstNode lambNode = new ASTNode;
    lambNode -> setTokenType (LAMBDA);
    lambNode -> setMacro (m);

    match (")", TokenStream, currentIndex );

    return lambNode;
}


/* the function try to match (<p1> <e1>) (<p2> <e2>) ... */
p_AstNode LL1_ConditionList(vector<Token>TokenStream, int &currentIndex)
{
    Token token = TokenStream[currentIndex];

    p_AstNode finalResult;

    if ( token.getStrval() == ")" )
    {
        return p_AstNode();
    }
    else if ( token.getStrval() == "(" )
    {
        match("(", TokenStream, currentIndex);
        token = TokenStream[currentIndex];
        if ( token.getStrval() == "(" )
        {
            /* predicate */
            p_AstNode boolvalue = LL1_exp(TokenStream, currentIndex);
            /* expression */
            p_AstNode curr_result = LL1_exp(TokenStream, currentIndex);
            match(")", TokenStream, currentIndex);

            p_AstNode next_result = LL1_ConditionList(TokenStream, currentIndex);

            if( boolvalue->getNumber() == 1 )
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
            match("else", TokenStream, currentIndex);
            /* expression */
            finalResult = LL1_exp(TokenStream, currentIndex);
            match(")", TokenStream, currentIndex);
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

vector<p_AstNode> LL1_ArguRefList(vector<Token>TokenStream, int &currentIndex)
{
    Token token = TokenStream[currentIndex];
    
    vector<p_AstNode> valueList;

    if ( token.getTokenType() == ID )
    {
        match( ID, TokenStream, currentIndex );
        p_AstNode argument = new ASTNode( ARGUMENT, token.getStrval() );

        valueList = LL1_ArguRefList(TokenStream, currentIndex);

        valueList.insert( valueList.begin(), argument );
    }
    else if ( token.getStrval() == ")" )
    {
        return valueList;
    }
    else
        error("LL1_ArguRefList()");

    return valueList;
}

/* DEF -> ( define DEFOBJ DEFBODY )
 */
p_AstNode LL1_DEF(vector<Token>TokenStream, int &currentIndex)
{
    match("(", TokenStream, currentIndex);    
    match("define", TokenStream, currentIndex);
    
    LispEnvironment env = LispEnvironment::getRunTimeEnv();

    p_AstNode defobj = LL1_DEFOBJ(TokenStream, currentIndex);
    string objName = defobj->getName();
    Macro macro = Macro(objName);

    vector<p_AstNode> arguments = defobj->getChild();
    if (arguments.size()>0)
    {
        macro.put_arguments (arguments);
        macro.set_Procedure_Macro();
    }

    LL1_DEFBODY (macro, TokenStream, currentIndex);

    if (!env.SearchMacro(objName).isEmpty())
    {
        env.DeleteMacro(objName);
    }
    env.InsertMacro (objName, macro);

    match (")", TokenStream, currentIndex);
}

/* DEFOBJ -> ID | ( ID Argulist )
 */
p_AstNode LL1_DEFOBJ(vector<Token>TokenStream, int &currentIndex)
{
    Token token = TokenStream[currentIndex];
    
    p_AstNode defobj;

    LispEnvironment env = LispEnvironment::getRunTimeEnv();

    /* define symbol */
    if (token.getTokenType() == ID)
    {
        match( ID, TokenStream, currentIndex );
        defobj = new ASTNode( ID, token.getStrval() );
    }
    /* define procedure */
    else if (token.getStrval() == "(")
    {
        match( "(", TokenStream, currentIndex );
        
        token = TokenStream[ currentIndex ];
        
        match( ID, TokenStream, currentIndex );
        
        /* Using enum PROC for the user-defined procedure */
        defobj = new ASTNode( PROC, token.getStrval() );

        vector<p_AstNode> arguList;
        arguList = LL1_ArguRefList(TokenStream, currentIndex);

        defobj->setChild( arguList );


        match( ")", TokenStream, currentIndex );
    }
    else
        error("LL1_DEFOBJ()");

    return defobj;
}

string LL1_DEFBODY (Macro &macro, vector<Token>TokenStream, int &currentIndex)
{
    Token token = TokenStream[currentIndex];

    LispEnvironment env = LispEnvironment::getRunTimeEnv();

    string      ts = token.getStrval();
    TokenType   tt = token.getTokenType();

    if (ts == "(" )
    {
        Token next_token = TokenStream[ currentIndex + 1 ];
        if (next_token.getStrval() == "define")
        {
            string def;
            def = contentInBracket (TokenStream, currentIndex);
            match(")", TokenStream, currentIndex);
            macro.put_predefine (def);
            return LL1_DEFBODY (macro, TokenStream, currentIndex);
        }
        else
        {
            string content;
            content = contentInBracket (TokenStream, currentIndex);
            macro.set_content(content);
            return content;
        }
    }

    else if (tt==ID || tt==NUM)
    {
        string content;
        while ( (ts=TokenStream[currentIndex].getStrval()) != ")")
        {
             content += ts;
             currentIndex++;
        }
        macro.set_content(content);
        return content;
    }
    else
        error("LL1_DEFBODY()");

}

p_AstNode LL1_COND(vector<Token>TokenStream, int &currentIndex)
{
    match ("cond", TokenStream, currentIndex);
    return LL1_ConditionList (TokenStream, currentIndex);
}

p_AstNode LocalVariablePairs(vector<Token>TokenStream, int &currentIndex)
{
    Token token = TokenStream[currentIndex];
    if ( token.getStrval() == ")" )
    {
        return p_AstNode();
    }
    else
    {
        match ("(", TokenStream, currentIndex);
        //locally defined variable
        LL1_exp (TokenStream, currentIndex);
        // value to the previous defined variable
        LL1_exp (TokenStream, currentIndex);
        match (")", TokenStream, currentIndex);
        LocalVariablePairs(TokenStream, currentIndex);
    }

}

p_AstNode LL1_LET(vector<Token>TokenStream, int &currentIndex)
{
    match ("let", TokenStream, currentIndex);
    match ("(", TokenStream, currentIndex);

    LocalVariablePairs (TokenStream, currentIndex);

    match (")", TokenStream, currentIndex);

    LL1_exp (TokenStream, currentIndex);
}

static vector<p_AstNode> VariableList (vector<Token>TokenStream, int &currentIndex)
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
        p_AstNode newnode = LL1_exp (TokenStream, currentIndex);
        valueList = VariableList (TokenStream, currentIndex);
        // keep the order
        valueList.insert (valueList.begin(), newnode);
    }

    return valueList;
}


int main()
{
    LispEnvironment env = LispEnvironment::getRunTimeEnv();
    env.runTimeStackPush();
    vector<Token> TokenStream;
    int currentIndex = 0;
    initTypeHash();
    
    idStack.push(bytecode_id);

    while (!false)
    {
        env.TurnOnCalculation();

        string sourceCode = getSourceCodeFromStream( cin ); 

        getTokenStream (TokenStream, sourceCode);
        
        p_AstNode p = eval (TokenStream, currentIndex);
        if (p)
        {
            cout << p;
        }

        TokenStream.clear();
        currentIndex = 0;
    }
    ifstream in("wtf.scm");

    while (!in.eof())
    {
        string sourceCode = getSourceCodeFromStream2(in);
        getTokenStream (TokenStream, sourceCode);
        p_AstNode p = eval (TokenStream, currentIndex);
        if (p)
            cout << p << endl;

        TokenStream.clear();
        currentIndex = 0;

    }

    env.runTimeStackPop();
 
}
