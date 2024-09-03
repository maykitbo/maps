#include "postgis_connector.h"


using namespace maykitbo::maps;


int main()
{
    std::string connection_info =
        "dbname = osm_db user = postgres password = postgres hostaddr = 127.0.0.1 port = 5432";
    PostGISConnector db;

    db.connect(connection_info);  // Connect to the database

    // // Example of inserting data
    // db.insertData("INSERT INTO your_table(name, location) VALUES('Example Name', 'POINT(50 50)');");

    // Example of fetching data
    // db.fetchData("SELECT name, location FROM your_table;");

    db.listTablesAndSizes();

    return 0;
}   
