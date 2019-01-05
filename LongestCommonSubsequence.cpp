//Longest Common Subsequence (LCS)

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<vector<int>> SetMat(int r, int c, int d)
{
    vector<vector<int>> m;

    for (int i = 0; i < r; i++)
    {
        vector<int> arr;
        for (int j = 0; j < c; j++)
        {
            if (d == 0)
                arr.push_back(0);
            else
            {
                if (i == 0 || j == 0)
                    arr.push_back(0);
                else
                    arr.push_back(INT_MAX);
            }
        }
        m.push_back(arr);
    }

    return m;
}

void PrintLcsString(vector<vector<int>> t, string f)
{
    stack<char> s;

    int r = t.size()-1;
    int c = t[0].size() - 1;

    while (true)
    {
        if (t[r][c] == 1)
        {
            s.push(f[c-1]);
            r--;
            c--;
        }
        else if (t[r][c] == 2)
            r--;
        else if (t[r][c] == 3)
            c--;

        if (r <= 0 || c <= 0)
            break;
    }

    while (!s.empty())
    {
        char c = s.top();
        cout << c;
        s.pop();
    }

    cout << endl;
}

int main()
{
    string f("gopaloui");
    string s("apaliuo");

    int c = f.length() + 1;
    int r = s.length() + 1;

    vector<vector<int>> m = SetMat(r, c, -1);
    vector<vector<int>> t = SetMat(r, c, 0);

    for (int i = 1; i < r; i++)
    {
        for (int j = 1; j < c; j++)
        {
            if (f[j - 1] == s[i - 1])
            {
                m[i][j] = m[i - 1][j - 1] + 1;
                t[i][j] = 1;
            }
            else
            {
                m[i][j] = m[i][j - 1] > m[i - 1][j] ? m[i][j - 1] : m[i - 1][j];
                t[i][j] = m[i][j - 1] > m[i - 1][j] ? 3 : 2;
            }
        }
    }

    cout << m[r-1][c-1] << endl;
    PrintLcsString(t, f);

    getchar();

    return 0;
}
