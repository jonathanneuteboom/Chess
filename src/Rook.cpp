#include "Piece.h"
#include <vector>

namespace Entities
{
    class Rook : public Piece
    {
        const int directions[4][2] = {
            {1, 0},
            {0, -1},
            {-1, 0},
            {0, 1}};

    public:
        bool canCastle;

        Rook(int x, int y, Player player, bool canCastle = true) : Piece(x, y, player)
        {
            this->canCastle = canCastle;
        }

        virtual void AppendMoves(Chess *game, std::vector<Move *> &potentialMoves)
        {
            AppendMovesWithlinearDirections(game, directions, 4, potentialMoves);
        }

        virtual bool CanCaptureSquare(int x, int y)
        {
            return this->x == x || this->y == y;
        }

        virtual PieceType GetType()
        {
            return canCastle ? ROOK_CASTLE : ROOK;
        }
    };
} // namespace Entities