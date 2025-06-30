#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <stack>
#include <queue>
#include <memory>
#include <optional>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <stdexcept>
#include <list> 
#include <map>   

using namespace std;

template <typename T>
class N {
public:
    T dato;
    N<T>* siguiente;
    N(T valor) : dato(valor), siguiente(nullptr) {}
};

template <typename T>
class ListaE {
private:
    N<T>* cabeza;
public:
    ListaE() : cabeza(nullptr) {}

    // Destructor para liberar memoria
    ~ListaE() {
        N<T>* actual = cabeza;
        while (actual != nullptr) {
            N<T>* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
        cabeza = nullptr;
    }

    void insertar(T valor) {
        N<T>* nuevo = new N<T>(valor);
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
    }

    // Método mostrar modificado para ser constante
    void mostrar(function<void(T)> mostrarElemento) const {
        N<T>* actual = cabeza;
        while (actual != nullptr) {
            mostrarElemento(actual->dato);
            actual = actual->siguiente;
        }
    }

    T* buscar(function<bool(T)> criterio) {
        N<T>* actual = cabeza;
        while (actual != nullptr) {
            if (criterio(actual->dato)) return &actual->dato;
            actual = actual->siguiente;
        }
        return nullptr;
    }

    bool eliminar(std::function<bool(T)> criterio) {
        if (!cabeza) return false;
        N<T>* actual = cabeza;
        N<T>* previo = nullptr;

        if (criterio(actual->dato)) {
            cabeza = cabeza->siguiente;
            delete actual;
            return true;
        }

        previo = actual;
        actual = actual->siguiente;
        while (actual) {
            if (criterio(actual->dato)) {
                previo->siguiente = actual->siguiente;
                delete actual;
                return true;
            }
            previo = actual;
            actual = actual->siguiente;
        }

        return false;
    }
};

template <typename T>
struct NodoCircular {
    T dato;
    shared_ptr<NodoCircular<T>> siguiente;

    NodoCircular(const T& valor) : dato(valor), siguiente(nullptr) {}
};

template <typename T>
class ListaCircular {
private:
    shared_ptr<NodoCircular<T>> cabeza;
    shared_ptr<NodoCircular<T>> actual;
    size_t tamaño;
public:
    ListaCircular() : cabeza(nullptr), actual(nullptr), tamaño(0) {}

    void insertar(const T& valor) {
        auto nuevo = make_shared<NodoCircular<T>>(valor);
        if (!cabeza) {
            cabeza = nuevo;
            cabeza->siguiente = cabeza;
        }
        else {
            nuevo->siguiente = cabeza->siguiente;
            cabeza->siguiente = nuevo;
            cabeza = nuevo;
        }
        tamaño++;
    }

    void rotar() {
        if (cabeza) actual = cabeza->siguiente;
    }

    T& obtenerActual() {
        if (!actual) actual = cabeza;
        return actual->dato;
    }

    shared_ptr<NodoCircular<T>> buscar(std::function<bool(const T&)> criterio) {
        if (!cabeza) return nullptr;
        auto temp = cabeza;
        do {
            if (criterio(temp->dato)) return temp;
            temp = temp->siguiente;
        } while (temp != cabeza);

        return nullptr;
    }

    bool eliminar(function<bool(const T&)> criterio) {
        if (!cabeza) return false;
        auto prev = cabeza;
        auto curr = cabeza->siguiente;

        do {
            if (criterio(curr->dato)) {
                prev->siguiente = curr->siguiente;
                if (curr == cabeza) cabeza = prev;
                tamaño--;
                return true;
            }
            prev = curr;
            curr = curr->siguiente;
        } while (prev != cabeza);

        return false;
    }

    void mostrar(function<void(const T&)> mostrarElemento) {
        if (!cabeza) return;
        auto temp = cabeza;
        do {
            mostrarElemento(temp->dato);
            temp = temp->siguiente;
        } while (temp != cabeza);
    }

    size_t obtenerTamaño() const { return tamaño; }
};

class cliente {
public:
    string id, name, correo;
    cliente() {}
    cliente(string i, string n, string c) : id(i), name(n), correo(c) {}
    bool operator<(const cliente& other) const {
        return id < other.id;
    }
    bool operator>(const cliente& other) const {
        return id > other.id;
    }
    bool operator==(const cliente& other) const {
        return id == other.id;
    }
};

class membresia {
public:
    string id, tipo;
    double precio;
    membresia() {}
    membresia(string i, string t, double p) : id(i), tipo(t), precio(p) {}

    // Nuevo: Método para serializar (convertir a string) la membresia
    string toString() const {
        return id + "," + tipo + "," + to_string(precio);
    }

    // Nuevo: Método estático para deserializar (crear desde string) la membresia
    static membresia fromString(const string& data) {
        stringstream ss(data);
        string id, tipo, precioStr;
        getline(ss, id, ',');
        getline(ss, tipo, ',');
        getline(ss, precioStr, ',');
        return membresia(id, tipo, stod(precioStr));
    }
};

class clase {
public:
    string id, nombre, horario;
    clase() {}
    clase(string i, string n, string h) : id(i), nombre(n), horario(h) {}
    bool operator<(const clase& other) const {
        return id < other.id;
    }
    bool operator>(const clase& other) const {
        return id > other.id;
    }
    bool operator==(const clase& other) const {
        return id == other.id;
    }
};

class trainer {
public:
    string id, nme, especialidad;
    trainer() {}
    trainer(string i, string n, string e) : id(i), nme(n), especialidad(e) {}
    bool operator<(const trainer& other) const {
        return id < other.id;
    }
    bool operator>(const trainer& other) const {
        return id > other.id;
    }
    bool operator==(const trainer& other) const {
        return id == other.id;
    }
};

class Asistencia {
public:
    string clienteId, claseId;
    string fecha;
    Asistencia() {}
    Asistencia(string c, string cl, string f) : clienteId(c), claseId(cl), fecha(f) {}
};

class Pago {
public:
    string clienteId;
    membresia m;
    Pago() {} // Constructor predeterminado
    Pago(string id, membresia mem) : clienteId(id), m(mem) {}

    // Nuevo: Método para serializar (convertir a string) el pago
    string toString() const {
        return clienteId + "|" + m.toString(); // Usamos '|' como separador para diferenciar de las comas internas de membresia
    }

    // Nuevo: Método estático para deserializar (crear desde string) el pago
    static Pago fromString(const string& data) {
        size_t pos = data.find('|');
        if (pos == string::npos) {
            throw invalid_argument("Formato de pago inválido: no se encontró el separador '|'");
        }
        string clienteId = data.substr(0, pos);
        string membresiaData = data.substr(pos + 1);
        membresia m = membresia::fromString(membresiaData);
        return Pago(clienteId, m);
    }
};



class HorariosEspecificos {
public:
    string id;
    // Ej: "M" para Mañana, "T" para Tarde
    string descripcion;
    // Ej: "06:00 - 12:00", "Mañana"
    HorariosEspecificos() {}
    HorariosEspecificos(string i, string d) : id(i), descripcion(d) {}
};

class RutinaEjercicio {
public:
    string rutinaId;
    string nombre;
    string descripcion;
    // Breve descripción de la rutina
    RutinaEjercicio() {}
    RutinaEjercicio(string i, string n, string d) : rutinaId(i), nombre(n), descripcion(d) {}
};

class ClienteTieneTrainer {
public:
    string clienteId;
    bool tieneTrainer;
    // true si tiene entrenador asignado, false si no
    ClienteTieneTrainer() {}
    ClienteTieneTrainer(string id, bool estado) : clienteId(id), tieneTrainer(estado) {}
};

class Equipo {
public:
    string equipoId;
    string nombre;
    enum class TipoEquipo {
        CARDIO,
        FUERZA,
        PESAS_LIBRES,
        MAQUINARIA,
        OTROS
    } tipo;
    enum class EstadoMantenimiento {
        OPERATIVO,
        EN_MANTENIMIENTO,
        DESHABILITADO
    } estado;
    string claseId;
    string zonaGimnasio;

    chrono::system_clock::time_point ultimoMantenimiento;
    chrono::system_clock::time_point proximoMantenimiento;

    bool haSidoMantenido() const {
        return ultimoMantenimiento != std::chrono::system_clock::time_point{};
    }

    bool tieneProgramacionMantenimiento() const {
        return proximoMantenimiento != std::chrono::system_clock::time_point{};
    }

    // constructor
    Equipo(const std::string& id, const std::string& name, TipoEquipo type)
        : equipoId(id),
        nombre(name),
        tipo(type),
        estado(EstadoMantenimiento::OPERATIVO),
        ultimoMantenimiento(chrono::system_clock::time_point{}),
        proximoMantenimiento(chrono::system_clock::time_point{}),
        claseId(""),
        zonaGimnasio("")
    {
    }

    void actualizarEstado(EstadoMantenimiento nuevoEstado) {
        estado = nuevoEstado;

        if (nuevoEstado == EstadoMantenimiento::OPERATIVO) {
            ultimoMantenimiento = std::chrono::system_clock::now();
            // 30 dias
            proximoMantenimiento = ultimoMantenimiento + std::chrono::hours(720);
        }
    }

    void programarMantenimiento(int horasHastaMantenimiento) {
        estado = EstadoMantenimiento::EN_MANTENIMIENTO;
        proximoMantenimiento = std::chrono::system_clock::now() +
            std::chrono::hours(horasHastaMantenimiento);
    }
};

class ReseñaDeEntrenador {
public:
    string reseñaId;
    string trainerId;
    string clienteId;
    string comentario;
    //  enumeracion
    enum class Calificacion {
        UNA = 1,
        DOS = 2,
        TRES = 3,
        CUATRO = 4,
        CINCO = 5
    } calificacion;
    // status
    enum class EstadoReseña {
        ACTIVA,
        REPORTADA,
        ELIMINADA
    } estado;
    chrono::system_clock::time_point fechaReseña;

    // Constructor
    ReseñaDeEntrenador(const string& id,
        const string& clienteId,
        const string& trainerId,
        Calificacion calif,
        const string& comentario)
        : reseñaId(id),
        clienteId(clienteId),
        trainerId(trainerId),
        comentario(comentario),
        calificacion(calif),
        estado(EstadoReseña::ACTIVA),
        fechaReseña(chrono::system_clock::now()) {

        // validacion
        if (calif < Calificacion::UNA || calif > Calificacion::CINCO) {
            throw std::invalid_argument("Invalid rating value");
        }
    }

    void reportarReseña() {
        estado = EstadoReseña::REPORTADA;
    }

    void limpiarReporte() {
        if (estado == EstadoReseña::REPORTADA) {
            estado = EstadoReseña::ACTIVA;
        }
    }

    string obtenerFechaFormateada() const {
        time_t time = chrono::system_clock::to_time_t(fechaReseña);
        struct tm tm_buffer;

        // Usar localtime_s en Windows, localtime en otros OS
#ifdef _MSC_VER
        if (localtime_s(&tm_buffer, &time) != 0) {
#else
        if (localtime(&time) == nullptr) {
#endif
            return "Fecha inválida";
        }

        stringstream ss;
#ifdef _MSC_VER
        ss << put_time(&tm_buffer, "%a %b %d %H:%M:%S %Y");
#else
        ss << put_time(localtime(&time), "%a %b %d %H:%M:%S %Y");
#endif
        return ss.str();
    }
};

class Objetivo {
public:
    string objetivoId;
    string clienteId;
    enum class Estado {
        InProgress,
        Achieved,
        Expired
    } estado;
    int targetDays;
    int currentDays;
    chrono::system_clock::time_point startDate;
    chrono::system_clock::time_point endDate;
    chrono::system_clock::time_point lastUpdated;
    Objetivo(const string& id,
        const string& clientId,
        int targetDays,
        const string& startDateStr,
        const string& endDateStr)
        : objetivoId(id),
        clienteId(clientId),
        targetDays(targetDays),
        currentDays(0),
        estado(Estado::InProgress) {

        startDate = parseDate(startDateStr);
        endDate = parseDate(endDateStr);
        lastUpdated = chrono::system_clock::now();

        if (endDate <= startDate) {
            throw invalid_argument("End date must be after start date");
        }

        updateStatus();
    }

    void incrementDays(int days = 1) {
        currentDays += days;
        lastUpdated = chrono::system_clock::now();
        updateStatus();
    }

    void resetProgress() {
        currentDays = 0;
        lastUpdated = chrono::system_clock::now();
        updateStatus();
    }

    int daysRemaining() const {
        return targetDays - currentDays;
    }

    int daysElapsed() const {
        return chrono::duration_cast<chrono::hours>(
            chrono::system_clock::now() - startDate).count() / 24;
    }

    int totalDaysInPeriod() const {
        return chrono::duration_cast<std::chrono::hours>(
            endDate - startDate).count() / 24;
    }

private:

    chrono::system_clock::time_point parseDate(const string& dateStr) {
        tm tm = {};
        istringstream ss(dateStr);
        ss >> get_time(&tm, "%Y-%m-%d");
        if (ss.fail()) {
            throw invalid_argument("Invalid date format. UseYYYY-MM-DD");
        }
        return chrono::system_clock::from_time_t(std::mktime(&tm));
    }

    void updateStatus() {
        auto now = chrono::system_clock::now();
        if (now > endDate) {
            estado = Estado::Expired;
        }
        else if (currentDays >= targetDays) {
            estado = Estado::Achieved;
        }
        else {
            estado = Estado::InProgress;
        }
    }
};

// Clase para Tabla Hash de Clientes
class TablaHashClientes {
private:
    std::vector<std::list<cliente>> tabla;
    int capacidad;

    // Función hash simple
    int funcionHash(const std::string& key) {
        int hash = 0;
        for (char c : key) {
            hash += c;
        }
        return hash % capacidad;
    }

public:
    TablaHashClientes(int cap) : capacidad(cap) {
        tabla.resize(capacidad);
    }

    void insertar(const cliente& cli) {
        int indice = funcionHash(cli.id);
        for (const auto& c : tabla[indice]) {
            if (c.id == cli.id) {
                throw std::runtime_error("Cliente con ID " + cli.id + " ya existe.");
            }
        }
        tabla[indice].push_back(cli);
    }

    cliente* buscar(const std::string& id) {
        int indice = funcionHash(id);
        for (auto& c : tabla[indice]) {
            if (c.id == id) {
                return &c;
            }
        }
        return nullptr;
    }

    void eliminar(const std::string& id) {
        int indice = funcionHash(id);
        auto& lista = tabla[indice];
        for (auto it = lista.begin(); it != lista.end(); ++it) {
            if (it->id == id) {
                lista.erase(it);
                return;
            }
        }
        throw std::runtime_error("Cliente con ID " + id + " no encontrado para eliminar.");
    }

    void mostrarTodos() {
        for (int i = 0; i < capacidad; ++i) {
            std::cout << "Bucket " << i << ":\n";
            if (tabla[i].empty()) {
                std::cout << "    Vacio\n";
            } else {
                for (const auto& cli : tabla[i]) {
                    std::cout << "    ID: " << cli.id << ", Nombre: " << cli.name << ", Correo: " << cli.correo << "\n";
                }
            }
        }
    }
};

// Clase para Nodo de Árbol Binario de Búsqueda
template <typename T>
class NodoArbol {
public:
    T dato;
    NodoArbol<T>* izquierda;
    NodoArbol<T>* derecha;

    NodoArbol(T val) : dato(val), izquierda(nullptr), derecha(nullptr) {}
};

// Clase para Árbol Binario de Búsqueda
template <typename T>
class ArbolBinarioBusqueda {
private:
    NodoArbol<T>* raiz;

    // Función auxiliar para insertar
    NodoArbol<T>* _insertar(NodoArbol<T>* nodo, T valor) {
        if (nodo == nullptr) {
            return new NodoArbol<T>(valor);
        }
        if (valor < nodo->dato) {
            nodo->izquierda = _insertar(nodo->izquierda, valor);
        } else if (valor > nodo->dato) {
            nodo->derecha = _insertar(nodo->derecha, valor);
        }
        return nodo;
    }

    // Función auxiliar para buscar
    NodoArbol<T>* _buscar(NodoArbol<T>* nodo, T valor) {
        if (nodo == nullptr || nodo->dato == valor) {
            return nodo;
        }
        if (valor < nodo->dato) {
            return _buscar(nodo->izquierda, valor);
        } else {
            return _buscar(nodo->derecha, valor);
        }
    }

    // Función auxiliar para encontrar el mínimo
    NodoArbol<T>* _encontrarMin(NodoArbol<T>* nodo) {
        while (nodo->izquierda != nullptr) {
            nodo = nodo->izquierda;
        }
        return nodo;
    }

    // Función auxiliar para eliminar
    NodoArbol<T>* _eliminar(NodoArbol<T>* nodo, T valor) {
        if (nodo == nullptr) {
            return nodo;
        }
        if (valor < nodo->dato) {
            nodo->izquierda = _eliminar(nodo->izquierda, valor);
        } else if (valor > nodo->dato) {
            nodo->derecha = _eliminar(nodo->derecha, valor);
        } else {
            // Caso 1: No tiene hijos o solo un hijo
            if (nodo->izquierda == nullptr) {
                NodoArbol<T>* temp = nodo->derecha;
                delete nodo;
                return temp;
            } else if (nodo->derecha == nullptr) {
                NodoArbol<T>* temp = nodo->izquierda;
                delete nodo;
                return temp;
            }

            // Caso 2: Tiene dos hijos
            NodoArbol<T>* temp = _encontrarMin(nodo->derecha);
            nodo->dato = temp->dato;
            nodo->derecha = _eliminar(nodo->derecha, temp->dato);
        }
        return nodo;
    }

    // Función auxiliar para recorrido en orden
    void _inorden(NodoArbol<T>* nodo, std::function<void(T)> imprimir) {
        if (nodo != nullptr) {
            _inorden(nodo->izquierda, imprimir);
            imprimir(nodo->dato);
            _inorden(nodo->derecha, imprimir);
        }
    }

    // Función auxiliar para liberar memoria
    void _eliminarArbol(NodoArbol<T>* nodo) {
        if (nodo != nullptr) {
            _eliminarArbol(nodo->izquierda);
            _eliminarArbol(nodo->derecha);
            delete nodo;
        }
    }

public:
    ArbolBinarioBusqueda() : raiz(nullptr) {}

    ~ArbolBinarioBusqueda() {
        _eliminarArbol(raiz);
    }

    void insertar(T valor) {
        raiz = _insertar(raiz, valor);
    }

    bool buscar(T valor) {
        return _buscar(raiz, valor) != nullptr;
    }

    void eliminar(T valor) {
        raiz = _eliminar(raiz, valor);
    }

    void inorden(std::function<void(T)> imprimir) {
        _inorden(raiz, imprimir);
    }
};

stack<membresia> historialMembresias;
queue<cliente> colaEspera;
ListaE<Pago> pagos;

ListaE<HorariosEspecificos> horarios;
ListaE<RutinaEjercicio> rutinas;
ListaE<ClienteTieneTrainer> estadoTrainersCliente;

ListaE<Equipo> equiposTotales;
ListaCircular<Equipo> equiposEnMantenimiento;

ListaE<ReseñaDeEntrenador> reseñasTotales;
queue<ReseñaDeEntrenador*> reseñasReportadas;

ListaE<Objetivo> objetivosHistoricos;
stack<Objetivo> objetivosActivos;

TablaHashClientes tablaClientes(100); 
ArbolBinarioBusqueda<trainer> arbolTrainers; 
ArbolBinarioBusqueda<clase> arbolClases;     

const string NOMBRE_ARCHIVO_PAGOS = "Pagos.txt";
// Función para guardar los pagos en el archivo
void guardarPagos(const ListaE<Pago>& listaPagos, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo); // Abre el archivo en modo escritura
    if (archivo.is_open()) {
        listaPagos.mostrar([&](Pago p) {
            archivo << p.toString() << endl; // Escribe cada pago en una línea
            });
        // ¡Añadido para forzar la escritura al disco!
        archivo.flush();

        archivo.close();
        cout << "Pagos guardados en " << nombreArchivo << endl;
    }
    else {
        cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << " para guardar pagos.\n";
    }
}

// Función para cargar los pagos desde el archivo
ListaE<Pago> cargarPagos(const string& nombreArchivo) {
    ListaE<Pago> pagosCargados;
    ifstream archivo(nombreArchivo); // Abre el archivo en modo lectura
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) { // Lee el archivo línea por línea
            try {
                pagosCargados.insertar(Pago::fromString(linea)); // Convierte la línea a un objeto Pago y lo inserta
            }
            catch (const invalid_argument& e) {
                cerr << "Error al cargar pago de la línea: '" << linea << "' - " << e.what() << endl;
            }
        }
        archivo.close();
        cout << "Pagos cargados desde " << nombreArchivo << endl;
    }
    else {
        cerr << "Advertencia: No se pudo abrir el archivo " << nombreArchivo << ". Se iniciará sin pagos previos.\n";
    }
    return pagosCargados;
}


void menu() {
    cout << endl;
    cout << "-----------------------------\n";
    cout << " SISTEMA DE GESTION DE GIMNASIO\n";
    cout << "-----------------------------\n";
    cout << "1. Registrar cliente (Tabla Hash)\n";
    cout << "2. Mostrar clientes (Tabla Hash)\n";
    cout << "3. Buscar cliente (Tabla Hash)\n";
    cout << "4. Registro de pagos\n";
    cout << "5. Reporte de clientes\n";
    cout << "6. Registrar Horario Especifico\n";
    cout << "7. Mostrar Horarios Especificos\n";
    cout << "8. Registrar Rutina de Ejercicio\n";
    cout << "9. Mostrar Rutinas de Ejercicio\n";
    cout << "10. Actualizar Estado Trainer Cliente\n";
    cout << "11. Agregar nueva reseña\n";
    cout << "12. Ver reseñas por entrenador\n";
    cout << "13. Reportar reseña\n";
    cout << "14. Eliminar reseña\n";
    cout << "15. Agregar nuevo equipo\n";
    cout << "16. Eliminar equipo\n";
    cout << "17. Poner equipo en mantenimiento\n";
    cout << "18. Todos los equipos\n";
    cout << "19. Equipos en mantenimiento\n";
    cout << "20. Nuevo Objetivo\n";
    cout << "21. Registrar Día Completado\n";
    cout << "22. Archivar Objetivos Completados\n";
    cout << "23. Eliminar Objetivo\n";
    cout << "24. Objetivos Activos\n";
    cout << "25. Registrar Trainer (Arbol Binario)\n";
    cout << "26. Buscar Trainer (Arbol Binario)\n";
    cout << "27. Eliminar Trainer (Arbol Binario)\n";
    cout << "28. Mostrar Trainers (Arbol Binario - Inorden)\n";
    cout << "29. Registrar Clase (Arbol Binario)\n";
    cout << "30. Buscar Clase (Arbol Binario)\n";
    cout << "31. Eliminar Clase (Arbol Binario)\n";
    cout << "32. Mostrar Clases (Arbol Binario - Inorden)\n";
    cout << "33. Salir\n";
    cout << "Seleccione una opcion: ";
}

int main() {
    // ListaE<cliente> clientes; // Remplazado por TablaHashClientes
    // Cargar pagos al inicio del programa
    pagos = cargarPagos(NOMBRE_ARCHIVO_PAGOS);
    int opcion;

    do {
        menu();
        cin >> opcion;
        cin.ignore();
        if (opcion == 1) {
            cout << endl;
            string id, nombre, correo;
            cout << "Ingrese ID: "; getline(cin, id);
            cout << "Ingrese nombre: "; getline(cin, nombre);
            cout << "Ingrese correo: "; getline(cin, correo);
            try {
                tablaClientes.insertar(cliente(id, nombre, correo)); // Insert into hash table
                estadoTrainersCliente.insertar(ClienteTieneTrainer(id, false));
                cout << endl;
                cout << "Cliente registrado exitosamente.\n";
            } catch (const std::runtime_error& e) {
                cerr << "Error al registrar cliente: " << e.what() << endl;
            }
        }

        else if (opcion == 2) {
            cout << endl;
            tablaClientes.mostrarTodos(); // mostrar de hash table
        }

        else if (opcion == 3) {
            string id;
            cout << "Ingrese ID a buscar: "; getline(cin, id);
            cout << endl;
            cliente* c = tablaClientes.buscar(id); // Buscar en hash table
            if (c) cout << "Cliente encontrado: " << c->name << endl;
            else cout << "Cliente no encontrado.\n";
        }

        else if (opcion == 4) {
            string id;
            cout << "Ingrese ID del cliente: "; getline(cin, id);

            cliente* c = tablaClientes.buscar(id); // Buscar en hash table
            if (c) {
                string idM, tipo;
                double precio;
                cout << "Ingrese ID de membresia: "; getline(cin, idM);
                cout << "Ingrese tipo de membresia: "; getline(cin, tipo);
                cout << "Ingrese precio: "; cin >> precio; cin.ignore();
                membresia m(idM, tipo, precio);
                historialMembresias.push(m); // Se registra en la pila
                pagos.insertar(Pago(id, m)); // Se registra en la lista de pagos
                guardarPagos(pagos, NOMBRE_ARCHIVO_PAGOS); // ¡Guardar pagos en el archivo!
                cout << "Pago registrado exitosamente.\n";
            } else {
                cout << "Cliente no encontrado.\n";
            }
        }

        else if (opcion == 5) {
            cout << endl;
            tablaClientes.mostrarTodos(); 
            cout << "\n--- Reporte detallado de Clientes (adaptado para Tabla Hash) ---\n";
            for (int i = 0; i < tablaClientes.capacidad; ++i) { 
                //-----------------------------------------------------------------------------------------------------------------------------------------------------
                // Faltaria esta opcion, pero primero hay que ver si al final se va a hacer los cambios en la estructura de datos de los clientes a un vector normal .
                //-----------------------------------------------------------------------------------------------------------------------------------------------------
            }
            
        }
        else if (opcion == 6) {
            cout << "\n--- Registrar Horario Especifico ---\n";
            string id, descripcion;
            cout << "Ingrese ID del horario: "; getline(cin, id);
            cout << "Ingrese descripcion (ej: 06:00-12:00): "; getline(cin, descripcion);
            horarios.insertar(HorariosEspecificos(id, descripcion));
            cout << "Horario registrado.\n";
        }
        else if (opcion == 7) {
            cout << "\n--- Mostrar Horarios Especificos ---\n";
            if (horarios.buscar([](HorariosEspecificos h) { return true; }) == nullptr) {
                cout << "No hay horarios registrados.\n";
            }
            else {
                horarios.mostrar([](HorariosEspecificos h) {
                    cout << "ID: " << h.id << ", Descripcion: " << h.descripcion << endl;
                    });
            }
        }
        else if (opcion == 8) {
            cout << "\n--- Registrar Rutina de Ejercicio ---\n";
            string id, nombre, descripcion;
            cout << "Ingrese ID de la rutina: "; getline(cin, id);
            cout << "Ingrese nombre de la rutina: "; getline(cin, nombre);
            cout << "Ingrese descripcion de la rutina: "; getline(cin, descripcion);
            rutinas.insertar(RutinaEjercicio(id, nombre, descripcion));
            cout << "Rutina registrada.\n";
        }
        else if (opcion == 9) {
            cout << "\n--- Mostrar Rutinas de Ejercicio ---\n";
            if (rutinas.buscar([](RutinaEjercicio r) { return true; }) == nullptr) {
                cout << "No hay rutinas registradas.\n";
            }
            else {
                rutinas.mostrar([](RutinaEjercicio r) {
                    cout << "ID: " << r.rutinaId << ", Nombre: " << r.nombre << ", Descripcion: " << r.descripcion << endl;
                    });
            }
        }
        else if (opcion == 10) {
            cout << "\n--- Actualizar Estado Trainer Cliente ---\n";
            string clienteId;
            cout << "Ingrese ID del cliente: "; getline(cin, clienteId);
            ClienteTieneTrainer* ctt = estadoTrainersCliente.buscar([&](ClienteTieneTrainer estado) { return estado.clienteId == clienteId; });
            if (ctt) {
                char respuesta;
                cout << "El cliente actualmente " << (ctt->tieneTrainer ? "tiene" : "no tiene") << " entrenador.\n";
                cout << "¿Asignar entrenador? (s/n): "; cin >> respuesta; cin.ignore();
                if (respuesta == 's' || respuesta == 'S') {
                    ctt->tieneTrainer = true;
                    cout << "Estado actualizado: Cliente ahora tiene entrenador.\n";
                } else if (respuesta == 'n' || respuesta == 'N') {
                    ctt->tieneTrainer = false;
                    cout << "Estado actualizado: Cliente ahora no tiene entrenador.\n";
                } else {
                    cout << "Opcion invalida.\n";
                }
            } else {
                cout << "Cliente no encontrado en el registro de estado de trainers.\n";
            }
        }
        else if (opcion == 11) {
            cout << "\n--- Agregar nueva reseña ---\n";
            string clienteId;
            string instructorId;
            string comentario;
            string puntuacion;
            string reseñaId;
            cout << "Ingrese ID de la reseña "; getline(cin, reseñaId);
            cout << "Ingrese ID del cliente: "; getline(cin, clienteId);
            cout << "Ingrese ID del instructor: "; getline(cin, instructorId);
            cout << "Ingrese reseña: "; getline(cin, comentario);
            cout << "Ingrese puntuación: "; getline(cin, puntuacion);
            int puntuacionNum = stoi(puntuacion);
            if (puntuacionNum < 1 || puntuacionNum > 5) {
                throw out_of_range("Invalid rating");
            }
            reseñasTotales.insertar(ReseñaDeEntrenador(reseñaId, clienteId, instructorId, static_cast<ReseñaDeEntrenador::Calificacion>(puntuacionNum), comentario));
            cout << "Reseña agregada con ID: " << reseñaId << endl;
        }
        else if (opcion == 12) { // mirar reviews de trainer
            cout << "\n--- Ver reseñas por entrenador ---\n";
            string trainerId;
            cout << "Ingrese ID del entrenador: "; getline(cin, trainerId);
            cout << "\nReseñas para el entrenador " << trainerId << ":\n";
            reseñasTotales.mostrar([&](ReseñaDeEntrenador r) {
                if (r.trainerId == trainerId) {
                    cout << "ID Reseña: " << r.reseñaId << "\n"
                        << "Cliente: " << r.clienteId << "\n"
                        << "Puntuación: " << static_cast<int>(r.calificacion) << "\n"
                        << "Comentario: " << r.comentario << "\n"
                        << "Fecha: " << r.obtenerFechaFormateada() << "Estado: " << (r.estado == ReseñaDeEntrenador::EstadoReseña::ACTIVA ? "Activa" : "Reportada") << "\n-----------------------------\n";
                }
                });
        }
        else if (opcion == 13) { // Report review
            cout << "\n--- Reportar reseña ---\n";
            string reseñaId;
            cout << "Ingrese ID de la reseña a reportar: "; getline(cin, reseñaId);
            ReseñaDeEntrenador* reseña = reseñasTotales.buscar([&](ReseñaDeEntrenador r) { return r.reseñaId == reseñaId; });
            if (reseña) {
                reseña->reportarReseña();
                reseñasReportadas.push(reseña);
                cout << "Reseña " << reseñaId << " reportada.\n";
            }
            else {
                cout << "Reseña no encontrada.\n";
            }
        }
        else if (opcion == 14) {
            cout << "\n--- Eliminar reseña ---\n";
            string reseñaId;
            cout << "Ingrese ID de la reseña a eliminar: "; getline(cin, reseñaId);

            if (reseñasTotales.eliminar([&](ReseñaDeEntrenador r) { return r.reseñaId == reseñaId; })) {
                cout << "Reseña " << reseñaId << " eliminada exitosamente.\n";
            }
            else {
                cout << "Reseña no encontrada.\n";
            }
        }
        else if (opcion == 15) {
            cout << "\n--- Agregar nuevo equipo ---\n";
            string equipoId, nombreEquipo, tipoStr;
            int tipoNum;
            cout << "Ingrese ID del equipo: "; getline(cin, equipoId);
            cout << "Ingrese nombre del equipo: "; getline(cin, nombreEquipo);
            cout << "Ingrese tipo de equipo (0: CARDIO, 1: FUERZA, 2: PESAS_LIBRES, 3: MAQUINARIA, 4: OTROS): ";
            cin >> tipoNum; cin.ignore();
            Equipo::TipoEquipo tipoEquipo = static_cast<Equipo::TipoEquipo>(tipoNum);
            equiposTotales.insertar(Equipo(equipoId, nombreEquipo, tipoEquipo));
            cout << "Equipo agregado exitosamente.\n";
        }
        else if (opcion == 16) {
            cout << "\n--- Eliminar equipo ---\n";
            string equipoId;
            cout << "Ingrese ID del equipo a eliminar: "; getline(cin, equipoId);
            if (equiposTotales.eliminar([&](Equipo e) { return e.equipoId == equipoId; })) {
                cout << "Equipo " << equipoId << " eliminado exitosamente.\n";
            }
            else {
                cout << "Equipo no encontrado.\n";
            }
        }
        else if (opcion == 17) {
            cout << "\n--- Poner equipo en mantenimiento ---\n";
            string equipoId;
            cout << "Ingrese ID del equipo a poner en mantenimiento: "; getline(cin, equipoId);
            Equipo* equipo = equiposTotales.buscar([&](Equipo e) { return e.equipoId == equipoId; });
            if (equipo) {
                equipo->actualizarEstado(Equipo::EstadoMantenimiento::EN_MANTENIMIENTO);
                equiposEnMantenimiento.insertar(*equipo); // Add to circular list
                cout << "Equipo " << equipoId << " puesto en mantenimiento.\n";
            }
            else {
                cout << "Equipo no encontrado.\n";
            }
        }
        else if (opcion == 18) {
            cout << "\n--- Todos los equipos ---\n";
            equiposTotales.mostrar([](Equipo e) {
                cout << "ID: " << e.equipoId << ", Nombre: " << e.nombre;
                cout << ", Estado: " << (e.estado == Equipo::EstadoMantenimiento::OPERATIVO ? "Operativo" : (e.estado == Equipo::EstadoMantenimiento::EN_MANTENIMIENTO ? "En Mantenimiento" : "Deshabilitado")) << "\n";
                });
        }
        else if (opcion == 19) {
            cout << "\n--- Equipos en mantenimiento ---\n";
            equiposEnMantenimiento.mostrar([](Equipo e) {
                cout << "ID: " << e.equipoId << ", Nombre: " << e.nombre << "\n";
                });
        }
        else if (opcion == 20) {
            cout << "\n--- Nuevo Objetivo ---\n";
            string objetivoId, clienteId, startDateStr, endDateStr;
            int targetDays;

            cout << "Ingrese ID del objetivo: "; getline(cin, objetivoId);
            cout << "Ingrese ID del cliente: "; getline(cin, clienteId);
            cout << "Ingrese días objetivo: "; cin >> targetDays; cin.ignore();
            cout << "Ingrese fecha de inicio (YYYY-MM-DD): "; getline(cin, startDateStr);
            cout << "Ingrese fecha de fin (YYYY-MM-DD): "; getline(cin, endDateStr);

            try {
                Objetivo nuevoObjetivo(objetivoId, clienteId, targetDays, startDateStr, endDateStr);
                objetivosActivos.push(nuevoObjetivo);
                cout << "Objetivo creado y activo.\n";
            }
            catch (const invalid_argument& e) {
                cerr << "Error al crear objetivo: " << e.what() << endl;
            }
        }
        else if (opcion == 21) {
            cout << "\n--- Registrar Día Completado ---\n";
            if (objetivosActivos.empty()) {
                cout << "No hay objetivos activos para actualizar.\n";
                continue;
            }
            string objetivoId;
            cout << "Ingrese ID del objetivo a actualizar: "; getline(cin, objetivoId);

            stack<Objetivo> tempStack;
            bool found = false;
            while (!objetivosActivos.empty()) {
                Objetivo obj = objetivosActivos.top();
                objetivosActivos.pop();
                if (obj.objetivoId == objetivoId) {
                    obj.incrementDays();
                    cout << "Día registrado para objetivo " << objetivoId << ". Progreso: " << obj.currentDays << "/" << obj.targetDays << endl;
                    found = true;
                }
                tempStack.push(obj);
            }
            while (!tempStack.empty()) {
                objetivosActivos.push(tempStack.top());
                tempStack.pop();
            }
            if (!found) {
                cout << "Objetivo con ID " << objetivoId << " no encontrado entre los objetivos activos.\n";
            }
        }
        else if (opcion == 22) {
            cout << "\n--- Archivar Objetivos Completados/Expirados ---\n";
            stack<Objetivo> nuevosActivos;
            int archivados = 0;
            while (!objetivosActivos.empty()) {
                Objetivo obj = objetivosActivos.top();
                objetivosActivos.pop();
                obj.updateStatus(); // Ensure status is up-to-date
                if (obj.estado == Objetivo::Estado::Achieved || obj.estado == Objetivo::Estado::Expired) {
                    objetivosHistoricos.insertar(obj);
                    archivados++;
                }
                else {
                    nuevosActivos.push(obj);
                }
            }
            objetivosActivos = nuevosActivos;
            cout << "Objetivos archivados: " << archivados << endl;
        }
        else if (opcion == 23) {
            cout << "\n--- Eliminar Objetivo ---\n";
            string objetivoId;
            cout << "Ingrese ID del objetivo a eliminar: "; getline(cin, objetivoId);
            stack<Objetivo> nuevosActivos;
            int eliminados = 0;
            while (!objetivosActivos.empty()) {
                Objetivo obj = objetivosActivos.top();
                objetivosActivos.pop();
                if (obj.objetivoId == objetivoId) {
                    eliminados++;
                }
                else {
                    nuevosActivos.push(obj);
                }
            }
            objetivosActivos = nuevosActivos;

            // Eliminar de objetivos históricos
            objetivosHistoricos.eliminar([&](Objetivo obj) {
                return obj.objetivoId == objetivoId;
                });

            cout << "Objetivos eliminados: " << eliminados << endl;
        }

        else if (opcion == 24) {
            cout << "\n--- Objetivos Activos ---\n";
            stack<Objetivo> temp = objetivosActivos;

            while (!temp.empty()) {
                Objetivo obj = temp.top();
                temp.pop();

                cout << "ID: " << obj.objetivoId
                    << " | Cliente: " << obj.clienteId
                    << " | Progreso: " << obj.currentDays << "/" << obj.targetDays
                    << " | Estado: ";

                switch (obj.estado) {
                case Objetivo::Estado::InProgress:
                    cout << "En progreso"; break;
                case Objetivo::Estado::Achieved:
                    cout << "Completado"; break;
                case Objetivo::Estado::Expired:
                    cout << "Expirado"; break;
                }
                cout << "\n";
            }
        }
        else if (opcion == 25) {
            // Guardar pagos al salir del programa
            guardarPagos(pagos, NOMBRE_ARCHIVO_PAGOS);
            cout << "Saliendo del programa..." << endl;
            return 0;
        }
        else if (opcion == 26) { // registrar Trainer (Arbol Binario)
            cout << "\n--- Registrar Trainer ---\n";
            string id, name, especialidad;
            cout << "Ingrese ID del trainer: "; getline(cin, id);
            cout << "Ingrese nombre del trainer: "; getline(cin, name);
            cout << "Ingrese especialidad del trainer: "; getline(cin, especialidad);
            arbolTrainers.insertar(trainer(id, name, especialidad));
            cout << "Trainer registrado exitosamente en el árbol binario.\n";
        }
        else if (opcion == 27) { // Buscar Trainer (Arbol Binario)
            cout << "\n--- Buscar Trainer ---\n";
            string id;
            cout << "Ingrese ID del trainer a buscar: "; getline(cin, id);
            trainer searchTrainer(id, "", ""); 
            if (arbolTrainers.buscar(searchTrainer)) {
                cout << "Trainer encontrado.\n";
            } else {
                cout << "Trainer no encontrado.\n";
            }
        }
        else if (opcion == 28) { // Eliminar Trainer (Arbol Binario)
            cout << "\n--- Eliminar Trainer ---\n";
            string id;
            cout << "Ingrese ID del trainer a eliminar: "; getline(cin, id);
            trainer deleteTrainer(id, "", ""); 
            arbolTrainers.eliminar(deleteTrainer);
            cout << "Trainer eliminado (si existía).\n";
        }
        else if (opcion == 29) { // Mostrar Trainers (Arbol Binario)
            cout << "\n--- Trainers Registrados (Inorden) ---\n";
            arbolTrainers.inorden([](trainer t) {
                cout << "ID: " << t.id << ", Nombre: " << t.nme << ", Especialidad: " << t.especialidad << endl;
            });
        }
        else if (opcion == 30) { // Registrar Clase (Arbol Binario)
            cout << "\n--- Registrar Clase ---\n";
            string id, nombre, horario;
            cout << "Ingrese ID de la clase: "; getline(cin, id);
            cout << "Ingrese nombre de la clase: "; getline(cin, nombre);
            cout << "Ingrese horario de la clase: "; getline(cin, horario);
            arbolClases.insertar(clase(id, nombre, horario));
            cout << "Clase registrada exitosamente en el árbol binario.\n";
        }
        else if (opcion == 31) { // Buscar Clase (Arbol Binario)
            cout << "\n--- Buscar Clase ---\n";
            string id;
            cout << "Ingrese ID de la clase a buscar: "; getline(cin, id);
            clase searchClase(id, "", ""); // 
            if (arbolClases.buscar(searchClase)) {
                cout << "Clase encontrada.\n";
            } else {
                cout << "Clase no encontrada.\n";
            }
        }
        else if (opcion == 32) { // Eliminar Clase (Arbol Binario)
            cout << "\n--- Eliminar Clase ---\n";
            string id;
            cout << "Ingrese ID de la clase a eliminar: "; getline(cin, id);
            clase deleteClase(id, "", ""); 
            arbolClases.eliminar(deleteClase);
            cout << "Clase eliminada (si existía).\n";
        }
        else if (opcion == 33) { // Mostrar Clases (Arbol Binario - Inorden)
            cout << "\n--- Clases Registradas (Inorden) ---\n";
            arbolClases.inorden([](clase c) {
                cout << "ID: " << c.id << ", Nombre: " << c.nombre << ", Horario: " << c.horario << endl;
            });
        }
        else {
            cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (true);

    return 0;
}
