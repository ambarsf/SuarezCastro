#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;
int opciones();
int menu();
//string LongtoString(long);

//struct for clients 
struct Clients{
	char ID[14];
	char name[40];
	char gender;
	char cityID[4];
	int posicion;
	bool available;
};

struct Header{
	int avail;
	int size;
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

struct Indice{
	unsigned int RRN;
	char Llave[14];
};

struct charast{
	char id[14];
};

int binary_insertion( vector<long>, long);
int binary_search(vector<long>, long);

int main (int argc, char* argv[]){	
	srand(time(0));
	int cont_ID = 500;
	int opcion;
	do{
		opcion = opciones();
		switch(opcion){
			case 1:{
				
				//if (file.fail()){
				//	cout<<"No se pudo abrir el archivo!"<<endl;
				//}
				int option=menu();
				switch (option){
					case 1:{
						ofstream file_cli_create("clients.bin",ios::app|ofstream::binary);
						Clients append_client;
						char tempid[14];
						ifstream fileId ("Id.txt");
						fileId.seekg((14*cont_ID),ios::beg);
						fileId.getline(tempid,sizeof(tempid));
						fileId.close();
						cont_ID++;
						strcpy(append_client.ID,tempid);
						cout<<endl;
						cout<<"Name >>";
						cin>>append_client.name;
						cout<<endl;
						cout<<"Gender >>";
						cin>>append_client.gender;
						cout<<endl;
						long Id_toadd = atol(append_client.ID);
						char** CitiesID1 = new char*[30];
						char cityID1[4];
						ifstream CityIDfile2("CityID.txt");
						for (int i = 0; i < 30; i++){
							CityIDfile2.getline(cityID1,sizeof(cityID1));
							CitiesID1[i]=new char[strlen(cityID1)+1];
							strcpy(CitiesID1[i],cityID1);
						}
						CityIDfile2.close();
						int temppos = rand() % 30 + 0;
						strcpy(append_client.cityID,CitiesID1[temppos]);
						append_client.posicion = -4; 
						file_cli_create.write(reinterpret_cast<char*>(&append_client), sizeof(append_client));
						cout<<"DONE"<<endl;
						ifstream ind_cli("Ind_Clients.bin", ifstream::binary);
						Indice ind1;
						vector<long> Indices_cl;
						vector<charast> Indices_allcl;
						while(ind_cli.read(reinterpret_cast<char*>(&ind1), sizeof(ind1))){
							cout<<ind1.RRN<<"   "<<ind1.Llave<<endl;
							Indices_cl.push_back(atol(ind1.Llave));
							charast tmp;
							strcpy(tmp.id,ind1.Llave);
							Indices_allcl.push_back(tmp);
						}
						/*for (int i = 0; i < Indices_cl.size(); i++){
						cout<<Indices_cl.at(i)<<endl;
						}*/
						ind_cli.close();
						//cout<<"HOY SI DONE"<<endl;
						//cout<<Indices_cl.size()<<endl;
						int insert_pos = binary_insertion(Indices_cl,Id_toadd);
						Indices_cl.insert(Indices_cl.begin() + insert_pos, Id_toadd);
						charast temp_charast;
						strcpy(temp_charast.id,append_client.ID);
						Indices_allcl.insert(Indices_allcl.begin() + insert_pos, temp_charast);
						ofstream update_Ind_cli("Ind_Clients.bin", ofstream::binary);
						for (int i = 0; i < Indices_allcl.size(); i++){
							Indice toinsert_cl;
							strcpy(toinsert_cl.Llave,Indices_allcl.at(i).id);
							toinsert_cl.RRN = i + 1;
							//update_Ind_cli.seekp((insert_pos + 1)*18,ios::beg);
							update_Ind_cli.write(reinterpret_cast<char*>(&toinsert_cl), sizeof(toinsert_cl));
						}
						update_Ind_cli.close();
					};// end case create
					break;
					case 2:{
						int decision = 0;
						cout<<"1.Show All"<<endl<<"2.Show by ID"<<endl;
						cin>>decision;
						if(decision == 1){
							Header head;
							ifstream file_cli("clients.bin", ifstream::binary);
							Clients client;
							cout<<"List of Clients: "<<endl;
							file_cli.read(reinterpret_cast<char*>(&head), sizeof(head));
							cout<<head.avail<<endl;
							while(file_cli.read(reinterpret_cast<char*>(&client), sizeof(client))){
								if(client.available == true){
								cout<<"ID: "<<client.ID<<endl;
								cout<<"Name: "<<client.name<<endl;
								cout<<"Gender: "<<client.gender<<endl;
								cout<<"CityID: "<<client.cityID<<endl;
								cout<<"POS -->"<<client.posicion<<endl;
								}
							}//fin while
							file_cli.close();
						}else{
							char id_toseek[14];
							cout<<"ID to seek >>";
							cin>>id_toseek;
							ifstream llaves_cli("Ind_Clients.bin",ifstream::binary);
							vector<long> llaves_clientes;
							vector<int> rrn_clientes;
							Indice ind_cli1;
							while(llaves_cli.read(reinterpret_cast<char*>(&ind_cli1),sizeof(ind_cli1))){
								llaves_clientes.push_back(atol(ind_cli1.Llave));
								rrn_clientes.push_back(ind_cli1.RRN);
							}
							llaves_cli.close();
							int position = binary_search(llaves_clientes, atol(id_toseek));
							int pos = rrn_clientes.at(position);
							if(pos == -1){
								cout<<"No match"<<endl;
							}else{
								//cout<<"POS-->"<<pos<<endl;
								ifstream archivo_clientes("clients.bin", ifstream::binary);
								Header client_head;
								archivo_clientes.read(reinterpret_cast<char*>(&client_head),sizeof(client_head));
								//cout<<"SIZE-->"<<client_head.size<<endl;
								archivo_clientes.seekg(((pos-1)*client_head.size)+8, archivo_clientes.beg);
								//cout<<"SIZE-->"<<archivo_clientes.tellg()<<endl;
								Clients client_toprint;
								archivo_clientes.read(reinterpret_cast<char*>(&client_toprint),sizeof(client_toprint));
								if(client_toprint.available != true){
									cout<<"ID: "<<client_toprint.ID<<endl;
									cout<<"Name: "<<client_toprint.name<<endl;
									cout<<"Gender: "<<client_toprint.gender<<endl;
									cout<<"CityID: "<<client_toprint.cityID<<endl;
									cout<<endl;
								}else{
									cout<<"No Match"<<endl;
								}
								archivo_clientes.close();
							}
						}
						//break;
					};// end case read
					break;
					/*case 4:{
						cout<<"The FUCK?"<<endl;
					};// end case update
					break;*/
					case 3:{
						char id_toseek[14];
						cout<<"ID to seek >>";
						cin>>id_toseek;
						ifstream llaves_cli("Ind_Clients.bin",ifstream::binary);
						vector<long> llaves_clientes;
						vector<int> rrn_clientes;
						Indice ind_cli1;
						while(llaves_cli.read(reinterpret_cast<char*>(&ind_cli1),sizeof(ind_cli1))){
							llaves_clientes.push_back(atol(ind_cli1.Llave));
							rrn_clientes.push_back(ind_cli1.RRN);
						}
						llaves_cli.close();
						int position = binary_search(llaves_clientes, atol(id_toseek));
						int pos = rrn_clientes.at(position);
						if(pos == -1){
							cout<<"No match"<<endl;
						}else{
							//cout<<"POS-->"<<pos<<endl;
							ifstream archivo_clientes("clients.bin", ifstream::binary);
							Header client_head;
							archivo_clientes.read(reinterpret_cast<char*>(&client_head),sizeof(client_head));
							//cout<<"SIZE-->"<<client_head.size<<endl;
							archivo_clientes.seekg(((pos-1)*client_head.size)+8, archivo_clientes.beg);
							//cout<<"SIZE-->"<<archivo_clientes.tellg()<<endl;
							Clients client_toprint;
							archivo_clientes.read(reinterpret_cast<char*>(&client_toprint),sizeof(client_toprint));
							//cout<<client_toprint.posicion<<endl;
							archivo_clientes.close();
							ofstream archivo_cli_mod("clients.bin",ofstream::binary);
							client_head.avail = (pos-1);
							client_toprint.available = true;
							client_toprint.posicion = -1;
							archivo_cli_mod.write(reinterpret_cast<char*>(&client_head),sizeof(client_head));
							archivo_cli_mod.seekp(((pos-1)*client_head.size)+8, archivo_cli_mod.beg);
							archivo_cli_mod.write(reinterpret_cast<char*>(&client_toprint),sizeof(client_toprint));
							archivo_cli_mod.close();
						}
					};//end case delete 
					break;
					case 4:{
						char id_toseek[14];
						cout<<"ID to seek >>";
						cin>>id_toseek;
						ifstream llaves_cli("Ind_Clients.bin",ifstream::binary);
						vector<long> llaves_clientes;
						vector<int> rrn_clientes;
						Indice ind_cli1;
						while(llaves_cli.read(reinterpret_cast<char*>(&ind_cli1),sizeof(ind_cli1))){
							llaves_clientes.push_back(atol(ind_cli1.Llave));
							rrn_clientes.push_back(ind_cli1.RRN);
						}
						llaves_cli.close();
						int position = binary_search(llaves_clientes, atol(id_toseek));
						int pos = rrn_clientes.at(position);
						if(pos == -1){
							cout<<"No match"<<endl;
						}else{
							//cout<<"POS-->"<<pos<<endl;
							ifstream archivo_clientes("clients.bin", ifstream::binary);
							Header client_head;
							archivo_clientes.read(reinterpret_cast<char*>(&client_head),sizeof(client_head));
							//cout<<"SIZE-->"<<client_head.size<<endl;
							archivo_clientes.seekg(((pos-1)*client_head.size)+8, archivo_clientes.beg);
							//cout<<"SIZE-->"<<archivo_clientes.tellg()<<endl;
							Clients client_toprint;
							archivo_clientes.read(reinterpret_cast<char*>(&client_toprint),sizeof(client_toprint));
							//cout<<client_toprint.posicion<<endl;
							archivo_clientes.close();
							ofstream archivo_cli_mod("clients.bin",ofstream::binary);
							cout<<"ID: "<<client_toprint.ID<<endl;
							cout<<"Name: "<<client_toprint.name<<endl;
							cout<<"Gender: "<<client_toprint.gender<<endl;
							cout<<"CityID: "<<client_toprint.cityID<<endl;
							char[40] client_newname;
							cout<<"New Name >>";
							cin>>client_newname;
							cout<<endl;
							char client_newgender;
							cout<<"New Gender >>";
							cin>>client_newgender;
							//archivo_cli_mod.write(reinterpret_cast<char*>(&client_head),sizeof(client_head));
							archivo_cli_mod.seekp(((pos-1)*client_head.size)+8, archivo_cli_mod.beg);
							archivo_cli_mod.write(reinterpret_cast<char*>(&client_toprint),sizeof(client_toprint));
							archivo_cli_mod.close();
						}
					};
					break;
				}//fin swwitch
			};//fin case clients
			break;
			case 2:{
				ifstream file("lines.bin", ifstream::binary);
				Lines lines;
				if (file.fail()){
					cout<<"No se pudo abrir el archivo!"<<endl;
				}
				int option=menu();
				switch (option){
					case 1:{

					};// end case create
					break;
					case 2:{
						cout<<"List of Lines: "<<endl;

						while(file.read(reinterpret_cast<char*>(&lines), sizeof(lines))){
							if (lines.available==false){
								cout<<"Number: "<<lines.number<<endl;
								cout<<"ID: "<<lines.ID<<endl;
								cout<<endl;
						}//fin if
					}//fin while
					file.close();

					};// end case read
					break;
					case 3:{

					};// end case update
					break;
					case 4:{

					};//end case delete 
				};		
			};//fin case lines
			break;
			case 3:{
				ifstream file("cities.bin", ifstream::binary);
				Cities cities;
				if (file.fail()){
					cout<<"No se pudo abrir el archivo!"<<endl;
				}
				int option=menu();
				switch (option){
					case 1:{

					};// end case create
					break;
					case 2:{
						cout<<"List of Cities: "<<endl;
						while(file.read(reinterpret_cast<char*>(&cities), sizeof(cities))){
							if (cities.available==false){
								cout<<"Name: "<<cities.CityName<<endl;
								cout<<"ID: "<<cities.IDCity<<endl;
								cout<<endl;
							}//fin if
						}//fin while
						file.close();

					};// end case read
					break;
					case 3:{

					};// end case update
					break;
					case 4:{

					};//end case delete 
				};
			};// fin case cities
		};
	}while(opcion < 4);
	return 0;
}// end main

int opciones (){
	int options;
	cout<<"Options: "<<endl;
	cout<<"1. Clients."<<endl;
	cout<<"2. Lines."<<endl;
	cout<<"3. Cities."<<endl;
	cout<<"9. Exit."<<endl;
	cout<<"Write your option: ";
	cin>>options;
	cout<<endl;
	if(options > 3){
		options = 9;
	}
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
	}while(options>4||options<1);
	return options;
}

int binary_insertion( vector<long> list, long element){
	int min = 0; 
	int max = list.size() - 1;
	if(element > list.at(max)){
		return max;
	}else if(element < list.at(min)){
		return min;
	}
	while(min<=max){
		int half = (max+min)/2;
		if(list.at(half) < element){
			min = half;
		}else{
			max = half;
		}
		if(max - min == 1){
			return min;
		}
	}
}

int binary_search(vector<long> list, long element){
	int min = 0; 
	int max = list.size() - 1;
	while(min<=max){
		int half = (max+min)/2;
		if(list.at(half) == element){
			cout<<list.at(half)<<endl;
			return half;
		}
		if(list.at(half) < element){
			min = half + 1;
		}else{
			max = half - 1;
		}
	}
	return -1;
}