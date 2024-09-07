#ifndef RUBIKS_CUBE_SOLVER_PATTERNDATABASE_H
#define RUBIKS_CUBE_SOLVER_PATTERNDATABASE_H

#include "NibbleArray.h"
#include "../Model/RubiksCube.h"
#include "bits/stdc++.h"
using namespace std;

class PatternDatabase
{
    NibbleArray database;
    size_t size;
    size_t numItems;

    PatternDatabase();

public:
    PatternDatabase(const size_t size);
    PatternDatabase(const size_t size, int init_val);

    virtual int getDatabaseIndex(const RubiksCube &cube) const=0;

    virtual bool setNumMoves(const RubiksCube &cube, const int numMoves);

    virtual bool setNumMoves(const int ind, const int numMoves);

    virtual int getNumMoves(const RubiksCube &cube) const;

    virtual int getNumMoves(const int ind) const;

    virtual size_t getSize() const;

    virtual size_t getNumItems() const;

    virtual bool isFull() const;

    virtual void toFile(const string &filePath) const;

    virtual bool fromFile(const string &filePath);

    virtual vector<int> inflate() const;

    virtual void reset();
};

#endif