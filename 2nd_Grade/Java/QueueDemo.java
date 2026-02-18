import java.util.LinkedList;
import java.util.NoSuchElementException;
import java.util.Queue;

public class QueueDemo {
    public static void main(String[] args) {
        Queue<String> q = new LinkedList<>();

        //q.remove();
        System.out.println(q.poll());
        q.offer("Apple");
        System.out.println("Did you add Banana? " + q.offer("Banana"));

        try {
            q.add("Cherry");
        } catch (IllegalStateException e) {
        }

        System.out.println("Head: " + q.peek());
        String head = null;
        try {
            head = q.remove();
            System.out.println(head + " removed");
            System.out.println("New head: " + q.element());
        } catch (NoSuchElementException e) {

        }
        
        head = q.poll();
        System.out.println(head + " removed");
        System.out.println("New head: " + q.peek());
    }
}
