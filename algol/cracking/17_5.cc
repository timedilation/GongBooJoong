#include <iostream>
using namespace::std;

int findMaxSameNumLen(int arr[], int size)
{
    int diff[size+1], index[size+1], max = 0, diffMin = 0;
    diff[0] = 0;
    for(int i=0; i<size+1; i++)
        index[i] = -1;
    int num_0=0, num_1=0;
    for(int i=0; i<size; i++) {
        if(arr[i] == 0)
            num_0++;
        else
            num_1++;
        diff[i+1] = num_0 - num_1;
        if(diffMin > diff[i+1]) {
            diffMin = diff[i+1];
        }
    }
    for(int i=0; i<size+1; i++) {
        int diffVal = diff[i] - diffMin;
        if(index[diffVal] == -1)
            index[diffVal] = i;
        else {
            if(i - index[diffVal] > max)
                max = i - index[diffVal];
        }
    }
    return max;
}
int main()
{
    int arr[] = {0, 0, 1, 0, 1, 0, 0, 0, 1};
    int res = findMaxSameNumLen(arr, 9);
    cout << res << endl;
}
