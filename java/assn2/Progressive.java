import java.util.*;

public class Progressive implements Strategy {

    /**
     * imagine a map of nodes of permutation.
     *
     * each permutation node is one way of sorting all tasks and the cost of
     * this permutation can be calculated. there exists at least one node with
     * the least cost.
     *
     * consider two permu-nodes are connected iff one can reach the other by one
     * swap of two tasks. we can always reach the node connected to the current
     * node and we wish it would have a smaller cost.
     *
     * it can prove that if we travel on this graph and long for the smallest
     * cost we would eventually reach the permutation node which represents the
     * min cost for the courier.
     *
     * so we select any of two tasks according to C(n,2) and swap them (equal to
     * step to one of the connected nodes). if it returns a smaller cost then we
     * keep going from this node otherwise return to the node before and explore
     * the next node connected.
     *
     * so the a* algo is not on the map of the city, but on the abstract graph
     * of permutation nodes. the heuristic estimate is the cost of connected
     * permu-nodes, say, the cost after one test swap. the past cost is the cost
     * of the current permu-node.
     */
    public void sort( TaskList list ){
        int costByNow;
        int distance;
        int range   = list.getSize();
        int currX   = 0;
        int currY   = 0;
        int counter = 0;
        int swap    = 0;
        int i;

        // iterate all tasks for the first componenet of swapping
        for(Task each : list.getList()){

            // total cost before swapping
            costByNow = list.getTotalCost();

            // A* differs from Greedy by considering travelled distance
            for(i = counter;i<range;i++){

                swap = i;

                // try swapping and get the new total cost
                Collections.swap(list.getList(),counter,swap);

                // another node explored
                list.incNodes();

                // compare cost after swapping
                int swappedCost = list.getTotalCost();

                if(swappedCost >= costByNow) {

                    // this node is not better, drop.
                    Collections.swap(list.getList(),counter,swap);
                    list.decNodes();

                }
            }
            ++counter;
        }
    }
}