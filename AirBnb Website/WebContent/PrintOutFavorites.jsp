<%@ page language="java" import ="dbPackage.*" %><html>
<head>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Your Favorite Lisitings</title>
</head>
<body>
<h3 style="text-align:center">Your Favorite Lisitings</h3>
<% 
    String n = session.getAttribute("userID").toString();
	int owner_id = Integer.parseInt(n);

	Favorite f = new Favorite(owner_id); 
	
	if(f.visited.size() == 0)
	{
		out.println("<h5>" + " You don't have any favorite listings."+ "</5>"); 
		response.sendRedirect("favouriteListing.jsp");
	}		
%>
<div>
<ul>
	<% for(int i = 0; i < f.faves.size(); i++) 
	{ %>

		<%= f.faves.get(i).name  %><br>
		<%= f.faves.get(i).address %><br> 
		<br>
 <% }  %>
</ul>
<a href="favouriteListing.jsp">Back</a>
</div>	
</body>
</html>