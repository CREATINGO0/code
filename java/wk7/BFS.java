
import java.util.*;

/**
 * BFS search alg.
 */
public class BFS {

    private LinkedList<DSGNode> toVisit;
    private LinkedList<DSGNode> visited;

    public void BFSearchPath(DIrectedStringGraph g,
            DSGNode start, DSGNode goal){
        toVisit.add(start);
        while( !toVisit.isEmpty() ){
            currNode = toVisit.removeFirst();
            if( currNode.equals(goal) ) break;

            // currNode.getEdges().sort();

            for( DSGEdge edge : currNode.getEdges() ){
                toVisit.add(edge.getTo());
            }
            visited.add(currNode);
        }
    }

}
