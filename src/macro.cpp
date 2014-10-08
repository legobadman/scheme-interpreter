#include "Tree.h"
#include "macro.h"


string Macro::macro_span (p_AstNode p)
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

string Macro::macro_span ()
{
    return content;
}

bool Macro::isEmpty()
{
    return empty;
}


void Macro::put_arguments (vector<p_AstNode> arguments)
{
    for (int i=0; i<arguments.size(); i++)
        formal_argu.push_back (arguments[i]->getName()); 
}


void Macro::put_predefine (string inner_define)
{
    pre_Def_List.push_back (inner_define);
}

void Macro::set_content (string c)
{
    content = c;
    empty   = false;
}

string Macro::get_content ()
{
    return content;
}

vector<string>  
Macro::get_Pre_Def_List()
{
    return pre_Def_List;
}


void Macro::outputtest ()
{
    std::cout << "name: " << name << std::endl;
    for (int i=0; i<formal_argu.size(); i++)
    {
        std::cout << formal_argu[i] << " ";
    }
    std::cout << std::endl;
    std::cout << content << std::endl;
}

bool Macro::is_Procedure_Macro ()
{
    return is_proc;
}

void Macro::set_Procedure_Macro ()
{
    is_proc = true;
}


