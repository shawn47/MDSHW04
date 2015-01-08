#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <map>
#include "Vertex.h"
#include <unordered_map>

#define TVECTOR_LENGTH 3703

using namespace std;

class Graph
{
public:
	Vertex* vertex;
	int** adj;
	int** sample;
	double** vertexTopK;
	map<string, int> vertexData;
	int K;
	int numV;
	double lamda;

	Graph();
	~Graph();

	void initialize(int numOfVertex, int K);
	
	void loadVertexInfo(int** adj, Vertex* vertex, string vertexFile, string edgeFile);
	void loadEdgeInfo(int** adj, Vertex* vertex, string vertexFile, string edgeFile);

	void getTopK(int** adj, int adjlength, Vertex* verties);
	double cosineDistance(Vertex v1, Vertex v2);
	double getLength(Vertex v);

	void simplification();
	void getNormalized(double* arr);
	double getJaccordSimilarity (list<Vertex> v1, list<Vertex> v2);
	list<Vertex> getNgbr(int index);
	void write2file();
	void writeVertexTopK2File();
	vector<vector<double>> sample2Matrix();
	void sample2file();
};
#endif