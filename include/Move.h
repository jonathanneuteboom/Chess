#pragma once

#include "Piece.h"
#include "MoveType.h"

namespace Entities
{
    class Piece;
    class Score;
    class Move
    {
    public:
        int x, y;
        int newX, newY;
        MoveType moveType;

        Move(int x, int y, int newX, int newY, MoveType moveType);
        void Print(Piece *piece);
    };
} // namespace Entities