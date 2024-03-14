package unimath.algebra;

public class Exponent extends AlgebraUnit {
    private final AlgebraUnit a;
    private final AlgebraUnit b;

    public Exponent(AlgebraUnit a, AlgebraUnit b) {
        this.a = a;
        this.b = b;
    }

    @Override
    public String computeValue() {
        return Double.toString(Math.pow(Double.parseDouble(a.computeValue()), Double.parseDouble(b.computeValue())));
    }

    @Override
    public String toString() {
        return String.format("%s ^ %s", a.toString(), b.toString());
    }
}
