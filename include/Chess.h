#pragma once

#include "Piece.h"
#include "Move.h"
#include "Score.h"
#include "MoveType.h"
#include "PieceType.h"
#include "Player.h"

namespace Entities
{
    class Piece;
    class Move;
    class Score;
    class Chess
    {
    public:
        Piece **board;
        int width;
        int height;
        int currentRound;
        Player currentPlayer;

        Piece **pieces[2] = {NULL, NULL};
        int numberOfPieces[2] = {0, 0};

        Chess(int width, int height, Player currentPlayer = WHITE);
        ~Chess();

        Chess *Clone();

        void PrintBoard();
        int GetCurrentRound();

        bool IsSquareOusideBounds(int x, int y);
        bool IsSquareFree(int x, int y);

        Piece *GetPiece(int x, int y);
        void SetPiece(Piece *piece, int x, int y);
        void AddPiece(Player player, PieceType pieceType, int x, int y);
        void RemovePiece(Piece *piece);
        int GetNumberOfMoves(Player player);

        void AppendMoves(std::vector<Move *> &moves);
        void ClearMoves(std::vector<Move *> &moves);
        void ExecuteMove(Move *move);
        void Walk(Move *move);
        Score* CalcBestMove();

        bool CanPlayerCaptureSquare(Player player, int x, int y);
        Player GetOpponent(Player player);
    };
} // namespace Entities