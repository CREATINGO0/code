/**
  * CS2911 Assn1, Room Booking Scenario
  * 3423267, Chad Luo
   */

import java.util.*;

public class Reservation {
    public Reservation(String aUser,
        String aTitle, int aCapacity, int aNumweeks,
        String aMonth, int aDate, int aHour,
        int aDuration) {
        user = aUser;
        title = aTitle;
        capacity = aCapacity;
        numweeks = aNumweeks;
        duration = aDuration;
        month = aMonth;
        date = aDate;
        hour = aHour;
        weeklist = new ArrayList<WeekReservation>();

        int year   = 2013;
        int minute = 0;
        int m;
        int eHour = aHour + aDuration; // end hour

        if(aMonth == "Jan") m = 0;
        else if(aMonth == "Jan") m = 1;
        else if(aMonth == "Feb") m = 2;
        else if(aMonth == "Mar") m = 3;
        else if(aMonth == "Apr") m = 4;
        else if(aMonth == "May") m = 5;
        else if(aMonth == "Jun") m = 6;
        else if(aMonth == "Jul") m = 7;
        else if(aMonth == "Aug") m = 8;
        else if(aMonth == "Sep") m = 9;
        else if(aMonth == "Nov") m = 10;
        else m = 11;
        

        for(int index = aNumweeks; index != 0; index--) {
            Calendar start = Calendar.getInstance();
            Calendar end  = Calendar.getInstance();
            start.set(year,m,date,hour,minute);
            end.set(year,m,date,eHour,minute);
            WeekReservation wkrsrv = new WeekReservation(start,end);
	  		weeklist.add(wkrsrv);
	  		date += 7;
        }

    }
    
    public String getUser(){
    	return user;
    }
    public String getTitle(){
    	return title;
    }
    public String getMonth(){
    	return month;
    }
    public int getDate(){
    	return date;
    }
    public int getHour(){
    	return hour;
    }
    public int getCapacity(){
    	return capacity;
    }
    public int getNumweeks(){
    	return numweeks;
    }
    public int getDuration(){
    	return duration;
    }
    public ArrayList<WeekReservation> getWeekList(){
    	return weeklist;
    }
    private String user;
    private String title;
    private String month;
    private int date;
    private int hour;
    private int capacity;
    private int numweeks;
    private int duration;
    private ArrayList<WeekReservation> weeklist;
}
