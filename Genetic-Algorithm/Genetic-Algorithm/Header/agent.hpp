#ifndef AGENT_HPP
#define AGENT_HPP

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

class Agent {
    public:
        int x, y;
        vector<int> gene;
        int geneSize;
        float rank;
        vector<vector<int>> walls;

        Agent(int _geneSize, vector<vector<int>> _walls);
        void fitnes();
        void move(int i);
};

#endif
