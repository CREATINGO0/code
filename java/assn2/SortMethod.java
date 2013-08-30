import java.util.*;

public class SortMethod{

	private Strategy strategy;

	/**
	* employ sorting algorithm
	* @param s employed algo
	*/
	public SortMethod(Strategy s){ this.strategy = s; }

	/**
	* run the sort
	* @param list list of tasks to be sorted
	*/
	public void runSort(TaskList list){ this.strategy.sort(list); }
}