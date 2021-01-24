#include <stdlib.h>
#include <vector>

#include "Pieces\Knight.h"
#include "Piece.h"

namespace Entities
{
    Knight::Knight(int x, int y, Player player) : Piece(x, y, player) {}

    bool Knight::CanCaptureSquare(int x, int y, Chess *game)
    {
        (void)game;

        int dx = abs(this->x - x);
        int dy = abs(this->y - y);
        return dx + dy == 3;
    }

    void Knight::AppendMoves(Chess *game, std::vector<Move *> &potentialMoves)
    {
        Move *newMove;
        for (int i = 0; i < 8; i++)
        {
            int newX = x + directions[i][0];
            int newY = y + directions[i][1];
            if (game->IsSquareOusideBounds(newX, newY))
                continue;

            if (game->IsSquareFree(newX, newY))
            {
                newMove = new Move(this, newX, newY, WALK);
                potentialMoves.push_back(newMove);
            }
            else if (game->GetPiece(newX, newY)->player != player)
            {
                newMove = new Move(this, newX, newY, CAPTURE);
                potentialMoves.push_back(newMove);
            }
        }
    }

    PieceType Knight::GetType()
    {
        return KNIGHT;
    }
} // namespace Entities