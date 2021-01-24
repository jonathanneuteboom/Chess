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
        this->doubleSquareMoveRound = doubleSquareMoveRound;
        this->game = game;
    }

    bool Pawn::CanCaptureSquare(int x, int y, Chess *game)
    {
        (void)game;

        int dy = player == WHITE ? 1 : -1;
        return y + dy == this->y &&
               std::abs(this->x - x) == 1;
    }

    void Pawn::AppendPromotionMoves(int newX, int newY, std::vector<Move *> &potentialMoves)
    {
        Move *newMove;

        bool lastRow = player == WHITE ? game->height - 1 : 0;
        if (lastRow != newY)
        {
            newMove = new Move(this, x, newY, WALK);
            potentialMoves.push_back(newMove);
        }
        else
        {
            newMove = new Move(this, newX, newY, QUEEN_PROMOTION);
            potentialMoves.push_back(newMove);

            newMove = new Move(this, newX, newY, ROOK_PROMOTION);
            potentialMoves.push_back(newMove);

            newMove = new Move(this, newX, newY, KNIGHT_PROMOTION);
            potentialMoves.push_back(newMove);

            newMove = new Move(this, newX, newY, BISHOP_PROMOTION);
            potentialMoves.push_back(newMove);
        }
    }

    void Pawn::AppendNormalCaptureMoves(int direction, std::vector<Move *> &potentialMoves)
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
            if (piece->player != player)
            {
                AppendPromotionMoves(newX, newY, potentialMoves);
            }
        }
    }

    void Pawn::AppendEnPassantMoves(int direction, std::vector<Move *> &potentialMoves)
    {
        const int enPassantPawns[2][2] = {
            {x - 1, y},
            {x + 1, y},
        };
        for (int i = 0; i < 2; i++)
        {
            int newX = enPassantPawns[i][0];
            int newY = enPassantPawns[i][1];

            Piece *piece = game->GetPiece(newX, newY);
            if (piece == nullptr)
                continue;

            if (piece->GetType() == PieceType::PAWN_EN_PASSANT)
            {
                Move *newMove = new Move(this, newX, newY + direction, EN_PASSANT_CAPTURE);
                potentialMoves.push_back(newMove);
            }
        }
    }

    void Pawn::AppendMoves(Chess *game, std::vector<Move *> &potentialMoves)
    {
        int direction = Player::WHITE == player ? 1 : -1;

        int newX = x;
        int newY = y + direction;
        if (game->IsSquareFree(newX, newY))
        {
            AppendPromotionMoves(newX, newY, potentialMoves);

            newY += direction;
            if (!didPawnMove && game->IsSquareFree(newX, newY))
            {
                AppendPromotionMoves(newX, newY, potentialMoves);
            }
        }

        AppendNormalCaptureMoves(direction, potentialMoves);

        AppendEnPassantMoves(direction, potentialMoves);
    }

    void Pawn::ExecuteMove(Chess *game, Move *move)
    {
        PieceType newPieceType;

        didPawnMove = true;
        switch (move->moveType)
        {
        case WALK:
        {
            int stepLength = abs(y - move->newSquare->y);
            if (stepLength == 2)
            {
                doubleSquareMoveRound = game->currentRound;
            }

            Piece *piece = game->GetPiece(move->newSquare->x, move->newSquare->y);
            if (piece != nullptr)
            {
                game->RemovePiece(move->newSquare->x, move->newSquare->y);
            }
            game->MovePiece(move);
            return;
        }
        case EN_PASSANT_CAPTURE:
        {
            Piece *opposingPawn = game->GetPiece(move->newSquare->x, move->piece->x);
            game->RemovePiece(opposingPawn);
            game->MovePiece(move);
            return;
        }
        case QUEEN_PROMOTION:
            newPieceType = QUEEN;
            break;
        case ROOK_PROMOTION:
            newPieceType = ROOK;
            break;
        case KNIGHT_PROMOTION:
            newPieceType = KNIGHT;
            break;
        case BISHOP_PROMOTION:
            newPieceType = BISHOP;
            break;
        default:
            break;
        }

        Piece *newPiece = PieceFactory::CreatePiece(
            game->currentPlayer,
            newPieceType,
            move->newSquare->x,
            move->newSquare->y, game);
        game->SetPiece(newPiece, move->newSquare->x, move->newSquare->y);
    }

    PieceType Pawn::GetType()
    {
        return doubleSquareMoveRound == game->GetCurrentRound() - 1 ? PAWN_EN_PASSANT : PAWN;
    }
} // namespace Entities