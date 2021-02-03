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

TEST(GeneralTests, manyMoves)
{
    std::vector<Move *> moves;
    Chess c = Chess(8, 8);
    Factories::BoardFactory::CreateBoard(&c);
    c.PrintBoard();
    c.AppendMoves(moves);

    int i = 0;

    while (moves.size() != 0)
    {
        int somewhatRandomNumber = i++ % moves.size();
        Move *move = moves[somewhatRandomNumber];
        c.ExecuteMove(move);
        moves.clear();
        c.AppendMoves(moves);
    }

    ASSERT_EQ(i, 284); // Apparently
}