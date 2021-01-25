#pragma once

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
        King(int x, int y, Player player, bool canCastle = true);
        virtual void AppendMoves(Chess *game, std::vector<Move *> &potentialMoves);
        int GetNewKingXForCastling(MoveType moveType, Piece *rook);
        Piece *GetCastlingRook(MoveType move, Chess *game);
        bool IsCastlingPossible(MoveType move, Chess *game);
        virtual bool CanCaptureSquare(int x, int y, Chess *game);
        virtual PieceType GetType();
        virtual void ExecuteMove(Chess *game, Move *move);
    };
} // namespace Entities