import java.util.*;

public class PaulScanner {
    static class Node {
        int i, comp = -1;
        Set<Node> adj;

        int nonLeafNeighbors() {
            int res = 0;
            for (Node a: adj) {
                if (a.i != i && a.adj.size() > 1) res++;
            }
            return res;
        }

        void dfs(int comp) {
            this.comp = comp;
            for (Node a: adj) {
                if (a.comp == -1) a.dfs(comp);
            }
        }

        public Node(int i) {
            this.i = i;
            adj = new HashSet<Node>();
        }
    }

    static boolean solve() {
        Scanner sc = new Scanner(System.in);
        int m = sc.nextInt(), n = sc.nextInt();

        Node[] nodes = new Node[n];
        for (int i = 0; i < n; i++) {
            nodes[i] = new Node(i);
        }
        while (m --> 0) {
            int a = sc.nextInt() - 1;
            int b = sc.nextInt() - 1;
            nodes[a].adj.add(nodes[b]);
            nodes[b].adj.add(nodes[a]);
        }

        for (Node a: nodes) {
            if (a.nonLeafNeighbors() > 2) return false;
        }

        int C = 0;
        for (Node a: nodes) if (a.comp == -1) a.dfs(C++);

        int[] nodeCount = new int[C];
        int[] edgeCount = new int[C];
        int[] loopCount = new int[C];
        for (Node a: nodes) {
            nodeCount[a.comp]++;
            for (Node b: a.adj) {
                if (a.i < b.i)  edgeCount[a.comp]++;
                if (a.i == b.i) loopCount[a.comp]++;
            }
        }

        int singles = 0, chains = 0, circles = 0;
        for (int k = 0; k < C; k++) {
            if (edgeCount[k] + loopCount[k] == 0) singles++;
            else if (edgeCount[k] < nodeCount[k]) chains++;
            else circles++;
        }
        return circles == 0 || (circles == 1 && chains == 0);
    }

    public static void main(String[] args) {
        System.out.println(solve() ? "possible" : "impossible");
    }
}
