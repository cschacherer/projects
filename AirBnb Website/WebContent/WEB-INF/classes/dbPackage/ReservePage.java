package dbPackage;

import java.util.*; 
import java.util.concurrent.TimeUnit;

//reservation home page
public class ReservePage {
	
	public static void ReserveStart(int user_id)
	{
		try
		{
			System.out.println("Where are you going? Please type in a city or state (Use proper capitalization)");
			System.out.println("Or type BACK to go back to the homepage.");
			String destination = StartPage.in.readLine(); 
			
			if(destination.equals("BACK"))
			{
				MainPage.HomePage(user_id);
			}
			
			TimePeriod tp = new TimePeriod(); 
			System.out.println("What is your starting date? Please enter it as MM/DD/YYYY");
			tp.stringStart = StartPage.in.readLine(); 
			
			System.out.println("What is your end date? Please enter it as MM/DD/YYYY");
			tp.stringEnd = StartPage.in.readLine();
			
			tp.StringToDate();
			
			long diff = tp.end.getTime() - tp.start.getTime(); 
		    long numDays = TimeUnit.DAYS.convert(diff, TimeUnit.MILLISECONDS); 		   
			
			List<House> searchResults = SearchListings.AddressAndDate(destination, tp); 
			
			if(searchResults.size() == 0)
			{
				System.out.println("Your search returned no results.  Try again.");
				ReserveStart(user_id); 
				
			}
			
			System.out.println("Search results appear below. Enter the number beside the listings name to schedule a reservation there.");
			for(int i = 0; i < searchResults.size(); i++)
			{
				int index = i + 1; 
				System.out.println(index + ": " );searchResults.get(i).PrintAttributes();
				System.out.println("");
			}
			
			String rChoice = StartPage.in.readLine(); 
			int rNum = Integer.parseInt(rChoice); 
			while(rNum < 1 || rNum > searchResults.size())
			{
				System.out.println("Please enter a valid number or enter BACK to go back to the main page.");
				rChoice = StartPage.in.readLine(); 
				if(rChoice.equals("BACK"))
				{
					MainPage.HomePage(user_id);
				}
				rNum = Integer.parseInt(rChoice); 
			}
			ReserveHouse(searchResults.get(rNum - 1), user_id, tp); 
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
	}
	
	//reserves the house
	public static void ReserveHouse(House h, int user_id, TimePeriod tp)
	{
		try
		{
			Reservation r = new Reservation(); 
			r.hid = h.hid; 
			r.uid = user_id; 
			r.period = tp; 
			
			System.out.println("How many people will be staying here?"); 
			String stringNum = StartPage.in.readLine();
			int numPeople = Integer.parseInt(stringNum); 
			while(numPeople > h.maxResidents)
			{
				System.out.println("The maximum number of people who can stay here is " + h.maxResidents + ". Choose a number below or equal to that.");
				System.out.println("Or type BACK to go back to the reservation homepage.");
				
				stringNum = StartPage.in.readLine();
				if(stringNum.equals("BACK"))
				{
					ReserveStart(user_id); 
				}
				numPeople = Integer.parseInt(stringNum);
			}
			
			r.people = numPeople; 
			
		    long diff = tp.end.getTime() - tp.start.getTime(); 
		    long numDays = TimeUnit.DAYS.convert(diff, TimeUnit.MILLISECONDS); 
			
			int totalCost = h.price * numPeople * (int)numDays; 
			r.cost = totalCost; 
			
			//confirm reservation
			System.out.println("Reservation: "); 
			r.PrintReservation(); 
			
			System.out.println("Confirm this reservation?"); 
			System.out.println("Type Confirm or type anything else to go back to reservation homepage.");
			String confirm = StartPage.in.readLine(); 
			
			if(confirm.equals("Confirm"))
			{
				//pass in the original date of the available house
				boolean result = r.AddToDatabase(h.openDates.get(0)); 
				if(result)
				{
					System.out.println("Your reservation has been added!\n");
				}
				else
				{
					System.out.println("There was an error, the reservation did not go through.\n");
				}
				MainPage.HomePage(user_id);
				
			}
			else
			{
				ReserveStart(user_id); 
			}
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}	
	}
}