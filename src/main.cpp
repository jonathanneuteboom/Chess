#include <iostream>
#include <vector>
#include "Chess.h"
#include "Piece.h"

using namespace Entities;

int leesGetal()
{
	int getal;
	std::cout << "Voer getal in" << std::endl;
	std::cin >> getal;
	return getal;
}

int main()
{
	Chess chess(4, 4);
	char white[] = "NQKRPPPP";
	char black[] = "RKQNPPPP";
	chess.InitBoard(white, black);

	std::vector<Move *> moves;
	while (true)
	{
		moves.clear();
		chess.PrintBoard();
		for (int i = 0; i < chess.numberOfPieces[chess.currentPlayer == WHITE ? 0 : 1]; i++)
		{
			chess.pieces[chess.currentPlayer == WHITE ? 0 : 1][i]->AppendMoves(&chess, moves);
		}

		for (int i = 0; i < (int)moves.size(); i++)
		{
			std::cout << i << ": ";
			moves[i]->Print();
		}

		int zet = leesGetal();
		chess.ExecuteMove(moves[zet]);
		for (int i = 0; i < (int)moves.size(); i++)
		{
			delete moves[i];
		}
	}

	return 0;
}
