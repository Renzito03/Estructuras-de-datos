#include <iostream>

using namespace std;

// 1. Estructura del Nodo
struct Nodo {
    int dato;
    Nodo* siguiente; // Flecha al vecino de la derecha
    Nodo* anterior;  // Flecha al vecino de la izquierda
};

// Prototipos de funciones para el menú
void insertarInicio(Nodo* &inicio, int valor);
void insertarFinal(Nodo* &inicio, int valor);
void eliminarPorValor(Nodo* &inicio, int valor);
void mostrarLista(Nodo* inicio);
bool buscarValor(Nodo* inicio, int valor);
void modificarValor(Nodo* inicio, int valorViejo, int valorNuevo);
int contarNodos(Nodo* inicio);

int main() {
    Nodo* inicio = nullptr; // La lista empieza vacía
    int opcion, valor, valorNuevo;

    do {
        cout << "\n===== LISTA CIRCULAR DOBLEMENTE ENLAZADA =====" << endl;
        cout << "1. Insertar al inicio" << endl;
        cout << "2. Insertar al final" << endl;
        cout << "3. Eliminar por valor" << endl;
        cout << "4. Mostrar lista (Recorrido)" << endl;
        cout << "5. Buscar un valor" << endl;
        cout << "6. Modificar un valor" << endl;
        cout << "7. Contar total de nodos" << endl;
        cout << "8. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese el valor a insertar al inicio: ";
                cin >> valor;
                insertarInicio(inicio, valor);
                break;
            case 2:
                cout << "Ingrese el valor a insertar al final: ";
                cin >> valor;
                insertarFinal(inicio, valor);
                break;
            case 3:
                if (inicio == nullptr) {
                    cout << "\nLa lista esta vacia." << endl;
                } else {
                    cout << "Ingrese el valor a eliminar: ";
                    cin >> valor;
                    eliminarPorValor(inicio, valor);
                }
                break;
            case 4:
                mostrarLista(inicio);
                break;
            case 5:
                cout << "Ingrese el valor a buscar: ";
                cin >> valor;
                if (buscarValor(inicio, valor)) {
                    cout << "¡Valor " << valor << " ENCONTRADO!" << endl;
                } else {
                    cout << "Valor no encontrado." << endl;
                }
                break;
            case 6:
                cout << "Ingrese el valor a cambiar: ";
                cin >> valor;
                cout << "Ingrese el nuevo valor: ";
                cin >> valorNuevo;
                modificarValor(inicio, valor, valorNuevo);
                break;
            case 7:
                cout << "\nTotal de nodos: " << contarNodos(inicio) << endl;
                break;
            case 8:
                cout << "\nSaliendo del programa. ¡Hasta luego!" << endl;
                break;
            default:
                cout << "\nOpcion no valida." << endl;
        }
    } while (opcion != 8);

    // Limpieza de memoria circular antes de salir
    if (inicio != nullptr) {
        Nodo* actual = inicio;
        Nodo* siguienteNodo;
        do {
            siguienteNodo = actual->siguiente;
            delete actual;
            actual = siguienteNodo;
        } while (actual != inicio);
    }

    return 0;
}

// === IMPLEMENTACIÓN DE LAS OPERACIONES ===

// 1. INSERCIÓN: Agregar al Inicio
void insertarInicio(Nodo* &inicio, int valor) {
    Nodo* nuevo = new Nodo();
    nuevo->dato = valor;

    if (inicio == nullptr) {
        // Si es el primer nodo de todos, se apunta a sí mismo en ambos sentidos
        nuevo->siguiente = nuevo;
        nuevo->anterior = nuevo;
        inicio = nuevo;
    } else {
        Nodo* ultimo = inicio->anterior; // El último siempre es el anterior al inicio

        nuevo->siguiente = inicio;
        nuevo->anterior = ultimo;

        ultimo->siguiente = nuevo; // El viejo último ahora apunta al nuevo
        inicio->anterior = nuevo;  // El viejo inicio ahora mira a la izquierda al nuevo
        inicio = nuevo;            // El inicio se mueve al nuevo nodo
    }
    cout << "¡Valor " << valor << " insertado al inicio!" << endl;
}

// 1. INSERCIÓN: Agregar al Final
void insertarFinal(Nodo* &inicio, int valor) {
    Nodo* nuevo = new Nodo();
    nuevo->dato = valor;

    if (inicio == nullptr) {
        nuevo->siguiente = nuevo;
        nuevo->anterior = nuevo;
        inicio = nuevo;
    } else {
        Nodo* ultimo = inicio->anterior; // Conseguimos el último directamente sin caminar

        nuevo->siguiente = inicio; // Su derecha es el inicio
        nuevo->anterior = ultimo; // Su izquierda es el viejo último

        ultimo->siguiente = nuevo;
        inicio->anterior = nuevo;
    }
    cout << "¡Valor " << valor << " insertado al final!" << endl;
}

// 2. ELIMINACIÓN: Borrar un nodo por valor
void eliminarPorValor(Nodo* &inicio, int valor) {
    Nodo* actual = inicio;
    bool encontrado = false;

    // Buscamos el nodo (usamos do-while porque es circular)
    do {
        if (actual->dato == valor) {
            encontrado = true;
            break;
        }
        actual = actual->siguiente;
    } while (actual != inicio);

    if (!encontrado) {
        cout << "El valor " << valor << " no existe en la lista." << endl;
        return;
    }

    // Caso A: Es el ÚNICO nodo en la lista
    if (actual->siguiente == actual) {
        inicio = nullptr;
    } else {
        // Ajustamos los puentes entre sus vecinos izquierdo y derecho
        actual->anterior->siguiente = actual->siguiente;
        actual->siguiente->anterior = actual->anterior;

        // Caso B: Si el nodo que borramos era justo el apuntador 'inicio'
        if (actual == inicio) {
            inicio = actual->siguiente; // Movemos el inicio al de la derecha
        }
    }

    delete actual; // Destruimos el nodo físicamente
    cout << "¡El nodo con el valor " << valor << " ha sido eliminado!" << endl;
}

// 3. RECORRIDO: Mostrar la lista redonda
void mostrarLista(Nodo* inicio) {
    if (inicio == nullptr) {
        cout << "\nLa lista esta vacia." << endl;
        return;
    }

    Nodo* temporal = inicio;
    cout << "\n--- Recorrido Circular (Da la vuelta) ---" << endl;
    cout << "(Ultimo) <-> ";
    do {
        cout << "[" << temporal->dato << "] <-> ";
        temporal = temporal->siguiente;
    } while (temporal != inicio); // Se detiene cuando vuelve a chocar con el inicio
    cout << "(Inicio de nuevo)" << endl;
}

// 4. BÚSQUEDA: Encontrar un valor
bool buscarValor(Nodo* inicio, int valor) {
    if (inicio == nullptr) return false;

    Nodo* temporal = inicio;
    do {
        if (temporal->dato == valor) return true;
        temporal = temporal->siguiente;
    } while (temporal != inicio);

    return false;
}

// 5. MODIFICACIÓN: Cambiar el valor de un nodo
void modificarValor(Nodo* inicio, int valorViejo, int valorNuevo) {
    if (inicio == nullptr) {
        cout << "Lista vacia." << endl;
        return;
    }

    Nodo* temporal = inicio;
    do {
        if (temporal->dato == valorViejo) {
            temporal->dato = valorNuevo;
            cout << "¡Modificado con exito!" << endl;
            return;
        }
        temporal = temporal->siguiente;
    } while (temporal != inicio);

    cout << "El valor viejo no existe." << endl;
}

// 6. CONTEO: Contar total de nodos
int contarNodos(Nodo* inicio) {
    if (inicio == nullptr) return 0;

    int contador = 0;
    Nodo* temporal = inicio;
    do {
        contador++;
        temporal = temporal->siguiente;
    } while (temporal != inicio);

    return contador;
}