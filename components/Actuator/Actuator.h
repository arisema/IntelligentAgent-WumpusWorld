#ifndef  Actuator_H
#define Actuator_H

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include "../../utilities/DataStructures.h"

namespace components{

class Actuator
{
private:
  std::pair<int, int> agent_location;
  std::string agent_direction;

public:
  Actuator(std::pair<int, int> agent_location, std::string agent_direction);

  std::pair<int, int> get_agent_location();
  void set_agent_location(std::pair<int, int>);

  std::string get_agent_direction();
  void set_agent_direction(std::string agent_direction);

  std::string get_room_direction(std::pair<int, int> room_location);
  void move_to(std::pair<int, int> room_location);
  void shoot_at(std::pair<int, int> room_location);

  void actuate(DataStructures::Decision decision);
};
}
#endif
