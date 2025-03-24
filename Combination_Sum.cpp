#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
void dfs(const std::vector<int>& candidates,int target,std::vector<std::vector<int>>& result,std::vector<int>& seq,int stind){
    if(target==0){
        result.emplace_back(seq);
        return;
    }
    for(int i=stind;i<candidates.size();++i){
        //+
        target-=candidates[i];
        if(target<0) break;
        seq.emplace_back(candidates[i]);
        dfs(candidates,target,result,seq,i);
        //-
        seq.pop_back();
        target+=candidates[i];
    }

}

std::vector<std::vector<int>> combination_sum(std::vector<int>& candidates, int target) {
    std::sort(candidates.begin(),candidates.end());
    std::vector<std::vector<int>> result;
    std::vector<int> sequence;
    dfs(candidates,target,result,sequence,0);
    return result;
}

template<typename T>
std::vector<T> get_words() {
    std::string line;
    std::getline(std::cin, line);
    std::istringstream ss{line};
    ss >> std::boolalpha;
    std::vector<T> v;
    std::copy(std::istream_iterator<T>{ss}, std::istream_iterator<T>{}, std::back_inserter(v));
    return v;
}

void ignore_line() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template<typename T>
void put_words(const std::vector<T>& v) {
    if (!v.empty()) {
        std::copy(v.begin(), std::prev(v.end()), std::ostream_iterator<T>{std::cout, " "});
        std::cout << v.back();
    }
    std::cout << '\n';
}

int main() {
    std::vector<int> candidates = get_words<int>();
    int target;
    std::cin >> target;
    ignore_line();
    std::vector<std::vector<int>> res = combination_sum(candidates, target);
    for (auto& row : res) {
        std::sort(row.begin(), row.end());
    }
    std::sort(res.begin(), res.end());
    for (const auto& row : res) {
        put_words(row);
    }
}
