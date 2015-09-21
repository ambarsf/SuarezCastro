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
	int cont_ID;
	int opcion;
	ifstream filetmp("clients.bin",ifstream::binary);
	filetmp.seekg(0,filetmp.end);
	cont_ID = filetmp.tellg();
	cont_ID = ((cont_ID-8)/68)+1;
	filetmp.close();
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
						cout<<"CONT_ID--->"<<cont_ID<<endl;
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
						file_cli_create.close();
						cout<<"DONE"<<endl;
						ifstream ind_cli("Ind_Clients.bin", ifstream::binary);
						Indice ind1;
						vector<long> Indices_cl;
						//vector<charast> Indices_allcl;
						vector<Indice> Ind_cl_toadd;
						while(ind_cli.read(reinterpret_cast<char*>(&ind1), sizeof(ind1))){
							//cout<<ind1.RRN<<"   "<<ind1.Llave<<endl;
							Indices_cl.push_back(atol(ind1.Llave));
							//charast tmp;
							//strcpy(tmp.id,ind1.Llave);
							//Indices_allcl.push_back(tmp);
							Ind_cl_toadd.push_back(ind1);
						}
						for (int i = 0; i < Ind_cl_toadd.size(); i++){
							cout<<Ind_cl_toadd.at(i).Llave<<endl;
						}
						ind_cli.close();
						//cout<<"HOY SI DONE"<<endl;
						//cout<<Indices_cl.size()<<endl;
						int insert_pos = binary_insertion(Indices_cl,Id_toadd);
						Indices_cl.insert(Indices_cl.begin() + insert_pos, Id_toadd);
						//charast temp_charast;
						//strcpy(temp_charast.id,append_client.ID);
						//cout<<"ANTES"<<endl;
						Indice a_agregar;
						strcpy(a_agregar.Llave,append_client.ID);
						a_agregar.RRN = cont_ID+1;
						Ind_cl_toadd.insert(Ind_cl_toadd.begin() + insert_pos, a_agregar);
						//cout<<"DESPUES"<<endl;
						ofstream update_Ind_cli("Ind_Clients.bin", ofstream::binary);
						//Ind_cl_toadd.push_back(a_agregar);
						//cout<<Indices_allcl.size()<<"-------"<<Ind_cl_toadd.size(); 
						for (int i = 0; i < Ind_cl_toadd.size(); i++){
							//if(atol(Ind_cl_toadd.at(i).Llave) == atol(Indices_allcl.at(i).id)){
								Indice Ind;
								strcpy(Ind.Llave,Ind_cl_toadd.at(i).Llave);
								Ind.RRN = Ind_cl_toadd.at(i).RRN;
								//cout<<"RRN-->"<<Ind.RRN<<endl;
								update_Ind_cli.write(reinterpret_cast<char*>(&Ind), sizeof(Ind));	
							//}
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
							int cont = 0;
							while(file_cli.read(reinterpret_cast<char*>(&client), sizeof(client))){
								if(client.available == true){
								cout<<"ID: "<<client.ID<<endl;
								cout<<"Name: "<<client.name<<endl;
								cout<<"Gender: "<<client.gender<<endl;
								cout<<"CityID: "<<client.cityID<<endl;
								cout<<"POS -->"<<client.posicion<<endl;
								}
								cont++;
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
							cout<<"POS"<<pos<<endl;
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
								cout<<"AQUI--->"<<client_head.avail<<endl;
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
						//cout<<"POS-->"<<pos<<endl;
						ifstream archivo_clientes("clients.bin", ifstream::binary);
						Header client_head;
						archivo_clientes.read(reinterpret_cast<char*>(&client_head),sizeof(client_head));
						archivo_clientes.seekg(((pos-1)*client_head.size)+8, archivo_clientes.beg);
						Clients client_toprint;
						archivo_clientes.read(reinterpret_cast<char*>(&client_toprint),sizeof(client_toprint));
						if(client_head.avail != -1){
							int donde = client_head.avail;
							Clients temporal;
							int pos_anterior = 0;
							cout<<"ANTES--->"<<donde<<endl;
							while(donde != -1){
								if(donde != -1){
									pos_anterior = donde;
								}
								archivo_clientes.seekg((donde*client_head.size)+8,archivo_clientes.beg);
								archivo_clientes.read(reinterpret_cast<char*>(&temporal),sizeof(temporal));
								donde = temporal.posicion;
								cout<<donde;
							}
							cout<<donde<<endl;
							archivo_clientes.close();
							fstream upavail_cl("clients.bin",fstream::binary|ios::out|ios::in);
							cout<<"POS.--->"<<pos_anterior<<endl;
							temporal.posicion = (pos-1);
							client_toprint.available = true;
							client_toprint.posicion = -1;
							cout<<temporal.posicion<<endl;
							upavail_cl.seekp((pos_anterior * client_head.size)+8,upavail_cl.beg);
							upavail_cl.write(reinterpret_cast<char*>(&temporal),sizeof(temporal));
							upavail_cl.seekp(((pos-1)*client_head.size)+8, upavail_cl.beg);	
							upavail_cl.write(reinterpret_cast<char*>(&client_toprint),sizeof(client_toprint));
							upavail_cl.close();
							//archivo_clientes.close();
						}else{
							archivo_clientes.close();
							fstream archivo_cli_mod("clients.bin",fstream::binary|ios::out|ios::in);
							client_head.avail = (pos-1);
							client_toprint.available = true;
							client_toprint.posicion = -1;
							cout<<client_toprint.ID<<endl;
							cout<<client_toprint.posicion<<endl;
							archivo_cli_mod.write(reinterpret_cast<char*>(&client_head),sizeof(client_head));
							archivo_cli_mod.seekp(((pos-1)*client_head.size)+8, archivo_cli_mod.beg);
							archivo_cli_mod.write(reinterpret_cast<char*>(&client_toprint),sizeof(client_toprint));
							archivo_cli_mod.close();
							//archivo_clientes.close();
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
							archivo_clientes.seekg(((pos-1)*client_head.size)+8, archivo_clientes.beg);
							Clients client_toprint;
							archivo_clientes.read(reinterpret_cast<char*>(&client_toprint),sizeof(client_toprint));
							archivo_clientes.close();
							fstream archivo_cli_mod("clients.bin",fstream::binary|ios::out|ios::in);
							cout<<"ID: "<<client_toprint.ID<<endl;
							cout<<"Name: "<<client_toprint.name<<endl;
							cout<<"Gender: "<<client_toprint.gender<<endl;
							cout<<"CityID: "<<client_toprint.cityID<<endl;
							char client_newname[40];
							cout<<"New Name >>";
							cin>>client_newname;
							cout<<endl;
							char client_newgender;
							cout<<"New Gender >>";
							cin>>client_newgender;
							Clients toadd;
							strcpy(toadd.ID,client_toprint.ID);
							strcpy(toadd.name,client_newname);
							toadd.gender = client_newgender;
							strcpy(toadd.cityID,client_toprint.cityID);
							//archivo_cli_mod.write(reinterpret_cast<char*>(&client_head),sizeof(client_head));
							archivo_cli_mod.seekp(((pos-1)*client_head.size)+8, archivo_cli_mod.beg);
							//cout<<archivo_cli_mod.tellp()<<endl;
							archivo_cli_mod.write(reinterpret_cast<char*>(&toadd),sizeof(toadd));
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
	cout<<"3. Delete"<<endl;
	cout<<"4. Update"<<endl;
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