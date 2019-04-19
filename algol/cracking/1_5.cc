#include <iostream>
using namespace::std;

bool needsOne(string str1, string str2) {
    int diff = str1.size() - str2.size();
    if((diff > 1) || (diff < -1))
        return false;
    bool samechar = true;
    if(str1.size() == str2.size()) {
        for(int i=0; i<str1.length(); i++) {
            if(str1[i] != str2[i]) {
                if(samechar == false)
                    return false;
                else
                    samechar = false;
            }
        }
    } else {
        int i =0, j = 0;
        bool isStr1Bigger = (str1.size() > str2.size()) ? true : false;
        while((i<str1.size())&&(j<str2.size())){
            if(str1[i] != str2[j]) {
                if(samechar == false)
                    return false;
                else {
                    samechar = false;
                    if(isStr1Bigger)
                        i++;
                    else
                        j++;
                }
            } else {
                i++;
                j++;
            }
        }
    }
    return true;
}        

int main()
{
	cout << needsOne("aaaab", "aaaac") << endl;
	cout << needsOne("a", "")<<endl;
	cout << needsOne("a", "b")<<endl;
	cout << needsOne("a", "bc")<<endl;
	cout << needsOne("ab", "bc")<<endl;
}
