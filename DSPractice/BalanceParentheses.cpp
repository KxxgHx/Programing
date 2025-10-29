#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool isBalanced(const string& expr){
    stack<char> s;
    for(char ch:expr){
        if(ch == '('){
            s.push(ch);
        }
        else if(ch == ')'){
            if(s.empty())
                return false;
            s.pop();
        }
    }
    return s.empty();
}

void printResult(const string& expr){
    if(isBalanced(expr)){
        cout << "The expression \"" << expr << "\" is balanced" << endl;
    }
    else
        cout << "The expression \"" << expr << "\" is Not balanced" << endl;
}

int main(){
    string expr1 = "((X + Y * (Z + 7))*(A + B))";
    string expr2 = "((X + Y * (Z + 7) + (A + B))";
    printResult(expr1);
    printResult(expr2);
    return 0;
}