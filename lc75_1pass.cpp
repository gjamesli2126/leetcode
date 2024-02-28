#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int low=0,mid=0,high=nums.size()-1;
        while(mid<=high){
            switch (nums[mid]) {
                case 0:
                    swap(nums[low],nums[mid]);
                    ++low;
                    ++mid;
                    break;
                case 1:
                    ++mid;
                    break;
                case 2:
                    swap(nums[mid],nums[high]);
                    --high;
            }
        }

    }
};

void printArray(const vector<int>& nums) {
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;
}

void printResult(bool passed) {
    if (passed) {
        cout << "\033[32mPass\033[0m" << endl;
    } else {
        cout << "\033[31mFail\033[0m" << endl;
    }
}

bool compareArrays(const vector<int>& nums1, const vector<int>& nums2) {
    if (nums1.size() != nums2.size()) return false;
    for (size_t i = 0; i < nums1.size(); ++i) {
        if (nums1[i] != nums2[i]) return false;
    }
    return true;
}

int mainTest() {
    // Test Case 1
    Solution solution1;
    vector<int> nums1 = {2, 0, 2, 1, 1, 0};
    vector<int> expected1 = {0, 0, 1, 1, 2, 2};
    solution1.sortColors(nums1);
    cout << "Expected: ";
    printArray(expected1);
    cout << "Output: ";
    printArray(nums1);
    printResult(compareArrays(nums1, expected1));

    // Test Case 2
    Solution solution2;
    vector<int> nums2 = {2, 0, 1};
    vector<int> expected2 = {0, 1, 2};
    solution2.sortColors(nums2);
    cout << "Expected: ";
    printArray(expected2);
    cout << "Output: ";
    printArray(nums2);
    printResult(compareArrays(nums2, expected2));

    return 0;
}
