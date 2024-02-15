#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if(!head) return nullptr;
        ListNode *fast=head;
        ListNode *slow=head;
        ListNode *entry=head;
        while(fast && fast->next){
            slow=slow->next;
            fast=fast->next->next;
            if(slow!=fast) continue;
            while(entry!=slow){
                slow=slow->next;
                entry=entry->next;
            }
            return entry;
        }
        return nullptr;
    }
};

ListNode* buildListWithCycle(const vector<int>& nums, int pos) {
    ListNode *head = nullptr, *tail = nullptr, *cycleStart = nullptr;
    for (int i = 0; i < nums.size(); ++i) {
        ListNode *newNode = new ListNode(nums[i]);
        if (!head) {
            head = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;

        if (i == pos) {
            cycleStart = newNode;
        }
    }

    if (tail) {
        tail->next = cycleStart; // Create a cycle
    }

    return head;
}

void freeList(ListNode *head) {
    unordered_map<ListNode*, bool> visited;
    while (head && !visited[head]) {
        visited[head] = true;
        ListNode *nextNode = head->next;
        delete head;
        head = nextNode;
    }
}

int main() {
    vector<pair<vector<int>, int>> testCases = {
            {{3, 2, 0, -4}, 1},
            {{1, 2}, 0},
            {{1}, -1}
    };

    Solution solution;
    for (int i = 0; i < testCases.size(); ++i) {
        ListNode *head = buildListWithCycle(testCases[i].first, testCases[i].second);
        ListNode *cycleStart = solution.detectCycle(head);

        cout << "Test " << i + 1 << ": ";
        if (cycleStart) {
            cout << "Cycle starts at node with value " << cycleStart->val << endl;
        } else {
            cout << "No cycle detected" << endl;
        }

        freeList(head);
    }

    return 0;
}
