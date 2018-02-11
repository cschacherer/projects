<%@ page language="java" import ="dbPackage.*" %><html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Add Listing</title>
<script LANGUAGE="javascript">
var index;
function addFav(owner_id){
	//index = document.getElementById("demo").innerHTML;
	index = owner_id;
	request.setAttribute("index", owner_id);
}
</script>
</head>
<body>
<h3 style="text-align:center">Add Favorite/s Listings</h3>
<% 
    String n = session.getAttribute("userID").toString();
	int owner_id = Integer.parseInt(n);

	Favorite f = new Favorite(owner_id); 
	
	if(f.visited.size() == 0)
	{
		out.println("<h5>" + " You have not visited anywhere."+ "</5>"); 
		response.sendRedirect("favouriteListing.jsp");
	}else
	{		
%>
<div>
<ul>
	<% for(int i = 0; i < f.visited.size(); i++) 
	{ %>
	
		<%= f.visited.get(i).name  %><br>
		<%= f.visited.get(i).address %><br> 
		<a href="addListing.jsp?index=<%=i%>#addbtn">Add</a><br>
		<br>
	
	<% }  %>
</ul>
</div>				

<div id="addbtn">
<%
	String f_t = (String)request.getParameter("index");
	if(f_t != null)
	{
		//out.println(f_t);
		int f_index = Integer.parseInt(f_t);
		boolean result = f.AddFaveToDatabase(f.visited.get(f_index)); 
		if(result)
		{
			out.println("Fave added!\n"); 
		}
		else
		{
			out.println("There was an error.  Try again.\n");
		}
		
		%><a href="favouriteListing.jsp">Back</a><% 
		
	}
}
%>
</div>
</body>
</html>