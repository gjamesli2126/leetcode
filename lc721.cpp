#include <bits/stdc++.h>
#define testMain main
using namespace std;

class UnionFind {
private:
    std::vector<int> parents;     // parent pointers

public:
    // constructor – each node is its own parent
    explicit UnionFind(int n) : parents(n) {
        std::iota(parents.begin(), parents.end(), 0);
    }

    // path-compressed find
    int find(int id) {
        if (id != parents[id]) parents[id] = find(parents[id]);
        return parents[id];
    }

    // union by simple parent overwrite
    void unite(int id0, int id1) {
        int root0 = find(id0);
        int root1 = find(id1);
        if (root0 != root1)
            parents[root1] = root0;   // attach root1 under root0
    }
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        unordered_map<string,int> email2ID;
        vector<string> id2Email;                 // index -> email
        vector<string> id2Name;                  // index -> owner’s name

        // 1. give every distinct e-mail a unique id
        for (auto &acc : accounts) {
            const string &name = acc[0];
            for (int i = 1; i < (int)acc.size(); ++i) {
                const string &email = acc[i];
                if (!email2ID.count(email)) {
                    int id = id2Email.size();
                    email2ID[email] = id;
                    id2Email.push_back(email);
                    id2Name.push_back(name);
                }
            }
        }

        UnionFind uf(id2Email.size());

        // 2. unite all e-mails that appear in the same account
        for (auto &acc : accounts) {
            int firstID = email2ID[acc[1]];
            for (int i = 2; i < (int)acc.size(); ++i)
                uf.unite(firstID, email2ID[acc[i]]);
        }

        // 3. collect e-mails by root
        unordered_map<int, vector<string>> root2Emails;
        for (int id = 0; id < (int)id2Email.size(); ++id)
            root2Emails[uf.find(id)].push_back(id2Email[id]);

        // 4. build answer
        vector<vector<string>> merged;
        for (auto &[root, emails] : root2Emails) {
            sort(emails.begin(), emails.end());
            vector<string> acct;
            acct.push_back(id2Name[root]);   // owner’s name
            acct.insert(acct.end(), emails.begin(), emails.end());
            merged.push_back(std::move(acct));
        }
        return merged;
    }
};

// Helper: Normalize merged accounts for comparison (sort emails and then sort accounts).
void normalizeAccounts(vector<vector<string>>& accts) {
    for (auto& acct : accts) {
        sort(acct.begin() + 1, acct.end());
    }
    sort(accts.begin(), accts.end(), [](auto& a, auto& b) {
        if (a[0] != b[0]) return a[0] < b[0];
        return a < b;
    });
}

// Helper: Print accounts.
void printAccounts(const vector<vector<string>>& accts) {
    cout << "[";
    for (size_t i = 0; i < accts.size(); ++i) {
        cout << "[";
        for (size_t j = 0; j < accts[i].size(); ++j) {
            cout << "\"" << accts[i][j] << "\""
                 << (j + 1 < accts[i].size() ? ", " : "");
        }
        cout << "]" << (i + 1 < accts.size() ? ", " : "");
    }
    cout << "]";
}

// Helper: Run and verify a test case.
void runTest(int testNum,
             vector<vector<string>> accounts,
             vector<vector<string>> expected) {
    Solution sol;
    auto result = sol.accountsMerge(accounts);
    normalizeAccounts(result);
    normalizeAccounts(expected);
    bool pass = (result == expected);
    if (pass) {
        cout << "\033[1;32mTest Case " << testNum << " Passed\033[0m\n";
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed\033[0m\n";
        cout << "Expected: ";
        printAccounts(expected);
        cout << "\nGot:      ";
        printAccounts(result);
        cout << "\n";
    }
}

int testMain() {
    // Example 1
    runTest(1,
            {
                    {"John","johnsmith@mail.com","john_newyork@mail.com"},
                    {"John","johnsmith@mail.com","john00@mail.com"},
                    {"Mary","mary@mail.com"},
                    {"John","johnnybravo@mail.com"}
            },
            {
                    {"John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"},
                    {"John","johnnybravo@mail.com"},
                    {"Mary","mary@mail.com"}
            }
    );
    // Example 2
    runTest(2,
            {
                    {"Gabe","Gabe0@m.co","Gabe3@m.co","Gabe1@m.co"},
                    {"Kevin","Kevin3@m.co","Kevin5@m.co","Kevin0@m.co"},
                    {"Ethan","Ethan5@m.co","Ethan4@m.co","Ethan0@m.co"},
                    {"Hanzo","Hanzo3@m.co","Hanzo1@m.co","Hanzo0@m.co"},
                    {"Fern","Fern5@m.co","Fern1@m.co","Fern0@m.co"}
            },
            {
                    {"Ethan","Ethan0@m.co","Ethan4@m.co","Ethan5@m.co"},
                    {"Fern","Fern0@m.co","Fern1@m.co","Fern5@m.co"},
                    {"Gabe","Gabe0@m.co","Gabe1@m.co","Gabe3@m.co"},
                    {"Hanzo","Hanzo0@m.co","Hanzo1@m.co","Hanzo3@m.co"},
                    {"Kevin","Kevin0@m.co","Kevin3@m.co","Kevin5@m.co"}
            }
    );
    return 0;
}