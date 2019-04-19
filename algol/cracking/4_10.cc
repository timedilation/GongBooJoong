#include <iostream>
#include <vector>
using namespace::std;


struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int _val):val(_val), left(NULL), right(NULL){}
};

TreeNode* makeMinBST(int*, int);

void traversePreorder(TreeNode* root, vector<int>& output)
{
    if(root == NULL)
        output.push_back(-1);
    else {
        output.push_back(root->val);
        traversePreorder(root->left, output);
        traversePreorder(root->right, output);
    }
}

int findSubTreeIndex(vector<int>& large, vector<int>& small)
{
    int start, j = 0;
    bool find = false;
    for(int i=0; i<large.size(); i++) {
        if(large[i] != small[j])
            j = 0;
        else if(j==0)
            start = i;
        else if(j == small.size()-1) {
            find=true;
            break;
        }
        j++;
    }
    if(find) return start;
    else return -1;
}

bool findSubTree(TreeNode* large, TreeNode* small)
{
    vector<int> largePreorder;
    vector<int> smallPreorder;
    traversePreorder(large, largePreorder);
    traversePreorder(small, smallPreorder);

    if(findSubTreeIndex(largePreorder, smallPreorder) != -1)
        return true;
    else return false;
}

int main()
{
    int a[] = {1,3,5,9,11,13,17,18,22,25,30,31};
    int b[] = {25,30,31};
    TreeNode* root = makeMinBST(a, 12);
    TreeNode* sub = makeMinBST(b, 3);

    bool find = findSubTree(root, sub);
    if(find)
        cout << "find" <<endl;
    else
        cout << "can't find" << endl;

    return 0;
}

TreeNode* makeMinBST(int* arr, int size)
{
    if(size == 0)
        return NULL;
    if(size == 1)
        return new TreeNode(arr[0]);
    TreeNode* node = new TreeNode(arr[(size+1)/2-1]);
    node->right = makeMinBST(arr+(size+1)/2, size-(size+1)/2);
    node->left = makeMinBST(arr, (size+1)/2-1);
    return node;
}
