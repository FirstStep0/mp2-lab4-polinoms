#include <iostream>
#include "stack.h"
#include <cstdint>
typedef unsigned char uchar;
typedef double type_coef;

class monom {
public:
	int32_t index;
	type_coef coef;
	monom() :monom(0, 0) {};
	monom(const monom& m) :monom(m.coef, m.index) {};
	monom(type_coef coef, int32_t x, int32_t y, int32_t z) :monom(coef, DegToIndex(x, y, z)) {};
	monom(type_coef coef, int32_t index = 0) :coef(coef), index(index) {}
	int32_t degx() { return (uchar)(index >> 16); }
	int32_t degy() { return (uchar)(index >> 8); }
	int32_t degz() { return (uchar)(index); }
	void SetIndex(int32_t degx, int32_t degy, int32_t degz) {
		index = DegToIndex(degx, degy, degz);
	}
	friend bool operator<(const monom& a, const monom& b) {
		return (a.index < b.index) || ((a.index == b.index) && (a.coef < b.coef));
	}
	friend bool operator>(const monom& a, const monom& b) {
		return (a.index > b.index) || ((a.index == b.index) && (a.coef > b.coef));
	}
	friend bool operator==(const monom& a, const monom& b) { return(a.index == b.index) && (a.coef == b.coef); };
	friend bool operator!=(const monom& a, const monom& b) { return(a.index != b.index) || (a.coef != b.coef); };
	monom& operator*=(const type_coef& coef) {
		this->coef *= coef;
		return *this;
	}
	monom& operator*=(const monom& m) {
		this->coef *= m.coef;
		index = sumoverflow(index, m.index);
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
	int32_t over(int32_t index1, int32_t index2) {
		int32_t index = index1 + index2;
		if (index >> (sizeof(uchar) << 3))throw string("overflow monom index");
		return index;
	}

	int32_t sumoverflow(int32_t index1, int32_t index2) {
		int32_t index = 0;
		index ^= over((uchar)index1, (uchar)index2);
		index ^= over((uchar)(index1 >> 8), (uchar)(index2 >> 8)) << 8;
		index ^= over((uchar)(index1 >> 16), (uchar)(index2 >> 16)) << 16;
		return index;
	}
	int32_t DegToIndex(int32_t degx, int32_t degy, int32_t degz) {
		return ((int32_t)(over(degx, 0) << (sizeof(uchar) << 4)) ^ (over(degy, 0) << (sizeof(uchar) << 3)) ^ over(degz, 0));
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
		auto it = begin();
		while (it != end()) {
			(*it) *= k; ++it;
		}
		unique();
		return *this;
	}
	friend bool operator==(const polinom& a, const polinom& b) {
		polinom p = a - b;
		if (p.size() == 0)return true;
		else return false;
	}
	friend polinom operator*(const polinom& p, const polinom& q) {
		polinom r;
		polinom* _p = const_cast<polinom*>(&p);
		polinom* _q = const_cast<polinom*>(&q);
		auto it1 = _p->begin();
		while (it1 != _p->end()) {
			auto it2 = _q->begin();
			while (it2 != _q->end()) {
				r.push_back((*it1) * (*it2));
				++it2;
			}
			++it1;
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
			if (((iterator<monom>)it->next) != end() && (*it).index == it->next->value.index) {
				(*it) += (*(iterator<monom>)it->next);
				erase(it->next);
			}
			else {
				iterator<monom> it2 = it++;
				if ((*it2).coef == 0) {
					erase(it2);
				}
			}
		}
	}
};