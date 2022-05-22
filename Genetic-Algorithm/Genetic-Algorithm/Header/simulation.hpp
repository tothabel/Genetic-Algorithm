#ifndef simulation_hpp
#define simulation_hpp

#include <SFML/Graphics.hpp>
#include "agent.hpp"
#include <random>
#include <iostream>
#include <algorithm>
#include <vector>
#include "SFML/Graphics.hpp"

using namespace std;

class Sim{
private:
    sf::VideoMode videomode;
    sf::RenderWindow window;
    
    const int POP_SIZE = 1000; //number of agents in each generation
    const int GENE_SIZE = 200; //how many steps can the agents take before dying
    const int POOL_SIZE = 100; //the number of agents selected for reproduction
    const int MUTATION_CHANCE = 1000; // 1/mutationchance
    const bool TARGET = true;
    int step;

    vector<Agent> population;
    
    int generation;
    
    vector<sf::RectangleShape> rects;
    
    vector<vector<int>> walls;
    bool drawingStage;
    vector<sf::RectangleShape> wallsDraw;
    bool drawBool;
    
public:
    Sim();
    void loop();
    void compute();
    void render();
    void draw(int x, int y);
};

#endif
