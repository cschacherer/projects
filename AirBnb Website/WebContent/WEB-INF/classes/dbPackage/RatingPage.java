package dbPackage;

import java.util.List;



public class RatingPage {



	public static void RatingStart(int user_id)
	{
		try
		{
			Feedback f = new Feedback();
			Ratings r = new Ratings();
			List<House> houseToRate = r.Houses();
			for(int i = 0; i < houseToRate.size(); i++ )
			{
				int ind = i + 1;

				System.out.println(ind + ": ");
				houseToRate.get(i).PrintAttributes();
				System.out.println("");
			}			
			System.out.println("Choose a number for the hotel you wish to see/rate its feedbacks");
			System.out.println("Type 'BACK' to return to Homepage");
			String userInput = StartPage.in.readLine();

			if(userInput.equals("BACK"))
			{
				MainPage.HomePage(user_id);
			}
			int userInput2 = Integer.parseInt(userInput);
			int hotelID = houseToRate.get(userInput2-1).hid; 			
			List<Feedback> Feedbacks = f.GetFeedback(hotelID); 

			//System.out.println(Feedbacks.size());

			for(int i = 0; i < Feedbacks.size(); i++)
			{
				int ind = i + 1;
				System.out.println(ind + ": ");
				Feedbacks.get(i).PrintFeedBacks();
				System.out.println("");
			}

			if(Feedbacks.size() > 0)
			{

				System.out.println("Choose the number of feedback you would like to rate");
				String userInput3 = StartPage.in.readLine();
				int feedbackRate = Integer.parseInt(userInput3);
				r.fid = Feedbacks.get(feedbackRate-1).fid;
				r.uid = user_id;	
				System.out.println("Rate ranges from 0 to 2 with 0 being unusefull and 2 being usefull ");
				System.out.println("Enter Rate: ");
				String userInput4 = StartPage.in.readLine();
				int newRate = Integer.parseInt(userInput4);	
				r.rate = newRate;
				r.AddToDatabase();
				System.out.println("");
			}
			else{
				
				System.out.println("There are no feedbacks at this time");
				RatingStart(user_id);
				
			}

		}

		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}

	}
}