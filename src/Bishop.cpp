#include <vector>
#include <stdlib.h>

#include "Piece.h"
#include "Move.h"
#include "Pieces\Bishop.h"

namespace Entities
{
    Bishop::Bishop(int x, int y, Player player) : Piece(x, y, player) {}

    void Bishop::AppendMoves(Chess *game, std::vector<Move *> &potentialMoves)
    {
        AppendMovesWithlinearDirections(game, directions, 4, potentialMoves);
    }

    bool Bishop::CanPieceCaptureSquare(int x, int y, Chess *game)
    {
        return Bishop::CanPieceCaptureSquare(this->x, this->y, x, y, game);
    }

    bool Bishop::CanPieceCaptureSquare(int bishopX, int bishopY, int x, int y, Chess *game)
    {
        int dx = x - bishopX;
        int dy = y - bishopY;
        if (abs(dx) != abs(dy))
            return false;

        int squaresInBetween = abs(dx) - 1;
        int xRichting = dx / abs(dx);
        int yRichting = dx / abs(dy);
        for (int i = 1; i <= squaresInBetween; i++)
        {
            int newX = bishopX + i * xRichting;
            int newY = bishopY + i * yRichting;
            if (game->GetPiece(newX, newY) != nullptr)
                return false;
        }

        return true;
    }

    PieceType Bishop::GetType()
    {
        return BISHOP;
    }
} // namespace Entities
