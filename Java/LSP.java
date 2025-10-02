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

class Square extends Rectangle {
    @Override
    void setWidth(int w) {
        width = height = w;
    }
    @Override
    void setHeight(int h) {
        width = height = h;
    }
}
public class LSP {
    public static void main(String[] args) {
        Rectangle r = new Square();
        r.setWidth(10);
        r.setHeight(5);
        System.out.println(r.getWidth() + ", " + r.getHeight());
    }
}
