#pragma once

#include <vector>

#include "PieceType.h"
#include "Move.h"
#include "Chess.h"
#include "Player.h"
#include "Square.h"

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
        virtual PieceType GetType() = 0;
        virtual bool CanCaptureSquare(int x, int y) = 0;
        virtual void ExecuteMove(Chess *game, Move *move);

        void AppendMovesWithlinearDirections(
            Chess *game,
            const int directions[][2],
            int numberOfDirections,
            std::vector<Move *> &potentialMoves,
            int maxSteps = 0);
        virtual ~Piece() {}
    };

} // namespace Entities