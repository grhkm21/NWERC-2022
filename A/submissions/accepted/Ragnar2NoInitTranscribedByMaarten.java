import java.io.*;
import java.util.*;

public class Ragnar2NoInitTranscribedByMaarten {
    public static void main(String[] args) throws IOException {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            new Ragnar2NoInitTranscribedByMaarten().run(reader);
        }
    }

    static class T {
        // Number of zeros and ones in the interval.
        int zeros, ones;
        // max over (ones left of cut) - (zeros right of cut) for cut in this interval.
        int inside;

        T(int x) {
            zeros = x == 0 ? 1 : 0;
            ones = x == 1 ? 1 : 0;
            inside = 1;
        }

        T(int zeros, int ones, int inside) {
            this.zeros = zeros;
            this.ones = ones;
            this.inside = inside;
        }
    }

    static T op(T l, T r) {
        return new T(l.zeros + r.zeros, l.ones + r.ones, Math.max(l.inside + r.zeros, r.inside + l.ones));
    }

    // All positions start at one and change to 0 one by one.
    static T _id = new T(0, 0, 0);

    static class SegmentTree {
        int n;
        T[] tree;
        T id;

        SegmentTree(int _n) {
            this.n = _n;
            tree = new T[2 * n];
            Arrays.fill(tree, _id);
            id = _id;

        }

        void update(int i, T val) {
            for (tree[i + n] = val, i = (i + n) / 2; i > 0; i /= 2)
                tree[i] = op(tree[2 * i], tree[2 * i + 1]);
        }

        T query(int l, int r) {
            T lhs = _id, rhs = _id;
            for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
                if ((l & 1) == 1) lhs = op(lhs, tree[l++]);
                if ((r & 1) == 0) rhs = op(tree[r--], rhs);
            }
            return op(l == r ? op(lhs, tree[l]) : lhs, rhs);
        }
    }

    public void run(BufferedReader reader) throws IOException {
        int n = Integer.parseInt(reader.readLine())+1;
        int[] v = new int[n];
        Integer[] ord = new Integer[n];
        int k = 0;
        for (String x : reader.readLine().split(" ")) {
            ord[k] = k;
            v[k++] = Integer.parseInt(x);
        }

        Arrays.sort(ord, Comparator.comparingInt(i -> v[i]));
        SegmentTree st = new SegmentTree(n);
        for (int i = 0; i < n - 1; ++i) st.update(i, new T(1));
        int left_one = 0;
        int right_zero = -1;
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            Integer pos = ord[i];
            // position pos will change from 1 to 0.
            right_zero = Math.max(right_zero, pos);
            while (left_one < n && v[left_one] <= v[pos]) ++left_one;
            st.update(pos, new T(0));
            int m = st.query(left_one, right_zero).inside;
            if ((m + i) % 2 != 1) --m;
            ans = Math.max(ans, m);
        }
        System.out.println(ans);
    }
}
