#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

template<class T>
class UnionFind{
private:
    std::unordered_map<T,T> repr;
public:
    T find(const T& me){
        if(!repr.contains(me)) repr[me]=me;
        if(repr[me]!=me) repr[me]=find(repr[me]);
        return repr[me];
    }
    void _union(const T& node1,const T& node2){
        T node1_repr=find(node1);
        T node2_repr=find(node2);
        repr[node2_repr]=node1_repr;
    }
};

class SameSet {
private:
    UnionFind<int> dsu;
public:
    void merge(int x, int y) {
        dsu._union(x,y);
    }

    bool is_same(int x, int y) {
        return dsu.find(x)==dsu.find(y);
    }
};
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
    SameSet sol;
    int query_length;
    std::cin >> query_length;
    ignore_line();
    for (int i = 0; i < query_length; i++) {
        std::vector<std::string> segs = get_words<std::string>();
        std::string op = segs.at(0);
        int x = std::stoi(segs.at(1));
        int y = std::stoi(segs.at(2));
        if (op == "union") {
            sol.merge(x, y);
        } else if (op == "is_same") {
            bool res = sol.is_same(x, y);
            std::cout << std::boolalpha << res << '\n';
        }
    }
}
