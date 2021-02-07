#include <fstream>
#include <string>
#include <vector>
using namespace std;

fstream cin("inp.txt");
ofstream cout("out.txt");

char UP(char a) {
	if ('a' <= a && a <= 'z') a -= 32;
	return a;
}

bool Equal(string& fir, string& sec) {
	for (int i = 0; i < fir.size(); i++)
		if (UP(fir[i]) != UP(sec[i])) return false;
	return true;
}

bool NotLetter(char a) {
	return !('A' <= UP(a) && UP(a) <= 'Z');
}

bool Check(string& s, string& t) {
	bool key = false;
	for (int i = 0; i < s.length() - t.length() + 1; i++) {
		if ((!i || s[i - 1] == ' ') && (i + t.length() == s.length() || NotLetter(s[i + t.length()])) && Equal(t, s.substr(i, t.length()))) {
			key = true;
			for (int j = 0; j < t.length(); j++)
				s[i + j] = UP(s[i + j]);
		}
	}
	return key;
}

void Search(vector <string>& List, string& t, vector <int>& num) {
	for (int i = 0; i < List.size(); i++)
		if (Check(List[i], t)) num.push_back(i);
}

vector <string> SplitToSentences(string& s) {
	vector <string> cur;
	int pos = 0, pos2 = 0;
	while (pos < s.length()) {
		while (pos2 < s.length() && s[pos2] != '.') pos2++;
		cur.push_back(s.substr(pos, pos2 - pos + 1));
		pos = pos2 + 1;
		while (pos < s.length() && s[pos] == ' ') pos++;
		pos2 = pos;
	}
	return cur;
}

int main() {

	string s; getline(cin, s);
	vector <string> sent = SplitToSentences(s);

	int n; cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> s;
		vector <int> num;
		Search(sent, s, num);
		cout << num.size() << endl;
		for (int j = 0; j < num.size(); j++)
			cout << sent[num[j]] << endl;
	}
}
