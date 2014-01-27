#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <math.h>
#include <glut.h>	
#include <ctime>  
#include <iterator> 
#include <fstream>
#include <string>
#include "Point.h"
#include "Vertex.h"
#include "Edge.h"


void printPoint (Point p) {  // function:
	std::cout << "x: " << p.x << "\ty:" << p.y << std::endl;
}



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


std::vector<Vertex * > graf;
std::vector< Point* > v;
std::vector< Point* > points;
std::vector<Edge *>  mst;
void init2D(float r, float g, float b)
{
	glClearColor(r,g,b,0.0);  
	glEnable( GL_LINE_SMOOTH );
	glEnable( GL_POLYGON_SMOOTH );
	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (-30, 200.0, -30, 150.0);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0,1.0);



	glLineWidth (3);
	for(int i = 0; i < mst.size(); i++){
		Edge *temp = mst.at(i);
		glBegin(GL_LINES);
		glVertex2i(temp->beg->point->x * 10,temp->beg->point->y * 10);
		glVertex2i(temp->end->point->x * 10,temp->end->point->y * 10);
		glEnd();	
	}
	glPointSize(4);
	glColor3f(1.0, 0, 0);
	glBegin(GL_POINTS);
	int test = v.size();
	for(int i = 0; i < points.size(); i++){
		Point *temp = points.at(i);

		glVertex2i(temp->x * 10,temp->y * 10);


	}
	glEnd();	
	glFlush();
}

void removeFromVector(std::vector<Edge *> *v, Edge * e){


	for(std::vector<Edge * >::iterator it = v->begin(); it != v->end(); ++it){	
		if( (*it) == e ){
			v->erase(it);
			break;
		}
	}

}


int main(int argc,char *argv[]){
	std::srand ( unsigned ( std::time(0) ) );
	//v.push_back(new Point(1, 2));
	//v.push_back(new Point(1,1));
	//v.push_back(new Point(4, 3));
	//v.push_back(new Point(4,2));
	//v.push_back(new Point(6, 3));
	//v.push_back(new Point(-1,8));
	//v.push_back(new Point(0, 0));

	//v.push_back(new Point(7, 4));
	//v.push_back(new Point(2,2));

	//v.push_back(new Point(1, 2));
	//v.push_back(new Point(1,1));
	//v.push_back(new Point(4, 3));
	//v.push_back(new Point(4,2));
	//v.push_back(new Point(6, 3));
	//v.push_back(new Point(-1,8));
	//v.push_back(new Point(0, 0));
	//v.push_back(new Point(7, 4));
	//v.push_back(new Point(2,2));
	//v.push_back(new Point(7, 3));
	//v.push_back(new Point(2,14));
	//v.push_back(new Point(9, 3));
	//v.push_back(new Point(4,-1));
	//v.push_back(new Point(5, 5));
	//v.push_back(new Point(-2,3));
	//v.push_back(new Point(-1, -1));

	std::string option;
	std::cin >>  option;


	if(option == "1"){

		for(int i = 0; i < 30; ){
			bool conflict = false;
			Point * tmp = new Point( (std::rand()%15), (std::rand()%15));
			for(int j = 0; j < v.size(); j++){
				if((v.at(j)->x == tmp->x) &&( v.at(j)->y == tmp->y)){
					conflict = true;
					break;
				}
			}
			if(!conflict){
				v.push_back( tmp);
				++i;
			}
		}

		std::ofstream myfile ("example.txt");
		if (myfile.is_open())
		{

			for(int i = 0; i< v.size(); ++i){
				myfile << v.at(i)->x << "," <<  v.at(i)->y << "\n";
			}

			myfile.close();
		}
		else
			std::cout << "Unable to open file";


	}else if(option == "2")
	{

		std::ifstream myfile ("example.txt");
		if(myfile.is_open()){

			while(!myfile.eof()){
				std::string x,y;
				std::getline(myfile, x, ',');
				std::getline(myfile, y, '\n');
				v.push_back(new Point(atoi(x.c_str()), atoi(y.c_str())));
			}

		}else 
			std::cout << "Unable to open file";
		v.pop_back();
	}



	points = v;

	std::sort(v.begin(), v.end(), pointSort);

	int size = v.size();
	int num  = ((size-1)*size)/2;

	int vertNum = size/2;
	int counter = 0;
	std::vector<Vertex * > graf;

	for(int i = 0; i < size; ++i){
		Vertex* nowy = new Vertex();
		nowy->point = v.at(i);
		graf.push_back(nowy);
	}
	while(mst.size() != vertNum && graf.size() != 0){



		for(int i = 0; i < graf.size(); ++i){
			Vertex * current = graf.at(i);
			for(int j = i+1; j < graf.size(); ++j){
				Edge *kraw = new Edge();
				kraw->beg = graf.at(i);
				kraw->end = graf.at(j);
				kraw->odleglosc = kraw->beg->point->odleglosc(kraw->end->point);
				kraw->beg->edges.push_back(kraw);
				kraw->end->edges.push_back(kraw);
			}	
		}

		std::vector<Edge *>  primList;
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

		//Oczyszczenie punktów do kolejnej iteracji.
		graf.clear();



		//odcinki
		for(int i = mst.size() - 1; i>= 0; --i){
			Edge * shortes = mst.at(i);
			Vertex * shortestBeg = shortes->beg;
			Vertex * shortestEnd = shortes->end;

			if(shortestBeg->edges.size() >1 || shortestEnd->edges.size() > 1){

				for(std::vector<Edge * >::iterator it = shortestBeg->edges.begin(); it != shortestBeg->edges.end(); ++it){	

					Edge  *temp = *it;
					if(temp != shortes){
						Vertex * vertexToClean;
						if(temp->beg == shortestBeg)
							vertexToClean = temp->end;
						else
							vertexToClean = temp->beg;

						removeFromVector(&(vertexToClean->edges), temp);
						removeFromVector(&mst, temp);

						if(vertexToClean->edges.size() == 0 && std::find(graf.begin(), graf.end(), vertexToClean) == graf.end()){
							graf.push_back(vertexToClean);
						}
						--i;
					}
				}
				for(std::vector<Edge * >::iterator it = shortestEnd->edges.begin(); it != shortestEnd->edges.end(); ++it){	

					Edge  *temp = *it;
					if(temp != shortes){
						Vertex * vertexToClean;
						if(temp->beg == shortestEnd)
							vertexToClean = temp->end;
						else
							vertexToClean = temp->beg;

						removeFromVector(&(vertexToClean->edges), temp);
						removeFromVector(&mst, temp);
						if(vertexToClean->edges.size() == 0 && std::find(graf.begin(), graf.end(), vertexToClean) == graf.end()){
							graf.push_back(vertexToClean);
						}
						--i;
					}
				}
			}

		}
		counter++;
	}
	//Edge * shortes = ((mst.back()));
	//Vertex * shortestBeg = shortes->beg;
	//Vertex * shortestEnd = shortes->end;
	//for(std::vector<Edge * >::iterator it = shortestBeg->edges.begin(); it != shortestBeg->edges.end(); ++it){	

	//	Edge  *temp = *it;
	//	if(temp != shortes){
	//		Vertex * vertexToClean;
	//		if(temp->beg == shortestBeg)
	//			vertexToClean = temp->end;
	//		else
	//			vertexToClean = temp->beg;

	//		removeFromVector(&(vertexToClean->edges), temp);
	//		removeFromVector(&mst, temp);
	//	}
	//}





	glutInit(&argc,argv);

	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (1050, 1050);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("AAL");
	init2D(0.0,0.0,0.0);
	glutDisplayFunc(display);
	glutMainLoop();
	system("Pause");
	return 0;
}

