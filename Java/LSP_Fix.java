class Rectangle {
    protected int width, height;

    void setWidth(int w) {
        width = w;
    }

    void setHeight(int h) {
        height = h;
    }

    int getWidth() {
        return width;
    }

    int getHeight() {
        return height;
    }
}

class Square_Fix {
    final private Rectangle rect;

    public Square_Fix() {
        rect = new Rectangle();
    }

    void setWidth(int w) {
        rect.setWidth(w);
        rect.setHeight(w);
    }

    int getWidth() {
        return rect.getWidth();
    }

    int getHeight() {
        return rect.getHeight();
    }
}

public class LSP_Fix {
    public static void main(String[] args) {
        Rectangle r = new Rectangle();
        Square_Fix r2 = new Square_Fix();

        r.setWidth(10);
        r.setHeight(5);
        r2.setWidth(10);

        System.out.println("Rectangle's Size : Width " + r.getWidth() + ", Height " + r.getHeight());
        System.out.println("Square's Size : Width " + r2.getWidth() + ", Height " + r2.getHeight());
    }
}
