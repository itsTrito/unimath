package unimath.algebra;

import unimath.util.StringUtils;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;

public class Interpreter {

    private String lastAnswer = "";
    private final HashMap<String, String> variables = new HashMap<>();
    private final HashMap<String, Function> functions = new HashMap<>();

    public String[] tokenize(String input) {

        ArrayList<String> tokens = new ArrayList<>();
        int i = 0;
        String last = null;
        while (i < input.length()) {
            char c = input.charAt(i);
            if (last == null) {
                last = Character.toString(c);
                i++;
                continue;
            }

            if (c == ' ') {
                i++;
                continue;
            }

            if (c == ',') {
                c = '.';
            }

            if (isDifferent(last, Character.toString(c))) {
                tokens.add(last);
                last = Character.toString(c);
            } else {
                last += c;
            }
            i++;
        }
        tokens.add(last);
        return tokens.toArray(new String[0]);
    }

    public String evaluate(String input) {
        AlgebraUnit unit = build(input);
        String result = unit.computeValue();
        lastAnswer = result;
        return result;
    }

    public AlgebraUnit build(String input) {
        input = replaceAns(input);
        if (input.contains("=")) {
            return new Term(handleAssignation(input));
        }
        input = replaceFunctions(input);
        input = replaceVariables(input);
        String[] tokens = tokenize(input);
        return parse(tokens);
    }

    private String replaceVariables(String input) {
        for (String var : variables.keySet()) {
            String value = "";
            if (input.contains(var)) {
                value = build(variables.get(var)).computeValue();
            }
            input = input.replaceAll(var, value);
        }
        return input;
    }

    private String replaceFunctions(String input) {
        for (String name : functions.keySet()) {
            Function f = functions.get(name);
            if (input.contains(name)) {
                String test = name + "(";
                int index = input.indexOf(test);
                int start = index + test.length();
                AlgebraUnit[] args = new AlgebraUnit[f.getArgsLength()];
                int i = 0;
                StringBuilder tmp = new StringBuilder();
                while (input.charAt(start) != ')') {
                    if (input.charAt(start) == ' ') {
                        start++;
                        continue;
                    }

                    if (input.charAt(start) == ',') {
                        args[i] = new Term(tmp.toString());
                        tmp = new StringBuilder();
                        i++;
                        start++;
                        continue;
                    }
                    tmp.append(input.charAt(start));
                    start++;
                }
                args[i] = new Term(tmp.toString());
                String before = input.substring(0, index);
                String after = input.substring(start + 1);
                input = before + f.computeValue(args) + after;
            }
        }
        return input;
    }

    private String handleFunctionAssignment(String signature, String value) {
        String[] tokens = signature.split("\\(");
        String name = tokens[0].trim();
        String[] args = tokens[1].substring(0, tokens[1].length() - 1).split(",");
        functions.put(name, new Function(value, args));
        return value;
    }

    private String handleVarAssignation(String var, String value) {
        variables.put(var, value);
        return value;
    }

    private String handleAssignation(String input) {
        String[] tokens = input.split("=");
        String var = tokens[0].trim();
        String value = tokens[1].trim();
        if (var.contains("(") && var.contains(")")) {
            return handleFunctionAssignment(var, value);
        }
        return handleVarAssignation(var, value);
    }

    private String replaceAns(String input) {
        if (lastAnswer.isEmpty()) {
            return input;
        }
        return input.replaceAll("[aA][nN][sS]", lastAnswer);
    }

    private String[] removeParenthesis(String[] tokens) {
        ArrayList<String> list = new ArrayList<>(Arrays.asList(tokens));
        int[] pIndexes = StringUtils.findTupleIndexes(tokens, "(", ")");
        for (int index = pIndexes.length - 1; index >= 1; index -= 2) {
            int start = pIndexes[index - 1];
            int end = pIndexes[index];
            String[] sub = Arrays.copyOfRange(tokens, start + 1, end);
            AlgebraUnit a = parse(sub);
            Parenthesis p = new Parenthesis(a);
            list.set(start, p.toString());
            for (int j = end; j >= start + 1; j--) {
                list.set(j, null);
            }
        }

        for (int i = list.size() - 1; i >= 0; i--) {
            if (list.get(i) == null) {
                list.remove(i);
            }
        }
        return list.toArray(new String[0]);
    }

    private AlgebraUnit parse(String[] tokens) {

        if (tokens.length == 1) {
            if (tokens[0].charAt(0) == '(') {
                String content = tokens[0].substring(1, tokens[0].length() - 1);
                return new Parenthesis(build(content));
            }
            return new Term(tokens[0]);
        }

        // Parenthesis
        tokens = removeParenthesis(tokens);

        if (tokens.length == 1) {
            return parse(tokens);
        }

        // Addition and Subtraction
        int i = tokens.length - 1;
        while (i > 0) {
            if (tokens[i].equals("+")) {
                return new Addition(parse(Arrays.copyOfRange(tokens, 0, i)), parse(Arrays.copyOfRange(tokens, i + 1, tokens.length)));
            } else if (tokens[i].equals("-")) {
                return new Subtraction(parse(Arrays.copyOfRange(tokens, 0, i)), parse(Arrays.copyOfRange(tokens, i + 1, tokens.length)));
            }
            i--;
        }

        // Multiplication and Division
        i = tokens.length - 1;
        while (i > 0) {
            switch (tokens[i]) {
                case "*" -> {
                    return new Multiplication(parse(Arrays.copyOfRange(tokens, 0, i)), parse(Arrays.copyOfRange(tokens, i + 1, tokens.length)));
                }
                case "/" -> {
                    return new Division(parse(Arrays.copyOfRange(tokens, 0, i)), parse(Arrays.copyOfRange(tokens, i + 1, tokens.length)));
                }
                case "%" -> {
                    return new Modulo(parse(Arrays.copyOfRange(tokens, 0, i)), parse(Arrays.copyOfRange(tokens, i + 1, tokens.length)));
                }
            }
            i--;
        }

        // Exponent
        i = tokens.length - 1;
        while (i > 0) {
            if (tokens[i].equals("^")) {
                return new Exponent(parse(Arrays.copyOfRange(tokens, 0, i)), parse(Arrays.copyOfRange(tokens, i + 1, tokens.length)));
            }
            i--;
        }


        return null;
    }

    private boolean isDifferent(String last, String current) {
        return isNumber(last) != isNumber(current) || !isNumber(current);
    }

    private boolean isNumber(String sub) {
        // Regex matches digits, points and commas
        return sub.matches("^[0-9.]*$");
    }

}
