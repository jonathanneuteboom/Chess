#include <vector>
#include <stdlib.h>

#include "Pieces\King.h"
#include "Piece.h"

namespace Entities
{

    King::King(int x, int y, Player player, bool canCastle) : Piece(x, y, player)
    {
        this->canCastle = canCastle;
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
                break;

            if (!game->IsSquareFree(newX, newY))
            {
                if (game->GetPiece(newX, newY)->player == player)
                    continue;

                move = new Move(this, newX, newY, CAPTURE);
            }
            else
            {
                move = new Move(this, newX, newY, WALK);
            }

            if (game->CanPlayerHitSquare(opponent, newX, newY))
                continue;

            potentialMoves.push_back(move);
        }

        if (!canCastle)
        {
            return;
        }

        if (IsCastlingPossible(QUEENSIDE_CASTLE, game))
        {
            Piece *rook = GetCastlingRook(QUEENSIDE_CASTLE, game);
            int newX = GetNewKingXForCastling(QUEENSIDE_CASTLE, rook);
            potentialMoves.push_back(new Move(this, newX, y, QUEENSIDE_CASTLE));
        }

        if (IsCastlingPossible(KINGSIDE_CASTLE, game))
        {
            Piece *rook = GetCastlingRook(KINGSIDE_CASTLE, game);
            int newX = GetNewKingXForCastling(KINGSIDE_CASTLE, rook);
            potentialMoves.push_back(new Move(this, newX, y, KINGSIDE_CASTLE));
        }
    }

    int King::GetNewKingXForCastling(MoveType moveType, Piece *rook)
    {
        int d = moveType == QUEENSIDE_CASTLE ? x - rook->x : rook->x - x;
        return (d + 1) / 2;
    }

    Piece *King::GetCastlingRook(MoveType move, Chess *game)
    {
        int i = move == QUEENSIDE_CASTLE ? 0 : game->width - 1;
        int dx = move == QUEENSIDE_CASTLE ? 1 : -1;
        for (; i != x; i += dx)
        {
            Piece *piece = game->GetPiece(i, y);
            if (piece != nullptr && piece->GetType() == ROOK_CASTLE)
                return piece;
        }

        return nullptr;
    }

    bool King::IsCastlingPossible(MoveType move, Chess *game)
    {
        Piece *rook = GetCastlingRook(move, game);
        if (rook == nullptr)
            return false;

        int dx = rook->x < x ? 1 : -1;
        for (int newX = rook->x + dx; newX != x; newX += dx)
        {
            Piece *piece = game->GetPiece(newX, y);
            if (piece != nullptr)
                return false;
        }

        int playerIndex = game->GetPlayerIndex(player);

        int newKingX = GetNewKingXForCastling(move, rook);
        for (int newX = newKingX; newX != x; newX += dx)
        {
            for (int i = 0; i < game->numberOfPieces[playerIndex]; i++)
            {
                if (game->pieces[playerIndex][i]->CanCaptureSquare(newX, y, game))
                    return false;
            }
        }

        return true;
    }

    bool King::CanCaptureSquare(int x, int y, Chess *game)
    {
        (void)game;

        int dx = abs(this->x - x);
        int dy = abs(this->y - y);
        return dx + dy == 1 ||
               (dx == 1 && dy == 1);
    }

    PieceType King::GetType()
    {
        return canCastle ? KING_CASTLE : KING;
    }

    void King::ExecuteMove(Chess *game, Move *move)
    {
        switch (move->moveType)
        {
        case KINGSIDE_CASTLE:
        {
            game->MovePiece(move);

            Piece *rook = GetCastlingRook(KINGSIDE_CASTLE, game);
            Move rookMove = Move(rook, move->newSquare->x - 1, y, WALK);
            game->MovePiece(&rookMove);
            break;
        }
        case QUEENSIDE_CASTLE:
        {
            game->MovePiece(move);

            Piece *rook = GetCastlingRook(QUEENSIDE_CASTLE, game);
            Move rookMove = Move(rook, move->newSquare->x + 1, y, WALK);
            game->MovePiece(&rookMove);
            break;
        }
        default:
            Piece::ExecuteMove(game, move);
            break;
        }
    }
} // namespace Entities