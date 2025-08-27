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

#![allow(non_snake_case)]
use std::env;
use std::io::{self};
use std::process;

mod karleksbrev;

fn main() {
    let args: Vec<String> = env::args().collect();
    let mut silent = false;

    if args.len() > 1 {
        if args[1] == "--silent" {
            silent = true;
        } else if args[1] == "-h" {
            println!("Usage: program [--silent] < input.txt");
            return;
        }
    }

    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Failed to read line");
    let values: Vec<i32> = input
        .split_whitespace()
        .map(|s| s.parse().expect("parse error"))
        .collect();
    let (N, K) = (values[0], values[1]);

    input.clear();
    io::stdin().read_line(&mut input).expect("Failed to read line");
    let S = input.trim().to_string();

    input.clear();
    io::stdin().read_line(&mut input).expect("Failed to read line");
    let values: Vec<i32> = input
        .split_whitespace()
        .map(|S| S.parse().expect("parse error"))
        .collect();
    let (L, R) = (values[0], values[1]);

    if S.len() as i32 != N {
        eprintln!(
            "[X] Error: length(S)={} does not match N={}",
            S.len(),
            N
        );
        process::exit(1);
    }

    for c in S.chars() {
        if c != '0' && c != '1' {
            eprintln!(
                "[X] Error: S={} contains character '{}', which is not 0 or 1",
                S, c
            );
            process::exit(1);
        }
    }

    if !silent {
        println!("[*] Running with N={}, K={}, S={}, L={}, R={}", N, K, S, L, R);
    }

    // Encode S
    let E = karleksbrev::encode(S.clone());
    if !silent {
        println!("[*] S={}, encode(S)={}", S, E);
    }

    // Sanity check E
    if E.is_empty() {
        eprintln!("[X] Error: encoder gave an empty E for S={}", S);
        process::exit(1);
    }
    if E.len() > K as usize {
        eprintln!(
            "[X] Error: encoder gave too long E. length(E)={} > K={}",
            E.len(),
            K
        );
        process::exit(1);
    }
    for c in E.chars() {
        if c != '0' && c != '1' {
            eprintln!(
                "[X] Error: encoder gave E containing character '{}', which is not 0 or 1",
                c
            );
            process::exit(1);
        }
    }

    if L < 0 || R < 0 || L as usize >= E.len() || R as usize >= E.len() {
        eprintln!(
            "[X] Error: L={} or R={} is out of bounds for length(E)={}",
            L, R, E.len()
        );
        process::exit(1);
    }

    // Corrupt E by flipping bits from L to R
    let mut E = E.chars().collect::<Vec<char>>();
    for i in L as usize..=R as usize {
        E[i] = if E[i] == '0' { '1' } else { '0' };
    }
    let E = E.into_iter().collect::<String>();

    if !silent {
        println!("[*] E={} after corrupting", E);
    }

    // Check that the decoder can decode flipped E
    let decoded = karleksbrev::decode(E.clone());
    if decoded != S {
        eprintln!(
            "[X] Error: decoder did not find S. E after corrupting={}, S={}, decode(E)={}",
            E, S, decoded
        );
        process::exit(1);
    }

    if !silent {
        println!("[*] decode(E)={}", decoded);
    }

    println!("Success! N={} len(E)={}", N, E.len());
}
