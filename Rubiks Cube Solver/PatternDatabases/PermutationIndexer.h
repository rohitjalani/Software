/*
This PermutationIndexer class is designed to facilitate efficient computation of the lexicographic rank (index) of permutations.
*/
#ifndef RUBIKS_CUBE_SOLVER_PERMUTATIONINDEXER_H
#define RUBIKS_CUBE_SOLVER_PERMUTATIONINDEXER_H
#include <bits/stdc++.h>
#include <math.h>
using namespace std;

template <size_t N, size_t K=N>
class PermutationIndexer
{
    /*
    Precomputed table containing the number of setbits in the binary
    representation of each number (from 1 to 2^N - 2).  The largest N-bit number is
    2^N-1 = (1 << N) - 1.
    */

   array<int, (1<<N)-1> onesCountLookup;

   /*
   Precomputed table of factorials (or "picks" if N!=K). They're in reverse order.
   */
  array<int, K> factorials;

public:

/*
Computes onesCountLookup: For each integer from 0 to 2^𝑁 − 2, it calculates the number of 1s in its binary representation and stores it in onesCountLookup.
Computes factorials: Computes factorials (or "picks") in reverse order based on N and K.
*/
    PermutationIndexer()
    {
        for(int i=0;i<(1<<N)-1;i++)
        {
            bitset<N> bits(i);
            this->onesCountLookup[i] = bits.count();
        }

        for(int i=0;i<K;i++)
        {
            this->factorials[i] = pick(N-1-i, K-1-i);
        }
    }

/*
Purpose: Calculates the lexicographic rank (index) of a permutation provided as an array perm of size K.
Steps:
    Initializes lehmer to store the Lehmer code, which represents the permutation in a factorial number system.
    Uses seen to track which elements of the permutation have been "seen".
    Calculates numOnes to determine how many elements to the left of each element in perm have already been seen.
    Converts the Lehmer code to base-10 index using precomputed factorials.
*/
    int rank(const array<int, K>& perm) const
    {
        array<int, K> lehmer;
        bitset<N> seen;
        lehmer[0] = perm[0];
        seen[N-1-perm[0]] = 1;

        for(int i=1;i<K;i++)
        {
            seen[N-1-perm[i]] = 1;
            int numOnes = this->oneCountLookup[seen.to_ulong()>>(N-perm[i])];
            lehmer[i] = perm[i]-numOnes;
        }

        int index = 0;
        for(int i=0;i<K;i++)
        {
            index += lehmer[i]*this->factorial[i];
        }

        return index;
    }
};

#endif