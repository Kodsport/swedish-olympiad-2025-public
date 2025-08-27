// Testing tool for the task Love Letter.
//
// Usage:
//
//   bash unix_compile.sh
//   bash unix_run.sh
//
// input.txt uses the following format:
//
// N K
// S
// L R
// Where N is the length of S,
// K is the maximum length of a message that the encoder may produce,
// S is the message that should be sent,
// L and R denote the interval that should be flipped.
// More precisely, the judge will corrupt m[L], m[L+1], ..., m[R]
//
// Example input:
//
// 5 10
// 01011
// 1 3
//
//
// If --silent is passed, the communication output will not be printed.
//
// The tool is provided as-is, and you should feel free to make
// whatever alterations or augmentations you like to it. Notably,
// this is not the grader used in Kattis. This grader is also more informative
// as to how your program failed compared to Kattis.

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        boolean silent = false;

        if (args.length > 0 && args[0].equals("--silent")) {
            silent = true;
        }

        if (args.length > 0 && args[0].equals("-h")) {
            System.out.println("Usage: program [--silent] < input.txt");
            return;
        }

        Scanner scanner = new Scanner(System.in);
        
        // Read input values
        int N, K, L, R;
        String S;
        
        String[] parts = scanner.nextLine().split(" ");
        N = Integer.parseInt(parts[0]);
        K = Integer.parseInt(parts[1]);
        S = scanner.nextLine();
        parts = scanner.nextLine().split(" ");
        L = Integer.parseInt(parts[0]);
        R = Integer.parseInt(parts[1]);
        
        // Validate input
        if (S.length() != N) {
            System.out.println("[X] Error: length(S)=" + S.length() + " does not match N=" + N);
            return;
        }
        
        for (char c : S.toCharArray()) {
            if (c != '0' && c != '1') {
                System.out.println("[X] Error: S=" + S + " contains character \"" + c + "\", which is not 0 or 1");
                return;
            }
        }

        if (!silent) {
            System.out.println("[*] Running with N=" + N + ", K=" + K + ", S=" + S + ", L=" + L + ", R=" + R);
        }

        // Encode S
        String E = karleksbrev.encode(S);
        if (!silent) {
            System.out.println("[*] S=" + S + ", encode(S)=" + E);
        }

        // Sanity check for E
        if (E == null || E.isEmpty()) {
            System.out.println("[X] Error: encoder gave an empty E for S=" + S);
            return;
        }
        if (E.length() > K) {
            System.out.println("[X] Error: encoder gave too long E. length(E)=" + E.length() + " > K=" + K);
            return;
        }
        for (char c : E.toCharArray()) {
            if (c != '0' && c != '1') {
                System.out.println("[X] Error: encoder gave E containing character \"" + c + "\", which is not 0 or 1");
                return;
            }
        }

        if (L < 0 || R < 0 || L >= E.length() || R >= E.length()) {
            System.out.println("[X] Error: L=" + L + " or R=" + R + " is out of bounds for length(E)=" + E.length());
            return;
        }

        // Corrupt E by flipping bits from L to R
        StringBuilder EBuilder = new StringBuilder(E);
        for (int i = L; i <= R; ++i) {
            char flippedBit = (E.charAt(i) == '0') ? '1' : '0';
            EBuilder.setCharAt(i, flippedBit);
        }
        E = EBuilder.toString();

        if (!silent) {
            System.out.println("[*] E=" + E + " after corrupting");
        }

        // Check that the decoder can decode flipped E
        String decoded = karleksbrev.decode(E);
        if (!decoded.equals(S)) {
            System.out.println("[X] Error: decoder did not find S. E after corrupting=" + E + ", S=" + S + ", decode(E)=" + decoded);
            return;
        }

        if (!silent) {
            System.out.println("[*] decode(E)=" + decoded);
        }

        System.out.println("Success! N=" + N + " len(E)=" + E.length());
    }
}
