#include "graph.h"
#include "vertex.h"
#include "util.h"
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include <utility>
#include <queue>

typedef struct
{
    Vertex vertex;
    double sim;
} PAIR;

bool operator<(const PAIR &x, const PAIR &y)
{
    return x.sim > y.sim;
}

void Graph:: sample2file() {
	char filename[] = "small.mci";
	ofstream fout(filename);
	string s="(mclheader\nmcltypematrix\ndimensions 12x12\n)\n(mclmatrix\nbegin\n";
	fout<<s;
	
	int i = 0, j = 0;
	
	for (i = 0; i < this->numV; i++) {
		if (i > 0)
			fout<<endl;
		fout<<i<<" ";
		for (j = 0; j < this->numV; j++) {
			if (this->sample[i][j] == 1) {
				fout<<j<<" ";
			}
		}
		fout<<" \$";
	}
	fout<<endl;
	s=")";
	fout<<s;
	
	fout.close();
}

void Graph::write2file() {
	char filename[] = "E:\\作业\\现代数据库系统概论\\hw4\\618506165_6_Project4\\citeseer\\sampleEdge.bin";
	ofstream fout(filename);
	int i = 0, j = 0;
	for (i = 0; i < this->numV; i++) {
		if (i > 0)
			fout<<endl;
		for (j = 0; j < this->numV - 1; j++) {
			fout<<this->sample[i][j]<<"\t";
		}
		fout<<this->sample[i][j];
	}
	fout.close();
}

Graph::Graph(){}

Graph::~Graph(){}

vector<vector<double>> Graph::sample2Matrix() {
	vector<vector<double>> smatrix;
	for (int i = 0; i < this->numV; i++) {
		vector<double> srow;
		for (int j = 0; j < this->numV; j++) {
			srow.push_back((double)this->sample[i][j]);
		}
		smatrix.push_back(srow);
	}
	return smatrix;
}

void Graph:: initialize(int numOfVertex, int K) {
	this->K = K;
	this->numV = numOfVertex;
	this->vertex = new Vertex[numOfVertex];
	this->adj = new int* [numOfVertex];
	this->sample = new int* [numOfVertex];
	this->vertexTopK = new double* [numOfVertex];
	for (int i = 0; i < numOfVertex; i++) {
		this->adj[i] = new int [numOfVertex];
		this->sample[i] = new int [numOfVertex];
		this->vertexTopK[i] = new double [numOfVertex];
	}
		
	for (int i = 0; i < numOfVertex; i++) {
		//this->vertex[i] = NULL;
		for (int j = 0; j < numOfVertex; j++) {
			this->adj[i][j] = 0;
			this->sample[i][j] = 0;
			this->vertexTopK[i][j] = 0;
		}
	}
}
	
void Graph::loadVertexInfo(int** adj, Vertex* vertex, string vertexFile, string edgeFile){
	ifstream nf;
	nf.open(vertexFile.c_str());
	string v;
	int i = 0;
	int line = 0;
	while (getline(nf,v)){
		std::vector<string> arr = split(v, "\t");
		int* tmpT = new int[arr.size() - 2];
		for (int i = 1; i < arr.size() - 1;i++)
			tmpT[i - 1] = atoi(arr[i].c_str());
        Vertex tmpV;
		tmpV.initVertex(arr.size() - 2);
        tmpV.setId(arr[0]);
        tmpV.setTermV(tmpT);
        tmpV.setLabel(arr[arr.size() - 1]);
        vertex[line] = tmpV;
		this->vertexData.insert(map<string,int>::value_type(tmpV.getId(), line));
    	line++; 
	}
	nf.close();
}
void Graph::loadEdgeInfo(int** adj, Vertex* vertex, string vertexFile, string edgeFile) {
	
	ifstream ef;
	ef.open(edgeFile.c_str());

	string e;
	int line = 0;
	while (getline(ef,e)){
		line++;
		std::vector<string> arr = split(e, "\t");
		map <string, int>::iterator iter1, iter2;

		iter1 = this->vertexData.find(arr[0]);
		iter2 = this->vertexData.find(arr[1]);
		if (iter1 != this->vertexData.end()) {
			if (iter2 != this->vertexData.end()) {
				int v1 = iter1->second;
				int v2 = iter2->second;
				adj[v1][v2] = 1;
			}
		}
	}
	ef.close();
}

void Graph::writeVertexTopK2File() {
	char filename[] = "E:\\作业\\现代数据库系统概论\\hw4\\618506165_6_Project4\\citeseer\\topK.bin";
	ofstream fout(filename);
	int i = 0, j = 0;
	for (i = 0; i < this->numV; i++) {
		if (i > 0)
			fout<<endl;
		for (j = 0; j < this->numV - 1; j++) {
			fout<<this->vertexTopK[i][j]<<"\t";
		}
		fout<<this->sample[i][j];
	}
	fout.close();
}

void Graph::getTopK(int** adj, int adjlength, Vertex* verties) {
	// cal the similarity of content between every vertex
	for (int i = 0; i < adjlength; i++) {
		for (int j = i; j < adjlength; j++) {
			this->vertexTopK[i][j] = cosineDistance(verties[i], verties[j]);
		}
		cout<<"line "<<i<<endl;
	}
	for (int i = 1; i < adjlength; i++)
		for (int j = 0; j < i; j++)
			this->vertexTopK[i][j] = vertexTopK[j][i];
	this->writeVertexTopK2File();
	for (int i = 0; i < adjlength; i++) {
		vector<PAIR> vec;
		for (int j = 0; j < adjlength; j++) {
			PAIR pair;
			pair.vertex = verties[j]; 
			pair.sim = this->vertexTopK[i][j];
			vec.push_back(pair);
		}
		std::sort(vec.begin(), vec.end());
		int count = vec.size();
		for (int j = 0; j < this->K; j++) {
			map <string, int>::iterator iter;
			iter = this->vertexData.find(vec[j].vertex.getId());
			adj[i][iter->second] = 1;
			cout<<i<<"\t"<<iter->second<<"\t"<<"connected"<<endl;
		}
	}

}

double Graph:: cosineDistance(Vertex v1, Vertex v2) {
	double rtn = 0, fenzi = 0, fenmu1 = 0, fenmu2 = 0;
	//int l1 = sizeof(v1.getTermV) / sizeof(int);
	//int l2 = sizeof(v2.getTermV) / sizeof(int);
	int l1 = v1.getTermVLen();
	int l2 = v2.getTermVLen();
	for (int i = 0; i < l1;i++) {
		fenzi += v1.getTermV()[i] * v2.getTermV()[i];
	}
	fenmu1 = getLength(v1);
	fenmu2 = getLength(v2);
	rtn = fenzi / (fenmu1 * fenmu2);
	return rtn;
} 

double Graph:: getLength(Vertex v) {
	double rtn = 0;
	//int l = sizeof(v.getTermV) / sizeof(int);
	int l= v.getTermVLen();
	for (int i = 0; i < l; i++)
		rtn += (v.getTermV()[i] * v.getTermV()[i]);
	return sqrt(rtn);
}

void Graph:: simplification() {
	// Local Ranking of Edges and Graph Simplification
	for (int i = 0; i < this->numV; i++) {
		cout<<i<<endl;
		// get the neighbor verties set of vertex i
		list<Vertex> ingbr = getNgbr(i);
		double* simT = new double[ingbr.size()];
		double* simC = new double[ingbr.size()];
		double* sim = new double[ingbr.size()];
		list<Vertex>::iterator ingbrIter;
		int j = 0;
		for(ingbrIter = ingbr.begin(); ingbrIter != ingbr.end(); ingbrIter++) {
			// get the neighbor verties set of vertex j
			list<Vertex> jngbr = getNgbr(this->vertexData.find((*ingbrIter).getId())->second);
			// cal the jaccord similarity between the ngbr verties set of i and j
			simT[j] = getJaccordSimilarity(ingbr, jngbr);
			j++;
		}

		// normalize
		this->getNormalized(simT);
		j = 0;
		for(ingbrIter = ingbr.begin(); ingbrIter != ingbr.end(); ingbrIter++) {
			// cal the topology similarity between vertex i and j
			simC[j] = cosineDistance(this->vertex[i], (*ingbrIter));
		}
		
		// normalize
		this->getNormalized(simC);
		for (j = 0; j < ingbr.size(); j++) {
			// aggregate simT and simC with the weight specified by lamda
			sim[j] = this->lamda * simT[j] + (1 - this->lamda) * simC[j];
		}

		vector<PAIR> vec;
		j = 0;
		for(ingbrIter = ingbr.begin(); ingbrIter != ingbr.end(); ingbrIter++) {
			PAIR pair;
			pair.vertex = (*ingbrIter);
			pair.sim = sim[j];
			vec.push_back(pair);
			j++;
		}
		std::sort(vec.begin(), vec.end());
		int count = vec.size();
		// retain the edges with highest similarity values
		// build edge set named with sample
		for (j = 0; j < sqrt(ingbr.size()); j++) {
			map <string, int>::iterator iter;
			iter = this->vertexData.find(vec[j].vertex.getId());
			this->sample[i][iter->second] = 1;
		}
		//-=-======================
		
	}
	/**
	for (int k = 0;k < 10;k++) {
		for (int p = 0; p < 10;p++) {
			cout<<this->sample[k][p]<<"  ";
		}
		cout<<endl;
	}
	*/
	this->write2file();
}
	
void Graph:: getNormalized(double* arr) {
	double min = DBL_MAX, max = 0;
	int len = sizeof(arr)/ sizeof(double);
	for (int j = 0; j < len; j++) {
		if (arr[j] > max)
			max = arr[j];
		if (arr[j] < min)
			min = arr[j];
	}
	for (int j = 0; j < len; j++) {
		arr[j] = (arr[j] - min) / (max - min);
	}
} 
	
double Graph:: getJaccordSimilarity (list<Vertex> v1, list<Vertex> v2) {
	double rtn = 0;
	int jiao = 0;
	list<Vertex>::iterator iter1, iter2;
	for(iter1 = v1.begin(); iter1 != v1.end(); iter1++) {
		for(iter2 = v2.begin(); iter2 != v2.end(); iter2++) {
			if ((*iter1).getId() == (*iter2).getId()) {
				jiao++;
			}
		}
	}
	rtn = (double)jiao / (double)(v1.size() + v2.size() - jiao);
	return rtn;
} 
	
list<Vertex> Graph:: getNgbr(int index) {
	list<Vertex> ngbr;
	for (int i = 0; i < this->numV; i++) {
		if (adj[index][i] == 1) {
			ngbr.push_back(this->vertex[i]);
		}
	}
	return ngbr;
}
