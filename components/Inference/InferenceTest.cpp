#include "Inference.cpp"
#include <gtest/gtest.h>

// test is_valid position
TEST( is_valid_position, valid ){
  ASSERT_TRUE(is_valid_position(make_pair(1, 1)));
  ASSERT_TRUE(is_valid_position(make_pair(2, 2)));
  ASSERT_TRUE(is_valid_position(make_pair(1, 3)));
  ASSERT_TRUE(is_valid_position(make_pair(4, 1)));
}

TEST( is_valid_position, invalid ){
  ASSERT_FALSE(is_valid_position(make_pair(0, 0)));
  ASSERT_FALSE(is_valid_position(make_pair(5, 6)));
  ASSERT_FALSE(is_valid_position(make_pair(1, 5)));
  ASSERT_FALSE(is_valid_position(make_pair(5, 2)));
}

// test get_adjacent_rooms
TEST( get_adjacent_rooms, adjacent_rooms ){

  vector<pair<int, int>> adjacent_rooms_test1;
  adjacent_rooms_test1.push_back(make_pair(2, 1));
  adjacent_rooms_test1.push_back(make_pair(1, 2));

  vector<pair<int, int>> adjacent_rooms_test2;
  adjacent_rooms_test1.push_back(make_pair(2, 2));
  adjacent_rooms_test1.push_back(make_pair(1, 3));
  adjacent_rooms_test1.push_back(make_pair(1, 1));

  vector<pair<int, int>> adjacent_rooms_test3;
  adjacent_rooms_test1.push_back(make_pair(4, 3));
  adjacent_rooms_test1.push_back(make_pair(2, 3));
  adjacent_rooms_test1.push_back(make_pair(3, 4));
  adjacent_rooms_test1.push_back(make_pair(3, 2));

  vector<pair<int, int>> adjacent_rooms_test4;
  adjacent_rooms_test1.push_back(make_pair(3, 1));
  adjacent_rooms_test1.push_back(make_pair(4, 2));

  ASSERT_EQ(adjacent_rooms_test1, get_adjacent_rooms(make_pair(1, 1)));
  ASSERT_EQ(adjacent_rooms_test2, get_adjacent_rooms(make_pair(1, 2)));
  ASSERT_EQ(adjacent_rooms_test3, get_adjacent_rooms(make_pair(3, 3)));
  ASSERT_EQ(adjacent_rooms_test4, get_adjacent_rooms(make_pair(4, 1)));
}

// test find_possible_move
// test inference
