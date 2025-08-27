import java.util.*;
import java.io.*;
import java.lang.reflect.Method;
import unsigned.UnsignedLong;

public class Main {

    private static final int _NUM_TESTCASES = 50;
    private static final int _USER_FAIL = 120;
    private static final String _SECRET_KEY = "SUCCESSiujwefguiwehuioew";
    private static final String _SECRET_FAIL = "FAILiujwefguiwehuioew";
    private static int test_type = 0;

	private static UnsignedLong rngState = new UnsignedLong(0);

    private static UnsignedLong nextRand() {
        rngState = rngState.xor(rngState.shiftLeft(21));    // rngState ^= (rngState << 21);
        rngState = rngState.xor(rngState.shiftRight(35));   // rngState ^= (rngState >>> 35);
        rngState = rngState.xor(rngState.shiftLeft(4));     // rngState ^= (rngState << 4);
        rngState = rngState.multiply(new UnsignedLong(2685821657736338717L)); // rngState = (rngState * 2685821657736338717L);
        return rngState;
    }

    private static int randInterval(int l, int r) {
        // Note: The range size is a 64-bit unsigned value
        UnsignedLong rangeSize = new UnsignedLong((long)(r - l + 1));
        UnsignedLong randValue = nextRand();
        UnsignedLong modValue = randValue.mod(rangeSize);  // randValue % rangeSize
        return l + (int)modValue.longValue();  // Convert to int and return
    }

    public static void permuteVector(List<AbstractMap.SimpleEntry<String, String>> vec) {
        for (int i = vec.size() - 1; i > 0; i--) {
            int j = randInterval(0, i);
            // Swap elements at indices i and j
            AbstractMap.SimpleEntry<String, String> temp = vec.get(i);
            vec.set(i, vec.get(j));
            vec.set(j, temp);
        }
    }

    public static int[] getLr(int elen) {
        int l, r;

        switch (test_type) {
            case 0:
                l = randInterval(0, elen - 1);
                r = randInterval(l, elen - 1);
                return new int[]{l, r};
            case 1:
                l = randInterval(0, elen - 1);
                return new int[]{l, l};
            case 2:
                do {
                    l = randInterval(0, elen - 3);
                } while (l % 2 != 0);
                do {
                    r = randInterval(l, elen - 1);
                } while (r % 2 != 0);
                return new int[]{l, r};
            case 3:
                do {
                    l = randInterval(0, elen - 1);
                } while (l % 2 != 0);
                r = randInterval(l, elen - 1);
                return new int[]{l, r};
            default:
                throw new IllegalStateException("Invalid test_type");
        }
    }

    public static void main(String[] args) throws Exception {
        if (args.length == 0) {
            String path = Main.class.getProtectionDomain().getCodeSource().getLocation().toURI().getPath();

            Runtime rt = Runtime.getRuntime();
			Process enc = new ProcessBuilder("/usr/bin/java", "-cp", System.getProperty("java.class.path"), "Main", "encoder")
				.redirectInput(ProcessBuilder.Redirect.INHERIT)
				.redirectError(ProcessBuilder.Redirect.INHERIT)
				.redirectOutput(ProcessBuilder.Redirect.PIPE)
				.start();

			Process dec = new ProcessBuilder("/usr/bin/java", "-cp", System.getProperty("java.class.path"), "Main", "decoder")
				.redirectOutput(ProcessBuilder.Redirect.INHERIT)
				.redirectError(ProcessBuilder.Redirect.INHERIT)
				.redirectInput(ProcessBuilder.Redirect.PIPE)
				.start();

            String buf = "";
            try (BufferedReader reader = new BufferedReader(new InputStreamReader(enc.getInputStream()))) {
				String line;
				while ((line = reader.readLine()) != null) {
					buf += line + "\n";
				}
            } catch (Exception e) {
                buf = "-1 -1";
            }

            int encWF = enc.waitFor();
            if (encWF != 0) {
                System.out.print(buf);
                buf = "-1 -1";
            }
            
            try (BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(dec.getOutputStream()))) {
                writer.write(buf);
                writer.flush();
            }
            
            if (encWF != 0) {
                if (encWF == _USER_FAIL) {
                    System.exit(0);
                }
                System.exit(encWF);
            }

            int decWF = dec.waitFor();
            if (decWF != 0) {
                if (encWF == _USER_FAIL) {
                    System.exit(0);
                }
                System.exit(encWF);
            }
        } else if (args[0].equals("encoder")) {
            int n, k;
			Scanner sc = new Scanner(System.in);

            n = sc.nextInt();
            k = sc.nextInt();
            int seed;
            test_type = sc.nextInt();
            seed = sc.nextInt();
            rngState = new UnsignedLong(seed);

            List<AbstractMap.SimpleEntry<String, String>> testcases = new ArrayList<>();
            for (int t = 0; t < _NUM_TESTCASES; t++) {
                char[] s = new char[n];
                for (int i = 0; i < n; i++) {
                    s[i] = randInterval(0, 1) == 1 ? '1' : '0';
                }

                String encoded = karleksbrev.encode(new String(s));

                if (encoded.length() == 0) {
                    System.out.println(_SECRET_FAIL + "Encoder gave an empty E");
                    System.exit(_USER_FAIL);
                }

                if (encoded.length() > k) {
                    System.out.println(_SECRET_FAIL + "Encoder gave too long E");
                    System.exit(_USER_FAIL);
                }

                for (char c : encoded.toCharArray()) {
                    if (!(c == '1' || c == '0')) {
                        System.out.println(_SECRET_FAIL + "Encoder gave E containing character which is not 0 or 1");
                        System.exit(_USER_FAIL);
                    }
                }

                char[] encoded_arr = encoded.toCharArray();
                int[] lr = getLr(encoded_arr.length);
                for (int i = lr[0]; i <= lr[1]; i++) {
                    encoded_arr[i] = encoded_arr[i] == '0' ? '1' : '0';
                }

                testcases.add(new AbstractMap.SimpleEntry<>(new String(s), new String(encoded_arr)));
            }

            System.out.println(n + " " + k);
            System.out.println(test_type + " " + seed);
            for (AbstractMap.SimpleEntry<String, String> p : testcases) {
                System.out.print(p.getKey());
                System.out.print("$");
                System.out.print(p.getValue());
                System.out.print("@");
            }

        } else if (args[0].equals("decoder")) {
            int n, k;
			Scanner sc = new Scanner(System.in);
            n = sc.nextInt();
            k = sc.nextInt();
			if (n == -1) System.exit(0);
            int seed;
            test_type = sc.nextInt();
            seed = sc.nextInt();
            rngState = new UnsignedLong(seed);
            sc.nextLine();
            String buf = sc.nextLine();

            List<String> pairs = new ArrayList<>(Arrays.asList(buf.split("@")));
            List<AbstractMap.SimpleEntry<String, String>> testcases = new ArrayList<>();

            for (String pair : pairs) {
                String[] pts = pair.split("\\$");

                assert pts.length == 2;
                testcases.add(new AbstractMap.SimpleEntry<>(pts[0], pts[1]));
            }
            permuteVector(testcases);
            
            UnsignedLong h = new UnsignedLong(0);
            for (AbstractMap.SimpleEntry<String, String> tc : testcases) {
                String S = tc.getKey();
                String E = tc.getValue();
                for (char c : S.toCharArray()) h = (h.add(new UnsignedLong((long)c - 48))).multiply(new UnsignedLong(31));
                for (char c : E.toCharArray()) h = (h.add(new UnsignedLong((long)c - 48))).multiply(new UnsignedLong(31));

                String decoded = karleksbrev.decode(E);
                if (!decoded.equals(S)) {
                    System.out.println(_SECRET_FAIL + "Decoder did not find S");
                    System.exit(0);
                }
            }

            System.err.println("Hash of run: " + h);
            
            System.out.println(_SECRET_KEY + seed);
        }
		System.exit(0);
    }
}

