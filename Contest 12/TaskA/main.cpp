#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <map>
#include <cctype>

using std::cin;
using std::cout;
using std::string;

class Postfix {
protected:
    int isOperator(char);

    void checkBrackets(const string &) const;

    int checkingLine(const string &) const;

public:
    string rewriteLineFromInfixToPostfix(const string &) const;
};

int Postfix::isOperator(char p) {
    switch (p) {
        case '+':
            return 3;
        case '-':
            return 3;
        case '*':
            return 3;
        case '/':
            return 3;
        case '(':
            return 1;
        case ')':
            return 1;
    }
    return 0;
}

void Postfix::checkBrackets(const string &s) const {
    int leftBrackets = 0;
    int rightBrackets = 0;

    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') leftBrackets++;
        if (s[i] == ')') rightBrackets++;
    }

    if (leftBrackets != rightBrackets)
        throw myExcp("Incorrect line.");
}

int Postfix::checkingLine(const string &s) const {
    if (s.length() == 0)
        return 1;

    Postfix p;
    if (s.length() == 1)
        if (p.isOperator(s[0]))
            return 1;

    if (p.isOperator(s[0]) > 1)
        return 1;

    char left;
    char right;
    int m = 0;
    for (int i, j = 1; j < s.length(); j++) {
        i = m;
        left = s[i];
        right = s[j];
        if (right == _SPACE_)
            continue;

        if ((!p.isOperator(left)) && (!p.isOperator(right)))
            return 1;

        if ((left == '(') && ((right == '+') || (right == '*') || (right == '/')))
            return 1;

        if ((right == ')') && ((left == '-') || (left == '+') || (left == '*') || (left == '/')))
            return 1;

        if ((left == ')') && (right == '('))
            return 1;

        if ((left == right) && (left == '('))
            continue;

        if ((left == right) && (left == ')'))
            continue;

        if (p.isOperator(left) == p.isOperator(right))
            return 1;

        if ((left == '*') && ((right == '+') || (right == '-') || (right == '/') || (right == ')') || (right == '+')))
            return 1;

        if ((left == '/') && ((right == '+') || (right == '-') || (right == '*') || (right == ')') || (right == '+')))
            return 1;

        if ((left == '+') && ((right == '*') || (right == '-') || (right == '/') || (right == ')') || (right == '+')))
            return 1;

        if ((left == '-') && ((right == '+') || (right == '-') || (right == '/') || (right == ')') || (right == '+')))
            return 1;

        if ((right == ')') && ((left == '+') || (left == '-') || (left == '*') || (left == '/')))
            return 1;
        m = j;
    }
    return 0;
}


string Postfix::rewriteLineFromInfixToPostfix(const string &infixString) const {

    if (!infixString.length()) {
        throw myExcp("String is empty.");
    }

    checkBrackets(infixString);
    int tmp3 = checkingLine(infixString);
    if (tmp3)
        throw myExcp("Incorrect line.");

    map<char, int> operations;
    operations['*'] = 3;
    operations['/'] = 3;
    operations['+'] = 2;
    operations['-'] = 2;
    operations['('] = 1;

    Stack<char> result;
    Stack<char> operationsStack;

    char temp;

    for (int i = 0; i < infixString.length(); i++) {
        if (infixString[i] == _SPACE_)
            continue;
        temp = infixString[i];

        if (operations.count(temp)) {
            if ((!operationsStack.isEmpty()) && (operations[temp] <= operations[operationsStack.peek()]) &&
                (temp != '('))
                while ((!operationsStack.isEmpty()) && (operations[temp] <= operations[operationsStack.peek()]))
                    result.push(operationsStack.pop());

            operationsStack.push(temp);
            continue;
        }

        if (((temp >= 'a') && (temp <= 'z')) || ((temp >= 'A') && (temp <= 'Z'))) {
            result.push(temp);
            continue;
        }

        if (temp == ')') {
            char t = '0';
            while ((!operationsStack.isEmpty()) && (t != '(')) {
                t = operationsStack.pop();
                result.push(t);
            }
            if (t == '(') result.pop();
            continue;
        }

        throw myExcp("Incorrect symbol.");
    }

    while (!operationsStack.isEmpty()) {
        result.push(operationsStack.pop());
    }

    if (result.isEmpty())
        throw myExcp("Line doesn't contain an expression.");

    string resultString = "";

    while (!result.isEmpty())
        operationsStack.push(result.pop());

    while (!operationsStack.isEmpty()) {
        resultString += operationsStack.pop();
    }
    return resultString;
}

int main() {


    return 0;
}