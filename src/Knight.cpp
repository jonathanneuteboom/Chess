#include <stdlib.h>
#include <vector>

#include "Pieces\Knight.h"
#include "Piece.h"

namespace Entities
{
    Knight::Knight(int x, int y, Player player) : Piece(x, y, player) {}

    bool Knight::CanPieceCaptureSquare(int x, int y, Chess *game)
    {
        (void)game;

        int dx = abs(this->x - x);
        int dy = abs(this->y - y);
        int difference = abs(dx - dy);
        return dx + dy == 3 && difference == 1;
    }

    void Knight::AppendMoves(Chess *game, std::vector<Move *> &potentialMoves)
    {
        Move *newMove;
        for (int i = 0; i < 8; i++)
        {
            int newX = x + moves[i][0];
            int newY = y + moves[i][1];
            if (game->IsSquareOusideBounds(newX, newY))
                continue;

            Piece *piece = game->GetPiece(newX, newY);
            if (piece != nullptr && piece->player == player)
                continue;

            newMove = new Move(this, newX, newY, WALK);
            potentialMoves.push_back(newMove);
        }
    }

    PieceType Knight::GetType()
    {
        return KNIGHT;
    }
} // namespace Entities