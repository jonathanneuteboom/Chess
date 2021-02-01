#include <gtest/gtest.h>
#include "Chess.h"
#include "BoardFactory.h"

using namespace Entities;

TEST(RookTests, Possibilities)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(5, 5);
    Factories::BoardFactory::CreateBoard(&c, "r", "");
    c.PrintBoard();

    // act
    c.pieces[c.GetPlayerIndex(WHITE)][0]->AppendMoves(&c, moves);

    // assert
    ASSERT_EQ(moves.size(), 8);
}

TEST(RookTests, Possibilities2)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(2, 2);
    Factories::BoardFactory::CreateBoard(&c, "r", " pp");
    c.PrintBoard();

    // act
    c.pieces[c.GetPlayerIndex(WHITE)][0]->AppendMoves(&c, moves);

    // assert
    ASSERT_EQ(moves.size(), 2);

    Move *eersteStap = moves[0];
    ASSERT_EQ(eersteStap->newX, 1);
    ASSERT_EQ(eersteStap->newY, 0);
    ASSERT_EQ(eersteStap->moveType, WALK);

    Move *tweedeStap = moves[1];
    ASSERT_EQ(tweedeStap->newX, 0);
    ASSERT_EQ(tweedeStap->newY, 1);
    ASSERT_EQ(tweedeStap->moveType, WALK);
}