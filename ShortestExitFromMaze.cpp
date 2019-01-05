//20th Jan 2017 (3rd) – Shortest Exit from Maze

#include "pch.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INVALID_COST = -1;

const int BOTTOM_LEFT = 1;
const int BOTTOM = 2;
const int BOTTOM_RIGHT = 3;
const int RIGHT = 4;
const int TOP_RIGHT = 5;

class Pos
{
    public:
        int r;
        int c;

        Pos(int r, int c)
        {
            this->r = r;
            this->c = c;
        }
};

class Cell
{
    public:
        bool move;	
        bool alreadyTraversed = false;
        int cost;

        Cell()
        {
            move = false;
            alreadyTraversed = false;
            cost = INVALID_COST;
        }
};

vector<vector<Cell *>> GetData(int n)
{
    vector<vector<Cell *>> grid;
    for (int i = 0; i < n; i++)
    {
        vector<Cell *> gr;
        for (int j = 0; j < n; j++)
            gr.push_back(new Cell());
            grid.push_back(gr);
    }

    //grid[0][0]->move = 1;
    grid[1][1]->move = 1;
    grid[0][2]->move = 1;
    //grid[1][3]->move = 1;
    grid[2][3]->move = 1;
    //grid[2][0]->move = 1;
    //grid[2][1]->move = 1;
    //grid[2][3]->move = 1;
    //grid[3][1]->move = 1;
    //grid[3][2]->move = 1;
    grid[3][3]->move = 1;

    grid[0][0]->cost = 0;

    return grid;
}

bool ValidPos(vector<vector<Cell *>> grid, Pos const *newPos, int const n)
{
    if (!(newPos->r < n && newPos->c < n && newPos->r >= 0 && newPos->c >= 0))
        return false;

    return (grid[newPos->r][newPos->c]->move);
}

bool AlreadyTraversed(vector<vector<Cell *>> grid, Pos const *newPos)
{
    return grid[newPos->r][newPos->c]->alreadyTraversed;
}

bool ThisIsDestnation(Pos const *newPos, Pos const *e)
{
    return (newPos->r == e->r && newPos->c == e->c);
}

void AddCost(vector<vector<Cell *>> grid, Pos const *currPos, Pos const *newPos)
{
    grid[newPos->r][newPos->c]->cost = grid[currPos->r][currPos->c]->cost + 1;
    std::cout << "row: " << newPos->r << " col: " << newPos->c << " cost: " << grid[newPos->r][newPos->c]->cost << endl;
}

void EnQ(vector<vector<Cell *>> grid, queue<const Pos *> *q, Pos const *newPos)
{
    grid[newPos->r][newPos->c]->alreadyTraversed = true;
    q->push(newPos);
}

bool Move(vector<vector<Cell *>> grid, int const n, queue<const Pos *> *q, Pos const *curr, Pos const *e, int dir)
{
    Pos *newPos = NULL;
    switch (dir)
    {
        case BOTTOM_LEFT:
            newPos = new Pos(curr->r+1, curr->c-1);
            break;

        case BOTTOM:
	    newPos = new Pos(curr->r+1, curr->c);
            break;

        case BOTTOM_RIGHT:
            newPos = new Pos(curr->r+1, curr->c+1);
            break;

        case RIGHT:
            newPos = new Pos(curr->r, curr->c+1);
            break;

        case TOP_RIGHT:
            newPos = new Pos(curr->r-1, curr->c+1);
            break;	
    }

    if (!ValidPos(grid, newPos, n))
        return false;

    if (AlreadyTraversed(grid, newPos))
        return false;

    AddCost(grid, curr, newPos);

    if (ThisIsDestnation(newPos, e))
        return true;

    EnQ(grid, q, newPos);

    return false;
}

bool DestinationFound(vector<vector<Cell *>> grid, int const n, queue<const Pos *> *q, Pos const *curr, Pos const *e)
{
    if (Move(grid, n, q, curr, e, BOTTOM_LEFT))
        return true;

    if (Move(grid, n, q, curr, e, BOTTOM))
        return true;

    if (Move(grid, n, q, curr, e, BOTTOM_RIGHT))
        return true;

    if (Move(grid, n, q, curr, e, RIGHT))
        return true;

    if (Move(grid, n, q, curr, e, TOP_RIGHT))
        return true;

    return false;
}

int GetShortestExitCost(vector<vector<Cell *>> grid, int const n, Pos const *s, Pos const *e)
{
    queue<const Pos *> q;
    q.push(s);

    while (!q.empty())
    {
        Pos const *curr = q.front();
        q.pop();
        if (DestinationFound(grid, n, &q, curr, e))
            return grid[n-1][n-1]->cost;
		
        delete curr;
    }

    return grid[n-1][n-1]->cost;
}

int main()
{
    int n = 4;
    vector<vector<Cell *>> grid = GetData(n);

    Pos *s = new Pos(0, 0);
    Pos *e = new Pos(3, 3);

    int cost = GetShortestExitCost(grid, n, s, e);

    if (cost == INVALID_COST)
    {
        std::cout << "Exit Not Found!\n";
        return 0;
    }

    std::cout << "Shortest Path Cost!" << cost; 

    return 0;
}
