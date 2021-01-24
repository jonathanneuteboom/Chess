#include <vector>
#include <stdlib.h>

#include "Piece.h"

namespace Entities
{
    class King : public Piece
    {
        bool canCastle;
        const int directions[8][2] = {
            {1, 0},
            {1, -1},
            {0, -1},
            {-1, -1},
            {-1, 0},
            {-1, 1},
            {0, 1},
            {1, 1},
        };

    public:
        King(int x, int y, Player player, bool canCastle = true) : Piece(x, y, player)
        {
            this->canCastle = canCastle;
        }

        virtual void AppendMoves(Chess *game, std::vector<Move *> &potentialMoves)
        {
            AppendMovesWithlinearDirections(game, directions, 8, potentialMoves, 1);

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

        int GetNewKingXForCastling(MoveType moveType, Piece *rook)
        {
            int d = moveType == QUEENSIDE_CASTLE ? x - rook->x : rook->x - x;
            return (d + 1) / 2;
        }

        Piece *GetCastlingRook(MoveType move, Chess *game)
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

        bool IsCastlingPossible(MoveType move, Chess *game)
        {
            Piece *rook = GetCastlingRook(move, game);
            if (rook == nullptr)
                return false;

            int dx = rook->x < x ? 1 : -1;
            for (int i = rook->x + dx; i != x; i += dx)
            {
                Piece *piece = game->GetPiece(i, y);
                if (piece != nullptr)
                    return false;
            }

            int playerIndex = player == WHITE ? BLACK : WHITE;

            int newKingX = GetNewKingXForCastling(move, rook);
            for (int newX = newKingX; newX != x; newX += dx)
            {
                for (int i = 0; i < game->numberOfPieces[playerIndex]; i++)
                {
                    if (game->pieces[playerIndex][i]->CanCaptureSquare(newX, y))
                        return false;
                }
            }

            return true;
        }

        virtual bool CanCaptureSquare(int x, int y)
        {
            int dx = abs(this->x - x);
            int dy = abs(this->x - y);
            return dx + dy == 1 ||
                   (dx == 1 && dy == 1);
        }

        virtual PieceType GetType()
        {
            return canCastle ? KING_CASTLE : KING;
        }

        virtual void ExecuteMove(Chess *game, Move *move)
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
    };
} // namespace Entities