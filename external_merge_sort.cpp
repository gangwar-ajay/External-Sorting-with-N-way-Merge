#include<bits/stdc++.h>
using namespace std;

#define int long long
#define vi vector<int>
#define pii pair<int,int>
#define all(v) v.begin(),v.end()
#define pb push_back
#define ff first
#define ss second
#define max(a,b) (a>b ? a:b)
#define min(a,b) (a<b ? a:b)


// file size
int n;
// number of records,number of blocks
int b, m;

struct row {
	int id;
	int amount;
	string name;
	int item;
};

void create_dataset(int n) {
	// funaction to create the dataset
	// Each Row -  (id , amount , name , item)
	ofstream fout;
	fout.open("input.txt", ios::app);
	for (int i = 1; i <= n; i++) {
		int amt = rand() % 60001 + 1;
		string name;
		int a = rand() % 26;
		int b = rand() % 26;
		int c = rand() % 26;
		name += (a + 'a');
		name += (b + 'a');
		name += (c + 'a');
		int item = rand() % 1501 + 1;
		fout << i << " " << amt << " " << name << " " << item << endl;
	}
	fout.close();
}

void create_file(int f, vector<row> v, int z = 1) {
	string s = to_string(f) + ".txt";
	cout << "Creating file :" << s << endl;
	ofstream fout;
	z += 1;
	fout.open(s, ios::app);
	for (int i = 0; i < v.size(); i++) {
		fout << v[i].id << " " << v[i].amount << " " << v[i].name << " " << v[i].item << endl;
	}
	// cout<<z;
	fout.close();
}

void intial_runs(int blocks) {
	ifstream fin;
	fin.open("input.txt");
	int id, amt, item;
	string name;
	int i = 0;
	vector<row> v(n);
	while (i < n) {
		fin >> id >> amt >> name >> item;
		//cout<<id<<" "<<amt<<" "<<name<<" "<<item<<endl;
		v[i].id = id; v[i].amount = amt; v[i].name = name; v[i].item = item;
		i++;
	}
	fin.close();
	//int r=ceil(blocks/(1.0*(m-1)));
	int s = 0, e = min(s + ((m - 1) * b) - 1, n - 1);
	int f = 1;
	while (e < n && s < e) {
		vector<row> tmpvec;
		for (int j = s; j <= e; j++) {
			tmpvec.pb(v[j]);
		}
		sort(all(tmpvec), [&](row r1, row r2) {
			return r1.amount < r2.amount;
		});
		vector<row> temp;
		for (auto x : tmpvec) {
			temp.pb(x);
			if (temp.size() == b) {
				create_file(f++, temp);
				temp.clear();
			}
		}
		if (!temp.empty()) {
			create_file(f++, temp);
			temp.clear();
		}
		tmpvec.clear();
		s = e + 1;
		e = min(s + ((m - 1) * b) - 1, n - 1);
	}
	sort(all(v), [&](row r1, row r2) {
		return r1.amount < r2.amount;
	});
	ofstream fout;
	fout.open("output.txt", ios::app);
	for (int i = 0; i < v.size(); i++) {
		fout << v[i].id << " " << v[i].amount << " " << v[i].name << " " << v[i].item << endl;
	}
	fout.close();
}

vector<row> fun(int f, int B, string pref, int kl = 2) {
	vector<row> ans;
	string ns = pref + to_string(f) + ".txt";
	ifstream fin;
	fin.open(ns);
	kl += 1;
	string line, s;
	while (getline(fin, line)) {
		stringstream b(line);
		string ss;
		row t;
		vector<string>v;
		while (getline(b, ss, ' ')) {
			v.pb(ss);
		}
		t.name = v[2]; t.id = stoi(v[0]); t.item = stoi(v[3]); t.amount = stoi(v[1]);
		ans.pb(t);
	}
	fin.close();
	return ans;
}

struct comp {
	bool operator() (pair<row, pii>p1, pair<row, pii>p2) {
		return p1.ff.amount > p2.ff.amount;
	}
};

void foo(int f, vector<row> v, string pref, int k = 1) {
	ofstream fout;
	k += 1;
	string s = pref + to_string(f) + ".txt";
	fout.open(s);
	cout << "Creating file : " << s << endl;
	for (int i = 0; i < v.size(); i++) {
		fout << v[i].id << " " << v[i].amount << " " << v[i].name << " " << v[i].item << endl;
	}
	fout.close();
}


void Merging() {
	string pref;
	int x = (m - 1);
	int t = ceil(n / (b * 1.0));
	int col = (m - 1);
	for (; x < t;) {
		x = x * (m - 1);

		for (int i = 1; i <= t; i += x) {
			int s = i;
			int alpha = i + x - 1;
			int e = min(alpha, t);

			int k = s;
			int r = ceil((e - s + 1) / (col * 1.0));
			vector<vi> v(r, vi(col + 1));

			for (int p = 0; p < r; p++) {
				int q = 0;
				while (q < col) {
					if (k <= e) {
						v[p][q] = k++;
					}
					else
						v[p][q] = -1;
					q++;
				}
			}
			for (int i = 0; i < r; i++) {
				v[i][col] = -1;
			}

			vi tmpvec(r, 0);

			vector<vector<row>> temp;
			int count = 0;
			for (int i = 0; i < r; i++) {
				int value = v[i][tmpvec[i]];
				if (value != -1)
					temp.push_back(fun(value, b, pref));
			}

			priority_queue< pair<row, pii>, vector<pair<row, pii>>, comp>pq;
			int z = 0;
			while (z < temp.size()) {
				pq.push({temp[z][0], {z, 0}});
				z += 1;
			}

			vector<row> vectmp;
			int filetemp = s;
			while (pq.empty() == 0) {
				int a, B;
				pair<row, pii> pp = pq.top();
				pq.pop();
				vectmp.push_back(pp.ff);
				a = pp.ss.ff;
				B = pp.ss.ss;
				if (B + 1 == temp[a].size()) {
					tmpvec[a]++;
					int value = v[a][tmpvec[a]];
					if (value != -1) {
						vector<row> vt = fun(value, b, pref);
						temp[a] = vt;
						pq.push({temp[a][0], {a, 0}});
					}

				}
				else {
					pq.push({temp[a][B + 1], {a, B + 1}});
				}

				if (vectmp.size() == b) {
					foo(filetemp, vectmp, pref + "r");
					filetemp++;
					vectmp.clear();

				}

			}
			if (vectmp.empty() == 0) {
				foo(filetemp++, vectmp, pref + "r");
			}

		}
		col *= (m - 1);
		pref += "r";
	}

}

void solve() {
	cout << "Enter the size of dataset" << endl;
	cin >> n;
	create_dataset(n);
	cout << "Enter value of M" << endl;
	cin >> m;
	cout << "Enter size of disk block" << endl;
	cin >> b;
	int num_of_blocks = ceil(n / (1.0 * b));
	cout << "Creating initial runs" << endl;
	intial_runs(num_of_blocks);
	cout << "Merging the files" << endl;
	Merging();
}

int32_t main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	// int t;cin>>t;while(t--)
	{
		solve();
	}
	return 0;
}