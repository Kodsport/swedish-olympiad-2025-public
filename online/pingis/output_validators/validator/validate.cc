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

  int n;
  judge_in >> n;

  vi wins(n);
  rep(i,0,n) judge_in >> wins[i];

  vi cnt(2*n+1,0);

  int tempN = n;
  int num = 0;
  while (tempN > 0){
    cnt[num] += (tempN+1)/2;
    tempN /= 2;
    num++;
  }

  vi input_cnt(2*n+1,0);
  rep(i,0,n) input_cnt[min(wins[i],2*n)] += 1;

  bool possible = true;
  rep(i,0,2*n) {
    if (input_cnt[i] != cnt[i]) possible = false;
  }

  auto check = [&](istream& sol, feedback_function feedback){
    vi ans(n);
    if(!(sol >> ans[0])) feedback("Expected more output");
    string trailing;
    if(ans[0] == -1){
      if(sol >> trailing) feedback("Trailing output");
      if (ans[0] == -1 && possible)
        feedback("Answer is not -1.");
      
      if (ans[0] != -1 && !possible)
        feedback("Answer is -1.");
      return ans;
    }

    rep(i,1,n){
      if(!(sol >> ans[i])) feedback("Expected more output");
    }
    if(sol >> trailing) feedback("Trailing output");

    // Checka att listan består av en permutation av 1->N
    vi vis(n,0);
    rep(i,0,n){

      if (ans[i] <= 0 || ans[i] > n) feedback("Answer is not a permutation of 1 to N. (1)");
      ans[i]--;
      vis[ans[i]] += 1;
      
    }
    rep(i,0,n){
      if (vis[i] != 1) feedback("Answer is not a permutation of 1 to N. (2)");
    }

    // Checka att det är en valid turneringsstart.
    vi tournament(2*n,-1);

    vi tempWins(n,0);
    rep(i,0,n) tempWins[i] = wins[i];

    rep(i,0,n) tournament[i+n] = ans[i];
    for (int i = 2*n-2; i > 0; i-=2){
      if (tempWins[tournament[i]] > tempWins[tournament[i+1]])
        swap(tournament[i],tournament[i+1]);

      if (tempWins[tournament[i]] != 0) feedback("Invalid permutation. (1)");
      if (tempWins[tournament[i+1]] < 1) feedback("Invalid permutation. (2)");

      tempWins[tournament[i+1]]--;
      tournament[i/2] = tournament[i+1];

    }
    if (tempWins[tournament[1]] != 0) feedback("Invalid permutation. (3)");
    
    return ans;
  };

  vi judge_array = check(judge_ans, judge_error);
  vi author_array = check(author_out, wrong_answer);

  /*
  if (!possible){
    assert(judge_array[0] == -1 && author_array[0] == -1);

    accept();
  }
  */

  if (judge_array == author_array){
    accept_with_score(1.0);
  }

  // Kolla vilken lösning som är lexikografiskt minst

  rep(i,0,n){
    if (judge_array[i] == author_array[i]) continue;
    if (judge_array[i] > author_array[i]) judge_error("Author found a better answer than the judge.");
    if (judge_array[i] < author_array[i]) accept_with_score(0.5);
  }


}
