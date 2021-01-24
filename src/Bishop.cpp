#include <vector>
#include <stdlib.h>

#include "Piece.h"
#include "Move.h"

namespace Entities
{
    class Bishop : public Piece
    {
        const int directions[4][2] = {
            {1, 1},
            {1, -1},
            {-1, -1},
            {-1, 1}};

    public:
        Bishop(int x, int y, Player player) : Piece(x, y, player) {}

        virtual void AppendMoves(Chess *game, std::vector<Move *> &potentialMoves)
        {
            AppendMovesWithlinearDirections(game, directions, 4, potentialMoves);
        }

        virtual bool CanCaptureSquare(int x, int y)
        {
            int dx = abs(this->x - x);
            int dy = abs(this->x - y);
            return dx == dy;
        }

        virtual PieceType GetType()
        {
            return BISHOP;
        }
    };
} // namespace Entities
