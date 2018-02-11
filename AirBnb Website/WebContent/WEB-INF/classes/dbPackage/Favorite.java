package dbPackage;

import java.util.*;
import java.sql.*;

//favorite class to hold a list of places the user has already visited and a list of favorites they have made
public class Favorite {
	public int uid; 
	public List<House> visited; 
	public List<House> faves; 
	
	public Favorite(int UID)
	{
		uid = UID; 
		GetVisits();
		GetFaves(); 
	}
	
	//gets a list of houses the user has visited before.  
	public void GetVisits()
	{
		visited = new ArrayList<House>(); 
		try
		{
			Connector con = new Connector(); 
			
			//get housing ids from visited table
			String query = "SELECT visited_hid FROM Visits WHERE visited_uid="+uid; 
			ResultSet rs = con.stmt.executeQuery(query); 
			List<Integer> housing_ids = new ArrayList<Integer>(); 

			while(rs.next())
			{
				int hid = rs.getInt("visited_hid");
				housing_ids.add(hid); 
			}

			//create houses from visited ids and adds it to visited list
			for(int i = 0; i < housing_ids.size(); i++)
			{
				House h = new House(housing_ids.get(i)); 
				visited.add(h); 
			}	
			con.closeConnection();
		}
		catch(Exception e)
		{
			System.out.println(e+", "+e.getMessage());
		}
	}
	
	//gets a list of places the user has already favorited
	public void GetFaves()
	{
		User u = new User(uid); 
		faves = u.UserFaves(); 
	}
	
	//adds a favorite place the the database
	public boolean AddFaveToDatabase(House h)
	{
		try
		{
			Connector con = new Connector(); 
			
			//gets favorite hids from Favorite table
			String query = "INSERT INTO Favorites(favorite_hid, favorite_uid) "
					+ "VALUE("+h.hid+", "+uid+")"; 
			int result = con.stmt.executeUpdate(query); 
			if(result > 0)
			{
				con.closeConnection();
				return true; 
			}
			
			con.closeConnection(); 
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		
		return false; 
	}
}
