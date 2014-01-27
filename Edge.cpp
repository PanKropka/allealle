#include "Edge.h"

bool Edge::operator>(const Edge e2){

	if(this->odleglosc > e2.odleglosc)
		return true;
	return false;
}
