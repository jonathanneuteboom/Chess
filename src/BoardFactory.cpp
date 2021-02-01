#include "BoardFactory.h"
#include <string>

using namespace Entities;

namespace Factories
{
    void BoardFactory::AddPieces(Chess *game, string pieces, Player player)
    {
        if (pieces.empty())
            return;

        int currentField = player == WHITE ? 0 : game->width * game->height - 1;
        int direction = player == WHITE ? 1 : -1;

        for (char const piece : pieces)
        {
            if (piece == ' ')
            {
                currentField += direction;
                continue;
            }
            if (piece == '-')
            {
                currentField += direction * game->width;
                continue;
            }

            int x = currentField % game->width;
            int y = currentField / game->width;
            Piece *pieceOfSquare = game->GetPiece(x, y);
            if (pieceOfSquare != nullptr)
                throw;

            game->AddPiece(player, (PieceType)piece, x, y);

            currentField += direction;
        }
    }

    void BoardFactory::CreateBoard(Chess *game, std::string whitePieces, std::string blackPieces)
    {
        AddPieces(game, whitePieces, WHITE);
        AddPieces(game, blackPieces, BLACK);
    }
} // namespace Factories