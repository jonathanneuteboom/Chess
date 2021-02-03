#pragma once

#include "Piece.h"
#include "Pieces\Bishop.h"
#include "Pieces\Rook.h"

namespace Entities
{
    class Queen : public Piece
    {
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
        Queen(int x, int y, Player player);

        virtual void AppendMoves(Chess *game, std::vector<Move *> &potentialMoves);
        virtual bool CanPieceCaptureSquare(int x, int y, Chess *game);
        virtual void ExecuteMove(Chess *game, Move *move);
        virtual PieceType GetType();
    };
} // namespace Entities