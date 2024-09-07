#ifndef RUBIKS_CUBE_SOLVER_NIBBLEARRAY_H
#define RUBIKS_CUBE_SOOLVER_NIBBLEARRAY_H
#include <bits/stdc++.h>
using namespace std;

class NibbleArray
{
    size_t size;
    vector<uint8_t> arr;

public:
    NibbleArray(const size_t size, const int val=0xFF);
    int get(const size_t pos) const;
    void set(const size_t pos, const int val);
    unsigned char *data();
    const unsigned char *data() const;
    size_t storageSize() const;
    void inflate(vector<int> &dest) const;
    void reset(const int val=0xFF);
};

#endif