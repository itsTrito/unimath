package unimath.algebra;

public class Function {
    private final String[] arguments;
    private final String value;

    public Function(String value, String... arguments) {
        this.value = value;
        this.arguments = arguments;
    }

    public String computeValue(AlgebraUnit... arguments) {
        String value = this.value;
        for (int i = 0; i < this.arguments.length; i++) {
            if (i < arguments.length) {
                value = value.replaceAll(this.arguments[i], arguments[i].toString());
            }
        }
        return value;
    }

    @Override
    public String toString() {
        return "(" + String.join(", ", arguments) + ") => " + value;
    }

    public int getArgsLength() {
        return this.arguments.length;
    }
}
