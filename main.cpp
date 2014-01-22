#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

class Point {
public:
	Point(int, int);
	int x;
	int y;
	bool operator<(const Point p2);
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
void printPoint (Point p) {  // function:
	std::cout << "x: " << p.x << "\ty:" << p.y << std::endl;
}
struct Edge{
	Point *beg;
	Point *end;
	int odleglosc;
};
struct Vertex {
	Point *p;
	std::list<Edge *> edges;
};




int main(){
	std::vector< Point* > v;
	v.push_back(new Point(1, 2));
	v.push_back(new Point(1,1));
	v.push_back(new Point(4, 3));
	v.push_back(new Point(4,2));
	v.push_back(new Point(6, 3));
	v.push_back(new Point(-1,8));
	v.push_back(new Point(0, 0));
	v.push_back(new Point(1,1));
	v.push_back(new Point(7, 4));
	v.push_back(new Point(2,2));

	int size = v.size();
	int num  = ((size-1)*size)/2;
	int counter = 0;
	std::vector<Vertex * > graf;
	for(int i = 0; i < size; ++i){

		Point *tmp =  v.at(i);
		Vertex *nowy = new Vertex();
		nowy->p = tmp;
		for(int j = i+1; j < size; ++j){
			Edge *kraw = new Edge();
			kraw->beg = v.at(i);
			kraw->end = v.at(j);
			kraw->odleglosc = 0;
			nowy->edges.push_back(kraw);
			counter++;

		}
		graf.push_back(nowy);
	}

	/*
	for_each(v.begin(), v.end(), printPoint);
	std::sort(v.begin(), v.end());
	std::cout << std::endl;
	for_each(v.begin(), v.end(), printPoint);

	*/

	system("Pause");
	return 0;
}