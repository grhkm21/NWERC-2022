import java.util.*;
import java.io.*;

public class PizzaPK{
   public static void main (String [] args){
       run();
   }

   static void run(){
       PizzaPK problem = readTest();
       if(problem.solvable())
          System.out.println( "possible");
       else
          System.out.println( "impossible");
   }

   public static PizzaPK readTest(){
      PizzaPK problem = null;
      try{
         BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
         String line = in.readLine();
         Scanner ir = new Scanner(line);
         int edges = ir.nextInt();
         int nodes = ir.nextInt();
         problem = new PizzaPK(nodes);
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
   int cycle = 0;
   int cc = 0; // component count

   int size;
   Node [] nodes;

   public PizzaPK(int sizeIn){
      size = sizeIn;
      nodes = new Node[size + 1];
      for (int k = 1; k <= size; k++)
         nodes[k] = new Node(k);
   }

   void addVertex(int n1, int n2){
      nodes[n1].addNeighbour(nodes[n2]);
      nodes[n2].addNeighbour(nodes[n1]);
   }

   boolean solvable(){
      for (int k = 1; k < size; k++){
         if (nodes[k].component == 0)
            makeComponent(k);
         if(fork)
            return false;
      }
      if (cycle >= 1)
         return cc == 1;
      return true;
   }

   void makeComponent(int next){
      cc++;
      int from = 0;
      while(next > 0){
         Node nextNode = nodes[next];
         if (nextNode.component == cc){
            cycle++;
            break;
         }
         int volgende = nextNode.setComponent(cc, from);
         from = next;
         next = volgende;
         if (next == Node.FORK)
            fork = true;
      }
   }

}

class Node{
   static final int FORK = -1;
   int num;
   int component;
   ArrayList<Node> neighbours = new ArrayList<Node>();

   public Node (int numIn){
     num = numIn;
   }

   void addNeighbour(Node n){
      neighbours.add(n);
   }
   
   int setComponent(int comp, int from){
      component = comp;
      int next = 0;
      for (Node n : neighbours){

         if (n!= this && n.num != from){
            if(n.isLeaf()){
                n.component = comp;
            }
            else{ // no leaf
               if(from == 0)
                  from = n.num;
               else if (next == 0 )
                       next = n.num;
                    else
                       return FORK;
             }
         }
      }
      return next;
   }
   
   boolean isLeaf(){
      return neighbours.size() == 1;
   }


}