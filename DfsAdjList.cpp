//DFS, Adjacency List, disjoint graphs (black, gray, white set, cycle detection)

#include "stdio.h"
#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct Node
{
    int startTime;
    int finishTime;
};

Node *CreateNode(int startTime, int finishTime)
{
    Node *n = new Node();

    n->startTime = startTime;
    n->finishTime = finishTime;

    return n;
}

vector<vector<int>> GetData(int n)
{
    vector<vector<int>> grid;
	
    //static const int arr0[] = { 1, 3 };
    //vector<int> first(arr0, arr0 + sizeof(arr0) / sizeof(arr0[0]));
    //grid.push_back(first);

    //static const int arr1[] = { 2 };
    //vector<int> second(arr1, arr1 + sizeof(arr1) / sizeof(arr1[0]));
    //grid.push_back(second);

    //static const int arr2[] = { 3 };
    //vector<int> third(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));
    //grid.push_back(third);

    //static const int arr3[] = { 0 };
    //vector<int> fourth(arr3, arr3 + sizeof(arr3) / sizeof(arr3[0]));;
    //grid.push_back(fourth);

    static const int arr0[] = { 1, 3 };
    vector<int> first (arr0, arr0+sizeof(arr0) / sizeof(arr0[0]));
    grid.push_back(first);

    static const int arr1[] = { 0, 2 };
    vector<int> second(arr1, arr1 + sizeof(arr1) / sizeof(arr1[0]));
    grid.push_back(second);

    static const int arr2[] = { 3, 4, 5 };
    vector<int> third(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));
    grid.push_back(third);

    static const int arr3[] = { 0, 2 };
    vector<int> fourth(arr3, arr3 + sizeof(arr3) / sizeof(arr3[0]));
    grid.push_back(fourth);

    static const int arr4[] = { 2, 5 };
    vector<int> fifth(arr4, arr4 + sizeof(arr4) / sizeof(arr4[0]));
    grid.push_back(fifth);

    static const int arr5[] = { 2, 4 };
    vector<int> sixth(arr5, arr5 + sizeof(arr5) / sizeof(arr5[0]));
    grid.push_back(sixth);

    return grid;
}

bool IsParent(int parent, int child, unordered_map<int, Node*> nodes, bool &isValid)
{
    isValid = false;
    auto pNode = nodes.find(parent);
    if (pNode == nodes.end())
        return false;

    if(pNode->second->finishTime != -1)
        return false;

    auto cNode = nodes.find(child);
    if (cNode == nodes.end())
        return false;

    isValid = true;
    return (pNode->second->startTime == cNode->second->startTime - 1);
}

void DFS(vector<vector<int>> grid, int const n, int f)
{	
    stack<int> s;
    unordered_set<int> backEdges;	
    unordered_map<int, Node*> nodes;
    int startTime = 0;
    int traveseOrder = 0;

    cout << endl;

    vector<bool> visited(n, false);
    visited[f] = true;
	
    s.push(f);
    while (!s.empty())
    {
        int u = s.top();
        s.pop();

        nodes.insert(pair<int, Node *>(u, CreateNode(startTime++, -1)));		

        cout << u << endl;

        bool goOn = false;
        for (int i = 0; i < grid[u].size(); i++)
        {
            int v = grid[u][i];
            if (visited[v])
            {
                bool isValid;
                if (!IsParent(u, v, nodes, isValid))
                    if(isValid)
                        backEdges.insert(u * n + v);
            }
            else
            {
                visited[v] = true;
                s.push(v);

                goOn = true;
            }
        }

        if (!goOn)
        {
            auto it = nodes.find(u);
            if (it != nodes.end())
                it->second->finishTime = startTime++;
        }
    }

    cout << endl;
    for (auto it = backEdges.begin(); it != backEdges.end(); ++it)
        cout << "(" << (*it) / n << ", " << (*it) % n << ")" << endl;

    cout << endl;

    for (auto it = nodes.begin(); it != nodes.end(); ++it)
    {
        //cout << "node: " << (*it).first << ", start time" << (*it).second->startTime % n << ", finish time" << (*it).second->finishTime << ", traverse order " << (*it).second->traverseOrder << endl;
    }
}

unordered_set<int> SetWhiteSet(int n)
{
    unordered_set<int> whiteSet;
    for (int i = 0; i < n; i++)
        whiteSet.insert(i);

    return whiteSet;
}

void SetExplorationStart(int node, int &clock, unordered_set<int> &whiteSet, unordered_set<int> &graySet, unordered_map<int, Node *> &path)
{
    whiteSet.erase(node);
    graySet.insert(node);
    path.insert(pair<int, Node *>(node, CreateNode(clock++, -1)));
}

void SetExplorationEnd(int node, int &clock, unordered_set<int> &graySet, unordered_set<int> &blackSet, unordered_map<int, Node *> path)
{
    auto it = path.find(node);
    if (it == path.end())
        return;

    it->second->finishTime = clock++;

    graySet.erase(node);
    blackSet.insert(node);
}

bool NeedToExplore(int u, int node, int n, unordered_set<int> whiteSet, unordered_set<int> graySet, unordered_set<int> &backEdges)
{
    if (graySet.find(node) != graySet.end())
    {
        backEdges.insert(u * n + node);
        cout << "cycle deteced  " << node << endl;
    }

    auto it = whiteSet.find(node);
    if (it == whiteSet.end())
        return false;

    return true;
}

void RecursiveDfs(vector<vector<int>> graph, int u, unordered_set<int> &whiteSet, unordered_set<int> &graySet, unordered_set<int> &blackSet, int &clock, unordered_map<int, Node *> &path, unordered_set<int> &backEdges)
{
    SetExplorationStart(u, clock, whiteSet, graySet, path);
    for (int i = 0; i < graph[u].size(); i++)
    {
        if(NeedToExplore(u, graph[u][i], graph.size(), whiteSet, graySet, backEdges))
            RecursiveDfs(graph, graph[u][i], whiteSet, graySet, blackSet, clock, path, backEdges);
    }

    SetExplorationEnd(u, clock, graySet, blackSet, path);
}

void PrintPath(vector<unordered_map<int, Node *>> paths, unordered_set<int> backEdges, int n)
{
    for (int i = 0; i < paths.size(); i++)
        for (auto it = paths[i].begin(); it != paths[i].end(); ++it)
            cout << "Node: " << it->first << ", " << it->second->startTime << ", " << it->second->finishTime << endl;

    for (auto it = backEdges.begin(); it != backEdges.end(); ++it)
        cout << "(" << (*it) / n << ", " << (*it) % n << ")" << endl;
}

int main()
{
    int n = 6;
    vector<vector<int>> graph = GetData(n);

    vector<unordered_map<int, Node *>> paths;
    unordered_set<int> whiteSet = SetWhiteSet(graph.size());
    unordered_set<int> graySet;
    unordered_set<int> blackSet;
    unordered_set<int> backEdges;

    for (int i = 0; i < whiteSet.size(); i++)
    {
        int clock = 0;
		
        unordered_map<int, Node *> path;
        RecursiveDfs(graph, 0, whiteSet, graySet, blackSet, clock, path, backEdges);
        paths.push_back(path);
    }

    PrintPath(paths, backEdges, graph.size());

    getchar();

    return 0;
}
