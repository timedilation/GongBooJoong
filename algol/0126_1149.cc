#include <iostream>
using namespace::std;

int main()
{
    int N, houses[3], min[3] = {0, 0, 0};
    cin >> N;
    while(N-->0) {
        for(int i=0; i<3; i++)
            cin >> houses[i];
        int tempmin[3];
        for(int i=0; i<3; i++){
            if(houses[i]+min[(i+1)%3] < houses[i]+min[(i+2)%3])
                tempmin[i] = houses[i]+min[(i+1)%3];
            else
                tempmin[i] = houses[i]+min[(i+2)%3];
        }
        for(int i=0; i<3; i++)
            min[i] = tempmin[i];
    }
    int realmin = min[0];
    for(int i=1; i<3; i++)
        if(realmin > min[i])
            realmin = min[i];
    cout << realmin;
}
