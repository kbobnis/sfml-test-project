//
// Created by Krzysiek on 30/01/2022.
//

#include "Subject.hpp"


void Subject::notify(EventType eventType, int data)
{
	for (Observer* obs: this->observers)
	{
		obs->reactToEvent(eventType, data);
	}
}

void Subject::registerObserver(Observer* observer)
{
	this->observers.push_back(observer);
}

