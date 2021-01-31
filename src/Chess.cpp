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
        pieces[playerIndex] = new Piece *[numberOfPieces[playerIndex]];

        int pieceCounter = 0;
        int currentField = player == WHITE ? 0 : width * height - 1;
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
            AddPiece(player, (PieceType)*letter, x, y);

            currentField += direction;
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

    void Chess::InitBoard(char whitePieces[], char blackPieces[])
    {
        SetPieces(whitePieces, WHITE);
        SetPieces(blackPieces, BLACK);

        int whitePlayer = GetPlayerIndex(WHITE);
        int blackPlayer = GetPlayerIndex(BLACK);
        int numberOfSquares = width * height;
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
        return !IsSquareOusideBounds(x, y) && GetPiece(x, y) == nullptr;
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

    void Chess::AddPiece(Player player, PieceType pieceType, int x, int y)
    {
        int playerIndex = GetPlayerIndex(player);
        Piece **newPieces = new Piece *[numberOfPieces[playerIndex] + 1];

        for (int i = 0; i < numberOfPieces[playerIndex]; i++)
        {
            newPieces[i] = pieces[playerIndex][i];
        }

        Piece *piece = PieceFactory::CreatePiece(player, pieceType, x, y, this);
        SetPiece(piece, x, y);
        int newPieceIndex = numberOfPieces[playerIndex]++;
        pieces[playerIndex][newPieceIndex] = piece;
    }

    void Chess::MovePiece(Move *move)
    {
        move->piece->MovePiece(move);

        SetPiece(nullptr, move->piece->x, move->piece->y);
        SetPiece(move->piece, move->newSquare->x, move->newSquare->y);
        move->piece->x = move->newSquare->x;
        move->piece->y = move->newSquare->y;
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

    PieceType Chess::GetPromotedPieceType(MoveType move)
    {
        switch (move)
        {
        case QUEEN_PROMOTION:
            return QUEEN;
        case ROOK_PROMOTION:
            return ROOK;
        case KNIGHT_PROMOTION:
            return KNIGHT;
        case BISHOP_PROMOTION:
            return BISHOP;
        default:
            throw;
        }
    }

    void Chess::ExecuteMove(Move *move)
    {
        switch (move->moveType)
        {
        case WALK:
        {
            Piece *piece = GetPiece(move->newSquare->x, move->newSquare->y);
            if (piece != nullptr)
            {
                RemovePiece(piece);
            }
            MovePiece(move);
            break;
        }
        case QUEEN_PROMOTION:
        case ROOK_PROMOTION:
        case KNIGHT_PROMOTION:
        case BISHOP_PROMOTION:
        {
            PieceType newPieceType = GetPromotedPieceType(move->moveType);
            RemovePiece(move->piece);
            AddPiece(currentPlayer, newPieceType, move->newSquare->x, move->newSquare->y);
            break;
        }
        case EN_PASSANT_CAPTURE:
        {
            Piece *opposingPawn = GetPiece(move->newSquare->x, move->piece->x);
            RemovePiece(opposingPawn);
            MovePiece(move);
            break;
        }
        case KINGSIDE_CASTLE:
        {
            King *king = (King *)move->piece;
            Piece *rook = king->GetCastlingRook(KINGSIDE_CASTLE, this);
            Move rookMove = Move(rook, move->newSquare->x - 1, move->piece->y, WALK);

            MovePiece(move);
            MovePiece(&rookMove);
            break;
        }
        case QUEENSIDE_CASTLE:
        {
            King *king = (King *)move->piece;
            Piece *rook = king->GetCastlingRook(QUEENSIDE_CASTLE, this);
            Move rookMove = Move(rook, move->newSquare->x + 1, move->piece->y, WALK);

            MovePiece(move);
            MovePiece(&rookMove);
            break;
        }
        default:
            throw;
        }

        currentPlayer = GetOpponent(currentPlayer);
        currentRound++;
    }
} // namespace Entities