#pragma once
#ifndef EDGE_H
#define EDGE_H

#include "Vertex.h"
class Edge{
public:
	Edge(){
		this->used = false;
		this->toRemove = false;
	}
	Vertex *beg;
	Vertex *end;
	double odleglosc;
	bool used;
	bool toRemove;
	bool operator>(const Edge e2);
};


#endif EDGE_H