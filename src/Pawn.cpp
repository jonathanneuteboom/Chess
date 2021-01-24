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

    void Pawn::AppendMoves(Chess *game, std::vector<Move *> &potentialMoves)
    {
        int direction = Player::WHITE == player ? 1 : -1;
        Move *newMove;
        int newX, newY = y + direction;
        if (game->IsSquareFree(x, newY))
        {
            bool isLastRow = game->IsSquareOusideBounds(x, newY + direction);
            if (isLastRow)
            {
                newMove = new Move(this, x, newY, QUEEN_PROMOTION);
                potentialMoves.push_back(newMove);

                newMove = new Move(this, x, newY, ROOK_PROMOTION);
                potentialMoves.push_back(newMove);

                newMove = new Move(this, x, newY, KNIGHT_PROMOTION);
                potentialMoves.push_back(newMove);

                newMove = new Move(this, x, newY, BISHOP_PROMOTION);
                potentialMoves.push_back(newMove);
            }
            else
            {
                newMove = new Move(this, x, newY, WALK);
                potentialMoves.push_back(newMove);

                newY = y + 2 * direction;
                if (!didPawnMove && game->IsSquareFree(x, newY))
                {
                    newMove = new Move(this, x, newY, DOUBLE_PAWN_WALK);
                    potentialMoves.push_back(newMove);
                }
            }
        }

        const int normalCaptureDirections[2][2] = {
            {x - 1, y + direction},
            {x + 1, y + direction},
        };
        for (int i = 0; i < 2; i++)
        {
            newX = normalCaptureDirections[i][0];
            newY = normalCaptureDirections[i][1];
            if (game->IsSquareOusideBounds(newX, newY))
                continue;
            Piece *piece = game->GetPiece(newX, newY);
            if (piece == nullptr)
                continue;
            if (piece->player != player)
            {
                potentialMoves.push_back(new Move(this, newX, newY, CAPTURE));
            }
        }

        const int enPassantPawns[2][2] = {
            {x - 1, y},
            {x + 1, y},
        };
        for (int i = 0; i < 2; i++)
        {
            newX = enPassantPawns[i][0];
            newY = enPassantPawns[i][1];

            Piece *piece = game->GetPiece(newX, newY);
            if (piece == nullptr)
                continue;

            if (piece->GetType() == PieceType::PAWN_EN_PASSANT)
            {
                potentialMoves.push_back(new Move(this, newX, newY + direction, EN_PASSANT_CAPTURE));
            }
        }
    }

    void Pawn::ExecuteMove(Chess *game, Move *move)
    {
        PieceType newPieceType;

        didPawnMove = true;
        switch (move->moveType)
        {
        case WALK:
            game->MovePiece(move);
            return;
        case CAPTURE:
            game->RemovePiece(move->newSquare->x, move->newSquare->y);
            game->MovePiece(move);
            return;
        case EN_PASSANT_CAPTURE:
        {
            Piece *opposingPawn = game->GetPiece(move->newSquare->x, move->piece->x);
            game->RemovePiece(opposingPawn);
            game->MovePiece(move);
            return;
        }
        case DOUBLE_PAWN_WALK:
            game->MovePiece(move);
            doubleSquareMoveRound = game->currentRound;
            return;
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