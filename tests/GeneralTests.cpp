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
    ASSERT_EQ(c.GetNumberOfMoves(WHITE), 20);
    ASSERT_EQ(c.GetNumberOfMoves(BLACK), 20);

    c.ExecuteMove(moves[0]);
    c.PrintBoard();

    // assert
    ASSERT_EQ(c.GetNumberOfMoves(WHITE), 22);
    ASSERT_EQ(c.GetNumberOfMoves(BLACK), 20);
}

TEST(GeneralTests, manyMoves)
{
    std::vector<Move *> moves;
    Chess c = Chess(8, 8);
    Factories::BoardFactory::CreateBoard(&c);

    int i = 0;

    while (true)
    {
        c.PrintBoard();
        moves.clear();

        c.AppendMoves(moves);
        if (moves.size() == 0)
            break;

        int somewhatRandomNumber = i++ % moves.size();
        Move *move = moves[somewhatRandomNumber];

        c.ExecuteMove(move);
    }

    ASSERT_EQ(i, 213); // Apparently
}