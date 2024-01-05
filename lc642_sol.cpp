// represents a Trie node
class Node {
public:
    unordered_map<char, Node*> children;
    unordered_map<string, int> counter;
    
    Node() {
    }
};

class AutocompleteSystem {
public:
    typedef pair<string, int> wordFreq;

    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
        root = new Node();
        for(int i = 0; i < sentences.size(); i ++) insert(sentences[i], times[i]);
        curNode = root;
    }
    
    vector<string> input(char c) {
        vector<string> hot;
        if(c == '#') {
            // reset everything
            insert(prefix, 1);
            prefix = "";
            curNode = root;
            return hot;
        }
        
        prefix += c;
        // Previously already reached the end || the current char doesn't match
        if(! curNode || ! curNode->children[c]) {
            curNode = nullptr;
            return hot;
        }
        
        auto cmp = [](wordFreq& w1, wordFreq& w2) {
            if(w1.second == w2.second) return w1.first > w2.first;
            return w1.second < w2.second;
        };
        priority_queue<wordFreq, vector<wordFreq>, decltype(cmp)> pq(cmp);
        
        for(auto e : curNode->children[c]->counter) {
            pq.push(make_pair(e.first, e.second));       
        }
        curNode = curNode->children[c];
        
        while(hot.size() < 3 && ! pq.empty()) {
            hot.push_back(pq.top().first);
            pq.pop();
        }
        return hot;
    }
    
private:
    Node* root;
    Node* curNode;
    string prefix;
    
    void insert(string& sentence, int times) {
        Node* cur = root;
        for(auto ch : sentence) {
            if(! cur->children[ch]) {
                cur->children[ch] = new Node();
            }
            cur = cur->children[ch];
            cur->counter[sentence] += times;
        }
    }
};