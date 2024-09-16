#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <time.h>
#include <cmath>


#include "adj.h"

using namespace std;
fstream archivo;

int main ()
{
    lista_m* general = new lista_m();

    menu(general, archivo);
    
    delete[] general;
    return 0;
}
