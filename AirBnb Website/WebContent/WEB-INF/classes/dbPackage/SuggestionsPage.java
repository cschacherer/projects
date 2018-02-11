package dbPackage;

import java.util.*;

public class SuggestionsPage {

	public static void SuggestionStart(int user_id)
	{
		System.out.println("Here is a list of all the places you have reserved.");
		System.out.println("Suggestions for other places to stay appear after each reservations.");
		
		User u = new User(user_id); 
		
		List<Reservation> reservations = u.UserReservations(); 
		
		for(int i = 0; i < reservations.size(); i++)
		{
			System.out.println("Reservation: ");
			reservations.get(i).PrintReservation();
			
			Suggestions s = new Suggestions(user_id, reservations.get(i).hid); 
			List<House> suggestions = s.GetSuggestions(); 
			
			System.out.println("\nSuggestions: ");
			if(suggestions.size() == 0)
			{
				System.out.println("No suggestions for this listing.\n");
			}
			else
			{
				for(int j = 0; j < suggestions.size(); j++)
				{
					suggestions.get(j).PrintAttributes();
					System.out.println("");
				}
			}
		}
		
		MainPage.HomePage(user_id);
	}
}
