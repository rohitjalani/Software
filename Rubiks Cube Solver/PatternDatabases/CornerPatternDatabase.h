#ifndef RUBIKS_CUBE_SOLVER_CORNERPATTERNDATABASE_H
#define RUBIKS_CUBE_SOLVER_CORNERPATTERNDATABASE_H

#include "../Model/RubiksCube.h"
#include "PatternDatabase.h"
#include "PermutationIndexer.h"
using namespace std;

class CornerPatternDatabase: public PatternDatabase
{
    typedef RubiksCube::FACE F;
    PermutationIndexer<8> permIndexer;

public:
    CornerPatternDatabase();
    CornerPatternDatabase(int init_val);
    int getDatabaseIndex(const RubiksCube& cube) const;
};

#endif