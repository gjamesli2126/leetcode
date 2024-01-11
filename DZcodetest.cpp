#include<bits/stdc++.h>
using namespace std;
class Sol{
private:
    unordered_set<string> bankSet,visited;
    unordered_map<char,unordered_set<char>> possible{
            {'A',{'G','T','C'}},
            {'G',{'A','T','C'}},
            {'T',{'A','G','C'}},
            {'C',{'A','G','T'}}
    };
public:
    int fuckyouGene(const string& start,const string& end,const vector<string>& bank){
        if(start!=end && bank.empty()) return -1;
        if(start==end) return 0;

        for(const string& s:bank) bankSet.insert(s);
        deque<pair<int,string>> dq;
        dq.push_back({0,start});

        while(!dq.empty()){
            auto [times,gene]=dq.front();
            dq.pop_front();
            if(gene==end) return times;
            visited.insert(gene);
            for(int i=0;i<8;++i){
                char g=gene[i];
                for(const char& nxg:possible[g]){
                    gene[i]=nxg;
                    if(!visited.contains(gene)&&bankSet.contains(gene)){
                        dq.emplace_back(times+1,gene);
                    }
                    gene[i]=g;
                }
            }

        }
        return -1;
    }
};
int main(){
    Sol sol;
    string startGene = "AACCGGTT";
    string endGene = "AAACGGTA";
    vector<string> bank = {"AACCGGTA","AACCGCTA","AAACGGTA"};
    int ans=sol.fuckyouGene(startGene,endGene,bank);
    cout<<ans<<endl;

    Sol sol2;
    startGene = "AACCGGTT";
    endGene = "AACCGCTA";
    bank = {"AACCGGTA","AACCGCTA","AAACGGTA"};
    ans=sol2.fuckyouGene(startGene,endGene,bank);
    cout<<ans<<endl;
}
/*
A gene string can be represented by an 8-character long string, with choices from 'A', 'C', 'G', and 'T'.

Suppose we need to investigate a mutation from a gene string startGene to a gene string
endGene where one mutation is defined as one single character changed in the gene string.

For example, "AACCGGTT" --> "AACCGGTA" is one mutation.
There is also a gene bank bank that records all the valid gene mutations. A gene must be in bank to make it a valid gene string.

Given the two gene strings startGene and endGene and the gene bank bank, return the minimum number of mutations
needed to mutate from startGene to endGene. If there is no such a mutation, return -1.

Note that the starting point is assumed to be valid, so it might not be included in the bank.

Example 1:
Input: startGene = "AACCGGTT", endGene = "AACCGGTA", bank = ["AACCGGTA"]
Output: 1

Example 2:
Input: startGene = "AACCGGTT", endGene = "AAACGGTA", bank = ["AACCGGTA","AACCGCTA","AAACGGTA"]
Output: 2

Example 3:
st"AACCGGTT"
->"AACCGGTA"
->"AACCGCTA"
ed"AACCGCTA"
["AACCGGTA","AACCGCTA","AAACGGTA"]
Output = 3
Expected = 2
*/

