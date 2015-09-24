#ifndef LINEAH
#define LINEA_H

class Linea{
	int numero;
	int IDcliente;
public:
	Linea(int, int);
	int getNumero();
	void setNumero(int);
	int getIDcliente();
	void setIDcliente(int);
};
#endif