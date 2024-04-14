<%-- Deleting a record --%>

<%@ page import="java.sql.*" %>
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>

<%
	String tableName = (String) session.getAttribute("tableName");
	String primaryKey = request.getParameter("primaryKey");
	String primaryKeyValue = request.getParameter("primaryKeyValue");

	try{
		Connection conn = (Connection) session.getAttribute("dbConnection");
        String sql = "DELETE FROM " + tableName + " WHERE " + primaryKey + " = ?";
        PreparedStatement statement = conn.prepareStatement(sql);
        statement.setString(1, primaryKeyValue);
        int rowsInserted = statement.executeUpdate();
        if (rowsInserted > 0) {
            out.println("Deleted!");
        } else {
            out.println("Failed!");
        }
    } catch(Exception error) {
        out.println(error.getMessage());
    }
%>