//
// Created by Krzysiek on 30/01/2022.
//

#ifndef HELLOSFML_SUBJECT_HPP
#define HELLOSFML_SUBJECT_HPP

#include "EventType.hpp"
#include <vector>
#include "Observer.hpp"

class Subject
{
private:
	std::vector<Observer*> observers;
protected:
	void notify(EventType eventType, int data);

public:
	void registerObserver(Observer* observer);
};


#endif //HELLOSFML_SUBJECT_HPP
