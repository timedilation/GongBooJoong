#include <iostream>
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
void printInorder(TreeNode* root)
{
    if(root==NULL) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
    return;
}

int main()
{
    int a[10] = {0,1,2,3,4,5,6,7,8,9};
    TreeNode* root = makeMinBST(a, 10);
    printInorder(root);
}
