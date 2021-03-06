#include <stdlib.h>
#include <vector>

#include "Pieces\Pawn.h"
#include "Piece.h"
#include "Player.h"
#include "Chess.h"
#include "Move.h"
#include "PieceFactory.h"

using namespace Factories;

namespace Entities
{
    Pawn::Pawn(int x, int y, Player player, Chess *game, int doubleSquareMoveRound) : Piece(x, y, player)
    {
        this->game = game;
        this->doubleSquareMoveRound = doubleSquareMoveRound;
    }

    bool Pawn::CanPieceCaptureSquare(int x, int y, Chess *game)
    {
        (void)game;

        int yRichting = player == WHITE ? 1 : -1;
        int dx = std::abs(this->x - x);
        return this->y + yRichting == y &&
               dx == 1;
    }

    void Pawn::AppendWalkingMoves(int newX, int newY, std::vector<Move *> &potentialMoves, Chess *game)
    {
        Move *newMove;

        int lastRow = player == WHITE ? game->height - 1 : 0;
        if (lastRow != newY)
        {
            newMove = new Move(x, y, newX, newY, WALK);
            potentialMoves.push_back(newMove);
        }
        else
        {
            newMove = new Move(x, y, newX, newY, QUEEN_PROMOTION);
            potentialMoves.push_back(newMove);

            newMove = new Move(x, y, newX, newY, ROOK_PROMOTION);
            potentialMoves.push_back(newMove);

            newMove = new Move(x, y, newX, newY, KNIGHT_PROMOTION);
            potentialMoves.push_back(newMove);

            newMove = new Move(x, y, newX, newY, BISHOP_PROMOTION);
            potentialMoves.push_back(newMove);
        }
    }

    void Pawn::AppendNormalCaptureMoves(int direction, std::vector<Move *> &potentialMoves, Chess *game)
    {
        const int normalCaptureDirections[2][2] = {
            {x - 1, y + direction},
            {x + 1, y + direction},
        };
        for (int i = 0; i < 2; i++)
        {
            int newX = normalCaptureDirections[i][0];
            int newY = normalCaptureDirections[i][1];
            if (game->IsSquareOusideBounds(newX, newY))
                continue;

            Piece *piece = game->GetPiece(newX, newY);
            if (piece == nullptr)
                continue;
            if (piece->player == player)
                continue;

            AppendWalkingMoves(newX, newY, potentialMoves, game);
        }
    }

    void Pawn::AppendEnPassantMoves(int direction, std::vector<Move *> &potentialMoves, Chess *game)
    {
        const int enPassantPawns[2][2] = {
            {x - 1, y},
            {x + 1, y},
        };
        for (int i = 0; i < 2; i++)
        {
            int newX = enPassantPawns[i][0];
            int newY = enPassantPawns[i][1];
            if (game->IsSquareOusideBounds(newX, newY))
                continue;

            Piece *piece = game->GetPiece(newX, newY);
            if (piece == nullptr)
                continue;

            if (piece->GetType() != PieceType::PAWN_EN_PASSANT ||
                piece->player == player)
                continue;

            Move *newMove = new Move(x, y, newX, newY + direction, EN_PASSANT_CAPTURE);
            potentialMoves.push_back(newMove);
        }
    }

    void Pawn::AppendMoves(Chess *game, std::vector<Move *> &potentialMoves)
    {
        int direction = Player::WHITE == player ? 1 : -1;

        int newX = x;
        int newY = y + direction;
        if (game->IsSquareFree(newX, newY))
        {
            AppendWalkingMoves(newX, newY, potentialMoves, game);

            newY += direction;
            if (!didPawnMove && game->IsSquareFree(newX, newY))
            {
                AppendWalkingMoves(newX, newY, potentialMoves, game);
            }
        }

        AppendNormalCaptureMoves(direction, potentialMoves, game);

        AppendEnPassantMoves(direction, potentialMoves, game);
    }

    PieceType Pawn::GetPromotedPieceType(MoveType move)
    {
        switch (move)
        {
        case QUEEN_PROMOTION:
            return QUEEN;
        case ROOK_PROMOTION:
            return ROOK;
        case KNIGHT_PROMOTION:
            return KNIGHT;
        case BISHOP_PROMOTION:
            return BISHOP;
        default:
            throw;
        }
    }

    void Pawn::ExecuteMove(Chess *game, Move *move)
    {
        didPawnMove = true;
        switch (move->moveType)
        {
        case WALK:
        {
            int stepLength = abs(y - move->newY);
            if (stepLength == 2)
            {
                doubleSquareMoveRound = game->currentRound;
            }
            game->Walk(move);
            break;
        }
        case QUEEN_PROMOTION:
        case ROOK_PROMOTION:
        case KNIGHT_PROMOTION:
        case BISHOP_PROMOTION:
        {
            Piece *piece = game->GetPiece(move->newX, move->newY);
            if (piece != nullptr)
            {
                game->RemovePiece(piece);
            }

            PieceType newPieceType = GetPromotedPieceType(move->moveType);
            game->AddPiece(player, newPieceType, move->newX, move->newY);
            game->RemovePiece(this);
            break;
        }
        case EN_PASSANT_CAPTURE:
        {
            Piece *opposingPawn = game->GetPiece(move->newX, y);
            game->RemovePiece(opposingPawn);
            game->Walk(move);
            break;
        }
        default:
            throw;
        }
    }

    PieceType Pawn::GetType()
    {
        return doubleSquareMoveRound == game->GetCurrentRound() - 1 ? PAWN_EN_PASSANT : PAWN;
    }
} // namespace Entities