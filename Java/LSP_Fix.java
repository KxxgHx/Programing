class Rectangle_Fix {
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


    static class Square_Fix {
        private final Rectangle_Fix rect;

        public Square_Fix() {
            rect = new Rectangle_Fix();
        }

        void setSize(int size) {
            rect.setWidth(size);
            rect.setHeight(size);
        }

        int getWidth() {
            return rect.getWidth();
        }

        int getHeight() {
            return rect.getHeight();
        }
    }
}

public class LSP_Fix {
    public static void main(String[] args) {
        Rectangle_Fix r = new Rectangle_Fix();
        Rectangle_Fix.Square_Fix s = new Rectangle_Fix.Square_Fix();

        r.setWidth(10);
        r.setHeight(5);

        s.setSize(10);

        System.out.println("Rectangle's Size : Width " + r.getWidth() + ", Height " + r.getHeight());
        System.out.println("Square's Size : Width " + s.getWidth() + ", Height " + s.getHeight());
    }
}

