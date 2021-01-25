#pragma once

#include "Piece.h"

namespace Entities
{
    class Knight : public Piece
    {
        const int directions[8][2] = {
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
        virtual bool CanCaptureSquare(int x, int y, Chess *game);
        virtual void AppendMoves(Chess *game, std::vector<Move *> &potentialMoves);
        virtual PieceType GetType();
    };
} // namespace Entities