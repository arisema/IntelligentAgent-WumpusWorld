#include "IA.h"
#include "../../utilities/DataStructures.h"
#include <iostream>


namespace agent{

using namespace DataStructures;

IntelligentAgent::IntelligentAgent(){
    ;
}

DataStructures::Decision IntelligentAgent::go(std::pair<int,int> agent_location, Percepts room_perceptions){
        
    ia_sensor.add_percept(agent_location, room_perceptions);
    IntelligentAgent::decision = ia_inferer.infer(agent_location);
    return decision;
    }

}
