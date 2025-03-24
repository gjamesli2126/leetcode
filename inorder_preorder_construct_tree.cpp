#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

template<typename T>
struct Node {
    T val;
    Node<T>* left;
    Node<T>* right;

    explicit Node(T val, Node<T>* left = nullptr, Node<T>* right = nullptr)
            : val{val}, left{left}, right{right} {}

    ~Node() {
        delete left;
        delete right;
    }
};
Node<int>* construct_with_pre_in(const std::unordered_map<int,int>& val_to_ind_map,const std::vector<int>& preorder,int pre_st_ind,int in_st_ind,unsigned int tree_size){
    if(tree_size<=0) return nullptr;
    int root_val=preorder.at(pre_st_ind);
    int inorder_root_ind=val_to_ind_map.at(root_val);
    int leftTreeSize=inorder_root_ind-in_st_ind;

    Node<int>* left_tree= construct_with_pre_in(val_to_ind_map,preorder,pre_st_ind+1,in_st_ind,leftTreeSize);
    Node<int>* right_tree= construct_with_pre_in(val_to_ind_map,preorder,pre_st_ind+1+leftTreeSize,inorder_root_ind+1,tree_size-1-leftTreeSize);
    return new Node(root_val,left_tree,right_tree);
}
//preorder: 第一個是 root
//in-order: root的左邊是 left, 右邊是 right
//要用 preorder定位 root 去 in-order找 Then 得出 left,right 所以要 建立 inorder的 val_index map
Node<int>* construct_binary_tree(std::vector<int>& preorder, std::vector<int>& inorder) {
    std::unordered_map<int,int> val_to_ind;
    for(int i=0;i<inorder.size();++i){
        val_to_ind[inorder[i]]=i;
    }
    return construct_with_pre_in(val_to_ind,preorder,0,0,inorder.size());
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

template<typename T, typename F>
void format_tree(Node<T>* node, F f, std::vector<std::string>& out) {
    if (node == nullptr) {
        out.emplace_back("x");
        return;
    }
    out.emplace_back(f(node->val));
    format_tree(node->left, f, out);
    format_tree(node->right, f, out);
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
    std::vector<int> preorder = get_words<int>();
    std::vector<int> inorder = get_words<int>();
    Node<int>* res = construct_binary_tree(preorder, inorder);
    std::vector<std::string> res_vec;
    format_tree(res, [](auto v) { return std::to_string(v); }, res_vec);
    put_words(res_vec);
}