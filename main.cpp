#include <iostream>
using namespace std;

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