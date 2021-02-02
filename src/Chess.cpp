#include <iostream>
#include <cstring>
#include <vector>

#include "Chess.h"
#include "Pieces\King.h"
#include "PieceType.h"
#include "Piece.h"
#include "PieceFactory.h"

using namespace Factories;

namespace Entities
{
    Chess::Chess(int width, int height, Player currentPlayer)
    {
        this->currentPlayer = currentPlayer;
        this->width = width;
        this->height = height;

        this->currentRound = 1;
        board = new Piece *[width * height];
        memset(board, 0, sizeof(board[0]) * width * height);
    }

    Chess::~Chess()
    {
        for (int i = 0; i < 2; i++)
        {
            while (numberOfPieces[i] > 0)
            {
                RemovePiece(pieces[i][0]);
            }
        }
        delete[] board;
    }

    void Chess::AppendMoves(std::vector<Move *> &moves)
    {
        int playerIndex = GetPlayerIndex(currentPlayer);
        for (int i = 0; i < numberOfPieces[playerIndex]; i++)
        {
            pieces[playerIndex][i]->AppendMoves(this, moves);
        }
    }

    bool Chess::CanPlayerCaptureSquare(Player player, int x, int y)
    {
        int playerIndex = GetPlayerIndex(player);
        for (int i = 0; i < numberOfPieces[playerIndex]; i++)
        {
            if (pieces[playerIndex][i]->CanPieceCaptureSquare(x, y, this))
                return true;
        }
        return false;
    }

    Player Chess::GetOpponent(Player player)
    {
        return player == WHITE ? BLACK : WHITE;
    }

    int Chess::GetPlayerIndex(Player player)
    {
        return player == WHITE ? 0 : 1;
    }

    void Chess::PrintBoard()
    {
        for (int i = 0; i < width; i++)
            std::cout << "-";
        std::cout << "--" << std::endl;

        for (int y = height - 1; y >= 0; y--)
        {
            std::cout << "|";
            for (int x = 0; x < width; x++)
            {
                char letter;
                Piece *piece = GetPiece(x, y);
                if (piece == nullptr)
                {
                    letter = ' ';
                }
                else
                {
                    letter = piece->GetType();
                }
                std::cout << letter;
            }
            std::cout << "|" << std::endl;
        }

        for (int i = 0; i < width; i++)
            std::cout << "-";
        std::cout << "--" << std::endl;
    }

    int Chess::GetCurrentRound()
    {
        return currentRound;
    }

    bool Chess::IsSquareOusideBounds(int x, int y)
    {
        return 0 > x || x >= width || 0 > y || y >= height;
    }

    bool Chess::IsSquareFree(int x, int y)
    {
        return !IsSquareOusideBounds(x, y) && GetPiece(x, y) == nullptr;
    }

    Piece *Chess::GetPiece(int x, int y)
    {
        return board[x + y * width];
    }

    void Chess::SetPiece(Piece *piece, int x, int y)
    {
        board[x + y * width] = piece;
    }

    void Chess::AddPiece(Player player, PieceType pieceType, int x, int y)
    {
        int playerIndex = GetPlayerIndex(player);
        Piece **newPieces = new Piece *[numberOfPieces[playerIndex] + 1];

        for (int i = 0; i < numberOfPieces[playerIndex]; i++)
        {
            newPieces[i] = pieces[playerIndex][i];
        }

        if (pieces[playerIndex] != NULL)
        {
            delete pieces[playerIndex];
        }
        pieces[playerIndex] = newPieces;

        Piece *piece = PieceFactory::CreatePiece(player, pieceType, x, y, this);
        SetPiece(piece, x, y);

        int newPieceIndex = numberOfPieces[playerIndex]++;
        pieces[playerIndex][newPieceIndex] = piece;
    }

    void Chess::RemovePiece(Piece *piece)
    {
        int playerIndex = GetPlayerIndex(piece->player);
        int newNumberOfPieces = numberOfPieces[playerIndex] - 1;
        Piece **newPieces = newNumberOfPieces > 0 ? new Piece *[newNumberOfPieces] : NULL;

        int pieceCounter = 0;
        for (int i = 0; i < numberOfPieces[playerIndex]; i++)
        {
            if (pieces[playerIndex][i]->x == piece->x &&
                pieces[playerIndex][i]->y == piece->y)
            {
                SetPiece(nullptr, piece->x, piece->y);
                continue;
            }

            newPieces[pieceCounter++] = pieces[playerIndex][i];
        }

        delete piece;
        delete pieces[playerIndex];
        pieces[playerIndex] = newPieces;
        numberOfPieces[playerIndex]--;
    }

    void Chess::ExecuteMove(Move *move)
    {
        move->piece->ExecuteMove(this, move);

        currentPlayer = GetOpponent(currentPlayer);
        currentRound++;
    }
} // namespace Entities