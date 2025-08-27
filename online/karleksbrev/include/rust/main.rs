use std::process;
use std::env;
use std::collections::VecDeque;
use std::io::{self, Write, Read, BufReader};
use std::process::{Command, Stdio};
use std::sync::{Arc, Mutex};

mod karleksbrev;


static mut _RNG_STATE: u64 = 0;

fn next_rand() -> u64 {
    unsafe {
        _RNG_STATE ^= _RNG_STATE << 21;
        _RNG_STATE ^= _RNG_STATE >> 35;
        _RNG_STATE ^= _RNG_STATE << 4;
        _RNG_STATE *= 2685821657736338717;
        _RNG_STATE
    }
}

fn rand_interval(l: u64, r: u64) -> u64 {
    let range = r - l + 1;
    l + (next_rand() % range)
}

fn permute_vector<T>(vec: &mut Vec<T>) {
    for i in (1..vec.len()).rev() {
        let j = rand_interval(0, i as u64) as usize;
        vec.swap(i, j);
    }
}

fn get_lr(test_type: u32, elen: usize) -> (usize, usize) {
    match test_type {
        0 => {
            let l = rand_interval(0, (elen - 1) as u64) as usize;
            let r = rand_interval(l as u64, (elen - 1) as u64) as usize;
            (l, r)
        }
        1 => {
            let l = rand_interval(0, (elen - 1) as u64) as usize;
            (l, l)
        }
        2 => {
            let mut l;
            let mut r;
            loop {
                l = rand_interval(0, (elen - 3) as u64) as usize;
                if l % 2 == 0 {
                    break;
                }
            }
            loop {
                r = rand_interval(l as u64, (elen - 1) as u64) as usize;
                if r % 2 == 0 {
                    break;
                }
            }
            (l, r)
        }
        3 => {
            let mut l;
            let r;
            loop {
                l = rand_interval(0, (elen - 1) as u64) as usize;
                if l % 2 == 0 {
                    break;
                }
            }
            r = rand_interval(l as u64, (elen - 1) as u64) as usize;
            (l, r)
        }
        _ => panic!("Invalid test_type"),
    }
}

fn main() -> io::Result<()> {
    
    const _USER_FAIL: i32 = 120;
    const _NUM_TESTCASES: usize = 50;
    static _SECRET_KEY: &str = "SUCCESSiujwefguiwehuioew";
    static _SECRET_FAIL: &str = "FAILiujwefguiwehuioew";

    let args: Vec<String> = env::args().collect();

    if args.len() == 2 {
        let mut input = String::new();
        io::stdin().read_line(&mut input).expect("Failed to read line");
        let mut iter = input.split_whitespace();
        let n: u32 = iter.next().unwrap().parse().expect("Invalid number");
        let k: u32 = iter.next().unwrap().parse().expect("Invalid number");
        
        // Reading test_type and seed
        input.clear();
        io::stdin().read_line(&mut input).expect("Failed to read line");
        
        let mut iter = input.split_whitespace();
        let test_type: u32 = iter.next().unwrap().parse().expect("Invalid number");
        let seed: u32 = iter.next().unwrap().parse().expect("Invalid number");
        unsafe { _RNG_STATE = u64::from(seed) };        
        
        // Generate test cases
        let mut testcases = Vec::new();
        for _ in 0.._NUM_TESTCASES {
            let mut s = String::new();
            for _ in 0..n {
                s.push(if rand_interval(0, 1) == 1 { '1' } else { '0' });
            }

            let encoded = karleksbrev::encode(s.clone());
            if encoded.is_empty() {
                println!("{}Encoder gave empty E", _SECRET_FAIL);
                process::exit(_USER_FAIL);
            }
            if encoded.len() > k as usize {
                println!("{}Encoder gave too long E", _SECRET_FAIL);
                process::exit(_USER_FAIL);
            }

            if encoded.chars().any(|c| c != '0' && c != '1') {
                println!("{}Encoder gave E containing non-binary character", _SECRET_FAIL);
                process::exit(_USER_FAIL);
            }

            let (l, r) = get_lr(test_type, encoded.len());
            let mut encoded_vec: Vec<char> = encoded.chars().collect();
            for i in l..=r {
                encoded_vec[i] = if encoded_vec[i] == '1' { '0' } else { '1' };
            }

            let new_encoded: String = encoded_vec.iter().collect();
            testcases.push((s, new_encoded));
        }

        for (S, E) in &testcases {
            println!("{}${}", S, E);
        }
    }    
    else {
        let mut input = String::new();
        io::stdin().read_line(&mut input).expect("Failed to read line");
        let mut iter = input.split_whitespace();
        let n: u32 = iter.next().unwrap().parse().expect("Invalid number");
        let k: u32 = iter.next().unwrap().parse().expect("Invalid number");
        
        // Reading test_type and seed
        input.clear();
        io::stdin().read_line(&mut input).expect("Failed to read line");
        
        let mut iter = input.split_whitespace();
        let test_type: u32 = iter.next().unwrap().parse().expect("Invalid number");
        let seed: u32 = iter.next().unwrap().parse().expect("Invalid number");
        unsafe { _RNG_STATE = u64::from(seed) };

        let exe_path = env::current_exe().expect("Failed to get current executable path");
        
        let encoder_arg = "encoder"; // The command line argument you want to add
        //Forking equivalent in Rust
        let mut child = Command::new(exe_path) // Replace with appropriate executable
            .arg(encoder_arg) // Add the "encoder" argument
            .stdin(Stdio::piped())
            .stdout(Stdio::piped())
            .spawn()?;

        if let Some(mut stdin) = child.stdin.take() {
            // Format the numbers and write them to stdin
            writeln!(stdin, "{} {}", n, k)?;
            writeln!(stdin, "{} {}", test_type, seed)?;
        }

        let mut output = String::new();
        // Read from the stdout stream
        if let Some(stdout) = child.stdout.take() {
            let mut reader = BufReader::new(stdout);
            
            reader.read_to_string(&mut output)?;

        }

        let status = child.wait()?;
        if !status.success() {
            println!("{}", output);
            if let Some(code) = status.code() {
                if code == _USER_FAIL { // Example condition: check for specific exit code (e.g., user fail)
                    process::exit(0);
                } else {
                    process::exit(code);
                }
            } else {
                // If status code is not available (e.g., signal termination), exit with failure
                process::exit(1);
            }
        }

        let mut testcases: Vec<(String, String)> = output
            .lines()                           // Split by newlines
            .map(|line| {
                let parts: Vec<&str> = line.split('$').collect(); // Split each line by `$`
                (parts[0].to_string(), parts[1].to_string())      // Convert to tuple of Strings
            })
            .collect();
        
        permute_vector(&mut testcases);

        // Print the resulting list of pairs
        let mut h: u64 = 0; 
        for (S, E) in &testcases {
            // Update hash for characters in S
            for c in S.chars() {
                h = (h + c as u64 - '0' as u64) * 31;
            }
    
            // Update hash for characters in E
            for c in E.chars() {
                h = (h + c as u64 - '0' as u64) * 31;
            }
    
            // Assume decode is defined
            let decoded = karleksbrev::decode(E.clone());
    
            if decoded != *S {
                println!("{}Decoder did not find S", _SECRET_FAIL);
                process::exit(0);
            }
        }
    
        eprintln!("Hash of run: {}", h);

        println!("{}{}", _SECRET_KEY, seed);

    }

    Ok(())
}
