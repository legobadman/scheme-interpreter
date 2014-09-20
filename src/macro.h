#ifndef MACRO_H_
#define MACRO_H_

#include <string>
#include <map>
#include <vector>
#include <cassert>
#include "Tree.h"

#include <iostream>


class Macro
{
public:
    Macro(string na="", string con="") : name(na), content(con), is_proc(false){}

    string macro_span (p_AstNode p)
    {
        vector<p_AstNode> realArguments = p->getChild();
        for (int i=0; i<realArguments.size(); i++)
        {
            argumap[formal_argu[i]] = realArguments[i]->getName();
        }
        map<string, string>::iterator it;
        string source_code = content;
        for (it = argumap.begin(); it != argumap.end(); it++ )
        {
            //cout << it->first << " " << it->second << endl;
            string old_value, new_value;
            old_value = it->first;
            new_value = it->second;
            for (string::size_type pos(0); pos!=string::npos; pos+=new_value.length())
            {
                if ((pos = source_code.find(old_value,pos)) != string::npos)
                    source_code.replace(pos, old_value.length(), new_value);
                else
                    break;
            }
        }
        return source_code;
    }

    string macro_span ()
    {
        return content;
    }

    bool isEmpty()
    {
        return name=="";
    }
    void put_arguments (vector<p_AstNode> arguments)
    {
        for (int i=0; i<arguments.size(); i++)
            formal_argu.push_back (arguments[i]->getName()); 
    }
    void put_preprocessing (string declare)
    {
        preprocessing.push_back(declare);
    }
    void set_content (string c)
    {
        content = c;
    }
    void outputtest ()
    {
        std::cout << "name: " << name << std::endl;
        for (int i=0; i<formal_argu.size(); i++)
        {
            std::cout << formal_argu[i] << " ";
        }
        std::cout << std::endl;
        std::cout << content << std::endl;
    }

    bool is_Procedure_Macro ()
    {
        return is_proc;
    }
    void set_Procedure_Macro ()
    {
        is_proc = true;
    }

private:
    string  name;
    string  content;           //e.g.   (+ x 2)
    map<string,string> argumap;
    vector<string> formal_argu;
    vector<string> preprocessing;
    bool    is_proc;           // e.g for macro (abs 2) is_proc should be set to 1
};

#endif
