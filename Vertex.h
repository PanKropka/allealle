#pragma once
#ifndef VERTEX_H
#define VERTEX_H
#include <vector>
#include "Edge.h"
#include "Point.h"

class Vertex { 
public:
	Point *point;
	std::vector<Edge *> edges;
};

#endif VERTEX_H