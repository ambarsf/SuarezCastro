#include <iostream>
using namespace std;
int opciones();
int menu();

int main (int argc, char* argv[]){
	int opcion=opciones();
	switch(opcion){
		case 1:{
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