import java.util.*;
public class BottleFlipPK{

   public static void main(String [] args){
      Scanner ir = new Scanner(System.in);
      int h  = ir.nextInt();
      int r  = ir.nextInt();
      int d1 = ir.nextInt();
      int d2 = ir.nextInt();
      double d = (double) d2/d1;
      System.out.println( h/(Math.sqrt(d) + 1));
   }

}