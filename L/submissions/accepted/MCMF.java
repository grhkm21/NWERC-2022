import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.List;
import java.util.Queue;
import java.util.Scanner;

public class MCMF {

	private static final long M = 100000;
	private static final long MM = M * M;
	private static final long MMM = M * M * M;

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int m = sc.nextInt();
		int n = sc.nextInt();

		m--;

		boolean[][] forced = new boolean[26][n];
		boolean[][] forbidden = new boolean[26][n];

		int[] lo = new int[26];
		int[] hi = new int[26];
		for (int i = 0; i < 26; i++) {
			hi[i] = n;
		}

		for (int o = 0; o < m; o++) {
			String s = sc.next();
			String t = sc.next();

			int[] gy = new int[26];
			boolean[] b = new boolean[26];
			for (int i = 0; i < n; i++) {
				int l = s.charAt(i) - 'a';

				if (t.charAt(i) == 'G') {
					gy[l]++;
					forced[l][i] = true;
				} else if (t.charAt(i) == 'Y') {
					gy[l]++;
					forbidden[l][i] = true;
				} else {
					b[l] = true;
					forbidden[l][i] = true;
				}
			}

			for (int l = 0; l < 26; l++) {
				lo[l] = Math.max(lo[l], gy[l]);
				if (b[l]) {
					hi[l] = Math.min(hi[l], gy[l]);
				}
			}
		}

		char[] ans = new char[n];
		for (int i = 0; i < n; ++i) {
			for (int l = 0; l < 26; l++) {
				if (forced[l][i]) {
					ans[i] = (char) (l + 'a');
					lo[l]--;
					hi[l]--;
				}
			}
		}
		List<Integer> le = new ArrayList<>();

		for (int i = 0; i < n; i++) {
			if (ans[i] == 0) {
				le.add(i);
			}
		}

		MinCostMaxFlow mcmf = new MinCostMaxFlow();

		for (int l = 0; l < 26; l++) {
			for (int x = 0; x < 2; x++) {
				for (int i = 0; i < le.size(); i++) {
					if (forbidden[l][le.get(i)]) {
						continue;
					}
					mcmf.addEdge(i, le.size() + 2 * l + x, 1, 0);
				}
			}
		}

		int q = le.size() + 52;

		for (int i = 0; i < le.size(); i++) {
			mcmf.addEdge(q, i, 1, 0);
		}
		for (int i = 0; i < 26; i++) {
			mcmf.addEdge(le.size() + 2 * i, q + 1, lo[i], M);
			mcmf.addEdge(le.size() + 2 * i + 1, q + 1, hi[i] - lo[i], MM);
		}

		mcmf.addEdge(q, q + 1, 0, 0);

		mcmf.compute(q, q + 1);

		for (int i = 0; i < 52; i++) {
			for (int id : mcmf.adjlist.get(le.size() + i)) {
				var e = mcmf.edges.get(id);
				if (e.to < le.size() && e.f != 0) {
					ans[le.get(e.to)] = (char) (i / 2 + 'a');
				}
			}
		}

		System.out.println(new String(ans));
	}

	private static class MinCostMaxFlow {

		static class Edge {
			int to;
			long f, cost;

			public Edge(int to, long f, long cost) {
				this.to = to;
				this.f = f;
				this.cost = cost;
			}
		}

		List<Edge> edges;
		List<List<Integer>> adjlist;
		private int[] pref;
		private int[] con;
		private long[] dist;

		private int s, t;
		private long maxflow, mincost;

		public MinCostMaxFlow() {
			adjlist = new ArrayList<>();
			edges = new ArrayList<>();
		}

		public void addEdge(int u, int v, long c, long cost) {
			while (adjlist.size() <= u || adjlist.size() <= v) {
				adjlist.add(new ArrayList<>());
			}
			adjlist.get(u).add(edges.size());
			edges.add(new Edge(v, c, cost));
			adjlist.get(v).add(edges.size());
			edges.add(new Edge(u, 0, -cost));
		}

		public void compute(int source, int target) {
			s = source;
			t = target;
			con = new int[adjlist.size()];
			while (SPFA()) {
				extend();
			}
		}

		private boolean SPFA() {
			pref = new int[adjlist.size()];
			dist = new long[adjlist.size()];
			for (int i = 0; i < adjlist.size(); i++) {
				pref[i] = -1;
				dist[i] = MMM;
			}

			boolean[] inqueue = new boolean[adjlist.size()];
			Queue<Integer> queue = new ArrayDeque<>();

			dist[s] = 0;
			queue.add(s);
			pref[s] = s;
			inqueue[s] = true;

			while (!queue.isEmpty()) {
				int cur = queue.poll();
				inqueue[cur] = false;
				for (int id : adjlist.get(cur)) {
					int to = edges.get(id).to;
					if (edges.get(id).f > 0 && dist[to] > dist[cur] + edges.get(id).cost) {
						dist[to] = dist[cur] + edges.get(id).cost;
						pref[to] = cur;
						con[to] = id;
						if (!inqueue[to]) {
							inqueue[to] = true;
							queue.add(to);
						}
					}
				}
			}
			return pref[t] != -1;
		}

		private void extend() {
			long w = MMM;
			for (int u = t; pref[u] != u; u = pref[u]) {
				w = Math.min(w, edges.get(con[u]).f);
			}
			maxflow += w;
			mincost += dist[t] * w;
			for (int u = t; pref[u] != u; u = pref[u]) {
				edges.get(con[u]).f -= w;
				edges.get(con[u] ^ 1).f += w;
			}
		}
	}
}
