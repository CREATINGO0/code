/**
 * Main class, generating the Directed Graph
 * @author Timothy Wiley
 */
public class Main {
    public static void main(String[] args) {
        Main main = new Main();
        main.run();
    }

    public void run() {
        // Generate Graph
        DirectedStringGraph graph = generateGraph();
        System.out.println(graph);
    }

    private DirectedStringGraph generateGraph() {
        DirectedStringGraph graph = new DirectedStringGraph();

        // Nodes
        graph.addNode("Arad");
        graph.addNode("Bucharest");
        graph.addNode("Cralova");
        graph.addNode("Dobreta");
        graph.addNode("Eforle");
        graph.addNode("Fagaras");
        graph.addNode("Glurglu");
        graph.addNode("Hirsova");
        graph.addNode("Iasl");
        graph.addNode("Lugoj");
        graph.addNode("Mehadia");
        graph.addNode("Neamt");
        graph.addNode("Oradea");
        graph.addNode("Pitesti");
        graph.addNode("Rimnicu Vilcea");
        graph.addNode("Sibiu");
        graph.addNode("Timisoara");
        graph.addNode("Urziceni");
        graph.addNode("Vaslui");
        graph.addNode("Zerlnd");

        // Links
        // Implement weighted edges.
        // When implemented the following code will work

        addLink(graph, "Arad", "Zerlnd", 75);
        addLink(graph, "Arad", "Timisoara", 118);
        addLink(graph, "Arad", "Sibiu", 140);
        addLink(graph, "Bucharest", "Pitesti", 101);
        addLink(graph, "Bucharest", "Fagaras", 211);
        addLink(graph, "Bucharest", "Urziceni", 85);
        addLink(graph, "Bucharest", "Glurglu", 90);
        addLink(graph, "Cralova", "Pitesti", 138);
        addLink(graph, "Cralova", "Rimnicu Vilcea", 146);
        addLink(graph, "Cralova", "Dobreta", 120);
        addLink(graph, "Dobreta", "Mehadia", 75);
        addLink(graph, "Eforle", "Hirsova", 86);
        addLink(graph, "Fagaras", "Sibiu", 99);
        addLink(graph, "Hirsova", "Urziceni", 98);
        addLink(graph, "Iasl", "Neamt", 87);
        addLink(graph, "Iasl", "Vaslui", 92);
        addLink(graph, "Lugoj", "Mehadia", 70);
        addLink(graph, "Lugoj", "Timisoara", 111);
        addLink(graph, "Oradea", "Sibiu", 151);
        addLink(graph, "Oradea", "Zerlnd", 71);
        addLink(graph, "Pitesti", "Rimnicu Vilcea", 97);
        addLink(graph, "Rimnicu Vilcea", "Sibiu", 80);
        addLink(graph, "Urziceni", "Vaslui", 142);

        graph.addDistance("Arad",366);
        graph.addDistance("Bucharest",0);
        graph.addDistance("Craiova",160);
        graph.addDistance("Dobreta",242);
        graph.addDistance("Eforie",161);
        graph.addDistance("Fagaras",178);
        graph.addDistance("Giurgiu",77);
        graph.addDistance("Hirsova",151);
        graph.addDistance("Iasi",226);
        graph.addDistance("Lugoj",244);
        graph.addDistance("Mehadia",241);
        graph.addDistance("Neamt",234);
        graph.addDistance("Oradea",380);
        graph.addDistance("Pitesti",98);
        graph.addDistance("Rimnicu Vilcea",193);
        graph.addDistance("Sibiu",253);
        graph.addDistance("Timisoara",329);
        graph.addDistance("Urziceni",80);
        graph.addDistance("Vaslui",199);
        graph.addDistance("Zerlnd",374);

        return graph;
    }

    private void addLink(DirectedStringGraph graph,
        String n1, String n2, int weight) {
        graph.addEdge(n1, n2, weight);
        graph.addEdge(n2, n1, weight);
    }

}
