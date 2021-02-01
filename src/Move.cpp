#include <iostream>
#include "Piece.h"
#include "MoveType.h"
#include "Move.h"

namespace Entities
{
    Move::Move(Piece *piece, int newX, int newY, MoveType moveType)
    {
        this->piece = piece;
        this->newX = newX;
        this->newY = newY;
        this->moveType = moveType;
    };

    void Move::Print()
    {
        std::cout << (char)(piece->GetType())
                  << "(" << piece->x + 1 << ", " << piece->y + 1
                  << ") -> (" << newX + 1 << ", " << newY + 1 << ") "
                  << (char)moveType << std::endl;
    }
} // namespace Entities