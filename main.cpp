#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <cstring>
#include <cmath>
#include <sstream>
#include <vector>

using namespace std;

char Gender();
int* inicio();
const char* toString(int*);
int* final(int*);

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
	int start; // muy feo estar escribiendo beginning
	int end;
	int to;// numero a quien se esta llamando 
};

int main(int argc, char* argv[]){
	vector<Clients> clients;
	vector<Cities> cities;

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
	ifstream CityIDfile("CitiesID.txt");
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

	for (int i = 0; i < clients.size(); ++i)
	{
		Clients client=clients[i];
		cout<< client.ID<<endl;
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
	while(fin[3] < inicio[3]){
		fin[3] = rand() % 24 + 1; 
	}
	fin[4] = rand() % 59 + 1;
	fin[5] = rand() % 59 + 1; 
	return fin;
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
