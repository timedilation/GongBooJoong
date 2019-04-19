/*
 * 시간복잡도: O(N)
 */
#include <iostream>
using namespace::std;

bool checkPalin(string input) {
    int alphabetMap[26] = {};
    int len = input.size();
    for(int i=0; i<len; i++) {
        int index = input[i] - 'a';
        alphabetMap[index]++;
    }
    if((len%2) == 0) {
        for(int i=0; i<len; i++) {
            if((alphabetMap[i]%2) !=0)
                return false;
        }
    }
    else {
        bool findOdd = false;
        for(int i=0; i<len; i++) {
            if((alphabetMap[i]%2) != 0) {
                if(findOdd)
                    return false;
                findOdd = true;
            }
        }
    }
    return true;
}

int main()
{
    cout << checkPalin("abab") << endl;
    cout << checkPalin("a") << endl;
    cout << checkPalin("aa") << endl;
    cout << checkPalin("abbab") << endl;
    cout << checkPalin("abcabcabd") << endl;
    cout << checkPalin("ab") << endl;
}
