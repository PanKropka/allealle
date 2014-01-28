#pragma once
#ifndef VERTEX_H
#define VERTEX_H
#include <vector>

class Edge;
class Point;

class Vertex { 
public:
	Point *point;
	std::vector<Edge *> edges;
};

#endif VERTEX_H