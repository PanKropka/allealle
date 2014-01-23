#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <math.h>

class Point {
public:
	Point(int, int);
	int x;
	int y;
	bool operator<(const Point p2);
	double odleglosc(const Point *p2);
};

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

void printPoint (Point p) {  // function:
	std::cout << "x: " << p.x << "\ty:" << p.y << std::endl;
}

class Edge;
struct Vertex;

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


bool Edge::operator>(const Edge e2){

	if(this->odleglosc > e2.odleglosc)
		return true;
	return false;
}
bool edgeSort(const Edge* one, const Edge* two)
{ //od najw do najm
	return one->odleglosc > two->odleglosc;
}

bool pointSort(const Point* one, const Point* two)
{ //od najm do najw


	if(one->x <  two->x)
		return true;
	else if(one->x == two->x && one->y < two->y)
		return true;
	else
		return false;


}

struct Vertex { 
	Point *point;
	std::vector<Edge *> edges;
};

bool sprawdzStopienPolaczonychWierzcholkow(Edge *e);



int main(){
	std::vector< Point* > v;
	v.push_back(new Point(1, 2));
	v.push_back(new Point(1,1));
	v.push_back(new Point(4, 3));
	v.push_back(new Point(4,2));
	v.push_back(new Point(6, 3));
	v.push_back(new Point(-1,8));
	v.push_back(new Point(0, 0));

	v.push_back(new Point(7, 4));
	v.push_back(new Point(2,2));

	std::sort(v.begin(), v.end(), pointSort);

	int size = v.size();
	int num  = ((size-1)*size)/2;
	int counter = 0;
	std::vector<Vertex * > graf;

	for(int i = 0; i < size; ++i){
		Vertex* nowy = new Vertex();
		nowy->point = v.at(i);
		graf.push_back(nowy);
	}

	for(int i = 0; i < size; ++i){
		Vertex * current = graf.at(i);
		for(int j = i+1; j < size; ++j){
			Edge *kraw = new Edge();
			kraw->beg = graf.at(i);
			kraw->end = graf.at(j);
			kraw->odleglosc = kraw->beg->point->odleglosc(kraw->end->point);
			kraw->beg->edges.push_back(kraw);
			kraw->end->edges.push_back(kraw);
			counter++;
		}	
	}

	std::vector<Edge *>  primList;
	std::vector<Edge *>  mst;
	std::set<Vertex *> odwiedzone; 
	Vertex *aktualny = graf.at(0);


	while(odwiedzone.size() != graf.size()){
		odwiedzone.insert(aktualny);

		for(int i = 0; i < aktualny->edges.size(); ++i){
			primList.push_back(aktualny->edges.at(i));
		}
		std::sort(primList.begin(), primList.end(), edgeSort);


		bool pocz = true;
		bool kon = true;
		do{
			pocz = true; kon = true;
			if(odwiedzone.find(primList.back()->beg) != odwiedzone.end()) pocz = false;
			if(odwiedzone.find(primList.back()->end) != odwiedzone.end()) kon = false;
			if(!pocz && !kon)
				primList.pop_back();
		}while(!pocz && !kon && primList.size() > 0);
		if(primList.size() > 0){
			//pierwszy juz odwiedzony
			if(!pocz){
				aktualny = primList.back()->end;
			}else
				aktualny = primList.back()->beg;

			mst.push_back(primList.back());
			mst.back()->used = true;
			primList.pop_back();
		}
	}

	for(int i = 0; i < graf.size(); ++i){
		int numRemoved = 0;
		int size =  graf.at(i)->edges.size();
		for(int j = 0; j < size - numRemoved; ++j){
			Edge* tmpP =graf.at(i)->edges.at(j);
			if(!tmpP->used){
				graf.at(i)->edges.erase(graf.at(i)->edges.begin() + j); //tu jest wyciek pamiêci
				numRemoved++;
				--j;
			}
		}
	}

	std::sort(mst.begin(), mst.end(), edgeSort);

	bool stop = false;

	while(!stop){
		for(int i = mst.size() - 1; i>= 0; --i){



		}
	}

	system("Pause");
	return 0;
}

bool sprawdzStopienPolaczonychWierzcholkow(Edge *e){
	bool moznaUsunacPoczatek = false;
	bool moznaUsunacKoniec = false;

	for(int j = 0; j <e->beg->edges.size(); ++j){
		if(e->beg->edges.at(j)->beg->edges.size() != 1 && 
			e->beg->edges.at(j)->end->edges.size() != 1){
				moznaUsunacPoczatek = true;
		}
	}

	for(int j = 0; j < e->end->edges.size(); ++j){
		if(e->end->edges.at(j)->beg->edges.size() != 1 && 
			e->end->edges.at(j)->end->edges.size() != 1){
				moznaUsunacKoniec = true;
		}
	}

	return false;
}