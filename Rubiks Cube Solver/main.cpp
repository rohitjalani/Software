// g++ -fdiagnostics-color=always -g main.cpp Model/RubiksCube.cpp Model/RubiksCube1dArray.cpp Solver/BFSSolver.h -o main.exe

#include <bits/stdc++.h>
#include "Model/RubiksCube1dArray.cpp"
#include "Solver/BFSSolver.h"
#include "Solver/DFSSolver.h"
#include "Solver/IDDFSSolver.h"

using namespace std;

int main() 
{
   RubiksCube1dArray object1dArray;

   if (object1dArray.isSolved()) cout << "SOLVED\n\n";
   else cout << "NOT SOLVED\n\n";

   object1dArray.u();
   object1dArray.print();

   object1dArray.l();
   object1dArray.print();

   object1dArray.f();
   object1dArray.print();

   object1dArray.r();
   object1dArray.print();

   object1dArray.b();
   object1dArray.print();

   object1dArray.d();
   object1dArray.print();

   if (object1dArray.isSolved()) cout << "SOLVED\n\n";
   else cout << "NOT SOLVED\n\n";

   object1dArray.dPrime();
   object1dArray.print();

   object1dArray.bPrime();
   object1dArray.print();

   object1dArray.rPrime();
   object1dArray.print();

   object1dArray.fPrime();
   object1dArray.print();

   object1dArray.lPrime();
   object1dArray.print();

   object1dArray.uPrime();
   object1dArray.print();

   if (object1dArray.isSolved()) cout << "SOLVED\n\n";
   else cout << "NOT SOLVED\n\n";


   // Create two Cubes ------------------------------------------------------------------------------------------

   RubiksCube1dArray cube1;
   RubiksCube1dArray cube2;

  // Equality and assignment of cubes --------------------------------------------------------------------------

   if(cube1 == cube2) cout << "Is equal\n";
   else cout << "Not Equal\n";

   cube1.randomShuffleCube(1);

   if(cube1 == cube2) cout << "Is equal\n";
   else cout << "Not Equal\n";

   cube2 = cube1;

   if(cube1 == cube2) cout << "Is equal\n";
   else cout << "Not Equal\n";


  // Unordered_map of Cubes  ------------------------------------------------------------------------------------

   unordered_map<RubiksCube1dArray, bool, Hash1d> mp1;

   mp1[cube1] = true;
   cube2.randomShuffleCube(8);
   if (mp1[cube1]) cout << "Cube1 is present\n";
   else cout << "Cube1 is not present\n";

   if (mp1[cube2]) cout << "Cube2 is present\n";
   else cout << "Cube2 is not present\n";

// BFS Solver -----------------------------------------------------------------------------------------------------
   cout<<" -------------- BFS Solver -------- "<<"\n";
   RubiksCube1dArray cubeBFS;
   cubeBFS.print();

   vector<RubiksCube::MOVE> shuffle_movesBFS = cubeBFS.randomShuffleCube(5);
   for(auto move: shuffle_movesBFS) cout << cubeBFS.getMove(move) << " ";
   cout << "\n";
   cubeBFS.print(); //print cube

   BFSSolver<RubiksCube1dArray, Hash1d> bfsSolver(cubeBFS);
   vector<RubiksCube::MOVE> solve_movesBFS = bfsSolver.solve();

   for(auto move: solve_movesBFS) cout << cubeBFS.getMove(move) << " ";
   cout<<"BFS Solved"<<"\n";
   cout << "\n";
   bfsSolver.rubiksCube.print();

// DFS Solver -----------------------------------------------------------------------------------------------------
   cout<<" -------------- DFS Solver -------- "<<"\n";
   RubiksCube1dArray cubeDFS;
   cubeDFS.print();

   vector<RubiksCube::MOVE> shuffle_movesDFS = cubeDFS.randomShuffleCube(5);
   for(auto move: shuffle_movesDFS)
   {
      cout<<cubeDFS.getMove(move)<<" ";
   }
   cout<<"\n";
   cubeDFS.print();

   DFSSolver<RubiksCube1dArray, Hash1d> dfsSolver(cubeDFS);
   vector<RubiksCube::MOVE> solve_movesDFS = dfsSolver.solve();

   for(auto move: solve_movesDFS)
   {
      cout<<cubeDFS.getMove(move)<<" ";
   }
   cout<<"DFS Solved"<<"\n";
   cout<<"\n";
   dfsSolver.rubiksCube.print();



// IDDFS Solver -----------------------------------------------------------------------------------------------------
   cout<<" -------------- IDDFS Solver -------- "<<"\n";
   RubiksCube1dArray cubeIDDFS;
   cubeIDDFS.print();

   vector<RubiksCube::MOVE> shuffle_movesIDDFS = cubeIDDFS.randomShuffleCube(5);
   for(auto move: shuffle_movesIDDFS)
   {
      cout<<cubeIDDFS.getMove(move)<<" ";
   }
   cout<<"\n";
   cubeDFS.print();

   IDDFSSolver<RubiksCube1dArray, Hash1d> iddfsSolver(cubeIDDFS);
   vector<RubiksCube::MOVE> solve_movesIDDFS = iddfsSolver.solve();

   for(auto move: solve_movesIDDFS)
   {
      cout<<cubeIDDFS.getMove(move)<<" ";
   }
   cout<<"IDDFS Solved"<<"\n";
   cout<<"\n";
   iddfsSolver.rubiksCube.print();
   
   return 0;
}