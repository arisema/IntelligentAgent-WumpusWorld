#include "Inference.h"
#include <iostream>


namespace components{

using namespace DataStructures;
using namespace std;

Inference::Inference(KnowledgeBase current_kb)
{
  Inference::current_kb = current_kb;
  Inference::p_hist = Inference::current_kb.get_data();
}

/**
 * [Inference::is_valid_position validates if a given position is valid or not]
 * @param  i [row of a given position]
 * @param  j [column of a given position]
 * @return   [bool]
 */
bool Inference::is_valid_position(int i, int j)
{
  if((i >= 1 && i <= 4) && (j >= 1 && j <= 4)) {
    return true;
  }
  return false;
}

/**
 * [Inference::get_adjacent_rooms find valid adjacent rooms of the current room]
 * @param current_room [piar<int, int> current room position in tumple format]
 * @return [vector<pair<int, int>> valid adjacent rooms]
 */
vector<pair<int, int>> Inference::get_adjacent_rooms(pair<int, int> current_room)
{
  vector<pair<int, int>> adjacent_rooms;
  vector<pair<int, int>> adjacent_rooms_candidates;
  adjacent_rooms_candidates.push_back(make_pair(current_room.first + 1, current_room.second));
  adjacent_rooms_candidates.push_back(make_pair(current_room.first - 1, current_room.second));
  adjacent_rooms_candidates.push_back(make_pair(current_room.first, current_room.second + 1));
  adjacent_rooms_candidates.push_back(make_pair(current_room.first, current_room.second - 1));

  for(auto itr = adjacent_rooms_candidates.begin(); itr < adjacent_rooms_candidates.end(); itr++) {
    if(is_valid_position(itr->first, itr->second)) {
      adjacent_rooms.push_back(*itr);
    }
  }

  return adjacent_rooms;
}

vector<pair<int, int>> Inference::get_adjacent_visited_rooms(pair<int, int> current_room)
{
  vector<pair<int, int>> adjacent_visited_rooms;
  vector<pair<int, int>> adjacent_visited_rooms_candidates = get_adjacent_rooms(current_room);
  for(auto itr = adjacent_visited_rooms_candidates.begin(); itr < adjacent_visited_rooms_candidates.end(); itr++) {
    if(current_kb.get_information_visited(*itr)){
      adjacent_visited_rooms.push_back(*itr);
    }
  }

  return adjacent_visited_rooms;
}

/**
 * [Inference::find_possible_move find the possible move base on the knowledgebase of the rooms.]
 * @param current_room [current room position in pair<int, int> format]
 * @return [selected room in pair<int, int> format]
 */
pair<int, int> Inference::find_possible_move(pair<int, int> current_room)
{
  // todo - calculate_possible_move
  vector<pair<int, int>> adjacent_rooms = get_adjacent_rooms(current_room);
  map<pair<int, int>, Knowledge> data = current_kb.get_data();

  // possible move candidate base on their priorities
  vector<pair<int, int>> possible_move_candidates1;
  vector<pair<int, int>> possible_move_candidates2;
  vector<pair<int, int>> possible_move_candidates3;

  // possible move which hold on of the prior possible moves
  vector<pair<int, int>> possible_move_candidates;

  for(auto itr = adjacent_rooms.begin(); itr < adjacent_rooms.end(); itr++) {
    // if the adjacent room is ok and unvisited.
    if(current_kb.get_information_ok(*itr) && !current_kb.get_information_visited(*itr)) {
      possible_move_candidates1.push_back(*itr);
    // if the adjacent room is ok and visited.
    }else if(current_kb.get_information_ok(*itr) && current_kb.get_information_visited(*itr)) {
      possible_move_candidates2.push_back(*itr);
    }else {
      possible_move_candidates3.push_back(*itr);
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
  pair<int, int> selected_room = possible_move_candidates[random_number];

  return selected_room;
}

bool Inference::infer_wumpus(pair<int, int> current_room){
  vector<pair<int, int>> adjacent_visited_rooms = get_adjacent_visited_rooms(current_room);

  bool conclusion = p_hist.at(adjacent_visited_rooms[0]).stench;
  for(auto itr = adjacent_visited_rooms.begin() + 1; itr < adjacent_visited_rooms.end(); itr++){
    conclusion = conclusion && p_hist.at(*itr).stench;
  }
  return conclusion;
}

bool Inference::infer_not_wumpus(pair<int, int> current_room){
  vector<pair<int, int>> adjacent_visited_rooms = get_adjacent_visited_rooms(current_room);

  bool conclusion = !p_hist.at(adjacent_visited_rooms[0]).stench;
  for(auto itr = adjacent_visited_rooms.begin() + 1; itr < adjacent_visited_rooms.end(); itr++){
    conclusion = conclusion || !p_hist.at(*itr).stench;
  }
  return conclusion;
}

bool Inference::infer_pit(pair<int, int> current_room){
  vector<pair<int, int>> adjacent_visited_rooms = get_adjacent_visited_rooms(current_room);

  bool conclusion = p_hist.at(adjacent_visited_rooms[0]).breeze;
  for(auto itr = adjacent_visited_rooms.begin() + 1; itr < adjacent_visited_rooms.end(); itr++){
    conclusion = conclusion && p_hist.at(*itr).breeze;
  }
  return conclusion;
}

bool Inference::infer_not_pit(pair<int, int> current_room){
  vector<pair<int, int>> adjacent_visited_rooms = get_adjacent_visited_rooms(current_room);

  bool conclusion = !p_hist.at(adjacent_visited_rooms[0]).breeze;
  for(auto itr = adjacent_visited_rooms.begin() + 1; itr < adjacent_visited_rooms.end(); itr++){
    conclusion = conclusion || !p_hist.at(*itr).breeze;
  }
  return conclusion;
}

bool Inference::infer_gold(pair<int, int> current_room){
  return p_hist.at(current_room).glitter;
}


/**
 * [Inference::infer infer response from the given knowledgebase]
 * @param  current_room [current room position in pair<int, int> format]
 * @return              [response which contain the infered action and an updated knowledgebase]
 */
Decision Inference::infer(pair<int, int> current_room)
{
  vector<pair<int, int>> adjacent_rooms = get_adjacent_rooms(current_room);

  Decision decision;
  for(int i = 0; i < adjacent_rooms.size(); i++){
    if(infer_wumpus(adjacent_rooms[i])){
      p_hist.at(adjacent_rooms[i]).wumpus = true;
      decision.shoot_at = adjacent_rooms[i];
    }else if(infer_gold(adjacent_rooms[i])){
      p_hist.at(adjacent_rooms[i]).gold = true;
      decision.grab = adjacent_rooms[i];
    }else if(infer_not_wumpus(adjacent_rooms[i]) && infer_not_pit(adjacent_rooms[i])){
      p_hist.at(adjacent_rooms[i]).ok = true;
    }else{
      continue;
    }
  }

  pair<int, int> selected_room = find_possible_move(current_room);
  decision.move_to = selected_room;

  current_kb.change_information_visited(current_room, true);

  return decision;
}
}
