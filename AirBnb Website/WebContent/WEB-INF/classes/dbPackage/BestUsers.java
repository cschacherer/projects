package dbPackage;

import java.util.*;
import java.sql.*;


public class BestUsers {

	public List<String> GetTrustedUsers()
	{
		List<String> mostTrusted = new ArrayList<String>(); 
		try
		{
			Connector con = new Connector(); 
			String query = "SELECT trusted_tuid, isTrusted FROM TrustedUser"; 
			ResultSet rs = con.stmt.executeQuery(query); 
			
			Map<Integer, List<Integer>> trusted = new HashMap<Integer, List<Integer>>(); 
			
 			while(rs.next())
			{
				int uid = rs.getInt("trusted_tuid"); 
			}
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		return mostTrusted; 
	}
}
