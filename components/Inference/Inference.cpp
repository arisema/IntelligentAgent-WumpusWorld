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
// Inference::Inference(KnowledgeBase& kb) :current_kb(kb)
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

    // cout << room.first << "," << room.second << ": " << endl;
    for(auto itr : adjacent_rooms_candidates) {
        if(is_valid_position(itr.first, itr.second)) {
          // adjacent_rooms.insert(itr);
          adjacent_rooms.push_back(itr);
          // cout << itr.first << "," << itr.second << endl;
        }
    }
    return adjacent_rooms;
}

std::vector<std::pair<int, int>> Inference::get_adjacent_visited_rooms(std::pair<int, int> current_room)
{
  std::vector<std::pair<int, int>> adjacent_visited_rooms;
  std::vector<std::pair<int, int>> adjacent_visited_rooms_candidates = get_adjacent_rooms(current_room);
  for(auto itr : adjacent_visited_rooms) {
    if(current_kb.get_information_visited(itr)){
      // adjacent_visited_rooms.insert(itr);
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
  std::map<std::pair<int, int>, DataStructures::Knowledge> data = current_kb.get_data();

  // possible move candidate base on their priorities
  std::vector<std::pair<int, int>> possible_move_candidates1;
  std::vector<std::pair<int, int>> possible_move_candidates2;
  std::vector<std::pair<int, int>> possible_move_candidates3;

  // possible move which hold on of the prior possible moves
  std::vector<std::pair<int, int>> possible_move_candidates;

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
  std::pair<int, int> selected_room = possible_move_candidates[random_number];

  return selected_room;
}

bool Inference::infer_wumpus(std::pair<int, int> current_room){
  std::vector<std::pair<int, int>> adjacent_visited_rooms = get_adjacent_visited_rooms(current_room);

  bool conclusion = p_hist.at(adjacent_visited_rooms[0]).stench;
  for(auto itr = adjacent_visited_rooms.begin() + 1; itr < adjacent_visited_rooms.end(); itr++){
    conclusion = conclusion && p_hist.at(*itr).stench;
  }
  return conclusion;
}

bool Inference::infer_not_wumpus(std::pair<int, int> current_room){
  std::vector<std::pair<int, int>> adjacent_visited_rooms = get_adjacent_visited_rooms(current_room);

  bool conclusion = !p_hist.at(adjacent_visited_rooms[0]).stench;
  for(auto itr = adjacent_visited_rooms.begin() + 1; itr < adjacent_visited_rooms.end(); itr++){
    conclusion = conclusion || !p_hist.at(*itr).stench;
  }
  return conclusion;
}

bool Inference::infer_pit(std::pair<int, int> current_room){
  std::vector<std::pair<int, int>> adjacent_visited_rooms = get_adjacent_visited_rooms(current_room);

  bool conclusion = p_hist.at(adjacent_visited_rooms[0]).breeze;
  for(auto itr = adjacent_visited_rooms.begin() + 1; itr < adjacent_visited_rooms.end(); itr++){
    conclusion = conclusion && p_hist.at(*itr).breeze;
  }
  return conclusion;
}

bool Inference::infer_not_pit(std::pair<int, int> current_room){
  std::vector<std::pair<int, int>> adjacent_visited_rooms = get_adjacent_visited_rooms(current_room);

  bool conclusion = !p_hist.at(adjacent_visited_rooms[0]).breeze;
  for(auto itr = adjacent_visited_rooms.begin() + 1; itr < adjacent_visited_rooms.end(); itr++){
    conclusion = conclusion || !p_hist.at(*itr).breeze;
  }
  return conclusion;
}

bool Inference::infer_gold(std::pair<int, int> current_room){
  return p_hist.at(current_room).glitter;
}


/**
 * [Inference::infer infer response from the given knowledgebase]
 * @param  current_room [current room position in std::pair<int, int> format]
 * @return              [response which contain the infered action and an updated knowledgebase]
 */
DataStructures::Decision Inference::infer(std::pair<int, int> current_room)
{
  std::vector<std::pair<int, int>> adjacent_rooms = get_adjacent_rooms(current_room);

  DataStructures::Decision decision;
  for(int i = 0; i < adjacent_rooms.size(); i++){
    if(infer_wumpus(adjacent_rooms[i])){
      p_hist.at(adjacent_rooms[i]).wumpus = true;
      decision.location = adjacent_rooms[i];
    }else if(infer_gold(adjacent_rooms[i])){
      p_hist.at(adjacent_rooms[i]).gold = true;
    }else if(infer_not_wumpus(adjacent_rooms[i]) && infer_not_pit(adjacent_rooms[i])){
      p_hist.at(adjacent_rooms[i]).ok = true;
    }else{
      continue;
    }
  }

  std::pair<int, int> selected_room = find_possible_move(current_room);
  decision.location = selected_room;

  current_kb.change_information_visited(current_room, true);

  return decision;
}

  // model: <room> bool value, <room> bool value, <room> bool value
  // model: wumpus: <room> boolvalue stench
  //        pit <room> boolvalue breeze
  // the inference will take current_room and infer wumpus, infer pit, infer okay. All three will have different models
  // then return detections to Actuator, which will possibly give suggestions on next step to take, i.e Decision
  // std::std::vector<deduction, std::set<std::pair<int, int>, bool>> model;

  // ----------------- RULE MATCHING -------------
  // for each adj in adjacentrooms:
  //      bool w = inferwumpus(adj)
  //      bool p = inferwumpus(adj)
  //      if (w) shoot(direction)
  //      if (p) pitrooms.add(adj)
  //      if (!w && !p) okrooms.add(adj)

  // inferwumpus(room):
  //    PH(get_info_sth) |= room.left.sth
  //    PH(get_info_sth) |= room.right.sth
  //    PH(get_info_sth) |= room.top.sth
  //    PH(get_info_sth) |= room.bottom.sth

  // infer(room, sthBoss):
  //    sth = getModel(sthBoss) //this is where it's at
  //    PH(get_info_sth) |= room.left.sth
  //    PH(get_info_sth) |= room.right.sth
  //    PH(get_info_sth) |= room.top.sth
  //    PH(get_info_sth) |= room.bottom.sth

  // test
  // get_adjacent_rooms(make_pair(0,0));
  // get_adjacent_rooms(make_pair(0,2));
  // get_adjacent_rooms(make_pair(3,1));
  // get_adjacent_rooms(make_pair(3,3));
  // get_adjacent_rooms(make_pair(-1,-1));
  // get_adjacent_rooms(make_pair(4,4))
  // rule_matching(current_room);

  // DataStructures::Decision agent_decision = rule_matching(current_room);
  //
  // if (agent_decision.decision == DataStructures::movement_decision::shoot_at) return agent_decision;
  //
  // else if (agent_decision.decision == DataStructures::movement_decision::move_to){
  //   agent_decision.location = ok_rooms.back();
  //   ok_rooms.pop_back();
  // }
  // return agent_decision;


/**
 * @brief rule matching function that will incorporate infered conclusions into knowledgebase as well as pass on conclusion for next action
 *
 * @param room
 */
DataStructures::Decision Inference::rule_matching(std::pair<int, int> room){

  std::cout << "Agent in: " << room.first << "," << room.second << std::endl;

  std::vector<std::pair<int, int>> adjacentRooms = get_adjacent_rooms(room);

  DataStructures::Decision d;

  for (auto adj : adjacentRooms){

    // check adjacent rooms for existence of wumpus or pit to figure out an ok room to move to
    // std::cout << "checking room: " << adj.first << "," << adj.second << std::endl;

    bool wumpus = current_kb.get_information_wumpus(adj);
    // if the presence of wumpus is not recorded in the adjacent room, perform model based inference to test for presence of wumpus
    if (!wumpus) wumpus = infer_presence(adj, DataStructures::Rule::Wumpus);

    bool pit = current_kb.get_information_pit(adj);
    if (!pit) pit = infer_presence(adj, DataStructures::Rule::Pit);

    bool gold = current_kb.get_information_glitter(room);

    if(wumpus){
        std::cout << "wumpus detected" << std::endl;

        current_kb.change_information_wumpus(adj, true); // update knowledgebase

        d.decision = DataStructures::movement_decision::shoot_at;
        d.location = adj;
    }

    if(pit){
        std::cout << "pit detected in: " << adj.first << "," << adj.second << std::endl;

        current_kb.change_information_pit(adj, true); // update knowledgebase
        pit_rooms.push_back(adj);

        d.decision = DataStructures::movement_decision::move_to;
    }

    if(!wumpus && !pit){
        std::cout << "room " << adj.first << "," << adj.second << " is ok" << std::endl;

        current_kb.change_information_ok(adj, true); // update knowledgebase
        ok_rooms.push_back(adj);

        d.decision = DataStructures::movement_decision::move_to;
    }
    if (gold){
      std::cout << "Gold Found!" << std::endl;
      d.decision = DataStructures::movement_decision::move_to;
    }
  }
  return d;
}

/**
 * @brief Infers the presence of a character such as a wumpus or pit in a room
 *
 * @param room The room from which will be inferred character exists in it or not.
 * @param character The game character which will be checked for existence.
 * @return true The character exists in the room.
 * @return false The character does not exist in the room.
 */
bool Inference::infer_presence(std::pair<int, int> room, DataStructures::Rule character){

    // PH(position, value) == Rule(position, value)

    DataStructures::model inference_model;
    DataStructures::constraint constraint;
    int counter;

    bool conclusion = false;

    if (character == DataStructures::Rule::Wumpus){
      inference_model = DataStructures::Model::generate_model(room, DataStructures::Rule::Wumpus);
      counter = inference_model.size();
      std::cout << "size" << inference_model.size() << std::endl;
      constraint = DataStructures::constraint::stench;
    }
    else if (character == DataStructures::Rule::Pit){
      inference_model = DataStructures::Model::generate_model(room, DataStructures::Rule::Pit);
      counter = inference_model.size()-1;
      constraint = DataStructures::constraint::breeze;
    }

    for (auto rule : inference_model){
      // std::cout << rule.first.first << "," << rule.first.second << ": " << "breeze: " << rule.second.breeze << " stench: " <<  rule.second.stench << std::endl;
      std::pair<int, int> model_room = std::make_pair(rule.first.first,rule.first.second);
      // cross-check equivalence in rooms
      conclusion = check_equivalence(model_room, constraint, inference_model);
      if (conclusion) --counter;
    }

    if (counter != 0) conclusion = false;
    return conclusion;
}

/**
 * @brief Checks the equivalence of contraints of the model with the data stored in the knowledgebase
 *
 * @param room Room that the constraint will be checked against
 * @param constraint Constraint that will be checked for validity in the knowlegebase
 * @return true Specified constraint is in congruity with data stored in the knowledgebase
 * @return false Specified constraint is not in conngruity with data stored in the knowledgebase
 */
bool Inference::check_equivalence(std::pair<int, int> room, DataStructures::constraint specific_constraint, DataStructures::model specified_model){

    bool is_equivalent = current_kb.get_specific_percept_info(room, specific_constraint) == DataStructures::Model::get_specific_constraint_info(room, specific_constraint, specified_model);
    // std::cout << "check equiv: " << is_equivalent << std::endl;
    return is_equivalent;

}

}
