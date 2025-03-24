#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#include <climits>
int min_coin_ways(const std::vector<int>& coins,int amount,int sum,std::unordered_map<int,int>& bfsmemo){
    if(sum==amount) return 0;
    if(bfsmemo.contains(sum)) return bfsmemo.at(sum);
    int ways=INT_MAX;
    if(sum>amount) return INT_MAX;
    for(int coin:coins){
        int single_result= min_coin_ways(coins,amount,sum+coin,bfsmemo);
        if(single_result==INT_MAX) continue;
        ways=std::min(ways,single_result+1);
    }
    bfsmemo[sum]=ways;
    return ways;

}
int coin_change(std::vector<int>& coins, int amount) {
    std::unordered_map<int,int> bfsmemo;
    int result=min_coin_ways(coins,amount,0,bfsmemo);
    return result==INT_MAX?-1:result;
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

int main() {
    std::vector<int> coins = get_words<int>();
    int amount;
    std::cin >> amount;
    ignore_line();
    int res = coin_change(coins, amount);
    std::cout << res << '\n';
}