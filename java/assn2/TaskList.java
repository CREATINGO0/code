import java.util.*;
import java.io.*;

public class TaskList {
	private ArrayList<Task> tasklist;
	private int nodes;
	private int totalCost;
	private int size;

	/**
	* construct a TaskList from input file.
	* generates nodes number.
	* @param args input file
	*/
	public TaskList( String[] args ){

		tasklist = new ArrayList<Task>();

		try {

			int fX,fY,tX,tY;
			Scanner sc = new Scanner(new FileReader(args[0]));
			while(sc.hasNextLine()) {
				sc.skip("Job");
				fX = sc.nextInt();
				fY = sc.nextInt();
				sc.skip(" to");
				tX = sc.nextInt();
				tY = sc.nextInt();
				Task newTask = new Task(fX,fY,tX,tY);
				tasklist.add(newTask);
				sc.skip("\n");
			}

			size = tasklist.size();

		} catch( FileNotFoundException e ){
			e.printStackTrace();
		}

	}

	/**
	* assuming list of tasks is ranked under a certain strategy.
	* prints all information of nodes, costs and procedure.
	*/
	public void printResults(){

		// print nodes
		// nodes calculated during sorting
		System.out.println(nodes + " nodes explored");

		// calculate and print total cost
		System.out.println("cost = " + this.getTotalCost());

		//print procedure
		int currX = 0;
		int currY = 0;
		for(Task each : tasklist){
			System.out.println(each.moveFrom(currX,currY));
			System.out.println(each);
			currX = each.tX();
			currY = each.tY();
		}

	}

	public ArrayList<Task> getList() { return tasklist; }
	public int getSize() { return size; }
	public void incNodes() { nodes++; }
	public void decNodes() { nodes--; }

	/**
	* return total cost of all tasks under current sort.
	* implemented only for easy life during sorting.
	*/
	public int getTotalCost() {
		int currX = 0;
		int currY = 0;
		int totalCost = 0;

		for(Task each : tasklist){
			totalCost += each.getFullCost(currX,currY);
			currX = each.tX();
			currY = each.tY();
		}
		return totalCost;
	}
}
