package dbPackage;

import java.util.*;
import java.sql.*;
import java.util.concurrent.TimeUnit;

//reservation class to hold relevent reservation information
public class Reservation {
	public int hid; 
	public int uid; 
	public TimePeriod period;
	public int people; 
	public int cost; 
	
	public Reservation()
	{
		hid = -1; 
		uid = -1; 
		period = new TimePeriod(); 
		people = -1; 
		cost = -1; 
	}
	
	//easy way to print out a reservation
	public void PrintReservation()
	{
		String name = GetName(); 
		System.out.println("Name: " + name);
		System.out.println("Date: "+period.PrintDate());
		System.out.println("Number of People: "+people);
		System.out.println("Cost: "+cost);
	}
	
	//get's the house's name from the housing id
	public String GetName()
	{
		String n = ""; 
		try
		{
			Connector con = new Connector(); 
			String query = "SELECT name FROM Housing WHERE h_id = "+hid; 
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
	
	//adds reservation to Reserve database
	public boolean AddToDatabase(TimePeriod originalDate)
	{
		try
		{
			Connector con = new Connector(); 
			
			String query = "INSERT INTO Reserve(reserve_hid, reserve_uid, startDate, endDate, cost, num_people) "
					+ "VALUES ("+hid+", "+uid+", '"+period.stringStart+"', '"+period.stringEnd+"', "+cost+", "+people+")"; 
			
			int result = con.stmt.executeUpdate(query); 
			con.closeConnection();
			if(result > 0)
			{
				UpdateAvailableDates(originalDate); 
				return true; 
			}
			
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		return false; 
	}
	
	//This will update the house's available dates to remove the one that has the new reservation
	//If there is more than one day between the house's available start/end date and the reservation start/end date
	//then it will create a new available date between the house's available start/end and the reservation start/end
	private void UpdateAvailableDates(TimePeriod originalDate)
	{
		try
		{
			Connector con = new Connector(); 
			House h = new House(hid); 

			
			TimePeriod beforeReservation = new TimePeriod(); 
			TimePeriod afterReservation = new TimePeriod(); 
			
			originalDate.StringToDate();
			
			//get difference between the original available date and the reservation start date
			long beforeDiff = period.start.getTime() - originalDate.start.getTime(); 
			long beforeDays = TimeUnit.DAYS.convert(beforeDiff, TimeUnit.MILLISECONDS);

			//if there is at least a two day available difference, add the new available date
			if(beforeDays > 1)
			{
				beforeReservation.start = originalDate.start; 
				
				//adds days to a date
				//beforeReservation.end = new Date();
				Calendar c = Calendar.getInstance(); 
				c.setTime(beforeReservation.start); 
				c.add(Calendar.DATE, (int)beforeDays - 1);
				beforeReservation.end = c.getTime();
				
				beforeReservation.DateToString();
					
				h.openDates.add(beforeReservation); 
			}
			
			//get difference between the original available date and the reservation start date
			long afterDiff = originalDate.end.getTime() - period.end.getTime(); 
			long afterDays = TimeUnit.DAYS.convert(afterDiff, TimeUnit.MILLISECONDS);
			
			//if there is at least a two day difference between available and reserve, add the new available date
			if(afterDays > 1)
			{
				afterReservation.end = originalDate.end; 

				Calendar c = Calendar.getInstance(); 
				c.setTime(afterReservation.end);
				c.add(Calendar.DATE, -(int)afterDays + 1); 
				afterReservation.start = c.getTime(); 
				
				afterReservation.DateToString();
				
				h.openDates.add(afterReservation);

			}
			
			con.closeConnection(); 
			
			//delete the original available dates
			h.DeleteDate(originalDate); 
			
			//add the new available before and after dates if there are any
			h.AddAvailableDates();
			
			
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
	}	
}
