#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

using namespace std;

// ==========================================
// 1. The Interface (面試官給的骨架)
// ==========================================
class Iterator {
public:
    // 回傳下一個元素
    virtual int next() = 0;
    // 是否還有元素
    virtual bool hasNext() = 0;
    // 虛擬解構子 (Good practice)
    virtual ~Iterator() = default;
};

// ==========================================
// 2. The Solution (你要實作的部分)
// ==========================================
class MergingIterator : public Iterator {
private:
    // 定義 Heap 的節點
    struct Node {
        int val;
        int iterIndex; // 紀錄是哪一個 Iterator 的值

        // Min-Heap 需要大於運算符 (反直覺，但 STL 是這樣設計的)
        bool operator>(const Node& other) const {
            return val > other.val;
        }
    };

    // 儲存所有的 Iterators (使用 pointer 以避免 copy)
    const vector<Iterator*>& iters;
    // Min-Heap
    priority_queue<Node, vector<Node>, greater<Node>> pq;

public:
    MergingIterator(const vector<Iterator*>& iterators) : iters(iterators) {
        // 初始化：把每個 Iterator 的第一個值丟進 Heap
        for (int i = 0; i < iters.size(); ++i) {
            if (iters[i] && iters[i]->hasNext()) {
                pq.push({iters[i]->next(), i});
            }
        }
    }

    bool hasNext() override {
        return !pq.empty();
    }

    int next() override {
        if (!hasNext()) throw runtime_error("No such element");

        // 1. 取出最小的
        Node top = pq.top();
        pq.pop();
        int res = top.val;
        int idx = top.iterIndex;

        // 2. 把該 Iterator 的下一個值補進去
        if (iters[idx]->hasNext()) {
            pq.push({iters[idx]->next(), idx});
        }

        return res;
    }
};

// ==========================================
// 3. Concrete Helper (為了測試而寫的模擬器)
// ==========================================
// 這不是題目核心，但你需要寫這個才能在 main 裡跑
class TestIterator : public Iterator {
    vector<int> data;
    int cur = 0;
public:
    TestIterator(vector<int> v) : data(v) {}

    bool hasNext() override { return cur < data.size(); }
    int next() override { return data[cur++]; }
};

// ==========================================
// 4. MainTest (Non fan-out / Sequential)
// ==========================================
int main() {
    // Test Case 1: Standard overlapping
    {
        cout << "Running Test 1: Standard Case... ";

        // 準備資料
        TestIterator* it1 = new TestIterator({1, 5, 9});
        TestIterator* it2 = new TestIterator({2, 6});
        TestIterator* it3 = new TestIterator({3, 4, 10});

        vector<Iterator*> inputs = {it1, it2, it3};
        MergingIterator merger(inputs);

        vector<int> expected = {1, 2, 3, 4, 5, 6, 9, 10};
        vector<int> actual;

        while(merger.hasNext()) {
            actual.push_back(merger.next());
        }

        assert(actual == expected);
        cout << "PASSED" << endl;

        // 清理記憶體 (面試時如果時間緊迫可省略，但寫出來更加分)
        delete it1; delete it2; delete it3;
    }

    // Test Case 2: Empty inputs
    {
        cout << "Running Test 2: Empty Case... ";

        TestIterator* it1 = new TestIterator({});
        TestIterator* it2 = new TestIterator({});

        vector<Iterator*> inputs = {it1, it2};
        MergingIterator merger(inputs);

        assert(merger.hasNext() == false);
        cout << "PASSED" << endl;

        delete it1; delete it2;
    }

    // Test Case 3: Jagged / Some empty
    {
        cout << "Running Test 3: Jagged Case... ";

        TestIterator* it1 = new TestIterator({});
        TestIterator* it2 = new TestIterator({10});
        TestIterator* it3 = new TestIterator({});

        vector<Iterator*> inputs = {it1, it2, it3};
        MergingIterator merger(inputs);

        assert(merger.next() == 10);
        assert(merger.hasNext() == false);
        cout << "PASSED" << endl;

        delete it1; delete it2; delete it3;
    }

    cout << "All tests passed." << endl;
    return 0;
}