package dbPackage;

public class MainPage {
	
	//main home page that allows the user to go to other pages
	public static void HomePage(int user_id)
	{
		try
		{
			System.out.println("What would you like to do? Please enter a number below.");
			System.out.println("1. View your information"); 
			System.out.println("2. Edit your listings"); //done
			System.out.println("3. Search and reserve a room"); //done
			System.out.println("4. Record a visit"); //done
			System.out.println("5. Record a favorite listing"); //done
			System.out.println("6. View or leave feedback on a listing"); //done
			System.out.println("7. Rate feedback"); 
			System.out.println("8. See most useful feedbacks.");
			System.out.println("9. Set another user as trusted/not trusted"); //done
			System.out.println("10. Browse listings"); //done (still need feedback for it)
			System.out.println("11. See suggested listings"); //done
			System.out.println("12. See degree of separation"); //done ish
			System.out.println("13. See top statistics"); //done (but still need feedback for it)
			System.out.println("14. See best users awards");
			System.out.println("15. Logout");
			
			String choice = StartPage.in.readLine(); 
			
			//view information
			if(choice.equals("1"))
			{
				UserPage.UserStart(user_id); 
			}
			//edit listings
			else if(choice.equals("2"))
			{
				HousingPage.HousingStart(user_id);
			}
			//reserve a house
			else if(choice.equals("3"))
			{
				ReservePage.ReserveStart(user_id);
			}
			//record a visit
			else if(choice.equals("4"))
			{
				VisitPage.VisitStart(user_id);
			}
			//record a favorite
			else if(choice.equals("5"))
			{
				FavoritesPage.FavoriteStart(user_id); 
			}
			
			//record a feedback
			else if(choice.equals("6"))
			{
				FeedbackPage.FeedBackStart(user_id); 
			}
			
			//record a feedback
			else if(choice.equals("7"))
			{
				RatingPage.RatingStart(user_id);
			}
			
			else if(choice.equals("8"))
			{
				UsefulnessRatePage.usefullStart(user_id);
			}
			
			//trust/not trust a user
			else if(choice.equals("9"))
			{
				TrustingPage.TrustingStart(user_id);
			}
			
			//browse listings
			else if(choice.equals("10"))
			{
				BrowsingPage.BrowsingStart(user_id);
			}
			
			//see suggestions 
			else if(choice.equals("11"))
			{
				SuggestionsPage.SuggestionStart(user_id);
			}
			
			//see degree of separation
			else if(choice.equals("12"))
			{
				DegreeSeparationPage.SeparationStart(user_id); 
			}
			
			//see top rated statistics 
			else if(choice.equals("13"))
			{
				StatisticsPage.StatisticsStart(user_id);
			}
			
			//see best users 
			else if(choice.equals("14"))
			{
				UserAwardsPage.UserAwardsStart(user_id);
			}
			
			//go back to start
			else if(choice.equals("15"))
			{
				return; 
			}
			
			//go back to this page
			else
			{
				System.out.println("Choose a valid number.");
				HomePage(user_id); 
			}
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}	
	}
}
