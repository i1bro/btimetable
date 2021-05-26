#include <iostream>
#include <pqxx/pqxx>

int main() {
    try {
        pqxx::connection C(
            "host=retired.tk "
            "port=58974 "
            "user=postgres "
            "password=T38ssGHzjcRviche7ex "
            "dbname=postgres");
        std::cout << "Connected to " << C.dbname() << std::endl;
        pqxx::work W{C};

        W.exec(
            "DROP TABLE IF EXISTS companies CASCADE;"
            "DROP TABLE IF EXISTS clients CASCADE;"
            "DROP TABLE IF EXISTS employees CASCADE;"
            "DROP TABLE IF EXISTS orders CASCADE;"
            "DROP TABLE IF EXISTS client_accounts CASCADE;"
            "DROP TABLE IF EXISTS company_accounts CASCADE;");

        W.exec(
            "CREATE TABLE companies("
            "id BIGINT GENERATED ALWAYS AS IDENTITY,"
            "name VARCHAR(255) NOT NULL,"
            "rating_sum BIGINT DEFAULT 0,"
            "rating_cnt BIGINT DEFAULT 0,"
            "PRIMARY KEY(id)"
            ")");

        W.exec(
            "CREATE TABLE clients("
            "id BIGINT GENERATED ALWAYS AS IDENTITY,"
            "full_name VARCHAR(255) NOT NULL,"
            "phone_number VARCHAR(16),"
            "email varchar(100),"
            "PRIMARY KEY(id)"
            ")");

        W.exec(
            "CREATE TABLE employees("
            "id BIGINT GENERATED ALWAYS AS IDENTITY,"
            "company_id BIGINT NOT NULL,"
            "full_name VARCHAR(255) NOT NULL,"
            "rating_sum BIGINT DEFAULT 0,"
            "rating_cnt BIGINT DEFAULT 0,"
            "PRIMARY KEY(id),"
            "CONSTRAINT fk_company "
            "FOREIGN KEY(company_id) "
            "REFERENCES companies(id) "
            "ON DELETE CASCADE"
            ")");

        W.exec(
            "CREATE TABLE orders("
            "id BIGINT GENERATED ALWAYS AS IDENTITY,"
            "company_id BIGINT NOT NULL,"
            "title VARCHAR(255) NOT NULL,"
            "time_start BIGINT NOT NULL,"
            "duration BIGINT NOT NULL,"
            "client_id BIGINT DEFAULT NULL,"
            "employee_id BIGINT NOT NULL,"
            "status INT DEFAULT 0,"
            "rating INT DEFAULT 0,"
            "PRIMARY KEY(id),"
            "CONSTRAINT fk_company "
            "FOREIGN KEY(company_id) "
            "REFERENCES companies(id) "
            "ON DELETE CASCADE,"
            "CONSTRAINT fk_client "
            "FOREIGN KEY(client_id) "
            "REFERENCES clients(id) "
            "ON DELETE SET NULL,"
            "CONSTRAINT fk_employee "
            "FOREIGN KEY(employee_id) "
            "REFERENCES employees(id) "
            "ON DELETE CASCADE"
            ")");

        W.exec(
            "CREATE TABLE client_accounts("
            "phone_number VARCHAR(16) NOT NULL,"
            "password VARCHAR(255) NOT NULL,"
            "client_id BIGINT NOT NULL,"
            "PRIMARY KEY(phone_number),"
            "CONSTRAINT fk_client "
            "FOREIGN KEY(client_id) "
            "REFERENCES clients(id) "
            "ON DELETE CASCADE"
            ")");

        W.exec(
            "CREATE TABLE company_accounts("
            "phone_number VARCHAR(16) NOT NULL,"
            "password VARCHAR(255) NOT NULL,"
            "company_id BIGINT NOT NULL,"
            "PRIMARY KEY(phone_number),"
            "CONSTRAINT fk_company "
            "FOREIGN KEY(company_id) "
            "REFERENCES companies(id) "
            "ON DELETE CASCADE"
            ")");

        W.commit();
        std::cout << "OK.\n";
    } catch (std::exception const &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}
