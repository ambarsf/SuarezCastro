#ifndef LLAMADAS_H
#define LLAMADAS_H

class Llamadas{
	int numero;
	int inicio;
	int final;
	int destino;
public:
	Llamadas(int,int,int,int);
	int getNumero();
	int getInicio();
	int getFinal();
	int getDestino();
	void setNumero(int);
	void setInicio(int);
	void setFinal(int);
	void setDestino(int);

};
#endif
