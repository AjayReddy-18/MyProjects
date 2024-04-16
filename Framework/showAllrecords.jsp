<%-- returning all the records of a table --%>

<%@ page import="java.sql.*" %>
<%@ page contentType="application/json; charset=UTF-8" %>

<%
Statement statement = null;
ResultSet resultSet = null;
String jsonResponse = "";
String tableName = (String) session.getAttribute("tableName");
String whereClause = request.getParameter("where");

try {
		Connection conn = (Connection) session.getAttribute("dbConnection");
	    statement = conn.createStatement();
	    resultSet = statement.executeQuery("SELECT JSON FROM v" + tableName + " WHERE " + whereClause);

	    jsonResponse += "[";

	    while (resultSet.next())
	    {
	       jsonResponse += resultSet.getString("JSON");
	       jsonResponse += ",";
	    }

	    jsonResponse = jsonResponse.substring(0, jsonResponse.length() - 1);
	    jsonResponse += "]";
	} 
	catch (SQLException error) 
	{
	    error.printStackTrace();
	    jsonResponse = "{\"error\": \"Failed to retrieve items: " + error.getMessage() + "\"}";

	} 
finally 
{
    try 
    {
        if (resultSet != null) resultSet.close();
        if (statement != null) statement.close();
        // if (conn != null) conn.close();
    } 
    catch (SQLException error) 
    {
        error.printStackTrace();
        jsonResponse = "{\"error\": \"Failed to close resources: " + error.getMessage() + "\"}";
    }
}

out.print(jsonResponse);
%>