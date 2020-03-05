#include "agent/IntelligentAgent/IA.h"
#include <iostream>
#include <map>
#include <thread>
#include <chrono>


using namespace DataStructures;
using namespace std;

map<pair<int, int>, Percepts> world;

void analyze_decision(Decision decision){
    if (decision.decision == movement_decision::move_to){
        std::cout << "move to " << decision.location.first << "," << decision.location.second << std::endl;
    }
    else if (decision.decision == movement_decision::shoot_at){
        std::cout << "shoot at " << decision.location.first << "," << decision.location.second << std::endl;
    } 
}

void init_world(){
    //initialize a test world

    //-----------------------
    // s |     | b | P |
    // W | s,b | P | b |
    // s |     | b | P |
    // a |     |   | b |
    //-----------------------

    world[make_pair(0,1)].stench = true;

    world[make_pair(0,3)].stench = true;

    world[make_pair(1,2)].stench = true;
    world[make_pair(1,2)].breeze = true;

    world[make_pair(2,1)].breeze = true;
    
    world[make_pair(2,3)].breeze = true;

    world[make_pair(3,0)].breeze = true;

    world[make_pair(3, 2)].breeze = true;
}

void init_world2(){
    //initialize a test world

    //-----------------------
    // s |     | b | P |
    // W | s,b | P | b |
    // s |     | b | P |
    // a |     |   | b |
    //-----------------------

    world[make_pair(1,0)].breeze = true;

    world[make_pair(2,1)].breeze = true;

    world[make_pair(3,0)].breeze = true;

    world[make_pair(1,2)].breeze = true;

    world[make_pair(3,2)].breeze = true;
    
    world[make_pair(2,3)].breeze = true;

    world[make_pair(0,2)].stench = true;

    world[make_pair(1,1)].stench = true;

    world[make_pair(1,3)].stench = true;
}

int main(){

    agent::IntelligentAgent ia = agent::IntelligentAgent();
    Decision agent_decision;

    init_world2();

    pair<int, int> r = make_pair(0,0);

    while(true){
        agent_decision = ia.go(r, world[r]);
    
        analyze_decision(agent_decision);

        r = agent_decision.location;
        std::chrono::milliseconds timespan(11100);
        std::this_thread::sleep_for(timespan);
    }
    return 0;
}
