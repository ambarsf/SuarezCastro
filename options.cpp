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

struct Indice_City{
	unsigned int RRN;
	char Llave[5];
};

int binary_insertion( vector<long>, long);
int binary_search(vector<long>, long);
int binary_search_int(vector<int>, int);

int main (int argc, char* argv[]){	
	srand(time(0));
	int cont_ID;
	int opcion;
	int contador_lines = 0;
	ifstream fileId_r ("rpn.txt", ifstream::binary);
	do{
		opcion = opciones();
		switch(opcion){
			case 1:{
				int option=menu();
				switch (option){
					case 1:{
						//cout<<"CONT_ID--->"<<cont_ID<<endl;
						ifstream filetmp("clients.bin",ifstream::binary);
						filetmp.seekg(0,filetmp.end);
						cont_ID = filetmp.tellg();
						cont_ID = ((cont_ID-8)/68);
						filetmp.close();
						ofstream file_cli_create("clients.bin",ios::app|ofstream::binary);
						Clients append_client;
						char tempid[14];
						ifstream fileId ("Id.txt");
						fileId.seekg((14*cont_ID),ios::beg);
						fileId.getline(tempid,sizeof(tempid));
						fileId.close();
						//cont_ID++;
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
						//cout<<"DONE"<<endl;
						ifstream ind_cli("Ind_Clients.bin", ifstream::binary);
						Indice ind1;
						vector<long> Indices_cl;
						//vector<charast> Indices_allcl;
						vector<Indice> Ind_cl_toadd;
						while(ind_cli.read(reinterpret_cast<char*>(&ind1), sizeof(ind1))){
							Indices_cl.push_back(atol(ind1.Llave));
							Ind_cl_toadd.push_back(ind1);
						}
						ind_cli.close();
						int insert_pos = binary_insertion(Indices_cl,Id_toadd);
						Indices_cl.insert(Indices_cl.begin() + insert_pos, Id_toadd);
						Indice a_agregar;
						strcpy(a_agregar.Llave,append_client.ID);
						a_agregar.RRN = cont_ID;
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
							//cout<<head.avail<<endl;
							//int cont = 0;
							while(file_cli.read(reinterpret_cast<char*>(&client), sizeof(client))){
								if(client.available != true){
									cout<<"ID: "<<client.ID<<endl;
									cout<<"Name: "<<client.name<<endl;
									cout<<"Gender: "<<client.gender<<endl;
									cout<<"CityID: "<<client.cityID<<endl;
									//cout<<"POS -->"<<client.posicion<<endl;
								}
								//cont++;
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
							if(position < 0){
								cout<<"No existe."<<endl;
								break;
							}
							int pos = rrn_clientes.at(position);
							//cout<<"POS"<<pos<<endl;
							if(pos == -1){
								cout<<"No match"<<endl;
							}else{
								ifstream archivo_clientes("clients.bin", ifstream::binary);
								Header client_head;
								archivo_clientes.read(reinterpret_cast<char*>(&client_head),sizeof(client_head));
								archivo_clientes.seekg(((pos-1)*client_head.size)+8, archivo_clientes.beg);
								Clients client_toprint;
								//cout<<"AQUI--->"<<client_head.avail<<endl;
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
					};// end case read
					break;
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
						if(position < 0){
							cout<<"No existe."<<endl;
							break;
						}
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
							//cout<<"ANTES--->"<<donde<<endl;
							while(donde != -1){
								if(donde != -1){
									pos_anterior = donde;
								}
								archivo_clientes.seekg((donde*client_head.size)+8,archivo_clientes.beg);
								archivo_clientes.read(reinterpret_cast<char*>(&temporal),sizeof(temporal));
								donde = temporal.posicion;
								//cout<<donde;
							}
							//cout<<donde<<endl;
							archivo_clientes.close();
							fstream upavail_cl("clients.bin",fstream::binary|ios::out|ios::in);
							//cout<<"POS.--->"<<pos_anterior<<endl;
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
							//cout<<client_toprint.ID<<endl;
							//cout<<client_toprint.posicion<<endl;
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
						if(position < 0){
							cout<<"No existe."<<endl;
							break;
						}
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
							cout<<endl;
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
				int option=menu();
				switch (option){
					case 1:{
						int cont_ID_line;
						ifstream filetmp_line("lines.bin",ifstream::binary);
						filetmp_line.seekg(0,filetmp_line.end);
						cont_ID_line = filetmp_line.tellg();
						cont_ID_line = ((cont_ID_line-8)/sizeof(Lines))+1;
						filetmp_line.close();
						int cont_cli;
						ifstream filetmp_cli("clients.bin",ifstream::binary);
						filetmp_cli.seekg(0,filetmp_cli.end);
						cont_cli = filetmp_cli.tellg();
						cont_cli = ((cont_cli-8)/sizeof(Clients))+1;	
						filetmp_cli.close();
						if(cont_ID_line < cont_cli){						
							ofstream file_line_create("lines.bin",ios::app|ofstream::binary);
							Lines append_line;
							char tempid[14];
							ifstream fileId ("Ind_Clients.bin",ifstream::binary);
							cout<<cont_ID_line<<">>>"<<endl;
							vector<Indice> vec_ID_cl;
							Indice i_cl_tmp;
							while(fileId.read(reinterpret_cast<char*>(&i_cl_tmp),sizeof(i_cl_tmp))){
								vec_ID_cl.push_back(i_cl_tmp);
							}
							//fileId.seekg((14*cont_ID_line),ios::beg);
							//fileId.getline(tempid,sizeof(tempid));
							int max = vec_ID_cl.size();
							cout<<"MAX--->"<<max<<endl;
							int random = rand() % max + 0;
							strcpy(tempid,vec_ID_cl.at(random).Llave);
							fileId.close();
							char tmpnum[11];
							//fileId_r.seekg(8*cont_ID_line,ios::end);
							//contador_lines++;
							contador_lines = fileId_r.tellg();
							fileId_r.seekg(contador_lines,fileId_r.beg);
							fileId_r.getline(tmpnum,sizeof(tmpnum));
							
							strcpy(append_line.ID,tempid);
							cout<<endl;
							strcpy(append_line.number,tmpnum);
							//cout<<"Number >>";
							//cin>>append_line.number;
							cout<<endl;
							long Id_toadd = atol(append_line.number);
							append_line.posicion = -4; 
							file_line_create.write(reinterpret_cast<char*>(&append_line), sizeof(append_line));
							file_line_create.close();
							//cout<<"DONE"<<endl;
							ifstream ind_line("Ind_lines.bin", ifstream::binary);
							Indice ind1;
							vector<long> Indices_lin;
							//vector<charast> Indices_allcl;
							vector<Indice> Ind_lin_toadd;
							while(ind_line.read(reinterpret_cast<char*>(&ind1), sizeof(ind1))){
								Indices_lin.push_back(atol(ind1.Llave));
								Ind_lin_toadd.push_back(ind1);
							}
							ind_line.close();
							int insert_pos = binary_insertion(Indices_lin,Id_toadd);
							Indices_lin.insert(Indices_lin.begin() + insert_pos, Id_toadd);
							Indice a_agregar;
							strcpy(a_agregar.Llave,append_line.ID);
							a_agregar.RRN = cont_ID_line+1;
							Ind_lin_toadd.insert(Ind_lin_toadd.begin() + insert_pos, a_agregar);
							//cout<<"DESPUES"<<endl;
							ofstream update_Ind_lin("Ind_lines.bin", ofstream::binary);
							//Ind_cl_toadd.push_back(a_agregar);
							//cout<<Indices_allcl.size()<<"-------"<<Ind_cl_toadd.size(); 
							for (int i = 0; i < Ind_lin_toadd.size(); i++){
								//if(atol(Ind_cl_toadd.at(i).Llave) == atol(Indices_allcl.at(i).id)){
									Indice Ind;
									strcpy(Ind.Llave,Ind_lin_toadd.at(i).Llave);
									Ind.RRN = Ind_lin_toadd.at(i).RRN;
									//cout<<"RRN-->"<<Ind.RRN<<endl;
									update_Ind_lin.write(reinterpret_cast<char*>(&Ind), sizeof(Ind));	
								//}
							}
							update_Ind_lin.close();
							cout<<"Created!"<<endl;
						}else{
							cout<<"Impossible to create"<<endl;
						}
					};// end case create
					break;
					case 2:{
						int decision = 0;
						cout<<"1.Show All"<<endl<<"2.Show by Number"<<endl;
						cout<<">>";
						cin>>decision;
						if(decision == 1){
							Header head;
							ifstream file_lin("lines.bin", ifstream::binary);
							Lines line;
							cout<<"List of Lines: "<<endl;
							file_lin.read(reinterpret_cast<char*>(&head), sizeof(head));
							//cout<<head.avail<<endl;
							//int cont = 0;
							while(file_lin.read(reinterpret_cast<char*>(&line), sizeof(line))){
								if(line.available != true){
								cout<<"Client ID: "<<line.ID<<endl;
								cout<<"Number: "<<line.number<<endl;
								}
								//cont++;
							}//fin while

							file_lin.close();
						}else{
							char id_toseek[11];
							cout<<"Number to seek >>";
							cin>>id_toseek;
							ifstream llaves_lin("Ind_lines.bin",ifstream::binary);
							vector<long> llaves_lines;
							vector<int> rrn_lines;
							Indice ind_lin1;
							while(llaves_lin.read(reinterpret_cast<char*>(&ind_lin1),sizeof(ind_lin1))){
								llaves_lines.push_back(atol(ind_lin1.Llave));
								rrn_lines.push_back(ind_lin1.RRN);
							}
							llaves_lin.close();
							int position = binary_search(llaves_lines, atol(id_toseek));
							if(position < 0){
								cout<<"No existe."<<endl;
								break;
							}
							int pos = rrn_lines.at(position);
							//cout<<"POS"<<rrn_lines.at(position)<<endl;
							if(pos == -1){
								cout<<"No match"<<endl;
							}else{
								ifstream archivo_lines("lines.bin", ifstream::binary);
								Header line_head;
								archivo_lines.read(reinterpret_cast<char*>(&line_head),sizeof(line_head));
								archivo_lines.seekg(((pos-1)*line_head.size)+sizeof(line_head), archivo_lines.beg);
								Lines line_toprint;
								//cout<<"AQUI--->"<<line_head.size<<endl;
								archivo_lines.read(reinterpret_cast<char*>(&line_toprint),sizeof(line_toprint));
								vector<long> Llave_cl;
								vector<Indice> All_keyscl;
								ifstream ind_cl("Ind_Clients.bin", ifstream::binary);
								Indice i_cl;
								while(ind_cl.read(reinterpret_cast<char*>(&i_cl),sizeof(i_cl))){
									Llave_cl.push_back(atol(i_cl.Llave));
									//cout<<atol(i_cl.Llave)<<endl;
									All_keyscl.push_back(i_cl);
								}
								ind_cl.close();
								//cout<<line_toprint.ID<<"<<<ID<<"<<endl;;
								int seek = binary_search(Llave_cl,atol(line_toprint.ID));
								//cout<<seek<<"<<<<<"<<endl;
								int toseek = All_keyscl.at(seek).RRN;
								ifstream client_seek("clients.bin", ifstream::binary);
								client_seek.seekg(((toseek-1)*sizeof(Clients))+8, client_seek.beg);
								//cout<<toseek<<"<----SEEK"<<endl;
								Clients cl_1;
								//cout<<"----><--->>"<<cl_1.ID<<endl;
								client_seek.read(reinterpret_cast<char*>(&cl_1),sizeof(cl_1));
								if(line_toprint.available != true){
									cout<<"ID: "<<cl_1.ID<<endl;
									cout<<"Number: "<<line_toprint.number<<endl;
									cout<<"Name: "<<cl_1.name<<endl;
									cout<<"Gender: "<<cl_1.gender<<endl;
									cout<<"CityID: "<<cl_1.cityID<<endl;
									cout<<endl;
								}else{
									cout<<"No Match"<<endl;
								}
								client_seek.close();
								archivo_lines.close();
							}
						}

					};// end case read
					break;
					case 3:{
						char id_toseek[14];
						cout<<"Number to seek >>";
						cin>>id_toseek;
						ifstream llaves_lin("Ind_lines.bin",ifstream::binary);
						vector<long> llaves_lines;
						vector<int> rrn_lines;
						Indice ind_line1;
						while(llaves_lin.read(reinterpret_cast<char*>(&ind_line1),sizeof(ind_line1))){
							llaves_lines.push_back(atol(ind_line1.Llave));
							rrn_lines.push_back(ind_line1.RRN);
						}
						llaves_lin.close();
						int position = binary_search(llaves_lines, atol(id_toseek));
						if(position < 0){
							cout<<"No existe."<<endl;
							break;
						}
						int pos = rrn_lines.at(position);
						//cout<<"POS-->"<<pos<<endl;
						ifstream archivo_lines("lines.bin", ifstream::binary);
						Header line_head;
						archivo_lines.read(reinterpret_cast<char*>(&line_head),sizeof(line_head));
						archivo_lines.seekg(((pos-1)*line_head.size)+8, archivo_lines.beg);
						Lines line_toprint;
						archivo_lines.read(reinterpret_cast<char*>(&line_toprint),sizeof(line_toprint));
						if(line_head.avail != -1){
							int donde = line_head.avail;
							Lines temporal;
							int pos_anterior = 0;
							//cout<<"ANTES--->"<<donde<<endl;
							while(donde != -1){
								if(donde != -1){
									pos_anterior = donde;
								}
								archivo_lines.seekg((donde*line_head.size)+8,archivo_lines.beg);
								archivo_lines.read(reinterpret_cast<char*>(&temporal),sizeof(temporal));
								donde = temporal.posicion;
								//cout<<donde;
							}
							//cout<<donde<<endl;
							archivo_lines.close();
							fstream upavail_lin("lines.bin",fstream::binary|ios::out|ios::in);
							//cout<<"POS.--->"<<pos_anterior<<endl;
							temporal.posicion = (pos-1);
							line_toprint.available = true;
							line_toprint.posicion = -1;
							cout<<temporal.posicion<<endl;
							upavail_lin.seekp((pos_anterior * line_head.size)+8,upavail_lin.beg);
							upavail_lin.write(reinterpret_cast<char*>(&temporal),sizeof(temporal));
							upavail_lin.seekp(((pos-1)*line_head.size)+8, upavail_lin.beg);	
							upavail_lin.write(reinterpret_cast<char*>(&line_toprint),sizeof(line_toprint));
							upavail_lin.close();
							//archivo_clientes.close();
						}else{
							archivo_lines.close();
							fstream archivo_lin_mod("lines.bin",fstream::binary|ios::out|ios::in);
							line_head.avail = (pos-1);
							line_toprint.available = true;
							line_toprint.posicion = -1;
							//cout<<client_toprint.ID<<endl;
							//cout<<client_toprint.posicion<<endl;
							archivo_lin_mod.write(reinterpret_cast<char*>(&line_head),sizeof(line_head));
							archivo_lin_mod.seekp(((pos-1)*line_head.size)+8, archivo_lin_mod.beg);
							archivo_lin_mod.write(reinterpret_cast<char*>(&line_toprint),sizeof(line_toprint));
							archivo_lin_mod.close();
							//archivo_clientes.close();
						}
					};// end case delete
					break;
					case 4:{
						cout<<"Unable to modify"<<endl;
					};//end case update 
				};		
			};//fin case lines
			break;
			case 3:{
				//int option=menu();
				switch (menu()){
					case 1:{
						int cont_ID_city;
						ifstream filetmp_city("cities.bin",ifstream::binary);
						filetmp_city.seekg(0,filetmp_city.end);
						cont_ID_city = filetmp_city.tellg();
						cont_ID_city = ((cont_ID_city-8)/sizeof(Cities));
						filetmp_city.close();						
						ofstream file_city_create("cities.bin",ios::app|ofstream::binary);
						Cities append_city;
						char tempid[4];
						ifstream fileId ("CityID.txt");
						fileId.seekg((4*cont_ID_city),ios::beg);
						//cout<<"POS"<<fileId.tellg()<<endl;
						fileId.getline(tempid,sizeof(tempid));
						fileId.close();
						strcpy(append_city.IDCity,tempid);
						cout<<endl;
						cout<<"Name >>";
						cin>>append_city.CityName;
						long Id_toadd = atol(append_city.IDCity);
						append_city.posicion = -4; 
						file_city_create.write(reinterpret_cast<char*>(&append_city), sizeof(append_city));
						file_city_create.close();
							//cout<<"DONE"<<endl;
						ifstream ind_city("indice_city.bin", ifstream::binary);
						Indice_City ind1;
						vector<long> Indices_city;
							//vector<charast> Indices_allcl;
						vector<Indice_City> Ind_city_toadd;
						while(ind_city.read(reinterpret_cast<char*>(&ind1), sizeof(ind1))){
							Indices_city.push_back(atol(ind1.Llave));
							Ind_city_toadd.push_back(ind1);
						}
						ind_city.close();
						int insert_pos = binary_insertion(Indices_city,Id_toadd);
						Indices_city.insert(Indices_city.begin() + insert_pos, Id_toadd);
						Indice_City a_agregar;
						strcpy(a_agregar.Llave,append_city.IDCity);
						a_agregar.RRN = cont_ID_city+1;
						Ind_city_toadd.insert(Ind_city_toadd.begin() + insert_pos, a_agregar);
							//cout<<"DESPUES"<<endl;
						ofstream update_Ind_city("indice_city.bin", ofstream::binary);
							//Ind_cl_toadd.push_back(a_agregar);
							//cout<<Indices_allcl.size()<<"-------"<<Ind_cl_toadd.size(); 
						for (int i = 0; i < Ind_city_toadd.size(); i++){
								//if(atol(Ind_cl_toadd.at(i).Llave) == atol(Indices_allcl.at(i).id)){
							Indice_City Ind;
							strcpy(Ind.Llave,Ind_city_toadd.at(i).Llave);
							Ind.RRN = Ind_city_toadd.at(i).RRN;
									//cout<<"RRN-->"<<Ind.RRN<<endl;
							update_Ind_city.write(reinterpret_cast<char*>(&Ind), sizeof(Ind));	
								//}
						}
						update_Ind_city.close();
						cout<<"Created!"<<endl;
					}// end case create
					break;
					case 2:{
						int decision = 0;
						cout<<"1.Show All"<<endl<<"2.Show by ID"<<endl;
						cin>>decision;
						if(decision == 1){
							Header head;
							ifstream file_city("cities.bin", ifstream::binary);
							Cities city;
							cout<<"List of Cities: "<<endl;
							file_city.read(reinterpret_cast<char*>(&head), sizeof(head));
							//cout<<head.avail<<endl;
							//int cont = 0;
							while(file_city.read(reinterpret_cast<char*>(&city), sizeof(city))){
								if(city.available != true){
									cout<<"City ID: "<<city.IDCity<<endl;
									cout<<"Name: "<<city.CityName<<endl;
									//cout<<"POS -->"<<client.posicion<<endl;
								}
								//cont++;
							}//fin while

							file_city.close();
						}else{
							char id_toseek[14];
							cout<<"ID to seek >>";
							cin>>id_toseek;
							ifstream llaves_cities("indice_city.bin",ifstream::binary);
							vector<int> llaves_city;
							vector<int> rrn_city;
							Indice_City ind_city1;
							while(llaves_cities.read(reinterpret_cast<char*>(&ind_city1),sizeof(ind_city1))){
								llaves_city.push_back(atoi(ind_city1.Llave));
								rrn_city.push_back(ind_city1.RRN);
							}
							llaves_cities.close();
							int position = binary_search_int(llaves_city, atoi(id_toseek));
							if(position < 0){
								cout<<"No existe."<<endl;
								break;
							}
							int pos = rrn_city.at(position);
							//cout<<"POS"<<pos<<endl;
							if(pos == -1){
								cout<<"No match"<<endl;
							}else{
								ifstream archivo_city("cities.bin", ifstream::binary);
								Header city_head;
								archivo_city.read(reinterpret_cast<char*>(&city_head),sizeof(city_head));
								archivo_city.seekg(((pos-1)*city_head.size)+8, archivo_city.beg);
								Cities city_toprint;
								//cout<<"AQUI--->"<<client_head.avail<<endl;
								archivo_city.read(reinterpret_cast<char*>(&city_toprint),sizeof(city_toprint));
								if(city_toprint.available != true){
									cout<<"ID: "<<city_toprint.IDCity<<endl;
									cout<<"Name: "<<city_toprint.CityName<<endl;
									cout<<endl;
								}else{
									cout<<"No Match"<<endl;
								}
								archivo_city.close();
							}
						}
					}
					break;
					case 3:{
						char id_toseek[14];
						cout<<"ID to seek >>";
						cin>>id_toseek;
						ifstream llaves_cities("indice_city.bin",ifstream::binary);
						vector<int> llaves_city;
						vector<int> rrn_city;
						Indice_City ind_city1;
						while(llaves_cities.read(reinterpret_cast<char*>(&ind_city1),sizeof(ind_city1))){
							llaves_city.push_back(atoi(ind_city1.Llave));
							rrn_city.push_back(ind_city1.RRN);
							//cout<<ind_city1.Llave<<endl;
						}
						llaves_cities.close();
						//cout<<"---->"<<atol(id_toseek)<<endl;
						int position = binary_search_int(llaves_city, atoi(id_toseek));
						if(position < 0){
							cout<<"No existe."<<endl;
							break;
						}
						int pos = rrn_city.at(position);
						//cout<<"POS-->"<<pos<<endl;
						ifstream archivo_city("cities.bin", ifstream::binary);
						Header city_head;
						archivo_city.read(reinterpret_cast<char*>(&city_head),sizeof(city_head));
						archivo_city.seekg(((pos-1)*city_head.size)+8, archivo_city.beg);
						Cities city_toprint;
						archivo_city.read(reinterpret_cast<char*>(&city_toprint),sizeof(city_toprint));
						if(city_head.avail != -1){
							int donde = city_head.avail;
							Cities temporal;
							int pos_anterior = 0;
							//cout<<"ANTES--->"<<donde<<endl;
							while(donde != -1){
								if(donde != -1){
									pos_anterior = donde;
								}
								archivo_city.seekg((donde*city_head.size)+8,archivo_city.beg);
								archivo_city.read(reinterpret_cast<char*>(&temporal),sizeof(temporal));
								donde = temporal.posicion;
								//cout<<donde;
							}
							//cout<<donde<<endl;
							archivo_city.close();
							fstream upavail_city("cities.bin",fstream::binary|ios::out|ios::in);
							//cout<<"POS.--->"<<pos_anterior<<endl;
							temporal.posicion = (pos-1);
							city_toprint.available = true;
							city_toprint.posicion = -1;
							cout<<temporal.posicion<<endl;
							upavail_city.seekp((pos_anterior * city_head.size)+8,upavail_city.beg);
							upavail_city.write(reinterpret_cast<char*>(&temporal),sizeof(temporal));
							upavail_city.seekp(((pos-1)*city_head.size)+8, upavail_city.beg);	
							upavail_city.write(reinterpret_cast<char*>(&city_toprint),sizeof(city_toprint));
							upavail_city.close();
							//archivo_clientes.close();
						}else{
							archivo_city.close();
							fstream archivo_city_mod("cities.bin",fstream::binary|ios::out|ios::in);
							city_head.avail = (pos-1);
							city_toprint.available = true;
							city_toprint.posicion = -1;
							//cout<<client_toprint.ID<<endl;
							//cout<<client_toprint.posicion<<endl;
							archivo_city_mod.write(reinterpret_cast<char*>(&city_head),sizeof(city_head));
							archivo_city_mod.seekp(((pos-1)*city_head.size)+8, archivo_city_mod.beg);
							archivo_city_mod.write(reinterpret_cast<char*>(&city_toprint),sizeof(city_toprint));
							archivo_city_mod.close();
							//archivo_clientes.close();
						}
						cout<<"Eliminado"<<endl;
					}// end case update
					break;
					case 4:{
						char id_toseek[14];
						cout<<"ID to seek >>";
						cin>>id_toseek;
						ifstream llaves_cities("indice_city.bin",ifstream::binary);
						vector<int> llaves_city;
						vector<int> rrn_city;
						Indice ind_city1;
						while(llaves_cities.read(reinterpret_cast<char*>(&ind_city1),sizeof(ind_city1))){
							llaves_city.push_back(atoi(ind_city1.Llave));
							rrn_city.push_back(ind_city1.RRN);
						}
						llaves_cities.close();
						int position = binary_search_int(llaves_city, atoi(id_toseek));
						if(position < 0){
							cout<<"No existe."<<endl;
							break;
						}
						int pos = rrn_city.at(position);
						if(pos == -1){
							cout<<"No match"<<endl;
						}else{
							//cout<<"POS-->"<<pos<<endl;
							ifstream archivo_city("cities.bin", ifstream::binary);
							Header city_head;
							archivo_city.read(reinterpret_cast<char*>(&city_head),sizeof(city_head));
							archivo_city.seekg(((pos-1)*city_head.size)+8, archivo_city.beg);
							Cities city_toprint;
							archivo_city.read(reinterpret_cast<char*>(&city_toprint),sizeof(city_toprint));
							archivo_city.close();
							fstream archivo_city_mod("cities.bin",fstream::binary|ios::out|ios::in);
							cout<<endl;
							cout<<"ID: "<<city_toprint.IDCity<<endl;
							cout<<"Name: "<<city_toprint.CityName<<endl;
							char city_newname[40];
							cout<<"New Name >>";
							cin>>city_newname;
							cout<<endl;
							Cities toadd;
							strcpy(toadd.IDCity,city_toprint.IDCity);
							strcpy(toadd.CityName,city_newname);
							archivo_city_mod.seekp(((pos-1)*city_head.size)+8, archivo_city_mod.beg);
							//cout<<archivo_cli_mod.tellp()<<endl;
							archivo_city_mod.write(reinterpret_cast<char*>(&toadd),sizeof(toadd));
							archivo_city_mod.close();
						}
					}//end case delete 
					break;
				};
			};// fin case cities
			break;
		};
	}while(opcion < 4);
	fileId_r.close();
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
			return half;
		}
		else if(list.at(half) < element){
			min = half + 1;
		}else{
			max = half - 1;
		}	
	}
	for (int i = 0; i < list.size(); i++){
		if(list.at(i) == element){
			return i;
		}
	}
	return -1;
}

int binary_search_int(vector<int> list, int element){
	int min = 0; 
	int max = list.size() - 1;
	while(min<=max){
		int half = (max+min)/2;
		if(list.at(half) == element){
			//cout<<list.at(half)<<endl;
			return half;
		}
		else if(list.at(half) < element){
			min = half + 1;
		}else{
			max = half - 1;
		}
	}
	for (int i = 0; i < list.size(); i++){
		if(list.at(i) == element){
			return i;
		}
	}
	return -1;
}