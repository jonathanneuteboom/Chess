#include <iostream>
#include <cstring>
#include <vector>

#include "Chess.h"
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

        this->numberOfSquares = width * height;
        board = new Piece *[width * height];
        memset(board, 0, sizeof(board[0]) * width * height);
    }

    Chess::~Chess()
    {
        for (int i = 0; i < numberOfSquares; i++)
        {
            if (board[i] == nullptr)
                continue;

            delete board[i];
        }
        delete board;
    }

    void Chess::AppendMoves(std::vector<Move *> &moves)
    {
        int playerIndex = GetPlayerIndex(currentPlayer);
        for (int i = 0; i < numberOfPieces[playerIndex]; i++)
        {
            pieces[playerIndex][i]->AppendMoves(this, moves);
        }
    }

    int Chess::GetNumberOfPieces(char pieces[])
    {
        if (pieces == NULL)
            return 0;

        int number = 0;
        for (char *letter = pieces; *letter != '\0'; letter++)
        {
            if (*letter == ' ' || *letter == '-')
                continue;

            number++;
        }
        return number;
    }

    void Chess::SetPieces(char characters[], Player player)
    {
        if (characters == NULL)
            return;

        int playerIndex = GetPlayerIndex(player);
        numberOfPieces[playerIndex] = GetNumberOfPieces(characters);
        pieces[playerIndex] = new Piece *[numberOfPieces[playerIndex]];

        int pieceNumber = 0;
        int currentField = player == WHITE ? 0 : numberOfSquares - 1;
        int direction = player == WHITE ? 1 : -1;

        for (char *letter = characters; *letter != '\0'; letter++)
        {
            if (*letter == ' ')
            {
                currentField += direction;
                continue;
            }
            if (*letter == '-')
            {
                currentField += direction * this->width;
                continue;
            }

            int x = currentField % this->width;
            int y = currentField / this->width;

            Piece *piece = PieceFactory::CreatePiece(player, *letter, x, y, this);

            int playerIndex = GetPlayerIndex(player);
            pieces[playerIndex][pieceNumber++] = piece;
            SetPiece(piece, x, y);

            currentField += direction;
        }
    }

    bool Chess::CanPlayerHitSquare(Player player, int x, int y)
    {
        int playerIndex = GetPlayerIndex(player);
        for (int i = 0; i < numberOfPieces[playerIndex]; i++)
        {
            if (pieces[playerIndex][i]->CanCaptureSquare(x, y, this))
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

    void Chess::InitBoard(char whitePieces[], char blackPieces[])
    {
        SetPieces(whitePieces, WHITE);
        SetPieces(blackPieces, BLACK);

        int whitePlayer = GetPlayerIndex(WHITE);
        int blackPlayer = GetPlayerIndex(BLACK);
        if (numberOfPieces[whitePlayer] + numberOfPieces[blackPlayer] > numberOfSquares)
        {
            throw "te veel stukken";
        }
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
        return GetPiece(x, y) == nullptr;
    }

    Piece *Chess::GetPiece(int x, int y)
    {
        if (IsSquareOusideBounds(x, y))
            return nullptr;

        return board[x + y * width];
    }

    void Chess::SetPiece(Piece *piece, int x, int y)
    {
        board[x + y * width] = piece;
    }

    void Chess::RemovePiece(int x, int y)
    {
        Piece *piece = GetPiece(x, y);
        int playerIndex = GetPlayerIndex(piece->player);
        Piece **newPieces = new Piece *[numberOfPieces[playerIndex] - 1];

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

    void Chess::RemovePiece(Piece *piece)
    {
        RemovePiece(piece->x, piece->y);
    }

    void Chess::ExecuteMove(Move *move)
    {
        move->piece->ExecuteMove(this, move);
        if (move->moveType == QUEEN_PROMOTION ||
            move->moveType == ROOK_PROMOTION ||
            move->moveType == KNIGHT_PROMOTION ||
            move->moveType == QUEEN_PROMOTION)
        {
            RemovePiece(move->piece);
        }

        currentPlayer = GetOpponent(currentPlayer);
        currentRound++;
    }

    void Chess::AddPiece(Player player, PieceType pieceType, int x, int y)
    {
        int playerIndex = GetPlayerIndex(player);
        Piece **newPieces = new Piece *[numberOfPieces[playerIndex] + 1];

        for (int i = 0; i < numberOfPieces[playerIndex]; i++)
        {
            newPieces[i] = pieces[playerIndex][i];
        }

        Piece *piece = PieceFactory::CreatePiece(player, pieceType, x, y, this);
        pieces[playerIndex][++numberOfPieces[playerIndex]] = piece;
    }

    void Chess::MovePiece(Move *move)
    {
        SetPiece(nullptr, move->piece->x, move->piece->y);
        SetPiece(move->piece, move->newSquare->x, move->newSquare->y);
        move->piece->x = move->newSquare->x;
        move->piece->y = move->newSquare->y;
    }
} // namespace Entities