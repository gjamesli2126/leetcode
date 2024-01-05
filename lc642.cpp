#include <bits/stdc++.h>
using namespace std;
#define mainTest main
class AutocompleteSystem {
private:


public:
    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {

    }

    vector<string> input(char c) {

    }
};

int mainTest() {
    // Test initialization data
    vector<string> sentences = {"i love you", "island", "iroman", "i love leetcode"};
    vector<int> times = {5, 3, 2, 2};

    // Create AutocompleteSystem object
    AutocompleteSystem* obj = new AutocompleteSystem(sentences, times);

    // Test input data and expected outputs
    vector<char> inputs = {'i', ' ', 'a', '#'};
    vector<vector<string>> expectedOutputs = {
            {"i love you", "island", "i love leetcode"},
            {"i love you", "i love leetcode"},
            {},
            {}
    };

    // Perform tests
    for (int i = 0; i < inputs.size(); ++i) {
        vector<string> actualOutput = obj->input(inputs[i]);
        bool status = (actualOutput == expectedOutputs[i]);
        cout << "Test " << i + 1 << ": "
             << "Input: '" << inputs[i] << "', "
             << "Expected: [";
        for (size_t j = 0; j < expectedOutputs[i].size(); ++j) {
            cout << "\"" << expectedOutputs[i][j] << "\"";
            if (j < expectedOutputs[i].size() - 1) cout << ", ";
        }
        cout << "], Actual: [";
        for (size_t j = 0; j < actualOutput.size(); ++j) {
            cout << "\"" << actualOutput[j] << "\"";
            if (j < actualOutput.size() - 1) cout << ", ";
        }
        cout << "], Status: " << (status ? "PASS" : "FAIL") << endl;
    }

    // Clean up
    delete obj;

    return 0;
}
