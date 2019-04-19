/*
 * 10.1 Sorted Merge: You are given two sorted arrays, A and B,
 * where A has a large enough buffer at the end to hold B.
 * Write a method to merge B into A in sorted order
 */
#include <iostream>
using namespace::std;

void mergeArr(int* to, int toSize, int* from, int fromSize)
{
    int insertIdx = toSize+fromSize-1,
        toIdx = toSize - 1,
        fromIdx = fromSize - 1;
    for(;insertIdx >= 0; insertIdx--) {
        if(toIdx < 0)
            to[insertIdx] = from[fromIdx--];
        else if(fromIdx < 0)
            to[insertIdx] = to[toIdx--];
        else {
            if(from[fromIdx] > to[toIdx])
                to[insertIdx] = from[fromIdx--];
            else
                to[insertIdx] = to[toIdx--];
        }
    }
    return;
}

int main()
{
    int to[11] = {1,2,5,7,12,13,0,0,0,0};
    int from[5] = {2,5,6,9,11};
    mergeArr(to, 6, from, 5);
    for(int i=0; i<11; i++)
        cout << to[i] << endl;
}
