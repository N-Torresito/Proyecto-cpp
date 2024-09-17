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
    char id_prestamo[4];
    char id_devolucion[4];
    char f_devolucion[11];
    int pago_pend = 0;
};

struct lista_m{
    libro* l_libros = nullptr;
    usuario* l_usuarios= nullptr;
    prestamo* l_prestamos= nullptr;
    devolucion* l_devolucion= nullptr;
    int cant_libros = 0;
    int cant_usuarios = 0;
    int cant_prestamo = 0;
    int cant_devolucion = 0;
};

void menu(lista_m* &lista, fstream &in);
void visualizar_datos(lista_m* &lista);
void cargar_datos(lista_m* &lista, fstream &in);
void guardar_datos(lista_m* &lista, fstream &out);
void agregar_libros(libro* &l_libros, int &tam);
void agregar_usuarios(usuario* &l_usuarios, int &tam);
void realizar_prestamo(prestamo* &l_prestamos, int &tam_prestamos, libro* &l_libros, int &tam_libros, usuario* &l_usuarios, int &tam_usuarios);
void devolver_libros(devolucion* &l_devolucion, int &tam_devolucion, prestamo* &l_prestamos, int &tam_prestamo, usuario* &l_usuarios, int &tam_usuarios, libro* &l_libros, int tam);
void visualizar_libros(libro* &l_libros, int tam);
void imprimir_libros_disponibles(libro* &l_libros, int tam);
void imprimir_libros_busqueda(libro* &l_libros, int tam);
void imprimir_libros(libro* &l_libros, int tam);
void imprimir_usuarios(usuario* &l_usuarios, int tam);
void imprimir_prestamo(prestamo* &l_prestamo, int &tam);
void imprimir_devoluciones(devolucion* &l_devoluciones, int &tam);
int calcular_tiempo(char* fecha, char select);
char* dar_fecha_actual();


void menu(lista_m* &lista, fstream &in){
    fflush(stdin);
    int select = 8;
    do{
        system("cls");
        cout << setw(50)<< setfill('*') <<"*" << '\n';
        cout << setw(35) << setfill(' ') << right << "Gestion de Biblioteca V1.0" << '\n';
        cout << setw(50)<< setfill('*') <<"*" << "\n\n";
        cout << "Bienvenido/a, elija alguna opción\n\n";

        cout << "1. Visualizar Datos Generales\n";
        cout << "2. Agregar Libros\n";
        cout << "3. Registrar Usuarios\n";
        cout << "4. Registrar Prestamo\n";
        cout << "5. Registrar Devoluciones\n";
        cout << "6. Guardar datos\n";
        cout << "7. Cargar datos\n";
        cout << "8. Salir\n\n";

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
            realizar_prestamo(lista->l_prestamos, lista->cant_prestamo, 
            lista->l_libros, lista->cant_libros, lista->l_usuarios, lista->cant_usuarios);
            break;

        case 5:
            devolver_libros(lista->l_devolucion, lista->cant_devolucion, lista->l_prestamos, 
            lista->cant_prestamo, lista->l_usuarios, lista->cant_usuarios, lista->l_libros, lista->cant_libros);
            break;

        case 6:
            guardar_datos(lista, in);
            break;

        case 7:
            cargar_datos(lista, in);
            break;

        case 8:
            break;

        default:
            cout << "Opción invalida, ingrese otra opción\n";
            break;
        }
    }while(select !=8 );
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
        visualizar_libros(lista->l_libros, lista->cant_libros);
        break;

    case 2:
        imprimir_usuarios(lista->l_usuarios, lista->cant_usuarios);
        break;

    case 3:
        imprimir_prestamo(lista->l_prestamos, lista->cant_prestamo);
        break;

    case 4:
        imprimir_devoluciones(lista->l_devolucion, lista->cant_devolucion);
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
                system("pause");
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
                if(strcasecmp((l_libros+i)->titulo,aux->titulo) == 0){
                    int respuesta = 0;
                    cout << "\nSe ha encontrado un libro con el mismo titulo, Seleccione una opción:\n\n";
                    cout << "1. Desea aumentar la cantidad de copias de: \n";
                    cout << (l_libros+i)->titulo << " - Autor:" << (l_libros+i)->autor << "- Año de publicación:" << (l_libros+i)->año_pub << '\n';
                    cout << "2. Ingresar el libro cómo una nueva edición/otro libro\n";
                    cin >> respuesta;
                    if(respuesta == 1){
                        (l_libros+i)->cant_copias += aux->cant_copias;
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
        } else if (strcasecmp(aux->p_nacimiento, "Colombia") == 0 || strcasecmp(aux->p_nacimiento, "colombia") == 0){
            cout << "Se ha detectado que el usuario es menor de edad y ciudadano Colombiano,"
                 << " se le ha asignado automaticamente I para tarjeta de identidad\n";
            aux->t_id = 'I';
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
                if(strcasecmp((l_usuarios+i)->id,aux->id) == 0){
                    cout << "Se ha encontrado un usuario con el mismo número de Id que el actual\n"
                    << "Comuniquese con servicio al cliente si cree que esto es un error\n"
                    << "Saliendo del modulo de registro\n";
                    
                    delete aux;
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

void cargar_datos(lista_m* &lista, fstream &in){
   
    in.open("biblioteca.dat", ios::in|ios::binary);

    if(!in.fail()){
        in.read((char*) &lista->cant_libros, sizeof(int));
        in.read((char*) &lista->cant_usuarios, sizeof(int));
        in.read((char*) &lista->cant_prestamo, sizeof(int));
        in.read((char*) &lista->cant_devolucion, sizeof(int));

        if(lista->cant_libros != 0){
            lista->l_libros = new libro[lista->cant_libros+1];
            for(int i = 0; i < lista->cant_libros; i++){
            in.read((char*) &*(lista->l_libros+i), sizeof(libro));
            }
        }

        if(lista->cant_usuarios != 0){
            lista->l_usuarios = new usuario[lista->cant_usuarios+1];
            for(int i = 0; i < lista->cant_usuarios; i++){
            in.read((char*) &*(lista->l_usuarios+i), sizeof(usuario));
            }
        }

        if(lista->cant_prestamo != 0){
            lista->l_prestamos = new prestamo[lista->cant_prestamo+1];
            for(int i = 0; i < lista->cant_prestamo; i++){
            in.read((char*) &*(lista->l_prestamos+i), sizeof(prestamo));
            }
        }

        if(lista->cant_devolucion != 0){
            lista->l_devolucion = new devolucion[lista->cant_devolucion+1];
            for(int i = 0; i < lista->cant_devolucion; i++){
            in.read((char*) &*(lista->l_devolucion+i), sizeof(devolucion));
            }
        }

        in.close();
        cout << "¡Se han cargado los datos correctamente!\n";
        system("pause");
        return;
    }
    in.close();
    cout << "Ha ocurrido un error al cargar los datos\n"; 
    cout << "Puede ser que no exista un archivo con los datos correspondientes o este corrupto\n";
    cout << "¿Desea intentar cargar los datos desde el archivo de texto?(y/n)\n";
    
    char respuesta = 'n';
    cin >> respuesta;
    respuesta = tolower(respuesta);

    if(respuesta == 'y'){
        in.open("biblioteca.txt", ios::in);

        if(!in.fail()){
            in >> lista->cant_libros; in.ignore();
            in >> lista->cant_usuarios; in.ignore();
            in >> lista->cant_prestamo; in.ignore();
            in >> lista->cant_devolucion; in.ignore();

            if(lista->cant_libros != 0){
                lista->l_libros = new libro[lista->cant_libros+1];
                for(int i = 0; i < lista->cant_libros; i++){
                    in.getline((lista->l_libros+i)->id,6,',');
                    in.getline((lista->l_libros+i)->titulo,31,',');
                    in.getline((lista->l_libros+i)->autor,26,',');
                    in >> (lista->l_libros+i)->año_pub;
                    in.ignore();
                    in >> (lista->l_libros+i)->cant_copias;
                    in.ignore();
                }
            }

            if(lista->cant_usuarios != 0){
                lista->l_usuarios = new usuario[lista->cant_usuarios+1];
                for(int i = 0; i < lista->cant_usuarios; i++){
                    in.getline((lista->l_usuarios+i)->nombre, 26, ',');
                    in.getline((lista->l_usuarios+i)->f_nacimiento, 11 ,',');
                    in.getline((lista->l_usuarios+i)->p_nacimiento, 21, ',');
                    in.getline((lista->l_usuarios+i)->direccion, 31, ',');
                    in.getline((lista->l_usuarios+i)->telefono, 11, ',');
                    in >> (lista->l_usuarios+i)->t_id;
                    in.ignore(1);
                    in.getline((lista->l_usuarios+i)->id, 16, '\n');
                }
            }

            if(lista->cant_prestamo  != 0){
                lista->l_prestamos = new prestamo[lista->cant_prestamo+1];
                for(int i = 0; i < lista->cant_prestamo; i++){
                    in.getline((lista->l_prestamos+i)->id_prestamo, 4, ',');
                    in.getline((lista->l_prestamos+i)->id_libro, 6, ',');
                    in.getline((lista->l_prestamos+i)->id_usuario,16,',');
                    in.getline((lista->l_prestamos+i)->f_prestamo, 11, ',');
                    in.getline((lista->l_prestamos+i)->f_devolucion, 11);
                }
            }

            if(lista->cant_devolucion != 0){
                lista->l_devolucion = new devolucion[lista->cant_devolucion+1];
                for(int i = 0; i < lista->cant_devolucion; i++){
                    in.getline((lista->l_devolucion+i)->id_devolucion, 4, ',');
                    in.getline((lista->l_devolucion+i)->id_prestamo, 4, ',');
                    in.getline((lista->l_devolucion+i)->f_devolucion, 11, ',');
                    in >> (lista->l_devolucion+i)->pago_pend;
                    in.ignore();
                }
            }

            in.close();
            cout << "¡Se han cargado los datos desde el respaldo correctamente!\n";
            system("pause");
            return;
        }
        cout << "¡Ha ocurrido un error al cargar los datos desde el respaldo!\n";
        cout << "Por favor llame a su tecnico de confianza o a soporte\n";
        system("pause");
        return;
    } 
    cout << "No se han cargado los datos y se ha rechazado la carga del respaldo\n";
    system("pause");
    return;
}

void guardar_datos(lista_m* &lista, fstream &out){
    out.open("biblioteca.dat", ios::out|ios::binary);   

    if (!out.fail()){

        out.write((char*) &lista->cant_libros, sizeof(int));
        out.write((char*) &lista->cant_usuarios, sizeof(int));
        out.write((char*) &lista->cant_prestamo, sizeof(int));
        out.write((char*) &lista->cant_devolucion, sizeof(int));

        if (lista->cant_libros != 0){
            for(int i = 0; i < lista->cant_libros; i++){
            out.write((char*) &*(lista->l_libros+i), sizeof(libro));
            }
        }

        if(lista->cant_usuarios != 0){
            for(int i = 0; i < lista->cant_usuarios; i++){
            out.write((char*) &*(lista->l_usuarios+i), sizeof(usuario));
            }
        }

        if (lista->cant_prestamo != 0){
            for(int i = 0; i < lista->cant_prestamo; i++){
            out.write((char*) &*(lista->l_prestamos+i), sizeof(prestamo));
            }
        }

        if(lista->cant_devolucion != 0){
            for(int i = 0; i < lista->cant_devolucion; i++){
            out.write((char*) &*(lista->l_devolucion+i), sizeof(devolucion));
            }
        }

        out.close();
    
        cout << "¡Datos guardados exitosamente!\n";
    }  

    out.close();

    out.open("biblioteca.txt", ios::out);   

    if (!out.fail()){

        out << lista->cant_libros << endl;
        out << lista->cant_usuarios << endl;
        out << lista->cant_prestamo << endl;
        out << lista->cant_devolucion << endl;
        
        if (lista->cant_libros != 0){
            for(int i = 0; i < lista->cant_libros; i++){
                out << (lista->l_libros+i)->id << ','
                    << (lista->l_libros+i)->titulo << ','
                    << (lista->l_libros+i)->autor << ','
                    << (lista->l_libros+i)->año_pub << ','
                    << (lista->l_libros+i)->cant_copias << endl;
            }
        }

        if(lista->cant_usuarios != 0){
            for(int i = 0; i < lista->cant_usuarios; i++){
                out << (lista->l_usuarios+i)->nombre << ','
                    << (lista->l_usuarios+i)->f_nacimiento << ','
                    << (lista->l_usuarios+i)->p_nacimiento << ','
                    << (lista->l_usuarios+i)->direccion << ','
                    << (lista->l_usuarios+i)->telefono << ','
                    << (lista->l_usuarios+i)->t_id << ','
                    << (lista->l_usuarios+i)->id << endl;
            }
        }

        if (lista->cant_prestamo != 0){
            for(int i = 0; i < lista->cant_prestamo; i++){
            out << (lista->l_prestamos+i)->id_prestamo << ','
                << (lista->l_prestamos+i)->id_libro << ','
                << (lista->l_prestamos+i)->id_usuario << ','
                << (lista->l_prestamos+i)->f_prestamo << ','
                << (lista->l_prestamos+i)->f_devolucion << endl;
            }
        }

        if(lista->cant_devolucion != 0){
            for(int i = 0; i < lista->cant_devolucion; i++){
            out << (lista->l_devolucion+i)->id_devolucion << ','
                << (lista->l_devolucion+i)->id_prestamo << ','
                << (lista->l_devolucion+i)->f_devolucion << ','
                << (lista->l_devolucion+i)->pago_pend << endl;
            }
        }

        out.close();
    
        cout << "¡Respaldo guardado exitosamente!\n";
        
        system("pause");  
        return;  
    }  


    cout << "Ha ocurrido un error al guardar los datos\n";

    system("pause");
    return;
}

void visualizar_libros(libro* &l_libros, int tam){
    int select = 4;
    cout << "Ingrese cómo quiere ver/buscar los libros\n";
    cout << "1. Todos los libros\n";
    cout << "2. Libros disponibles\n";
    cout << "3. Autor/Id/Titulo\n";
    cout << "4. Salir\n";

    cin >> select;

    switch (select)
    {
    case 1:
        imprimir_libros(l_libros, tam);
        break;

    case 2:
        imprimir_libros_disponibles(l_libros, tam);
        break;

    case 3:
        imprimir_libros_busqueda(l_libros, tam);
        break;

    case 4:
        return;
        break;
    
    default:
        return;
        break;
    }
}

void imprimir_libros_busqueda(libro* &l_libros, int tam){
system("cls");
int seleccion = 4;

    cout << "Ingrese que tipo de busqueda desea realizar\n";
    cout << "1. Por titulo\n";
    cout << "2. Por autor\n";
    cout << "3. Por Id\n";
    cin >> seleccion;

    char titulo_aux[31];
    char autor_aux[26];
    char id_aux[6];
    switch (seleccion)
    {
    case 1:
        cout << "Ingrese el titulo del libro a buscar\n";
        cin.ignore();
        cin.getline(titulo_aux, 31);
        break;
     case 2:
        cout << "Ingrese el autor del libro a buscar\n";
        cin.ignore();
        cin.getline(autor_aux, 26);
        break;

     case 3:
        cout << "Ingrese el Id del libro a buscar\n";
        cin.ignore();
        cin.getline(id_aux, 6);
        break;

     case 4:
        return;
        break;

    default:
        cout << "No es una opción valida\n";
        system("pause");
        return;
        break;
    }

    libro* lista = nullptr;
    int tam_titulos = 0; 
    if(seleccion == 1){
        for(int i = 0; i < tam; i++){
            if(strstr((l_libros+i)->titulo,titulo_aux) != nullptr){
                tam_titulos++;
            }
        }

        lista = new libro[tam_titulos];
        libro aux;

        for(int i = 0, j = 0; i < tam; i++){
            
            if(strstr((l_libros+i)->titulo,titulo_aux) != nullptr){
                *(lista+j) = *(l_libros+i);
                j++;
            }
        }

        for (int i = 0; i < tam_titulos ; i++) {
            for (int j = 0; j < tam_titulos; j++) {
            
                if (strcmp((lista+j)->titulo, (lista+i)->titulo) > 0) {                
                    aux = *(lista+i); 
                    *(lista+i) = *(lista+j); 
                    *(lista+i) = aux; 
                }
            }
        }

    }

    bool existe = false;
    switch (seleccion)
    {
    case 1:
        cout << setfill(' ') << left << setw(7) << "ID" << setw(32) << "Titulo"
        << setw(25) << "Autor" << setw(7) << "Año"
        << setw(20) << "Copias disponibles" << endl;
            if (tam_titulos != 0 && lista != nullptr) {
                for(int i = 0; i < tam_titulos; i++){
                    
                    cout<< setfill(' ') << setw(7) << (lista+i)->id << setw(32) << (lista+i)->titulo 
                        << setw(25) << (lista+i)->autor << setw(7) << (lista+i)->año_pub <<
                        setw(20) << (lista+i)->cant_copias <<'\n';
                }
            } else {
                cout << "No hay libros con ese titulo ni contienen ese titulo\n";
            }
        cout<<endl;
        delete[] lista;
        system("pause");
        break;
    
     case 2:
        cout << setfill(' ') << left << setw(7) << "ID" << setw(32) << "Titulo"
             << setw(25) << "Autor" << setw(7) << "Año"
            << setw(20) << "Copias disponibles" << endl;
            if (tam != 0 && l_libros != nullptr) {
                for(int i = 0; i < tam; i++){
                    if(strstr((l_libros+i)->autor, autor_aux) != nullptr){
                        cout<< setfill(' ') << setw(7) << (l_libros+i)->id << setw(32) << (l_libros+i)->titulo 
                        << setw(25) << (l_libros+i)->autor << setw(7) << (l_libros+i)->año_pub <<
                        setw(20) << (l_libros+i)->cant_copias <<'\n';
                        existe = true;
                    }
                } 
            }
            if(!existe){
                cout << "No se han encontrado libros con ese autor\n";
            }    
            cout<<endl;
            system("pause");
        break;

     case 3:
        cout << setfill(' ') << left << setw(7) << "ID" << setw(32) << "Titulo"
             << setw(25) << "Autor" << setw(7) << "Año"
            << setw(20) << "Copias disponibles" << endl;
            existe = false;
            if (tam != 0 && l_libros != nullptr) {
                for(int i = 0; i < tam; i++){
                    if(strcmp((l_libros+i)->id, id_aux) == 0){
                        cout<< setfill(' ') << setw(7) << (l_libros+i)->id << setw(32) << (l_libros+i)->titulo 
                        << setw(25) << (l_libros+i)->autor << setw(7) << (l_libros+i)->año_pub <<
                        setw(20) << (l_libros+i)->cant_copias <<'\n';
                        existe = true;
                    }
                } 
            }
            if(!existe){
                cout << "No se han encontrado libros con ese Id\n";
            }    
            cout<<endl;
            system("pause");
        break;
    }

}

void imprimir_libros_disponibles(libro* &l_libros, int tam){
    fflush(stdin);
    cout << setfill(' ') << left << setw(7) << "ID" << setw(32) << "Titulo"
    << setw(25) << "Autor" << setw(7) << "Año"
     << setw(20) << "Copias disponibles" << endl;
        if (tam != 0 && l_libros != nullptr) {
            for(int i = 0; i < tam; i++){
                if((l_libros+i)->cant_copias > 0){
                    cout<< setfill(' ') << setw(7) << (l_libros+i)->id << setw(32) << (l_libros+i)->titulo 
                    << setw(25) << (l_libros+i)->autor << setw(7) << (l_libros+i)->año_pub <<
                    setw(20) << (l_libros+i)->cant_copias <<'\n';
                }
            } 
        } else {
            cout << "No hay libros registrados\n";
        }
    cout<<endl;
    system("pause");
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
    //char* aux = new char[11];
    char aux[11];
    strcpy(aux, fecha);
    time_t ahora = time(NULL);
    tm* tm_fecha = localtime(&ahora);
    char* token = strtok(aux, "/");
    tm_fecha->tm_year = (atoi(token) - 1900);
    token = strtok(NULL, "/");
    tm_fecha->tm_mon = (atoi(token) - 1);
    token = strtok(NULL, "/");
    tm_fecha->tm_mday = atoi(token);
    token = strtok(NULL, "/");
    
    double tiempo = difftime(ahora, mktime(tm_fecha));

    //delete[] aux;

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
    system("cls");
    prestamo* aux = new prestamo();
    bool existe = false;

    cout << "Ingrese el Id del libro para el prestamo\n";
    cin.ignore();
    cin.getline(aux->id_libro, 6);

        cout << "Ingrese el Id del usuario\n";
        cin.getline(aux->id_usuario, 16);

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

        existe = false;

        for (int i = 0; i < tam_libros; i++){
            if(strcmp((l_libros+i)->id,aux->id_libro) == 0){
                existe = true;
                (l_libros+i)->cant_copias = (l_libros+i)->cant_copias - 1;
                break;
            }
        }

        if(!existe){
            cout << "No se ha encontrado un libro con el Id ingresado o no tiene copias disponibles, regresando al menu principal\n";
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
                delete aux;
                return;
            }
        }

        prestamo* copia = new prestamo[tam_prestamos+1];
        *(copia+tam_prestamos) = *aux;
        for(int i = 0; i < tam_prestamos; i++){
            *(copia+i) = *(l_prestamos+i);
        }

        delete[] l_prestamos;
        l_prestamos = copia;
        tam_prestamos++;

    }
    cout << "Prestamo realizado exitosamente!\n";
    system("pause");
}

void imprimir_prestamo(prestamo* &l_prestamo, int &tam){
    fflush(stdin);
    cout<< setfill(' ') << left << setw(12) << "Prestamo #" << setw(18) << "Usuario #" 
        << setw(10) << "Libro #" << setw(12) << "Fecha del Prestamo" << endl;

    if (tam != 0 && l_prestamo != nullptr) {
        for(int i = 0; i < tam; i++){
        cout<< setfill(' ') << left << setw(12) << (l_prestamo+i)->id_prestamo << setw(18) << (l_prestamo+i)->id_usuario 
        << setw(10) << (l_prestamo+i)->id_libro << setw(12) << (l_prestamo+i)->f_prestamo << endl;
        } 
    } else {
        cout << "No hay prestamos registrados\n";
    }
cout<<endl;
system("pause");
}

void devolver_libros(devolucion* &l_devolucion, int &tam_devolucion, prestamo* &l_prestamos, int &tam_prestamo, usuario* &l_usuarios, int &tam_usuarios, libro* &l_libros, int tam_libros){
    fflush(stdin);
    devolucion* aux = new devolucion();
    bool existe = false;

    if(tam_prestamo == 0){
        cout << "No existen prestamos a devolver\n";
        system("pause");
        return;
    }
    system("cls");

    cout << "Ingrese el Id del prestamo a devolver\n";
    cin.ignore();
    cin.getline(aux->id_prestamo, 4);

        for (int i = 0; i < tam_prestamo; i++){
            if(strcmp((l_prestamos+i)->id_prestamo,aux->id_prestamo) == 0){
                existe = true;
            }
        }

        if(!existe){
            cout << "No se ha encontrado un prestamo con ese Id, porfavor verifique y vuelva a intentarlo\n";
            system("pause");
            delete aux;
            return;
        }

    cout << "Ingrese un Id para esta devolución\n";
    cin.getline(aux->id_prestamo, 4);

   char* fecha_actual = dar_fecha_actual();

    strcpy(aux->f_devolucion, fecha_actual);   
    cout << "Se tiene en cuenta que se devuelve el libro el día de hoy, por lo que la fecha de devolución sería:"
         << fecha_actual << endl;
    
    delete[] fecha_actual;

    usuario pTemp;
    prestamo pTemp2;

    for (int i = 0; i < tam_prestamo; i++){
        if(strcmp((l_prestamos+i)->id_prestamo,aux->id_prestamo) == 0){
            pTemp2 = *(l_prestamos+i);
        }
    }

    for (int i = 0; i < tam_usuarios; i++){
        if(strcmp((l_usuarios+i)->id,pTemp2.id_usuario) == 0){
            pTemp = *(l_usuarios+i);
        }
    } 
    
    cout << "Días pasados" << calcular_tiempo(pTemp2.f_devolucion, 'a') << '\n';

    if(calcular_tiempo(pTemp.f_nacimiento, 'a') < 18){
        if(calcular_tiempo(pTemp2.f_devolucion,'d') < 0){
            cout << "El usuario no debe pagar nada\n";
            aux->pago_pend = 0;

        } else {
            cout << "¡La devolución debió ser hace " << (calcular_tiempo(pTemp2.f_devolucion,'d')) << "días!\n";
            cout << "El usuario debe pagar:" << 2500*floor(calcular_tiempo(pTemp2.f_devolucion,'d'));
            aux->pago_pend = 2500*floor(calcular_tiempo(pTemp2.f_devolucion,'d'));
        }
    }

    if(calcular_tiempo(pTemp.f_nacimiento, 'a') > 50){
        if(calcular_tiempo(pTemp2.f_devolucion,'d') <= 0){
            cout << "El usuario no debe pagar nada\n";
            aux->pago_pend = 0;
        } else {
            cout << "¡La devolución debió ser hace " << (calcular_tiempo(pTemp2.f_devolucion,'d')) << "días!\n";
            cout << "El usuario debe pagar:" << 5000*floor(calcular_tiempo(pTemp2.f_devolucion,'d'));
            aux->pago_pend = 5000*floor(calcular_tiempo(pTemp2.f_devolucion,'d'));
        }
    }

    if(calcular_tiempo(pTemp.f_nacimiento, 'a') > 17 && 50 > calcular_tiempo(pTemp.f_nacimiento, 'a')){
        if(calcular_tiempo(pTemp2.f_devolucion,'d') <= 0){
            cout << "El usuario no debe pagar nada\n";
            aux->pago_pend = 0;

        } else {
            cout << "¡La devolución debió ser hace " << (calcular_tiempo(pTemp2.f_devolucion,'d')) << "días!\n";
            cout << "El usuario debe pagar:" << 15000*floor(calcular_tiempo(pTemp2.f_devolucion,'d'));
            aux->pago_pend = 15000*floor(calcular_tiempo(pTemp2.f_devolucion,'d'));
        }
    }

    system("pause");

    for (int i = 0; i < tam_libros; i++){
        if(strcmp((l_libros+i)->id,pTemp2.id_libro) == 0){
            (l_libros+i)->cant_copias++;
        }
    } 

    if(tam_devolucion == 0){
            l_devolucion = aux;
            tam_devolucion++;
    } else {
        devolucion* copia = new devolucion[tam_devolucion+1];
        *(copia+tam_devolucion) = *aux;
        for(int i = 0; i < tam_devolucion; i++){
            *(copia+i) = *(l_devolucion+i);
        }
        delete[] l_devolucion;
        l_devolucion = copia;
        tam_devolucion++;
        cout << "Devolución exitosa!\n";
    }
}

char* dar_fecha_actual(){
    char* fecha = new char[11];
    *(fecha)= '\0';
    
    time_t t = time(NULL);
    tm* hoy = localtime(&t);

    string aux = to_string(hoy->tm_year + 1900);
    strcpy(fecha, aux.c_str());
    aux = to_string(hoy->tm_mon+1);
    strcat(fecha, "/");
    if(hoy->tm_mon+1 < 10){strcat(fecha, "0");};
    strcat(fecha, aux.c_str());
    if(hoy->tm_mday < 10){strcat(fecha, "0");};
    aux = to_string(hoy->tm_mday);
    strcat(fecha, "/");
    strcat(fecha, aux.c_str());
    strcat(fecha, "\0");

    return fecha;
}

void imprimir_devoluciones(devolucion* &l_devoluciones, int &tam){
    fflush(stdin);
    cout << setfill(' ') << left << setw(20) << "Id devolución" << setw(20) << "Fecha devolución" << "Pago/Saldo\n";
        if (tam != 0 && l_devoluciones != nullptr) {
            for(int i = 0; i < tam; i++){
            cout<< setfill(' ') << left << setw(20) << (l_devoluciones+i)->id_devolucion << setw(20) << (l_devoluciones+i)->f_devolucion
            << (l_devoluciones+i)->pago_pend << endl;
            } 
        } else {
            cout << "No hay devoluciones registradas\n";
        }
    cout<<endl;
    system("pause");
}