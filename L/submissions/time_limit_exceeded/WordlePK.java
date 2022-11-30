import java.io.*;
import java.util.*;


public class WordlePK{
   public static void main (String [] args){
      WordlePK problem = readTest();
      //WordlePK problem = useTest(sample2);
      problem.solve();
      System.out.println(problem.solution());
   }

   public static WordlePK readTest(){
      WordlePK problem = null;
      try{
         BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
         String line = in.readLine();
         Scanner ir = new Scanner(line);
         int rounds = ir.nextInt();
         int length = ir.nextInt();
         problem = new WordlePK(length);
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
   LetterNode [] letters = new LetterNode[26];
   PositionNode [] positions;
   Sink end = new Sink();
   Extra extra = new Extra();
   Edge extraToEnd;

   public WordlePK(int lenIn){
      length = lenIn;
      positions = new PositionNode[length];
      Node.length = length;
      build();
   }

   void build(){
      for (int k = 0; k < length; k++)
         positions[k] = new PositionNode(k);
      for (int k = 0; k < 26; k++)
         letters[k] = new LetterNode(k);

      for (int k = 0; k < length; k++)
         for (int l = 0; l < 26; l++)
           addEdge(k, l, 1);

      for (int l = 0; l < 26; l++){
         letters[l].addSink(end);
         letters[l].addExtra(extra);
      }
   }

   void addEdge(int from, int to, int cap){
      Edge e = new Edge(positions[from], letters[to], cap);
      positions[from].addEdge(e, to);
      letters[to].addEdge(e, from);
   }

   void addRound(String guess, String scores){
       int [] letterScore = new int[26];
       for (int k = 0; k < length; k++){
          int guessInt = guess.charAt(k) - 'a';
          char score = scores.charAt(k);
          LetterNode letter = letters[guessInt];
          PositionNode position = positions[k];
          switch (score){
             case 'G':  position.fix(guessInt);
                        letterScore[guessInt]++;
                        break;
             case 'Y':  position.remove(guessInt);
                        letterScore[guessInt]++;
                        break;
             case 'B':  position.remove(guessInt);
                        letter.clearExtra();
                        break;
          }
       }
       for (int l = 0; l < 26; l++)
          letters[l].update(letterScore[l]);
   }
   
   void solve(){
      connectOver();
      for (int k = 0; k < length; k++){
         if (positions[k].findPath(null) == false)
            System.out.println("Alarm");;
      }
   }

   void connectOver(){
      int over = length;
      for (int l = 0; l < 26; l++)
         over -= letters[l].getScore();
      Edge e = new Edge(extra, end, over);
      extra.toSink = e;
      extraToEnd = e;
   }

   String solution(){
      StringBuffer s = new StringBuffer(length);
      for (int k = 0; k < length; k++)
         s.append((char)(positions[k].letter + 'a'));
      return s.toString();
   }


}

class Node{
   public static final int INF = 2000;
   static int length;

   int id;

   Node(int idIn){
      id = idIn;
   }

   boolean findPath(Node from){
      System.out.println("alarm : findpath in Node");
      return false;
   }

}

class LetterNode extends Node{

   Edge toSink;
   Edge toExtra;
   Edge [] positions;

   public LetterNode(int l){
      super(l);
      positions = new Edge[length];
   }

   void clearExtra(){
    // toExtra.kill();
      toExtra = null;
   }

   void addEdge(Edge e, int k){
       positions[k] = e;
   }

   void addSink(Node sink){
      Edge e = new Edge(this, sink, 0);
      toSink = e;
   }

   void addExtra(Extra extra){
      Edge e = new Edge(this, extra, INF);
      toExtra = e;
      extra.addEdge(e, id);
   }

   void update(int score){
      toSink.update(score);
   }
   
   int getScore(){
      return toSink.cap;
   }
   
   boolean findPath(Node from){

      if(toSink.findPath(this))
         return true;

      if (toExtra != null && toExtra.findPath(this))
         return true;

      int pos = from.id;
      for (int k = 0; k < length; k++)
         if (k != pos){
            if (positions[k].findPath(this))
               return true;
         }
      return false;
   }
}

class PositionNode extends Node{
    Edge [] letters = new Edge [26];
    int letter = -1;

    PositionNode(int pos){
       super(pos);
    }

    void addEdge(Edge e, int l){
       letters[l] = e;
    }

    void fix (int letter){
       this.letter = letter;
       for (int l = 0; l < 26; l++)
          if (l != letter){
             //letters[l].kill();
             letters[l] = null;
          }
    }

    void remove (int l){
       //letters[l].kill();
       letters[l] = null;
    }

    boolean findPath(Node node){
        int l = -1;
        if (node != null)
           l = node.id;
        for (int k = 0; k < 26; k++)
           if (k != l){
               if (letters[k] != null && letters[k].findPath(this)){
                  letter = k;
                  return true;
               }
           }
        return false;
    }

}

class Extra extends Node{
   Edge [] letters = new Edge[26];
   Edge toSink;

   Extra (){
      super(-2);
   }

   void addEdge(Edge e, int l){
      letters[l] = e;
   }

   boolean findPath(Node node){
      if (toSink.findPath(this))
         return true;
      int l = -1;
      if (node != null)
         l = node.id;
      for (int k = 0; k < 26; k++)
         if (k != l)
            if (letters[k] != null && letters[k].findPath(this))
               return true;
         return false;
   }
}

class Sink extends Node{
   Sink(){
      super (-1);
   }

   boolean findPath(Node from){
      return true;
   }
}

class Edge{
   Node from;
   Node to;
   int cap = 0;
   int flow = 0;
   boolean visited = false;

   public Edge(Node fromIn, Node toIn, int capIn){
      from = fromIn;
      to = toIn;
      cap = capIn;
   }

   boolean findPath(Node fromIn){
      if (visited)
         return false;
      visited = true;
      if (fromIn == from){
         if  (cap - flow > 0 && to.findPath(fromIn)){
            flow ++;
            visited = false;
            return true;
         }
      }
      else{
         if (flow > 0 && from.findPath(to)){
            flow --;
            visited = false;
            return true;
         }
      }
      visited = false;
      return false;
   }

   void update(int c){
      if (c > cap)
         cap = c;
   }
/*
   void kill(){
      cap = 0;
   }
*/
}