#include "Token.h"
#include "tokenType.h"
#include "Tree.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <map>
#include <list>
#include "LL1.h"
#include "LispEnvironment.h"
#include <stdlib.h>
#include "procedure.h"

using namespace std;


string getSourceCodeFromStream( istream &in );
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
    string content, token_str;
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
//    cout << "宏展开后: "<<endl;
//    cout << p;
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

        /*
        if ( str == "cond" )
            expNode = LL1_COND(TokenStream, currentIndex);
        else if ( str == "if" )
        {
            expNode = LL1_IF(TokenStream, currentIndex);
        }
        else if (str == "let")
        {
            LL1_LET(TokenStream, currentIndex);
        }
        else if (str == "cons")
        {
            expNode = LL1_CONS(TokenStream, currentIndex);
        }
        else if (str == "car")
        {
            expNode = LL1_CAR(TokenStream, currentIndex);
        }
        else if (str == "cdr")
        {
            expNode = LL1_CDR(TokenStream, currentIndex); 
        }
        else if (str == "list")
        {
            expNode = LL1_LIST(TokenStream, currentIndex);
        }
        else if (str == "lambda")
        {
            expNode = LL1_LAMB(TokenStream, currentIndex);
        }
        else
        {
        */
        p_AstNode procNode = LL1_procedure(TokenStream, currentIndex);
        vector<p_AstNode> valueList = LL1_exp_(TokenStream, currentIndex);

        // eval(code);
        /*
        if (procNode->getTokenType() == LAMBDA)
        {
            p_AstNode realArgu = new ASTNode("");
            assert(realArgu);
            realArgu -> setChild(valueList);
            procNode -> addChild(realArgu);
            //expNode = substitudeArgument (procNode, valueList);
            expNode = procNode;
        }
        */
        //else
        //{
        procNode -> setChild (valueList);
        expNode = procNode;
        //}

        Macro   macro = env.SearchMacro(expNode->getName());
        //macro.outputtest();
        if (!macro.isEmpty())
        {
            string  code = macro.macro_span(procNode);

            vector<Token> Q;
            getTokenStream (Q, code );

            expNode = eval(Q,0);
        }
        else
        {
            expNode = interpreter(procNode);
        }
        //}
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
                //macro.outputtest();
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

        /*
        p_AstNode searchNode = env.getSymbol( token_string );
        if (searchNode -> getTokenType() == NUM)
        {
            returnNode = new ASTNode(ID, token_string);
        }
        else
        {
            returnNode = deepCopy (searchNode);
        }
        returnNode = deepCopy( searchNode );    
        if( !returnNode )
        {
            cerr << token.getStrval() << " doesn't exist" << endl;
            exit(0);
        }
        */
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
    else
    {
        match(str, TokenStream, currentIndex);

        map<string, TokenType>::iterator it;
        it = tokenTypeHash.find(str);

        if (it == tokenTypeHash.end())
            procNode = new ASTNode (PROC, str);
        else
            procNode = new ASTNode (it->second, str);
    }

    return procNode;
}

/*
p_AstNode LL1_Operator(vector<Token>TokenStream, int &currentIndex)
{
    Token   token = TokenStream[currentIndex];
    string str = token.getStrval();
    p_AstNode newnode = new ASTNode( ARITH_OP, str );

    if ( str == "+" )
    {
        match("+", TokenStream, currentIndex);
    }
    else if ( str == "-" )
    {
        match("-", TokenStream, currentIndex);
    }
    else if ( str == "*" )
    {
        match("*", TokenStream, currentIndex);
    }
    else if ( str == "/" )
    {
        match("/", TokenStream, currentIndex);
    }
    else
    {
        error("LL1_Operator()");
    }
    return newnode;

}
*/

/*
p_AstNode LL1_Rop(vector<Token>TokenStream, int &currentIndex)
{
    Token   token = TokenStream[currentIndex];
    string str = TokenStream[currentIndex].getStrval();
    
    p_AstNode newnode = new ASTNode( BOOL_OP, str );
    if ( str == "<" )
    {
        match("<", TokenStream, currentIndex);
    }
    else if ( str == "<=" )
    {
        match("<=", TokenStream, currentIndex);
    }
    else if ( str == ">" )
    {
        match(">", TokenStream, currentIndex);
    }
    else if ( str == ">=" )
    {
        match(">=", TokenStream, currentIndex);
    }
    else if ( str=="=" )
    {
        match("=", TokenStream, currentIndex);
    }
    else
    {
        error("ROP()");
    }
    return newnode;
}

p_AstNode LL1_Boolop(vector<Token>TokenStream, int &currentIndex)
{
    Token   token = TokenStream[currentIndex];
    string str = TokenStream[currentIndex].getStrval();

    p_AstNode newnode = new ASTNode( PROC, str );

    if ( str == "and" )
    {
        match("and", TokenStream, currentIndex);
    }
    else if ( str == "or" )
    {
        match("or", TokenStream, currentIndex);
    }
    else if ( str == "not" )
    {
        match("not", TokenStream, currentIndex);
    }
    else
    {
        error("LL1_Boolop()");
    }
    return newnode;
}
*/


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

    /* generate a formal argument node */
    // p_AstNode formalArgu = new ASTNode("lambda");
    
    vector<p_AstNode> arguments = LL1_ArguRefList(TokenStream, currentIndex);

    match (")", TokenStream, currentIndex );

    Macro m;
    m.put_arguments(arguments);
    
    string content = contentInBracket(TokenStream, currentIndex);
    m.set_content(content);
    //formalArgu -> setChild( arguments );

    /* 
    if( arguments.size()>0 )
    {
        env.runTimeStackPush();
        env.pushArgumentInStack( arguments );
        env.TurnOffCalculation();
    }
    */

    //p_AstNode bodyNode = LL1_exp(TokenStream, currentIndex);

    p_AstNode lambNode = new ASTNode;
    lambNode -> setTokenType (LAMBDA);
    lambNode -> setMacro (m);

    match (")", TokenStream, currentIndex );
    //lambNode -> addChild (formalArgu);
    //lambNode -> addChild (bodyNode);

    return lambNode;
}

/* 返回引用还是值返回? */
vector<p_AstNode> LL1_exp_(vector<Token>TokenStream, int &currentIndex)
{
    Token token = TokenStream[currentIndex];

    vector<p_AstNode> valueList;

    if ( token.getStrval()=="(" || token.getStrval()=="\"" || 
            token.getTokenType()==ID || token.getTokenType()==NUM )
    {
        p_AstNode newnode = LL1_exp(TokenStream, currentIndex);
        valueList = LL1_exp_(TokenStream, currentIndex);
        valueList.insert (valueList.begin(), newnode);
    }
    else if ( token.getStrval()==")" )
        return valueList;
    else
        error("LL1_exp()");

    return valueList;
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
    if ( token.getTokenType() == ID )
    {
        match( ID, TokenStream, currentIndex );
        defobj = new ASTNode( ID, token.getStrval() );
    }
    /* define procedure */
    else if ( token.getStrval() == "(" )
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
        if ( next_token.getStrval() == "define" )
        {
            string def;
            while (ts=="(" && next_token.getStrval()=="define")
            {
                def = contentInBracket (TokenStream, currentIndex);
                macro.put_preprocessing (def);
            }
            token = TokenStream[currentIndex];
            ts = token.getStrval ();
            next_token = TokenStream[currentIndex+1];
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

/*
p_AstNode LL1_DEFBODY(vector<Token>TokenStream, int &currentIndex)
{
    Token token = TokenStream[currentIndex];

    p_AstNode defbody, followingModel, calcModel;
    
    LispEnvironment env = LispEnvironment::getRunTimeEnv();

    string      ts = token.getStrval();
    TokenType   tt = token.getTokenType();

    if ( ts == "(" || tt==ID || tt==NUM )
    {
        Token next_token = TokenStream[ currentIndex + 1 ];
        if ( next_token.getStrval() == "define" )
        {
            LL1_DEF(TokenStream, currentIndex);
            defbody = LL1_DEFBODY(TokenStream, currentIndex);
        }
        else
        {
            calcModel = LL1_exp(TokenStream, currentIndex);
            
            followingModel = LL1_DEFBODY(TokenStream, currentIndex);
            if( !followingModel )
                defbody = calcModel;
            else
            {
                delete calcModel;
                defbody = followingModel;
            }
            
        }
    }
    else if ( ts == ")" )
    {
        return NULL;
    }
    else
        error("LL1_DEFBODY()");

    return defbody;    

}
*/

/*
p_AstNode LL1_IF(vector<Token>TokenStream, int &currentIndex)
{
    p_AstNode ifTree, bopNode, thenNode, elseNode;

    LispEnvironment env = LispEnvironment::getRunTimeEnv();

    match("if", TokenStream, currentIndex);
    ifTree = new ASTNode( IF, "if" );
    
    // judgement
    bopNode = LL1_exp(TokenStream, currentIndex);
        // then-part
    thenNode = LL1_exp(TokenStream, currentIndex);
        // else-part
    elseNode = LL1_exp(TokenStream, currentIndex);

    // the children of iftree in order is bopNode, thenNode, elseNode
    ifTree->addChild( bopNode );
    ifTree->addChild( thenNode );
    ifTree->addChild( elseNode );

    return ifTree;
}
*/

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


/*
p_AstNode LL1_CONS(vector<Token>TokenStream, int &currentIndex)
{
    match("cons", TokenStream, currentIndex);

    p_AstNode consTypeNode = new ASTNode (CONS, "cons" );
    //left part
    p_AstNode leftNode = LL1_exp (TokenStream, currentIndex);
    //right part
    p_AstNode rightNode = LL1_exp (TokenStream, currentIndex);

    vector<p_AstNode> child;
    child.push_back( leftNode );
    child.push_back( rightNode );
    
    consTypeNode->setChild( child );

    return consTypeNode;
}

p_AstNode LL1_CAR(vector<Token>TokenStream, int &currentIndex)
{
    match ("car", TokenStream, currentIndex);
    p_AstNode consNode = LL1_exp (TokenStream, currentIndex);
        
    p_AstNode carNode = new ASTNode(CAR,"car");
    carNode->addChild( consNode );

    return carNode;    
}

p_AstNode LL1_CDR(vector<Token>TokenStream, int &currentIndex)
{ 
    match("cdr", TokenStream, currentIndex);
    p_AstNode consNode = LL1_exp (TokenStream, currentIndex);
        
    p_AstNode cdrNode = new ASTNode(CDR,"cdr");
    cdrNode->addChild ( consNode );

    return cdrNode;    

}

p_AstNode LL1_LIST (vector<Token>TokenStream, int &currentIndex)
{
    match("list", TokenStream, currentIndex);
    
    p_AstNode listTypeNode = new ASTNode( LIST, "list" );

    listTypeNode -> setChild (VariableList(TokenStream, currentIndex));

    return listTypeNode;
}
*/

int main()
{
    LispEnvironment env = LispEnvironment::getRunTimeEnv();
    env.runTimeStackPush();
    vector<Token> TokenStream;
    int currentIndex = 0;
    initTypeHash();
    

    while (true)
    {
        env.TurnOnCalculation();

        string sourceCode = getSourceCodeFromStream( cin ); 

        getTokenStream (TokenStream, sourceCode);
        
        p_AstNode p = eval (TokenStream, currentIndex);
        if (p)
        {
            cout << p << endl;
        }

        TokenStream.clear();
        currentIndex = 0;
    }

    env.runTimeStackPop();
 
}
