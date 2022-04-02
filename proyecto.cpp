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

void AdicionarVuelo(DatosVuelo &Vuelos)
{
    DatosVuelo aux;
    aux = new(Vuelo);

    cout<<"\nEscriba el numero del vuelo: ";
    cin>>cadena;
    while(strlen(cadena) != 6)
    {
        cout<<"\nEl numero de vuelo debe ser de 6 caracteres...";
        cout<<"\nEscriba el numero del vuelo: ";
        cin>>cadena;
    }
    strcpy(aux->NroVuelo,cadena);

    cout<<"\nEscriba el origen del vuelo: ";
    cin>>cadena;
    while(strlen(cadena) > 6 || strlen(cadena) < 1)
    {
        cout<<"\nEl origen del vuelo no puede tener mas de 6 caracteres...";
        cout<<"\nEscriba el origen del vuelo: ";
        cin>>cadena;
    }
    strcpy(aux->Origen,cadena);
    
    cout<<"\nEscriba el destino del vuelo: ";
    cin>>cadena;
    while(strlen(cadena) > 6 || strlen(cadena) < 1)
    {
        cout<<"\nEl destino del vuelo no puede tener mas de 6 caracteres...";
        cout<<"\nEscriba el destino del vuelo: ";
        cin>>cadena;
    }
    strcpy(aux->Destino,cadena);

    cout<<"\nEscriba la matricula del avion: ";
    cin>>cadena;
    while(strlen(cadena) > 6 || strlen(cadena) < 1)
    {
        cout<<"\nLa matricula del avion no puede tener mas de 6 caracteres...";
        cout<<"\nEscriba la matricula del avion: ";
        cin>>cadena;
    }
    strcpy(aux->MatriAvion,cadena);

    cout<<"\nEscriba el nombre del piloto: ";
    cin>>cadena;
    while(strlen(cadena) > 20 || strlen(cadena) < 1)
    {
        cout<<"\nMaximo 20 caracteres...";
        cout<<"\nEscriba el nombre del piloto";
        cin>>cadena;
    }
    strcpy(aux->NombPilo,cadena);

    cout<<"\nEscriba la hora del vuelo: ";
    cin>>cadena;
    while(strlen(cadena) != 4)
    {
        cout<<"\nLa hora debe tener 4 digitos...";
        cout<<"\nEscriba la hora del vuelo: ";
        cin>>cadena;
    }
    strcpy(aux->HoraVuelo,cadena);

    cout<<"\nEscriba la fecha del vuelo: ";
    cin>>cadena;
    while(strlen(cadena) != 6)
    {
        cout<<"\nLa fecha debe tener 6 digitos...";
        cout<<"\nEscriba la fecha del vuelo: ";
        cin>>cadena;
    }
    strcpy(aux->fecha,cadena);

    cout<<"\nEscriba el estado del vuelo (0.Programado 1.Realizado): ";
    cin>>cadena;
    while(strcmp(cadena,"1") != 0 && strcmp(cadena,"0") != 0)
    {
        cout<<"\nEstado de vuelo no valido...";
        cout<<"\nEscriba el estado del vuelo (0.Programado 1.Realizado): ";
        cin>>cadena;
    }
    aux->estado = atoi(cadena);
    aux->sgte = Vuelos;
	Vuelos = aux;

    cout<<"\n\n\tVuelo agregado con exito...";
    getchar();
    return;
}

void AdicionarPasajero(DatosVuelo &Vuelos)
{   
    DatosVuelo aux;
    aux = Vuelos;
    DatosPasajero aux2;
    aux2 = new(Pasajero);
    bool agregado = false;

    cout<<"\nEscriba el numero del vuelo: ";
    cin>>cadena;

    while(aux != NULL && agregado == false)
    {
        if(strcmp(aux->NroVuelo,cadena) == 0)
        {
            strcpy(aux2->NroVuelo,cadena);

            cout<<"\nEscriba la cedula del pasajero: ";
            cin>>cadena;
            while(strlen(cadena) != 9)
            {
                cout<<"\nEl numero de cedula debe ser de 9 digitos...";
                cout<<"\nEscriba la cedula: ";
                cin>>cadena;
            }
            strcpy(aux2->cedula,cadena);

            cout<<"\nEscriba el nombre del pasajero: ";
            cin>>cadena;
            while(strlen(cadena) > 20 || strlen(cadena) < 1)
            {
                cout<<"\nMaximo 20 caracteres...";
                cout<<"\nEscriba el nombre del pasajero";
                cin>>cadena;
            }
            strcpy(aux2->nombre,cadena);

            cout<<"\nEscriba el numero de telefono del pasajero: ";
            cin>>cadena;
            while(strlen(cadena) != 10)
            {
                cout<<"\nEl numero de telefono debe tener 10 digitos...";
                cout<<"\nEscriba el numero de telefono del pasajero: ";
                cin>>cadena;
            }
            strcpy(aux2->telefono,cadena);

            cout<<"\nEscriba el estado del pasajero (1.Reserva 2.A bordo): ";
            cin>>cadena;
            while(strcmp(cadena,"1") != 0 && strcmp(cadena,"2") != 0)
            {
                cout<<"\nEstado de vuelo no valido...";
                cout<<"\nEscriba el estado del pasajero (1.Reserva 2.A bordo): ";
                cin>>cadena;
            }

            if(aux->estado == 1 && strcmp(cadena,"1") == 0)
                aux2->estado = 3;//3.perdio el vuelo
            else 
                aux2->estado = atoi(cadena);

            aux2->sgte = aux->ListaP;
            aux->ListaP = aux2;

            agregado = true;    
        }
        aux = aux->sgte;
    }

    if(!agregado)
        cout<<"\n\n\tNumero de vuelo no existente...";
    return;
}

void RealizaVuelo(DatosVuelo &Vuelos)
{
    DatosVuelo aux;
    aux = Vuelos;
    bool realizado = false;
    cout<<"\nEscriba el vuelo que se va a realizar: ";
    cin>>cadena;
    while(aux != NULL && realizado == false)
    {
        if(strcmp(aux->NroVuelo,cadena) == 0)
        {
            if(aux->estado == 0)
            {
                aux->estado = 1;
                cout<<"\n\nEstado del vuelo cambiado a realizado...";
            }
            else
                cout<<"\n\nEste vuelo ya se ha realizado...";
            realizado = true;
        }
        aux = aux->sgte;
    }
    if(!realizado)
        cout<<"\n\n\tVuelo no existente...";
    return;
}

void EstadoP(DatosVuelo &Vuelos)
{
    DatosPasajero
    aux2 = NULL;
    DatosVuelo aux;
    aux = Vuelos;
    bool realizado = false;
    int op = 0;
    char cadena2[20];
    cout<<"\nEscriba la cedula del pasajero: ";
    cin>>cadena;
    cout<<"\nEscriba el numero del vuelo: ";
    cin>>cadena2;
    
    while(aux != NULL && realizado == false)
    {
        aux2 = aux->ListaP;
        while(aux2 != NULL && realizado == false)
        {
            if(strcmp(aux2->cedula,cadena) == 0 && strcmp(aux->NroVuelo,cadena2) == 0)
            {   
                cout<<"Nombre del pasajero: "<<aux2->nombre;
                cout<<"\n\nDesea pasar al pasajero a bordo?\n\n1.Si\n2.No\nEscriba una opcion: ";
                cin>>op;
                if(op == 1)
                {
                    if(aux2->estado == 1)
                    {
                        aux2->estado = 2;
                        cout<<"\n\nEl estado del pasajero ha sido cambiado a 'A bordo'";
                    }
                    else if(aux2->estado == 2)
                        cout<<"\n\nEl pasajero ya habia pasado a bordo...";
                    else if(aux2->estado == 3)
                        cout<<"\n\nEl pasajero ya ha perdido el vuelo...";
                }else if(op == 2)
                    cout<<"\n\n\tBueno ❤️";
                else
                    cout<<"\n\n\tEsa opcion no estaba...";
                realizado = true;
            }
            aux2 = aux2->sgte;
        }
        aux = aux->sgte;
    }
    if(!realizado)
        cout<<"\n\n\tNumero de cedula del pasajero o numero no de vuelo no coinciden...";

    return;
}

void menu()
{
    cout<<"\n\t REGISTRO YALITAZ AIRLINES\n\n";
    cout<<"0. SALIR                                         "<<endl;
    cout<<"1. ADICIONAR VUELO                               "<<endl;
    cout<<"2. ADICIONAR PASAJERO                            "<<endl;
    cout<<"3. LISTADO PASAJEROS DE UN VUELO                 "<<endl;
    cout<<"4. LISTADO VUELOS PROGRAMADOS                    "<<endl;
    cout<<"5. LISTADO VUELOS REALIZADOS                     "<<endl;
    cout<<"6. LISTADO VUELOS PROGRAMADOS DE UNA PERSONA     "<<endl;
    cout<<"7. LISTADO VUELOS REALIZADOS DE UNA PERSONA      "<<endl;
    cout<<"8. REALIZAR VUELO                                "<<endl;
    cout<<"9. PASAR A BORDO A UN PASAJERO                   "<<endl;
    cout<<"\n INGRESE OPCION: ";
}

int main()
{
    DatosVuelo Vuelos = NULL;
    leerArchivo(Vuelos);
    char opc[20];
    int op = 0;
    system("color 0b");
    do
    {
        system("color 0b");
        menu();
        cin>>opc;
        while(strcmp(opc,"0") != 0 && strcmp(opc,"1") != 0 && strcmp(opc,"2") != 0 && strcmp(opc,"3") != 0 && strcmp(opc,"4") != 0 && strcmp(opc,"5") != 0 && strcmp(opc,"6") != 0 && strcmp(opc,"7") != 0 && strcmp(opc,"8") != 0 && strcmp(opc,"9") != 0 )
        {
            cout<<"\n\n OPCION NO VALIDA...";
            cout<<"\n INGRESE OPCION: ";
            cin>>opc;
        }
        op = atoi(opc);
        switch(op)//switch que funciona con "op"
        {
            case 0:
                system("color 4B");
                cout<<"\n\n\t\t\t\tCHAO BB";
                break;
            case 1:
                system("color 70");
                AdicionarVuelo(Vuelos);
                break;
            case 2:
                system("color 4E");
                AdicionarPasajero(Vuelos);
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                system("color 5F");
                RealizaVuelo(Vuelos);
                break;
            case 9:
                system("color 2E");
                EstadoP(Vuelos);
                break;
        }
        cout<<endl<<endl;
        system("pause"); //hace una pausa para que el usuario pueda ver que pasa en pantalla
        system("cls");//borra lo que hay en pantalla
    }while(op!=0);//el do seguira en loop hasta que el usuario digite la opcion 0
    return 0;
    return 0;
}
