#include "PieceFactory.h"
#include "Piece.h"
#include "PieceType.h"
#include "Chess.h"
#include "Player.h"
#include "Pawn.cpp"
#include "Knight.cpp"
#include "Bishop.cpp"
#include "Rook.cpp"
#include "Queen.cpp"
#include "King.cpp"

using namespace Entities;

namespace Factories
{
    Entities::Piece *PieceFactory::CreatePiece(Player player, char letter, int x, int y, Entities::Chess *game)
    {
        switch (letter)
        {
        case PAWN:
            return new Pawn(x, y, player, game);
        case PAWN_EN_PASSANT:
            return new Pawn(x, y, player, game);
        case BISHOP:
            return new Bishop(x, y, player);
        case KING:
            return new King(x, y, player, false);
        case KING_CASTLE:
            return new King(x, y, player);
        case KNIGHT:
            return new Knight(x, y, player);
        case QUEEN:
            return new Queen(x, y, player);
        case ROOK:
            return new Rook(x, y, player, false);
        case ROOK_CASTLE:
            return new Rook(x, y, player);
        }

        throw "No Piece option";
    }
} // namespace Factories