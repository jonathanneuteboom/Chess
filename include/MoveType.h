#pragma once

namespace Entities
{
    enum MoveType
    {
        NONE = ' ',
        WALK = 'W',
        EN_PASSANT_CAPTURE = 'E',
        QUEEN_PROMOTION = 'Q',
        ROOK_PROMOTION = 'R',
        KNIGHT_PROMOTION = 'K',
        BISHOP_PROMOTION = 'B',
        KINGSIDE_CASTLE = 'k',
        QUEENSIDE_CASTLE = 'q'
    };
}