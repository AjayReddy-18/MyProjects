<%-- JSP file to store table details --%>

<%@ page contentType="application/json;charset=UTF-8" %>
<%@ page language="java" %>
<%@ include file="MySQLConnection.jsp" %>
<%@ page import="java.util.ArrayList" %>
<%@ page import="java.util.List" %>
<%@ page import="org.json.JSONObject" %>

<%
    String tableName = "Cashier";
    if ((String)session.getAttribute("tableName") != tableName || session.getAttribute("fields") == null || session.getAttribute("fieldsCount") == null) {
        Statement statement = null;
        ResultSet resultSet = null;
        List<String> fieldsList = new ArrayList<String>();
        try {
            String databaseName = (String) session.getAttribute("database");

            Connection conn = (Connection) session.getAttribute("dbConnection");
            statement = conn.createStatement();
            resultSet = statement.executeQuery("SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_SCHEMA = '" + databaseName + "' AND TABLE_NAME = '" + tableName + "' ORDER BY ORDINAL_POSITION");

            while (resultSet.next()) {
                fieldsList.add(resultSet.getString("COLUMN_NAME"));
            }

            int fieldsCount = fieldsList.size();
            String[] fields = fieldsList.toArray(new String[0]);

            session.setAttribute("tableName", tableName);
            session.setAttribute("fields", fields);
            session.setAttribute("fieldsCount", fieldsCount);
        } catch (SQLException error) {
            error.printStackTrace();
        } finally {
            try {
                if (resultSet != null) resultSet.close();
                if (statement != null) statement.close();
                // if (conn != null) conn.close();
            } catch (SQLException error) {
                error.printStackTrace();
            }
        }
    }

    String stableName = (String) session.getAttribute("tableName");
    String[] fields = (String[]) session.getAttribute("fields");
    int fieldsCount = (Integer) session.getAttribute("fieldsCount");

    JSONObject jsonObject = new JSONObject();
    jsonObject.put("tableName", stableName);
    jsonObject.put("fields", fields);
    jsonObject.put("fieldsCount", fieldsCount);

    String jsonResult = jsonObject.toString();

    out.println(jsonResult);
%>