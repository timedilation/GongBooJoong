#include <iostream>
using namespace::std;

int findMagicIndex(int arr[], int size)
{
    int res = -1;
    if(size != 0) {
        int target = size/2;
        if(arr[target] == target) {
            res = target;
        } else if(arr[target] > target) {
            res = findMagicIndex(arr, size/2);
        } else {
            res = findMagicIndex(arr+target+1, size/2);
        }
    }
    return res;
}

int main()
{
    int arr[] = {1, 1, 4, 7, 7, 10, 15};
    cout << findMagicIndex(arr, 7) << endl;
}
