#include <iostream>
#include <stack>
#include <string>
#include <cctype> 

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
    stack<int> numbers; 
    stack<char> operations; 

    for (int i = 0; i < expr.length(); i++) {

        if (expr[i] == ' ')
            continue;


        if (isdigit(expr[i])) {
            int val = expr[i] - '0';
            numbers.push(val);
        }

        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            operations.push(expr[i]);
        }

        else if (expr[i] == ')') {

            int val2 = numbers.top();
            numbers.pop();
            
            int val1 = numbers.top();
            numbers.pop();
            
            char op = operations.top();
            operations.pop();
            
            int result = applyOp(val1, val2, op);

            numbers.push(result);
            
            cout << "Operation: " << val1 << " " << op << " " << val2 << " = " << result << endl;
        }
    }
    return numbers.top();
}

int main() {
    string expr = "(((6+9)/3)*(6-4))";
    cout << "Result of expression (" << expr << ") is: "
         << evaluateExpression(expr) << endl;
    return 0;
}