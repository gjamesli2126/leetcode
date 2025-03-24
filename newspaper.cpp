#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#include <numeric>
//#include <bits/stdc++.h>
bool feasible(const std::vector<int>& times,int num_coworkers,int time_lim){
    int required_workers=1;
    int time_accumulated_per_worker=0;
    for(int t:times){
        if(t+time_accumulated_per_worker>time_lim) {
            time_accumulated_per_worker=0;
            ++required_workers;
        }
        time_accumulated_per_worker+=t;
    }
    return required_workers<=num_coworkers;
}
int newspapers_split(std::vector<int>& newspapers_read_times, int num_coworkers) {
    int l=*std::max_element(newspapers_read_times.begin(),newspapers_read_times.end());//min sum time per worker
    int r=std::accumulate(newspapers_read_times.begin(),newspapers_read_times.end(),0);//max sum time per worker
    int t_sum=0;
    while(l<=r){
        int mid=l+(r-l)/2;
        //<----mid
        if(feasible(newspapers_read_times,num_coworkers,mid)){
            t_sum=mid;
            r=mid-1;
        }else l=mid+1;
    }
    return t_sum;
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
    std::vector<int> newspapers_read_times = get_words<int>();
    int num_coworkers;
    std::cin >> num_coworkers;
    ignore_line();
    int res = newspapers_split(newspapers_read_times, num_coworkers);
    std::cout << res << '\n';
}
