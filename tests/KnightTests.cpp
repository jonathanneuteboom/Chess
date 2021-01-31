
#include <gtest/gtest.h>
#include "Chess.h"

using namespace Entities;

TEST(KnightTests, AllMoves)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(5, 5);
    c.InitBoard((char *)"--  n", NULL);

    // act
    c.AppendMoves(moves);

    // assert
    ASSERT_EQ(moves.size(), 8);

    Move *stap = moves[0];
    ASSERT_EQ(stap->newSquare->x, 3);
    ASSERT_EQ(stap->newSquare->y, 4);
    ASSERT_EQ(stap->moveType, WALK);

    stap = moves[1];
    ASSERT_EQ(stap->newSquare->x, 4);
    ASSERT_EQ(stap->newSquare->y, 3);
    ASSERT_EQ(stap->moveType, WALK);

    stap = moves[2];
    ASSERT_EQ(stap->newSquare->x, 4);
    ASSERT_EQ(stap->newSquare->y, 1);
    ASSERT_EQ(stap->moveType, WALK);

    stap = moves[3];
    ASSERT_EQ(stap->newSquare->x, 3);
    ASSERT_EQ(stap->newSquare->y, 0);
    ASSERT_EQ(stap->moveType, WALK);

    stap = moves[4];
    ASSERT_EQ(stap->newSquare->x, 1);
    ASSERT_EQ(stap->newSquare->y, 0);
    ASSERT_EQ(stap->moveType, WALK);

    stap = moves[5];
    ASSERT_EQ(stap->newSquare->x, 0);
    ASSERT_EQ(stap->newSquare->y, 1);
    ASSERT_EQ(stap->moveType, WALK);

    stap = moves[6];
    ASSERT_EQ(stap->newSquare->x, 0);
    ASSERT_EQ(stap->newSquare->y, 3);
    ASSERT_EQ(stap->moveType, WALK);

    stap = moves[7];
    ASSERT_EQ(stap->newSquare->x, 1);
    ASSERT_EQ(stap->newSquare->y, 4);
    ASSERT_EQ(stap->moveType, WALK);
}

TEST(KnightTests, CantHitItself)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(5, 5);
    c.InitBoard((char *)" p       p  n  p       p", NULL);
    c.PrintBoard();

    // act
    c.pieces[c.GetPlayerIndex(WHITE)][2]->AppendMoves(&c, moves);

    // assert
    ASSERT_EQ(moves.size(), 4);

    Move *stap;
    stap = moves[0];
    ASSERT_EQ(stap->newSquare->x, 4);
    ASSERT_EQ(stap->newSquare->y, 3);
    ASSERT_EQ(stap->moveType, WALK);

    stap = moves[1];    
    ASSERT_EQ(stap->newSquare->x, 3);
    ASSERT_EQ(stap->newSquare->y, 0);
    ASSERT_EQ(stap->moveType, WALK);

    stap = moves[2];
    ASSERT_EQ(stap->newSquare->x, 0);
    ASSERT_EQ(stap->newSquare->y, 1);
    ASSERT_EQ(stap->moveType, WALK);

    stap = moves[3];
    ASSERT_EQ(stap->newSquare->x, 1);
    ASSERT_EQ(stap->newSquare->y, 4);
    ASSERT_EQ(stap->moveType, WALK);
}