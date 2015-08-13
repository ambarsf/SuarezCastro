#include "Llamadas.h"
using namespace std;

Llamadas::Llamadas(int numero, int inicio ,int final ,int destino){
	this->numero=numero;
	this->inicio=inicio;
	this->final=final;
	this->destino=destino;
}

int Llamadas::getNumero(){
	return numero;
}

int Llamadas::getInicio(){
	return inicio;
}

int Llamadas::getFinal(){
	return final;
}

int Llamadas::getDestino(){
	return destino;
}

void Llamadas::setNumero(int numero){
	this->numero=numero;
}

void Llamadas::setInicio(int inicio){
	this->inicio=inicio;
}

void Llamadas::setFinal(int final){
	this->final=final;
}

void Llamadas::setDestino(int destino){
	this->destino=destino;
}
