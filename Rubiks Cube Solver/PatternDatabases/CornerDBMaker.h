#ifndef RUBIKS_CUBE_SOLVER_CORNERDBMAKER_H
#define RUBIKS_CUBE_SOLVER_CORNERDBMAKER_H
#include "CornerPatternDatabase.h"
using namespace std;

class CornerDBMaker
{
private:
    string fileName;
    CornerPatternDatabase cornerDb;

public:
    CornerDBMaker(string _fileName);
    CornerDBMaker(string _fileName, int init_val);

    bool bfsAndStore();
};

#endif