<%-- inserting a new record or updating an existing record in a table  --%>

<%@ page import="java.sql.*" %>
<%@ page import="java.util.Arrays" %>
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>

<% 
	String[] columnNames = (String[]) session.getAttribute("fields");
	String values = request.getParameter("values");
	int columnsCount = columnNames.length;
	String columnsForSqlQuery = Arrays.toString(columnNames).replace("[", "(").replace("]", ")");

	String[] valuesArray = values.split(",");

	StringBuilder quotedValues = new StringBuilder();

	for (int i = 0; i < valuesArray.length; i++) {
		quotedValues.append("'").append(valuesArray[i]).append("'").append(",");
	}

	quotedValues.deleteCharAt(quotedValues.length() - 1);

	String valuesForSqlQuery = quotedValues.toString();

	try {
		String tableName = (String) session.getAttribute("tableName");
		Connection conn = (Connection) session.getAttribute("dbConnection");
		String sql = "INSERT INTO " + tableName + " " + columnsForSqlQuery + " VALUES (" + valuesForSqlQuery + ") ON DUPLICATE KEY UPDATE ";

		for (int i = 1; i < columnsCount; i++) {
			sql += columnNames[i] + " = VALUES(" + columnNames[i] + "),";
		}
		sql = sql.substring(0, sql.length() - 1);
		PreparedStatement statement = conn.prepareStatement(sql);
		int rowsInserted = statement.executeUpdate();
        if (rowsInserted > 0) {
            out.println("Success!");
        } else {
            out.println("Failed!");
        }

	} catch(Exception error) {
        out.println(error.getMessage());
	}
%>