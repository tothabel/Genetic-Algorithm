#include "Header/simulation.hpp"
using namespace std;

Sim::Sim(){
    this->videomode = {1000, 1000};
    this->window.create(videomode, "Genetic Algorithm");
    this->window.setFramerateLimit(120);
    
    step = 0;
    generation = 0;
    
    for (int i = 0; i < POP_SIZE; i++){
        Agent newAgent(GENE_SIZE, walls);
        population.push_back(newAgent);
    }
    
    for (int i = 0; i < POP_SIZE; i++){
        sf::RectangleShape newRect(sf::Vector2f(5.f, 5.f));
        newRect.setPosition(population[i].x, population[i].y);
        newRect.setFillColor(sf::Color(179, 255, 224));
        
        rects.push_back(newRect);
    }
    
    drawingStage = true;
    drawBool = false;
    
}

void Sim::loop(){
    while (this->window.isOpen()) {
        sf::Event event;
        while (this->window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    this->window.close();
                    break;
                    
                case sf::Event::KeyReleased:
                    if (event.key.code == sf::Keyboard::Space){
                        drawingStage = !drawingStage;
                    }
                    else if (event.key.code == sf::Keyboard::R){
                        walls.clear();
                        wallsDraw.clear();
                        generation = 0;
                        population.clear();
                        
                        for (int i = 0; i < POP_SIZE; i++){
                            Agent newAgent(GENE_SIZE, walls);
                            population.push_back(newAgent);
                        }
                        cout << "\n\n\n\n\n";
                    }
                    break;
                    
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left){
                        if (drawingStage)
                            drawBool = true;
                    }
                    break;
                    
                case sf::Event::MouseMoved:
                    if (drawingStage && drawBool){
                        int x, y;
                        x = ((event.mouseMove.x + 5) / 10) * 10;
                        y = ((event.mouseMove.y + 5) / 10) * 10;
                        
                        vector<int> newWall = {x, y};
                        
                        sf::RectangleShape newWallDraw(sf::Vector2f(5.f, 5.f));
                        newWallDraw.setPosition(float(x), float(y));
                        newWallDraw.setFillColor(sf::Color(153, 0, 77));
                        
                        bool add = true;
                        for (int i = 0; i < walls.size(); i++)
                            if (newWall == walls[i])
                                add = false;
                        if (add){
                            walls.push_back(newWall);
                        
                            wallsDraw.push_back(newWallDraw);
                        }
                    }
                    
                case sf::Event::MouseButtonReleased:
                    if (event.mouseButton.button == sf::Mouse::Left)
                        drawBool = false;
                    
                default:
                    break;
            }
        }
        
        if (!drawingStage)
            compute();
        render();
    }
}

void Sim::compute(){
    random_device device;
    default_random_engine gen(device());
    
    //reproduction
    if (step >= GENE_SIZE){
        float ranks[POP_SIZE];
        vector<int> bestAgents;

        //run fitness function and get ranks then sort it in accending order
        for (int i = 0; i < POP_SIZE; i++){
            population[i].fitnes();
            ranks[i] = population[i].rank;
        }
        sort(ranks, ranks+POP_SIZE);

        //find best agents //potential error: try switching the loops
        for (int j = 1; j <= POOL_SIZE; j++){
            for (int i = 0; i < POP_SIZE; i++){
                if (ranks[POP_SIZE-j] == population[i].rank)
                    bestAgents.push_back(i);
            }
        }

        //crossover
        //
        //mutation
        for (int i = 0; i < POOL_SIZE; i++){
            for (int j = 0; j < GENE_SIZE; j++){
                uniform_int_distribution<int> mutationChance(0, MUTATION_CHANCE);
                uniform_int_distribution<int> randAllele(0, 3);

                if (mutationChance(gen) == 0)
                    population[bestAgents[i]].gene[j] = randAllele(gen);
            }
        }

        //create next population based of the best agents
        vector<Agent> nextPopulation;
        for (int i = 0; i < POP_SIZE; i++){
            Agent newAgent(GENE_SIZE, walls);
            for (int j = 0; j < GENE_SIZE; j++){
                //set genes from best parents randomly
                uniform_int_distribution<int> randAgent(0, POOL_SIZE-1);
                int parent = bestAgents[randAgent(gen)];
                newAgent.gene[j] = population[parent].gene[j];
            }

            nextPopulation.push_back(newAgent);
        }
        
        //test
        for (int i = 0; i < GENE_SIZE; i++)
           cout << population[0].gene[i];
        float avgRank = 0;
        for (int i = 0; i < POP_SIZE; i++)
            avgRank += ranks[i];
        avgRank /= POP_SIZE;
        cout << "\tavg.rank: " << avgRank << "\tgen: " << generation << "\tx: " << population[0].x << " y: " << population[0].y;
        cout << endl;
        //
        
        population = nextPopulation;
        step = 0;
        generation++;
        
    }

    //move
    for (int i = 0; i < POP_SIZE; i++){
        population[i].move(step);
        rects[i].setPosition(float(population[i].x), float(population[i].y));
    }

    step++; 
}

void Sim::render(){
    this->window.clear(sf::Color(0, 172, 230));
    
    for (int i = 0; i < POP_SIZE; i++)
        window.draw(rects[i]);
    for (int i = 0; i < wallsDraw.size(); i++)
        window.draw(wallsDraw[i]);
    if (TARGET){
        sf::RectangleShape target(sf::Vector2f(50.f, 50.f));
        target.setFillColor(sf::Color(0, 255, 255));
        target.setPosition(475, 50);
        window.draw(target);
    }
    
    this->window.display();
}
