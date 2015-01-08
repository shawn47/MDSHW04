#include <iostream>
#include <string>
#include "vertex.h"
#include "graph.h"

using namespace std;

int main(int argc,char *argv[]){
	string nodeInfoPath;
	string edgeInfoPath;
	int k = 3;
	nodeInfoPath = "D:\\��ҵ\\�ִ����ݿ�ϵͳ����\\hw4\\618506165_6_Project4\\citeseer\\citeseer.content";
	edgeInfoPath = "D:\\��ҵ\\�ִ����ݿ�ϵͳ����\\hw4\\618506165_6_Project4\\citeseer\\citeseer.cites";
	cout<<k<<endl;
	cout<<nodeInfoPath<<endl;
	cout<<edgeInfoPath<<endl;
	Graph* g = new Graph();

	

	g->initialize(3312, 3);
	g->loadVertexInfo(g->adj, g->vertex, nodeInfoPath, edgeInfoPath);
	cout<<"vertex info loadind complete"<<endl;
	g->loadEdgeInfo(g->adj, g->vertex, nodeInfoPath, edgeInfoPath);
	cout<<"edge info loadind complete"<<endl;
	cout<<g->adj[0][99]<<endl;
	//g->getTopK(g->adj, 3312, g->vertex);
	g->getTopK(g->adj, 3312, g->vertex);
	g->simplification();
	cout<<"========"<<endl;
	g->sample2file();
	cout<<"========"<<endl;
	/**
	vector<vector<double>> samplematrix = g->sample2Matrix();
	MarkovCluster mcl;
	vector<vector<double>> cluster_matrix = mcl.calculate_cluster_matrix(samplematrix, 2, 2);
	vector<vector<int>> clusters = mcl.collect_clusters(cluster_matrix, 5);
	for (int i = 0; i < clusters.size(); ++i) {
		for (int j = 0; j < clusters[i].size(); ++j) {
			cout << clusters[i][j] << " ";
		}
		cout << endl;
	}
	*/
	cout<<"========"<<endl;
}