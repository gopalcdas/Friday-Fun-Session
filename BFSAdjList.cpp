// BFS, Adjacency List

#include "stdio.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> GetData(int n)
{
    vector<vector<int>> grid;

    static const int arr1[] = { 1, 3 };
    vector<int> first(arr1, arr1 + sizeof(arr1) / sizeof(arr1[0]));
    grid.push_back(first);

    static const int arr2[] = { 2 };
    vector<int> second(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));
    grid.push_back(second);

    static const int arr3[] = { 1, 3 };
    vector<int> third(arr3, arr3 + sizeof(arr3) / sizeof(arr3[0]));
    grid.push_back(third);

    static const int arr4[] = { 3 };
    vector<int> fourth(arr4, arr4 + sizeof(arr4) / sizeof(arr4[0]));
    grid.push_back(fourth);

    return grid;
}

void BFS(vector<vector<int>> grid, int const n, int f)
{
    queue<int> q;
    q.push(f);
    vector<bool> visited(n, false);
    visited[f] = true;

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();

        cout << curr << endl;

        for (int i = 0; i < grid[curr].size(); i++)
        {
            if (!visited[grid[curr][i]])
            {
                visited[grid[curr][i]] = true;
                q.push(grid[curr][i]);
            }
        }
    }
}

int main()
{
    int n = 4;
    vector<vector<int>> grid = GetData(n);

    BFS(grid, n, 0);

    getchar();

    return 0;
}
