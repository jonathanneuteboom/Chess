#pragma once

#include "Piece.h"
#include "MoveType.h"
#include "Square.h"

namespace Entities
{
    class Piece;
    class Move
    {
    public:
        Piece *piece;
        Square *newSquare;
        MoveType moveType;

        Move(Piece *piece, int x, int y, MoveType moveType);
        void Print();
    };
} // namespace Entities