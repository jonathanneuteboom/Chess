#include <gtest/gtest.h>
#include "Chess.h"
#include "BoardFactory.h"

using namespace Entities;

TEST(QueenTests, Possibilities)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(5, 5);
    Factories::BoardFactory::CreateBoard(&c, "--  Q", "");
    c.PrintBoard();

    // act
    c.pieces[c.GetPlayerIndex(WHITE)][0]->AppendMoves(&c, moves);

    // assert
    ASSERT_EQ(moves.size(), 16);
}

TEST(QueenTests, Possibilities2)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(5, 5);
    Factories::BoardFactory::CreateBoard(&c, "--  Q", "");
    c.PrintBoard();
    int squares[16][2] = {
        {0, 0},
        {1, 1},
        {2, 0},
        {2, 1},
        {3, 1},
        {4, 0},
        {3, 2},
        {4, 2},
        {3, 3},
        {4, 4},
        {2, 3},
        {2, 4},
        {1, 3},
        {0, 4},
        {0, 2},
        {1, 2}};

    // assert
    for (int i = 0; i < 16; i++)
    {
        bool canCaptureSquare = c.pieces[c.GetPlayerIndex(WHITE)][0]->CanPieceCaptureSquare(squares[i][0], squares[i][1], &c);
        ASSERT_EQ(canCaptureSquare, true);
    }
}