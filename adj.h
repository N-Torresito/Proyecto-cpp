#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstring>
using namespace std;

/*
La manera en que se manejan los datos en el archivo binario y en el archivo de texto será de la siguiente forma:
cantidad de libros
cantidad de usuarios
cantidad de prestamos
cantidad de devoluciones
lista de libros (Arreglo dinamico)
lista de usuarios (Arreglo dinamico)
lista de prestamos (Arreglo dinamico)
lista de devoluciones (Arreglo dinamico)

The way the data is handled in the binary file and in the text file will be as follows:
number of books
number of users
number of loans
number of returns
list of books (dynamic array)
list of users (dynamic array)
list of loans (dynamic array)
list of returns (dynamic array)
*/

struct libro {
    char id[6];
    char titulo[31];
    char autor[26];
    int año_pub;
    int cant_copias;
};

struct usuario {
    char id[16];
    char t_id;
    char nombre[26];
    char direccion[31];
    char telefono[11];
    char f_nacimiento[11];
    char p_nacimiento[21];
};

struct prestamo{
    char id_prestamo[4];
    char id_usuario[16];
    char id_libro[6];
    char f_prestamo[11];
    char f_devolucion[11];
};

struct devolucion{
    char id_devolucion[4];
    char f_devolucion[11];
    int pago_pend = 0;
};

struct lista_m{
    libro* l_libros;
    usuario* l_usuarios;
    prestamo* l_prestamos;
    devolucion* l_devolucion;
    int cant_libros;
    int cant_usuarios;
    int cant_prestamo;
    int cant_devolución;
};

void menu(lista_m* &lista, fstream*& in);
void visualizar_datos(lista_m* &lista);
void cargar_datos(lista_m* &lista, fstream* &in);
void guardar_datos(lista_m* &lista, fstream* &out);
void agregar_libros(libro* &l_libros, int &tam);
void imprimir_libros(libro* &l_libros, int tam);

void menu(lista_m* &lista, fstream*& in){
int select = 5;
    do{
        system("cls");
        cout << setw(50)<< setfill('*') <<"*" << '\n';
        cout << setw(35) << setfill(' ') << right << "Gestion de Biblioteca V0.2" << '\n';
        cout << setw(50)<< setfill('*') <<"*" << "\n\n";
        cout << "Bienvenido/a, elija alguna opción\n\n";

        cout << "1. Visualizar Datos Generales\n";
        cout << "2. Agregar Libros\n";
        cout << "3. Registrar Usuarios\n";
        cout << "4. Registrar Prestamo\n";
        cout << "5. Salir\n\n";

        cout << "Selección: ";
        cin >> select;
        cout << "\n\n";

        switch (select)
        {
        case 1:
            visualizar_datos(lista);
            break;

        case 2:
            agregar_libros(lista->l_libros, lista->cant_libros);
            break;

        case 3:
            /* code */
            break;

        case 4:
            /* code */
            break;

        case 5:
            break;

        default:
            cout << "Opción invalida, ingrese otra opción\n";
            break;
        }
    }while(select !=5 );
}

void visualizar_datos(lista_m* &lista){
    system("cls");
    int select;
    cout << "Ingrese que datos desea visualizar\n";
    
    cout << "1. Libros\n";
    cout << "2. Usuarios\n";
    cout << "3. Prestamos\n";
    cout << "4. Devoluciones\n";
    cout << "5. Cancelar\n\n";

    cin >> select;
    cout << "\n\n";

    switch (select)
    {
    case 1:
        imprimir_libros(lista->l_libros, lista->cant_libros);
        break;

    case 2:
        /* code */
        break;

    case 3:
        /* code */
        break;

    case 4:
        /* code */
        break;

    case 5:
        break;

    default:
        cout << "Opción invalida, ingrese otra opción\n";
        break;
    }
}

void agregar_libros(libro* &l_libros, int &tam)
{
char select = 'n';
do{
    system("cls");
    libro* aux = new libro();
    cout << "Ingrese el Id del libro (5 caracteres)\n";
    cin.ignore();
    cin.getline(aux->id, 6);
    cout << "Ingrese el titulo del libro (30 caracteres)\n";
    cin.getline(aux->titulo, 31);
    cout << "Ingrese el Autor del libro (25 caracteres)\n";
    cin.getline(aux->autor, 26);
    cout << "Ingrese el año de publicación\n";
    cin >> aux->año_pub;
    cout << "Ingrese la cantidad de copias\n";
    cin >> aux->cant_copias;

    if(tam == 0){
        l_libros = aux;
        tam++;
    } else {
        libro* copia = new libro[tam+1];
        *(copia+tam) = *aux;
        for(int i = 0; i < tam; i++){
            *(copia+i) = *(l_libros+i);
        }
        l_libros = copia;
        tam++;
    }

    cout << "Libro añadido exitosamente!\n";
    cout << "¿Desea añadir otro libro? (y/n)" << endl;
    cin >> select;
    select = tolower(select);
}while(select != 'n');
}

void cargar_datos(lista_m* &lista, fstream*& in){

in->open("biblioteca.dat", ios::in);

if (!in->fail())
{

}



}

void guardar_datos(lista_m* &lista, fstream* &out){



}

void imprimir_datos(){

}

void imprimir_libros(libro* &l_libros, int tam){
    
    if (tam != 0) {
        for(int i = 0; i < tam; i++){
        cout<<(l_libros+i)->id << " " << (l_libros+i)->titulo << " " << (l_libros+i)->autor << '\n';
        } 
    } else {
        cout << "No hay libros registrados\n";
    }

    cout<<endl;
    system("pause");
}