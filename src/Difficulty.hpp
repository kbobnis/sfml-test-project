//
// Created by Krzysiek on 31/01/2022.
//

#ifndef HELLOSFML_DIFFICULTY_HPP
#define HELLOSFML_DIFFICULTY_HPP


#include "observer/Observer.hpp"

class Difficulty : public Observer
{
	float* moveTime;
	float baseMoveTime;
	int difficulty = 0;

public:
	Difficulty(float* moveTime);

	void reactToEvent(EventType type, int data) override;

	int getDifficulty();
};


#endif //HELLOSFML_DIFFICULTY_HPP
