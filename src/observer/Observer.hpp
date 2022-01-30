//
// Created by Krzysiek on 30/01/2022.
//

#ifndef HELLOSFML_OBSERVER_HPP
#define HELLOSFML_OBSERVER_HPP

#include "EventType.hpp"

class Observer
{
public:
	virtual void reactToEvent(EventType type, int data) = 0;
};

#endif //HELLOSFML_OBSERVER_HPP