#pragma once
#include <iostream>

/**
 * @author Lets Make Games and David Wadsworth
 * 
 * generic type for keeping track of 2D objects
 */

class Vector2D
{
public:
	double x;
	double y;

	Vector2D();
	Vector2D(double x, double y);
	Vector2D(double xy);

	Vector2D& add(const Vector2D& vec);
	Vector2D& subtract(const Vector2D& vec);
	Vector2D& multiply(const Vector2D& vec);
	Vector2D& divide(const Vector2D& vec);

	friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator/=(const Vector2D& vec);

	Vector2D& operator+=(const double& vec);
	Vector2D& operator-=(const double& vec);
	Vector2D& operator*=(const double& vec);
	Vector2D& operator/=(const double &vec);
	Vector2D& operator=(const double& vec);

	friend bool operator>=(const Vector2D& v1, const Vector2D& v2);

	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);

};