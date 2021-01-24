#include "PieceFactory.h"
#include "Piece.h"
#include "PieceType.h"
#include "Chess.h"
#include "Player.h"

#include "Pieces\King.h"
#include "Pieces\Queen.h"
#include "Pieces\Rook.h"
#include "Pieces\Bishop.h"
#include "Pieces\Knight.h"
#include "Pieces\Pawn.h"

using namespace Entities;

namespace Factories
{
    Entities::Piece *PieceFactory::CreatePiece(Player player, char letter, int x, int y, Entities::Chess *game)
    {
        switch (letter)
        {
        case PAWN:
            return new Entities::Pawn(x, y, player, game);
        case PAWN_EN_PASSANT:
            return new Entities::Pawn(x, y, player, game);
        case BISHOP:
            return new Entities::Bishop(x, y, player);
        case KING:
            return new Entities::King(x, y, player, false);
        case KING_CASTLE:
            return new Entities::King(x, y, player);
        case KNIGHT:
            return new Entities::Knight(x, y, player);
        case QUEEN:
            return new Entities::Queen(x, y, player);
        case ROOK:
            return new Entities::Rook(x, y, player, false);
        case ROOK_CASTLE:
            return new Entities::Rook(x, y, player);
        }

        throw "No Piece option";
    }
} // namespace Factories