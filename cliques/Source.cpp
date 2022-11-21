#include <stdlib.h>
#include <iostream>
#include "config.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "CliquesInteraction/SqlCliqueFiller.h"



int main() {
    sql::Driver* driver;
    sql::Connection* con;

    try {
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
    }
    catch (sql::SQLException e) {
        std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
        exit(1);
    }
    
    con->setSchema("alt_exam");
    SqlCliqueFiller cliqueFiller(con);
    try {
        cliqueFiller.fillCliquesAuthors();
        std::cout << "Authors found" << std::endl;
        cliqueFiller.updateCliquesCiting(false);
        std::cout << "Authors coefficients found" << std::endl;

        cliqueFiller.fillCliquesCoauthors();
        std::cout << "Coauthors coefficients found" << std::endl;
        cliqueFiller.updateCliquesCiting(true);
        std::cout << "Coauthors coefficients found" << std::endl;
    }
    catch (sql::SQLException& e) {
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line " 
            << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }

    delete con;
    return 0;
}