#pragma once
#ifndef EDGE_H
#define EDGE_H

class Vertex;
class Edge{
public:
	Edge(){
		this->used = false;
		this->toRemove = false;
		this->intersect = false;
	}
	Vertex *beg;
	Vertex *end;
	double odleglosc;
	bool used;
	bool intersect;
	bool toRemove;
	bool operator>(const Edge e2);
};


#endif EDGE_H