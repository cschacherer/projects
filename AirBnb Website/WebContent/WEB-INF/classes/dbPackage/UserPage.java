package dbPackage;

import java.util.*;

//allows the user to see their information
public class UserPage {

	public static void UserStart(int user_id)
	{
		System.out.println("What would you like to view?");
		System.out.println("1. Personal Information");
		System.out.println("2. Your listings");
		System.out.println("3. Your reservations");
		System.out.println("4. Your visits");
		System.out.println("5. Your favorites");
		System.out.println("6. Go back to home page");
		
		try
		{
			String choice = StartPage.in.readLine(); 
			int numChoice = Integer.parseInt(choice); 
			while(numChoice < 1 || numChoice > 6)
			{
				System.out.println("Coose a valid answer.");
				choice = StartPage.in.readLine(); 
				numChoice = Integer.parseInt(choice); 
			}
			
			//create a new user from user_id
			User u = new User(user_id);
			
			//prints out personal attributes 
			if (choice.equals("1"))
			{ 
				System.out.println("Personal Information: ");

				u.PrintAttributes();
				System.out.println("");
				
				UserStart(user_id); 
			}
			
			//prints out the houses that they own and thier attributes
			else if (choice.equals("2"))
			{
				List<House> houses = u.UserListings(); 
				
				if(houses.size() == 0)
				{
					System.out.println("You have no listings.\n");
				}
				else
				{
					System.out.println("Your Listings: ");
					for(int i = 0; i < houses.size(); i++)
					{
						houses.get(i).PrintAttributes();
						System.out.println("");
					}
				}
				UserStart(user_id); 
			}
			
			//prints out their reservations 
			else if (choice.equals("3"))
			{
				List<Reservation> reservations = u.UserReservations(); 
				
				if(reservations.size() == 0)
				{
					System.out.println("You have no reservations.\n");
				}
				else
				{
					System.out.println("Your Reservations: ");
					for(int i = 0; i < reservations.size(); i++)
					{
						reservations.get(i).PrintReservation();
						System.out.println("");
					}
				}
				UserStart(user_id); 
			}
			
			//prints out their visits
			else if(choice.equals("4"))
			{
				List<Visit> visits = u.UserVisits(); 
				
				if(visits.size() == 0)
				{
					System.out.println("You have not recorded any visits.\n");
				}
				else
				{
					System.out.println("Your Visits: ");
					for(int i = 0; i < visits.size(); i++)
					{
						visits.get(i).PrintVisit();
						System.out.println("");
					}
				}
				UserStart(user_id); 
			}
			
			//prints out a list of their favorite hotels
			else if (choice.equals("5"))
			{
				List<House> faves = u.UserFaves(); 
				
				if(faves.size() == 0)
				{
					System.out.println("You do not have any favorite places to stay.\n");
				}
				else
				{
					System.out.println("Your Favorites: ");
					for(int i = 0; i < faves.size(); i++)
					{
						System.out.println("Name: " + faves.get(i).name);
						System.out.println("Address: " + faves.get(i).address); 
						System.out.println("");
					}
				}
				UserStart(user_id); 
			}
			
			//go back to homepage
			else
			{
				MainPage.HomePage(user_id);
			}
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
	}
}
