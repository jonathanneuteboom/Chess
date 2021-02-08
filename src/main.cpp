#include <iostream>
#include <vector>
#include "Chess.h"
#include "Score.h"
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
	string white = "   P K";
	string black = " N P";
	Factories::BoardFactory::CreateBoard(&chess, white, black);

	

	
	Score * asd = chess.CalcBestMove();
	chess.PrintBoard();


	

	
	return 0;
}
