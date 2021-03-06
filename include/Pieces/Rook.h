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

        bool didRookMove;

    public:
        Rook(int x, int y, Player player, bool didRookMove = false);

        virtual void AppendMoves(Chess *game, std::vector<Move *> &potentialMoves);
        virtual bool CanPieceCaptureSquare(int x, int y, Chess *game);
        virtual void ExecuteMove(Chess *game, Move *move);

        static bool CanPieceCaptureSquare(int rookX, int rookY, int x, int y, Chess *game);

        virtual PieceType GetType();
    };
} // namespace Entities