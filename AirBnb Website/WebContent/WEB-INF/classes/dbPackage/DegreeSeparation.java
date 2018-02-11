package dbPackage;

import java.sql.*; 

public class DegreeSeparation {

	public int FindDegree(String login1, String login2)
	{
		int degree = 0; 
		
		try
		{
			Connector con = new Connector(); 
			
			int uid1 = Trust.GetUIDFromLogin(login1); 
			int uid2 = Trust.GetUIDFromLogin(login2); 
			
			String query = "SELECT F1.favorite_hid FROM Favorites F1, Favorites F2 WHERE F1.favorite_uid = "+uid1+" AND F2.favorite_uid ="+uid2
					+ " AND F1.favorite_hid = F2.favorite_hid"; 
			
			ResultSet rs = con.stmt.executeQuery(query); 
			while(rs.next())
			{
				int fave = rs.getInt("F1.favorite_hid"); 
				System.out.println(fave); 
				degree = 1; 				
			}
			
			con.closeConnection();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		
		return degree; 
	}
}

