import java.lang.Math;

public class Task {
	private int fromX;
	private int fromY;
	private int toX;
	private int toY;
	private int cost;

	/**
	* constructor of a Task.
	* @param fromX start point x coordinate
	* @param fromY start point y coordinate
	* @param toX end point x coordinate
	* @param toX end point y coordinate
	*/
	public Task(int fromX, int fromY, int toX, int toY) {
		this.fromX = fromX;
		this.fromY = fromY;
		this.toX   = toX;
		this.toY   = toY;
		cost   = Math.abs(toX - fromX) + Math.abs(toY - fromY);
	}

	public int fX() { return fromX; }
	public int fY() { return fromY; }
	public int tX() { return toX; }
	public int tY() { return toY; }

	/**
	* calculate the distance from last position to the start of this task.
	* @param lastX last position, x coordinate.
	* @param lastY last position, y coordinate.
	*/
	public int getTransferCost(int lastX, int lastY) {
		int move = Math.abs(fromX - lastX) + Math.abs(fromY - lastY);
		return move;
	}

	/**
	* calculate the cost of transfer and finish this task.
	* @param lastX last position, x coordinate.
	* @param lastY last position, y coordinate.
	*/
	public int getFullCost(int lastX, int lastY) {
		int move = Math.abs(fromX - lastX) + Math.abs(fromY - lastY);
		move += cost;
		return move;
	}

	/**
	* return carry information.
	*/
	public String toString() {
		return "Carry from " + this.fromX + " " + this.fromY
		+ " to " + this.toX + " " + this.toY;
	}

	/**
	* return move information.
	*/
	public String moveFrom(int currX,int currY) {
		return "Move from " + currX + " " + currY
		+ " to " + this.fX() + " " + this.fY();
	}
}