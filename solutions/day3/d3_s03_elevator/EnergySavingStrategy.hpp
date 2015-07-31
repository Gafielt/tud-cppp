#ifndef ENERGYSAVINGSTRATEGY_HPP_
#define ENERGYSAVINGSTRATEGY_HPP_

#include "ElevatorStrategy.hpp"
#include <list>

/**
 * Finds a strategy for minimizing the energy by performing backtracking
 */
class EnergySavingStrategy: public ElevatorStrategy {
public:
	virtual ~EnergySavingStrategy();
	virtual void createPlan(const Building*);
	virtual int nextFloor();
private:
	/** 
	 * Return a list with potential floors to find next. 
	 * Potential floors are floors which either contain people or are set as destination floor by people in elevator.
	 */
	std::list<int> getPotentiaNextlFloors(const Building& currentBuilding);
	/**
	 * Backtracks a possible solution.
	 * 
	 * @param currentBuilding current configuration
	 * @param tmpPlan: list for floor targets performed before
	 * @param maxEnergy: current max energy. Can be overwritten if better plan was found
	 */
	void backtrack(const Building& currentBuilding, std::list<int>& tmpPlan, int& maxEngery);
	/** current plan */
	std::list<int> plan;
};

#endif /* ENERGYSAVINGSTRATEGY_HPP_ */
