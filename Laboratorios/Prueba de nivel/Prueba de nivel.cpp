/*
PRUEBA DE NIVEL.
14.02.2024
NOMBRE: David Ortega Lozano
*/


//Bibliotecas
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;



//Declaración de constantes:
#define LINE "---------------------------"
#define ARCHIVO_IN "pedidos.txt"
#define ARCHIVO_OUT "informe.txt"



//Datos enumerados:
enum Estado { PENDIENTE, ENVIADO, ENTREGADO };



//Datos estructurados:
typedef struct {
    int day;
    int month;
}Date;

typedef struct {
    string ID;
    string nombre;
    int cantidad;
    double precio;
    Date fecha;
    Estado estado;
}Pedido;

typedef struct {
    Pedido pedidos[100];
    int nPedidos;
}Tienda;



//PROTOTIPOS:
int menu();

bool cargaDatos(Tienda& t);

void modificar(Tienda& t, int indice);

void informeGeneral(const Tienda t);

void generaInforme(const Tienda t);

int buscaPedido(const Tienda t, string nPedido);

void datosPedido(Pedido p);

string estadoToString(Estado e);

//He creido conveniente crear esta función para simplificar y evitar repetir código
bool comprobarRango(int min, int max, int num);

//He creido conveniente crear esta función para simplificar y evitar repetir código
string solicitarPedido();



int main() {
    //Variables locales:
    Tienda t;
    int option;
    int pedido;


    //Se inicializa la tienda:
    if (cargaDatos(t)) {

        //Se solicita y realiza la opción deseada:
        do {
            option = menu();
            switch (option) {

                //Opción de salida
            case 0:
                break;


                //Opción de Mostrar datos pedido
            case 1:
                //Se comprueba que exista el número de pedido
                do {
                    pedido = buscaPedido(t, solicitarPedido());
                }while(comprobarRango(0, t.nPedidos, pedido));

                datosPedido(t.pedidos[pedido]);
                break;


                //Opción de Modificar datos pedido
            case 2:
                //Se comprueba que exista el número de pedido
                do {
                    pedido = buscaPedido(t, solicitarPedido());
                } while (comprobarRango(0, t.nPedidos, pedido));

                modificar(t, pedido);
                break;


                //Opción de Mostrar informe general de pedidos
            case 3:
                informeGeneral(t);
                break;
                

                //Opción de Generar informe anual de ventas
            case 4:
                generaInforme(t);
                break;
            }
        } while (option != 0);
    }

    return 0;
}

int menu() {
    //Variables locales:
    int option;
    string titulo = "          MENU";
    string option1 = "1. Mostrar datos pedido.";
    string option2 = "2. Modificar datos pedido.";
    string option3 = "3. Mostrar informe general de pedidos.";
    string option4 = "4. Generar informe anual de ventas.";
    string option0 = "0. Salir";
    string solicitud = "Elige un número entre 0 y 4:";

    //Se muestra el menú, se solicita una opción y se asegura que la opción es válida
    do {
        cout << LINE << endl;
        cout << titulo << endl;
        cout << LINE << endl;
        cout << option1 << endl;
        cout << option2 << endl;
        cout << option3 << endl;
        cout << option4 << endl;
        cout << option0 << endl;
        cout << solicitud << endl;
        cin >> option;
    } while (comprobarRango(0, 4, option));

    return option;
}

bool cargaDatos(Tienda& t) {
    /*
    He decidido hacer esta función buleana, para poder finalizar el programa en el caso de que no se consiga abrir el archivo
    */

    //Variables locales:
    Pedido p;
    string estado;
    bool abierto = true;

    //Se abre el archivo de pedidos
    ifstream dT;										
    dT.open(ARCHIVO_IN);							

    //En el caso de que se abra correctamente:
    if (dT.is_open()) {									

        //Se obtiene el número de pedidos en la lista
        dT >> t.nPedidos;

        //Se recoge cada valor de cada pedido y se van añadiendo a la lista
        for (int i = 0; i < t.nPedidos; i++) {
            dT >> p.ID >> p.nombre >> p.cantidad >> p.precio >> p.fecha.day >> p.fecha.month >> estado;
            if (estado == "PENDIENTE") {
                p.estado = Estado(0);
            }
            else if (estado == "ENVIADO") {
                p.estado = Estado(1);
            }
            else if (estado == "ENTREGADO") {
                p.estado = Estado(2);
            }
            t.pedidos[i] = p;
        }

        //Por último se cierra el archivo
        dT.close();										
    }
    else {	
        //En el caso de que haya surgido algún problema, se devuelve un mensage de error y se finaliza la ejecución
        abierto = false;								
        cout << " A habido un problema al abrir el archivo" << endl;
    }

    return abierto;										

}

void modificar(Tienda& t, int indice) {

    //Variables locales:
    string nPedido;
    int option;
    Pedido p = t.pedidos[indice];
        //Texto del menú de campos a editar:
    string solicitud2 = "¿Qué dato quieres modificar?";
    string option1 = "1. Cantidad";
    string option2 = "2. Precio";
    string option3 = "3. Estado";
    string solicitud3 = "Elige:";

    //Primero se muestran los datos del pedido
    datosPedido(p);

    //Se le da a escoger el campo que quiere editar de la información del pedido y se asegura que es una opción válida
    do {
        cout << solicitud2 << endl << option1 << endl << option2 << endl << option3 << endl << solicitud3;
        cin >> option;
    } while (comprobarRango(1, 3, option));

    //Se edita el campo deseado
    switch (option) {
        //Se solicita la nuva cantidad del pedido y se modifica
    case 1:
        cout << "La cantidad actual del pedido es: " << p.cantidad << endl;
        cout << "Inserte la nueva cantidad del pedido: ";
        cin >> p.cantidad;
        cout << endl << "La cantidad se ha modificado correctamente" << endl;
        break;


        //Se solicita el nuevo precio del pedido y se modifica
    case 2:
        cout << "El Precio actual del pedido es: " << p.precio << endl;
        cout << "Inserte el nuevo precio del pedido: ";;
        cin >> p.precio;
        cout << "El Precio se ha modificado correctamente" << endl;
        break;


        //Se comprueba el estado del pedido y se pregunta si se quiere avanzar
    case 3:
        cout << "El Estado actual del pedido es: " << estadoToString(Estado(p.estado)) << endl;

        switch (p.estado) {
            //El caso de que se quiera cambiar de Pendiente a Enviado
        case 0:
            do {
                cout << "¿Quieres cambiar el estado a Enviado?" << endl << "1. Sí" << endl << "2. No" << endl;
                cin >> option;
            } while (comprobarRango(1, 2, option));
            if (option == 1) {
                p.estado = Estado(1);
            }
            break;


            //El caso de que se quiera cambiar de Enviado a Entregado
        case 1:
            do {
                cout << "¿Quieres cambiar el estado a Entregado?" << endl << "1. Sí" << endl << "2. No" << endl;
                cin >> option;
            } while (comprobarRango(1, 2, option));
            if (option == 1) {
                p.estado = Estado(2);
            }
            break;


            //El caso que se quiera restaurar de Entregado a Pendiente
        case 2:
            do {
                cout << "¿Quieres cambiar el estado a Pendiente?" << endl << "1. Sí" << endl << "2. No" << endl;
                cin >> option;
            } while (comprobarRango(1, 2, option));
            if (option == 1) {
                p.estado = Estado(0);
            }
            break;
        }
        cout << "El Estado se ha modificado correctamente" << endl;
        break;
    }

    //Finalmente se actualiza la lista de pedidos
    t.pedidos[indice] = p;
}

void informeGeneral(const Tienda t) {
    //Variables locales:
    int ventas[4];
    double importe = 0.0, enviados = 0.0, entregados = 0.0;
    Pedido p;

    //Se inicializa a 0 el número de ventas de cada trimestre
    for (int i = 0; i < 4; i++) {
        ventas[i] = 0;
    }

    for (int i = 0; i < t.nPedidos; i++) {
        p = t.pedidos[i];

        //Primero se adjudica la venta al trimestre correspondiente
        if (p.fecha.month < 4) {
            ventas[0]++;
        }
        else if (p.fecha.month < 7) {
            ventas[1]++;
        }
        else if (p.fecha.month < 10) {
            ventas[2]++;
        }
        else {
            ventas[3]++;
        }

        //Despues se suma el precio de la venta al importe anual
        importe += p.precio;

        //Por último, se calcula el número de pedidos enviados, y el número de estos últimos que se han entregado
        if (p.estado == Estado(1)) {
            enviados++;
        }
        else if (p.estado == Estado(2)) {
            enviados++;
            entregados++;
        }
    }

    //Finalmente se muestra el informe
    cout << LINE << endl << "    DATOS ANUALES 2023" << endl << LINE << endl;
    for (int i = 0; i < 4; i++) {
        cout << "Ventas trimestre " << i + 1 << ": " << ventas[i] << endl;
    }
    cout << "Número total de pedidos: " << t.nPedidos << endl;
    cout << "Importe total de ventas: " << importe << endl;
    cout << "Porcentaje de pedidos enviados: " << (enviados / t.nPedidos) * 100 << '%' << endl;
    cout << "Porcentaje de pedidos entregados: " << (entregados / t.nPedidos) * 100 << '%' << endl;
}

void generaInforme(const Tienda t) {
    //Variables locales:
    Pedido p;
    int cant;

    //Se abre el archivo del informe, y en caso de que no se encuentre, se crea uno nuevo.
    ofstream dT;										 
    dT.open(ARCHIVO_OUT);							

    //Se escribe la cabecera del informe
    dT << "LISTADO DE PEDIDOS PENDIENTES DE ENVÍO:" << endl;
    dT << "NÚMERO      CANT     FECHA" << endl;

    //Para cada pedido, se comprueba si aun está pendiente y se muestra su ID, cantidad y fecha
    for (int i = 0; i < t.nPedidos; i++) {
        p = t.pedidos[i];

        if (p.estado == Estado(0)) {
            dT << p.ID << "        ";
            cant = p.cantidad;
            if (cant < 10) {
                dT << "  ";
            }
            else if (cant < 100) {
                dT << " ";
            }
            dT << cant << "       " << p.fecha.day << '/' << p.fecha.month << endl;
        }
    }

    //Por último se cierra el archivo
    dT.close();
}

int buscaPedido(const Tienda t, string nPedido) {
    //Variable local:
    int position = -1;

    for (int i = 0; i < t.nPedidos; i++) {
        if (t.pedidos[i].ID == nPedido) {
            position = i;
            i = t.nPedidos;
        }
    }

    return position;
}

void datosPedido(Pedido p) {
    //Variables locales:
    string titulo = "DATOS PEDIDO: ";
    string info1 = "Nombre producto: ";
    string info2 = "Cantidad: ";
    string info3 = "Precio: ";
    string info4 = "Fecha: ";
    string info5 = "Estado: ";
    
    //Se muestran los datos del pedido
    cout << LINE << endl << titulo << p.ID << endl << LINE << endl;
    cout << info1 << p.nombre << endl;
    cout << info2 << p.cantidad << endl;
    cout << info3 << p.precio << endl;
    cout << info4 << p.fecha.day << '/' << p.fecha.month << endl;
    cout << info5 << estadoToString(p.estado) << endl;
}

string estadoToString(Estado e) {
    //Variable local:
    string estado;

    //Dependiendo del estado se devuelve el string correspondiente
    switch (int(e)) {
    case 0:
        estado = "Pendiente";
        break;
    case 1:
        estado = "Enviado";
        break;
    default:
        estado = "Entregado";
        break;
    }

    return estado;
}

bool comprobarRango(int min, int max, int num) {
    //Variable local:
    bool error = false;

    //Si el número dado se sale del rango enviar mensaje de error y devolver true
    if (num > max || num < min) {
        error = true;
        cout << "opción no válida, seleccione una opción correcta" << endl;
    }

    return error;
}

string solicitarPedido() {
    //Variable local:
    string nPedido;

    //Se solicita el número de pedido y se devuelve
    cout << "Introduce el número de pedido: ";
    cin >> nPedido;

    return nPedido;
}