/**
 * CS2911 Assn1, Room Booking Scenario
 * 34232267, Chad Luo
*/

import java.util.*;

public class WeekReservation {
	public WeekReservation (Calendar aStart, Calendar aEnd) {
		start = aStart;
		end = aEnd;
	}
	public Calendar getStart(){
		return start;
	}
	public Calendar getEnd(){
		return end;
	}
	private Calendar start;
	public Calendar end;
}