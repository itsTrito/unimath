package unimath.algebra;

public class Modulo<T extends Number> extends AlgebraUnit<T> {
    private final AlgebraUnit<T> a;
    private final AlgebraUnit<T> b;

    public Modulo(AlgebraUnit<T> a, AlgebraUnit<T> b) {
        this.a = a;
        this.b = b;
    }

    @Override
    public T computeValue() {
        return modulo(a.computeValue(), b.computeValue());
    }

    @Override
    public String toString() {
        return String.format("%s % %s", a.toString(), b.toString());
    }

    private static <T extends Number>T modulo(T a, T b) {
        if (a instanceof Long) {
            return (T)(Long) (a.longValue() % b.longValue());
        }
        if (a instanceof Short) {
            return (T)(Integer) (a.shortValue() % b.shortValue());
        }
        if (a instanceof Float) {
            return (T)(Float) (a.floatValue() % b.floatValue());
        }
        if (a instanceof Double) {
            return (T)(Double) (a.doubleValue() % b.doubleValue());
        }
        if (a instanceof Byte) {
            return (T)(Integer) (a.byteValue() % b.byteValue());
        }

        return (T)(Integer) (a.intValue() % b.intValue());
    }
}
