#include "validate.h"

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define debug(...) //ignore
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long double ld;

int main(int argc, char **argv) {
    init_io(argc, argv);
	string _SECRET_FAIL = "FAILiujwefguiwehuioew";

    string line;
    getline(author_out, line);

    string ans;
    judge_ans >> ans;

    if (line == ans)
    {
        accept();
    }
    else if (line.find(_SECRET_FAIL)==0)
    {
        line = line.substr(_SECRET_FAIL.size());
        author_message(line.c_str());
        wrong_answer(line.c_str());
    }
    else
    {
        author_message("Unexpected output. Did you write to stdout?");
        wrong_answer("Unexpected output");
    }
}
