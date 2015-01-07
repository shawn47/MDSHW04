#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include <vector>
using namespace std;

class Vertex
{
public:
	string id;
	int* termV;
	int termVLen;
	string label;
	Vertex();
	~Vertex();
	void initVertex(int len);
	string getId();
	void setId(string id);
	int* getTermV();
	int Vertex::getTermVLen();
	void setTermV(int* termV);
	string getLabel();
	void setLabel(string label);
};

#endif