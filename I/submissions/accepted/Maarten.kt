fun solve(xs: List<Int>): Int {
    if (xs.isEmpty()) return 1000000
    if (xs.size == 1) return xs[0]
    return xs[1] - xs[0]
}

fun main() {
    val (c, d) = readln().split(" ").map { it.toInt() }
    val items = readln().split(" ")
    val fizzes = (c..d).filter { i -> items[i - c].contains('F') }
    val buzzes = (c..d).filter { i -> items[i - c].contains('B') }
    println(solve(fizzes).toString() + " " + solve(buzzes))
}
