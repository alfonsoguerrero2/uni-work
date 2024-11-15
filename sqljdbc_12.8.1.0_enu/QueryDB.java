import java.io.*;
import java.sql.*;
import java.util.*;

/**
 * Example of how to query a database using JDBC.
 *
 * <p>
 * The program demonstrates
 * </p>
 * <ul>
 * <li>Use of properties to hold JDBC driver and database details</li>
 * <li>Use of the SQL command SELECT</li>
 * <li>Processing of ResultSet objects</li>
 * </ul>
 *
 * @author Karim Djemame and Nick Efford
 * @version 2.2 [2024-10-02]
 */

public class QueryDB {

  /**
   * Establishes a connection to the database.
   *
   * The details of which driver to use, which database to
   * access and the username and password to use are being
   * hard-coded.
   * Refer to the connection string, JDBC SQL authentication
   * on Azure
   *
   * @return Connection object representing the connection
   * @throws IOException  if properties file cannot be accessed
   * @throws SQLException if connection fails
   */

  public static Connection getConnection() throws IOException, SQLException {

    //
    String url = "jdbc:sqlserver://myfreeserver1.database.windows.net:1433;database=database1;user=Alfonso@myfreeserver1;password={Frutilla123};encrypt=true;trustServerCertificate=false;hostNameInCertificate=*.database.windows.net;loginTimeout=30;";

    Connection connection = null;

    try {
      // Load the SQL Server JDBC driver

      // Establish the connection
      connection = DriverManager.getConnection(url);

    } catch (SQLException e) {
      System.err.println("Connection failed.");
      e.printStackTrace();
      throw e;
    }

    return connection;
  }

  /**
   * Queries the database to find student names.
   *
   * @param forename forename to search for in database
   * @param database connection to database
   * @throws SQLException if query fails
   */

  public static void findNames(String forename, Connection database)
      throws SQLException {
    Statement statement = database.createStatement();
    ResultSet results = statement.executeQuery(
        "SELECT * FROM students");
    while (results.next()) {
      String surname = results.getString("surname");
      String forename2 = results.getString("forename");
      System.out.println(forename2 + " " + surname);
      // System.out.println(results);
    }
    statement.close();
  }

  /**
   * Main program.
   */

  public static void main(String[] argv) {
    if (argv.length == 0) {
      System.err.println("usage: java QueryDB <forename>");
      System.exit(1);
    }

    Connection connection = null;

    try {
      connection = getConnection();
      findNames(argv[0], connection);
    } catch (Exception error) {
      error.printStackTrace();
    } finally {

      // This will always execute, even if an exception has
      // been thrown elsewhere in the code - so this is
      // the ideal place to close the connection to the DB...

      if (connection != null) {
        try {
          connection.close();
        } catch (Exception error) {
        }
      }
    }
  }

}
