#include "vertex.h"
#include <utility>

using namespace std;
//ʹ��ģ�嶨��һ������getArrayLen,�ú�������������array�ĳ��� 
template <class T>
int getArrayLen(T& array) { 
  return (sizeof(array) / sizeof(array[0]));
}
Vertex::Vertex(){}
Vertex::~Vertex() {}
void Vertex::initVertex(int len) {
	this->termVLen = len;
	this->termV = new int[len];
}
int Vertex::getTermVLen() {
	return this->termVLen;
}
string Vertex::getId() {
	return this->id;
}
void Vertex::setId(string id) {
	this->id = id;
}
int* Vertex:: getTermV() {
	return this->termV;
}
void Vertex::setTermV(int* termV) {
	this->termV = termV;
}
string Vertex::getLabel() {
	return this->label;
}
void Vertex::setLabel(string label) {
	this->label = label;
}