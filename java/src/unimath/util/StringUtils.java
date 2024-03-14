package unimath.util;

import java.util.ArrayList;
import java.util.Stack;

public class StringUtils {

    public static int[] findTupleIndexes(String[] arr, String start, String end) {
        ArrayList<Integer> indexes = new ArrayList<>();
        Stack<Integer> stack = new Stack<>();
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] == null) {
                continue;
            }
            if (arr[i].equals(start)) {
                stack.push(i);
            } else if (arr[i].equals(end) && !stack.isEmpty()) {
                if (stack.size() == 1) {
                    indexes.add(stack.pop());
                    indexes.add(i);
                } else {
                    stack.pop();
                }
            }
        }
        return indexes.stream().mapToInt(i -> i).toArray();
    }
}
