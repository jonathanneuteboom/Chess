#include <gtest/gtest.h>
#include "Chess.h"

using namespace Entities;

TEST(Pion, standardWalk)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(4, 4);
    c.InitBoard((char *)"p", NULL);

    // act
    c.AppendMoves(moves);

    // assert
    ASSERT_EQ(moves.size(), 2);

    Move *eenStap = moves[0];
    ASSERT_EQ(eenStap->newSquare->x, 0);
    ASSERT_EQ(eenStap->newSquare->y, 1);
    ASSERT_EQ(eenStap->moveType, WALK);

    Move *tweeStappen = moves[1];
    ASSERT_EQ(tweeStappen->newSquare->x, 0);
    ASSERT_EQ(tweeStappen->newSquare->y, 2);
    ASSERT_EQ(tweeStappen->moveType, WALK);
}

TEST(Pion, promotion)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(4, 4);
    c.InitBoard((char *)"    p", NULL);
    c.PrintBoard();

    // act
    c.AppendMoves(moves);

    // assert
    ASSERT_EQ(moves.size(), 5);

    Move *eenStap = moves[0];
    ASSERT_EQ(eenStap->newSquare->x, 0);
    ASSERT_EQ(eenStap->newSquare->y, 2);
    ASSERT_EQ(eenStap->moveType, WALK);

    Move *queenPromotion = moves[1];
    ASSERT_EQ(queenPromotion->newSquare->x, 0);
    ASSERT_EQ(queenPromotion->newSquare->y, 3);
    ASSERT_EQ(queenPromotion->moveType, QUEEN_PROMOTION);

    Move *rookPromotion = moves[2];
    ASSERT_EQ(rookPromotion->newSquare->x, 0);
    ASSERT_EQ(rookPromotion->newSquare->y, 3);
    ASSERT_EQ(rookPromotion->moveType, ROOK_PROMOTION);

    Move *knightPromotion = moves[3];
    ASSERT_EQ(knightPromotion->newSquare->x, 0);
    ASSERT_EQ(knightPromotion->newSquare->y, 3);
    ASSERT_EQ(knightPromotion->moveType, KNIGHT_PROMOTION);

    Move *bishopPromotion = moves[4];
    ASSERT_EQ(bishopPromotion->newSquare->x, 0);
    ASSERT_EQ(bishopPromotion->newSquare->y, 3);
    ASSERT_EQ(bishopPromotion->moveType, BISHOP_PROMOTION);
}

TEST(Pion, promotionMove)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(4, 4);
    c.InitBoard((char *)"--p", NULL);
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
    c.InitBoard((char *)"-p", (char *)"-   p  P");
    c.AppendMoves(moves);

    // act
    ASSERT_EQ(moves.size(), 1);

    // assert
    Move *normalWalk = moves[0];
    ASSERT_EQ(normalWalk->newSquare->x, 1);
    ASSERT_EQ(normalWalk->newSquare->y, 2);
    ASSERT_EQ(normalWalk->moveType, EN_PASSANT_CAPTURE);
}

TEST(Pion, Capture)
{
    // arrange
    std::vector<Move *> moves;
    Chess c = Chess(4, 4);
    c.InitBoard((char *)"- p", (char *)"- pp");

    // act
    c.AppendMoves(moves);

    // assert
    ASSERT_EQ(moves.size(), 1);

    Move *capture = moves[0];
    ASSERT_EQ(capture->newSquare->x, 2);
    ASSERT_EQ(capture->newSquare->y, 2);
    ASSERT_EQ(capture->moveType, WALK);
}