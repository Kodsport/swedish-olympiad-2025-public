
const MOD: u64 = 1125899906842679;
const K: usize = 50;

fn hashf(x: &String) -> u64 {
    let mut ret = 0u64;
    for v in x.chars() {
        ret = (ret + if v == '1' { 1 } else { 0 }) * 2374662 % MOD;
    }
    ret
}

fn hashstring(x: &String) -> String {
    let mut ret = vec!['0'; K];
    let h = hashf(x);

    for j in 0..K {
        if h & (1 << j) != 0 {
            ret[j] = '1';
        }
    }
    
    ret.iter().collect()
}

pub fn encode(x: String) -> String {
    format!("{}{}", x, hashstring(&x))
}

pub fn decode(x: String) -> String {
    let n = x.len();
    let mut u: Vec<char> = x.chars().collect();

    for i in 0..n {
        for j in i..n {
            // Toggle bits between i and j
            for l in i..=j {
                u[l] = if u[l] == '1' { '0' } else { '1' };
            }
            
            // Extract the meat (original message without hash part)
            let meat: String = u.iter().take(n - K).collect();
            let encoded = encode(meat.clone());

            // Check if toggled string matches encoded form
            if u.iter().collect::<String>() == encoded {
                return meat;
            }
            
            // Undo the toggle to restore the original state for the next iteration
            for l in i..=j {
                u[l] = if u[l] == '1' { '0' } else { '1' };
            }
        }
    }
    
    panic!("its joever");
}
