#include <iostream>
#include <string>
#include <sstream>

using namespace std;

string next_id (string curr_id)
{
    string  next;
    char    head = curr_id[0];

    int num = 0, factor = 1;

    for (int i=1; i<curr_id.size(); i++)
    {
        num = num * factor + (curr_id[i]-'0');
        factor *= 10;
    }

    stringstream ss;
    if (head == 'z')
    {
        ss << "a" << num+1;
        ss >> next;
        return next;
    }
    else
    {
        if (num > 0)
            ss << (char)(head+1) << num;
        else
            ss << (char)(head+1) << endl;
        ss >> next;
        return next;
    }
}

int main2()
{
    string in;
    while(cin>>in)
    {
        string id = next_id (in); 
        cout << id << endl;
    }
    return 0;
}
