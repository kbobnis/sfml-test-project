//
// Created by Krzysiek on 30/01/2022.
//

#ifndef HELLOSFML_PIECE_H
#define HELLOSFML_PIECE_H

#include "Board.h";

enum PieceType
{
	I, J, L, O, S, T, Z
};

class Piece
{
private:
public:
	PieceType type;
	std::vector<Pair> cellPositions;
	Pair rotationPoint;
	int howManyRotations;

	Piece(PieceType type, std::vector<Pair> cellPositions, Pair rotationPoint, int howManyRotations) :
			type(type),
			cellPositions(cellPositions),
			rotationPoint(rotationPoint),
			howManyRotations(howManyRotations)
	{

	}
};

#endif //HELLOSFML_PIECE_H
