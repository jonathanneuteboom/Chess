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
    c.pieces[c.GetPlayerIndex(WHITE)][2]->AppendMoves(&c, moves);

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

    // act
    c.pieces[c.GetPlayerIndex(WHITE)][0]->AppendMoves(&c, moves);

    // assert
    ASSERT_EQ(moves.size(), 8);
}

TEST(BishopTests, Possibilites3)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(5, 5);
    Factories::BoardFactory::CreateBoard(&c, "--  B", "- p p - p p");
    c.PrintBoard();

    // act
    c.pieces[c.GetPlayerIndex(WHITE)][0]->AppendMoves(&c, moves);
    c.ExecuteMove(moves[0]);

    // assert
    ASSERT_EQ(moves.size(), 4);
    ASSERT_EQ(c.numberOfPieces[c.GetPlayerIndex(WHITE)], 1);
    ASSERT_EQ(c.numberOfPieces[c.GetPlayerIndex(BLACK)], 3);
}