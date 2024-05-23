#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;
using namespace sql;

// para crear un estudiante
void createStudent(Connection *con, int id, string codigo, string nombres, string apellidos, string direccion, int telefono, string fecha_nacimiento, int id_tipo_sangre) {
    PreparedStatement *pstmt;
    pstmt = con->prepareStatement("INSERT INTO estudiantes(id_estudiante, codigo, nombres, apellidos, direccion, telefono, fecha_nacimiento, id_tipo_sangre) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");

    pstmt->setInt(1, id);
    pstmt->setString(2, codigo);
    pstmt->setString(3, nombres);
    pstmt->setString(4, apellidos);
    pstmt->setString(5, direccion);
    pstmt->setInt(6, telefono);
    pstmt->setString(7, fecha_nacimiento);
    pstmt->setInt(8, id_tipo_sangre);

    pstmt->execute();
    delete pstmt;
}

//  para leer un estudiante
void readStudent(Connection *con, int id) {
    PreparedStatement *pstmt;
    ResultSet *res;
    
    pstmt = con->prepareStatement("SELECT * FROM estudiantes WHERE id_estudiante = ?");
    pstmt->setInt(1, id);
    res = pstmt->executeQuery();

    while (res->next()) {
        cout << "ID: " << res->getInt("id_estudiante") << endl;
        cout << "Codigo: " << res->getString("codigo") << endl;
        cout << "Nombres: " << res->getString("nombres") << endl;
        cout << "Apellidos: " << res->getString("apellidos") << endl;
        cout << "Direccion: " << res->getString("direccion") << endl;
        cout << "Telefono: " << res->getInt("telefono") << endl;
        cout << "Fecha de Nacimiento: " << res->getString("fecha_nacimiento") << endl;
        cout << "ID Tipo de Sangre: " << res->getInt("id_tipo_sangre") << endl;
    }

    delete res;
    delete pstmt;
}

//  para actualizar un estudiante
void updateStudent(Connection *con, int id, string codigo, string nombres, string apellidos, string direccion, int telefono, string fecha_nacimiento, int id_tipo_sangre) {
    PreparedStatement *pstmt;
    pstmt = con->prepareStatement("UPDATE estudiantes SET codigo=?, nombres=?, apellidos=?, direccion=?, telefono=?, fecha_nacimiento=?, id_tipo_sangre=? WHERE id_estudiante=?");

    pstmt->setString(1, codigo);
    pstmt->setString(2, nombres);
    pstmt->setString(3, apellidos);
    pstmt->setString(4, direccion);
    pstmt->setInt(5, telefono);
    pstmt->setString(6, fecha_nacimiento);
    pstmt->setInt(7, id_tipo_sangre);
    pstmt->setInt(8, id);

    pstmt->executeUpdate();
    delete pstmt;
}

// para eliminar un estudiante
void deleteStudent(Connection *con, int id) {
    PreparedStatement *pstmt;
    pstmt = con->prepareStatement("DELETE FROM estudiantes WHERE id_estudiante=?");
    pstmt->setInt(1, id);

    pstmt->execute();
    delete pstmt;
}

int main() {
    try {
        sql::mysql::MySQL_Driver *driver;
        sql::Connection *con;

        
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "user", "password");

        // Conectar a la base de datos
        con->setSchema("bd_nombre");

        // Crear un nuevo estudiante
        createStudent(con, 1, "A001", "Juan", "Perez", "Calle Falsa 123", 5551234, "2000-01-01", 1);

        // Leer un estudiante
        readStudent(con, 1);

        // Actualizar un estudiante
        updateStudent(con, 1, "A002", "Juan", "Gonzalez", "Calle Verdadera 456", 5555678, "2000-01-02", 2);

        // Eliminar un estudiante
        deleteStudent(con, 1);

        delete con;
    } catch (sql::SQLException &e) {
        cout << "Error: " << e.what();
        return 1;
    }

    return 0;
}
