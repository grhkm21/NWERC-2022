import java.io.*;
import java.util.*;

public class WordlePKI2{
   static int INF = 1024;
   static int EXTRA = -2;

   public static void main (String [] args){
      WordlePKI2 problem = readTest();
      problem.solve();
      System.out.println(problem.solution());
   }

   public static WordlePKI2 readTest(){
      WordlePKI2 problem = null;
      try{
         BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
         String line = in.readLine();
         Scanner ir = new Scanner(line);
         int rounds = ir.nextInt();
         int length = ir.nextInt();
         problem = new WordlePKI2(length);
         for (int k = 1; k < rounds; k++){
            line = in.readLine();
            String [] words = line.split(" ");
            problem.addRound(words[0], words[1]);
         }
      }
      catch (IOException iox){System.out.println( iox);}
      return problem;
   }

//////////////////////////////////
   boolean [] visitedP;
   boolean []visitedL;
   int length;
   int [][] flowP2L;
   int [][] capP2L;
   int [] capL2S  = new int[26];
   int [] flowL2E = new int[26];
   int [] capL2E  = new int[26];
   int capE2S;
   char [] answer;

   public WordlePKI2(int lenIn){
      length = lenIn;
      flowP2L = new int[length][26];
      capP2L = new int[length][26];
      answer = new char[length];
      build();
   }
   
   void build(){
     for (int p = 0; p < length; p++)
       for (int l = 0; l < 26; l++)
          capP2L[p][l] = 1;
     for(int l = 0; l < 26; l++)
     capL2E [l] = INF;
     for (int p = 0; p < length; p++)
        answer[p] = 'X';
   }
   
   void addRound(String guess, String scores){
      int [] letterScore = new int[26];
      for (int k = 0; k < length; k++){
         int guessInt = guess.charAt(k) - 'a';
         char score = scores.charAt(k);
         switch (score){
            case 'G':  for (int l = 0; l < 26; l++)
                          if (l != guessInt)
                             capP2L[k][l] = 0;
                       letterScore[guessInt]++;
                       break;
            case 'Y':  capP2L[k][guessInt] = 0;
                       letterScore[guessInt]++;
                       break;
            case 'B':  capP2L[k][guessInt] = 0;
                       capL2E[guessInt] = 0;
                       break;
         }
      }
      for (int l = 0; l < 26; l++){
         if (letterScore[l] > capL2S[l])
            capL2S[l] = letterScore[l];
      }
   }

   void solve(){
      connectExtra();
      for (int k = 0; k < length; k++)
         pathFromP(k);
   }

   void connectExtra(){
      int over = length;
      for (int l = 0; l < 26; l++)
         over -= capL2S[l];
      capE2S = over;
   }

   void pathFromP(int p){
      visitedP = new boolean[length];
      visitedL = new boolean[26];
      visitedP[p] = true;
      for (int l = 0; l < 26; l++ )
             if (capP2L[p][l] > flowP2L[p][l]){
                if (pathFromL(l, p)){
                   flowP2L[p][l]++;
                   answer[p] = (char)(l + 'a');
                   return;
                }
             }

   }

   boolean pathFromP(int p, int from){
      if (visitedP[p] )
         return false;
      visitedP[p] = true;
      for (int l = 0; l < 26; l++ )
         if (l != from){
             if (capP2L[p][l] > flowP2L[p][l]){
                if (pathFromL(l, p)){
                   flowP2L[p][l]++;
                   answer[p] = (char)(l + 'a');
                   return true;
                }
             }
         }
       return false;
   }

   boolean pathFromL(int l, int from){
      if(visitedL[l])
         return false;
      visitedL[l] = true;
      if (capL2S[l] > 0){
         capL2S[l]--;
         return true;
      }

      if (from != EXTRA && capL2E[l] - flowL2E[l] > 0)
         if(pathFromE (l)){
            flowL2E[l]++;
            return true;
         }

      for (int p = 0; p < length; p++)
         if (p != from){
            if (flowP2L[p][l] > 0 && !visitedP[p]){
               if (pathFromP(p,l)){
                  flowP2L[p][l]--;
                  return true;
               }
            }
         }
      return false;
   }

   boolean pathFromE(int from){
      if(capE2S > 0){
         capE2S--;
         return true;
      }
      for (int l = 0; l < 26; l++)
         if (l != from){
            if (capL2E[l] > 0){
               if (flowL2E[l] > 0){
                  if (pathFromL(l, EXTRA)){
                     flowL2E[l]--;
                     return true;
                  }
               }
            }
         }
      return false;
   }

   String solution(){
      return new String(answer);
   }

}
