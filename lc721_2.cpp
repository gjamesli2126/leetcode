#include <bits/stdc++.h>
#define testMain main
using namespace std;
//true time complex: n × m × α(n × m) + n × m × log(n × m)
class UnionFind{
private:
    vector<int> this_parent;
public:
    explicit UnionFind(int n):this_parent(n){
        iota(this_parent.begin(),this_parent.end(),0);//begin,end, start_from_val
    };
    int find_parent(int this_id){
        if(this_id!=this_parent[this_id]) this_parent[this_id]= find_parent(this_parent[this_id]);
        return this_parent[this_id];
    }
    void unite(int id1,int id2){
        int root1=find_parent(id1);
        int root2=find_parent(id2);
        if(root1!=root2) this_parent[root2]=root1;
    }
};
struct nameANDemails{
    string name;
    vector<string> emails;
};
class Solution {
    //unordered_map: email->cluster_id
    //vector<struct>: cluster_id-> {name, emailS}
    unordered_map<string,int> email_clusterID;//is ans
    vector<nameANDemails> clusterID_struct;

public:
    //time: account number: n, have max m email in each account
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        //1. create 支離破碎 graph, time: O(mn)
        for(vector<string>& account:accounts){
            const string& name=account[0];
            nameANDemails nae{.name=name};
            for(int i=1;i<(int)account.size();i++){
                const string& email=account[i];
                if(!email_clusterID.contains(email)){
                    email_clusterID[email]=(int)clusterID_struct.size();//assign each email with the cluster ID
                }
                nae.emails.push_back(email);
            }
            clusterID_struct.emplace_back(nae);
        }
        //2. unite, find true cluster ID
        UnionFind uf((int)email_clusterID.size());//time O(mn)
        //try unite, of course each cluster has it's ID correct, but what if other cluster actually share the same cluster ID with us? so need to do the following
        for(const vector<string>& account:accounts){//time O(mn*a(mn))
            int id1=email_clusterID[account[1]];
            for(int i=2;i<(int)account.size();i++){
                uf.unite(id1,email_clusterID[account[i]]);
            }
        }
        //3. collect the ans
        unordered_map<int,vector<string>> rootID2emails;
        for(const auto& [email,id]:email_clusterID){//time: O(mn*a(mn))
            rootID2emails[uf.find_parent(id)].push_back(email);//<----O(a(mn))
        }
        //4. So we succcessfully gather the ans, build the ans to align return
        /*time complex for step4:
         * If you had naively written “O(nm·(nm log(nm)))”,
         * that’d assume each of the ~nm clusters has ~nm emails in it—and so you’d sort nm items nm times,
         * which isn’t what happens. Instead, the emails are partitioned among clusters,
         * and each email only contributes to one sort and one copy,
         * so you sum once over all nm emails rather than multiply.
         * */
        vector<vector<string>> ans;
        for(auto& [id,emails]:rootID2emails){//time: O(mnlog(mn)+mn)
            vector<string> eachEntry;
            eachEntry.push_back(clusterID_struct[id].name);
            sort(emails.begin(),emails.end());
            for(const auto& email:emails) eachEntry.push_back(email);
            ans.emplace_back(move(eachEntry));
        }
        return ans;
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
    // Test 3: a long chain that loops back and crosses multiple owners
    runTest(3,
            {
                    {"Alice","alice@mail.com","bob@mail.com"},
                    {"Bob","bob@mail.com","charlie@mail.com"},
                    {"Charlie","charlie@mail.com","alice@mail.com","dave@mail.com"},
                    {"Eve","eve@mail.com"},
                    {"Alice","alice@mail.com","zoe@mail.com","eve@mail.com"}
            },
            {
                    // all of alice/bob/charlie/dave/eve/zoe collapse into one group
                    {"Alice",
                     "alice@mail.com",
                     "bob@mail.com",
                     "charlie@mail.com",
                     "dave@mail.com",
                     "eve@mail.com",
                     "zoe@mail.com"
                    }
            }
    );


    // — Very Long Chain Test —
    const int L = 200000;                     // number of accounts
    vector<vector<string>> bigAccounts;
    bigAccounts.reserve(L);

    // account i links email[i] ↔ email[i+1]
    for (int i = 0; i < L; ++i) {
        bigAccounts.push_back({
                                      "User",
                                      "e" + to_string(i)     + "@bigtest.com",
                                      "e" + to_string(i + 1) + "@bigtest.com"
                              });
    }

    // run it!
    auto start = chrono::steady_clock::now();
    auto merged = Solution().accountsMerge(bigAccounts);
    auto end   = chrono::steady_clock::now();

    double secs = chrono::duration<double>(end - start).count();
    cout << "Merged " << L << " accounts ("
         << L + 1 << " emails) into "
         << merged.size() << " group(s) in "
         << secs << " s\n";

    return 0;
}