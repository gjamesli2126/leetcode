#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
void dfs(const std::vector<int>& nums,int depth,std::vector<int>& seq,std::vector<std::vector<int>>& result){
    if(depth==nums.size()) {
        result.emplace_back(seq);
        return;
    }
    //+
    seq.emplace_back(nums[depth]);
    dfs(nums,1+depth,seq,result);
    //-
    seq.pop_back();
    dfs(nums,1+depth,seq,result);
}
std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    std::vector<int> seq;
    dfs(nums,0,seq,result);
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

template<typename T>
void put_words(const std::vector<T>& v) {
    if (!v.empty()) {
        std::copy(v.begin(), std::prev(v.end()), std::ostream_iterator<T>{std::cout, " "});
        std::cout << v.back();
    }
    std::cout << '\n';
}

int main() {
    std::vector<int> nums = get_words<int>();
    std::vector<std::vector<int>> res = subsets(nums);
    for (auto& row : res) {
        std::sort(row.begin(), row.end());
    }
    std::sort(res.begin(), res.end());
    for (const auto& row : res) {
        put_words(row);
    }
}
