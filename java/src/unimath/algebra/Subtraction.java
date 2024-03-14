package unimath.algebra;

public class Subtraction extends AlgebraUnit {
    private final AlgebraUnit a;
    private final AlgebraUnit b;

    public Subtraction(AlgebraUnit a, AlgebraUnit b) {
        this.a = a;
        this.b = b;
    }

    @Override
    public String computeValue() {
        return Float.toString(Float.parseFloat(a.computeValue()) - Float.parseFloat(b.computeValue()));
    }

    @Override
    public String toString() {
        return String.format("%s - %s", a.toString(), b.toString());
    }
}
