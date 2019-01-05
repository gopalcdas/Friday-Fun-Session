// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdio.h"
#include <iostream>
#include <vector>
#include <queue>
//#include <algorithm>

using namespace std;

class Data
{
    private:
        int data;
        int sourceArray;
        int nextIndex;

public:
    Data(int data, int sourceArray, int nextIndex)
    {
        this->data = data;
        this->sourceArray = sourceArray;
        this->nextIndex = nextIndex;
    }

    int getData() const
    {
        return data;
    }

    int getSourceArray() const
    {
        return sourceArray;
    }

    int getNextIndex() const
    {
        return nextIndex;
    }
};

class sortOperator
{
    public:
        int operator()(const Data &d1, const Data &d2)
        {
            return d1.getData() > d2.getData();
        }
};

class sortOperatorInt
{
    public:
        int operator()(const int &d1, const int &d2)
        {
            return d1 > d2;
        }
};

vector<vector<int>> GetData()
{
    vector<vector<int>> grid;

    static const int arr1[] = { 1, 3, 7, 12, 200, 231 };
    vector<int> first(arr1, arr1 + sizeof(arr1) / sizeof(arr1[0]));
    grid.push_back(first);

    static const int arr2[] = { 2, 10, 17, 20, 21, 37 };
    vector<int> second(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));
    grid.push_back(second);

    static const int arr3[] = { 1, 1, 1, 1, 2000 };
    vector<int> third(arr3, arr3 + sizeof(arr3) / sizeof(arr3[0]));
    grid.push_back(third);

    static const int arr4[] = { 1, 12, 19, 27, 33 };
    vector<int> fourth(arr4, arr4 + sizeof(arr4) / sizeof(arr4[0]));
    grid.push_back(fourth);

    return grid;
}

void Sort(vector<vector<int>> grid)
{
    std::priority_queue<Data, std::vector<Data>, sortOperator> q;

    for (int i = 0; i < grid.size(); i++)
        q.push(Data(grid[i][0], i, grid[i].size() >= 2 ? 1 : -1));

    while (!q.empty())
    {
        Data d = q.top();
        cout << d.getData() << endl;
        q.pop();

        if (d.getNextIndex() != -1)
            q.push(Data(grid[d.getSourceArray()][d.getNextIndex()], d.getSourceArray(), d.getNextIndex() + 1 < grid[d.getSourceArray()].size() ? d.getNextIndex() + 1 : -1));
    }
}

bool myfunction(int i, int j) { return (i < j); }

int main()
{
    vector<vector<int>> grid = GetData();

    vector<int> newData = { 3, 5, 22, 6, 87,4, 324 ,4 };
    sort(newData.begin(), newData.end(), myfunction);

    Sort(grid);

    getchar();

    return 0;
}
