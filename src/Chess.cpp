#include <iostream>
#include <cstring>
#include <vector>

#include "Chess.h"
#include "Score.h"
#include "Pieces\King.h"
#include "PieceType.h"
#include "Piece.h"
#include "PieceFactory.h"

using namespace Factories;

namespace Entities
{
    Score *Chess::CalcBestMove()
    {
        std::vector<Move *> moves;
        AppendMoves(moves);

        Move *bestMove;
        Score *bestScore = new Score();

        for (int i = 0; i < (int)moves.size(); i++)
        {
            Chess *newBoard = Clone();
            newBoard->ExecuteMove(moves[i]);
        }

        ClearMoves(moves);

        return bestScore;
    }

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

    Chess *Chess::Clone()
    {
        Chess *clone = new Chess(width, height, currentPlayer);
        clone->currentRound = currentRound;

        for (int player = 0; player < 2; player++)
        {
            clone->pieces[player] = new Piece *[numberOfPieces[player]];
            for (int i = 0; i < numberOfPieces[player]; i++)
            {
                Piece *piece = pieces[player][i];
                Piece *newPiece = PieceFactory::CreatePiece((Player)player, piece->GetType(), piece->x, piece->y, this);
                clone->pieces[player][i] = newPiece;
                SetPiece(newPiece, newPiece->x, newPiece->y);
            }
        }

        return clone;
    }

    void Chess::AppendMoves(std::vector<Move *> &moves)
    {
        for (int i = 0; i < numberOfPieces[currentPlayer]; i++)
        {
            pieces[currentPlayer][i]->AppendMoves(this, moves);
        }
    }

    bool Chess::CanPlayerCaptureSquare(Player player, int x, int y)
    {
        for (int i = 0; i < numberOfPieces[player]; i++)
        {
            if (pieces[player][i]->CanPieceCaptureSquare(x, y, this))
                return true;
        }
        return false;
    }

    Player Chess::GetOpponent(Player player)
    {
        return player == WHITE ? BLACK : WHITE;
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
        std::cout << "--" << std::endl
                  << "Round: " << currentRound << std::endl;
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

    void Chess::Walk(Move *move)
    {
        Piece *piece = GetPiece(move->newX, move->newY);
        if (piece != nullptr)
        {
            RemovePiece(piece);
        }

        piece = GetPiece(move->x, move->y);
        SetPiece(piece, move->newX, move->newY);
        SetPiece(nullptr, move->x, move->y);

        piece->x = move->newX;
        piece->y = move->newY;
    }

    void Chess::SetPiece(Piece *piece, int x, int y)
    {
        board[x + y * width] = piece;
    }

    void Chess::AddPiece(Player player, PieceType pieceType, int x, int y)
    {
        Piece **newPieces = new Piece *[numberOfPieces[player] + 1];

        for (int i = 0; i < numberOfPieces[player]; i++)
        {
            newPieces[i] = pieces[player][i];
        }

        if (pieces[player] != NULL)
        {
            delete pieces[player];
        }
        pieces[player] = newPieces;

        Piece *piece = PieceFactory::CreatePiece(player, pieceType, x, y, this);
        SetPiece(piece, x, y);

        int newPieceIndex = numberOfPieces[player]++;
        pieces[player][newPieceIndex] = piece;
    }

    void Chess::RemovePiece(Piece *piece)
    {
        int player = piece->player;
        int newNumberOfPieces = numberOfPieces[player] - 1;
        Piece **newPieces = newNumberOfPieces > 0 ? new Piece *[newNumberOfPieces] : NULL;

        int pieceCounter = 0;
        for (int i = 0; i < numberOfPieces[player]; i++)
        {
            if (pieces[player][i]->x == piece->x &&
                pieces[player][i]->y == piece->y)
            {
                SetPiece(nullptr, piece->x, piece->y);
                continue;
            }

            newPieces[pieceCounter++] = pieces[player][i];
        }

        delete piece;
        delete pieces[player];
        pieces[player] = newPieces;
        numberOfPieces[player]--;
    }

    int Chess::GetNumberOfMoves(Player player)
    {
        std::vector<Move *> moves;
        for (int i = 0; i < numberOfPieces[player]; i++)
        {
            pieces[player][i]->AppendMoves(this, moves);
        }
        return moves.size();
    }

    void Chess::ExecuteMove(Move *move)
    {
        Piece *piece = GetPiece(move->x, move->y);
        piece->ExecuteMove(this, move);

        currentPlayer = GetOpponent(currentPlayer);
        currentRound++;
    }

    void Chess::ClearMoves(std::vector<Move *> &moves)
    {
        for (int i = 0; i < (int)moves.size(); i++)
        {
            delete moves[i];
        }
        moves.clear();
    }
} // namespace Entities