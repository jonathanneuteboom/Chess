
#include <gtest/gtest.h>
#include "Chess.h"
#include "BoardFactory.h"

using namespace Entities;

TEST(KnightTests, AllMoves)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(5, 5);
    Factories::BoardFactory::CreateBoard(&c, "--  N", "");

    // act
    c.AppendMoves(moves);

    // assert
    ASSERT_EQ(moves.size(), 8);

    Move *stap = moves[0];
    ASSERT_EQ(stap->newX, 3);
    ASSERT_EQ(stap->newY, 4);
    ASSERT_EQ(stap->moveType, WALK);

    stap = moves[1];
    ASSERT_EQ(stap->newX, 4);
    ASSERT_EQ(stap->newY, 3);
    ASSERT_EQ(stap->moveType, WALK);

    stap = moves[2];
    ASSERT_EQ(stap->newX, 4);
    ASSERT_EQ(stap->newY, 1);
    ASSERT_EQ(stap->moveType, WALK);

    stap = moves[3];
    ASSERT_EQ(stap->newX, 3);
    ASSERT_EQ(stap->newY, 0);
    ASSERT_EQ(stap->moveType, WALK);

    stap = moves[4];
    ASSERT_EQ(stap->newX, 1);
    ASSERT_EQ(stap->newY, 0);
    ASSERT_EQ(stap->moveType, WALK);

    stap = moves[5];
    ASSERT_EQ(stap->newX, 0);
    ASSERT_EQ(stap->newY, 1);
    ASSERT_EQ(stap->moveType, WALK);

    stap = moves[6];
    ASSERT_EQ(stap->newX, 0);
    ASSERT_EQ(stap->newY, 3);
    ASSERT_EQ(stap->moveType, WALK);

    stap = moves[7];
    ASSERT_EQ(stap->newX, 1);
    ASSERT_EQ(stap->newY, 4);
    ASSERT_EQ(stap->moveType, WALK);
}

TEST(KnightTests, Possibilites)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(5, 5);
    Factories::BoardFactory::CreateBoard(&c, "--  N", "");
    c.PrintBoard();

    bool squares[5][5] = {
        {0, 1, 0, 1, 0},
        {1, 0, 0, 0, 1},
        {0, 0, 0, 0, 0},
        {1, 0, 0, 0, 1},
        {0, 1, 0, 1, 0}};

    // assert
    for (int x = 0; x < 5; x++)
    {
        for (int y = 0; y < 5; y++)
        {
            bool canCaptureSquare = c.pieces[c.GetPlayerIndex(WHITE)][0]->CanPieceCaptureSquare(x, y, &c);
            bool shouldCaptureSquare = squares[x][y];
            ASSERT_EQ(canCaptureSquare, shouldCaptureSquare);
        }
    }
}

TEST(KnightTests, CantHitItself)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(5, 5);
    Factories::BoardFactory::CreateBoard(&c, " p       p  N  p       p", "");
    c.PrintBoard();

    // act
    c.pieces[c.GetPlayerIndex(WHITE)][2]->AppendMoves(&c, moves);

    // assert
    ASSERT_EQ(moves.size(), 4);

    Move *stap;
    stap = moves[0];
    ASSERT_EQ(stap->newX, 4);
    ASSERT_EQ(stap->newY, 3);
    ASSERT_EQ(stap->moveType, WALK);

    stap = moves[1];
    ASSERT_EQ(stap->newX, 3);
    ASSERT_EQ(stap->newY, 0);
    ASSERT_EQ(stap->moveType, WALK);

    stap = moves[2];
    ASSERT_EQ(stap->newX, 0);
    ASSERT_EQ(stap->newY, 1);
    ASSERT_EQ(stap->moveType, WALK);

    stap = moves[3];
    ASSERT_EQ(stap->newX, 1);
    ASSERT_EQ(stap->newY, 4);
    ASSERT_EQ(stap->moveType, WALK);
}