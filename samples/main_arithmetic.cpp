// реализация пользовательского приложения
#include <iostream>
#include <string>
#include "arithmetic.h"
using namespace std;
typedef unsigned int uint;
const int Exit = 10;
polinom f, s;

double parseToDouble(const string& str) {
	double res = 0.0;
	double pos = str.size();
	if (str.size() == 0)throw string("parseToDouble(): empty str");
	for (int i = 0; i < str.size(); i++)if (!(('0' <= str[i] && str[i] <= '9') || (str[i] == '.')))throw string("parseToDouble(): incorrect str");

	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '.') {
			pos = i + 1;
		}
		else {
			res *= 10.0;
			res += (str[i] - '0');
		}
	}
	return res / pow(10.0, str.size() - pos);
}

void print_slash(int n) {
	for (int k = 0; k < n; k++) {
		cout << " ";
	}
	cout << "^";
}

void SetPolinom(polinom& p) {
	polinom test;
	cout << "Example input: 2.0x3y4+2z2+4.5x1y1z1\n";
	cout << "Input monom:\n";
	string str;
	getline(cin, str);
	str += '+';
	//cout << str;
	string temp = "";
	for (int i = 0; i < str.size(); i++) {
		char& ch = str[i];
		if (ch == '+') {
			int j = 0;
			string co = "";
			double coef = 1.0;
			bool was_point = false;
			while ((j < temp.size()) && (('0' <= temp[j] && temp[j] <= '9') || temp[j] == '.')) {
				
				if (temp[j] == '.') { 
					if (was_point) {
						print_slash(i - temp.size() + j);
						cout << "\n" << "incorrect_input\n";
						return;
					}
					was_point = true;
				}
				co += temp[j];
				j++;
			}
			if (co.size()) coef = parseToDouble(co);

			temp += '#';
			uint u, x, y, z;
			u = x = y = z = 0;
			char type_deg = 0;
			while (j < temp.size()) {
				if (('0' <= temp[j] && temp[j] <= '9')) {
					u *= 10;
					u += (temp[j] - '0');
				}
				else {
					switch (type_deg) {
					case 'x': {
						x = u;
						break;
					}
					case 'y': {
						y = u;
						break;
					}
					case 'z': {
						z = u;
						break;
					}
					}
					u = 0;

					switch (temp[j]) {
					case 'x': {
						type_deg = 'x';
						break;
					}
					case 'y': {
						type_deg = 'y';
						break;
					}
					case 'z': {
						type_deg = 'z';
						break;
					}
					case '#': {
						break;
					}
					default: {
						print_slash(i - temp.size() + j + 1);
						cout << "\n";
						cout << "incorrect_input\n";
						return;
					}
					}
				}
				j++;
			}
			test += monom(coef, x, y, z);
			temp = "";
		}
		else {
			temp += ch;
		}
	}
	p = test;
}

void Initialize() {
	f += monom(5, 1);
	s += monom(2, 3);
}

int main()
{
	Initialize();
	cout.precision(10);
	int code = 0;
	while (code != Exit) {
		system("cls");
		cout << "+---------------------------------+\n";
		cout << "|program for working with polinoms|\n";
		cout << "+---------------------------------+\n";
		cout << "[command for polinoms]\n";
		cout << "1. Set first polinom\n";
		cout << "first: " << f << "\n";
		cout << "2. Set second polinom\n";
		cout << "second: " << s << "\n";
		cout << "[arithmetic operations]\n";
		cout << "3. Add\n";
		cout << "4. Sub\n";
		cout << "5. Multiply\n";
		cout << "\n";
		cout << "10. Exit\n";
		cout << ">";
		cin >> code;
		cin.clear();
		cin.ignore(10000, '\n');
		try {
			switch (code) {
			case 1: {
				SetPolinom(f);
				break;
			}
			case 2: {
				SetPolinom(s);
				break;
			}
			case 3: {
				polinom r = f + s;
				cout << r << "\n";
				break;
			}
			case 4: {
				polinom r = f - s;
				cout << r << "\n";
				break;
			}
			case 5: {
				polinom r = f * s;
				cout << r << "\n";
				break;
			}
			case 10: {
				break;
			}
			default: {
				cout << "command not found\n";
			}
			}
		}
		catch (string s) {
			cout << s << "\n";
		}
		catch(...){
			cout << "undefined error\n";
		}
		system("pause");
	}
}
