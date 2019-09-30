#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
const char *r[] = { "EKMFLGDQVZNTOWYHXUSPAIBRCJ", "AJDKSIRUXBLHWTMCQGZNPYFVOE", "BDFHJLCPRTXVZNYEIWGAKMUSQO", "ESOVPZJAYQUIRHXLNFTGKDCMWB", "VZBRGITYUPSDNHLXAWMJQOFECK" };//rotor
const char *refl = "YRUHQSLDPXNGOKMIEBFZCWVJAT";//reflector
char p[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";//plugboard
char start[3];
const char *arrow = "RFWAK";
const char *abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";//map
int times[3] = { 0 };
int cycle[3] = { 0 };
char map[3][26];
char rotor[3][26];
int RotorNum[3];
string inputString = "ZATVAWORBRQGRJSXZVNORWZBLORMEGRASLQLAFWXZYODVVTDHCIRDMNWOPNIXVKASIIIALOOSZXAMSYCQHYGPRLMSACGAWPCPAVZTMUUZCTJDVBUZAGFWMIVEZGBTLFIQDPPRZHDNKIPQHUGCXZM";
bool finded = false;

void spin(int n) {
	char t1 = rotor[n][0];
	char t2 = map[n][0];
	for (int i = 1; i <= 25; i++) {
		rotor[n][i - 1] = rotor[n][i];
		map[n][i - 1] = map[n][i];
	}
	rotor[n][25] = t1;
	map[n][25] = t2;
}

int find(const char f[], char c) {
	int n = 0;
	for (int i = 0; i < 26; i++) {
		if (f[i] == c)
			n = i;
	}
	return n;
}

char encode(char input) {
	int c = find(rotor[0], map[0][find(rotor[1], map[1][find(rotor[2], map[2][find(abc, refl[find(map[2], rotor[2][find(map[1], rotor[1][find(map[0], rotor[0][find(abc, p[input - 'A'])])])])])])])]);
	return abc[find(p, abc[c])];
}
/*
plug:
ABCDEFGHIJKLMNOPQRSTUVWXYZ
ABCDEFGHIJKLMNOPQRSTUVWXYZ

R1 :
YZABCDEFGHIJKLMNOPQRSJUVWX
QOBDFHJLCPRTXVZNYEIWGAKMUS

R2 :
DEFGHIJKLMNOPQRSJUVWXYZABC
KSIRUXBLHWTMCQGZNPYFVOEAJD

R3 :
HIJKLMNOPQRSJUVWXYZABCDEFG
QVZNTOWYHXUSPAIBRCJEKMFLGD

RF :
ABCDEFGHIJKLMNOPQRSTUVWXYZ
YRUHQSLDPXNGOKMIEBFZCWVJAT
*/
void runEnigma();
int main() {
	RotorNum[0] = 0;
	do{
		int bol = 0;
		int bol2 = 0;
		for (int i = 25; i >= 0; i--){
			if ((abc[i] != p[find(abc, p[i])]) || (p[i] != abc[find(p, abc[i])])){
				bol++;
				break;
			}
			if (p[i] == abc[i])
				bol2++;
		}

		if (bol > 0)
			continue;
		if (bol2 < 14)
			continue;

		for (int j = 1; j < 5; j++) {
			RotorNum[1] = j;
			for (int k = 1; k < 5; k++) {
				if (j != k) {
					RotorNum[2] = k;
					for (int i = 0; i < 26; i++) {
						start[0] = abc[i];
						for (int a = 0; a < 26; a++) {
							start[1] = abc[a];
							for (int b = 0; b < 26; b++) {
								start[2] = abc[b];
								runEnigma();
								if (finded) {
									cout << "find!\n";
									for (int d = 0; d < 3; d++)
										cout << "rotor" << d + 1 << ":" << RotorNum[d] + 1 << endl;
									for (int d = 0; d < 3; d++)
										cout << "start" << d + 1 << ":" << start[d] << endl;
									for (int d = 0; d < 26; d++)
										cout << p[d];
									cout << endl;
									system("pause");
								}
							}
						}
					}
				}
			}
		}
	} while (next_permutation(p, p + 26)&&(finded == 0));
	if (!finded) {
		cout << "Fail!!!!!!!" << endl;
	}
	system("pause");
}

void runEnigma() {
	for (int i = 0; i < 3; i++) {
		times[i] = 0;
		cycle[i] = 0;
		for (int j = 0; j < 26; j++) {
			map[i][j] = '\0';
			rotor[i][j] = '\0';
		}
	}

	for (int i = 0; i < 3; i++) {
		int shift = (start[i] - 'A') % 26;
		for (int j = 0; j < 26; j++) {
			map[i][j] = (start[i] - 'A' + j) % 26 + 'A';
		}
		for (int j = 0; j < 26; j++) {
			rotor[i][j] = r[RotorNum[i]][(j + shift) % 26];
		}
	}
	for (int i = 0; i < 2; i++) {
		if (arrow[RotorNum[i]] <= start[i]) {
			cycle[i] = arrow[RotorNum[i]] - start[i] + 26;
		}
		else
			cycle[i] = -(start[i] - arrow[RotorNum[i]]);
		if (cycle[i] == 26)
			cycle[i] = 0;
	}

	char temp;
	if (start[1] == 'Z')
		temp = 'A';
	else
		temp = start[1] + 1;

	if (arrow[RotorNum[1]] <= temp)
		cycle[2] = arrow[RotorNum[1]] - temp + 26;

	else
		cycle[2] = -(temp - arrow[RotorNum[1]]);


	if (cycle[2] == 26) {
		cycle[2] = 0;
	}

	if (cycle[1] == 1) {
		spin(1);
		times[1]++;
		spin(2);
	}

	//cout << "The string that you want to encrypted: ";
	string ans = "";

	char input;
	for (size_t i = 0; i < inputString.length(); i++) {
		input = inputString[i];
		times[0]++;
		spin(0);
		if (times[0] % 26 == cycle[0]) {
			times[1]++;
			spin(1);
			if (times[1] % 26 == cycle[1]) {
				spin(2);
			}
		}
		if (i >= 138)
			ans += encode(input);

		if (((times[1] % 26) == cycle[2]) && (times[1] != 0)) {
			times[1]++;
			spin(1);
			if (times[1] % 26 == cycle[1]) {
				spin(2);
			}
		}
	}
	if (ans == "HEILHITLER") {
		finded = true;
		cout << ans << endl;
	}
}