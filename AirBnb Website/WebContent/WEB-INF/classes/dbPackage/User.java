package dbPackage;

import java.util.*;
import java.sql.*;

public class User {
	
	public int uid; 
	public String firstName; 
	public String lastName;
	public String login; 
	public String password;
	public String address; 
	public String phoneNumber; 
	
	//basic user constructor
	public User()
	{
		uid = -1; 
		firstName = ""; 
		lastName = ""; 
		login = ""; 
		password = ""; 
		address = ""; 
		phoneNumber = ""; 
	}
	
	//user constructor that creates a new user from the database from the given uid
	public User(int UID)
	{
		try
		{
			Connector con = new Connector(); 
	        String query = "SELECT * FROM Users WHERE u_id = "+UID;
	        ResultSet rs = con.stmt.executeQuery(query); 
	        
	        while(rs.next())
	        {
	        	uid = rs.getInt("u_id"); 
	        	firstName = rs.getString("first_name"); 
	        	lastName = rs.getString("last_name"); 
	        	login = rs.getString("login"); 
	        	password = rs.getString("password"); 
	        	address = rs.getString("address"); 
	        	phoneNumber = rs.getString("phone_number"); 
	        }
	        
	        con.closeConnection(); 
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
	}
	
	//returns whether or not the user is in the database and is able to log in.  
	public boolean LoginUser()
	{
		try
		{
			Connector con = new Connector();
	        
	        String query;
			ResultSet results; 
			
			query="Select * from Users where login = '"+ login +"' and password = '"+password+"'";
			
			results = con.stmt.executeQuery(query); 
			
			while(results.next())
			{
				uid = results.getInt("u_id");
				firstName = results.getString("first_name"); 
				lastName = results.getString("last_name"); 
				login = results.getString("login"); 
				password = results.getString("password"); 
				address = results.getString("address"); 
				phoneNumber = results.getString("phone_number"); 
			}
			
			con.closeConnection(); 
			
			if(uid > 0)
			{
				//the query did work
				return true; 
			}
		}
		catch(Exception e)
		{
			System.out.println(e + ", " + e.getMessage());
		}
		return false; 
	}
	
	//gets a uid from the a login name. 
	public static int GetUID(String tempLogin)
	{
		try{
			Connector con = new Connector();
	        
	        String query;
			ResultSet results; 
			
			query="Select * from Users where login = '"+ tempLogin +"'";
			
			results = con.stmt.executeQuery(query); 
			
			int database_uid = -1; 
			
			if(results.next())
			{
				database_uid = results.getInt("u_id");
			}
			
			con.closeConnection(); 
			
			return database_uid; 
		}
		catch(Exception e)
		{
			System.out.println(e + ", " + e.getMessage());
		}
		return 1; 
	}
	
	//adds user information to database
	public boolean AddToDatabase()
	{
		try
		{
			Connector con = new Connector();
	        
	        String query;
			ResultSet results; 
			
			query="Select * from Users where login = '"+ login +"'";
			
			results = con.stmt.executeQuery(query); 
			
			if(results.next())
			{
				//there is a duplicate login
				System.out.println ("Login already exists.");
				con.closeConnection(); 
				return false; 
			}
			else
			{
				query = "INSERT INTO Users(first_name, last_name, login, password, address, phone_number)" +
						"VALUES('"+firstName+"', '"+lastName+"', '"+login+"', '"+password+"', '"+address+"', '"+phoneNumber+"')"; 
				int insertResult = con.stmt.executeUpdate(query);
				if(insertResult > 0)
				{
					System.out.println ("User added to database.");
				}
				else
				{
					System.out.println ("User NOT added to database.");
				}
				con.closeConnection();
				
				uid = GetUID(login); 
				if(uid > 0)
				{
					return true;
				}
			}
		}
		catch(Exception e)
		{
			System.out.println(e + ", " + e.getMessage());
		}
		return false; 
	}
	
	//gets a list of listings the user has put up 
	public List<House> UserListings()
	{
		List<House> listings = new ArrayList<House>(); 
		try
		{
			Connector con = new Connector();
	        String query = "SELECT h_id FROM Housing WHERE housing_uid ="+uid; 
	        ResultSet rs = con.stmt.executeQuery(query); 
	        List<Integer> housing_ids = new ArrayList<Integer>(); 
	        
	        while(rs.next())
	        {
	        	int hid = rs.getInt("h_id"); 
	        	housing_ids.add(hid); 
	        }
	        
	        for(int i = 0; i < housing_ids.size(); i++)
	        {
	        	House h = new House(housing_ids.get(i)); 
	        	listings.add(h); 
	        }  
	        con.closeConnection(); 
		}
		catch(Exception e)
		{
			System.out.println(e + ", " + e.getMessage());
		}
		return listings; 
	}
	
	//gets a list of reservations the user has made from the database.  
	public List<Reservation> UserReservations()
	{
		List<Reservation> reservations = new ArrayList<Reservation>();
		try
		{
			Connector con = new Connector(); 
			String query = "SELECT * FROM Reserve WHERE reserve_uid ="+uid; 
			ResultSet rs = con.stmt.executeQuery(query); 
			
			while(rs.next())
			{
				Reservation r = new Reservation(); 
				r.hid = rs.getInt("reserve_hid"); 
				r.uid = rs.getInt("reserve_uid"); 
				r.period.stringStart = rs.getString("startDate"); 
				r.period.stringEnd = rs.getString("endDate"); 
				r.people = rs.getInt("num_people"); 
				r.cost = rs.getInt("cost"); 
				
				r.period.StringToDate();
				
				reservations.add(r); 
			}
	        con.closeConnection(); 
			
		}
		catch(Exception e)
		{
			System.out.println(e + ", " + e.getMessage());
		}
		return reservations; 
	}
	
	//gets a list of places the user has visited
	public List<Visit> UserVisits()
	{
		List<Visit> visits = new ArrayList<Visit>(); 
		try
		{
			Connector con = new Connector(); 
			String query = "SELECT * FROM Visits WHERE visited_uid ="+uid; 
			ResultSet rs = con.stmt.executeQuery(query); 
			
			while(rs.next())
			{
				Visit v = new Visit(); 
				v.hid = rs.getInt("visited_hid"); 
				v.uid = rs.getInt("visited_uid"); 
				v.period.stringStart = rs.getString("startDate"); 
				v.period.stringEnd = rs.getString("endDate"); 
				v.people = rs.getInt("num_people"); 
				v.cost = rs.getInt("cost"); 
				
				v.period.StringToDate();
				
				visits.add(v); 
			}
	        con.closeConnection(); 
			
		}
		catch(Exception e)
		{
			System.out.println(e + ", " + e.getMessage());
		}
		return visits; 
	}
	
	//gets a list of favorite houses from users
	public List<House> UserFaves()
	{
		List<House> faves = new ArrayList<House>(); 
		try
		{
			Connector con = new Connector(); 
			
			//gets favorite hids from Favorite table
			String query = "SELECT favorite_hid FROM Favorites WHERE favorite_uid ="+uid; 
			ResultSet rs = con.stmt.executeQuery(query); 
			List<Integer> housing_ids = new ArrayList<Integer>(); 
			while(rs.next())
			{
				int hid = rs.getInt("favorite_hid"); 
				housing_ids.add(hid); 
			}
			
			//create houses from favorite hids
			for(int i = 0; i < housing_ids.size(); i++)
			{
				House h = new House(housing_ids.get(i)); 
				faves.add(h); 
			}
			con.closeConnection();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		return faves; 
	}
	
	//prints the user's attributes
	public void PrintAttributes()
	{
		System.out.println("Name: " + firstName + " " + lastName);
		System.out.println("Login: " + login); 
		System.out.println("Password: " + password); 
		System.out.println("Address: "+address); 
		System.out.println("Phone Number: "+ phoneNumber);
	}
}
