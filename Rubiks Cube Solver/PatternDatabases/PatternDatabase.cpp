#include "PatternDatabase.h"
using namespace std;

/*
- numMoves: Number(min) of moves required to reach a particular cube state
- database: Type-'NibbleArray', Purpose: Holds the data of the pattern database, where each element represents the number of moves (in nibbles) required to solve a specific cube state.
          Usage: Utilizes a compact representation to efficiently store large amounts of data, with each entry representing a cube state in the form of 4-bit values (nibbles).
- size: Total size of the pattern database(number of unique cube states that pattern database can hold)
- numItems: Purpose: Keeps track of the number of entries in the pattern database that have been set.
          Usage: Helps determine how many cube states have been evaluated and stored in the database.

*/
PatternDatabase::PatternDatabase(const size_t size): // Initializes database of size with 0 initial values
    database(size, 0xFF), size(size), numItems(0)
    {}

PatternDatabase::PatternDatabase(const size_t size, int init_val): // Initializes database of size with init_val initial values
    database(size, init_val), size(size), numItems(0)
    {}

// Sets number of moves required for a specific index 'ind' cube state in pattern database
bool PatternDatabase::setNumMoves(const int ind, const int numMoves)
{
    int oldMoves = this->getNumMoves(ind);

    // New items getting added
    if(oldMoves == 0xF)
    {
        ++this->numItems;
    }

    if(oldMoves > numMoves)
    {
        this->database.set(ind, numMoves);
        return true;
    }

    return false;
}

// Sets number of moves required for a specific cube state 'cube' in pattern database
bool PatternDatabase::setNumMoves(const RubiksCube &cube, const int numMoves)
{
    return this->setNumMoves(this->getDatabaseIndex(cube),numMoves);
}

// Returns number of moves for the index 'ind' cube state
int PatternDatabase::getNumMoves(const int ind) const
{
    return this->database.get(ind);
}

// Uses cube's database index to get the number of moves using cube state 'cube'
int PatternDatabase::getNumMoves(const RubiksCube &cube) const
{
    return this->getNumMoves(this->getDatabaseIndex(cube));
}

// Get size of database
size_t PatternDatabase::getSize() const
{
    return this->size;
}

// Returns number of items in database
size_t PatternDatabase::getNumItems() const
{
    return this->numItems;
}

// Checks if database is full
bool PatternDatabase::isFull() const
{
    return this->numItems==this->size;
}

/*
toFile(const string &filePath) const writes the database to a file.
    Opens a file for writing in binary mode.
    Writes the contents of the database to the file.
    Closes the file.
*/
void PatternDatabase::toFile(const string &filePath) const
{
    ofstream writer(filePath, ios::out | ios::trunc);

    if(!writer.is_open())
    {
        throw "Failed to open the file to write";
    }

    writer.write(
        reinterpret_cast<const char*>(this->database.data()),
        this->database.storageSize()
    );

    writer.close();
}

/*
fromFile(const string &filePath) reads the database from a file.
    Opens a file for reading in binary mode.
    Checks if the file size matches the expected database size.
    Reads the contents of the file into the database.
    Closes the file and sets numItems to the size of the database.
*/
bool PatternDatabase::fromFile(const string &filePath)
{
    ifstream reader(filePath, ios::in|ios::ate);


    if(!reader.is_open())
    {
        return false;
    }

    size_t fileSize = reader.tellg();
    
    if(fileSize != this->database.storageSize())
    {
        reader.close();
        throw "Database corrupt! Failed to open Reader";
    }

    reader.seekg(0, ios::beg);
    reader.read(
        reinterpret_cast<char*> (this->database.data()),
        this->database.storageSize()
    );

    reader.close();
    this->numItems = this->size;
    return true;
}

/*
inflate() creates a vector containing all the values in the database, expanded from their nibble representation.
reset() resets the database to its initial state with all entries set to 0xFF and numItems set to 0.
*/
vector<int> PatternDatabase::inflate() const
{
    vector<int> inflated;
    this->database.inflate(inflated);
    return inflated;
}

void PatternDatabase::reset()
{
    if(this->numItems != 0)
    {
        this->database.reset(0xFF);
        this->numItems = 0;
    }
}
