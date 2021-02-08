#pragma once

#include "Move.h"

namespace Entities
{
    class Move;
    class Score
    {
        long whiteMoves;
        long blackMoves;
        bool whiteWins;
        bool blackWins;
        Move *move;

        bool operator!=(const Score &score);

        bool operator>(const Score score);

        bool operator<(const Score score);
    };
} // namespace Entities
