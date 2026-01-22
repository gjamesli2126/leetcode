#define mainTest main
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <climits>
#include <random>

using namespace std;

// ==========================================
// YOUR SOLUTION GOES HERE
// ==========================================
class Solution {
public:
    // Returns {start_index, end_index} (inclusive) of the shortest segment.
    // If no segment is found, return {-1, -1}.
    // If multiple segments have the same minimal length, return the one with the smallest start index.
    pair<int, int> findShortestSnippet(const vector<string>& document, const vector<string>& keywords) {
        // TODO: Implement Sliding Window approach (O(N))
        unordered_map<string,int> querys;
        for(const string& s:keywords) querys[s]++;
        int togo=querys.size();//剩徐item line number
        int org_len=INT_MAX;
        pair<int,int> ans={-1,-1};
        // sliding window
        for(int right=0,left=0;right<document.size();right++){
            const string& word=document[right];
            if(querys.contains(word)){
                querys[word]--;
                if(!querys[word]) --togo;
            }

            for(;togo==0;left++){
                //新的符合窗口
                int this_len=right-left;
                if(this_len<org_len){
                    ans={left,right};
                    org_len=this_len;
                }
                //嘗試縮左邊
                const string& left_word=document[left];
                if(querys.contains(left_word)){
                    querys[left_word]++;
                    if(querys[left_word]==1) ++togo;
                }
            }
        }
        if(org_len==INT_MAX) return {-1,-1};
        return ans;
    }
};

// ==========================================
// TEST HARNESS & VALIDATION
// ==========================================

const string GREEN = "\033[32m";
const string RED = "\033[31m";
const string RESET = "\033[0m";

// Helper: Brute Force Reference Implementation (O(N^2)) to verify correctness
pair<int, int> bruteForceReference(const vector<string>& doc, const vector<string>& keys) {
    unordered_set<string> req(keys.begin(), keys.end());
    if (req.empty()) return {-1, -1}; // Edge case: no keywords needed (or logic decision)

    int minLen = INT_MAX;
    pair<int, int> result = {-1, -1};

    for (int i = 0; i < doc.size(); ++i) {
        unordered_set<string> currentSet;
        for (int j = i; j < doc.size(); ++j) {
            if (req.count(doc[j])) {
                currentSet.insert(doc[j]);
            }

            // Check if valid
            if (currentSet.size() == req.size()) {
                int len = j - i + 1;
                if (len < minLen) {
                    minLen = len;
                    result = {i, j};
                }
                break; // Found shortest starting at i, move to next i
            }
        }
    }
    return result;
}

// Helper: Print Test Info
void printTestHeader(int testId, const string& name) {
    cout << "Test #" << testId << " [" << name << "]: ";
}

// Helper: Run a single test
void runTest(int testId, const vector<string>& doc, const vector<string>& keys, string testName, int& failCount) {
    Solution sol;
    pair<int, int> expected = bruteForceReference(doc, keys);
    pair<int, int> actual = sol.findShortestSnippet(doc, keys);

    bool passed = (expected == actual);

    // Check for "Valid but different index" edge case? 
    // Usually standard sliding window finds same as greedy brute force, 
    // provided we prioritize shortest length, then earliest start.

    printTestHeader(testId, testName);
    if (passed) {
        cout << GREEN << "PASSED" << RESET << endl;
    } else {
        cout << RED << "FAILED" << RESET << endl;
        cout << "  Doc Size: " << doc.size() << ", Keys: " << keys.size() << endl;
        cout << "  Expected: {" << expected.first << ", " << expected.second << "}" << endl;
        cout << "  Actual:   {" << actual.first << ", " << actual.second << "}" << endl;
        failCount++;
    }
}

// Helper: Generate Random String
string randomString(int len) {
    static const char alphanum[] = "abcdef"; // Small alphabet to force collisions
    string s;
    for (int i = 0; i < len; ++i) s += alphanum[rand() % (sizeof(alphanum) - 1)];
    return s;
}

int mainTest() {
    srand(time(0));
    int failCount = 0;
    int testCount = 0;

    // ---------------------------------------------------------
    // PHASE 1: MANUAL CORNER CASES (10 Cases)
    // ---------------------------------------------------------

    // 1. Basic Case
    runTest(++testCount, {"world", "hello", "world", "a", "b", "hello"}, {"hello", "world"}, "Basic Match", failCount);

    // 2. Exact Match (Document == Keywords)
    runTest(++testCount, {"a", "b", "c"}, {"a", "b", "c"}, "Exact Document", failCount);

    // 3. Keywords not present
    runTest(++testCount, {"a", "b", "c"}, {"z"}, "Not Found", failCount);

    // 4. Single Word Document
    runTest(++testCount, {"a"}, {"a"}, "Single Word Match", failCount);

    // 5. Repeated Keywords in Doc
    runTest(++testCount, {"x", "y", "a", "b", "a", "c", "a"}, {"a", "c"}, "Repeated Words in Doc", failCount);
    // Expected: {4, 5} ("a", "c") length 2, vs {2, 5} ("a", "b", "a", "c") length 4

    // 6. Dense Match (Keywords adjacent)
    runTest(++testCount, {"start", "key1", "key2", "end"}, {"key1", "key2"}, "Adjacent Match", failCount);

    // 7. Keywords at ends
    runTest(++testCount, {"key1", "noise", "noise", "key2"}, {"key1", "key2"}, "Ends of Doc", failCount);

    // 8. Empty Document
    runTest(++testCount, {}, {"a"}, "Empty Doc", failCount);

    // 9. Subset logic (Doc has more than needed)
    runTest(++testCount, {"a", "b", "c", "d"}, {"b", "c"}, "Subset Match", failCount);

    // 10. Order Independence
    runTest(++testCount, {"c", "b", "a"}, {"a", "b"}, "Reverse Order", failCount);

    // ---------------------------------------------------------
    // PHASE 2: GENERATED STRESS TESTS (90 Cases)
    // ---------------------------------------------------------
    cout << "------------------------------------------------" << endl;
    cout << "Running Randomized Stress Tests (Wait for it...)" << endl;

    for (int i = 0; i < 900; ++i) {
        int docSize = (rand() % 5000) + 5; // Document size 5 to 55
        int keySize = (rand() % 50) + 1;  // Keywords size 1 to 5

        vector<string> doc;
        vector<string> keys;

        // Generate Doc
        for(int j=0; j<docSize; ++j) doc.push_back(randomString(3));

        // Generate Keys (pick from doc to ensure possibility, or random to ensure failure)
        for(int j=0; j<keySize; ++j) {
            if (rand() % 3 == 0) keys.push_back(randomString(3)); // Random word
            else keys.push_back(doc[rand() % docSize]); // Existing word
        }

        // Ensure keys are unique (Set semantics)
        sort(keys.begin(), keys.end());
        keys.erase(unique(keys.begin(), keys.end()), keys.end());

        runTest(++testCount, doc, keys, "Random Case " + to_string(i+1), failCount);
    }

    // ---------------------------------------------------------
    // SUMMARY
    // ---------------------------------------------------------
    cout << "------------------------------------------------" << endl;
    double errorRate = (double)failCount / testCount;
    cout << "Total Tests: " << testCount << endl;
    cout << "Error Rate: ";
    if (failCount == 0) cout << "\033[94m0%\033[0m" << endl;
    else cout << "\033[33m" << (errorRate * 100) << "%\033[0m" << endl;

    return 0;
}