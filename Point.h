#pragma once
class Point {
public:
	Point(int, int);
	int x;
	int y;
	bool operator<(const Point p2);
	double odleglosc(const Point *p2);
};