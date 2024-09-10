#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "adj.h"

using namespace std;
fstream* archivo;

int main ()
{

lista_m* general = new lista_m;

menu(general, archivo);
    
    return 0;
}