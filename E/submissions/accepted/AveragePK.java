import java.io.*;
import java.util.*;
public class AveragePK{

   public static void main (String [] args){
      run();
   }
   
   public static void run(){
      Scanner ir = new Scanner(System.in);
      ir.useDelimiter("\\D");
      int a = ir.nextInt();
      int b = ir.nextInt();

       AveragePK problem = new AveragePK(a,b);
       problem.solve();
       problem.writeSolution();
   }
   
/////////////////////////////////////////
   int a,b;
   int [][] solution;

   public AveragePK(int aIn, int bIn){
      a = aIn;
      b = bIn;
   }

   void solve(){
      if (a < b-1)
         return;
      int r = (2 * a + b)/(b * b);
      if (r == 0)
         r++;
      int n = b * r - 1;
      int sum = a * r;
      int score = n * (n+1)/2;
      if (score == sum)
          mkSolution(n, 0, 0);
      else{
         if (score < sum){
            r++;
            n = b * r -1;
            sum = a * r;
         }

         int x = 1 + (int) Math.sqrt(2*(sum - n));
         while ( x * (x+1)/2 + n - x > sum)
            x--;

         int z = n - x;
         
         if (x * (x+1)/2 + z == sum)
            mkSolution(x, 0, z);
         else{
            z--;
            int y = sum - (x * (x+1)/2 + z);
            mkSolution(x, y ,z);
         }
      }
   }

    void mkSolution(int x, int y, int z){
        int aantal = x + z + 2;
        if (y == 0)
           aantal--;
        int som = x * (x+1)/2 + y + z;
        solution = new int[aantal-1][2];
        int loc = 0;
        for (int n = 2; n <= x+1; n++)
           solution[loc++] = new int[]{n-1,n};
        for (int w = x + 2; w <= x + z + 1; w++)
           solution[loc++] = new int[]{1,w};
        if ( y > 0)
          solution[loc] = new int[]{y,loc + 2};
    }
    
    void writeSolution(){
       if (solution == null){
          System.out.println("impossible");
          return;
       }
       int nodes = 1 + solution.length;
       System.out.println((nodes) + " " + (nodes - 1));
       for (int[] edge: solution){
          System.out.println(edge[0] + " "  + edge[1]);
       }
    }

}