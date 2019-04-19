/*
 * 시간복잡도 O(n)
 */
#include <iostream>
#include <vector>
#include <queue>
using namespace::std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int _val):val(_val), left(NULL), right(NULL){}
};

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

int findPassNum(TreeNode* root, int val)
{
    queue<pair<TreeNode*, vector<int> > > queue;
    int passNum = 0;
    if(root == NULL)
        return 0;
    vector<int> valList;
    if(root->val == val)
        passNum = 1;
    queue.push(pair<TreeNode*, vector<int> >(root, valList));
    while(queue.empty() == false) {
        TreeNode* curr = queue.front().first;
        vector<int> valList = queue.front().second;
        int currPassVal = curr->val;
        if(currPassVal == val)
            passNum++;
        for(int i=0; i<valList.size(); i++) {
            valList[i] += currPassVal;
            if(valList[i] == val)
                passNum++;
        }
        valList.push_back(currPassVal);
        if(curr->left != NULL)
            queue.push(pair<TreeNode*, vector<int> >(curr->left, valList));
        if(curr->right != NULL)
            queue.push(pair<TreeNode*, vector<int> >(curr->right, valList));
        queue.pop();
    }
    return passNum;
}


int main()
{
    int a[] = {-10,-2,0,5,8,16,18,22,25,30,31};
    TreeNode* root = makeMinBST(a, 11);
    cout << findPassNum(root, 16) << endl;
}
