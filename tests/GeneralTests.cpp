#include <gtest/gtest.h>
#include "Chess.h"
#include "BoardFactory.h"

using namespace Entities;

TEST(GeneralTests, StartingMoves)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(8, 8);
    Factories::BoardFactory::CreateBoard(&c);
    c.PrintBoard();

    // act
    c.AppendMoves(moves);

    // assert
    ASSERT_EQ(moves.size(), 20);

    c.ExecuteMove(moves[0]);

    // act
    moves.clear();
    c.AppendMoves(moves);

    // assert
    ASSERT_EQ(moves.size(), 20);
}