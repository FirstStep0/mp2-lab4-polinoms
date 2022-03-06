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
/*double get_double(string& buffer) {
	bool was_point = false;
	int j;
	string co;
	for (j = 0; (j < buffer.size()) && (('0' <= buffer[j] && buffer[j] <= '9') || buffer[j] == '.'); j++) {
		if (buffer[j] == '.') {
			if (was_point) {
				//print_slash(j, "incorrect_input");
				throw error(j, "incorrect_input");
				//return;
			}
			was_point = true;
		}
		co += buffer[j];
	}
	buffer = buffer.substr(j, buffer.size() - j);

	return co.size() ? parseToDouble(co) : 1.0;
}*/
struct error {
	uint pos;
	string message;
	error(uint pos, string message) :pos(pos), message(message) {};
};

void print_slash(int pos, string message) {
	for (int k = 0; k < pos; k++) {
		cout << " ";
	}
	cout << "^\n";
	if (message.size())
		cout << message << "\n";
}

unsigned int parseToUInt(const string& str) {
	uint res = 0;
	for (int i = 0; i < str.size(); i++) {
		if (!('0' <= str[i] && str[i] <= '9'))throw string("error: ParseToUInt()");
		res *= 10;
		res += (str[i] - '0');
	}
	return res;
}

void SetPolinom(polinom& p) {
	polinom test;
	cout << "Example input: -2.0x3y-2z2+4.5xy2z\n";
	cout << "the order of variables and monom can be any\n";
	cout << "Input monom:\n";
	string str;
	getline(cin, str);
	str += '+';
	string temp = "";
	bool minus = false;
	for (int i = 0; i < str.size(); i++) {
		char& ch = str[i];
		if (ch == '+' || ch == '-') {
			bool current_minus = minus;
			minus = (ch == '-') ? true : false;
			if (temp.size() > 0) {
				bool was_point = false;
				int j = 0;
				string co = "";
				double coef = 1.0;
				temp += '#';
				for (; (j < temp.size()) && (('0' <= temp[j] && temp[j] <= '9') || temp[j] == '.'); j++) {
					if (temp[j] == '.') {
						if (was_point) {
							throw error(i - temp.size() + j + 1, "many dots");
						}
						was_point = true;
					}
					co += temp[j];
				}
				if (co.size()) coef = parseToDouble(co);

				uint u, x, y, z;
				string str_u = "";
				x = y = z = 0;
				char type_deg = 0;
				for (; j < temp.size(); j++) {
					if (('0' <= temp[j] && temp[j] <= '9')) {
						str_u += temp[j];
					}
					else {
						if (!str_u.empty())u = parseToUInt(str_u);
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
						u = 1;
						str_u = "";

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
							throw error(i - temp.size() + j + 1, "incorrect_input");
							return;
						}
						}
					}
				}
				if (current_minus)coef = -coef;
				test += monom(coef, x, y, z);
				temp = "";
			}
		}
		else {
			if (ch != ' ')
			temp += ch;
		}
	}
	p = test;
}

void Initialize() {
	f += monom(5, 1, 0, 0);
	s += monom(-2, 0, 2, 3);
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
		cout << " " << f << "\n";
		cout << "2. Set second polinom\n";
		cout << " " << s << "\n";
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
		catch (error e) {
			print_slash(e.pos, e.message);
		}
		catch(...){
			cout << "undefined error\n";
		}
		system("pause");
	}
}
