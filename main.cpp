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
const char* toString(int*);
int* final(int*);
int mayor(int,int);

//struct for clients 
struct Clients{
	int ID;
	char name[40];
	char gender;
};

//struct for lines per client
struct Lines{
	int number;
	int ID;
};

//struct for cities
struct Cities{
	int IDCity;
	char CityName [40];
};

//struct for calls
struct Calls{
	int from; // numero de quien hace la llamada
	int* start; // muy feo estar escribiendo beginning
	int* end;
	int to;// numero a quien se esta llamando 
};

Calls llamadas(vector<Lines>);
void Ordenar(vector<Calls>&);
void Ordenar2(vector<Calls>&,int,int,int);

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
	/*for (int i = 0; i < 500; ++i){
		cout<<ClientId[i]<<endl;
	}*/

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
	char numbers[8];
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
	char cityID[3];
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
	for (int i = 0; i < 500; i++)
	{
		Clients client;
		char id [14];
		strcpy(id,ClientId[i]);
		string Id="";
		for (int j = 0; j < strlen(id); j++)
		{
			Id+=id[j];
		}
		client.ID=atoi(Id.c_str());
		strcpy(client.name,ClientName[i]);
		client.gender=Gender();
		clients.push_back(client);
	}

	//fill the Cities vector
	for (int i = 0; i < 30; i++)
	{
		Cities city;
		char id [3];
		strcpy(id,CitiesID[i]);
		string Id="";
		for (int j = 0; j < strlen(id); j++)
		{
			Id+=id[j];
		}
		city.IDCity=atoi(Id.c_str());
		strcpy(city.CityName,CityName[i]);
		cities.push_back(city);
	}

	for (int i = 0; i < 500; i++)
	{
		Clients client=clients[i];
		Lines line;
		char number[8];
		strcpy(number,PhoneNumbers[i]);
		string num="";
		for (int j = 0; j < strlen(number); j++)
		{
			num+=number[j];
		}
		line.number=atoi(num.c_str());
		line.ID=client.ID;
		lines.push_back(line);
	}

	/*for (int i = 0; i < clients.size(); i++)
	{
		Clients client=clients[i];
		cout<<client.ID<<endl;
	}*/
	for (int i = 0; i < 20; i++){
		calls.push_back(llamadas(lines));
		//cout<<"I--->"<<i<<"  "<<calls.at(i).from<<"   "<<calls.at(i).to<<"   "<<toString(calls.at(i).start);
		//cout<<"   "<<toString(calls.at(i).end)<<endl;	
	}
	cout<<"ANTES"<<endl;
	Ordenar(calls);
	/*for (int i = 0; i < calls.size()-1; i++){
		for (int j = i+1; j < calls.size(); j++){
			cout<<j;
			if(calls.at(i).start[1] > calls.at(j).start[1]){
				swap(calls.at(i), calls.at(j));

			}
		}
	}*/
	cout<<"DESPUES"<<endl;
	for (int i = 0; i < calls.size(); i++){
		//calls.push_back(llamadas(lines));
		cout<<toString(calls.at(i).start)<<endl;	
	}
	return 0;
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
		//cout<<endl<<"LIMIT"<<limit<<"MAYOR"<<retval<<endl;
	}
	return retval;
}

const char* toString(int * ints){
	stringstream ss;
	for (int i = 0; i < 6; i++){
		if(10 - ints[i] > 0){
			ss<<"0"<<ints[i];
		}else{
			ss<<ints[i];	
		}
	}
	return ss.str().c_str();
}

Calls llamadas(vector<Lines> lineas){
	Calls call;
	int size = lineas.size() - 1;
	int pos = rand() % size + 0;
	call.from = lineas.at(pos).number;
	//cout<<"FROM    "<<call.from<<"    POS    "<<pos<<endl;
	call.start = inicio();
	//cout<<"START-->"<<toString(call.start)<<endl;
	call.end = final(call.start);
	//cout<<"END---->"<<toString(call.end)<<endl;
	int pos2 = rand() % size + 0;
	while(lineas.at(pos).ID == lineas.at(pos2).ID){
		pos2 = rand() % size + 0;	
	}
	call.to = lineas.at(pos2).number;
	//cout<<"TO    "<<call.to<<"    POS2    "<<pos2<<endl;
	return call;
}


void Ordenar(vector<Calls>& calls){
	Ordenar2(calls,1,0,calls.size());
	//cout<<"SI1"<<endl;
	int cont;
	int contador = 1;
	while(contador < 5){
		cont = 0;
		for(int j = 0; j < calls.size(); j++){
			for (int i = cont + 1; i < calls.size() ; i++){
				if(calls.at(i).start[contador] != calls.at(cont).start[contador]){
					Ordenar2(calls,contador+1,cont,i);
					cout<<"SI"<<cont<<"   "<<i<<endl;
					cont = i;
					break;
				}
			}
		}
		contador++;
	}
}

void Ordenar2(vector<Calls>& calls,int pos, int beg, int end){
	for (int i = beg; i < end -1; i++){
		for (int j = i+1; j < end; j++){
			if(calls.at(i).start[pos] > calls.at(j).start[pos]){
				swap(calls.at(i),calls.at(j));
			}
		}
	}
}


