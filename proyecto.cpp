#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <ctime>
#include <stdio.h>
using namespace std;

struct Pasajero
{
    char NroVuelo[7];
    char cedula [10];
    char nombre[21];
    char telefono[11];
    int estado; //(1: reserva, 2: a bordo)
    Pasajero *sgte;
};typedef struct Pasajero *DatosPasajero;

struct Vuelo
{
    char NroVuelo [7];
    char Origen [9];
    char Destino [9];
    char MatriAvion [7];
    char NombPilo [21];
    char HoraVuelo [5];
    char fecha [7];
    int estado;
    struct Vuelo *sgte;
    struct Pasajero *ListaP = NULL;
};typedef struct Vuelo *DatosVuelo;

char cadena[20];

void leerArchivo(DatosVuelo &Vuelos)
{
    DatosVuelo aux;
    DatosPasajero aux2;
    char cadena[20];
    ifstream vuelosFile;
    vuelosFile.open("Vuelos.txt");
    if (vuelosFile.good())//verifica que se pudo abrir el archivo sin problema
	{
        while(!vuelosFile.eof())//mientras no sea el final del archivo
        {    
            aux = new(Vuelo);
            vuelosFile>>cadena;
            strcpy(aux->NroVuelo,cadena);
            fflush(stdin);
            vuelosFile>>cadena;
            strcpy(aux->Origen,cadena);
            fflush(stdin);
            vuelosFile>>cadena;
            strcpy(aux->Destino,cadena);
            fflush(stdin);
            vuelosFile>>cadena;
            strcpy(aux->MatriAvion,cadena);
            fflush(stdin);
            vuelosFile>>cadena;
            strcpy(aux->NombPilo,cadena);
            fflush(stdin);
            vuelosFile>>cadena;
            strcpy(aux->HoraVuelo,cadena);
            fflush(stdin);
            vuelosFile>>cadena;
            strcpy(aux->fecha,cadena);
            fflush(stdin);
            vuelosFile>>cadena;
	  	    aux->estado = atof(cadena);
	  	    aux->sgte = Vuelos;
	  	    Vuelos = aux;
        }
        vuelosFile.close();
        bool encontro = false;
        ifstream pasajerosFile;
        pasajerosFile.open("PASAJEROS.txt");
        if(pasajerosFile.good())
        {
            while(!pasajerosFile.eof())
            {
                aux2 = new(Pasajero);
                aux = Vuelos;
                pasajerosFile>>cadena;
                encontro = false;
                while(aux != NULL && encontro == false)
                {
                    if(strcmp(aux->NroVuelo,cadena) == 0)
                    {
                        encontro = true;
                        strcpy(aux2->NroVuelo,cadena);
                        fflush(stdin);
                        pasajerosFile>>cadena;
                        strcpy(aux2->cedula,cadena);
                        fflush(stdin);
                        pasajerosFile>>cadena;
                        strcpy(aux2->nombre,cadena);
                        fflush(stdin);
                        pasajerosFile>>cadena;
                        strcpy(aux2->telefono,cadena);
                        fflush(stdin);
                        pasajerosFile>>cadena;
	  	                aux2->estado = atoi(cadena);
                        aux2->sgte = aux->ListaP;
                        aux->ListaP = aux2;
                    }
                    aux = aux->sgte;
                }
            }
        }
        else
            cout<<"El archivo no se pudo abrir..."<<endl;
	}
	else
		cout<<"El archivo no se pudo abrir..."<<endl;
    return;
}

int main()
{
    DatosVuelo Vuelos = NULL;
    DatosPasajero Pasajeros = NULL;
    leerArchivo(Vuelos);


    cout<<Vuelos->NroVuelo<<endl;
    cout<<Vuelos->Origen<<endl;
    cout<<Vuelos->Destino<<endl;
    cout<<Vuelos->MatriAvion<<endl;
    cout<<Vuelos->NombPilo<<endl;
    cout<<Vuelos->HoraVuelo<<endl;
    cout<<Vuelos->fecha<<endl;
    return 0;
}