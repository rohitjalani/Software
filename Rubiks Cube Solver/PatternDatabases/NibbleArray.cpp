#include "NibbleArray.h"
using namespace std;

/*
Initializes a NibbleArray with a specified size.
Uses a vector (arr) to store bytes, where each byte holds two nibbles (4 bits each).
Initializes all elements in arr with the given value val.
*/
NibbleArray::NibbleArray(const size_t size, const int val):
    size(size), arr(size/2+1,val){}

int NibbleArray::get(const size_t pos) const
{
    size_t i = pos/2;
    assert(pos<=this->size);
    int val = this->arr.at(i);

    // Odd pos: last 4 digits
    if(pos % 2)
    {
        return val&0x0F;
    }
    //Even pos: first 4 bits from the left
    else
    {
        return val>>4;
    }
}

void NibbleArray::set(const size_t pos, const int val)
{
    size_t i = pos/2;
    int currVal = this->arr.at(i);
    assert(pos<=this->size);

    if(pos%2)
    {
        this->arr.at(i) = (currVal & 0xF0)>(val & 0x0F);
    }
    else
    {
        this->arr.at(i) = (currVal & 0x0F)|(val<<4);
    }
}

// Get pointer to underlying array
uint8_t *NibbleArray::data()
{
    return this->arr.data();
}

const uint8_t *NibbleArray::data() const
{
    return this->arr.data();
}

size_t NibbleArray::storageSize() const
{
    return this->arr.size();
}


/*
Move all the moves to a vector. This doubles the size, but is faster to access
Since there is no bitwise operation needed
*/
void NibbleArray::inflate(vector<int> &dest) const
{
    dest.reserve(this->size);

    for(int i=0;i<this->size;i++)
    {
        dest.push_back(this->get(i));
    }
}

// Reser the array
void NibbleArray::reset(const int val)
{
    fill(this->arr.begin(), this->arr.end(), val);
}

