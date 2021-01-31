#include <gtest/gtest.h>
#include "Chess.h"

using namespace Entities;

TEST(RookTests, Possibilites)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(5, 5);
    c.InitBoard((char *)"r", NULL);
    c.PrintBoard();

    // act
    c.pieces[c.GetPlayerIndex(WHITE)][0]->AppendMoves(&c, moves);

    // assert
    ASSERT_EQ(moves.size(), 8);
}