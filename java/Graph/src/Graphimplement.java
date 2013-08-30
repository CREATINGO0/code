import java.util.*;

/** Graph implemented with adjacency list
 *  object o represents each element in the list
 *  o is a sublist indicating adjacency with other vertices
 *
 */
public class Graphimplement {
	void addNode( Object o ){
		Graph.add(o);
	}
	void removeNode( Object o ){
		Graph.remove(o);
	}
	void addEdge( Object o1, Object o2 ){
		o1.add(Graph.indexOf(o2));
		o2.add(Graph.indexOf(o1));
	}
	int nEdges(){
		return Graph.size();
	}
	boolean isConnected( Object o1, Object o2 ){
		return true;
	}
	boolean containsNode( Object o ){
		return Graph.contains(o);
	}
	
	private ArrayList<ArrayList[]> Graph;
}