#include <iostream>
using namespace::std;

int maxSum(int arr[], int size)
{
    int maxSum=0, currSum=0;
    for(int i=0; i<size; i++) {
        currSum += arr[i];
        if(currSum > maxSum)
            maxSum = currSum;
        if(currSum < 0)
            currSum = 0;
    }
    return maxSum;
}

int main()
{
    int arr[] = {2, -8, -3, 2, -1, 4, -10};
    int res = maxSum(arr, 6);
    cout << res << endl;
}
