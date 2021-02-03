#include <gtest/gtest.h>
#include "Chess.h"
#include "BoardFactory.h"

using namespace Entities;

TEST(BishopTests, Possibilites1)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(5, 5);
    Factories::BoardFactory::CreateBoard(&c, "- p p   B   p p", "");
    c.PrintBoard();

    // act
    c.pieces[WHITE][2]->AppendMoves(&c, moves);

    // assert
    ASSERT_EQ(moves.size(), 0);
}

TEST(BishopTests, Possibilites2)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(5, 5);
    Factories::BoardFactory::CreateBoard(&c, "--  B", "");
    c.PrintBoard();

    bool squares[5][5] = {
        {1, 0, 0, 0, 1},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {1, 0, 0, 0, 1}};

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

TEST(BishopTests, Possibilites3)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(5, 5);
    Factories::BoardFactory::CreateBoard(&c, "--  B", "- p p - p p");
    c.PrintBoard();

    // act
    c.pieces[WHITE][0]->AppendMoves(&c, moves);
    c.ExecuteMove(moves[0]);

    // assert
    ASSERT_EQ(moves.size(), 4);
    ASSERT_EQ(c.numberOfPieces[WHITE], 1);
    ASSERT_EQ(c.numberOfPieces[BLACK], 3);
}