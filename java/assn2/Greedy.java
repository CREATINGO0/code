import java.util.*;

public class Greedy implements Strategy {

	/**
	* sort tasks according to greedy algo.
	* always find the shortest start from current location.
	* based on variation of selection sort.
	*/
	public void sort( TaskList list ){
		int distance;
		int range   = list.getSize();
		int currX   = 0;
		int currY   = 0;
		int counter = 0;
		int swap    = 0;
		int i;

		// iterate all tasks
		for(Task each : list.getList()){

			distance = each.getTransferCost(currX,currY);

			// for each task, search the closest upcoming
			for(i = counter;i<range;i++){
				Task iter = list.getList().get(i);
				if(distance>iter.getTransferCost(currX,currY)){
					distance = iter.getTransferCost(currX,currY);
					swap = i;
			// raise the closest upcoming
					Collections.swap(list.getList(),counter,swap);
					currX = each.tX();
					currY = each.tY();
				}
			}

			++counter;
			
		}
	}
}