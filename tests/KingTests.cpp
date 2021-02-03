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
    c.pieces[WHITE][0]->AppendMoves(&c, moves);

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
    ASSERT_EQ(c.pieces[WHITE][0]->GetType(), KING_CASTLE);
}

TEST(KingTests, Possibilities3)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(2, 2);
    Factories::BoardFactory::CreateBoard(&c, "K", "");
    c.PrintBoard();

    // act
    c.pieces[WHITE][0]->AppendMoves(&c, moves);
    c.ExecuteMove(moves[0]);

    // assert
    ASSERT_EQ(c.pieces[WHITE][0]->GetType(), KING);
}

TEST(KingTests, Possibilites4)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(5, 5);
    Factories::BoardFactory::CreateBoard(&c, "--  K", "");
    c.PrintBoard();

    bool squares[5][5] = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}};

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

TEST(KingTests, NoMovesLeft3)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(5, 5);
    Factories::BoardFactory::CreateBoard(&c, "--  K", "-    QB  Bp-N  R");
    c.PrintBoard();

    c.AppendMoves(moves);

    ASSERT_EQ(c.CanPlayerCaptureSquare(BLACK, 2, 2), false);
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

    c.pieces[WHITE][0]->AppendMoves(&c, moves);

    ASSERT_EQ(moves.size(), 0);
}

TEST(KingTests, ValidCastling)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(8, 8);
    Factories::BoardFactory::CreateBoard(&c, "    K  R", "R");
    c.PrintBoard();

    c.pieces[WHITE][0]->AppendMoves(&c, moves);

    ASSERT_EQ(moves.size(), 6);
    Move *castlingMove = moves[5];
    ASSERT_EQ(castlingMove->newX, 6);
    ASSERT_EQ(castlingMove->newY, 0);
    ASSERT_EQ(castlingMove->moveType, KINGSIDE_CASTLE);
}

TEST(KingTests, ExecuteKingsideCastle)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(8, 8);
    Factories::BoardFactory::CreateBoard(&c, "    K  R", "");
    c.PrintBoard();

    Piece *king = c.pieces[WHITE][0];
    Piece *rook = c.pieces[WHITE][1];

    king->AppendMoves(&c, moves);
    Move *castlingMove = moves[5];
    c.ExecuteMove(castlingMove);
    c.PrintBoard();

    king = c.pieces[WHITE][0];
    rook = c.pieces[WHITE][1];

    ASSERT_EQ(king->x, 6);
    ASSERT_EQ(king->y, 0);
    ASSERT_EQ(rook->x, 5);
    ASSERT_EQ(rook->y, 0);
}

TEST(KingTests, ExecuteQueensideCastle)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(8, 8);
    Factories::BoardFactory::CreateBoard(&c, "R   K", "");
    c.PrintBoard();

    Piece *king = c.pieces[WHITE][1];
    Piece *rook = c.pieces[WHITE][0];

    king->AppendMoves(&c, moves);
    Move *castlingMove = moves[5];
    c.ExecuteMove(castlingMove);
    c.PrintBoard();

    king = c.pieces[WHITE][0];
    rook = c.pieces[WHITE][1];

    ASSERT_EQ(king->x, 2);
    ASSERT_EQ(king->y, 0);
    ASSERT_EQ(rook->x, 3);
    ASSERT_EQ(rook->y, 0);
}

TEST(KingTests, ExecuteSmallKingsideCastle)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(4, 4);
    Factories::BoardFactory::CreateBoard(&c, "  KR", "");
    c.PrintBoard();

    Piece *king = c.pieces[WHITE][0];
    Piece *rook = c.pieces[WHITE][1];

    king->AppendMoves(&c, moves);
    Move *castlingMove = moves[4];
    c.ExecuteMove(castlingMove);
    c.PrintBoard();

    king = c.pieces[WHITE][0];
    rook = c.pieces[WHITE][1];

    ASSERT_EQ(king->x, 3);
    ASSERT_EQ(king->y, 0);
    ASSERT_EQ(rook->x, 2);
    ASSERT_EQ(rook->y, 0);
}

TEST(KingTests, ExecuteSmallQueensideCastle)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(8, 8);
    Factories::BoardFactory::CreateBoard(&c, "R K", "");
    c.PrintBoard();

    Piece *king = c.pieces[WHITE][1];
    Piece *rook = c.pieces[WHITE][0];

    king->AppendMoves(&c, moves);
    Move *castlingMove = moves[5];
    c.ExecuteMove(castlingMove);
    c.PrintBoard();

    king = c.pieces[WHITE][0];
    rook = c.pieces[WHITE][1];

    ASSERT_EQ(king->x, 1);
    ASSERT_EQ(king->y, 0);
    ASSERT_EQ(rook->x, 2);
    ASSERT_EQ(rook->y, 0);
}

TEST(KingTests, NoCastlingIfEndResultIsCheck2)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(8, 8);
    Factories::BoardFactory::CreateBoard(&c, "    K  R", " R");
    c.PrintBoard();

    c.pieces[WHITE][0]->AppendMoves(&c, moves);

    ASSERT_EQ(moves.size(), 5);
}

TEST(KingTests, NoCastlingIfEndResultIsCheck3)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(8, 8);
    Factories::BoardFactory::CreateBoard(&c, "    K  R", "  R");
    c.PrintBoard();

    c.pieces[WHITE][0]->AppendMoves(&c, moves);

    ASSERT_EQ(moves.size(), 3);
}