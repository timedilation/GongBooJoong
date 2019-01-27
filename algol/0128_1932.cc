#include <iostream>
using namespace::std;

int main()
{
    int n;
    cin >> n;
    int l = 1, prev[n+1];
    for(int i=0; i<n+1;i++)
        prev[i] = 0;
    while(l <= n){
        int num[l];
        cin >> num[0];
        num[0] = prev[0] + num[0];
        for(int i=1; i<l; i++){
            cin >> num[i];
            num[i] = prev[i-1] > prev[i] ? prev[i-1]+num[i] : prev[i]+num[i];
        }
        for(int i=0; i<l; i++){
            prev[i] = num[i];
        }
        l++;
    }
    int max = 0;
    for(int i=0; i<n; i++)
        max = prev[i] > max ? prev[i] : max;
    cout << max;
}
