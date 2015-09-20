#include "Linea.h"
using namespace std;

Linea::Linea(int numero, int IDcliente){
	this->numero=numero;
	this->IDcliente=IDcliente;
}

int Linea::getNumero(){
	return numero;
}

void Linea::setNumero(int numero){
	this->numero=numero;
}

int Linea::getIDcliente(){
	return IDcliente;
}

void Linea::setIDcliente(int IDcliente){
	this->IDcliente=IDcliente;
}