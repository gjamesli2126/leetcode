#include <bits/stdc++.h>
#define mainTest main
using namespace std;

// ANSI color codes for output
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define RESET "\033[0m"

// Q1: Using splice to move a single element within the same list.
// Example: l1: [1, 4, 5, 6], target = 5
// After q1, l1 should become: [5, 1, 4, 6]
void q1(list<int>& lst, int target) {
    // TODO: Find the iterator to the first occurrence of target.
    // If found, do:
    // auto it = find(lst.begin(), lst.end(), target);
    // if (it != lst.end()) lst.splice(lst.begin(), lst, it);
}

// Q2: Using splice to move all elements from one list into another.
// Example: l1: [1, 2, 3], l2: [4, 5, 6]
// After q2, l1 should become: [1, 2, 3, 4, 5, 6] and l2 should be empty.
void q2(list<int>& lst1, list<int>& lst2) {
    // TODO: Splice the entire lst2 into the end of lst1.
    // Hint: lst1.splice(lst1.end(), lst2);
}

// Q3: Using splice to insert an entire list into another list at a specified position.
// Example: l1: [1, 4, 5, 6], l2: [9, 7, 0, 3], pos = 1
// (Meaning: insert after the element at index 1, which is 4)
// After q3, l1 should become: [1, 4, 9, 7, 0, 3, 5, 6] and l2 should be empty.
void q3(list<int>& lst1, list<int>& lst2, int pos) {
    // TODO: Advance an iterator to position pos (0-indexed) in lst1, then to the element after it.
    // Example: auto it = lst1.begin(); advance(it, pos+1);
    // Then splice lst2 into lst1 at that position:
    // lst1.splice(it, lst2);
}

// Q4: Using splice to move a range of elements from one list into another list.
// Example: l1: [1, 2, 3, 4], l2: [5, 6, 7, 8], startIdx = 1, endIdx = 3
// (In l2, the elements at positions 1 and 2 are [6, 7])
// After q4, l1 should become: [1, 6, 7, 2, 3, 4] and l2 should become: [5, 8]
void q4(list<int>& lst1, list<int>& lst2, int startIdx, int endIdx) {
    // TODO: Convert startIdx and endIdx into iterators for lst2.
    // Example:
    // auto itStart = lst2.begin(); advance(itStart, startIdx);
    // auto itEnd = lst2.begin(); advance(itEnd, endIdx);
    // Then, advance an iterator in lst1 to after the first element:
    // auto pos = lst1.begin(); if(pos != lst1.end()) ++pos;
    // Finally, splice the range: lst1.splice(pos, lst2, itStart, itEnd);
}

// Q5: Using splice to rotate a list by moving the last k elements to the front.
// Example: l1: [1, 2, 3, 4, 5, 6], k = 2
// After q5, l1 should become: [5, 6, 1, 2, 3, 4]
void q5(list<int>& lst, int k) {
    // TODO: If k is valid, find an iterator to the element at position lst.size() - k.
    // Example:
    // auto it = lst.begin(); advance(it, lst.size() - k);
    // Then move the range [it, lst.end()) to the front:
    // lst.splice(lst.begin(), lst, it, lst.end());
}

// Helper: Convert a list<int> to a vector<int> for easy comparison.
vector<int> listToVector(const list<int>& lst) {
    return vector<int>(lst.begin(), lst.end());
}

// Test runner for q1.
void runTest1(int testNum, list<int> input, int target, vector<int> expected) {
    q1(input, target);
    vector<int> output = listToVector(input);
    if (output == expected) {
        cout << GREEN << "Test Case " << testNum << " (q1) Passed: ";
        for (int n : output) cout << n << " ";
        cout << RESET << "\n";
    } else {
        cout << RED << "Test Case " << testNum << " (q1) Failed: Got ";
        for (int n : output) cout << n << " ";
        cout << "Expected ";
        for (int n : expected) cout << n << " ";
        cout << RESET << "\n";
    }
}

// Test runner for q2.
void runTest2(int testNum, list<int> lst1, list<int> lst2,
              vector<int> expected1, vector<int> expected2) {
    q2(lst1, lst2);
    vector<int> output1 = listToVector(lst1);
    vector<int> output2 = listToVector(lst2);
    if (output1 == expected1 && output2 == expected2) {
        cout << GREEN << "Test Case " << testNum << " (q2) Passed: lst1 = ";
        for (int n : output1) cout << n << " ";
        cout << "; lst2 = ";
        for (int n : output2) cout << n << " ";
        cout << RESET << "\n";
    } else {
        cout << RED << "Test Case " << testNum << " (q2) Failed: Got lst1 = ";
        for (int n : output1) cout << n << " ";
        cout << "; lst2 = ";
        for (int n : output2) cout << n << " ";
        cout << "Expected lst1 = ";
        for (int n : expected1) cout << n << " ";
        cout << "; lst2 = ";
        for (int n : expected2) cout << n << " ";
        cout << RESET << "\n";
    }
}

// Test runner for q3.
void runTest3(int testNum, list<int> lst1, list<int> lst2, int pos,
              vector<int> expected1, vector<int> expected2) {
    q3(lst1, lst2, pos);
    vector<int> output1 = listToVector(lst1);
    vector<int> output2 = listToVector(lst2);
    if (output1 == expected1 && output2 == expected2) {
        cout << GREEN << "Test Case " << testNum << " (q3) Passed: lst1 = ";
        for (int n : output1) cout << n << " ";
        cout << "; lst2 = ";
        for (int n : output2) cout << n << " ";
        cout << RESET << "\n";
    } else {
        cout << RED << "Test Case " << testNum << " (q3) Failed: Got lst1 = ";
        for (int n : output1) cout << n << " ";
        cout << "; lst2 = ";
        for (int n : output2) cout << n << " ";
        cout << "Expected lst1 = ";
        for (int n : expected1) cout << n << " ";
        cout << "; lst2 = ";
        for (int n : expected2) cout << n << " ";
        cout << RESET << "\n";
    }
}

// Test runner for q4.
void runTest4(int testNum, list<int> lst1, list<int> lst2, int startIdx, int endIdx,
              vector<int> expected1, vector<int> expected2) {
    q4(lst1, lst2, startIdx, endIdx);
    vector<int> output1 = listToVector(lst1);
    vector<int> output2 = listToVector(lst2);
    if (output1 == expected1 && output2 == expected2) {
        cout << GREEN << "Test Case " << testNum << " (q4) Passed: lst1 = ";
        for (int n : output1) cout << n << " ";
        cout << "; lst2 = ";
        for (int n : output2) cout << n << " ";
        cout << RESET << "\n";
    } else {
        cout << RED << "Test Case " << testNum << " (q4) Failed: Got lst1 = ";
        for (int n : output1) cout << n << " ";
        cout << "; lst2 = ";
        for (int n : output2) cout << n << " ";
        cout << "Expected lst1 = ";
        for (int n : expected1) cout << n << " ";
        cout << "; lst2 = ";
        for (int n : expected2) cout << n << " ";
        cout << RESET << "\n";
    }
}

// Test runner for q5.
void runTest5(int testNum, list<int> input, int k, vector<int> expected) {
    q5(input, k);
    vector<int> output = listToVector(input);
    if (output == expected) {
        cout << GREEN << "Test Case " << testNum << " (q5) Passed: ";
        for (int n : output) cout << n << " ";
        cout << RESET << "\n";
    } else {
        cout << RED << "Test Case " << testNum << " (q5) Failed: Got ";
        for (int n : output) cout << n << " ";
        cout << "Expected ";
        for (int n : expected) cout << n << " ";
        cout << RESET << "\n";
    }
}

int mainTest() {
    // q1 Test: Move target element to the front.
    // Example: [1, 4, 5, 6], target = 5 -> [5, 1, 4, 6]
    runTest1(1, {1, 4, 5, 6}, 5, {5, 1, 4, 6});

    // q2 Test: Splice entire lst2 at the end of lst1.
    // Example: l1: [1, 2, 3], l2: [4, 5, 6] ->
    // l1 becomes [1, 2, 3, 4, 5, 6] and l2 becomes [].
    runTest2(2, {1, 2, 3}, {4, 5, 6}, {1, 2, 3, 4, 5, 6}, {});

    // q3 Test: Insert entire lst2 into lst1 after position pos.
    // Example: l1: [1, 4, 5, 6], l2: [9, 7, 0, 3], pos = 1 ->
    // l1 becomes [1, 4, 9, 7, 0, 3, 5, 6] and l2 becomes [].
    runTest3(3, {1, 4, 5, 6}, {9, 7, 0, 3}, 1, {1, 4, 9, 7, 0, 3, 5, 6}, {});

    // q4 Test: Splice a range from lst2 into lst1.
    // Example: l1: [1, 2, 3, 4], l2: [5, 6, 7, 8], startIdx = 1, endIdx = 3 ->
    // Range in lst2: [6, 7]; then l1 becomes [1, 6, 7, 2, 3, 4] and l2 becomes [5, 8].
    runTest4(4, {1, 2, 3, 4}, {5, 6, 7, 8}, 1, 3, {1, 6, 7, 2, 3, 4}, {5, 8});

    // q5 Test: Rotate the list by moving the last k elements to the front.
    // Example: l1: [1, 2, 3, 4, 5, 6], k = 2 ->
    // l1 becomes [5, 6, 1, 2, 3, 4]
    runTest5(5, {1, 2, 3, 4, 5, 6}, 2, {5, 6, 1, 2, 3, 4});

    return 0;
}