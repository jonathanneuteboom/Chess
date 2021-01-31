#pragma once

#include "Player.h"
#include "Piece.h"

namespace Factories
{
    class Piece;
    class Chess;
    class PieceFactory
    {
    public:
        static Entities::Piece *CreatePiece(Player player, char letter, int x, int y, Entities::Chess *game);
    };
} // namespace Factories