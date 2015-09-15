#ifndef VECTOR3_HPP_
#define VECTOR3_HPP_

#include <iostream>

class Vector3 {
public:
	Vector3();
	Vector3(double a, double b, double c);
	Vector3(const Vector3& other);
	~Vector3();
	
	Vector3 operator+(Vector3 rhs);
	Vector3 operator-(Vector3 rhs);
	double operator*(Vector3 rhs);
	
	double getA();
	double getB();
	double getC();
private:
	double a, b, c;
};

std::ostream& operator<<(std::ostream& out, Vector3 rhs);

#endif /* VECTOR3_HPP_ */
