#include <iostream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

class Actuators
{
private:
  pair<int, int> agent_location;
  string agent_direction;

public:
  Actuators(pair<int, int> agent_location, string agent_direction);

  pair<int, int> get_agent_location();
  void set_agent_location(pair<int, int> agent_location);

  pair<int, int> get_agent_direction();
  void set_agent_direction(pair<int, int> agent_location);

  string room_direction(pair<int, int> room_location);
  void move_to(pair<int, int> room_location);
  void shoot_at(pair<int, int> room_location);
}
