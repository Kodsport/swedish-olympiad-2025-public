#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "karleksbrev.h"

using namespace std;


namespace {
	static const int USER_FAIL = 120;
	const int num_testcases = 50;
	string _SECRET_KEY = "SUCCESSiujwefguiwehuioew";
	string _SECRET_FAIL = "FAILiujwefguiwehuioew";
    unsigned long long rng_state;
    unsigned long long next_rand()
    {
        rng_state ^= (rng_state << 21);
        rng_state ^= (rng_state >> 35);
        rng_state ^= (rng_state << 4);
        rng_state *= 2685821657736338717ULL;
        return rng_state;
    }
    unsigned long long rand_interval(unsigned long long l, unsigned long long r) {
        unsigned long long range = r - l + 1;
        return l + (next_rand() % range);
    }
}

template <typename T>
void permute_vector(std::vector<T>& vec) {
    for (size_t i = vec.size() - 1; i > 0; --i) {
        size_t j = rand_interval(0, i);
        std::swap(vec[i], vec[j]);
    }
}

int main() {
	ios_base::sync_with_stdio(false);
	int n, k;
	cin >> n >> k;
	int test_type, seed;
	cin >> test_type >> seed;
	rng_state = seed;

	int pipefds[2];
	ignore = pipe(pipefds);

	auto get_lr = [test_type](int elen)
	{
		// Random
		if (test_type == 0)
		{
			int l = rand_interval(0, elen-1);
			int r = rand_interval(l, elen-1);
			return make_pair(l,r);
		}
		if (test_type == 1)
		{
			int l = rand_interval(0, elen-1);
			return make_pair(l,l);
		}
		if (test_type == 2)
		{
			int l,r;
			while ((l=rand_interval(0,elen-3))%2) {}
			while ((r=rand_interval(l,elen-1))%2) {}
			return make_pair(l,r);
		}
		if (test_type == 3)
		{
			int l,r;
			while ((l=rand_interval(0,elen-1))%2) {}
			r = rand_interval(l, elen-1);
			return make_pair(l,r);
		}
	};

	pid_t pid = fork();
	if (pid == 0) {
		close(pipefds[0]);

		// {S, E}
		vector<pair<string,string>> testcases;

		for (int i = 0; i < num_testcases; i++)
		{
			string s;
			for (int j = 0; j < n; j++) s += (rand_interval(0, 1) ? "1" : "0");
			string encoded = encode(s);

			if (encoded.size() == 0)
			{
				cout << _SECRET_FAIL << "Encoder gave empty E" << endl;
				close(pipefds[1]);
				exit(USER_FAIL);
			}

			if (encoded.size() > (size_t)k) {
				cout << _SECRET_FAIL << "Encoder gave too long E" << endl;
				close(pipefds[1]);
				exit(USER_FAIL);
			}

			for (char c : encoded) {
				if (c != '0' && c != '1') {
					cout << _SECRET_FAIL << "Encoder gave E containing character which is not 0 or 1" << endl;
					close(pipefds[1]);
					exit(USER_FAIL);
				}
			}

			int l,r;
			tie(l, r) = get_lr(encoded.size());
			// flip the interval
			for (int i = l; i <= r; i++)
			{
				if (encoded[i]=='1') encoded[i]='0';
				else encoded[i]='1';
			}
			testcases.emplace_back(s, encoded);
		}

		char nullbyte[1];
		nullbyte[0]=0;
		char dollar[1];
		dollar[0]='$';
		for (auto [s, e] : testcases)
		{
			ignore = write(pipefds[1], s.c_str(), s.size());
			ignore = write(pipefds[1], dollar, 1);
			ignore = write(pipefds[1], e.c_str(), e.size());
			ignore = write(pipefds[1], dollar, 1);
		}
		
		ignore = write(pipefds[1], nullbyte, 1);
		
		close(pipefds[1]);
		exit(EXIT_SUCCESS);
	}
	else {
		int status;
		char buf[50000];
		if (waitpid(pid, &status, 0) == -1) {
			perror("waitpid fail");
			return EXIT_FAILURE;
		}
		if (WIFSIGNALED(status)) {
			kill(getpid(), WTERMSIG(status));
			exit(1);
		}
		int ex = WEXITSTATUS(status);
		if (ex == USER_FAIL) { exit(0); }
		if (ex != EXIT_SUCCESS) { exit(ex); }
		ignore = read(pipefds[0], buf, sizeof(buf));

		// {S,E}
		vector<pair<string,string>> testcases;
		
		string curr_string = "";
		bool s_curr = 1;
		for (int i = 0; i < 50000; i++)
		{
			if (buf[i] == 0) break;
			if (buf[i]=='$')
			{
				if (s_curr)
				{
					testcases.push_back(make_pair("",""));
					testcases.back().first = curr_string;
				}
				else testcases.back().second = curr_string;
				s_curr ^= 1;
				curr_string = "";
			}
			else
			{
				curr_string += buf[i];
			}
		}

		permute_vector(testcases);

		unsigned long long h = 0;
		for (auto [S,E] : testcases)
		{
			for (auto c : S) h = (h+c-'0')*31;
			for (auto c : E) h = (h+c-'0')*31;

			string decoded = decode(E);

			if (decoded!=S)
			{
				cout << _SECRET_FAIL << "Decoder did not find S" << endl;
				close(pipefds[1]);
				exit(0);
			}
		}
		cerr << "Hash of run: " << h << endl;

		cout << _SECRET_KEY << seed << endl;
		exit(EXIT_SUCCESS);
	}

}
