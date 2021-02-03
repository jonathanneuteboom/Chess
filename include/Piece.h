#pragma once

#include <vector>

#include "PieceType.h"
#include "Move.h"
#include "Chess.h"
#include "Player.h"

namespace Entities
{
    class Chess;
    class Piece
    {
    public:
        Player player;
        int x, y;

        Piece(int x, int y, Player player);
        virtual void AppendMoves(Chess *game, std::vector<Move *> &potentialMoves) = 0;
        virtual bool CanPieceCaptureSquare(int x, int y, Chess *game) = 0;
        virtual void ExecuteMove(Chess *game, Move *move) = 0;
        virtual PieceType GetType() = 0;

        void AppendMovesWithlinearDirections(
            Chess *game,
            const int directions[][2],
            int numberOfDirections,
            std::vector<Move *> &potentialMoves);
        virtual ~Piece() {}
    };

} // namespace Entities