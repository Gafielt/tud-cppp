#ifndef BUILDING_HPP_
#define BUILDING_HPP_

#include <string>
#include <sstream>

class Building {
public:
	Building(unsigned int numFloors);
	inline const std::string toString() const{
		std::stringstream output;
		output << "A building with " << this->numFloors << " floors \n";
		return output.str();
	}
private:
	unsigned int numFloors;
};

#endif
