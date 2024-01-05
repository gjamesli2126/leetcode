#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Trie {
private:
    struct TrieNode{
        unordered_map<char,TrieNode*> children;
        bool isWord=false;
        ~TrieNode(){
            for(auto &[c,t]:children) delete t;
        }
    };
    TrieNode *root;
public:
    Trie() {
        root=new TrieNode();
    }
    ~Trie(){
        delete root;
    }
    void insert(string word) {
        TrieNode *cur=root;
        for(const char& c:word){
            if(!cur->children.contains(c))
                cur->children[c]=new TrieNode();
            cur=cur->children[c];
        }
        cur->isWord=true;
    }

    bool search(string word) {
        TrieNode *cur=root;
        for(const char& c:word){
            if(!cur->children.contains(c)) return false;
            cur=cur->children[c];
        }
        return cur->isWord;
    }

    bool startsWith(string prefix) {
        TrieNode *cur=root;
        for(const char& c:prefix){
            if(!cur->children.contains(c)) return false;
            cur=cur->children[c];
        }
        return true;
    }

};

int mainTest() {
    // Test sequence and expected results
    vector<pair<string, vector<string>>> testSequence = {
            {"insert", {"apple"}},
            {"search", {"apple"}},       // true
            {"search", {"app"}},         // false
            {"startsWith", {"app"}},     // true
            {"insert", {"app"}},
            {"search", {"app"}},         // true
            {"insert", {"applesauce"}},
            {"search", {"applesauce"}},  // true
            {"startsWith", {"apple"}},   // true
            {"startsWith", {"apples"}},  // true
            {"search", {"appl"}},        // false
    };

    vector<bool> expectedResults = {true, false, true, true, true, true, true, false};

    Trie trie;
    int resultIndex = 0;

    for (const auto& test : testSequence) {
        if (test.first == "insert") {
            trie.insert(test.second[0]);
        } else if (test.first == "search") {
            bool result = trie.search(test.second[0]);
            cout << "Test " << resultIndex + 1 << ": "
                 << "search(\"" << test.second[0] << "\") -> "
                 << (result ? "true" : "false") << ", Expected: " << (expectedResults[resultIndex] ? "true" : "false")
                 << ", Status: " << (result == expectedResults[resultIndex++] ? "PASS" : "FAIL") << endl;
        } else if (test.first == "startsWith") {
            bool result = trie.startsWith(test.second[0]);
            cout << "Test " << resultIndex + 1 << ": "
                 << "startsWith(\"" << test.second[0] << "\") -> "
                 << (result ? "true" : "false") << ", Expected: " << (expectedResults[resultIndex] ? "true" : "false")
                 << ", Status: " << (result == expectedResults[resultIndex++] ? "PASS" : "FAIL") << endl;
        }
    }

    return 0;
}