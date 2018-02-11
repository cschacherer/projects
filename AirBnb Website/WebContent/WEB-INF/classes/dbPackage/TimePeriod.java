package dbPackage;

import java.util.*;
import java.text.DateFormat;
import java.text.SimpleDateFormat;

//class to hold time periods
public class TimePeriod {

	public Date start; 
	public Date end; 
	
	public String stringStart; 
	public String stringEnd; 
	
	//keeps the correct date formating when converting from or to a string
	public static DateFormat df = new SimpleDateFormat("MM/dd/yyyy"); 
	
	public TimePeriod()
	{
		start = new Date(0); 
		end = new Date(0); 
	}
	
	//creates the start and end date from stringStart and stringEnd
	public void StringToDate()
	{
		try
		{
			start = df.parse(stringStart);
			end = df.parse(stringEnd);
		}
		catch(Exception e)
		{
			System.out.println(e+", "+e.getMessage());
		}
	}
	
	//creates strings from the start and end dates 
	public void DateToString()
	{
		try
		{
			stringStart = df.format(start); 
			stringEnd = df.format(end); 
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
	}
	
	//easy way to print this time period
	public String PrintDate()
	{
		return (stringStart + " to " + stringEnd); 
	}
}
