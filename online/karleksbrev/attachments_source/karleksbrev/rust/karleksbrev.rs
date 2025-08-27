pub fn encode(S: String) -> String {
    let mut E = String::new();
    for c in S.chars() {
        E.push_str(&c.to_string().repeat(5));
    }
    E
}

// Note: this E is E after it has been corrupted
pub fn decode(E: String) -> String {
    let mut ret = String::new();
    let mut chars = E.chars();
    while let Some(chunk) = chars.by_ref().take(5).collect::<String>().chars().nth(2) {
        ret.push(chunk);
    }
    
    ret
}
