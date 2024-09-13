#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstring>
#include <time.h>
#include <math.h>
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
int calcular_tiempo(char* fecha, char select);
void imprimir_usuarios(usuario* &l_usuarios, int tam);
void agregar_usuarios(usuario* &l_usuarios, int &tam);
void imprimir_prestamo(prestamo* &l_prestamo, int &tam);
void realizar_prestamo(prestamo* &l_prestamos, int &tam_prestamos, libro* &l_libros, int &tam_libros, usuario* &l_usuarios, int &tam_usuarios);


void menu(lista_m* &lista, fstream*& in){
    fflush(stdin);
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
            agregar_usuarios(lista->l_usuarios, lista->cant_usuarios);
            break;

        case 4:
            realizar_prestamo(lista->l_prestamos, lista->cant_prestamo, lista->l_libros, lista->cant_libros, lista->l_usuarios, lista->cant_usuarios);
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
    fflush(stdin);
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
        imprimir_usuarios(lista->l_usuarios, lista->cant_usuarios);
        break;

    case 3:
        imprimir_prestamo(lista->l_prestamos, lista->cant_prestamo);
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

void agregar_libros(libro* &l_libros, int &tam){
    fflush(stdin);
    char select = 'n';
    do{
        system("cls");
        libro* aux = new libro();
        cout << "Ingrese el Id del nuevo libro (5 caracteres)\n";
        cin.ignore();
        cin.getline(aux->id, 6);

        for (int i = 0; i < tam; i++){
            if(strcmp((l_libros+i)->id,aux->id) == 0){
                cout << "Se ha encontrado un libro existente con un Id igual al ingresado," 
                << "intente denuevo con otro Id o elimine el libro existente con ese Id\n";
                return;
            }
        }

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

            for (int i = 0; i < tam; i++){
                if(strcmp((l_libros+i)->titulo,aux->titulo) == 0){
                    int respuesta = 0;
                    cout << "\nSe ha encontrado un libro con el mismo titulo, Seleccione una opción:\n\n";
                    cout << "1. Desea aumentar la cantidad de copias de: \n";
                    cout << (l_libros+i)->titulo << " - Autor:" << (l_libros+i)->autor << "- Año de publicación:" << (l_libros+i)->año_pub << '\n';
                    cout << "2. Ingresar el libro cómo una nueva edición/otro libro\n";
                    cin >> respuesta;
                    if(respuesta == 1){
                        (l_libros+tam)->cant_copias += aux->cant_copias;
                        cout << "¡Se han añadido exitosamente las copias del libro!\n";
                        system("pause");
                        return;
                    } else {
                        break;
                    }
                }
            }

            libro* copia = new libro[tam+1];
            *(copia+tam) = *aux;
            for(int i = 0; i < tam; i++){
                *(copia+i) = *(l_libros+i);
            }
            delete[] l_libros;
            l_libros = copia;
            tam++;
            cout << "Libro añadido exitosamente!\n";
        }
        
        cout << "¿Desea añadir otro libro? (y/n)" << endl;
        cin >> select;
        select = tolower(select);
    }while(select != 'n');
}

void agregar_usuarios(usuario* &l_usuarios, int &tam){
    fflush(stdin);
    char select = 'n';
    do{
        system("cls");
        usuario* aux = new usuario();
        
        cout << "Ingrese el Nombre del usuario (25 caracteres)\n";
        cin.ignore();
        cin.getline(aux->nombre, 26);
        cout << "Ingrese la Dirección del usuario\n";
        cin.getline(aux->direccion, 31);
        cout << "Ingrese el telefono movil del usuario\n";
        cin.getline(aux->telefono, 11);
        cout << "Ingrese el país de nacimiento del usuario\n";
        cin.getline(aux->p_nacimiento, 21);
        cout << "Ingrese la fecha de nacimiento del usuario (Formato aaaa/mm/dd, Ej. 2012/12/24)\n";
        cin.getline(aux->f_nacimiento, 11);

        if(calcular_tiempo(aux->f_nacimiento, 'a') < 7){
            cout << "El usuario es muy joven para ser registrado\n";
            delete aux;
            system("pause");
            return;
        } else if (calcular_tiempo(aux->f_nacimiento, 'a') > 17){
            cout << "Se ha detectado que el usuario es mayor de edad\n"
            << "Ingrese el tipo cedula del usuario 'C' para cédula de ciudadania, 'E' para cédula de extranjeria\n";
            cin.get(aux->t_id);
        } else if (strcmp(aux->p_nacimiento, "Colombia") == 0 || strcmp(aux->p_nacimiento, "colombia") == 0)  {
            cout << "Se ha detectado que el usuario es menor de edad y ciudadano Colombiano,"
                 << " se le ha asignado automaticamente I para tarjeta de identidad\n";
        } else {
            cout << "Se ha detectado que el usuario no cumple con los requisitos para ser registrado,"
                 << " saliendo del modulo de registro\n";
            delete aux;
            system("pause");
            return;
        }

        cout << "Ingrese el Id del usuario (15 caracteres)\n";
        cin.ignore();
        cin.getline(aux->id, 16);

        if(tam == 0){
            l_usuarios = aux;
            tam++;
        } else {

            for (int i = 0; i < tam; i++){
                if(strcmp((l_usuarios+i)->id,aux->id) == 0){
                    cout << "Se ha encontrado un usuario con el mismo número de Id que el actual\n"
                    << "Comuniquese con servicio al cliente si cree que esto es un error\n"
                    << "Saliendo del modulo de registro\n";
                    system("pause");
                    return;
                }
            }

            usuario* copia = new usuario[tam+1];
            *(copia+tam) = *aux;
            for(int i = 0; i < tam; i++){
                *(copia+i) = *(l_usuarios+i);
            }
            delete[] l_usuarios;
            l_usuarios = copia;
            tam++;
            cout << "Usuario añadido exitosamente!\n";
        }

        cout << "¿Desea añadir otro usuario? (y/n)" << endl;
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

void imprimir_libros(libro* &l_libros, int tam){
    fflush(stdin);
    cout << setfill(' ') << left << setw(7) << "ID" << setw(32) << "Titulo"
    << setw(25) << "Autor" << setw(7) << "Año"
     << setw(20) << "Copias disponibles" << endl;
        if (tam != 0 && l_libros != nullptr) {
            for(int i = 0; i < tam; i++){
            cout<< setfill(' ') << setw(7) << (l_libros+i)->id << setw(32) << (l_libros+i)->titulo 
            << setw(25) << (l_libros+i)->autor << setw(7) << (l_libros+i)->año_pub <<
            setw(20) << (l_libros+i)->cant_copias <<'\n';
            } 
        } else {
            cout << "No hay libros registrados\n";
        }
    cout<<endl;
    system("pause");
}

int calcular_tiempo(char* fecha, char select){
//Will use 'select' variable to interchange between days and years 
//Se usa 'select' para cambiar entre dias y años en el valor de retorno
    fflush(stdin);
    char* aux = new char[11];
    strcpy(aux, fecha);
    time_t ahora = time(NULL);
    tm* tm_fecha = localtime(&ahora);
    char* token = strtok(aux, "/");
    tm_fecha->tm_year = (stoi(token) - 1900);
    token = strtok(NULL, "/");
    tm_fecha->tm_mon = (stoi(token) - 1);
    token = strtok(NULL, "/");
    tm_fecha->tm_mday = stoi(token);
    token = strtok(NULL, "/");
    
    unsigned tiempo = difftime(ahora, mktime(tm_fecha));

    delete[] aux;

    tiempo /= 60;
    tiempo /= 60;
    tiempo /= 24;
        if(select != 'a'){return tiempo;}
    tiempo /= 30.436875; 
    //No todos los meses tienen 30 días exactamente por lo que se toma un aproximado de la cantidad de dias en un mes
    //Not every months have 30 days, so I took an aproximate to how many days are in a month 
    tiempo /= 12;
        return tiempo;
}

void imprimir_usuarios(usuario* &l_usuarios, int tam){
    fflush(stdin);
    cout << setfill(' ') << left << setw(26) << "Nombre" << setw(13) << "Telefono" << "Id\n";

        if (tam != 0 && l_usuarios != nullptr) {
            for(int i = 0; i < tam; i++){
            cout<< setfill(' ') << left << setw(26) << (l_usuarios+i)->nombre << setw(13) << (l_usuarios+i)->telefono 
            << setw(3) << (l_usuarios+i)->t_id << setw(20) << (l_usuarios+i)->id << endl;
            } 
        } else {
            cout << "No hay usuarios registrados\n";
        }
    cout<<endl;
    system("pause");
}

void realizar_prestamo(prestamo* &l_prestamos, int &tam_prestamos, libro* &l_libros, int &tam_libros, usuario* &l_usuarios, int &tam_usuarios){
    fflush(stdin);
    system("cls");
    prestamo* aux = new prestamo();
    bool existe = false;

    cout << "Ingrese el Id del libro para el prestamo\n";
    cin.ignore();
    cin.getline(aux->id_libro, 6);

        for (int i = 0; i < tam_libros; i++){
            if(strcmp((l_libros+i)->id,aux->id_libro) == 0 && (l_libros+i)->cant_copias!= 0){
                existe = true;
                break;
            }
        }

        if(!existe){
            cout << "No se ha encontrado un libro con el Id ingresado o no tiene copias disponibles, regresando al menu principal\n";
            system("pause");
            return;
        }

    cout << "Ingrese el Id del usuario\n";
    cin.getline(aux->id_usuario, 16);

        existe = false;
        for (int i = 0; i < tam_usuarios; i++){
            if(strcmp((l_usuarios+i)->id,aux->id_usuario) == 0){
                existe = true;
            }
        }

        if(!existe){
            cout << "No se ha encontrado al usuario con el Id ingresado, regresando al menu principal\n";
            system("pause");
            return;
        }

    cout << "Ingrese un Id para el prestamo (3 caracteres)\n";
    cin.getline(aux->id_prestamo, 4);

    cout << "Ingrese la fecha del prestamo (Formato aaaa/mm/dd, Ej. 2012/12/24)\n";
    cin.getline(aux->f_prestamo, 11);

    cout << "Ingrese la fecha de devolución esperada del prestamo(Formato aaaa/mm/dd, Ej. 2012/12/24)\n";
    cin.getline(aux->f_devolucion, 21);
        
    if(tam_prestamos == 0){
        l_prestamos = aux;
        tam_prestamos++;
        
    } else {

        for (int i = 0; i < tam_prestamos; i++){
            if(strcmp((l_prestamos+i)->id_prestamo,aux->id_prestamo) == 0){
                cout << "Se ha encontrado otro prestamo con el mismo Id que el actual, saliendo al menú principal\n";
                system("pause");
                return;
            }
        }

        prestamo* copia = new prestamo[tam_prestamos+1];
        *(copia+tam_prestamos) = *aux;
        for(int i = 0; i < tam_prestamos; i++){
            *(copia+i) = *(l_prestamos+i);
        }
        delete[] l_usuarios;
        l_prestamos = copia;
        tam_prestamos++;

        for (int i = 0; i < tam_libros; i++){
            if(strcmp((l_libros+i)->id,aux->id_libro) == 0){
                (l_libros+i)->cant_copias--;
                break;
            }
        }

        cout << "Prestamo realizado exitosamente!\n";
        system("pause");
    }
}

void imprimir_prestamo(prestamo* &l_prestamo, int &tam){
    fflush(stdin);
    cout<< setfill(' ') << left << setw(6) << "Prestamo #" << setw(18) << "Usuario #" 
        << setw(8) << "Libro #" << setw(12) << "Fecha del Prestamo" << endl;

    if (tam != 0 && l_prestamo != nullptr) {
        for(int i = 0; i < tam; i++){
        cout<< setfill(' ') << left << setw(6) << (l_prestamo+i)->id_prestamo << setw(18) << (l_prestamo+i)->id_usuario 
        << setw(8) << (l_prestamo+i)->id_libro << setw(12) << (l_prestamo+i)->f_prestamo << endl;
        } 
    } else {
        cout << "No hay prestamos registrados\n";
    }
cout<<endl;
system("pause");
}

