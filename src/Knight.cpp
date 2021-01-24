#include <stdlib.h>
#include <vector>

#include "Piece.h"

namespace Entities
{
    class Knight : public Piece
    {
        const int directions[8][2] = {
            {1, 2},
            {2, 1},
            {2, -1},
            {1, -2},
            {-1, -2},
            {-2, -1},
            {-2, 1},
            {-1, 2}};

    public:
        Knight(int x, int y, Player player) : Piece(x, y, player) {}

        virtual bool CanCaptureSquare(int x, int y)
        {
            int dx = abs(this->x - x);
            int dy = abs(this->x - y);
            return dx + dy == 3;
        }

        virtual void AppendMoves(Chess *game, std::vector<Move *> &potentialMoves)
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

        virtual PieceType GetType()
        {
            return KNIGHT;
        }
    };
} // namespace Entities