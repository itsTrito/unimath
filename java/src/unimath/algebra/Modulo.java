package unimath.algebra;

public class Modulo extends AlgebraUnit {
    private final AlgebraUnit a;
    private final AlgebraUnit b;

    public Modulo(AlgebraUnit a, AlgebraUnit b) {
        this.a = a;
        this.b = b;
    }

    @Override
    public String computeValue() {
        return Double.toString(Double.parseDouble(a.computeValue()) % Double.parseDouble(b.computeValue()));
    }

    @Override
    public String toString() {
        return a.toString() + " % " + b.toString();
    }
}
