#include "Inference.h"
#include <iostream>


namespace components{

// using namespace DataStructures;
// using namespace std;

/**
 * @brief Construct a new Inference:: Inference object
 *
 * @param kb Knowledgebase object
 */
Inference::Inference(KnowledgeBase& kb): current_kb(kb)
{

}

/**
 * [Inference::is_valid_position validates if a given position is valid or not]
 * @param  i [row of a given position]
 * @param  j [column of a given position]
 * @return   [bool]
 */
bool Inference::is_valid_position(int i, int j)
{
  // this function is not generic enough to handle a grid that's not 4X4, needs improvement
  if((i >= 0 && i <= 3) && (j >= 0 && j <= 3)) return true;
  else return false;
}

/**
 * [Inference::get_adjacent_rooms find valid adjacent rooms of the current room]
 * @param current_room [piar<int, int> current room position in tumple format]
 * @return [std::vector<pair<int, int>> valid adjacent rooms]
 */
std::vector<std::pair<int, int>> Inference::get_adjacent_rooms(std::pair<int, int> room)
{
    std::vector<std::pair<int, int>> adjacent_rooms;
    std::vector<std::pair<int, int>> adjacent_rooms_candidates;
    adjacent_rooms_candidates.push_back(std::make_pair(room.first + 1, room.second));
    adjacent_rooms_candidates.push_back(std::make_pair(room.first - 1, room.second));
    adjacent_rooms_candidates.push_back(std::make_pair(room.first, room.second + 1));
    adjacent_rooms_candidates.push_back(std::make_pair(room.first, room.second - 1));
    for(auto itr : adjacent_rooms_candidates) {
        if(is_valid_position(itr.first, itr.second)) {
          adjacent_rooms.push_back(itr);
        }
    }
    return adjacent_rooms;
}

std::vector<std::pair<int, int>> Inference::get_adjacent_visited_rooms(std::pair<int, int> room)
{
  std::vector<std::pair<int, int>> adjacent_visited_rooms;
  std::vector<std::pair<int, int>> adjacent_visited_rooms_candidates = get_adjacent_rooms(room);

  for(auto itr : adjacent_visited_rooms_candidates){
    if(current_kb.get_information_visited(itr)) {
      adjacent_visited_rooms.push_back(itr);
    }
  }
  return adjacent_visited_rooms;
}


/**
 * [Inference::find_possible_move find the possible move base on the knowledgebase of the rooms.]
 * @param current_room [current room position in std::pair<int, int> format]
 * @return [selected room in std::pair<int, int> format]
 */
std::pair<int, int> Inference::find_possible_move(std::pair<int, int> current_room)
{
  // todo - calculate_possible_move
  std::vector<std::pair<int, int>> adjacent_rooms = get_adjacent_rooms(current_room);

  // possible move candidate base on their priorities
  std::vector<std::pair<int, int>> possible_move_candidates1;
  std::vector<std::pair<int, int>> possible_move_candidates2;
  std::vector<std::pair<int, int>> possible_move_candidates3;

  // possible move which hold on of the prior possible moves
  std::vector<std::pair<int, int>> possible_move_candidates;

  for(auto itr : adjacent_rooms) {
    // if the adjacent room is ok and unvisited.
    if(current_kb.get_information_ok(itr) && !current_kb.get_information_visited(itr)) {
      possible_move_candidates1.push_back(itr);
    // if the adjacent room is ok and visited.
    }else if(current_kb.get_information_ok(itr) && current_kb.get_information_visited(itr)) {
      possible_move_candidates2.push_back(itr);
    }else {
      possible_move_candidates3.push_back(itr);
    }
  }

  // assign possible_moves
  if(possible_move_candidates1.size() > 0){
    possible_move_candidates = possible_move_candidates1;
  }else if(possible_move_candidates2.size() > 0){
    possible_move_candidates = possible_move_candidates2;
  }else{
    possible_move_candidates = possible_move_candidates3;
  }

  // fix the random number generator.
  srand((int)time(0));
  int random_number = rand()%possible_move_candidates.size();
  std::pair<int, int> selected_room = possible_move_candidates[random_number];

  return selected_room;
}

/**
 * [Inference::validate_conclusion check if there is sufficient information to decide.]
 * @param adjacent_rooms [list of adjacent rooms of a given room. ]
 * @return [return true if the adjacent rooms are sufficient to decide else false.]
 */
bool Inference::validate_conclusion(std::vector<std::pair<int, int>> adjacent_rooms){
  for(auto itr : adjacent_rooms) {
    if(!current_kb.get_information_visited(itr)) return false;
  }
  return true;
}


/**
 * [Inference::infer_wumpus if there is stench on all the adjacent room, there is wumpus in that room.]
 * @param  room [a given room]
 * @return      [return true if wumpus exist else return false.]
 */
bool Inference::infer_wumpus(std::pair<int, int> room){
  std::vector<std::pair<int, int>> adjacent_rooms = get_adjacent_rooms(room);
  if(!validate_conclusion(adjacent_rooms)) return false;

  bool conclusion = current_kb.get_information_stench(adjacent_rooms[0]);
  for(auto itr = adjacent_rooms.begin() + 1; itr != adjacent_rooms.end(); itr++){
    conclusion = conclusion && current_kb.get_information_stench(*itr);
  }
  return conclusion;
}

/**
 * [Inference::infer_not_wumpus if there is no stench atleast in one of the adjacent rooms, there is no wumpus in that room.]
 * @param  room [a given room]
 * @return      [return true if wumpus doesn't exist else false.]
 */
bool Inference::infer_not_wumpus(std::pair<int, int> room){
  std::vector<std::pair<int, int>> adjacent_visited_rooms = get_adjacent_visited_rooms(room);
  // if(!validate_conclusion(adjacent_visited_rooms)) return false;

  // if(current_kb.get_information_ok(room)) return true;
  bool conclusion = !current_kb.get_information_stench(adjacent_visited_rooms[0]); // todo - error return false for any room
  for(auto itr = adjacent_visited_rooms.begin() + 1; itr != adjacent_visited_rooms.end(); itr++){
    conclusion = conclusion || !current_kb.get_information_stench(*itr);
  }
  return conclusion;
}

/**
 * [Inference::infer_pit if there is breeze in all adjacent rooms, there is pit in that room]
 * @param  room [a given room]
 * @return      [return true if pit exist else return false]
 */
bool Inference::infer_pit(std::pair<int, int> room){
  std::vector<std::pair<int, int>> adjacent_rooms = get_adjacent_rooms(room);
  if(!validate_conclusion(adjacent_rooms)) return false;

  bool conclusion = current_kb.get_information_breeze(adjacent_rooms[0]);
  for(auto itr = adjacent_rooms.begin() + 1; itr != adjacent_rooms.end(); itr++){
    conclusion = conclusion && current_kb.get_information_breeze(*itr);
  }
  return conclusion;
}

/**
 * [Inference::infer_not_pit if there is no breeze in atleast one of the adjacent rooms, there is pit in that room]
 * @param  room [a given room]
 * @return      [return true if pit doesn't exist]
 */
bool Inference::infer_not_pit(std::pair<int, int> room){
  std::vector<std::pair<int, int>> adjacent_visited_rooms = get_adjacent_visited_rooms(room);
  // if(!validate_conclusion(adjacent_visited_rooms)) return false;

  // if(current_kb.get_information_ok(room)) return true;
  bool conclusion = !current_kb.get_information_breeze(adjacent_visited_rooms[0]);
  for(auto itr = adjacent_visited_rooms.begin() + 1; itr != adjacent_visited_rooms.end(); itr++){
    conclusion = conclusion || !current_kb.get_information_breeze(*itr);;
  }
  return conclusion;
}

/**
 * [Inference::infer_gold infer gold if there is glitter in a given room]
 * @param  room [a given room]
 * @return      [return true if there is gold else return false.]
 */
bool Inference::infer_gold(std::pair<int, int> room){
  return current_kb.get_information_glitter(room);
}


/**
 * [Inference::infer infer response from the given knowledgebase]
 * @param  current_room [current room position in std::pair<int, int> format]
 * @return              [response which contain the infered action and an updated knowledgebase]
 */
DataStructures::Decision Inference::infer(std::pair<int, int> current_room)
{
  // std::cout << "Agent in: (" << current_room.first << "," << current_room.second << ")" << std::endl;
  current_kb.change_information_visited(current_room, true);

  std::vector<std::pair<int, int>> adjacent_rooms = get_adjacent_rooms(current_room);

  DataStructures::Decision decision;
  for(auto itr : adjacent_rooms){
    if(infer_wumpus(itr)){
      // std::cout << "Wumpus in: (" << itr.first << "," << itr.second << ")" << std::endl;
      current_kb.change_information_wumpus(itr, true);
      decision.decision = DataStructures::movement_decision::shoot_at;
      decision.location = itr;
      return decision;
    }else if(infer_gold(itr)){
      // std::cout << "Gold in: (" << itr.first << "," << itr.second << ")" << std::endl;
      current_kb.change_information_gold(itr, true);
    }else if(infer_not_wumpus(itr) && infer_not_pit(itr)){
      // std::cout << "Ok_room in: (" << itr.first << "," << itr.second << ")" << std::endl;
      current_kb.change_information_ok(itr, true);
    }else{
      continue;
    }
  }

  std::pair<int, int> selected_room = find_possible_move(current_room);
  decision.decision = DataStructures::movement_decision::move_to;
  decision.location = selected_room;

  return decision;
}

}
