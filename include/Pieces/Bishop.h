#pragma once

#include "Piece.h"
#include "Move.h"

namespace Entities
{
    class Bishop : public Piece
    {
        const int directions[4][2] = {
            {1, 1},
            {1, -1},
            {-1, -1},
            {-1, 1}};

    public:
        Bishop(int x, int y, Player player);
        virtual void AppendMoves(Chess *game, std::vector<Move *> &potentialMoves);
        virtual bool CanPieceCaptureSquare(int x, int y, Chess *game);
        virtual void ExecuteMove(Chess *game, Move *move);
        
        static bool CanPieceCaptureSquare(int bishopX, int bishopY, int x, int y, Chess *game);
        virtual PieceType GetType();
    };
} // namespace Entities
