package structures;

import java.util.List;
import java.util.Map;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.LinkedList;

public class Graph {

  private Map<Integer, List<Integer>> edges;

  Graph() {
    this.edges = new LinkedHashMap<Integer, List<Integer>>();
  }

  public void addEdge(int u, int v) {
    if (this.edges.containsKey(u)) {
      this.edges.get(u).add(v);
    } else {
      List<Integer> destList = new LinkedList<Integer>();
      destList.add(v);
      this.edges.put(u, destList);
    }
  }


  public List adj(int u) {
    return this.edges.get(u);
  }
}
