#include <gtest/gtest.h>
#include "Chess.h"
#include "BoardFactory.h"

using namespace Entities;

TEST(Pion, standardWalk)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(4, 4);
    Factories::BoardFactory::CreateBoard(&c, "p", "");

    // act
    c.AppendMoves(moves);

    // assert
    ASSERT_EQ(moves.size(), 2);

    Move *eenStap = moves[0];
    ASSERT_EQ(eenStap->newX, 0);
    ASSERT_EQ(eenStap->newY, 1);
    ASSERT_EQ(eenStap->moveType, WALK);

    Move *tweeStappen = moves[1];
    ASSERT_EQ(tweeStappen->newX, 0);
    ASSERT_EQ(tweeStappen->newY, 2);
    ASSERT_EQ(tweeStappen->moveType, WALK);
}

TEST(Pion, promotion)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(4, 4);
    Factories::BoardFactory::CreateBoard(&c, "    p", "");
    c.PrintBoard();

    // act
    c.AppendMoves(moves);

    // assert
    ASSERT_EQ(moves.size(), 5);

    Move *eenStap = moves[0];
    ASSERT_EQ(eenStap->newX, 0);
    ASSERT_EQ(eenStap->newY, 2);
    ASSERT_EQ(eenStap->moveType, WALK);

    Move *queenPromotion = moves[1];
    ASSERT_EQ(queenPromotion->newX, 0);
    ASSERT_EQ(queenPromotion->newY, 3);
    ASSERT_EQ(queenPromotion->moveType, QUEEN_PROMOTION);

    Move *rookPromotion = moves[2];
    ASSERT_EQ(rookPromotion->newX, 0);
    ASSERT_EQ(rookPromotion->newY, 3);
    ASSERT_EQ(rookPromotion->moveType, ROOK_PROMOTION);

    Move *knightPromotion = moves[3];
    ASSERT_EQ(knightPromotion->newX, 0);
    ASSERT_EQ(knightPromotion->newY, 3);
    ASSERT_EQ(knightPromotion->moveType, KNIGHT_PROMOTION);

    Move *bishopPromotion = moves[4];
    ASSERT_EQ(bishopPromotion->newX, 0);
    ASSERT_EQ(bishopPromotion->newY, 3);
    ASSERT_EQ(bishopPromotion->moveType, BISHOP_PROMOTION);
}

TEST(Pion, promotionMove)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(4, 4);
    Factories::BoardFactory::CreateBoard(&c, "--p", "");
    c.PrintBoard();

    // act
    c.AppendMoves(moves);
    c.ExecuteMove(moves[0]);

    //assert
    EXPECT_EQ(c.numberOfPieces[c.GetPlayerIndex(WHITE)], 1);
    EXPECT_EQ(c.numberOfPieces[c.GetPlayerIndex(BLACK)], 0);

    Piece *queen = c.pieces[c.GetPlayerIndex(WHITE)][0];
    EXPECT_EQ(queen->GetType(), QUEEN);
    EXPECT_EQ(queen->x, 0);
    EXPECT_EQ(queen->y, 3);
}

TEST(Pion, enPassant)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(4, 4);
    Factories::BoardFactory::CreateBoard(&c, "-p", "-   p  P");
    c.PrintBoard();
    c.AppendMoves(moves);

    // act
    ASSERT_EQ(moves.size(), 1);

    // assert
    Move *normalWalk = moves[0];
    ASSERT_EQ(normalWalk->newX, 1);
    ASSERT_EQ(normalWalk->newY, 2);
    ASSERT_EQ(normalWalk->moveType, EN_PASSANT_CAPTURE);
}

TEST(PawnTests, PawnTypes)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(4, 4);
    Factories::BoardFactory::CreateBoard(&c, "p", "p");
    c.PrintBoard();
    ASSERT_EQ(c.pieces[c.GetPlayerIndex(WHITE)][0]->GetType(), PAWN);

    // act
    c.AppendMoves(moves);
    c.ExecuteMove(moves[1]);
    c.PrintBoard();

    // assert
    ASSERT_EQ(c.pieces[c.GetPlayerIndex(WHITE)][0]->GetType(), PAWN_EN_PASSANT);

    moves.clear();
    c.AppendMoves(moves);
    c.ExecuteMove(moves[1]);
    c.PrintBoard();

    // assert
    ASSERT_EQ(c.pieces[c.GetPlayerIndex(WHITE)][0]->GetType(), PAWN);
}

TEST(Pion, Capture)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(4, 4);
    Factories::BoardFactory::CreateBoard(&c, "- p", "- pp");

    // act
    c.AppendMoves(moves);

    // assert
    ASSERT_EQ(moves.size(), 1);

    Move *capture = moves[0];
    ASSERT_EQ(capture->newX, 2);
    ASSERT_EQ(capture->newY, 2);
    ASSERT_EQ(capture->moveType, WALK);
}

TEST(PawnTests, Possibilites)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(5, 5);
    Factories::BoardFactory::CreateBoard(&c, "  p", "");
    c.PrintBoard();

    bool squares[5][5] = {
        {0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0}};

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