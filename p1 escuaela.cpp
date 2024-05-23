 #include <iostream>
#include <C:\MySQL\MySQL Connector C++ 8.4\include\mysql\jdbc.h>  


using namespace sql::mysql;

MySQL_Driver *driver;
sql::Connection *con;


void connectDB() {
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "root");
    con->setSchema("bd_Escuela");
}


void createEstudiante(std::string codigo, std::string nombres, std::string apellidos, std::string direccion, int telefono, std::string fecha_nacimiento, int id_tipo_sangre) {
    try {
        connectDB();
        sql::PreparedStatement *pstmt;
        pstmt = con->prepareStatement("INSERT INTO estudiantes(codigo, nombres, apellidos, direccion, telefono, fecha_nacimiento, id_tipo_sangre) VALUES (?, ?, ?, ?, ?, ?, ?)");
        pstmt->setString(1, codigo);
        pstmt->setString(2, nombres);
        pstmt->setString(3, apellidos);
        pstmt->setString(4, direccion);
        pstmt->setInt(5, telefono);
        pstmt->setString(6, fecha_nacimiento);
        pstmt->setInt(7, id_tipo_sangre);
        pstmt->execute();
        delete pstmt;
        delete con;
    } catch (sql::SQLException &e) {
        std::cerr << "Error al crear estudiante: " << e.what() << std::endl;
    }
}

//  leer todos los estudiantes
void readEstudiantes() {
    try {
        connectDB();
        sql::Statement *stmt;
        sql::ResultSet *res;
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM estudiantes");
        while (res->next()) {
            std::cout << "ID: " << res->getInt("id_estudiante")
                      << ", Codigo: " << res->getString("codigo")
                      << ", Nombres: " << res->getString("nombres")
                      << ", Apellidos: " << res->getString("apellidos")
                      << ", Dirección: " << res->getString("direccion")
                      << ", Teléfono: " << res->getInt("telefono")
                      << ", Fecha de Nacimiento: " << res->getString("fecha_nacimiento")
                      << ", ID Tipo Sangre: " << res->getInt("id_tipo_sangre")
                      << std::endl;
        }
        delete res;
        delete stmt;
        delete con;
    } catch (sql::SQLException &e) {
        std::cerr << "Error al leer estudiantes: " << e.what() << std::endl;
    }
}

//  actualizar un estudiante existente
void updateEstudiante(int id, std::string codigo, std::string nombres, std::string apellidos, std::string direccion, int telefono, std::string fecha_nacimiento, int id_tipo_sangre) {
    try {
        connectDB();
        sql::PreparedStatement *pstmt;
        pstmt = con->prepareStatement("UPDATE estudiantes SET codigo=?, nombres=?, apellidos=?, direccion=?, telefono=?, fecha_nacimiento=?, id_tipo_sangre=? WHERE id_estudiante=?");
        pstmt->setString(1, codigo);
        pstmt->setString(2, nombres);
        pstmt->setString(3, apellidos);
        pstmt->setString(4, direccion);
        pstmt->setInt(5, telefono);
        pstmt->setString(6, fecha_nacimiento);
        pstmt->setInt(7, id_tipo_sangre);
        pstmt->setInt(8, id);
        pstmt->execute();
        delete pstmt;
        delete con;
    } catch (sql::SQLException &e) {
        std::cerr << "Error al actualizar estudiante: " << e.what() << std::endl;
    }
}

//  eliminar un estudiante
void deleteEstudiante(int id) {
    try {
        connectDB();
        sql::PreparedStatement *pstmt;
        pstmt = con->prepareStatement("DELETE FROM estudiantes WHERE id_estudiante=?");
        pstmt->setInt(1, id);
        pstmt->execute();
        delete pstmt;
        delete con;
    } catch (sql::SQLException &e) {
        std::cerr << "Error al eliminar estudiante: " << e.what() << std::endl;
    }
}

// principal
int main() {
    // Crear un estudiante
    createEstudiante("C0oo", "manuel", "maroquin", "Calle 23", 16787779, "2000-08-01", 1);

    // Leer estudiantes
    readEstudiantes();

    // Actualizar un estudiante
    updateEstudiante(1, "C001", "Juan", "Perez", "te pesco 036", 878787721, "2020-9-21", 2);

    // Eliminar un estudiante
    deleteEstudiante(1);

    return 0;
}
