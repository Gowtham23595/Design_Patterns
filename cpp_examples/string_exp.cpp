#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool checkString(string s)
{
    stack<char> tempF;
    for(char c:s){
        if(c == '(' || c == '{' || c == '['){
            tempF.push(c);
        }
        else{
            if(tempF.empty()){
                return false;
            }
            else{
                char t = tempF.top();
                if((c == ')' && t != '(') ||(c == '}' && t != '{') || (c == ']' && t != '[')){
                    return false;
                }
                tempF.pop();
            }
        }
    }
    return true;
}

int main()
{
    string s = "{{[]}}";

    if(checkString(s)){
        cout << "Matching\n";
    }
    else
    {
        cout << "Not Matching\n";
    }


}