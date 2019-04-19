#include <iostream>
using namespace::std;

struct ListNode {
    ListNode* next;
    int val;
    ListNode(int _val) : next(NULL), val(_val) {}
};

void removeDup(ListNode* head) {
    ListNode* curr = head;
    while(curr != NULL) {
        ListNode* search = curr;
        while(search->next != NULL) {
            if(curr->val == search->next->val)
                search->next = search->next->next;
            search = search->next;
        }
        curr = curr->next;
    }
}

void printList(ListNode* head) {
    while(head != NULL) {
        cout << head->val << ' ';
        head = head->next;
    }
    cout << endl;
}
int main()
{
    ListNode* root = new ListNode(1);
    root->next = new ListNode(2);
    root->next->next = new ListNode(2);
    root->next->next->next = new ListNode(1);
    root->next->next->next->next = new ListNode(3);
    printList(root);
    removeDup(root);
    printList(root);
}
