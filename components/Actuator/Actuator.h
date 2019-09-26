#include <iostream>
#include <string>
#include <vector>
#include <tuple>

<<<<<<< HEAD
using namespace std;
=======
#include "../../utilities/DataStructures.h"

>>>>>>> master

class Actuators
{
<<<<<<< HEAD
private:
  pair<int, int> agent_location;
  string agent_direction;

public:
  Actuators(pair<int, int> agent_location, string agent_direction);

  pair<int, int> get_agent_location();
  void set_agent_location(pair<int, int>);

  string get_agent_direction();
  void set_agent_direction(string agent_direction);

  string get_room_direction(pair<int, int> room_location);
  void move_to(pair<int, int> room_location);
  void shoot_at(pair<int, int> room_location);
};
=======
    public:
        Actuator();
        ~Actuator();
        void actuate(DataStructures::Decision decision); //change return type to action
};

}
#endif;
>>>>>>> master
