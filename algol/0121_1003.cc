#include <iostream>
using namespace::std;

int memo[41];

void fibonacci(int n){
    if(memo[n] != -1){
        return;
    }
    fibonacci(n-1);
    memo[n] = memo[n-1] + memo[n-2];
}

int main()
{
    int n;
    cin >> n;
    memo[0] = 0;
    memo[1] = 1;
    for(int i=2; i<41; i++){
        memo[i] = -1;
        memo[i] = -1;
    }
    while(n-- > 0) {
        int fib;
        cin >> fib;
        if(fib == 0)
            cout << 1 << " " << 0 << endl;
        else {
            fibonacci(fib);
            cout << memo[fib-1] << " " << memo[fib] << endl;
        }
    }

}
