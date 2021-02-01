#include <iostream>
#include <vector>
#include "Chess.h"
#include "Piece.h"
#include "BoardFactory.h"

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
	string white = "NQKRPPPP";
	string black = "RKQNPPPP";
	Factories::BoardFactory::CreateBoard(&chess, white, black);

	std::vector<Move *> moves;
	while (true)
	{
		moves.clear();
		chess.PrintBoard();
		chess.AppendMoves(moves);

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
