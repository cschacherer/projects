package dbPackage;

import java.io.*;
import java.util.*; 

//page that logs in the user and then directs them to the main page
public class StartPage {
	
	//use this for all input reading for all of the classes
	public static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
	
	public static void main(String[] args) 
	{
		/*
		System.out.println("Welcome to Uotel! Would you like to Sign up or Login?"); 
		
		//Scanner sc = new Scanner(System.in);
		//String choice = sc.nextLine(); 
		String choice = ""; 
		try
		{
			choice = in.readLine(); 
			//while ((choice = in.readLine()) == null && choice.length() == 0);

			while(!choice.equals("Login")&& !choice.equals("Sign up"))
			{
				System.out.println("(Please type Sign up or Login)");
				//choice = sc.nextLine();
				while ((choice = in.readLine()) == null && choice.length() == 0);

			}
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		
			
		User user; 
		if(choice.equals("Sign up"))
		{
			user = CreateNewUser(); 
		}
		//choice is login
		else
		{
			user = CheckLogin(); 
		}
		
		HousingPage.HousingStart(user.uid); 
		*/
		
		//HousingPage.HousingStart(1);
		
		MainPage.HomePage(6); 
		
		main(args); 
	}
	
	//signs up user and adds them to the database
	public static User CreateNewUser()
	{
		User newUser = new User(); 
		
		try
		{
			System.out.println("Please type in your first name.");
			while ((newUser.firstName = in.readLine()) == null && newUser.firstName.length() == 0);
			
			System.out.println("Please type in your last name.");
			while ((newUser.lastName = in.readLine()) == null && newUser.lastName.length() == 0);
			
			System.out.println("Please type in a login.");
			while ((newUser.login = in.readLine()) == null && newUser.login.length() == 0);
			
			System.out.println("Please type in a password.");
			while ((newUser.password = in.readLine()) == null && newUser.password.length() == 0);
			
			System.out.println("Please type in a address.");
			while ((newUser.address = in.readLine()) == null && newUser.address.length() == 0);
			
			System.out.println("Please type in a phone number.");
			while ((newUser.phoneNumber = in.readLine()) == null && newUser.phoneNumber.length() == 0);
			
			boolean success = newUser.AddToDatabase(); 
			while(success == false)
			{
				System.out.println("Try a different login. This one is already in use."); 
				while ((newUser.login = in.readLine()) == null && newUser.login.length() == 0);
				
				success = newUser.AddToDatabase(); 
			}			
		}
		catch(Exception e)
		{
			System.out.println(e); 
		}
		
		return newUser; 
	}
	
	//Logs the user in if the login and password or correct
	public static User CheckLogin()
	{
		User newUser = new User(); 
		
		try
		{
			System.out.println("Please type in a login.");
			newUser.login = in.readLine(); 
			
			System.out.println("Please type in a password.");
			newUser.password = in.readLine(); 
			
			boolean loginSuccess = newUser.LoginUser(); 
			while(loginSuccess == false)
			{
				System.out.println("Login and password were incorrect. Try again.");
				System.out.println("Please type in a login.");
				newUser.login = in.readLine();
				
				System.out.println("Please type in a password.");
				newUser.password = in.readLine();			}
			
			System.out.println("Logged in successfully!");
		}
		catch(Exception e)
		{
			System.out.println(e); 
		}
		
		return newUser; 
	}
	
	

}
