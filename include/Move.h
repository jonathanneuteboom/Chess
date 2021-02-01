#pragma once

#include "Piece.h"
#include "MoveType.h"

namespace Entities
{
    class Piece;
    class Move
    {
    public:
        Piece *piece;
        int newX;
        int newY;
        MoveType moveType;

        Move(Piece *piece, int newX, int newY, MoveType moveType);
        void Print();
    };
} // namespace Entities