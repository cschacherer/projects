package dbPackage;

import java.util.*;
import java.sql.*;

public class Trust{
	
	public int uid; 
	public List<Integer> trusted; 
	public List<Integer> notTrusted;
	
	public Trust(int UID)
	{
		uid = UID;  
	}
	
	public List<String> GetTrustedUsers()
	{
		List<String> trustedUsers = new ArrayList<String>(); 
		try
		{
			Connector con = new Connector(); 
			
			String query = "SELECT trusted_tuid FROM TrustedUser WHERE trusted_uid = "+uid +" AND isTrusted = 1"; 
			ResultSet rs = con.stmt.executeQuery(query); 
			
			while(rs.next())
			{
				int tuid = rs.getInt("trusted_tuid"); 
				User u = new User(tuid); 
				trustedUsers.add(u.login); 
			}
			
			con.closeConnection();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		return trustedUsers; 
	}
	
	public List<String> GetNotTrustedUsers()
	{
		List<String> notTrusted = new ArrayList<String>(); 
		try
		{
			Connector con = new Connector(); 
			
			String query = "SELECT trusted_tuid FROM TrustedUser WHERE trusted_uid = "+uid +" AND isTrusted = 0"; 
			ResultSet rs = con.stmt.executeQuery(query); 
			
			while(rs.next())
			{
				int tuid = rs.getInt("trusted_tuid"); 
				User u = new User(tuid); 
				notTrusted.add(u.login); 
			}
			
			con.closeConnection();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		return notTrusted; 
	}
	
	public boolean AddTrusted(String login, int t)
	{
		try
		{
			Connector con = new Connector(); 
			
			int tuid = GetUIDFromLogin(login); 
			
			String query = "INSERT INTO TrustedUser(trusted_uid, trusted_tuid, isTrusted) "
					+ "VALUE('"+uid+"', '"+tuid+"', "+t+")";
			
			int result = con.stmt.executeUpdate(query); 
			if(result > 0)
			{
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
	
	public static int GetUIDFromLogin(String login)
	{
		int id = -1; 
		try
		{
			Connector con = new Connector(); 
			
			String query = "SELECT u_id FROM Users WHERE login = '"+login+"'"; 
			ResultSet rs = con.stmt.executeQuery(query); 
			
			if(rs.next())
			{
				id = rs.getInt("u_id"); 
			}
			
			con.closeConnection();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		return id; 
	}
	
	public static void PrintAllLogins()
	{
		try
		{
			Connector con = new Connector(); 
			String query = "SELECT login FROM Users"; 
			ResultSet rs = con.stmt.executeQuery(query); 
			
			while(rs.next())
			{
				String login = rs.getString("login"); 
				System.out.println(login);
			}
			
			con.closeConnection();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
	}
	
	public static List<String> ReturnAllLogins()
	{
		List<String> allLogins = new ArrayList<String>(); 
		try
		{
			Connector con = new Connector(); 
			String query = "SELECT login FROM Users"; 
			ResultSet rs = con.stmt.executeQuery(query); 
			
			while(rs.next())
			{
				String login = rs.getString("login"); 
				allLogins.add(login); 
			}
			
			con.closeConnection();
			
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		return allLogins; 
	}
}

