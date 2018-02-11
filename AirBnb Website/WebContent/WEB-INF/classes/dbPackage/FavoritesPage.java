package dbPackage;

//main page to record favorite houses
public class FavoritesPage {

	public static void FavoriteStart(int owner_id)
	{
		System.out.println("What would you like to do?");
		System.out.println("1. Add a new favorite listing");
		System.out.println("2. See your favorite listings");
		System.out.println("3. Go back to home page");

		try
		{
			String choice = StartPage.in.readLine(); 
			
			while(!choice.equals("1") && !choice.equals("2") && !choice.equals("3"))
			{
				System.out.println("Please enter a valid input");   
				choice = StartPage.in.readLine(); 
			}
			
			if(choice.equals("1"))
			{
				AddNewFavorite(owner_id); 
			}
			else if (choice.equals("2"))
			{
				PrintOutFavorites(owner_id); 
			}
			else
			{
				MainPage.HomePage(owner_id);
			}
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
	}
	
	public static void AddNewFavorite(int owner_id)
	{
		Favorite f = new Favorite(owner_id); 
		
		if(f.visited.size() == 0)
		{
			System.out.println("You have not visited anywhere.\n"); 
			FavoriteStart(owner_id); 
		}
			
		
		for(int i = 0; i < f.visited.size(); i++)
		{
			int index = i + 1; 
			System.out.println(index + ": "+f.visited.get(i).name);
			System.out.println(f.visited.get(i).address);
			System.out.println("");
		}
		
		try
		{
			System.out.println("Which would you like to declare as a favorite?"); 
			String fChoice = StartPage.in.readLine(); 
			int fNum = Integer.parseInt(fChoice); 
			
			while(fNum < 1 || fNum > f.visited.size())
			{
				System.out.println("Enter a valid number?"); 
				fChoice = StartPage.in.readLine(); 
				fNum = Integer.parseInt(fChoice); 
			}
			
			//minus fNum by 1 to get right hid since index is added by 1
			boolean result = f.AddFaveToDatabase(f.visited.get(fNum - 1)); 
			if(result)
			{
				System.out.println("Fave added!\n"); 
			}
			else
			{
				System.out.println("There was an error.  Try again.\n");
			}
			
			FavoriteStart(owner_id);
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
	}
	
	public static void PrintOutFavorites(int owner_id)
	{
		Favorite f = new Favorite(owner_id); 
		
		if(f.faves.size() == 0)
		{
			System.out.println("You don't have any favorite listings.\n");
			FavoriteStart(owner_id); 
		}
		//print out the favorites
		System.out.println("Here is a list of your favorite listings.");
		for(int i = 0; i < f.faves.size(); i++)
		{
			int index = i + 1; 
			System.out.println(index + ": "+f.faves.get(i).name);
			System.out.println(f.faves.get(i).address);
			System.out.println("");
		}
		
		FavoriteStart(owner_id); 
	}
}
