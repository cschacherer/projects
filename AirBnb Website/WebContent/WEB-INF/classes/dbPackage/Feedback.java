package dbPackage;

import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;

public class Feedback implements Comparable<Feedback>{
	public int fid; 
	public int uid; 
	public int hid; 
	public int score; 
	public String text;
	public String date;
	public double usefulness;

	// default constructor
	public Feedback()
	{
		fid = -1;
		uid = -1;
		hid = -1;
		score = 0;
		text = " ";
		date = " ";
		usefulness = 0.0;
	}


	//constructor that creates new user feedback
	public Feedback(int FID)
	{
		try
		{
			Connector con = new Connector();
			String query = "SELECT * FROM Feedback WHERE f_id = '"+FID+"'"; 
			ResultSet rs = con.stmt.executeQuery(query); 

			while(rs.next())
			{
				fid = rs.getInt("f_id"); 
				uid = rs.getInt("feedback_uid");
				hid = rs.getInt("feedback_hid");
				score = rs.getInt("score");
				text = rs.getString("text");
				usefulness = GetUsefulnessRating(); 
			}
			con.closeConnection();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
	}
	
	public boolean inFeedback()
	{
		try
		{
			Connector con = new Connector();
			//add info to database
			String query = "SELECT * FROM Feedback WHERE feedback_hid = "+hid+" AND feedback_uid ="+uid;  
			ResultSet rs = con.stmt.executeQuery(query);
			
			if(rs.next())
			{
				con.closeConnection();
				return true;
			}
			
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		return false; 
	}

	//adds the Feedback to the database. 
	public void AddToDatabase()
	{
		try
		{
			Connector con = new Connector();
			//add info to database
			String query = "INSERT INTO Feedback(feedback_uid, feedback_hid, score, text, date) "
							+ "VALUES('"+uid+"', '"+hid+"', '"+score+"', '"+text+"', '"+date+"')"; 
			
			int insertResult = con.stmt.executeUpdate(query);
			if(insertResult > 0)
			{
				System.out.println ("Feedback added to database.");
			}
			else
			{
				System.out.println ("Feedback NOT added to database.");
			}

			//get Feedback id
			query = "SELECT f_id FROM Feedback WHERE feedback_uid ='"+uid+"' AND feedback_hid ='"+hid+"'"; 
			ResultSet rs = con.stmt.executeQuery(query); 
			if(rs.next())
			{
				fid = rs.getInt("f_id"); 
			}
			con.closeConnection();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
	}

	//Get Hotel name that a feedback is for
	public String GetHotelName()
	{
		String n = ""; 
		try
		{
			Connector con = new Connector(); 
			String query = "SELECT name FROM Housing WHERE h_id = '"+hid+"'"; 
			ResultSet rs = con.stmt.executeQuery(query); 

			if(rs.next())
			{
				n = rs.getString("name"); 
			}
			con.closeConnection();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage()); 
		}
		return n; 
	}


	//Get user first name that wrote feedback
	private String GetUsername()
	{
		String n = ""; 
		try
		{
			Connector con = new Connector(); 
			String query = "SELECT login FROM Users WHERE u_id = '"+uid+"'"; 
			ResultSet rs = con.stmt.executeQuery(query); 

			if(rs.next())
			{
				n = rs.getString("login"); 
			}
			con.closeConnection();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage()); 
		}
		return n; 
	}

	public List<Feedback> GetFeedback(int hotel_id)
	{
		List<Feedback> f = new ArrayList<Feedback>(); 
		try
		{
			Connector con = new Connector(); 
			String query = "SELECT * FROM Feedback WHERE feedback_hid = "+hotel_id; 
			ResultSet rs = con.stmt.executeQuery(query); 
			while(rs.next())
			{
				Feedback newFeedback = new Feedback(); 
				
				newFeedback.fid = rs.getInt("f_id");  
				newFeedback.date = rs.getString("date"); 
				newFeedback.score = rs.getInt("score");
				newFeedback.text = rs.getString("text"); 
				newFeedback.uid = rs.getInt("feedback_uid");
				newFeedback.hid = rs.getInt("feedback_hid");

				newFeedback.usefulness = newFeedback.GetUsefulnessRating();

				f.add(newFeedback); 
			}
			con.closeConnection();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage()); 
		}
		return f;

	}

	//Get usefulness of rating - Average on 
	public double GetUsefulnessRating()
	{
		int sum = 0;
		double usefulRate = 0;
		try
		{
			Connector con = new Connector(); 
			String query = "SELECT rating FROM Ratings WHERE rating_fid = '"+fid+"'";
			ResultSet rs = con.stmt.executeQuery(query);

			List<Integer> allrates = new ArrayList<Integer>(); 
			while(rs.next())
			{
				int rate = rs.getInt("rating"); 
				allrates.add(rate); 
				sum = sum+rate;
			}

			if(allrates.size() == 0)
			{
				usefulRate = 0; 
			}
			else
			{
				usefulRate  = sum / allrates.size();
			}

			con.closeConnection();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage()); 
		}	 
		return usefulRate;
	}


	//print feedbacks
	public void PrintFeedBacks()
	{
		String hName = GetHotelName(); 
		String uName = GetUsername();
		System.out.println("Hotel Name: " + hName);
		System.out.println("User Name: " + uName);
		System.out.println("Score: "+score);
		System.out.println("Feedback: "+text);
		System.out.println("Date: "+date);
		System.out.println("Usefullness: "+usefulness);

	}


	public int compareTo(Feedback o) {
		return this.usefulness > o.usefulness? 1 : (this.usefulness < o.usefulness? -1: 0);
	}

    @Override
    public String toString(){
        return String.valueOf(usefulness);
    }
}

