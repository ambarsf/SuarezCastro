#include <iostream>
using namespace std;

int menu();
int opciones();

int main(int argc, char* argv[]){
	int opcion=opciones;
	switch(opcion){
		case 1:{

		};//end case 1
		case 2:{

		};//end case 2
		case 3:{

		};//end case 3
	};//end switch
	return 0;
}

int menu(){
	int option;
	cout<<"MENU:"<<endl;
	cout<<"1. Create."<<endl;
	cout<<"2. Read."<<endl;
	cout<<"3. Update."<<endl;
	cout<<"4. Delete."<<endl;
	do{
		cout<<"Write your option: ";
		cin>>option;
		cout<<endl;
	}while(option>4||option<1);
	return option;
}

int opciones(){
	int option;
	cout<<"Options:"<<endl;
	cout<<"1. Clients."<<endl;
	cout<<"2. Lines."<<endl;
	cout<<"3. Cities."<<endl;
	do{
		cout<<"Write your option: ";
		cin>>option;
		cout<<endl;
	}while(option>3||option<1);
	return option;

}