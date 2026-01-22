#include <bits/stdc++.h>
#define mainTest main
using namespace std;

// ==========================================
//  USER SOLUTION (Sliding Window - O(N))
// ==========================================
class Solution {
public:
    pair<int, int> findShortestSnippet(const vector<string>& document, const unordered_set<string>& keywords) {
        if(keywords.empty() || document.empty()) return {-1,0};
        int startIdx=-1;
        int minLen=INT_MAX;
        int formed=0;
        int left=0;
        int requried=keywords.size();
        unordered_map<string,int> window_counts;
        for(int right=0;right<document.size();right++){
            const string& new_word=document[right];
            if(keywords.contains(new_word)){
                window_counts[new_word]++;
                if(window_counts[new_word]==1) ++formed;
            }
            //shrink the shit
            while(left<=right && formed==requried){
                // 越短越合法
                if(right-left+1<minLen){
                    startIdx=left;
                    minLen=right-left+1;
                }
                //開縮小 from left
                const string& old_word=document[left];
                --window_counts[old_word];
                if(!window_counts[old_word]) --formed;
                ++left;
            }
        }
        return startIdx==-1?pair<int,int>{-1,0}:pair<int,int>{startIdx,minLen};

    }
};

// ==========================================
//  TEST HELPERS
// ==========================================

void printResult(const vector<string>& doc, const unordered_set<string>& keys, pair<int, int> res, int expectedLen) {
    bool passed = (expectedLen == -1 && res.first == -1) || (res.second == expectedLen);

    if (passed) {
        cout << "\033[32m[PASS]\033[0m ";
    } else {
        cout << "\033[31m[FAIL]\033[0m ";
    }

    // Print details
    cout << "Exp: " << expectedLen << ", Got: " << res.second;
    if (res.first != -1) {
        cout << " | Snippet: { ";
        for(int i=0; i<res.second; ++i) cout << doc[res.first + i] << " ";
        cout << "}";
    } else {
        cout << " | Result: Not Found";
    }
    cout << endl;
}

struct TestCase {
    string name;
    vector<string> doc;
    unordered_set<string> keys;
    int expectedLen;
};

// ==========================================
//  MAIN TEST DRIVER
// ==========================================
int mainTest() {
    Solution sol;

    vector<TestCase> tests = {
            // --- BASIC CASES ---
            {"Basic Example",
                    {"this", "is", "a", "test", "document", "for", "search"},
                    {"test", "for"}, 3}, // "test", "document", "for"

            {"Reversed Order",
                    {"world", "hello"},
                    {"hello", "world"}, 2},

            // --- CORNER CASES: EMPTY & MISSING ---
            {"Empty Document",
                    {},
                    {"a", "b"}, -1},

            {"Empty Keywords",
                    {"a", "b", "c"},
                    {}, -1},

            {"Keyword Not In Doc",
                    {"a", "b", "c", "d"},
                    {"a", "z"}, -1}, // 'z' is missing

            // --- CORNER CASES: BOUNDARIES ---
            {"Match at Start",
                    {"a", "b", "x", "y", "z"},
                    {"a", "b"}, 2},

            {"Match at End",
                    {"x", "y", "z", "a", "b"},
                    {"a", "b"}, 2},

            {"Whole Document Match",
                    {"a", "b", "c"},
                    {"a", "b", "c"}, 3},

            // --- CORNER CASES: DUPLICATES & SHRINKING ---
            {"Duplicate Keywords in Doc (Shrink Left)",
                    {"a", "a", "a", "b"},
                    {"a", "b"}, 2}, // Should pick the last "a" and "b" -> {a, b}

            {"Sandwiched Match (Optimization)",
                    {"a", "b", "c", "d", "a", "b"},
                    {"b", "c"}, 2}, // {b, c} is better than {c, d, a, b}

            {"Dense Duplicates",
                    {"x", "a", "b", "a", "b", "a", "x"},
                    {"a", "b"}, 2}, // "a", "b" or "b", "a"

            {"Single Word Match",
                    {"a"},
                    {"a"}, 1},

            // --- CORNER CASES: SUBSET ---
            {"Doc smaller than Keys",
                    {"a", "b"},
                    {"a", "b", "c"}, -1},
    };

    cout << "=== RUNNING CORNER CASE TESTS ===" << endl;
    for (const auto& t : tests) {
        cout << left << setw(35) << t.name << " : ";
        pair<int, int> res = sol.findShortestSnippet(t.doc, t.keys);
        printResult(t.doc, t.keys, res, t.expectedLen);
    }

    // --- STRESS TEST ---
    cout << endl << "=== STRESS TEST (Random Data) ===" << endl;
    // Simple brute force check for random correctness
    int stressTests = 100;
    int passedStress = 0;

    srand(time(0));
    for(int i=0; i<stressTests; i++) {
        // Generate small random case to verify strict correctness
        int docSize = 10 + rand() % 20;
        vector<string> doc;
        for(int j=0; j<docSize; j++) doc.push_back(string(1, 'a' + (rand() % 5))); // vocabulary a-e

        unordered_set<string> keys;
        int keyCount = 1 + rand() % 3;
        for(int j=0; j<keyCount; j++) keys.insert(string(1, 'a' + (rand() % 5)));

        // Run Optimized
        pair<int, int> optRes = sol.findShortestSnippet(doc, keys);

        // Run Brute Force (Ground Truth)
        int bfMin = INT_MAX;
        for(int start=0; start<docSize; start++) {
            unordered_set<string> found;
            for(int end=start; end<docSize; end++) {
                if(keys.count(doc[end])) found.insert(doc[end]);
                if(found.size() == keys.size()) {
                    bfMin = min(bfMin, end - start + 1);
                    break;
                }
            }
        }
        if (bfMin == INT_MAX) bfMin = 0; // Not found notation for comparison

        if (optRes.second == bfMin) passedStress++;
        else {
            cout << "Stress Fail! Doc: ";
            for(auto s:doc) cout << s;
            cout << " Keys: ";
            for(auto k:keys) cout << k;
            cout << " Exp: " << bfMin << " Got: " << optRes.second << endl;
            break;
        }
    }

    cout << "Stress Results: " << passedStress << "/" << stressTests << " Passed." << endl;

    return 0;
}