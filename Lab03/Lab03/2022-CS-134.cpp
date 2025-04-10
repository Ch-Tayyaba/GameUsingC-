#include<iostream>
#include<stack>

using namespace std;

bool isOperator(char c);
int precedence(char c);
string convertToPrefix(string infix);
string convertToPostfix(string infix);
int evaluatePrefix(string expression);
int evaluatePostfix(string expression);

int main()
{
	string infixExpression;
	cout << "Infix Expression: ";
	cin >> infixExpression;
	string postfixExpression = convertToPostfix(infixExpression);
	cout << "Postfix Expression: " << postfixExpression << endl;
	string prefixExpression = convertToPrefix(infixExpression);
	cout << "Prefix Expression: " << prefixExpression << endl;


	string prefix;
	string postfix;
	int prefixAns = 0;
	int postfixAns = 0;
	cout << "Enter Input(Prefix): ";
	cin >> prefix;
	prefixAns = evaluatePrefix(prefix);
	cout << "Answer: " << prefixAns << endl;
	cout << "Enter Input(Postfix): ";
	cin >> postfix;
	postfixAns = evaluatePostfix(postfix);
	cout << "Answer: " << postfixAns << endl;

	
	return 0;
}

bool isOperator(char c) {
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

int precedence(char c) {
	if (c == '*' || c == '/')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	return 0;
}

string convertToPostfix(string infix)
{
	string expression;
	stack<char> forOperators;
	for (int idx = 0; idx < infix.size(); idx++) {
		if (isdigit(infix[idx])) {
			expression += infix[idx];
		}
		else if (infix[idx] == '(') {
			forOperators.push(infix[idx]);
		}
		else if (infix[idx] == ')') {
			while (!forOperators.empty() && forOperators.top() != '(') {
				expression += forOperators.top();
				forOperators.pop();
			}
			forOperators.pop();
		}
		else {
			while (!forOperators.empty() && precedence(forOperators.top()) >= precedence(infix[idx])) {
				expression += forOperators.top();
				forOperators.pop();
			}
			forOperators.push(infix[idx]);
		}
	}

	while (!forOperators.empty()) {
		expression += forOperators.top();
		forOperators.pop();
	}

	return expression;
}
string convertToPrefix(string infix)
{
	string expression;
	stack<char> forOperators;
	for (int idx = infix.length(); idx >= 0; idx--) {
		if (isdigit(infix[idx])) {
			expression += infix[idx];
		}
		else if (infix[idx] == ')') {
			forOperators.push(infix[idx]);
		}
		else if (infix[idx] == '(') {
			while (!forOperators.empty() && forOperators.top() != ')') {
				expression += forOperators.top();
				forOperators.pop();
			}
			forOperators.pop();
		}
		else {
			while (!forOperators.empty() && (precedence(forOperators.top()) > precedence(infix[idx]))) {
				expression += forOperators.top();
				forOperators.pop();
			}
			forOperators.push(infix[idx]);
		}
	}
		while (!forOperators.empty()) {
			expression += forOperators.top();
			forOperators.pop();
		}
		
		string extra = "";
		for (int idx = expression.length() - 1; idx >= 0; idx--)
		{
			extra += expression[idx];
		}
		

		return extra;
	
}

int evaluatePrefix(string expression) {
	stack<int> forEvaluate;
	int result = 0;
	for (int idx = expression.length() - 1; idx >= 0; idx--)
	{
		if (isdigit(expression[idx]))
		{
			int number = expression[idx] - '0';
			forEvaluate.push(number);
		}
		else
		{
			int value02 = forEvaluate.top();
			forEvaluate.pop();
			int value01 = forEvaluate.top();
			forEvaluate.pop();
				
			if (expression[idx] == '+')
			{
				result = value01 + value02;
			}
			else if (expression[idx] == '-')
			{
				result = value01 - value02;
			}
			else if (expression[idx] == '*')
			{
				result = value01 * value02;
			}
			else if (expression[idx] == '/')
			{
				result = value01 / value02;
			}
			forEvaluate.push(result);
		}
	}
	return result;
}

int evaluatePostfix(string expression)
{
	stack<int> forEvaluate;
	int result = 0;
	for (int idx = 0; idx < expression.length(); idx++)
	{
		if (isdigit(expression[idx]))
		{
			int number = expression[idx] - '0';
			forEvaluate.push(number);
		}
		else
		{
			int value02 = forEvaluate.top();
			forEvaluate.pop();
			int value01 = forEvaluate.top();
			forEvaluate.pop();

			if (expression[idx] == '+')
			{
				result = value01 + value02;
			}
			else if (expression[idx] == '-')
			{
				result = value01 - value02;
			}
			else if (expression[idx] == '*')
			{
				result = value01 * value02;
			}
			else if (expression[idx] == '/')
			{
				result = value01 / value02;
			}
			forEvaluate.push(result);
		}
	}
	return result;
}

