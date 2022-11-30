import java.util.*;
import java.util.stream.*;

public class Paul {
	static int solve(int[] xs) {
		if (xs.length == 0) return (int) 1e6;
		if (xs.length == 1) return xs[0];
		return xs[1]-xs[0];
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int c = sc.nextInt();
		int d = sc.nextInt();
		sc.nextLine();
		String[] items = sc.nextLine().split(" ");
		var fizzes = IntStream.rangeClosed(c,d).filter(i -> items[i-c].charAt(0) == 'F').toArray();
		var buzzes = IntStream.rangeClosed(c,d).filter(i -> items[i-c].charAt(0) == 'B' || items[i-c].length() == 8).toArray();
		System.out.println(solve(fizzes) + " " + solve(buzzes));
	}
}
