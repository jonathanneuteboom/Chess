#pragma once

namespace Entities
{
    enum MoveType
    {
        NONE = ' ',
        WALK = 'W',
        CAPTURE = 'C',
        EN_PASSANT_CAPTURE = 'E',
        DOUBLE_PAWN_WALK = 'D',
        QUEEN_PROMOTION = 'Q',
        ROOK_PROMOTION = 'R',
        KNIGHT_PROMOTION = 'K',
        BISHOP_PROMOTION = 'B',
        KINGSIDE_CASTLE = 'k',
        QUEENSIDE_CASTLE = 'q'
    };
}