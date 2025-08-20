/*
Ejercicio 2.1.2. Viajes.
29.02.2024
NOMBRE: David Ortega Lozano
*/


//BIBLIOTECAS:
#include <iostream>
#include <iomanip>

//ESPACIO DE CARACTERES:
using namespace std;

//CONSTANTES:
const int SPACE_LENTH = 17;
const int N_COLUMNS = 3;
const string LINE = "------------------------------";
const int MAX_DOLARS = 999;
const int MAX_DAYS = 365;



/*
  Clase que recoge y gestiona los datos de un viaje, recoge nombre del destino, la duración en días y el coste en dólares.
  Implementa los setters y getters de todos los atributos y el método displayTravel() que muestra los atributos en consola.

  @author David Ortega Lozano
  @version 1.0
 */
class Travel
{
private:
    string destination;
    int duration;
    float cost;

public:
    /*
      Primer método constructor que recoge todos los datos del viaje desde los parámetros.

      @param city    La ciudad de destino del viaje
      @param days    El número de días que dura el viaje 
      @param dolars  El número de dólares que cuesta el viaje
     */
    Travel(string city, int days, float dolars) {
        this->destination = city;
        this->duration = days;
        this->cost = dolars;
    }

    /*
      Segundo Método constructor que recoge el precio del viaje dando opciones al usuario.

      @param city    La ciudad de destino del viaje
      @param days    El número de días que dura el viaje
     */
    Travel(string city, int days) {
        //Variables locales
        int option;
        float dolars;
        bool repeat = false;

        //Inicializo los atributos de ciudad de destino y duración del viaje
        this->destination = city;
        this->duration = days;

        //Solicito y compruebo el precio del viaje.
        do {
            cout << endl << "Select the price:" << endl << "1. $50" << endl << "2. $100" << endl << "3. $150" << endl;
            cin >> option;
            if (option > 3 || option < 1) {
                repeat = true;
                cout << endl << "Wrong option, select one correct option" << endl;
            }
        } while (repeat);

        //Dependiendo de la opción elegida se asigna uno u otro precio.
        switch (option)
        {
        case 1:
            dolars = 50.00;
            break;
        case 2:
            dolars = 100.00;
            break;
        case 3:
            dolars = 150.00;
            break;
        }

        //Finalmente, también se inicializa el precio del viaje.
        this->cost = dolars;
    }

    /*
      Métodos getter que devuelven el valor de los respectivos atributos.

      @return el respectivo atributo.
     */
    string getDestination() {
        return this->destination;
    }
    int getDuration() {
        return this ->duration;
    }
    float getCost() {
        return this->cost;
    }
 
    /*
      Métodos setter que modifican el valor de los respectivos atributos.

      @param el nuevo valor del respectivo atributo.
     */
    void setDestination(string city) {
        this->destination = city;
    }
    void setDuration(int days) {
        this->duration = days;
    }
    void setCost(float dolars) {
        this->cost = dolars;
    }

    /*
      Método que muestra los valosres de los atributos en formato tabla por la consola.
     */
    void displayTravel() {

        //Variables Locales:
        int n, numInt, numDec;

        //Almaceno la parte entera y decimal por separado en dos enteros
        numInt = int(this->cost);
        numDec = int((this->cost - numInt) * 100);

        //Imprime la primera columna del destino con los espacios necesarios para la tabulación
        cout << "| " << this->destination;
        for(int i = 0; i < SPACE_LENTH - 2 - this->destination.size(); i++) {
            cout << ' ';
        }

        //Imprime la segunda columna de la duración con los espacios calculados en función de las unidades del número
        cout << "| " << this->duration << " days";
        if (this->duration < 10) {
            n = 6;
        }
        else if (this->duration < 100) {
            n = 7;
        }
        else {
            n = 8;
        }
        for (int i = 0; i < SPACE_LENTH - 2 - n; i++) {
            cout << ' ';
        }

        //Imprime la tercera columna del precio con los espacios calculados en función de las unidades de la parte entera
        cout << "| $" << numInt << ".";
        //Se añade un 0 en caso de que la parte decimal sea menor de 0,10
        if (numDec < 10) 
            cout << '0';
        cout << numDec;

        if (numInt < 10) 
            n = 5;
        else if (numInt < 100) 
            n = 6;
        else 
            n = 7;

        for (int i = 0; i < SPACE_LENTH - 2 - n; i++) {
            cout << ' ';
        }
        //Por último se cierra la tabla.
        cout << '|' << endl;
    }
};

//ENUNCIADOS DE FUNCIONES:
Travel createNewTravel();
void printLine();
void printTitle();
int menu();
bool comprobarRango(int min, int max, int num, string sentence);

//FUNCIÓN MAIN:
int main()
{
    //Variables locales:
    bool continuar = true;
    string city;
    int days;
    float dolars;
    bool error = false;

    //Se crean dos nuevos viajes
    cout << "Enter the data of the first trip" << endl;
    Travel t1 = createNewTravel();
    cout << endl << "Enter the data of the second trip" << endl;
    Travel t2 = createNewTravel();


    //Se solicita la opción en el menú, a continuación se realiza la función correspondiente
    do {
        switch (menu()) {
            //Opción de salida
        case 0:
            continuar = false;
            break;

            //Opción para cambiar el destino del primer viaje
        case 1:
            cout << endl << "Enter the new travel destination 1: ";
            cin >> city;
            t1.setDestination(city);
            break;

            //Opción para cambiar el destino del segundo viaje
        case 2:
            cout << endl << "Enter the new travel destination 2: ";
            cin >> city;
            t2.setDestination(city);
            break;

            //Opción para cambiar la duración del primer viaje
        case 3:
            cout << endl << "Enter the new travel time 1: ";
            do {
                cin >> days;
            } while (comprobarRango(0, MAX_DAYS, days, "Travel time not valid, try again"));

            t1.setDuration(days);
            break;

            //Opción para cambiar la duración del segundo viaje
        case 4:
            cout << endl << "Enter the new travel time 2: ";
            do {
                cin >> days;
            } while (comprobarRango(0, MAX_DAYS, days, "Travel time not valid, try again"));

            t2.setDuration(days);
            break;

            //Opción para cambiar el coste del primer viaje
        case 5:
            cout << endl << "Enter the new travel cost 1: ";
            do {
                cin >> dolars;
            } while (comprobarRango(0, MAX_DOLARS, int(dolars), "Travel cost not valid, try again"));

            t1.setCost(dolars);
            break;

            //Opción para cambiar el coste del segundo viaje
        case 6:
            cout << endl << "Enter the new travel cost 2: ";
            do {
                cin >> dolars;
            } while (comprobarRango(0, MAX_DOLARS, int(dolars), "Travel cost not valid, try again"));

            t2.setCost(dolars);
            break;

            //Opción para generar informe
        case 7:
            cout << endl << endl;
            printTitle();
            t1.displayTravel();
            t2.displayTravel();
            printLine();
            cout << endl << endl;
            break;
        }
    } while (continuar);
}

//DEFINICIÓN DE LAS FUNCIONES:
//Función, que solicita los atributos del viaje al usuario y devuelve el objeto
Travel createNewTravel() {
    //Variables locales:
    string city;
    int days;
    float dolars;
    int option;
    Travel t = Travel("", 0, 0.0);
    
    //Se solicitan los datos del usuario
    cout << "Enter the destination city: ";
    cin >> city;
    cout << endl << "Enter the number of days of travel time: ";
    do {
        cin >> days;
    } while (comprobarRango(0, MAX_DAYS, days, "Travel time not valid, try again"));


    //Por último se solicita si se quiere introducir un precio o seleccionarlo de entre las opciones
    do {
        cout << endl << "What do you want?" << endl << "1. Enter the trip price" << endl << "2. Select the trip price" << endl;
        cin >> option;
    }while(comprobarRango(1, 2, option, "Wrong option, select one correct option"));

    //En caso de introducir el precio, se solicita y se dan todos los parámetros al constructor
    if (option == 1) {
        cout << endl << "Enter the trip price: ";
        do {
            cin >> dolars;
        } while (comprobarRango(0, MAX_DOLARS, int(dolars), "Travel cost not valid, try again"));


        t = Travel(city, days, dolars);
    }
    //En caso de seleccionar el precio, se dan solo el resto de parámetros al constructor,
    //que gracias a la sobrecarga se encarga de solicitar la elección de coste.
    else {
        t = Travel(city, days);
    }


    //Se envía una confirmación al usuario
    cout << endl << "Your trip has been successfully booked" << endl;

    //Se devuelve el objeto de la clase Travel
    return t;
}

//Función, que imprime una línea de guiones con el tamaño adecuado para el informe
void printLine() {

    for (int i = 0; i < (SPACE_LENTH * 3) + 1; i++) {
        cout << '-';
    }
    cout << endl;
}

//Función que imprime la totalidad del encabezado del resumen de viajes, las líneas y los títulos
void printTitle() {

    printLine();

    cout 
        << left << setw(SPACE_LENTH)
        << "| Destination" 
        << left << setw(SPACE_LENTH)
        << "| Duration"
        << left << setw(SPACE_LENTH)
        << "| Cost"
        << "|"
        << endl;

    printLine();
}

//Función que muestra todas las opciones y devuelve la solicitada por el usuario
int menu() {
    //Variables locales:
    int option;
    string title = "          MENU";
    string option1 = "1. Change travel destination 1.";
    string option2 = "2. Change travel destination 2.";
    string option3 = "3. Change travel time 1";
    string option4 = "4. Change travel time 2";
    string option5 = "5. Change travel cost 1";
    string option6 = "6. Change travel cost 2";
    string option7 = "7. Generate a report";
    string option0 = "0. Salir";
    string request = "Choose a number from 0 to 7:";

    //Se muestra el menú, se solicita una opción y se asegura que la opción es válida
    do {
        cout << LINE << endl;
        cout << title << endl;
        cout << LINE << endl;
        cout << option1 << endl;
        cout << option2 << endl;
        cout << option3 << endl;
        cout << option4 << endl;
        cout << option5 << endl;
        cout << option6 << endl;
        cout << option7 << endl;
        cout << option0 << endl;
        cout << request << endl;
        cin >> option;
    } while (comprobarRango(0, 7, option,"Wrong option, try again"));

    return option;
}

//Función que dado un entero, devuelve si está dentro del rango dado como parámetros
bool comprobarRango(int min, int max, int num, string sentence) {
    //Variable local:
    bool error = false;

    //Si el número dado se sale del rango enviar mensaje de error y devolver true
    if (num > max || num < min) {
        error = true;
        cout << endl << sentence << endl;
    }

    return error;
}