#include <iostream>
#include <string>
#include <unordered_map>
using namespace::std;

void countBabies(vector<pair<string,int> >& babiesCount, vector<pair<string, string> >& sameBabyNames)
{
    unordered_map<string, string> name2UniqName;
    for(auto sameNamePair:sameBabyNames) {
        if(name2UniqName.find(sameNamePair->first) != name2UniqName.end()) {
            string 
            name2UniqName.insert(sameNamePair->second, sameNamePair->first);
        } else if(name2UniqName.find(sameNamePair->second) != name2UniqName.end()) {
        } else{
            name2UniqName.insert(sameNamePair->second, sameNamePair->first);
        }

    }
}

int main()
{
}
