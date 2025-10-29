#include <iostream>
#include <stack>
#include <string>
#include <cctype> // isdigit 함수를 사용하기 위함

using namespace std;

int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

int evaluateExpression(const string& expr) {
    stack<int> num;
    stack<int> operation;
    for (int i = 0; i < expr.length(); i++)
    {
        if(expr[i] == ' ')
            continue;
        if(isdigit(expr[i]))
        {
            int val = expr[i] - '0';
            num.push(val);
        }
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/'){
            operation.push(expr[i]);
        }
        else if (expr[i] == ')')
        {
            int val2 = num.top();
            num.pop();
            int val1 = num.top();
            num.pop();
            char opr = operation.top();
            operation.pop();
            int result = applyOp(val1, val2, opr);
            num.push(result);

            cout << "Operation: " << val1 << " " << opr << " " << val2 << " = " << result << endl;
            }
    }
    return num.top();
}

int main() {
    string expr = "(((6+9)/3)*(6-4))";
    cout << "Result of expression (" << expr << ") is: "
         << evaluateExpression(expr) << endl;
    return 0;
}