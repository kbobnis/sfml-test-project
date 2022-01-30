//
// Created by Krzysiek on 30/01/2022.
//

#include "Piece.hpp"

Piece::Piece(PieceType type, std::vector<Pair> cellPositions, Pair rotationPoint, int howManyRotations) :
type(type),
cellPositions(cellPositions),
rotationPoint(rotationPoint),
howManyRotations(howManyRotations)
{
	int minX = 999;
	int maxX = -1;

	for (Pair cell: cellPositions)
	{
		if (cell.x < minX)
		{
			minX = cell.x;
		}
		if (cell.x > maxX)
		{
			maxX = cell.x;
		}
	}

	length = maxX - minX + 1;
}

int Piece::GetLength()
{
	return length;
}

std::vector<Pair> Piece::GetShapeAfterRotation(int rotation) const
{
	std::vector<Pair> afterRotation;
	for (int i = 0; i < cellPositions.size(); i++)
	{
		int rotatedX = cellPositions[i].x;
		int rotatedY = cellPositions[i].y;

		///rotate 90'
		//columns' = -(rows - py) + px
		//rows' = (columns - px) + py

		for (int j = 0; j < rotation; ++j)
		{
			int tmp = rotatedX;
			rotatedX = -(rotatedY - rotationPoint.y) + rotationPoint.x;
			rotatedY = (tmp - rotationPoint.x) + rotationPoint.y;
		}

		afterRotation.push_back(Pair(rotatedX, rotatedY));
	}
	return afterRotation;
}