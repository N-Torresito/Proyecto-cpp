#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "adj.h"

using namespace std;
fstream* archivo;

l_libros* libros_gen = nullptr;
l_usuario* usuarios_gen = nullptr;
l_prestamo* prestamos_gen = nullptr;
l_devolucion* devoluciones_gen = nullptr;

int main ()
{

menu(devoluciones_gen, libros_gen, prestamos_gen, usuarios_gen, archivo);
    
    return 0;
}