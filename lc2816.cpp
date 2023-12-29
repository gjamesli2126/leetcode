#include <bits/stdc++.h>
using namespace std;
// Definition for singly-linked list.
// struct ListNode {
//     int val;
//     ListNode next;
//     ListNode() : val(0), next(nullptr) {}
//     ListNode(int x) : val(x), next(nullptr) {}
//     ListNode(int x, ListNode next) : val(x), next(next) {}
// };
 
class Solution {
private:
    void doubledFrom(ListNode* head){
        ListNode* node=head;
        while(node!=nullptr){
            int carry=0;
            if(node->next && node->next->val>4) carry=1;
            node->val=(node->val*2)%10 + carry;
            node=node->next;
        }
    }
public:
    ListNode* doubleIt(ListNode *head) {
        //prehead
        if(head->val>4) head=new ListNode(0,head);
        doubledFrom(head);
        return head;
    }
};