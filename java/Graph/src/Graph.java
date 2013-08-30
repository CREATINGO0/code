import java.util.ArrayList;


public interface Graph {
	void addNode( Object o );
	void removeNode( Object o );
	void addEdge( Object o1, Object o2 );
	int nEdges();
	boolean isConnected( Object o1, Object o2 );
	boolean containsNode( Object o );
	
	ArrayList<ArrayList[]> Graph;
}
