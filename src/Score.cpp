#include "Score.h"

namespace Entities
{
    bool Score::operator!=(const Score &score)
    {
        return whiteMoves != score.whiteMoves ||
               blackMoves != score.blackMoves ||
               whiteWins != score.whiteWins ||
               blackWins != score.blackWins;
    }

    bool Score::operator>(const Score score)
    {
        return this != &score && this < &score;
    }

    bool Score::operator<(const Score score)
    {
        return whiteMoves - blackMoves < score.whiteMoves - score.blackMoves;
    }
} // namespace Entities
