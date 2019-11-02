#include "../../../agent/IntelligentAgent/IA.h"
#include "../../../utilities/DataStructures.h"
#include <iostream>
#include <cxxtest/TestSuite.h>

using namespace std;
using namespace DataStructures;

class go : public CxxTest::TestSuite
{
private:
  agent::IntelligentAgent ia = agent::IntelligentAgent();
  map<pair<int, int>, Percepts> world;

public:
    bool decision_comparator(Decision decision1, Decision decision2){
      if((decision1.decision == decision2.decision) && (decision1.location == decision2.location)){
        return true;
      }else{
        return false;
      }
    }
    void test_cases1(void)
    {
        world[make_pair(0,1)].stench = true;
        world[make_pair(0,3)].stench = true;
        world[make_pair(1,2)].stench = true;

        world[make_pair(1,2)].breeze = true;
        world[make_pair(2,1)].breeze = true;
        world[make_pair(2,3)].breeze = true;
        world[make_pair(3,0)].breeze = true;
        world[make_pair(3,2)].breeze = true;

        Decision agent_decision1_opt1;
        Decision agent_decision1_opt2;
        pair<int, int> room1 = make_pair(0, 0);
        agent_decision1_opt1.decision = move_to;
        agent_decision1_opt1.location = make_pair(0, 1);
        agent_decision1_opt2.decision = move_to;
        agent_decision1_opt2.location = make_pair(1, 0);

        Decision agent_decision2;
        pair<int, int> room2 = make_pair(0, 1);
        agent_decision2.decision = move_to;
        agent_decision2.location = make_pair(0, 0);

        Decision agent_decision3_opt1;
        Decision agent_decision3_opt2;
        pair<int, int> room3 = make_pair(1, 0);
        agent_decision3_opt1.decision = move_to;
        agent_decision3_opt1.location = make_pair(1, 1);
        agent_decision3_opt2.decision = move_to;
        agent_decision3_opt2.location = make_pair(2, 0);

        Decision agent_decision4_opt1;
        Decision agent_decision4_opt2;
        pair<int, int> room4 = make_pair(1, 1);
        agent_decision4_opt1.decision = move_to;
        agent_decision4_opt1.location = make_pair(1, 2);
        agent_decision4_opt2.decision = move_to;
        agent_decision4_opt2.location = make_pair(2, 1);

        TS_ASSERT( decision_comparator(agent_decision1_opt1, ia.go(room1, world[room1])) || decision_comparator(agent_decision1_opt2, ia.go(room1, world[room1])));
        TS_ASSERT( decision_comparator(agent_decision2, ia.go(room2, world[room2])));
        TS_ASSERT( decision_comparator(agent_decision3_opt1, ia.go(room3, world[room3])) || decision_comparator(agent_decision3_opt2, ia.go(room3, world[room3])));
        TS_ASSERT( decision_comparator(agent_decision4_opt1, ia.go(room4, world[room4])) || decision_comparator(agent_decision4_opt2, ia.go(room4, world[room4])));
    }

    void test_cases2(void)
    {
        world[make_pair(1,0)].breeze = true;
        world[make_pair(2,1)].breeze = true;
        world[make_pair(3,0)].breeze = true;
        world[make_pair(1,2)].breeze = true;
        world[make_pair(3,2)].breeze = true;
        world[make_pair(2,3)].breeze = true;

        world[make_pair(0,2)].stench = true;
        world[make_pair(1,1)].stench = true;
        world[make_pair(1,3)].stench = true;
        world[make_pair(2,2)].stench = true;

        Decision agent_decision1_opt1;
        Decision agent_decision1_opt2;
        pair<int, int> room1 = make_pair(0, 0);
        agent_decision1_opt1.decision = move_to;
        agent_decision1_opt1.location = make_pair(0, 1);
        agent_decision1_opt2.decision = move_to;
        agent_decision1_opt2.location = make_pair(1, 0);

        Decision agent_decision2;
        pair<int, int> room2 = make_pair(1, 0);
        agent_decision2.decision = move_to;
        agent_decision2.location = make_pair(0, 0);

        Decision agent_decision3;
        pair<int, int> room3 = make_pair(0, 2);
        agent_decision3.decision = move_to;
        agent_decision3.location = make_pair(0, 1);

        Decision agent_decision4_opt1;
        Decision agent_decision4_opt2;
        pair<int, int> room4 = make_pair(1, 1);
        agent_decision4_opt1.decision = move_to;
        agent_decision4_opt1.location = make_pair(0, 1);
        agent_decision4_opt2.decision = move_to;
        agent_decision4_opt2.location = make_pair(1, 0);

        TS_ASSERT( decision_comparator(agent_decision1_opt1, ia.go(room1, world[room1])) || decision_comparator(agent_decision1_opt2, ia.go(room1, world[room1])));
        TS_ASSERT( decision_comparator(agent_decision2, ia.go(room2, world[room2])));
        TS_ASSERT( decision_comparator(agent_decision3, ia.go(room3, world[room3])));
        TS_ASSERT( decision_comparator(agent_decision4_opt1, ia.go(room4, world[room4])) || decision_comparator(agent_decision4_opt2, ia.go(room4, world[room4])));
    }
};
