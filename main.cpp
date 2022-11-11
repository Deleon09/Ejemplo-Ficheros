#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>

using namespace std;

//Estructura de cada nodo de la lista
struct Nodo{
    string nombre;
    string apellido;
    string cedula;
    Nodo *siguiente;
};

//Inicializamos la lista vacia
Nodo *pInicio;

//------FUNCIONES PARA MANIPULAR LISTAS------

//Funcion que inserta un nuevo nodo en la lista
void insertarFinal(string nom, string ape, string ced){
    Nodo *NodoN = new Nodo();
    
    NodoN->nombre = nom;
    NodoN->apellido = ape;
    NodoN->cedula = ced;
    NodoN->siguiente = NULL;

    if(pInicio==NULL){
        pInicio = NodoN;
    }

    else {
        Nodo *p = pInicio;
        Nodo *q = NULL;
        while(p!=NULL){
            q=p;
            p=p->siguiente;
        }
        q->siguiente = NodoN;
    }

}

//Funcion que muestra todas las personas en la lista
void mostrar(){
    Nodo *s = pInicio;

	if(s==NULL){
		cout<<"La lista esta vacia.\n";
		return;
	}

    cout<<"Listado de personas: \n";
    while(s!=NULL){
    	cout<<s->nombre<<" "<<s->apellido<<" "<<s->cedula<<"\n";    
    	s=s->siguiente;
    }
    
    cout<<endl;
}

//------FUNCIONES DEL PROGRAMA------

//Funcion que imprime el menu, a la vez pide y retorna un numero ingresado por el usuario
int menu(){
	int x;
	cout<<"<<------Bienvenido------>>"<<endl<<endl;
	cout<<"1. Agregar Persona:"<<endl;
	cout<<"2. Ver Personas:"<<endl;
	cout<<"3. Salir."<<endl;
	cout<<"Opcion ";
	cin>>x;
	cout<<endl;
	return x;
}

//Funcion que lee los registros guardados en el archivo "Personas.txt" y los inserta en la pila
//NOTA: Para que el programa funcione como se espera el archivo "main.cpp" y el archivo 
//      "Personas.txt" deben de estar en la misma carpeta
void init(){
	
	ifstream leer("Personas.txt", ios::in);
	string Nom;
	string Ced;
	string Ape;
	
	leer>>Nom;
	while(!leer.eof()){ //Leer el archivo hasta el final
		leer>>Ape;
		leer>>Ced;
		
		insertarFinal(Nom, Ape, Ced);
		leer>>Nom;
	}
	
	leer.close();
	
}

//Funcion que verifica si ya existe una persona con la misma cedula
//NOTA: retorna true si no se encontro ninguna persona con la misma cedula
//      caso contrario retorna false
bool verifica(string ced){
	ifstream leer("Personas.txt", ios::in);
	string Nom;
	string Ced;
	string Ape;
	
	leer>>Nom;
	
	while(!leer.eof()){ //Leer el archivo hasta el final
		leer>>Ape;
		leer>>Ced;
		if(Ced == ced){
			leer.close();
			return false;
		}
		leer>>Nom;
	}
	
	leer.close();
	return true;
}

//Funcion que solicita los datos de la persona y a la vez
//inserta en el archivo y en la lista
void agregar(ofstream &es){
	system("cls");
	string Nom;
	string Ced;
	string Ape;
	
	es.open("Personas.txt", ios::out | ios::app); 
	cout<<"Nombre: "; cin>>Nom;
	cout<<"Apellido: "; cin>>Ape;
	cout<<"Cedula: "; cin>>Ced;
	
	if(verifica(Ced)){
		es<<Nom<<" "<<Ape<<" "<<Ced<<"\n";
		insertarFinal(Nom, Ape, Ced);	
	}
		
	es.close();
}

int main(int argc, char** argv) {
	
	ofstream Esc;
	int opc;
	
	init(); //Al llamar esta funcion se recuperan los datos desde el archivo "Personas.txt" y se insertan en la lista
	
	do{
		opc = menu();
		switch(opc){
			case 1:
				agregar(Esc);
				break;
			case 2: 
				mostrar();
				break;
			case 3: 
				cout<<"Saliendo...";
				break;
			default: 
				break;
		}
		
	}while(opc != 3);
	
	return 0;
}
