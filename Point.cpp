#include "Point.h"
#include <algorithm>
#include <math.h>


Point::Point(int x, int y){
	this->x = x;
	this->y = y;
}
bool Point::operator<(const Point p2){

	if(p2.x > x)
		return true;
	else if(p2.x == x && p2.y > y)
		return true;
	else
		return false;


}

double Point::odleglosc(const Point *p2){

	return sqrt(pow(p2->y - this->y, 2) + pow(p2->x - this->x, 2));
}
