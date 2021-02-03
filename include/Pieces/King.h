#pragma once

#include "Piece.h"
#include "Rook.h"

namespace Entities
{
    class King : public Piece
    {
        bool didKingMove;
        const MoveType castlingOptions[2] = {
            QUEENSIDE_CASTLE,
            KINGSIDE_CASTLE};
        const int directions[8][2] = {
            {1, 0},
            {1, -1},
            {0, -1},
            {-1, -1},
            {-1, 0},
            {-1, 1},
            {0, 1},
            {1, 1},
        };

    public:
        King(int x, int y, Player player, bool didKingMove = false);
        virtual void AppendMoves(Chess *game, std::vector<Move *> &potentialMoves);
        int GetNewKingXForCastling(MoveType moveType, Piece *rook);
        Rook *GetCastlingRook(MoveType move, Chess *game);
        bool IsCastlingPossible(MoveType move, Chess *game);
        virtual bool CanPieceCaptureSquare(int x, int y, Chess *game);
        virtual PieceType GetType();
        virtual void ExecuteMove(Chess *game, Move *move);
    };
} // namespace Entities