#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
char Gender();

//struct for clients 
struct Client{
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
};