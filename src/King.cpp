#include <vector>
#include <stdlib.h>

#include "Pieces\King.h"
#include "Piece.h"

namespace Entities
{

    King::King(int x, int y, Player player, bool didKingMove) : Piece(x, y, player)
    {
        this->didKingMove = didKingMove;
    }

    void King::AppendMoves(Chess *game, std::vector<Move *> &potentialMoves)
    {
        Player opponent = game->GetOpponent(player);
        Move *move;

        for (int i = 0; i < 8; i++)
        {
            int newX = x + directions[i][0];
            int newY = y + directions[i][1];
            if (game->IsSquareOusideBounds(newX, newY))
                continue;

            Piece *piece = game->GetPiece(newX, newY);
            if (piece != nullptr && piece->player == player)
                continue;

            if (game->CanPlayerCaptureSquare(opponent, newX, newY))
                continue;

            move = new Move(this, newX, newY, WALK);
            potentialMoves.push_back(move);
        }

        if (didKingMove)
            return;

        for (int i = 0; i < 2; i++)
        {
            MoveType castlingOption = castlingOptions[i];
            if (IsCastlingPossible(castlingOption, game))
            {
                Piece *rook = GetCastlingRook(castlingOption, game);
                int newX = GetNewKingXForCastling(castlingOption, rook);
                move = new Move(this, newX, y, castlingOption);
                potentialMoves.push_back(move);
            }
        }
    }

    int King::GetNewKingXForCastling(MoveType moveType, Piece *rook)
    {
        int distance = (abs(x - rook->x) + 1) / 2;
        return moveType == QUEENSIDE_CASTLE ? x - distance : x + distance;
    }

    Rook *King::GetCastlingRook(MoveType move, Chess *game)
    {
        int i = move == QUEENSIDE_CASTLE ? 0 : game->width - 1;
        int dx = move == QUEENSIDE_CASTLE ? 1 : -1;
        for (; i != x; i += dx)
        {
            Piece *piece = game->GetPiece(i, y);
            if (piece != nullptr && piece->GetType() == ROOK_CASTLE)
                return (Rook *)piece;
        }

        return nullptr;
    }

    bool King::IsCastlingPossible(MoveType move, Chess *game)
    {
        Piece *rook = GetCastlingRook(move, game);
        if (rook == nullptr)
            return false;

        int dx = rook->x < x ? 1 : -1;
        int xInBetween = rook->x + dx;
        for (; xInBetween != x; xInBetween += dx)
        {
            Piece *piece = game->GetPiece(xInBetween, y);
            if (piece != nullptr)
                return false;
        }

        int newKingX = GetNewKingXForCastling(move, rook);
        Player opponent = game->GetOpponent(player);
        for (int xInBetween = newKingX; xInBetween != x; xInBetween += dx)
        {
            if (game->CanPlayerCaptureSquare(opponent, xInBetween, y))
            {
                return false;
            }
        }

        return true;
    }

    bool King::CanPieceCaptureSquare(int x, int y, Chess *game)
    {
        (void)game;

        int dx = abs(this->x - x);
        int dy = abs(this->y - y);
        return dx + dy == 1 ||
               (dx == 1 && dy == 1);
    }

    PieceType King::GetType()
    {
        return didKingMove ? KING : KING_CASTLE;
    }

    void King::ExecuteMove(Chess *game, Move *move)
    {
        didKingMove = true;
        switch (move->moveType)
        {
        case WALK:
            Piece::ExecuteMove(game, move);
            break;
        case KINGSIDE_CASTLE:
        {
            Rook *rook = GetCastlingRook(KINGSIDE_CASTLE, game);
            Move rookMove = Move(rook, move->newX - 1, rook->y, WALK);

            rook->ExecuteMove(game, &rookMove);
            Piece::ExecuteMove(game, move);
            break;
        }
        case QUEENSIDE_CASTLE:
        {
            Rook *rook = GetCastlingRook(QUEENSIDE_CASTLE, game);
            Move rookMove = Move(rook, move->newX + 1, rook->y, WALK);

            rook->ExecuteMove(game, &rookMove);
            Piece::ExecuteMove(game, move);
            break;
        }
        default:
            throw;
        }
    }
} // namespace Entities