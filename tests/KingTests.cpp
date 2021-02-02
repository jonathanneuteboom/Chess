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

TEST(KingTests, NoMovesLeft)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(4, 4);
    Factories::BoardFactory::CreateBoard(&c, "K", "-  Q  N");
    c.PrintBoard();

    c.AppendMoves(moves);

    ASSERT_EQ(c.CanPlayerCaptureSquare(BLACK, 0, 0), true);
    ASSERT_EQ(moves.size(), 0);
}

TEST(KingTests, NoMovesLeft2)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(4, 4);
    Factories::BoardFactory::CreateBoard(&c, "K", "- N p");
    c.PrintBoard();

    c.AppendMoves(moves);

    ASSERT_EQ(c.CanPlayerCaptureSquare(BLACK, 0, 0), false);
    ASSERT_EQ(moves.size(), 0);
}

TEST(KingTests, Castling1)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(4, 1);
    Factories::BoardFactory::CreateBoard(&c, "RQKR", "");
    c.PrintBoard();

    c.AppendMoves(moves);

    ASSERT_EQ(moves.size(), 1);
    ASSERT_EQ(moves[0]->newX, 3);
    ASSERT_EQ(moves[0]->newY, 0);
    ASSERT_EQ(moves[0]->moveType, KINGSIDE_CASTLE);
}

TEST(KingTests, NoCastlingWithMovedKing)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(4, 1);
    Factories::BoardFactory::CreateBoard(&c, "RQkR", "");
    c.PrintBoard();

    c.AppendMoves(moves);

    ASSERT_EQ(moves.size(), 0);
}

TEST(KingTests, NoCastlingWithMovedRook)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(4, 1);
    Factories::BoardFactory::CreateBoard(&c, "RQKr", "");
    c.PrintBoard();

    c.AppendMoves(moves);

    ASSERT_EQ(moves.size(), 0);
}

TEST(KingTests, Castling2)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(4, 1);
    Factories::BoardFactory::CreateBoard(&c, "RKQR", "");
    c.PrintBoard();

    c.AppendMoves(moves);

    ASSERT_EQ(moves.size(), 1);
    ASSERT_EQ(moves[0]->newX, 0);
    ASSERT_EQ(moves[0]->newY, 0);
    ASSERT_EQ(moves[0]->moveType, QUEENSIDE_CASTLE);
}

TEST(KingTests, NoCastlingIfEndResultIsCheck1)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(4, 4);
    Factories::BoardFactory::CreateBoard(&c, "  KR", "- N     Q");
    c.PrintBoard();

    c.pieces[c.GetPlayerIndex(WHITE)][0]->AppendMoves(&c, moves);

    ASSERT_EQ(moves.size(), 0);
}

TEST(KingTests, ValidCastling)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(8, 8);
    Factories::BoardFactory::CreateBoard(&c, "    K  R", "R");
    c.PrintBoard();

    c.pieces[c.GetPlayerIndex(WHITE)][0]->AppendMoves(&c, moves);

    ASSERT_EQ(moves.size(), 6);
    Move *castlingMove = moves[5];
    ASSERT_EQ(castlingMove->newX, 6);
    ASSERT_EQ(castlingMove->newY, 0);
    ASSERT_EQ(castlingMove->moveType, KINGSIDE_CASTLE);
}

TEST(KingTests, NoCastlingIfEndResultIsCheck2)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(8, 8);
    Factories::BoardFactory::CreateBoard(&c, "    K  R", " R");
    c.PrintBoard();

    c.pieces[c.GetPlayerIndex(WHITE)][0]->AppendMoves(&c, moves);

    ASSERT_EQ(moves.size(), 5);
}

TEST(KingTests, NoCastlingIfEndResultIsCheck3)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(8, 8);
    Factories::BoardFactory::CreateBoard(&c, "    K  R", "  R");
    c.PrintBoard();

    c.pieces[c.GetPlayerIndex(WHITE)][0]->AppendMoves(&c, moves);

    ASSERT_EQ(moves.size(), 3);
}