#pragma once

#include "Piece.h"

namespace Entities
{
    class Knight : public Piece
    {
        const int moves[8][2] = {
            {1, 2},
            {2, 1},
            {2, -1},
            {1, -2},
            {-1, -2},
            {-2, -1},
            {-2, 1},
            {-1, 2}};

    public:
        Knight(int x, int y, Player player);
        virtual bool CanPieceCaptureSquare(int x, int y, Chess *game);
        virtual void AppendMoves(Chess *game, std::vector<Move *> &potentialMoves);
        virtual void ExecuteMove(Chess *game, Move *move);
        virtual PieceType GetType();
    };
} // namespace Entities