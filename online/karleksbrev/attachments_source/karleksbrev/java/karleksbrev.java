public class karleksbrev {
    public static String encode(String S) {
        StringBuilder E = new StringBuilder();
        for (char c : S.toCharArray()) {
            for (int i = 0; i < 5; i++) {
                E.append(c);
            }
        }
        return E.toString();
    }

    // Note: this E is E after it has been corrupted
    public static String decode(String E) {
        StringBuilder ret = new StringBuilder();
        while (E.length() > 0) {
            String chunk = E.substring(0, 5);
            E = E.substring(5);
            ret.append(chunk.charAt(2));
        }
        return ret.toString();
    }
}
