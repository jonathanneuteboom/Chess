#include <gtest/gtest.h>
#include "Chess.h"
#include "BoardFactory.h"

using namespace Entities;

TEST(KingTests, Possibilities1)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(5, 5);
    Factories::BoardFactory::CreateBoard(&c, "--  k", "");
    c.PrintBoard();

    // act
    c.pieces[c.GetPlayerIndex(WHITE)][0]->AppendMoves(&c, moves);

    // assert
    ASSERT_EQ(moves.size(), 8);
}

TEST(KingTests, Possibilities2)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(1, 1);
    Factories::BoardFactory::CreateBoard(&c, "K", "");
    c.PrintBoard();

    // assert
    ASSERT_EQ(c.pieces[c.GetPlayerIndex(WHITE)][0]->GetType(), KING_CASTLE);
}

TEST(KingTests, Possibilities3)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(2, 2);
    Factories::BoardFactory::CreateBoard(&c, "K", "");
    c.PrintBoard();

    // act
    c.pieces[c.GetPlayerIndex(WHITE)][0]->AppendMoves(&c, moves);
    c.ExecuteMove(moves[0]);

    // assert
    ASSERT_EQ(c.pieces[c.GetPlayerIndex(WHITE)][0]->GetType(), KING);
}