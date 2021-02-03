#include <vector>
#include <stdlib.h>

#include "Pieces\Rook.h"
#include "Piece.h"

namespace Entities
{
    Rook::Rook(int x, int y, Player player, bool didRookMove) : Piece(x, y, player)
    {
        this->didRookMove = didRookMove;
    }

    void Rook::AppendMoves(Chess *game, std::vector<Move *> &potentialMoves)
    {
        AppendMovesWithlinearDirections(game, directions, 4, potentialMoves);
    }

    bool Rook::CanPieceCaptureSquare(int x, int y, Chess *game)
    {
        return Rook::CanPieceCaptureSquare(this->x, this->y, x, y, game);
    }

    bool Rook::CanPieceCaptureSquare(int rookX, int rookY, int x, int y, Chess *game)
    {
        if (rookX == x)
        {
            if (rookY == y)
                return false;

            int yRichting = rookY < y ? 1 : -1;
            int sqauresInBetween = abs(rookY - y) - 1;
            for (int i = 1; i <= sqauresInBetween; i++)
            {
                int newY = rookY + i * yRichting;
                if (game->GetPiece(x, newY))
                    return false;
            }
            return true;
        }

        else if (rookY == y)
        {
            int xRichting = rookX < x ? 1 : -1;
            int sqauresInBetween = abs(rookX - x) - 1;
            for (int i = 1; i <= sqauresInBetween; i++)
            {
                int newX = rookX + i * xRichting;
                if (game->GetPiece(newX, y))
                    return false;
            }
            return true;
        }

        return false;
    }

    void Rook::ExecuteMove(Chess *game, Move *move)
    {
        didRookMove = true;
        Piece::ExecuteMove(game, move);
    }

    PieceType Rook::GetType()
    {
        return didRookMove ? ROOK : ROOK_CASTLE;
    }
} // namespace Entities