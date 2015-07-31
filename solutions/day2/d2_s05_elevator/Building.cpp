#include "Building.hpp"

Building::Building(int numberOfFloors) {
	// add given number of floors
	while (numberOfFloors-- > 0) {
		floors.push_back(Floor());
	}
}

void Building::letPeopleIn() {
	elevator.addPeople(floors.at(elevator.getFloor()).removeAllPeople());
}

std::list<PersonPtr> Building::removeArrivedPeople() {
	return elevator.removeArrivedPeople();
}

void Building::moveElevatorToFloor(int i) {
	elevator.moveToFloor(i);
}

void Building::addWaitingPerson(int floor, PersonPtr p) {
	floors.at(floor).addWaitingPerson(p);
}

