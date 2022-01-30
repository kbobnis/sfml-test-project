//
// Created by Krzysiek on 30/01/2022.
//

#ifndef HELLOSFML_PIECE_H
#define HELLOSFML_PIECE_H

#include <vector>
#include "Pair.h"

enum PieceType
{
	I, J, L, O, S, T, Z
};

class Piece
{
private:
	int length;
public:
	PieceType type;
	std::vector<Pair> cellPositions;
	Pair rotationPoint;
	int howManyRotations;

	Piece(PieceType type, std::vector<Pair> cellPositions, Pair rotationPoint, int howManyRotations) ;

	std::vector<Pair> GetShapeAfterRotation(int rotation) const;

	int GetLength();
};

#endif //HELLOSFML_PIECE_H
