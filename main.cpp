#include <iostream>
#include <fstream>
#include <string>

using namespace std;

enum Opcion{
    wifi = 1,
    pac,
    tut,
    salir
};

struct Paciente {
    string nombre;
    string edad;
};

struct Tutor {
    string nombre;
    string celular;
};

void ingresarDatosWiFi() {
    string ssid, pss;
    cout << "Ingrese el SSID: ";
    cin >> ssid;

    cout << "Ingrese la contraseña de la red WiFi: ";
    cin >> pss;

    ofstream archivoConfig("config.txt");
    if (archivoConfig.is_open()) {
        archivoConfig << "SSID: " << ssid << "\n";
        archivoConfig << "Contraseña: " << pss << "\n";
        archivoConfig.close();
        cout << "Datos del WiFi guardados en config.txt\n";
    } else {
        cerr << "Error al abrir el archivo.\n";
    }
}

void ingresarDatosPaciente(Paciente& paciente) {
    cout << "Ingrese el nombre del paciente: ";
    cin.ignore();
    getline(cin, paciente.nombre);

    cout << "Ingrese la edad del paciente: ";
    getline(cin, paciente.edad);

    ofstream archivoPaciente("paciente.csv");
    if (archivoPaciente.is_open()) {
        archivoPaciente << "Nombre" << ";" << "Edad\n";
        archivoPaciente << paciente.nombre << ";" << paciente.edad << "\n";
        archivoPaciente.close();
        cout << "Datos del paciente guardados en paciente.csv\n";
    } else {
        cerr << "Error al abrir el archivo paciente.csv.\n";
    }
}

void ingresarDatosTutor(Tutor& tutor) {
    cout << "Ingrese el nombre del tutor: ";
    cin.ignore();
    getline(cin, tutor.nombre);

    bool esNumeroValido = false;
        do {
            cout << "Ingrese el numero de celular del tutor: ";
            cin >> tutor.celular;

            esNumeroValido = true;
            for (char c : tutor.celular) {
                if (!isdigit(c)) {
                    esNumeroValido = false;
                    break;
                }
            }

            if (!esNumeroValido) {
                cout << "El numero de celular debe contener solo digitos. Intente nuevamente.\n";
            }
        } while (!esNumeroValido);

    tutor.celular = "+54" + tutor.celular;

    ofstream archivoTutor("tutor.csv", ios::app);
    if (archivoTutor.is_open()) {
        archivoTutor << "Nombre" << ";" << "Celular\n";
        archivoTutor << tutor.nombre << ";" << tutor.celular << "\n";
        archivoTutor.close();
        cout << "Datos del tutor guardados en tutor.csv\n";
    } else {
        cerr << "Error al abrir el archivo tutor.csv.\n";
    }
}

int main() {
    int opcion;
    Paciente paciente;
    Tutor tutor;

    do {
        cout << "\nMenu Principal:\n";
        cout << "1. Cargar datos del WiFi\n";
        cout << "2. Agregar datos del paciente\n";
        cout << "3. Agregar datos de tutores\n";
        cout << "4. Salir\n";
        cout << "Elija una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case Opcion::wifi:
                ingresarDatosWiFi();
                break;
            case Opcion::pac:
                ingresarDatosPaciente(paciente);
                break;
            case Opcion::tut:
                ingresarDatosTutor(tutor);
                break;
            case Opcion::salir:
                cout << "Lulu\n";
                break;
            default:
                cout << "Opcion inválida. Intente nuevamente.\n";
        }
    } while (opcion != 4);

    return 0;
}
