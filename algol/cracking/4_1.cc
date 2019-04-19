#include <iostream>
#include <queue>
using namespace::std;
#define N 5

int a[N][N] = {
    {0, 1, 0, 0, 0},
    {0, 0, 0, 0, 1},
    {0, 1, 0, 0, 0},
    {0, 1, 1, 0, 0},
    {1, 0, 0, 1, 0}
};

bool canReach(int from, int to) {
    int reached[N][N] = {};
    queue<int> visit;
    visit.push(from);
    while(visit.empty()==false) {
        int dot = visit.front();
        for(int i=0; i<N; i++) {
            if(a[dot][i] == 1) {
                if(i == to)
                    return true;
                if(reached[dot][i] == 0) {
                    reached[dot][i] = 1;
                    visit.push(i);
                }
            }
        }
        visit.pop();
    }
    return false;
}

int main()
{
    cout << canReach(0,2) << endl;
}
