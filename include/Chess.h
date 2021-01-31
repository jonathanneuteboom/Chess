#pragma once

#include "Piece.h"
#include "Move.h"
#include "MoveType.h"
#include "PieceType.h"
#include "Player.h"

namespace Entities
{
    class Piece;
    class Move;
    class Chess
    {
    public:
        Piece **board;
        int width;
        int height;
        int currentRound;
        Player currentPlayer;

        Piece **pieces[2];
        int numberOfPieces[2] = {0, 0};

        Chess(int width, int height, Player currentPlayer = WHITE);
        ~Chess();

        int GetNumberOfPieces(char pieces[]);
        void SetPieces(char pieces[], Player player);
        void InitBoard(char white[], char black[]);
        void PrintBoard();
        int GetLetterOfPiece(Piece *);
        int GetCurrentRound();
        bool IsSquareOusideBounds(int x, int y);
        bool IsSquareFree(int x, int y);
        Piece *GetPiece(int x, int y);
        void SetPiece(Piece *piece, int x, int y);
        void AppendMoves(std::vector<Move *> &moves);
        void ExecuteMove(Move *move);
        void AddPiece(Player player, PieceType pieceType, int x, int y);
        Piece *GetFirstPieceOfType(Player player, PieceType pieceType);
        void RemovePiece(Piece *piece);
        PieceType GetPromotedPieceType(MoveType move);
        void MovePiece(Move *move);
        int GetPlayerIndex(Player player);
        bool CanPlayerCaptureSquare(Player player, int x, int y);
        Player GetOpponent(Player player);
    };
} // namespace Entities