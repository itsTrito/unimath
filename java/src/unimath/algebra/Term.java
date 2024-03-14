package unimath.algebra;

public class Term extends AlgebraUnit {

    private final String value;

    public Term(String value) {
        this.value = value;
    }

    @Override
    public String computeValue() {
        return value;
    }

    @Override
    public String toString() {
        return value;
    }
}
