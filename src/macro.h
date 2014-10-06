#ifndef MACRO_H_
#define MACRO_H_

#include <string>
#include <map>
#include <vector>
#include <cassert>
#include <vector>
//#include "Tree.h"

#include <iostream>

using namespace std;

typedef class ASTNode *p_AstNode;

class Macro
{
public:
    Macro(string na="", string con="") : name(na), content(con), is_proc(false){}

    string macro_span (p_AstNode p);

    string macro_span ();

    bool isEmpty();
    void put_arguments (vector<p_AstNode> arguments);
    void put_preprocessing (string declare);
    void set_content (string c);
    void outputtest ();

    bool is_Procedure_Macro ();
    void set_Procedure_Macro ();

private:
    string  name;
    string  content;           //e.g.   (+ x 2)
    map<string,string> argumap;
    vector<string> formal_argu;
    vector<string> preprocessing;
    bool    is_proc;           // e.g for macro (abs 2) is_proc should be set to 1
};

#endif
