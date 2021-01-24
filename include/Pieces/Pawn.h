#pragma once

#include "Piece.h"
#include "Player.h"
#include "Chess.h"
#include "Move.h"
#include "PieceFactory.h"

using namespace Factories;

namespace Entities
{
    class Pawn : public Piece
    {
        bool didPawnMove = false;
        int doubleSquareMoveRound;
        Chess *game;

    public:
        Pawn(int x, int y, Player player, Chess *game, int doubleSquareMoveRound = -1);

        virtual bool CanCaptureSquare(int x, int y, Chess *game);

        virtual void AppendMoves(Chess *game, std::vector<Move *> &potentialMoves);

        virtual void ExecuteMove(Chess *game, Move *move);

        virtual PieceType GetType();
    };
} // namespace Entities