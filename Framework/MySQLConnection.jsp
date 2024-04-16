<%-- Setting connection object as session attribute --%>

<%@ page import="java.sql.*" %>
<%
    if (session.getAttribute("dbConnection") == null) {
        Connection conn = null;
        String host = "138.68.140.83";
        String username = "Ajay";
        String password = "Ajay@123";
        String databaseName = "dbAjay";

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://" + host + ":3306/" + databaseName, username, password);
            session.setAttribute("dbConnection", conn);
            session.setAttribute("database", databaseName);
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            
        }
    }
%>
