#include <iostream>
using namespace::std;
// swap없애는 코드 짜고 싶은데 너무 졸리다

int howManyWays(int stairN) {
    if(stairN == 1)
        return 1;
    else if(stairN == 2)
        return 2;
    else if(stairN == 3)
        return 4;
    int prev = 4, pprev = 2, ppprev = 1, curr = 0, currIdx = 4;
    while(currIdx <= stairN) {
        curr = prev + pprev + ppprev;
        ppprev = pprev;
        pprev = prev;
        prev = curr;
        currIdx++;
    }
    return curr;
}

int main()
{
    cout << howManyWays(36) << endl;
}
