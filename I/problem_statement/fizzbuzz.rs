fn main() {
    for x in 1.. {
        if x % 3 == 0 {
            print!("Fizz");
        }
        if x % 5 == 0 {
            print!("Buzz");
        }
        if x % 3 != 0 && x % 5 != 0 {
            print!("{}", x);
        }
        print!(" ");
    }
}
