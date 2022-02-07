#pragma once

#include <iostream>
#include <cstdint> // для фиксированных переменных


class Money
{
private:
	int m_kopeika;
public:
	Money(int kop); // Указывается сумма в копейках (10 000 копеек = 100 рублей)
	Money(int32_t rub, uint8_t kop);
    Money(int32_t rub, int kop); // Костыль на случай, если напутаешь с минусом
	Money(const Money& m);
	Money(double rub);
	Money();
	~Money(){} // ненужный деструктор

	//геттеры
	int32_t getRubel() const;
	uint8_t getKopeika() const;

	friend std::ostream& operator<< (std::ostream& out, const Money& m);

//	Money operator= (const Money& m);
	Money& operator= (const Money& m);
	bool operator > (const Money& m) const;
	bool operator < (const Money& m) const;
	bool operator >=(const Money& m) const;
	bool operator <=(const Money& m) const;
	bool operator ==(const Money& m) const;
	bool operator !=(const Money& m) const;

	Money operator+(const Money& m);
	Money operator-(const Money& m);
	Money operator-() const;
	Money operator*(const int x);
	Money operator/(const int x);
	
};

