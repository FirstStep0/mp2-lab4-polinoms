#include <iostream>
#include "stack.h"
#include <cstdint>
typedef unsigned char uchar;
typedef float type_coef;

const int base = 256;
const double eps = 0.000001;

class monom {
public:
	int32_t index;
	type_coef coef;
	monom() :monom(0, 0) {};
	monom(const monom& m) :monom(m.coef, m.index) {};
	monom(type_coef coef, int32_t x, int32_t y, int32_t z) :coef(coef) {
		SetIndex(x, y, z);
	};
	monom(type_coef coef, int32_t index = 0) :coef(coef), index(index) {}
	int32_t degx() { return (uchar)(index >> 16); }
	int32_t degy() { return (uchar)(index >> 8); }
	int32_t degz() { return (uchar)(index); }
	void SetIndex(int32_t degx, int32_t degy, int32_t degz) {
		index = DegToIndex(over(degx, 0), over(degy, 0), over(degz, 0));
	}
	friend bool operator<(const monom& a, const monom& b) {
		return (a.index < b.index) || ((a.index == b.index) && (a.coef < b.coef));
	}
	friend bool operator>(const monom& a, const monom& b) {
		return (a.index > b.index) || ((a.index == b.index) && (a.coef > b.coef));
	}
	friend bool operator==(const monom& a, const monom& b) { return(a.index == b.index); };
	friend bool operator!=(const monom& a, const monom& b) { return(a.index != b.index); };
	monom& operator*=(const type_coef& coef) {
		this->coef *= coef;
		return *this;
	}
	monom& operator*=(const monom& m) {
		this->coef *= m.coef;
		monom* _m = const_cast<monom*>(&m);
		index = sumoverflow(*this, *_m);
		return *this;
	}
	friend monom operator*(const monom& a, const monom& b) {
		monom r = a;
		r *= b;
		return r;
	}
	monom& operator+=(const monom& m) {
		if (this->index == m.index) {
			this->coef += m.coef;
			return *this;
		}
		throw string("operator+= can't add monoms with different index");
	}
	monom& operator-=(const monom& m) {
		this->coef -= m.coef;
		return *this;
	}
private:
	int32_t over(int32_t deg1, int32_t deg2) {
		int32_t deg = deg1 + deg2;
		if (deg >= base)throw string("overflow monom index");
		return deg;
	}
	int32_t sumoverflow(monom& i1,monom& i2) {
		return DegToIndex(over(i1.degx(), i2.degx()), over(i1.degy(), i2.degy()), over(i1.degz(), i2.degz()));
	}
	int32_t DegToIndex(int32_t degx, int32_t degy, int32_t degz) {
		return (degx << 16) ^ (degy << 8) ^ (degz);
		//return (degx*base+degy)*base+degz
	}
};

std::ostream& operator<<(std::ostream& out, monom& m) {
	out << m.coef;
	int32_t temp = m.degx();
	if (temp)out << "x" << temp;
	temp = m.degy();
	if (temp)out << "y" << temp;
	temp = m.degz();
	if (temp)out << "z" << temp;
	return out;
}

class polinom : protected list<monom> {
public:
	polinom() :list<monom>() {}
	polinom(const polinom& p) :list<monom>(p) {};
	polinom(const list<monom>& data) :list<monom>(data) {
		sort(); unique();
	}
	polinom(const monom& m) :list<monom>() {
		push_front(m);
	}
	polinom& operator*=(const type_coef& k) {
		for (auto it = begin(); it != end(); ++it) {
			(*it) *= k;
		}
		unique();
		return *this;
	}
	friend bool operator==(const polinom& a, const polinom& b) {
		polinom p = a - b;
		if (p.empty())return true;
		else return false;
	}
	friend polinom operator*(const polinom& p, const polinom& q) {
		polinom r;
		polinom* _p = const_cast<polinom*>(&p);
		polinom* _q = const_cast<polinom*>(&q);
		for (auto it1 = _p->begin(); it1 != _p->end(); ++it1) {
			for (auto it2 = _q->begin(); it2 != _q->end(); ++it2) {
				r.push_back((*it1) * (*it2));
			}
		}
		r.sort();
		r.unique();
		return r;
	};

	polinom& operator*=(const polinom& p) {
		(*this) = (*this) * p;
		return *this;
	}
	polinom& operator+=(polinom p) {
		count += p.size();
		merge(p);
		unique();
		return *this;
	}
	polinom& operator-=(polinom p) {
		p *= -1;
		return operator+=(p);
	}
	friend polinom operator+(const polinom& a, const polinom& b) {
		polinom c = a;
		c += b;
		return c;
	}
	friend polinom operator-(const polinom& a, const polinom& b) {
		polinom c = a;
		c -= b;
		return c;
	}
	friend ostream& operator<<(ostream& ost, polinom& p) {
		auto it = p.begin();
		while (it != p.end()) {
			ost << (*it);
			++it;
			if (it != p.end())ost << "+";
		}
		return ost;
	}
private:
	void merge(list<monom>& l) {
		list<monom>::merge(l, [](const monom& a, const monom& b) {return a > b; });
	}
	void sort() {
		list<monom>::sort([](const monom& a, const monom& b) {return a > b; });
	}
	void unique() {
		iterator<monom> it = this->begin();
		while (it != end()) {
			iterator<monom> next_it = it->next;
			if ((next_it) != end() && (*it) == (*next_it)) {
				(*it) += (*next_it);
				erase(next_it);
			}
			else {
				iterator<monom> old_it = it++;
				type_coef m = (*old_it).coef;
				m = (m >= 0) ? m: -m;
				if (m < eps) {
					erase(old_it);
				}
			}
		}
	}
};