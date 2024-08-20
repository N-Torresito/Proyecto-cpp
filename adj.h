#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstring>
using namespace std;

struct libro {
 char id[5];
 char titulo[30];
 char autor[25];
 int año_pub;
 int cant_copias;
};

struct usuario {
 char id[15];
 char t_id;
 char nombre[25];
 char direccion[30];
 char telefono[10];
 char f_nacimiento[10];
 char p_nacimiento[20];
};

struct prestamo{
 char id_prestamo[3];
 char id_usuario[15];
 char id_libro[5];
 char f_prestamo[10];
 char f_devolucion[10];
};

struct devolucion{
 char id_devolucion[3];
 char f_devolucion[10];
 int pago_pend = 0;
};

struct l_libros {
 libro libros;
 l_libros* siguiente = nullptr;
};

struct l_usuario{
 usuario usuario;
 l_usuario* siguiente = nullptr;
};

struct l_prestamo{
 prestamo prestamo;
 l_prestamo* siguiente = nullptr;
};

struct l_devolucion{
 devolucion devolucion;
 l_devolucion* siguiente = nullptr;
};

struct cant_l{
 int cant_libros;
 int cant_usuarios;
 int cant_prestamo;
 int cant_devolución;
};

void menu(l_devolucion* &dev, l_libros* &lib, l_prestamo* &pres, l_usuario* &usu, fstream*& in);
void visualizar_datos(l_devolucion* &dev, l_libros* &lib, l_prestamo* &pres, l_usuario* &usu);
void agregar_datos();
void cargar_datos(l_devolucion* &dev, l_libros* &lib, l_prestamo* &pres, l_usuario &usu, fstream*& in);
void guardar_datos(l_devolucion* &dev, l_libros* &lib, l_prestamo* &pres, l_usuario* &usu, fstream* &out);
void agregar_libros(l_libros* &lib);
void imprimir_libros(l_libros* inicial);

void menu (l_devolucion* &dev, l_libros* &lib, l_prestamo* &pres, l_usuario* &usu, fstream*& in){
int select = 5;
do{
    system("cls");
    cout << setw(50)<< setfill('*') <<"*" << '\n';
    cout << setw(35) << setfill(' ') << right << "Gestion de Biblioteca V0.1" << '\n';
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
        visualizar_datos(dev, lib, pres, usu);
        break;

    case 2:
        agregar_libros(lib);
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

void visualizar_datos(l_devolucion* &dev, l_libros* &lib, l_prestamo* &pres, l_usuario* &usu){
    int select;
    system("cls");
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
        imprimir_libros(lib);
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

void agregar_libros(l_libros* &lib)
{
char select = 'n';
do{
    system("cls");
    l_libros* aux = new l_libros;
    cout << "Ingrese el Id del libro (5 caracteres)\n";
    cin.ignore();
    cin.getline(aux->libros.id, 5);
    cout << "Ingrese el titulo del libro (30 caracteres)\n";

    cin.getline(aux->libros.titulo, 29);
    cout << "Ingrese el Autor del libro (25 caracteres)\n";

    cin.getline(aux->libros.autor, 24);
    cout << "Ingrese el año de publicación\n";
    cin >> aux->libros.año_pub;
    cout << "Ingrese la cantidad de copias\n";
    cin >> aux->libros.cant_copias;

    if(lib == nullptr)
        {
            lib = aux;	
        }else{
            l_libros* temp = lib;
            while(temp->siguiente != nullptr)
            {
                temp = temp->siguiente;
            }
            temp->siguiente = aux;
        }

    cout << "Libro añadido exitosamente!\n";
    cout << "¿Desea añadir otro libro? (y/n)" << endl;
    cin >> select;
    select = tolower(select);
}while(select != 'n');
}

void cargar_datos(l_devolucion* &dev, l_libros* &lib, l_prestamo* &pres, l_usuario &usu, fstream*& in){

in->open("devolucion.dat", ios::in);


if (!in->fail())
{
    while(in->eof())
    {
        l_devolucion* nuevo = new l_devolucion();
        in->read((char*) dev, sizeof(devolucion));



        dev = dev->siguiente; 

    }
}



}

void guardar_datos(l_devolucion* &dev, l_libros* &lib, l_prestamo* &pres, l_usuario* &usu, fstream* &out){



}

void agregar_libros(){

}

void imprimir_datos(){

}

void imprimir_libros(l_libros* inicial) {
    l_libros* temp = inicial;
    while (temp != nullptr) {
        cout<<temp->libros.id << " " << temp->libros.titulo << " " << temp->libros.autor << '\n';
        temp = temp->siguiente;
    }
    cout<<endl;
    system("pause");
}