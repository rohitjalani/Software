#include "CornerPatternDatabase.h"
CornerPatternDatabase::CornerPatternDatabase() : PatternDatabase(100179840) {}
CornerPatternDatabase::CornerPatternDatabase(int init_val) : PatternDatabase(100179840, init_val) {}

int CornerPatternDatabase::getDatabaseIndex(const RubiksCube &cube) const
{

/*
Purpose: Retrieves the corner permutation indices of a given RubiksCube object.
Details: It fetches the corner indices using cube.getCornerIndex(i) for each of the 8 corners of the cube.
*/
    array<int, 8> cornerPerm = {
        cube.getCornerIndex(0),
        cube.getCornerIndex(1),
        cube.getCornerIndex(2),
        cube.getCornerIndex(3),
        cube.getCornerIndex(4),
        cube.getCornerIndex(5),
        cube.getCornerIndex(6),
        cube.getCornerIndex(7),
    };

/*
Purpose: Computes the lexicographic rank of the corner permutation.
Details: Utilizes the PermutationIndexer class (permIndexer) to calculate the rank based on the permutation of corner indices.
*/
    int rank = this->permIndexer.rank(cornerPerm);

/*
Purpose: Retrieves the corner orientations of the RubiksCube.
Details: Fetches the orientation values using cube.getCornerOrientation(i) for each of the 7 corners (since the orientation of one corner is determined by the others).
*/
    array<int, 7> cornerOrientation = {
        cube.getCornerOrientation(0),
        cube.getCornerOrientation(1),
        cube.getCornerOrientation(2),
        cube.getCornerOrientation(3),
        cube.getCornerOrientation(4),
        cube.getCornerOrientation(5),
        cube.getCornerOrientation(6),
    };

/*
Purpose: Calculates a unique orientation number based on the corner orientations.
Details: Converts the orientations into a single number representation, where each orientation contributes to the final number based on its position.
*/
    int orientationNum = 
        cornerOrientation[0]*729 + // 3^6
        cornerOrientation[1]*243 + // 3^5
        cornerOrientation[2]*81 + // 3^4
        cornerOrientation[3]*27 + // 3^3
        cornerOrientation[4]*9 + // 3^2
        cornerOrientation[5]*3 + // 3^1
        cornerOrientation[6]; // 3^0

/*
Purpose: Computes and returns the database index for the given cube state.
Details: Combines the rank and orientation number to produce a unique index that represents the state of the cube in the pattern database.
*/
    return (rank*2187)+orientationNum; // 3^7 is 2187
}