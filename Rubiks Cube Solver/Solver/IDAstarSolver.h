#include <bits/stdc++.h>
#include "../Model/RubiksCube.h"
#include "../PatternDatabases/CornerPatternDatabase.h"

#ifndef RUBIKS_CUBE_SOLVER_IDASTARSOLVER_H
#define RUBIKS_CUBE_SOLVER_IDASTARSOLVER_H

template<typename T, typename H>

class IDAstarSolver
{
private:
    CornerPatternDatabase cornerDB;
    vector<RubiksCube::MOVE> moves;
    unordered_map<T, RubiksCube::MOVE, H> move_done;
    unordered_map<T, bool, H> visited;


/*
Node: A nested struct representing a state in the search, containing cube (current cube state), depth (depth in the search tree), 
and estimate (heuristic estimate of the remaining moves to solve the cube).
*/
    struct Node
    {
        T cube;
        int depth;
        int estimate;

        Node(T _cube, int _depth, int _estimate):cube(_cube), depth(_depth), estimate(_estimate) {};
    };

/*
Defines a comparator for nodes in the priority queue based on the sum of depth and estimate. It prioritizes nodes with a lower sum.
*/
    struct compareCube
    {
        bool operator()(pair<Node, int> const &p1, pair<Node, int> const &p2)
        {
            auto n1 = p1.first;
            auto n2 = p2.first;
            if(n1.depth+n1.estimate == n2.depth+n2.estimate)
            {
                return n1.estimate>n2.estimate;
            }
            else
            {
                return n1.depth+n1.estimate>n2.depth+n2.estimate;
            }
        };
    };

    void resetStructure()
    {
        moves.clear();
        move_done.clear();
        visited.clear();
    }

// returns {solved cube, bound}: if the cube was solved
// returns {rubiksCube, next_bound}, if the cube was not solved

/*
Private Function IDAstar(int bound):
    Implements the IDA* algorithm to iteratively search for the solution within a given bound.
    Uses a priority queue (pq) to expand nodes based on their estimated cost (depth + estimate).
    Updates next_bound based on the minimum cost encountered that exceeds the current bound.
    Returns a pair consisting of the solved cube state and the final bound when the cube is solved.
*/
    pair<T, int> IDAstar(int bound)
    {
        priority_queue<pair<Node, int>, vector<pair<Node, int>>, compareCube> pq;
        Node start = Node(rubiksCube, 0, cornerDB.getNumMoves(rubiksCube));
        pq.push(make_pair(start, 0));
        int next_bound = 100;
        while(!pq.empty())
        {
            auto p = pq.top();
            Node node = p.first;
            pq.pop();

            if(visited[node.cube]) continue;

            visited[node.cube] = true;
            move_done[node.cube] = RubiksCube::MOVE(p.second);

            if(node.cube.isSolved()) 
            {
                return make_pair(node.cube, bound);
            }

            node.depth++;
            for(int i=0;i<18;i++)
            {
                node.estimate = cornerDB.getNumMoves(node.cube);
                if(node.estimate+node.depth > bound)
                {
                    next_bound = min(next_bound, node.estimate+node.depth);
                }
                else
                {
                    pq.push(make_pair(node, i));
                }
            }
            node.cube.invert(curr_move);
        }
    }

public:
    T rubiksCube;
    IDAstarSolver(T _rubiksCube, string fileName)
    {
        rubiksCube = _rubiksCube;
        cornerDB.fromFile(fileName);
    }

    vector<RubiksCube::MOVE> solve()
    {
        int bound = 1;
        auto p = IDAstar(bound);
        while(p.second != bound)
        {
            resetStructure();
            bound = p.second;
            p = IDAstar(bound);
        }

        T solved_cube = p.first;
        assert(solved_cube.isSolved());
        T curr_cube = solved_cube;
        while(!(curr_cube == rubiksCube))
        {
            RubiksCube::MOVE curr_move = move_done[curr_cube];
            moves.push_back(curr_move);
            curr_move.invert(curr_move);
        }
        rubiksCube = solved_cube;
        reverse(moves.begin(), moves.end());
        return moves;
    }
};

#endif // RUBIKS_CUBE_SOLVER_IDASTARSOLVER_H