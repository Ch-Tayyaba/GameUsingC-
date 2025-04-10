#pragma once
#include<iostream>
using namespace std;


int main()
{
    Solution s;
    string ans = s.decodeString("3[a]2[bc]");
    cout << ans;

    return 0;
}



class Solution {
public:
    string decodeString(string s) {
        int k = 0;
        int opening = 0;
        string forDecode = "";
        string decoded = "";
        for (int idx = 0; idx < s.size(); idx++)
        {
            if (s[idx] == '[')
            {
                forDecode = "";
                k = s[idx - 1];
                for (int i = idx + 1; i < s.size(); i++)
                {
                    if (s[i] == '[')
                    {
                        opening++;
                    }
                    else if (s[i] == ']' && opening > 0)
                    {
                        opening--;
                    }
                    else if (s[i] == ']' && opening == 0)
                    {
                        break;
                    }
                    forDecode += s[i];

                }
                for (int idx = 0; idx < k; idx++)
                {
                    decoded += forDecode;
                }
            }
        }
        return decoded;
    }
};