#include <gtest/gtest.h>
#include "Chess.h"
#include "BoardFactory.h"

using namespace Entities;

TEST(RookTests, Possibilities)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(5, 5);
    Factories::BoardFactory::CreateBoard(&c, "R", "");
    c.PrintBoard();

    // act
    c.pieces[WHITE][0]->AppendMoves(&c, moves);

    // assert
    ASSERT_EQ(moves.size(), 8);
}

TEST(RookTests, Possibilities2)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(2, 2);
    Factories::BoardFactory::CreateBoard(&c, "R", " pp");
    c.PrintBoard();

    // act
    c.pieces[WHITE][0]->AppendMoves(&c, moves);

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

TEST(RookTests, Possibilites3)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(5, 5);
    Factories::BoardFactory::CreateBoard(&c, "--  r", "");
    c.PrintBoard();

    bool squares[5][5] = {
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {1, 1, 0, 1, 1},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0}};

    // assert
    for (int x = 0; x < 5; x++)
    {
        for (int y = 0; y < 5; y++)
        {
            bool canCaptureSquare = c.pieces[WHITE][0]->CanPieceCaptureSquare(x, y, &c);
            bool shouldCaptureSquare = squares[x][y];
            ASSERT_EQ(canCaptureSquare, shouldCaptureSquare);
        }
    }
}

TEST(RookTests, AfterMoveNoCastling)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(8, 1);
    Factories::BoardFactory::CreateBoard(&c, "    K  R", "");
    c.PrintBoard();

    // act
    c.pieces[WHITE][1]->AppendMoves(&c, moves);
    c.ExecuteMove(moves[0]);
    moves.clear();

    c.pieces[WHITE][0]->AppendMoves(&c, moves);

    // assert
    ASSERT_EQ(moves.size(), 2);
}