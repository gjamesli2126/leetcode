#include<bits/stdc++.h>
using namespace std;
#define mainTest main
/*
 * Below is the interface for Iterator, which is already defined for you.
 * **DO NOT** modify the interface for Iterator.
 */
class Iterator {
    struct Data;
    Data* data;
public:
    Iterator(const vector<int>& nums);
    Iterator(const Iterator& iter);//copy constructor

    // Returns the next element in the iteration.
    int next();

    // Returns true if the iteration has more elements.
    bool hasNext() const;
};


class PeekingIterator : public Iterator {
public:
    PeekingIterator(const vector<int>& nums) : Iterator(nums) {
        // Initialize any member here.
        // **DO NOT** save a copy of nums and manipulate it directly.
        // You should only use the Iterator interface methods.
    }

    // Returns the next element in the iteration without advancing the iterator.
    int peek() {
        return Iterator(*this).next();
    }

    // hasNext() and next() should behave the same as in the Iterator interface.
    // Override them if needed.
    int next() {
        return Iterator::next();
    }

    bool hasNext() const {
        return Iterator::hasNext();
    }
};

/*
 * In the PeekingIterator class, the peek method is designed to return the next element in the iteration without advancing the iterator. To achieve this, the method creates a temporary copy of the current PeekingIterator object and then calls the next method on this temporary copy.

The line return Iterator(*this).next(); is doing exactly that. It creates a temporary Iterator object by copying the current PeekingIterator object (*this refers to the current object). Then, it calls the next method on this temporary Iterator object. This way, the next method is executed on the temporary object, and the current object's state remains unchanged, allowing the peek method to return the next element without advancing the iterator.

By using this approach, the PeekingIterator class can provide the peek functionality while still adhering to the interface and behavior of the underlying Iterator class.
 * */