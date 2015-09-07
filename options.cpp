#include <iostream>
#include <fstream>


using namespace std;
int opciones();
int menu();

//struct for clients 
struct Clients{
	char ID[14];
	char name[40];
	char gender;
	char cityID[4];
	int posicion;
	bool available;
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

int main (int argc, char* argv[]){
	int opcion=opciones();
	switch(opcion){
		case 1:{
			ifstream file("clients.bin", ifstream::binary);
			Clients client;
			if (file.fail()){
				cout<<"No se pudo abrir el archivo!"<<endl;
			}
			int option=menu();
			switch (option){
				case 1:{

				};// end case create
				case 2:{
					cout<<"List of Clients: "<<endl;
					while(file.read(reinterpret_cast<char*>(&client), sizeof(client))){
						if (client.available==false){
							cout<<"ID: "<<client.ID<<endl;
							cout<<"Name: "<<client.name<<endl;
							cout<<"Gender: "<<client.gender<<endl;
							cout<<"CityID: "<<client.cityID<<endl;
							cout<<endl;
						}//fin if
					}//fin while
					file.close();
				};// end case read
				case 3:{

				};// end case update
				case 4:{

				};//end case delete 
			};
		};//fin case clients

		case 2:{
			int option=menu();
			switch (option){
				case 1:{

				};// end case create
				case 2:{

				};// end case read
				case 3:{

				};// end case update
				case 4:{

				};//end case delete 
			};		
		};//fin case lines

		case 3:{
			int option=menu();
			switch (option){
				case 1:{

				};// end case create
				case 2:{

				};// end case read
				case 3:{

				};// end case update
				case 4:{

				};//end case delete 
			};
		};// fin case cities
	};
	return 0;
}// end main

int opciones (){
	int options;
	cout<<"Options: "<<endl;
	cout<<"1. Clients."<<endl;
	cout<<"2. Lines."<<endl;
	cout<<"3. Cities."<<endl;
	do{
		cout<<"Write your option: ";
		cin>>options;
		cout<<endl;
	}while(options>3||options<1);
	return options;
}

int menu(){
	int options;
	cout<<"MENU: "<<endl;
	cout<<"1. Create"<<endl;
	cout<<"2. Read"<<endl;
	cout<<"3. Update"<<endl;
	cout<<"4. Delete"<<endl;
	do{
		cout<<"Write your option: ";
		cin>>options;
		cout<<endl;
	}while(options>3||options<1);
	return options;
}