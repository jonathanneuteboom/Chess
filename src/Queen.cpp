#include <vector>
#include <stdlib.h>

#include "Piece.h"

namespace Entities
{
    class Queen : public Piece
    {
        const int directions[8][2] = {
            {1, 0},
            {1, -1},
            {0, -1},
            {-1, -1},
            {-1, 0},
            {-1, 1},
            {0, 1},
            {1, 1},
        };

    public:
        Queen(int x, int y, Player player) : Piece(x, y, player) {}

        virtual void AppendMoves(Chess *game, std::vector<Move *> &potentialMoves)
        {
            AppendMovesWithlinearDirections(game, directions, 8, potentialMoves);
        }

        virtual bool CanCaptureSquare(int x, int y)
        {
            int dx = abs(this->x - x);
            int dy = abs(this->x - x);
            return dx == dy || this->x == x || this->y == y;
        }

        virtual PieceType GetType()
        {
            return QUEEN;
        }
    };
} // namespace Entities