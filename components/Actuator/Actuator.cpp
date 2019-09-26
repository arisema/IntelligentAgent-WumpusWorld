#include "Actuators.h"

/**
 * [Actuators::Actuators initilize the Actuator with the agent_location and agent_direction]
 * @param agent_location  [current location of the agent in pair<int, int> format]
 * @param agent_direction [current direction of the agent in pair<int, int> format]
 */
Actuators::Actuators(pair<int, int> agent_location, string agent_direction)
{
  Actuators::agent_location = agent_location;
  Actuators::agent_direction = agent_direction;
}

/**
 * [get_agent_location getter agent_location attribute]
 * @return [agent_location in pair<int, int> format]
 */
pair<int, int> Actuators::get_agent_location()
{
  return Actuators::agent_location;
}

/**
 * [set_agent_location setter for agent_location attribute]
 * @param agent_location [agent_location in pair<int, int> format]
 */
void Actuators::set_agent_location(pair<int, int> agent_location)
{
  Actuators::agent_location = agent_location;
}

/**
 * [get_agent_direction getter for agent_direction attribute]
 * @return [agent_direction in string format]
 */
string Actuators::get_agent_direction()
{
  return Actuators::agent_direction;
}
/**
 * @brief A wrapper function that will navigate based on obtained decisions
 *
 * @param decision Decision obtained from inference class infer function
 */
void Actuator::actuate(Decision decision)
{
    //todo
}

/**
 * [set_agent_direction setter for agent_direction]
 * @param agent_location [agent_location in string format]
 */
void Actuators::set_agent_direction(string agent_direction)
{
  Actuators::agent_direction = agent_direction;
}

/**
 * [get_room_direction find room room direction relative to the agent_location]
 * @param  room_location [room_location in pair<int, int> format]
 * @return               [calcuated room direction in string format]
 */
string Actuators::get_room_direction(pair<int, int> room_location)
{
  string room_direction;
  if(room_location.first - agent_location.first > 0) {
    room_direction = "top";
  }else if(room_location.first - agent_location.first < 0) {
    room_direction = "bottom";
  }else if(room_location.second - agent_location.second > 0) {
    room_direction = "right";
  }else {
    room_direction = "left";
  }
  return room_direction;
}

/**
 * [move_to decide how the move_to a give room action will be implemented]
 * @param room_location [room_location in pair<int, int> format]
 */
void Actuators::move_to(pair<int, int> room_location)
{
  string room_direction = get_room_direction(room_location);
  string agent_direction = get_agent_direction();

  pair<int, int> updated_agent_location;
  pair<int, int> updated_agent_direction;
  if(room_direction == agent_direction) {
    updated_agent_location = Actuator.shoot();
    // if room direction is in the top
  }else if(room_direction == "top" && agent_direction =="right") {
    updated_agent_direction = Actuator.move_left();
    updated_agent_location = Actuators.move_forward();
  }else if(room_direction == "top" && agent_direction =="bottom") {
    updated_agent_location = Actuators.move_backward();
  }else if(room_direction == "top" && agent_direction =="left") {
    updated_agent_direction = Actuator.move_right();
    updated_agent_location = Actuators.move_forward();
    // if room direction is in the right
  }else if(room_direction == "right" && agent_direction =="top") {
    updated_agent_direction = Actuator.move_right();
    updated_agent_location = Actuators.move_forward();
  }else if(room_direction == "right" && agent_direction =="bottom") {
    updated_agent_direction = Actuator.move_left();
    updated_agent_location = Actuators.move_forward();
  }else if(room_direction == "right" && agent_direction =="left") {
    updated_agent_location = Actuators.move_backward();
    // if room direction is in the bottom
  }else if(room_direction == "bottom" && agent_direction =="top") {
    updated_agent_location = Actuators.move_backward();
  }else if(room_direction == "bottom" && agent_direction =="right") {
    updated_agent_direction = Actuator.move_right();
    updated_agent_location = Actuators.move_forward();
  }else if(room_direction == "bottom" && agent_direction =="left") {
    updated_agent_direction = Actuator.move_left();
    updated_agent_location = Actuators.move_forward();
    // if agent direction is in the left
  }else if(room_direction == "left" && agent_direction =="top") {
    updated_agent_direction = Actuator.move_left();
    updated_agent_location = Actuators.move_forward();
  }else if(room_direction == "left" && agent_direction =="right") {
    updated_agent_location = Actuators.move_backward();
  }else if(room_direction == "left" && agent_direction =="bottom") {
    updated_agent_direction = Actuator.move_left();
    updated_agent_location = Actuators.move_forward();
  }
  set_agent_location(updated_agent_location);
  set_agent_direction(updated_agent_direction);
}

/**
 * [shoot_at decide how shoot_at action will be implemented]
 * @param wumpus_location [ infered wumpus_location in pair<int,int> format]
 */
void Actuators::shoot_at(pair<int, int> wumpus_location)
{
  string wumpus_direction = get_room_direction(wumpus_location);
  string agent_direction = get_agent_direction();

  pair<int, int> updated_agent_direction;

  if(wumpus_direction == agent_direction) {
    updated_agent_location = Actuator.shoot();
    // if room direction is in the top
  }else if(wumpus_direction == "top" && agent_direction =="right") {
    updated_agent_direction = Actuator.move_left();
    updated_agent_location = Actuators.shoot();
  }else if(wumpus_direction == "top" && agent_direction =="bottom") {
    updated_agent_direction = Actuator.move_left();
    updated_agent_direction = Actuator.move_left();
    updated_agent_location = Actuators.shoot();
  }else if(wumpus_direction == "top" && agent_direction =="left") {
    updated_agent_direction = Actuator.move_right();
    updated_agent_location = Actuators.shoot();
    // if room direction is in the right
  }else if(wumpus_direction == "right" && agent_direction =="top") {
    updated_agent_direction = Actuator.move_right();
    updated_agent_location = Actuators.shoot();
  }else if(wumpus_direction == "right" && agent_direction =="bottom") {
    updated_agent_direction = Actuator.move_left();
    updated_agent_location = Actuators.shoot();
  }else if(wumpus_direction == "right" && agent_direction =="left") {
    updated_agent_direction = Actuator.move_left();
    updated_agent_direction = Actuator.move_left();
    updated_agent_location = Actuators.shoot();
    // if room direction is in the bottom
  }else if(wumpus_direction == "bottom" && agent_direction =="top") {
    updated_agent_direction = Actuator.move_right();
    updated_agent_direction = Actuator.move_right();
    updated_agent_location = Actuators.shoot();
  }else if(wumpus_direction == "bottom" && agent_direction =="right") {
    updated_agent_direction = Actuator.move_right();
    updated_agent_location = Actuators.shoot();
  }else if(wumpus_direction == "bottom" && agent_direction =="left") {
    updated_agent_direction = Actuator.move_left();
    updated_agent_location = Actuators.shoot();
    // if agent direction is in the left
  }else if(wumpus_direction == "left" && agent_direction =="top") {
    updated_agent_direction = Actuator.move_left();
    updated_agent_location = Actuators.shoot();
  }else if(wumpus_direction == "left" && agent_direction =="right") {
    updated_agent_direction = Actuator.move_left();
    updated_agent_direction = Actuator.move_left();
    updated_agent_location = Actuators.shoot();
  }else if(wumpus_direction == "left" && agent_direction =="bottom") {
    updated_agent_direction = Actuator.move_left();
    updated_agent_location = Actuators.shoot();
  }
  set_agent_direction(updated_agent_direction);
}
