#include "../Inference.h"
#include "../../KnowledgeBase/KB.h"
#include <tuple>
#include <vector>
#include <cxxtest/TestSuite.h>

using namespace std;

class is_valid_position : public CxxTest::TestSuite
{
private:
  components::KnowledgeBase current_kb = components::KnowledgeBase();
  components::Inference inference = components::Inference(current_kb);

public:
    void test_valid_cases(void)
    {
      inference.is_valid_position(1, 1);
        TS_ASSERT_EQUALS(true, inference.is_valid_position(1, 1));
        TS_ASSERT_EQUALS(true, inference.is_valid_position(1, 3));
        TS_ASSERT_EQUALS(true, inference.is_valid_position(3, 3));
        TS_ASSERT_EQUALS(true, inference.is_valid_position(4, 1));
    }

    void test_invalid_cases(void)
    {
        TS_ASSERT_EQUALS(false, inference.is_valid_position(0, 0));
        TS_ASSERT_EQUALS(false, inference.is_valid_position(1, 5));
        TS_ASSERT_EQUALS(false, inference.is_valid_position(6, 1));
        TS_ASSERT_EQUALS(false, inference.is_valid_position(6, 6));
    }
};

class get_adjacent_rooms : public CxxTest::TestSuite
{
private:
    components::KnowledgeBase current_kb = components::KnowledgeBase();
    components::Inference inference = components::Inference(current_kb);

    vector<pair<int, int>>  adjacent_rooms1;
    adjacent_rooms1.push_back(make_pair(2, 1));
    adjacent_rooms1.push_back(make_pair(1, 2));

    vector<pair<int, int>> adjacent_rooms2;
    adjacent_rooms2.push_back(make_pair(2, 3));
    adjacent_rooms2.push_back(make_pair(1, 2));
    adjacent_rooms2.push_back(make_pair(1, 4));

    vector<pair<int, int>> adjacent_rooms3;
    adjacent_rooms3.push_back(make_pair(4, 3));
    adjacent_rooms3.push_back(make_pair(2, 3));
    adjacent_rooms3.push_back(make_pair(3, 2));
    adjacent_rooms3.push_back(make_pair(3, 4));

    vector<pair<int, int>> adjacent_rooms4;
    adjacent_rooms4.push_back(make_pair(3, 1));
    adjacent_rooms4.push_back(make_pair(4, 2));

public:
    void valid_adjacent_rooms(void)
    {
        TS_ASSERT_EQUALS(adjacent_rooms1, inference.get_adjacent_rooms(make_pair(1, 1)));
        TS_ASSERT_EQUALS(adjacent_rooms2, inference.get_adjacent_rooms(make_pair(1, 3)));
        TS_ASSERT_EQUALS(adjacent_rooms3, inference.get_adjacent_rooms(make_pair(3, 3)));
        TS_ASSERT_EQUALS(adjacent_rooms4, inference.get_adjacent_rooms(make_pair(4, 11)));
    }
};

class find_possible_move : public CxxTest::TestSuite
{
private:
  components::KnowledgeBase current_kb = components::KnowledgeBase();
  components::Inference inference = components::Inference(current_kb);

public:
    void possible_move_case1(void)
    {
        // construct a knowledge base
        current_kb.change_information_ok(make_pair(1, 1), true);
        current_kb.change_information_ok(make_pair(2, 1), true);
        current_kb.change_information_ok(make_pair(1, 2), true);
        current_kb.change_information_wumpus(make_pair(3, 2), true);
        current_kb.change_information_pit(make_pair(3, 2), true);
        current_kb.change_information_pit(make_pair(3, 2), true);
        current_kb.change_information_pit(make_pair(3, 2), true);
        current_kb.change_information_gold(make_pair(4, 3), true);

        TS_ASSERT_EQUALS(make_pair(2, 1), inference.find_possible_move(make_pair(1, 1)));
        TS_ASSERT_EQUALS(make_pair(1, 1), inference.is_valid_position(2, 1));
        TS_ASSERT_EQUALS(make_pair(1, 1), inference.is_valid_position(3, 3));
        TS_ASSERT_EQUALS(make_pair(1, 1), inference.is_valid_position(4, 1));
    }

    void possible_move_case2(void)
    {
        // construct a knowledge base
        current_kb.change_information_ok(make_pair(1, 1), true);
        current_kb.change_information_ok(make_pair(2, 1), true);
        current_kb.change_information_ok(make_pair(1, 2), true);
        current_kb.change_information_wumpus(make_pair(3, 2), true);
        current_kb.change_information_pit(make_pair(3, 2), true);
        current_kb.change_information_pit(make_pair(3, 2), true);
        current_kb.change_information_pit(make_pair(3, 2), true);
        current_kb.change_information_gold(make_pair(4, 3), true);

        TS_ASSERT_EQUALS(make_pair(2, 1), inference.find_possible_move(make_pair(1, 1)));
        TS_ASSERT_EQUALS(make_pair(1, 1), inference.is_valid_position(2, 1));
        TS_ASSERT_EQUALS(make_pair(1, 1), inference.is_valid_position(3, 3));
        TS_ASSERT_EQUALS(make_pair(1, 1), inference.is_valid_position(4, 1));
    }

    void possible_move_case3(void)
    {
        // construct a knowledge base
        current_kb.change_information_ok(make_pair(1, 1), true);
        current_kb.change_information_ok(make_pair(2, 1), true);
        current_kb.change_information_ok(make_pair(1, 2), true);
        current_kb.change_information_wumpus(make_pair(3, 2), true);
        current_kb.change_information_pit(make_pair(3, 2), true);
        current_kb.change_information_pit(make_pair(3, 2), true);
        current_kb.change_information_pit(make_pair(3, 2), true);
        current_kb.change_information_gold(make_pair(4, 3), true);

        TS_ASSERT_EQUALS(make_pair(2, 1), inference.find_possible_move(make_pair(1, 1)));
        TS_ASSERT_EQUALS(make_pair(1, 1), inference.is_valid_position(2, 1));
        TS_ASSERT_EQUALS(make_pair(1, 1), inference.is_valid_position(3, 3));
        TS_ASSERT_EQUALS(make_pair(1, 1), inference.is_valid_position(4, 1));
    }

    void possible_move_case4(void)
    {
        // construct a knowledge base
        current_kb.change_information_ok(make_pair(1, 1), true);
        current_kb.change_information_ok(make_pair(2, 1), true);
        current_kb.change_information_ok(make_pair(1, 2), true);
        current_kb.change_information_wumpus(make_pair(3, 2), true);
        current_kb.change_information_pit(make_pair(3, 2), true);
        current_kb.change_information_pit(make_pair(3, 2), true);
        current_kb.change_information_pit(make_pair(3, 2), true);
        current_kb.change_information_gold(make_pair(4, 3), true);

        TS_ASSERT_EQUALS(make_pair(2, 1), inference.find_possible_move(make_pair(1, 1)));
        TS_ASSERT_EQUALS(make_pair(1, 1), inference.is_valid_position(2, 1));
        TS_ASSERT_EQUALS(make_pair(1, 1), inference.is_valid_position(3, 3));
        TS_ASSERT_EQUALS(make_pair(1, 1), inference.is_valid_position(4, 1));
    }
};

class infer : public CxxTest::TestSuite
{
private:
  components::KnowledgeBase current_kb = components::KnowledgeBase();
  components::Inference inference = components::Inference(current_kb);

public:
    void infer_case1(void)
    {
        // construct a knowledge base
        current_kb.change_information_ok(make_pair(1, 1), true);
        current_kb.change_information_ok(make_pair(2, 1), true);
        current_kb.change_information_ok(make_pair(1, 2), true);
        current_kb.change_information_wumpus(make_pair(3, 2), true);
        current_kb.change_information_pit(make_pair(3, 2), true);
        current_kb.change_information_pit(make_pair(3, 2), true);
        current_kb.change_information_pit(make_pair(3, 2), true);
        current_kb.change_information_gold(make_pair(4, 3), true);

        TS_ASSERT_EQUALS(make_pair(2, 1), inference.find_possible_move(make_pair(1, 1)));
        TS_ASSERT_EQUALS(make_pair(1, 1), inference.is_valid_position(2, 1));
        TS_ASSERT_EQUALS(make_pair(1, 1), inference.is_valid_position(3, 3));
        TS_ASSERT_EQUALS(make_pair(1, 1), inference.is_valid_position(4, 1));
    }

    void infer_case2(void)
    {
        // construct a knowledge base
        current_kb.change_information_ok(make_pair(1, 1), true);
        current_kb.change_information_ok(make_pair(2, 1), true);
        current_kb.change_information_ok(make_pair(1, 2), true);
        current_kb.change_information_wumpus(make_pair(3, 2), true);
        current_kb.change_information_pit(make_pair(3, 2), true);
        current_kb.change_information_pit(make_pair(3, 2), true);
        current_kb.change_information_pit(make_pair(3, 2), true);
        current_kb.change_information_gold(make_pair(4, 3), true);

        TS_ASSERT_EQUALS(make_pair(2, 1), inference.find_possible_move(make_pair(1, 1)));
        TS_ASSERT_EQUALS(make_pair(1, 1), inference.is_valid_position(2, 1));
        TS_ASSERT_EQUALS(make_pair(1, 1), inference.is_valid_position(3, 3));
        TS_ASSERT_EQUALS(make_pair(1, 1), inference.is_valid_position(4, 1));
    }

    void infer_case3(void)
    {
        // construct a knowledge base
        current_kb.change_information_ok(make_pair(1, 1), true);
        current_kb.change_information_ok(make_pair(2, 1), true);
        current_kb.change_information_ok(make_pair(1, 2), true);
        current_kb.change_information_wumpus(make_pair(3, 2), true);
        current_kb.change_information_pit(make_pair(3, 2), true);
        current_kb.change_information_pit(make_pair(3, 2), true);
        current_kb.change_information_pit(make_pair(3, 2), true);
        current_kb.change_information_gold(make_pair(4, 3), true);

        TS_ASSERT_EQUALS(make_pair(2, 1), inference.find_possible_move(make_pair(1, 1)));
        TS_ASSERT_EQUALS(make_pair(1, 1), inference.is_valid_position(2, 1));
        TS_ASSERT_EQUALS(make_pair(1, 1), inference.is_valid_position(3, 3));
        TS_ASSERT_EQUALS(make_pair(1, 1), inference.is_valid_position(4, 1));
    }

    void infer_case4(void)
    {
        // construct a knowledge base
        current_kb.change_information_ok(make_pair(1, 1), true);
        current_kb.change_information_ok(make_pair(2, 1), true);
        current_kb.change_information_ok(make_pair(1, 2), true);
        current_kb.change_information_wumpus(make_pair(3, 2), true);
        current_kb.change_information_pit(make_pair(3, 2), true);
        current_kb.change_information_pit(make_pair(3, 2), true);
        current_kb.change_information_pit(make_pair(3, 2), true);
        current_kb.change_information_gold(make_pair(4, 3), true);

        TS_ASSERT_EQUALS(make_pair(2, 1), inference.find_possible_move(make_pair(1, 1)));
        TS_ASSERT_EQUALS(make_pair(1, 1), inference.is_valid_position(2, 1));
        TS_ASSERT_EQUALS(make_pair(1, 1), inference.is_valid_position(3, 3));
        TS_ASSERT_EQUALS(make_pair(1, 1), inference.is_valid_position(4, 1));
    }
};
