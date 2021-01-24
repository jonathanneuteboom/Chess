#include <iostream>
#include "Piece.h"
#include "MoveType.h"
#include "Square.h"
#include "Move.h"

namespace Entities
{
    Move::Move(Piece *piece, int x, int y, MoveType moveType)
    {
        this->piece = piece;
        this->newSquare = new Square(x, y);
        this->moveType = moveType;
    };

    void Move::Print()
    {
        std::cout << (char)(piece->GetType())
                  << "(" << piece->x + 1 << ", " << piece->y + 1
                  << ") -> (" << newSquare->x + 1 << ", " << newSquare->y + 1 << ") "
                  << (char)moveType << std::endl;
    }
} // namespace Entities