#include "money.h"
#include <exception>
#include <cmath>

Money::Money(int kop) : m_kopeika(kop){}

// решительно не помню, почему я сделал именно так
Money::Money(int32_t rub, uint8_t kop) 
    : Money (rub > 0 ? 	static_cast<int>(rub * 100 + kop) : static_cast<int>(rub * 100 - kop))
{
	if (kop > 100)
		throw std::out_of_range("Invalid type of uint8_t m_kopeika ()");
}

// решительно не помню, почему я сделал именно так
Money::Money(int32_t rub, int kop) : Money (rub, static_cast<uint8_t>(kop < 0 ? kop*-1 : kop)){}

Money::Money(const Money& m) : Money(m.m_kopeika) {}

Money::Money(double rub) : m_kopeika(static_cast<int>(std::round(rub*100))) {}

Money::Money() : Money(0, 0) { }

int32_t Money::getRubel() const
{
	return static_cast<int32_t>(m_kopeika/100);
}

uint8_t Money::getKopeika() const
{
	if(m_kopeika > 0)
		return static_cast<uint8_t>(m_kopeika%100);
	else
		return static_cast<uint8_t>(-m_kopeika % 100);
}

Money& Money::operator=(const Money& m)
{
	if (this != &m)
		m_kopeika = m.m_kopeika;
	
	return *this;
}

bool Money::operator>(const Money& m) const
{
	return m_kopeika > m.m_kopeika;
}

bool Money::operator<(const Money& m) const
{
	return !(*this>=m);
}

bool Money::operator>=(const Money& m) const
{
	return m_kopeika >= m.m_kopeika;
}
 
bool Money::operator<=(const Money& m) const
{
	return !(*this>m);
}

bool Money::operator==(const Money& m) const
{
	return m_kopeika == m.m_kopeika;
}

bool Money::operator!=(const Money& m) const
{
	return !(*this == m);
}

Money Money::operator+(const Money& m)
{
	return Money(m_kopeika + m.m_kopeika);
}

Money Money::operator-(const Money& m)
{
	return -m + *this;
}

Money Money::operator-() const
{
	return Money(-m_kopeika);
}

Money Money::operator*(const int x)
{
	return Money(m_kopeika*x);
}

Money Money::operator/(const int x)
{
	return Money(static_cast<double>(m_kopeika) / static_cast<double>(x) / 100);
}

std::ostream& operator<<(std::ostream& out, const Money& m)
{
	out << m.getRubel() << " руб. " << static_cast<int>(m.getKopeika()) << " коп. ";
	return out;
}
