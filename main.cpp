#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <cstring>
#include <cmath>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

char Gender();
int* inicio();
char* toString(int*);
int* final(int*);
int mayor(int,int);
double CalcularTarifa(double,double,double);

//struct for clients 
struct Clients{
	char ID[14];
	char name[40];
	char gender;
	char cityID[4];
	int posicion;
	bool available;
};
//estructura para el indice de clientes y el de lineas
struct Indice/*_Cli_Lin*/{
	unsigned int RRN;
	char Llave[14];
};

struct Indice_City{
	unsigned int RRN;
	char Llave[14];
};
//struct for lines per client
struct Lines{
	char number[11];
	char ID[14];
	int posicion;
	bool available;
};
//struct for cities
struct Cities{
	char IDCity[4];
	char CityName [40];
	int posicion;
	bool available;
};

//struct for calls
struct Calls{
	char from[11]; // numero de quien hace la llamada
	char start[15]; // muy feo estar escribiendo beginning
	char end[15];
	char to[11];// numero a quien se esta llamando
	double tarifa; 
};

Calls llamadas(vector<Lines>);
void Ordenar(vector<Calls>&);
void Ordenar2(vector<Calls>&,int,int,int);
double Tarifa(int*,int*);
void Organize(vector<char*>&);
int* toInt(char*);
char* Solucion(char*);

int main(int argc, char* argv[]){
	vector<Calls> calls;
	vector<Clients> clients;
	vector<Cities> cities;
	vector<Lines> lines;
	srand(time(0));

	//leer los id
	char** ClientId = new char* [500];
	char tempid[14];
	ifstream fileId ("Id.txt");
	if (fileId.is_open()){
		for (int i = 0; i < 500; i++){
			fileId.getline(tempid,sizeof(tempid));
			ClientId[i] = new char[strlen(tempid) + 1];
			strcpy(ClientId[i],tempid);
		}
		fileId.close();
	}else{
		cout<<"ERROR"<<endl;
	}
	

	// Read Clients
	char** ClientName= new char* [500];
	char client[40];
	ifstream namefile ("RandomNames.txt");
	if (namefile.is_open()){
		for (int i = 0; i < 500; i++)
		{
			namefile.getline(client,sizeof(client));
			ClientName[i]=new char[strlen(client)+1];
			strcpy(ClientName[i],client);
		}
		namefile.close();
	}else{
		cout<<"Unable to open file"<<endl;
	}

	// Read Cities
	char** CityName=new char*[30];
	char city[40];
	ifstream cityfile("RandomCities.txt");
	if (cityfile.is_open()){
		for (int i = 0; i < 30; i++)
		{
			cityfile.getline(city,sizeof(city));
			CityName[i]=new char[strlen(city)+1];
			strcpy(CityName[i],city);
		}
		cityfile.close();
	}else{
		cout<<"Unable to open file"<<endl;
	}


	// Read Phone Numbers
	char** PhoneNumbers=new char*[750];
	char numbers[11];
	ifstream phonefile("RandomPhoneNumbers.txt");
	if (phonefile.is_open()){
		for (int i = 0; i < 750; i++)
		{
			phonefile.getline(numbers,sizeof(numbers));
			PhoneNumbers[i]=new char[strlen(numbers)+1];
			strcpy(PhoneNumbers[i],numbers);
		}
		phonefile.close();
	}else{
		cout<<"Unable to open file"<<endl;
	}
	// Read Cities ID
	char** CitiesID=new char*[30];
	char cityID[4];
	ifstream CityIDfile("CityID.txt");
	if (CityIDfile.is_open()){
		for (int i = 0; i < 30; i++)
		{
			CityIDfile.getline(cityID,sizeof(cityID));
			CitiesID[i]=new char[strlen(cityID)+1];
			strcpy(CitiesID[i],cityID);
		}
		CityIDfile.close();
	}else{
		cout<<"Unable to open file"<<endl;
	}
	//fill the clients vector
	ifstream clientsfile("clients.bin", ifstream::binary);
	Clients clientes;
	if (clientsfile.fail()){
		ofstream indice_clients("Ind_Clients.bin",ofstream::binary);
		ofstream clientesfile("clients.bin", ofstream::binary);
		vector<char*> llaves_cli;
		for (int i = 0; i < 500; i++){
			Clients client;
			strcpy(client.ID,ClientId[i]);
			strcpy(client.name,ClientName[i]);
			int random=rand()%30;
			strcpy(client.cityID,CitiesID[random]);
			client.gender=Gender();
			client.posicion=-1;
			client.available=false;
			llaves_cli.push_back(client.ID);
			clientesfile.write(reinterpret_cast<const char*>(&client), sizeof(client));
		}
		Organize(llaves_cli);
			for (int i = 0; i < llaves_cli.size(); ++i){
				Indice ind;
				ind.RRN = i+1;
				strcpy(ind.Llave,llaves_cli.at(i));
				indice_clients.write(reinterpret_cast<const char*>(&ind), sizeof(ind));
			}
		cout<<"Clients file has been written :)"<<endl;
		clientesfile.close();
	}
	while(clientsfile.read(reinterpret_cast<char*>(&clientes), sizeof(clientes))){
		clients.push_back(clientes);
	}//fin while
	clientsfile.close();
	//fill the Cities 
	//ifstream file("cities.bin", ifstream::binary);
	Cities ciudades;
	//if (file.fail()){
	ofstream citiesfile ("cities.bin", ofstream::binary);
	ofstream indice_city("indice_city.bin", ofstream::binary);
	vector<char*> llaves_city;
	for (int i = 0; i < 30; i++){
		Cities city;
		strcpy(city.IDCity,CitiesID[i]);
		strcpy(city.CityName,CityName[i]);
		city.posicion=-1;
		city.available=false;
		llaves_city.push_back(city.IDCity);
		citiesfile.write(reinterpret_cast<const char*>(&city), sizeof(city));
	}
	cout<<"Cities file has been written :)"<<endl;
	citiesfile.close();
	Organize(llaves_city);
	for (int i = 0; i < llaves_city.size(); i++){
		Indice ind_city;
		ind_city.RRN = i + 1;
		strcpy(ind_city.Llave, llaves_city.at(i));
		indice_city.write(reinterpret_cast<const char*>(&ind_city), sizeof(ind_city));
	}
	indice_city.close();
	//}
	/*while(file.read(reinterpret_cast<char*>(&ciudades), sizeof(ciudades))){
		cities.push_back(ciudades);
	}//fin while
	file.close();*/

	// fill the lines
	ifstream linesfile ("lines.bin",ifstream::binary);
	Lines lineas;
	if(linesfile.fail()){
		vector<char*> llaves_lines;
		ofstream lineasfile("lines.bin", ofstream::binary);
		ofstream indice_line("Ind_lines.bin", ofstream::binary);	
		cout<<"1"<<endl;
		for (int j = 0; j < 500; j++){
			Lines line;
			strcpy(line.number,PhoneNumbers[j]);
			strcpy(line.ID,ClientId[j]);
			llaves_lines.push_back(line.ID);
			line.posicion=-1;
			line.available=false;
			lines.push_back(line);
			lineasfile.write(reinterpret_cast<const char*>(&line), sizeof(line));
		}
		Organize(llaves_lines);
		for (int i = 0; i < llaves_lines.size(); ++i){
			Indice ind;
			ind.RRN = i+1;
			strcpy(ind.Llave,llaves_lines.at(i));
			indice_line.write(reinterpret_cast<const char*>(&ind), sizeof(ind));
		}
		cout<<"2"<<endl;
		cout<<"Lines file has been written :)"<<endl;
		lineasfile.close();
	}
	while(linesfile.read(reinterpret_cast<char*>(&lineas), sizeof(lineas))){
		lines.push_back(lineas);
	}//fin while
	linesfile.close();
	cout<<"3"<<endl;
	//ifstream file_calls1("calls.bin", ifstream::binary);
	Calls llamadas_1;
	//if(file_calls1.fail()){	
	ofstream file_calls("calls.bin",ofstream::binary);
	cout<<lines.size()<<endl;
	for (int i = 0; i < 500; i++){
		calls.push_back(llamadas(lines));
	}
	Ordenar(calls);
	cout<<"5"<<endl;
	for (int i = 0; i < calls.size(); i++){
		Calls llam = calls.at(i);
		file_calls.write(reinterpret_cast<const char*>(&llam), sizeof(llam));
	}
	file_calls.close();
	/*}else{
		while(file_calls1.read(reinterpret_cast<char*>(&llamadas_1), sizeof(llamadas_1))){
			calls.push_back(llamadas_1);
		}
		file_calls1.close();
	}*/
	//Ordenar(calls);
	return 0;
}

void Organize(vector<char*> &list){
	cout<<"4"<<endl;
	for (int i = 0; i < list.size() - 1; i++){
		for (int j = i + 1; j < list.size(); j++){
			if(atoi(list.at(i)) > atoi(list.at(j))){
				swap(list.at(i),list.at(j));
			}
		}
	}	
}

char Gender(){
	int num=(rand()%2);
	char gender;
	if (num==0){
		gender='F';
	}else{
		gender='M';
	}
	return gender;
}

int* inicio(){
	int* inicio = new int[7];
	inicio[0] = 2015;
	inicio[1] = rand() % 12 + 1;
	inicio[2] = rand() % 31 + 1;
	inicio[3] = rand() % 24 + 1;
	inicio[4] = rand() % 59 + 1;
	inicio[5] = rand() % 59 + 1;
	return inicio;
}

int* final(int* inicio){
	int* fin = new int[7];
	fin[0] = 2015;
	fin[1] = inicio[1];
	fin[2] = inicio[2];
	fin[3] = mayor(inicio[3],24);
	if(fin[3] == inicio[3]){
		fin[4] = mayor(inicio[4],59);
		fin[5] = mayor(inicio[5],59);
	}else{ 
		fin[4] = rand() % 59 + 1;
		fin[5] = rand() % 59 + 1;
	}
	return fin;
}

int mayor(int num, int limit){
	int retval = rand() % limit + num;
	while(retval > limit){
		retval = rand() % limit + num;
	}
	return retval;
}

char* toString(int * ints){
	stringstream ss;
	for (int i = 0; i < 6; i++){
		if(10 - ints[i] > 0){
			ss<<"0"<<ints[i];
		}else{
			ss<<ints[i];	
		}
	}
	return (char*)ss.str().c_str();
}

Calls llamadas(vector<Lines> lineas){
	Calls call;
	int size = lineas.size() - 1;
	int pos = rand() % size + 0;
	strcpy(call.from,lineas.at(pos).number);
	strcpy(call.start,toString(inicio()));
	strcpy(call.end,toString(final(toInt(call.start))));
	int pos2 = rand() % size + 0;
	while(lineas.at(pos).ID == lineas.at(pos2).ID){
		pos2 = rand() % size + 0;	
	}
	strcpy(call.to,lineas.at(pos2).number);
	call.tarifa = Tarifa(toInt(call.start), toInt(call.end));
	return call;
}

double Tarifa(int* inicio, int* fin){
	double begin = inicio[3] + inicio[4]/60 + inicio[5]/3600;
	double end = fin[3] + fin[4]/60 + fin[5]/3600;
	double valor = CalcularTarifa(begin,end,0);
	return valor;
}

double CalcularTarifa(double inicio, double fin, double valor){
	int range = 0;
	double dig = 0;
	while(fin > range){
		range = 0;
		if(inicio >= 0 && inicio < 8){
			range = 8;
			dig = 0.6;
		}else if(inicio >= 8 && inicio < 16){
			range = 16;
			dig = 2.4;
		}else{
			range = 24;
			dig = 3;
		}
		//cout<<"RANGE"<<range<<"FIN"<<fin<<"INICI"<<inicio<<"DIG"<<dig<<endl;
		valor += (range-inicio)*dig;
		inicio = range;
		//cout<<valor<<endl;
	}
	return valor+=(fin - inicio)*dig;
}


void Ordenar(vector<Calls>& calls){
	//cout<<"ORDENAR0"<<endl;
	Ordenar2(calls,1,0,calls.size());
	//cout<<"ORDENAR"<<endl;
	int cont;
	int contador = 1;
	while(contador < 5){
		cont = 0;
		for(int j = 0; j < calls.size(); j++){
			for (int i = cont + 1; i < calls.size() ; i++){
				if(toInt(calls.at(i).start)[contador] != toInt(calls.at(cont).start)[contador]){
					Ordenar2(calls,contador+1,cont,i);
					cont = i;
					break;
				}
			}
		}
		contador++;
	}
	//cout<<"BIEN"<<endl;
}

void Ordenar2(vector<Calls>& calls,int pos, int beg, int end){
	//cout<<"ORDENAR1"<<endl;
	for (int i = beg; i < end -1; i++){
		for (int j = i+1; j < end; j++){
			//cout<<toInt(calls.at(i).start)[pos]<<"   ";
			//cout<<toInt(calls.at(j).start)[pos]<<endl;
			if(toInt(calls.at(i).start)[pos] > toInt(calls.at(j).start)[pos]){
				//cout<<"ORDENAR3"<<endl;
				swap(calls.at(i),calls.at(j));
				//cout<<"ORDENAR4"<<endl;
			}
		}
	}
}

int* toInt(char* string){
	int* retval = new int[6];
	retval[0] = 2015;
	int cont = 1;
	for (int i = 4; i < 13; i+=2){
		stringstream ss;
		ss<<string[i]<<string[i+1];
		retval[cont] = atoi(ss.str().c_str());
		cont++;
	}
	return retval;
}

