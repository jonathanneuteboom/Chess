#pragma once

#include "Piece.h"

namespace Entities
{
    class Rook : public Piece
    {
        const int directions[4][2] = {
            {1, 0},
            {0, -1},
            {-1, 0},
            {0, 1}};

        bool canCastle;

    public:
        Rook(int x, int y, Player player, bool canCastle = true);

        virtual void AppendMoves(Chess *game, std::vector<Move *> &potentialMoves);

        virtual bool CanCaptureSquare(int x, int y, Chess *game);

        static bool CanCaptureSquare(int rookX, int rookY, int x, int y, Chess *game);

        virtual PieceType GetType();
    };
} // namespace Entities