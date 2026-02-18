import java.util.Stack;

public class StackDemo {
    public static void main(String[] args) {
        Stack<String> s1 = new Stack<>();

        s1.push("Apple");
        s1.push("Banana");
        s1.push("Cherry");

        System.out.println(s1.peek());

        System.out.println(s1.pop());
        System.out.println(s1.pop());
        System.out.println(s1.pop());
        System.out.println();

        Stack<Integer> s2 = new Stack<>();

        s2.add(10);
        s2.add(20);
        s2.add(1, 100);
        
        for(int value:s2)
        {
            System.out.print(value + " ");
        }
        System.out.println();

        while(!s2.empty())
            System.out.print(s2.pop() + " ");
    }
}
