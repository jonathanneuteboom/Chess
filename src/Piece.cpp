#include <vector>

#include "Player.h"
#include "Move.h"
#include "Piece.h"
#include <vector>

namespace Entities
{
    Piece::Piece(int x, int y, Player player)
    {
        this->x = x;
        this->y = y;
        this->player = player;
    }

    void Piece::AppendMovesWithlinearDirections(
        Chess *game,
        const int directions[][2],
        int numberOfDirections,
        std::vector<Move *> &potentialMoves)
    {
        for (int i = 0; i < numberOfDirections; i++)
        {
            for (int steps = 1;; steps++)
            {
                int newX = x + steps * directions[i][0];
                int newY = y + steps * directions[i][1];
                if (game->IsSquareOusideBounds(newX, newY))
                    break;

                if (!game->IsSquareFree(newX, newY))
                {
                    if (game->GetPiece(newX, newY)->player != player)
                    {
                        potentialMoves.push_back(new Move(this, newX, newY, WALK));
                    }

                    break;
                }

                potentialMoves.push_back(new Move(this, newX, newY, WALK));
            }
        }
    }
} // namespace Entities