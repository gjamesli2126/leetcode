#include <bits/stdc++.h>
using namespace std;
#define mainTest main
/*
 * The reason for sorting the input before using `next_permutation` in C++ is because `next_permutation` generates the next lexicographically greater permutation of a sequence. If the sequence is not initially sorted in ascending order, `next_permutation` might not be able to iterate through all possible permutations, or it might start in the middle of the sequence of all permutations.

Here's a more detailed explanation:

1. **Lexicographical Ordering**: `next_permutation` rearranges the elements into the next permutation that is lexicographically greater than the current arrangement. Lexicographical order is similar to dictionary order, meaning that the function compares elements as if they are characters in a word.

2. **Starting Point**: If the input sequence is sorted in ascending order, `next_permutation` starts with the lexicographically smallest permutation. This ensures that all permutations are covered as it iterates through to the lexicographically largest permutation.

3. **Coverage of All Permutations**: If the input is not sorted, `next_permutation` will only cycle through the permutations that are lexicographically larger than the initial arrangement. This could exclude a significant portion of the possible permutations.

4. **Example**: Consider a sequence `[2, 1, 3]`. If you apply `next_permutation` without sorting, it will generate permutations starting from this sequence and miss the permutations that come before it in lexicographical order, such as `[1, 2, 3]` and `[1, 3, 2]`.

5. **Reaching the End**: When `next_permutation` can no longer find a greater permutation (i.e., when the sequence is in its highest possible lexicographical order), it returns `false` to indicate that the permutations have been exhausted. If you start with a sorted sequence, this ensures you've explored all possible permutations.

In summary, sorting the sequence first ensures that you start from the lexicographically smallest arrangement and systematically move through every possible permutation of the elements.
 * */
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        sort(nums.begin(),nums.end());
        do{
            ans.push_back(nums);
        } while (next_permutation(nums.begin(),nums.end()));
        return ans;
    }
};

void printResult(const vector<vector<int>>& result) {
    cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << "[";
        for (size_t j = 0; j < result[i].size(); ++j) {
            cout << result[i][j];
            if (j < result[i].size() - 1) cout << ", ";
        }
        cout << "]";
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

bool compareSets(const vector<vector<int>>& a, const vector<vector<int>>& b) {
    if (a.size() != b.size()) return false;

    for (const auto& vec : a) {
        if (find(b.begin(), b.end(), vec) == b.end()) return false;
    }
    return true;
}
int mainTest() {
    // Define test cases and expected results
    vector<pair<vector<int>, vector<vector<int>>>> testCases = {
            {{1, 2, 3}, {{1, 2, 3}, {1, 3, 2}, {2, 1, 3}, {2, 3, 1}, {3, 1, 2}, {3, 2, 1}}},
            {{0, 1}, {{0, 1}, {1, 0}}},
            {{1}, {{1}}}
    };

    // Iterate through test cases and display results
    for (auto& [testCase, expected] : testCases) {
        Solution solution; // Create a new Solution object for each test case
        cout << "Input: ";
        printResult({testCase});
        vector<vector<int>> result = solution.permute(testCase);
        cout << "Output: ";
        printResult(result);

        // Determine pass/fail status
        bool isPass = compareSets(result, expected);
        if (isPass) {
            cout << "\033[32mPass\033[0m" << endl;
        } else {
            cout << "\033[31mFail\033[0m" << endl;
        }
        cout << endl;
    }

    return 0;
}