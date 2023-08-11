package unimath.algebra;

public class Exponent<T extends Number> extends AlgebraUnit<T> {
    private final AlgebraUnit<T> a;
    private final AlgebraUnit<T> b;

    public Exponent(AlgebraUnit<T> a, AlgebraUnit<T> b) {
        this.a = a;
        this.b = b;
    }

    @Override
    public T computeValue() {
        return exponent(a.computeValue(), b.computeValue());
    }

    @Override
    public String toString() {
        return String.format("%s ^ %s", a.toString(), b.toString());
    }

    private static <T extends Number>T exponent(T a, T b) {
        return (T)(Double) Math.pow(a.doubleValue(), b.doubleValue());
    }
}
