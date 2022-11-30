import java.io.*;
import java.util.*;

public class WordlePKI{
   static int INF = 1024;
   static int EXTRA = -2;

   public static void main (String [] args){
      WordlePKI problem = readTest();
      problem.solve();
      System.out.println(problem.solution());
   }

   public static WordlePKI readTest(){
      WordlePKI problem = null;
      try{
         BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
         String line = in.readLine();
         Scanner ir = new Scanner(line);
         int rounds = ir.nextInt();
         int length = ir.nextInt();
         problem = new WordlePKI(length);
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
   int length;
   int [][] flowP2L;
   int [][] capP2L;
   int [] capL2S  = new int[26];
   int [] flowL2E = new int[26];
   int [] capL2E  = new int[26];
   int capE2S;
   char [] answer;

   public WordlePKI(int lenIn){
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
      for (int k = 0; k < length; k++){
         if (pathFromP(k, -1) == false)
            System.out.println("Alarm " + k);
      }
   }

   void connectExtra(){
      int over = length;
      for (int l = 0; l < 26; l++)
         over -= capL2S[l];
      capE2S = over;
   }

   boolean pathFromP(int p, int from){
      for (int l = 0; l < 26; l++ )
         if (l != from){
             if (capP2L[p][l] > flowP2L[p][l]){
                capP2L[p][l] -= INF;
                if (pathFromL(l, p)){
                   capP2L[p][l] += INF;
                   flowP2L[p][l]++;
                   answer[p] = (char)(l + 'a');
                   return true;
                }
                else
                   capP2L[p][l] += INF;
             }
         }
         return false;
   }

   boolean pathFromL(int l, int from){
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
            if (flowP2L[p][l] > 0 && capP2L[p][l] >= 0){
               capP2L[p][l] -= INF;
               if (pathFromP(p,l)){
                  flowP2L[p][l]--;
                  capP2L[p][l]+= INF;
                  return true;
               }
               capP2L[p][l]+= INF;
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
               capL2E[l] -= INF;
               if (flowL2E[l] > 0){
                  if (pathFromL(l, EXTRA)){
                     flowL2E[l]--;
                     capL2E[l] += INF;
                     return true;
                  }
               }
               capL2E[l] += INF;
            }
         }
      return false;
   }

   String solution(){
      return new String(answer);
   }

}
