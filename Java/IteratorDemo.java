import java.util.*;

public class IteratorDemo {
    public static void main(String[] args) {
        Collection<String> list = Arrays.asList("A", "B", "C");

        Iterator<String> iterator = list.iterator();
        while(iterator.hasNext())
            System.out.print(iterator.next() + ",");
        System.out.println();

        while(iterator.hasNext()) //이미 순회를 하였기에 empty 상태가 됨
            System.out.print(iterator.next() + ",");
        System.out.println();

        iterator = list.iterator(); //iterator을 재설정하여 다시 채움
        while(iterator.hasNext())
            System.out.print(iterator.next() + ",");
        System.out.println();
    }
}
