#include <iostream>
#include <stack>
#define N 5
using namespace::std;

stack<pair<int,int> > way;
int isVisited[N][N] = {};
int grid[N][N] = {
    {1,1,1,1,1},
    {1,1,0,1,0},
    {1,0,0,1,1},
    {0,0,0,0,1},
    {0,0,0,1,1}
};


bool findWay(int r, int c)
{
    bool find = false;
    if((r<5) && (c<5)) {
        isVisited[r][c] = 1;
        if(grid[r][c] != 0) {
            if((r==4) && (c==4))
                find = true;
            else if((isVisited[r+1][c] == 0) && (findWay(r+1,c)==true))
                find = true;
            else if((isVisited[r][c+1] == 0) && (findWay(r,c+1)==true))
                find = true;
        }
    }
    if(find)
        way.push(pair<int,int>(r,c));
    return find;
}

int main()
{
    findWay(0,0);
    while(way.empty()==false) {
        cout << way.top().first << "," <<way.top().second << endl;
        way.pop();
    }
    return 0;
}
