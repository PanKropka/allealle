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
int det(Vertex *x,Vertex *y,Vertex *z)
{
	return(	x->point->x * y->point->y +
		y->point->x * z->point->y + 
		z->point->x * x->point->y - 
		z->point->x * y->point->y - 
		x->point->x * z->point->y - 
		y->point->x * x->point->y
		);
}

bool isPartOf(Vertex *x,Vertex *y,Vertex *z){


	if (det(x,y,z) != 0) 
		return false; 
	else
	{
		if ((std::min(x->point->x, y->point->x) <= z->point->x) && 
			(z->point->x <= std::max(x->point->x,y->point->x)) && 
			(std::min(x->point->y, y->point->y) <= z->point->y) &&
			(z->point->y <= std::max(x->point->y,y->point->y)))
			return true; 
		else
			return false;
	}

}
bool doesEdgesIntersect(Edge * first, Edge * second){

	if (isPartOf(first->beg,first->end,second->beg) == true ) 
		return true; 
	else if (isPartOf(first->beg,first->end,second ->end) == true)
		return true;
	else if (isPartOf(second->beg,second ->end,first->beg) == true)
		return true;
	else if (isPartOf(second->beg,second ->end,first->end) == true)
		return true;
	else if ((det(first->beg,first->end,second->beg))*(det(first->beg,first->end,second ->end)) >= 0)
		return false;
	else if ((det(second->beg,second ->end,first->beg))*(det(second->beg,second ->end,first->end)) >= 0) 
		return false;
	else 
		return true;


}


std::vector<Vertex * > graf;
std::vector< Point* > v;
std::vector< Point* > points;
std::vector<Edge *>  mst;
std::vector<Edge *>  result;
std::vector<Edge *> fromIntersecting;

void init2D(float r, float g, float b)
{
	glClearColor(r,g,b,0.0);  
	glEnable( GL_LINE_SMOOTH );
	glEnable( GL_POLYGON_SMOOTH );
	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (-30, 200.0, -30, 150.0);
}



const int MULTIPLY = 1;
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0,1.0);



//	glLineWidth (3);
	for(int i = 0; i < result.size(); i++){
		Edge *temp = result.at(i);
		if(temp->intersect)
			glColor3f(1.0, 1.0,0.0);
		else
			glColor3f(1.0, 1.0,1.0);
		glBegin(GL_LINES);
		glVertex2i(temp->beg->point->x * MULTIPLY,temp->beg->point->y * MULTIPLY);
		glVertex2i(temp->end->point->x * MULTIPLY,temp->end->point->y * MULTIPLY);
		glEnd();	
	}
//	glPointSize(4);
	glColor3f(1.0, 0, 0);
	glBegin(GL_POINTS);
	int test = v.size();
	for(int i = 0; i < points.size(); i++){
		Point *temp = points.at(i);

		glVertex2i(temp->x * MULTIPLY,temp->y * MULTIPLY);


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
void clearVertexEdges(Edge* e, std::vector<Edge*> * v, int *i){
	Edge * shortes = e;

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
				removeFromVector(v, temp);

				if(vertexToClean->edges.size() == 0 && std::find(graf.begin(), graf.end(), vertexToClean) == graf.end()){
					graf.push_back(vertexToClean);
				}
				--(*i) ;
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
				removeFromVector(v, temp);
				if(vertexToClean->edges.size() == 0 && std::find(graf.begin(), graf.end(), vertexToClean) == graf.end()){
					graf.push_back(vertexToClean);
				}
				--(*i);
			}
		}


	}
}



int main(int argc,char *argv[]){
	std::srand ( unsigned ( std::time(0) ) );


	std::string option;
	std::cin >>  option;


	if(option == "1"){

		for(int i = 0; i < 100; ){
			bool conflict = false;
			Point * tmp = new Point( (std::rand()%200 - 1) - 10, (std::rand()%200) - 10);
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

	std::cout << "Poczatek " << std::endl;
	while(result.size() != vertNum && graf.size() != 0){
std::cout << "Obieg  " << counter << std::endl;


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

		//dodanie do vektora odcinkow ktore sie przecinaly
		for(int i = 0; i< fromIntersecting.size();++i){
			mst.push_back(fromIntersecting.at(i));
		}

		fromIntersecting.clear();


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
		for(int i = 0; i< mst.size();++i){
			bool doesIntersect = false;
			if(counter > 0){
				for(int a = 0; a< result.size(); ++a){
					Edge* temp1 = mst.at(i);
					Edge* temp2 = result.at(a);
					if(temp1 != temp2){
						if(doesEdgesIntersect(temp1, temp2)){
							temp1->intersect = true;
							temp2->intersect = true;
							doesIntersect = true;

							removeFromVector(&temp1->beg->edges, temp1);
							removeFromVector(&temp1->end->edges, temp1);
							removeFromVector(&temp2->beg->edges, temp2);
							removeFromVector(&temp2->end->edges, temp2);

							Edge * first = new Edge();
							Edge * second = new Edge();

							int iter = 0;
							do{
								iter = std::rand()%2;
								switch(iter){

								case 1: 
									first->beg = temp2->beg;
									first->end = temp1->beg;
									second->beg = temp1->end;
									second->end = temp2->end;
									break;
								case 0:
									first->beg = temp2->beg;
									first->end = temp1->end;
									second->beg = temp1->beg;
									second->end = temp2->end;
									break;

								}

								
							}while(doesEdgesIntersect(first,second));

							mst.push_back(first);
							mst.push_back(second);

							removeFromVector(&result, temp2);

							break;
						}
					}

				}

			}
			if(!doesIntersect){
				result.push_back(mst.at(i));
			}
		}
		mst.clear();
	}

	glutInit(&argc,argv);

	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (1050, 1050);
	glutInitWindowPosition (100, 0);
	glutCreateWindow ("AAL");
	init2D(0.0,0.0,0.0);
	glutDisplayFunc(display);
	glutMainLoop();
	system("Pause");
	return 0;
}

