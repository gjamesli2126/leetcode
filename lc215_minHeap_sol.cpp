class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> heap; // Min heap 0,1,2,3,4,5 : top=0
        for (int num : nums) {
            heap.push(num);
            if (heap.size() > k) {
                heap.pop();
            }
        }
        return heap.top();
    }
};