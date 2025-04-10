#include<iostream>
#include<stack>

using namespace std;

int main()
{
	string prefix;
	string postfix;
	int prefixAns;
	int postfixAns;
	cout << "Enter Input(Prefix): ";
	cin >> prefix;
	prefixAns = evaluate(prefix, "prefix");
	cout << "Answer: " << prefixAns;
	cout << "Enter Input(Postfix): ";
	cin >> postfix;
	postfixAns = evaluate(postfix, "postfix");
	cout << "Answer " << postfixAns;

	return 0;
}

int evaluate(string expression, string type) {
	stack<int> forEvaluate;
	int start;
	int stop;
	if (type == "prefix")
	{
		start = expression.size() - 1;
		stop = -1 ;
	}
	else if (type == "postfix")
	{
		start = 0;
		stop = expression.size();
	}
	for (int idx = start; idx <= stop; idx--)
	{
		if (isdigit(expression[idx]))
		{
			forEvaluate.push(expression[idx]);
		}
		else
		{
			int value02 = forEvaluate.top();
			int value01 = forEvaluate.top();
			forEvaluate.pop();
			forEvaluate.pop();
			int result;
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
	return forEvaluate.top();
}