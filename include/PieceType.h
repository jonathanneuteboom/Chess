#pragma once

namespace Entities
{
    enum PieceType
    {
        EMPTY = ' ',
        PAWN = 'p',
        PAWN_EN_PASSANT = 'P',
        KNIGHT = 'N',
        BISHOP = 'B',
        ROOK = 'r',
        ROOK_CASTLE = 'R',
        QUEEN = 'Q',
        KING = 'k',
        KING_CASTLE = 'K'
    };
}