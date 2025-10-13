import java.util.*;

public class IteratorDemo {
    public static void main(String[] args) {
        Collection<String> list = Arrays.asList("A", "B", "C");

        Iterator<String> iterator = list.iterator();
        while(iterator.hasNext())
            System.out.print(iterator.next() + ",");
        System.out.println();

        while(iterator.hasNext())
            System.out.print(iterator.next() + ",");
        System.out.println();

        iterator = list.iterator();
        while(iterator.hasNext())
            System.out.print(iterator.next() + ",");
        System.out.println();
    }
}
