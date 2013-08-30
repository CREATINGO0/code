import java.util.*;
import java.lang.Math;

public class CourierDeliveryKurikaesu {

	/**
	* Body of courier delivery system.
	* Save inputs as tasks in a list;
	* sort according to algos;
	* print results.
	* @author xluo086
	*/
	public static void main(String[] args) {

		TaskList tList = new TaskList(args);

		// greedy
		// SortMethod method = new SortMethod(new Greedy());

		// progressive
		SortMethod method = new SortMethod(new Progressive());

		// for extra large inputs
		// 2 is simply a magic number for input of 1k tasks
		double upperBound = Math.log((double)tList.getSize());
		upperBound += 2;
		for(int i = 0; i<upperBound; i++) method.runSort(tList);
		
		tList.printResults();
	}

}	