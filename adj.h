#include <fstream>
#include <iomanip>
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

void menu (){
int select = 5;

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
    /* code */
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



void agregar_datos()
{

}

void cargar_datos(l_devolucion* &dev, l_libros* &lib, l_prestamo* &pres, l_usuario &usu, fstream*&
 in){

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