#include <vector>
#include <stdlib.h>

#include "Piece.h"
#include "Pieces\Bishop.h"
#include "Pieces\Rook.h"
#include "Pieces\Queen.h"

namespace Entities
{
    Queen::Queen(int x, int y, Player player) : Piece(x, y, player) {}

    void Queen::AppendMoves(Chess *game, std::vector<Move *> &potentialMoves)
    {
        AppendMovesWithlinearDirections(game, directions, 8, potentialMoves);
    }

    bool Queen::CanPieceCaptureSquare(int x, int y, Chess *game)
    {
        int dx = abs(this->x - x);
        int dy = abs(this->y - y);
        if (dx == dy)
        {
            return Bishop::CanPieceCaptureSquare(this->x, this->y, x, y, game);
        }

        if (this->x == x || this->y == y)
        {
            return Rook::CanPieceCaptureSquare(this->x, this->y, x, y, game);
        }

        return false;
    }

    void Queen::ExecuteMove(Chess *game, Move *move)
    {
        game->Walk(move);
    }

    PieceType Queen::GetType()
    {
        return QUEEN;
    }
} // namespace Entities