package unimath.algebra;

public class Term<T extends Number> extends AlgebraUnit<T> {

    private final T value;

    public Term(T value) {
        this.value = value;
    }

    @Override
    public T computeValue() {
        return value;
    }

    @Override
    public String toString() {
        return value.toString();
    }
}
