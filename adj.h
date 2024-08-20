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

void cargar_datos(l_devolucion* dev, l_libros* lib, l_prestamo* pres, l_usuario usu, fstream* in){

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

void guardar_datos(l_devolucion* dev, l_libros* lib, l_prestamo* pres, l_usuario usu, fstream* out){



}

void agregar_libros(){



}