import java.util.*;
public class MonteCarloPK{

   boolean done = false;
   static int len;
   static long MOD;
   static String patternString;
   static long PATTERN;

   static{
      len = 63;
      MOD = Long.MAX_VALUE/2 + 1; // 2^62
      long t = System.currentTimeMillis(); 
      PATTERN = 23 + t  * 3 * 5 * 7 * 11 * 13 * 17 * 18;
      patternString = Long.toString(PATTERN, 2);
   }

   public static void main (String [] args){
      MonteCarloPK problem = new MonteCarloPK();
      problem.run();
   }

   static Scanner sc = new Scanner(System.in);

   public void send(String comm){
      System.out.println(comm);
      System.out.flush();
   }
  
   public int read(){
      int num  = sc.nextInt();
      return num;
   }

   void run(){
      clearL();
      set1();
      seedPatternR();
      if (!done)
         findPatternR();
   }
   
   void clearL(){
      int bit = read();
      if (bit == 1)
         command("flip");
      for (int k = 2; k <= len; k++){
         bit = command("left");
         if (bit == 1)
            command("flip");
      }
   }
                         
   void set1(){
      int bit = command("left");
      if (bit == 0)
         command("flip");
   }
   
   void seedPatternR(){
      for (int k = 1; k <= len && !done; k++){
         int bit = command("right");
         if (bit == 1)
            finish(k);
         char patBit = patternString.charAt(k-1);
         if (patBit == '1')
            command("flip");
      }
   }

   void findPatternR(){
      long pat = 0;
      int len = 0;
      while (pat != PATTERN){
         int bit = command("right"); 
         if (pat > MOD)
         pat -= MOD;
         pat = 2 * pat + bit;
         len++;
      }
      finish(len);
   }

   int command(String com){
      send("? "+ com);
      int num  = read();
      return num;
   }

   void finish(int n){
      send("! "+ n);     
      System.exit(0);
   }

}




