//
// Created by Krzysiek on 31/01/2022.
//

#include "Difficulty.hpp"

Difficulty::Difficulty(float* moveTime) :
		moveTime(moveTime)
{
	this->baseMoveTime = *moveTime;
}

void Difficulty::reactToEvent(EventType type, int data)
{
	switch (type)
	{
		case RowsCleared:
			difficulty += data;

			float moveTime = baseMoveTime;

			for (int i = 0; i < difficulty; i++)
			{
				moveTime -= moveTime / (float) 10;
			}
			*this->moveTime = moveTime;
			break;
	}
}

int Difficulty::getDifficulty()
{
	return this->difficulty;
}


