package unsigned; // Declare the package

import java.math.BigInteger;


public class UnsignedLong {
    private static final BigInteger MAX_VALUE = BigInteger.valueOf(2).pow(64); // 2^64
    private BigInteger value;

    // Constructor to create an UnsignedLong from a long (which is signed)
    public UnsignedLong(long value) {
        this.value = BigInteger.valueOf(value).and(MAX_VALUE.subtract(BigInteger.ONE));
    }

    // Constructor to create an UnsignedLong from a BigInteger
    public UnsignedLong(BigInteger value) {
        this.value = value.and(MAX_VALUE.subtract(BigInteger.ONE));
    }

    // Addition
    public UnsignedLong add(UnsignedLong other) {
        BigInteger result = this.value.add(other.value);
        return new UnsignedLong(result.and(MAX_VALUE.subtract(BigInteger.ONE)));
    }

    // Subtraction
    public UnsignedLong subtract(UnsignedLong other) {
        BigInteger result = this.value.subtract(other.value);
        if (result.signum() < 0) {
            result = result.add(MAX_VALUE); // Simulate wrapping around
        }
        return new UnsignedLong(result.and(MAX_VALUE.subtract(BigInteger.ONE)));
    }

    // Multiplication
    public UnsignedLong multiply(UnsignedLong other) {
        BigInteger result = this.value.multiply(other.value);
        return new UnsignedLong(result.and(MAX_VALUE.subtract(BigInteger.ONE)));
    }

    // Division
    public UnsignedLong divide(UnsignedLong other) {
        if (other.value.equals(BigInteger.ZERO)) {
            throw new ArithmeticException("Division by zero");
        }
        BigInteger result = this.value.divide(other.value);
        return new UnsignedLong(result.and(MAX_VALUE.subtract(BigInteger.ONE)));
    }

    // Modulo
    public UnsignedLong mod(UnsignedLong other) {
        if (other.value.equals(BigInteger.ZERO)) {
            throw new ArithmeticException("Modulo by zero");
        }
        BigInteger result = this.value.mod(other.value);
        return new UnsignedLong(result.and(MAX_VALUE.subtract(BigInteger.ONE)));
    }

    
    // Left shift
    public UnsignedLong shiftLeft(int n) {
        BigInteger result = this.value.shiftLeft(n);
        return new UnsignedLong(result.and(MAX_VALUE.subtract(BigInteger.ONE)));
    }

    // Right shift (logical, unsigned)
    public UnsignedLong shiftRight(int n) {
        BigInteger result = this.value.shiftRight(n);
        return new UnsignedLong(result.and(MAX_VALUE.subtract(BigInteger.ONE)));
    }

    
    // XOR operation
    public UnsignedLong xor(UnsignedLong other) {
        BigInteger result = this.value.xor(other.value);
        return new UnsignedLong(result.and(MAX_VALUE.subtract(BigInteger.ONE)));
    }

    // Convert to long (only works correctly for values that fit in 64 bits)
    public long longValue() {
        return this.value.longValue();
    }

    // Convert to BigInteger for other operations
    public BigInteger toBigInteger() {
        return this.value;
    }

    @Override
    public String toString() {
        return this.value.toString();
    }

    // Compare two UnsignedLong values
    public int compareTo(UnsignedLong other) {
        return this.value.compareTo(other.value);
    }
}