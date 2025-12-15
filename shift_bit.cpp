#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    unsigned int swapEvenOddBits(unsigned int x) {
        unsigned int msk_odd=0xAAAAAAAA;//0b10101010,,,,,10
        unsigned int msk_even=0x55555555;//0b010101.....01
        return (x&msk_odd)>>1 | (x&msk_even)<<1;
    }
};

int mainTest() {
    Solution sol;

    // Test 1: 0b00000000 => expect 0
    unsigned int t1 = 0b00000000;
    cout << "Input: " << bitset<8>(t1)
         << " -> Output: " << bitset<8>(sol.swapEvenOddBits(t1))
         << " (Expected: 00000000)" << endl;

    // Test 2: 0b00000001 => expect 0b00000010
    unsigned int t2 = 0b00000001;
    cout << "Input: " << bitset<8>(t2)
         << " -> Output: " << bitset<8>(sol.swapEvenOddBits(t2))
         << " (Expected: 00000010)" << endl;

    // Test 3: 0b00000010 => expect 0b00000001
    unsigned int t3 = 0b00000010;
    cout << "Input: " << bitset<8>(t3)
         << " -> Output: " << bitset<8>(sol.swapEvenOddBits(t3))
         << " (Expected: 00000001)" << endl;

    // Test 4: 0b10101010 => expect 0b01010101
    unsigned int t4 = 0b10101010;
    cout << "Input: " << bitset<8>(t4)
         << " -> Output: " << bitset<8>(sol.swapEvenOddBits(t4))
         << " (Expected: 01010101)" << endl;

    // Test 5: 0b11110000 => expect 0b11110000
    unsigned int t5 = 0b11110000;
    cout << "Input: " << bitset<8>(t5)
         << " -> Output: " << bitset<8>(sol.swapEvenOddBits(t5))
         << " (Expected: 11110000)" << endl;

    // Test 6: 0b11001100 => expect 0b11001100
    unsigned int t6 = 0b11001100;
    cout << "Input: " << bitset<8>(t6)
         << " -> Output: " << bitset<8>(sol.swapEvenOddBits(t6))
         << " (Expected: 11001100)" << endl;

    return 0;
}