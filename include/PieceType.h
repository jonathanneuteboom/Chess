#pragma once

namespace Entities
{
    enum PieceType
    {
        EMPTY = ' ',
        PAWN = 'p',
        PAWN_EN_PASSANT = 'P',
        KNIGHT = 'n',
        BISHOP = 'b',
        ROOK = 'r',
        ROOK_CASTLE = 'R',
        QUEEN = 'q',
        KING = 'k',
        KING_CASTLE = 'K'
    };
}