
public class karleksbrev {
    // Define the modulus as a constant
    static final long MOD = 1125899906842679L;

    // Hashf method to compute the hash for a given string
    static long Hashf(String x) {
        long ret = 0;
        for (char v : x.toCharArray()) {
            ret += v == '1' ? 1L : 0L;
            ret *= 1087L;
        }
        return ret;
    }

    // Length of the result hash string
    static int k = 50;

    // Hashstring method to create a hash string of length k
    static String Hashstring(String x) {
        char[] ret = new char[k];
        for (int i = 0; i < k; i++) {
            ret[i] = '0';
        }

        long h = Hashf(x);

        for (int j = 0; j < k; j++) {
            // Check the bit at position j using the bitwise AND
            if ((h & (1L << j)) > 0) {
                ret[j] = '1';
            }
        }

        return new String(ret);
    }

    // Method to encode the string
    public static String encode(String x) {
        return x + Hashstring(x);
    }

    // Method to decode the string
    public static String decode(String x) {
        int n = x.length();

        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                // Create a mutable character array from the string
                char[] u = x.toCharArray();

                // Flip the bits in the range [i, j]
                for (int l = i; l <= j; l++) {
                    u[l] = (u[l] == '1') ? '0' : '1';
                }

                // Extract the original message without the hash part
                String meat = new String(u, 0, n - k);
                String encoded = encode(meat);

                // Check if flipping the bits and encoding results in the original string
                if (new String(u).equals(encoded)) {
                    return meat;
                }
            }
        }

        throw new IllegalStateException("its joever");
    }
}
