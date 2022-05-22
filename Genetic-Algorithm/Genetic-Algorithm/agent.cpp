#include "agent.hpp"
random_device device;
default_random_engine gen(device());

Agent::Agent(int _geneSize, vector<vector<int>> _walls){
    x = 500;
    y = 1000;

    rank = 0;

    geneSize = _geneSize;

    uniform_int_distribution<int> dir(0, 3);
    for (int i = 0; i < geneSize; i++){
        gene.push_back(dir(gen));
    }
    
    walls = _walls;
}

void Agent::move(int i){
    int direction = gene[i];
    switch (direction)
    {
    case 0:
        if (x > 5){
            bool allow = true;
            for (int i = 0; i < walls.size(); i++){
                if (x - 10 == walls[i][0] && y == walls[i][1]){
                    allow = false;
                    break;
                }
            }
            if (allow)
                x -= 10;
        }
        break;
        case 1:
            if (x < 995){
                bool allow = true;
                for (int i = 0; i < walls.size(); i++){
                    if (x + 10 == walls[i][0] && y == walls[i][1]){
                        allow = false;
                        break;
                    }
                }
                if (allow)
                    x += 10;
            }
            break;
        case 2:
            if (y > 5){
                bool allow = true;
                for (int i = 0; i < walls.size(); i++){
                    if (y - 10 == walls[i][1] && x == walls[i][0]){
                        allow = false;
                        break;
                    }
                }
                if (allow)
                    y -= 10;
            }
            break;
        case 3:
            if (y < 995){
                bool allow = true;
                for (int i = 0; i < walls.size(); i++){
                    if (y + 10 == walls[i][1] && x == walls[i][0]){
                        allow = false;
                        break;
                    }
                }
                if (allow)
                    y += 10;
            }
            break;
    
    default:
        break;
    }
}

void Agent::fitnes(){
    //rank = -(abs(500-x)+abs(500-y)); //go to middle
    //rank = x*x; //go to right hand side
    //rank = x*y; //go to the bottom right
    //rank = -1*(y*y);
    
    //target
    if (x <= 525 && x >= 475 && y >= 50 && y <= 100)
        rank = 9999;
    else
        rank = -1 * (float(sqrt(pow(x - 500, 2) + pow(y - 75, 2) * 1.0)));
}
