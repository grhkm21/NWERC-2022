import java.util.*;
import java.io.*;

public class PizzaPK2{
  
  static String infile = "29-random-possible.in";
   public static void main (String [] args){
      run();
   }

   static void run(){
       PizzaPK2 problem = readTest();
       if(problem.solvable())
          System.out.println( "possible");
       else
          System.out.println( "impossible");
   }

   public static PizzaPK2 readTest(){
      PizzaPK2 problem = null;
      InputStream is = null;
      try{
         is = System.in;
         BufferedReader in = new BufferedReader(new InputStreamReader(is));
         String line = in.readLine();
         Scanner ir = new Scanner(line);
         int edges = ir.nextInt();
         int nodes = ir.nextInt();
         problem = new PizzaPK2(nodes);
         for (int k = 1; k <= edges; k++){
            line = in.readLine();
            String [] words = line.split(" ");
            problem.addVertex(Integer.parseInt(words[0]), Integer.parseInt(words[1]));
         }
      }
      catch (IOException iox){System.out.println( iox);}
      return problem;
   }

////////////////////////////////////

   boolean fork = false;
   int cycle = 0; // cycle count
   int cc = 0; // component count

   int size;
   Node [] nodes;

   public PizzaPK2(int sizeIn){
      size = sizeIn;
      nodes = new Node[size + 1];
   }

   void addVertex(int n1, int n2){
      if (nodes[n1] == null)
         nodes[n1] = new Node(n1);
      if (nodes[n2] == null)
         nodes[n2] = new Node(n2);
      nodes[n1].addNeighbour(nodes[n2]);
      nodes[n2].addNeighbour(nodes[n1]);
   }

   boolean solvable(){
      for (int k = 1; k < size; k++){
         if (nodes[k] != null && nodes[k].component == 0)
            makeComponent(nodes[k]);
         if(fork)
            return false;

      }
      if (cycle >= 1)
         return cc == 1;
      return true;
   }

   void makeComponent(Node next){
      cc++;
      ArrayList<Node> verder = next.startComponent(cc);
      if (verder == null){
         switch (next.diagnosis){
            case Node.END   : break;
            //case Node.CYCLE : cycle++; break;
            case Node.FORK  : fork = true; break;
            case Node.LEAF  : cc--; break;
         }
         return;
      }

      Node volgende = verder.get(0);
      int diagnosis = follow(cc, next, volgende);
      switch (diagnosis){
          case Node.END   : break;
          case Node.CYCLE : cycle++; break;
          case Node.FORK  : fork = true; break;
       }
       if (diagnosis != Node.CYCLE)
           if (verder.size() > 1){
              volgende = verder.get(1);
              diagnosis = follow(cc, next, volgende);
              switch (diagnosis){
                 case Node.END   : break;
                // case Node.CYCLE : cycle++; break;
                 case Node.FORK  : fork = true; break;
              }
           }
   }

   int follow(int cc, Node from, Node next){
       while(next != null){
          Node volgende = next.setComponent(cc, from);
          from = next;
          next = volgende;
       }
       return from.diagnosis;
   }

}

class Node implements Comparable<Node>{
   static final int END = 0;
   static final int CYCLE = 1;
   static final int FORK = 2;
   static final int LEAF = 3;
   
   int diagnosis;
   int num;
   int component;

   TreeSet<Node> neighbours = new TreeSet<Node>();

   public Node (int numIn){
      num = numIn;
   }

   void addNeighbour(Node n){
      neighbours.add(n);
   }
   
  ArrayList<Node> startComponent(int comp){
     if (neighbours.size() == 1){ // leaf
         Node n = neighbours.first();
         if (n == this){
            component = comp;
            diagnosis = END;
            return null;
         }
         else if (n.isLeaf()){
            component = comp;
            n.component = comp;
            diagnosis = END;
            return null;
         }
         else{
            diagnosis = LEAF;
            return null;
         }
      }
      component = comp;

      ArrayList<Node> door = new ArrayList<Node>();
      for (Node n : neighbours)
         if (n!= this){
            if(n.isLeaf()){
               n.component = comp;
             }
            else{ // no leaf
               door.add(n);
            }
            if (door.size() > 2){
               diagnosis = FORK;
               return null;
            }
        }
        if (door.size() == 0){
           diagnosis = END;
           return null;
        }
        return door;
   }

   Node setComponent(int comp, Node from){
      if (component > 0){
         diagnosis = CYCLE;
         return null;
      }
      component = comp;
      Node next = null;
      for (Node n : neighbours){
         if (n!= this && n != from){
             if(n.isLeaf())
                n.component = comp;
             else{ // no leaf
                if (next == null ){
                   next = n;
                }
                else{  //second exit
                   diagnosis = FORK;
                   return null;
                }
             }
         }
      }
      if (next == null)
         diagnosis = END;
      return next;
   }
   
   boolean isLeaf(){
      return neighbours.size() == 1;
   }

   public String toString(){
      String answer = "Node : " + num + " Neighbours : " ;
      for (Node n : neighbours)
         answer += " " + n.num;
      return answer;
   }
   
   public int compareTo(Node that){
      return this.num - that.num;
   }
}