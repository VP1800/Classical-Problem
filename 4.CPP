#include <iostream>
#include <stack>
#include <string>
using namespace std;

// Function to determine precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Function to check if the character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Function to convert infix expression to RPN
string infixToRPN(string expr) {
    stack<char> s;
    string result;
    
    for (char c : expr) {
        // If the character is an operand, add it to result
        if (isalpha(c)) {
            result += c;
        }
        // If the character is '(', push it to stack
        else if (c == '(') {
            s.push(c);
        }
        // If the character is ')', pop from the stack to result until '(' is found
        else if (c == ')') {
            while (!s.empty() && s.top() != '(') {
                result += s.top();
                s.pop();
            }
            s.pop();  // Remove '(' from stack
        }
        // If an operator is encountered
        else if (isOperator(c)) {
            while (!s.empty() && precedence(s.top()) >= precedence(c)) {
                if (c == '^' && s.top() == '^') break; // Right-associative check for '^'
                result += s.top();
                s.pop();
            }
            s.push(c);
        }
    }
    
    // Pop remaining operators from the stack
    while (!s.empty()) {
        result += s.top();
        s.pop();
    }
    
    return result;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        string expression;
        cin >> expression;
        cout << infixToRPN(expression) << endl;
    }
    return 0;
}