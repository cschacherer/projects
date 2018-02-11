package dbPackage;

import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class UserAwards {
	public List<User> UsersUsefulFeedback()
	{
		List<User> result = new ArrayList<User>();
		try
		{
			Connector con = new Connector();
			String query = "SELECT u_id FROM Users, Feedback WHERE u_id = feedback_uid";
			ResultSet rs = con.stmt.executeQuery(query);
			
			Map<Integer, Double> dic = new HashMap<Integer, Double>();
			while(rs.next())
			{
				int uid = rs.getInt("u_id");
				double s = AverageUsefulness(uid);
				dic.put(uid, s);
			}
						
			double highestAvg = Collections.max(dic.values());
			for(Map.Entry<Integer, Double> entry : dic.entrySet())
			{
				if(entry.getValue() == highestAvg)
				{
					int uid = entry.getKey();
					User s = new User(uid);
					result.add(s);
				}
			}
			con.closeConnection();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		
		return result;
	}
	
	public double AverageUsefulness(int user_id)
	{
		double sum = 0.0;
		double result = 0.0;
		List<Feedback> AvgFeedback = new ArrayList<Feedback>();

		try
		{
			Connector con = new Connector();
 		    String query = "SELECT f_id FROM Feedback WHERE feedback_uid = "+user_id;
 		    ResultSet rs = con.stmt.executeQuery(query);
			while(rs.next())
			{
				int fid = rs.getInt("feedback_fid"); 
				Feedback viewfeedback = new Feedback(fid);
				AvgFeedback.add(viewfeedback);
			}
			
			for(int i = 0 ; i < AvgFeedback.size(); i++)
			{
				sum += AvgFeedback.get(i).usefulness;
			}	
			result = sum/AvgFeedback.size();
			
			con.closeConnection();
          
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
	    }
		return result;
		
	}
}
