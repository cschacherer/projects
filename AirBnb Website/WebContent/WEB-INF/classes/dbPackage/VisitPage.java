package dbPackage;

import java.util.*;
import java.util.concurrent.TimeUnit;

//main page dealing with the visit information
public class VisitPage {

	public static void VisitStart(int user_id)
	{
		User u = new User(user_id); 
		List<Reservation> res = u.UserReservations(); 
		
		if(res.size() == 0)
		{
			System.out.println("You have not reserved a room anywhere."); 
			System.out.println("You must have a reservation to record a visit.\n");
			MainPage.HomePage(user_id);
		}
		
		System.out.println("Here is a list of your reservations."
				+ " Choose which one you would like to record a stay at.");
		int index = -1; 
		for (int i = 0; i < res.size(); i++)
		{
			index = i + 1; 
			System.out.println(index + ": ");
			res.get(i).PrintReservation(); 
			System.out.println("");
		}
		
		try
		{
			String vChoice = StartPage.in.readLine(); 
			int numV = Integer.parseInt(vChoice); 
			
			while(numV < 1 || numV > res.size())
			{
				System.out.println("Please enter a valid input or type BACK to go to the homepage.");
				vChoice = StartPage.in.readLine(); 
				if(vChoice.equals("BACK"))
				{
					MainPage.HomePage(user_id);
				}
				numV = Integer.parseInt(vChoice); 
			}
			
			RecordVisit(res.get(numV - 1)); 
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
	}
	
	//creates a new visit from the reservation that the user chose above
	public static void RecordVisit(Reservation r)
	{
		Visit v = new Visit(); 
		v.hid = r.hid; 
		v.uid = r.uid; 
		
		System.out.println("Your reservation says your stay was from " + r.period.PrintDate() + ". Would you like to keep this date or change it?"); 
		System.out.println("Keep"); 
		System.out.println("Change"); 
		
		try
		{
			String choice = StartPage.in.readLine();

			while(!choice.equals("Keep") && !choice.equals("Change"))
			{
				System.out.println("Please choose a valid answer.");
				choice = StartPage.in.readLine(); 
			}
			
			if (choice.equals("Keep"))
			{
				v.period = r.period; 
			}
			else
			{
				System.out.println("Enter your first day of your visit. Please enter it as MM/DD/YYYY.");
				v.period.stringStart = StartPage.in.readLine(); 
				
				System.out.println("Enter your last day of your visit. Please enter it as MM/DD/YYYY.");
				v.period.stringEnd = StartPage.in.readLine(); 
				
				v.period.StringToDate();
				
				/*
				long diff = v.period.end.getTime() - v.period.start.getTime(); 
			    long numDays = TimeUnit.DAYS.convert(diff, TimeUnit.MILLISECONDS);
			    while((numDays <= 1) || (v.period.start.before(r.period.start)) || (v.period.end.after(r.period.end)))
			    {
					System.out.println("You stay has to include at least one night. The start date cannot be "
							+ "before your reservation's start date and the end date cannot be after your "
							+ "reservation's end date. ");
					
					System.out.println("Enter another start date.");
					v.period.stringStart = StartPage.in.readLine(); 
					
					System.out.println("Enter another end date.");
					v.period.stringEnd = StartPage.in.readLine(); 
					
					v.period.StringToDate();
					
					diff = v.period.end.getTime() - v.period.start.getTime(); 
				    numDays = TimeUnit.DAYS.convert(diff, TimeUnit.MILLISECONDS);
			    }
			    */
			}
			
			long vDiff = v.period.end.getTime() - v.period.start.getTime(); 
		    long vNumDays = TimeUnit.DAYS.convert(vDiff, TimeUnit.MILLISECONDS);
			
			System.out.println("How many people stayed there?"); 
			String stringNum = StartPage.in.readLine();
			v.people = Integer.parseInt(stringNum);   
		    
			
		    House h = new House(r.hid); 
			int totalCost = h.price * v.people * (int)vNumDays; 
			v.cost = totalCost; 
			
			System.out.println("Here is your visit information."); 
			v.PrintVisit();
			
			System.out.println("Type Confirm to enter the data or type anything else to go back to the homepage.");
			
			String confirm = StartPage.in.readLine(); 
			if(confirm.equals("Confirm"))
			{
				boolean result = v.AddToDatabase(); 
				if (result)
				{
					System.out.println("Visit added!\n"); 
				}
				else
				{
					System.out.println("There was an error, try again.\n"); 
				}
				MainPage.HomePage(v.uid);
			}
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		
	}
}
