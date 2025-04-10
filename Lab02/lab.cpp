//DSA - Lab 2
//Stack Problems

//1. Valid Parentheses
class Solution {
public:
    bool isValid(string s) {
        stack<char> temp;
        for (int idx = 0; idx < s.length(); idx++) {
            if (s[idx] == '(' || s[idx] == '[' || s[idx] == '{') {
                temp.push(s[idx]);
            }
            else if ((s[idx] == ')' || s[idx] == ']' || s[idx] == '}')) {
                char c = temp.top();
                if (temp.empty())
                    return false;
                if (c == '(' && s[idx] != ')')
                    return false;
                else if (c == '[' && s[idx] != ']')
                    return false;
                else if (c == '{' && s[idx] != '}')
                    return false;
                temp.pop();
            }

        }
        return temp.empty();
    }
};

//2. Min Stack(Easy)
class MinStack {
public:
    stack<int> mainStack;
    stack<int> minValueStack;
    MinStack() {

    }

    void push(int val) {
        if (minValueStack.empty() || val <= minValueStack.top())
        {
            minValueStack.push(val);
        }
        mainStack.push(val);
    }

    void pop() {
        if (minValueStack.top() == mainStack.top())
        {
            minValueStack.pop();
        }
        mainStack.pop();
    }

    int top() {
        return mainStack.top();
    }

    int getMin() {
        return minValueStack.top();
    }
};

//3. Trapping Rain Water(Medium)
class Solution {
public:
    int trap(vector<int>& height) {
        int size = height.size();
        int lpos = 0;
        int rpos = size - 2;
        int lmax = height[0];
        int rmax = height[size - 1];
        int  water = 0;
        while (lpos <= rpos)
        {
            if (height[lpos] >= lmax)
            {
                lmax = height[lpos];
                lpos++;
            }
            else if (height[rpos] >= rmax)
            {
                rmax = height[rpos];
                rpos--;
            }
            else if (lmax <= rmax && height[lpos] < lmax)
            {
                water = water + (lmax - height[lpos]);
                lpos++;
            }
            else
            {
                water = water + (rmax - height[rpos]);
                rpos--;
            }
        }
        return water;
    }
};

//4. Decode string
class Solution {
public:
        string decodeString(string s) {
        stack<int> forCount;
        stack<string> forString;
        int currCount = 0;
        string currStr = "";
        for (int idx = 0; idx < s.size(); idx++)
        {
            if (isdigit(s[idx]))
            {
                currCount = currCount * 10 + (s[idx] - '0');
            }
            else if (s[idx] == '[')
            {
                forCount.push(currCount);
                forString.push(currStr);
                currCount = 0;
                currStr = "";
            }
            else if (s[idx] == ']')
            {
                int repeatCount = forCount.top();
                forCount.pop();
                string repeatedStr;
                for (int i = 0; i < repeatCount; i++)
                {
                    repeatedStr += currStr;
                }
                currStr = forString.top() + repeatedStr;
                forString.pop();
            }
            else
            {
                currStr += s[idx];
            }
        }
        return currStr;
    }
};

//5. Container with most water





//Sir, I have an issue of laptop so I did not complete my tasks.My laptop is just recovered yesterday so i have not time to do tasks.But I will complete them before evaluation