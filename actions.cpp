
Actuators::Actuators(pair<int, int> agent_location, string agent_direction)
{
  Actuators::agent_location = agent_location;
  Actuators::agent_direction = agent_direction;
}

pair<int, int> get_agent_location()
{
  return Actuators::agent_location;
}

void set_agent_location(pair<int, int> agent_location)
{
  Actuators::agent_location = agent_location;
}

pair<int, int> get_agent_direction()
{
  return Actuators::agent_direction;
}
void set_agent_direction(pair<int, int> agent_location)
{
  Actuators::agent_location = agent_location;
}

string get_room_direction(pair<int, int> room_location)
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

void move_to(pair<int, int> room_location)
{
  string room_direction = get_room_direction(room_location);
  pair<int, int> updated_agent_location;
  pair<int, int> updated_agent_direction
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

void move_to(pair<int, int> room_location)
{
  string room_direction = get_room_direction(room_location);
  pair<int, int> updated_agent_direction
  if(room_direction == agent_direction) {
    updated_agent_location = Actuator.shoot();
    // if room direction is in the top
  }else if(room_direction == "top" && agent_direction =="right") {
    updated_agent_direction = Actuator.move_left();
    updated_agent_location = Actuators.shoot();
  }else if(room_direction == "top" && agent_direction =="bottom") {
    updated_agent_direction = Actuator.move_left();
    updated_agent_direction = Actuator.move_left();
    updated_agent_location = Actuators.shoot();
  }else if(room_direction == "top" && agent_direction =="left") {
    updated_agent_direction = Actuator.move_right();
    updated_agent_location = Actuators.shoot();
    // if room direction is in the right
  }else if(room_direction == "right" && agent_direction =="top") {
    updated_agent_direction = Actuator.move_right();
    updated_agent_location = Actuators.shoot();
  }else if(room_direction == "right" && agent_direction =="bottom") {
    updated_agent_direction = Actuator.move_left();
    updated_agent_location = Actuators.shoot();
  }else if(room_direction == "right" && agent_direction =="left") {
    updated_agent_direction = Actuator.move_left();
    updated_agent_direction = Actuator.move_left();
    updated_agent_location = Actuators.shoot();
    // if room direction is in the bottom
  }else if(room_direction == "bottom" && agent_direction =="top") {
    updated_agent_direction = Actuator.move_right();
    updated_agent_direction = Actuator.move_right();
    updated_agent_location = Actuators.shoot();
  }else if(room_direction == "bottom" && agent_direction =="right") {
    updated_agent_direction = Actuator.move_right();
    updated_agent_location = Actuators.shoot();
  }else if(room_direction == "bottom" && agent_direction =="left") {
    updated_agent_direction = Actuator.move_left();
    updated_agent_location = Actuators.shoot();
    // if agent direction is in the left
  }else if(room_direction == "left" && agent_direction =="top") {
    updated_agent_direction = Actuator.move_left();
    updated_agent_location = Actuators.shoot();
  }else if(room_direction == "left" && agent_direction =="right") {
    updated_agent_direction = Actuator.move_left();
    updated_agent_direction = Actuator.move_left();
    updated_agent_location = Actuators.shoot();
  }else if(room_direction == "left" && agent_direction =="bottom") {
    updated_agent_direction = Actuator.move_left();
    updated_agent_location = Actuators.shoot();
  }
  set_agent_direction(updated_agent_direction);
}
