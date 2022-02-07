#pragma once

#include <iostream>
#include <cstdint> // ��� ������������� ����������


class Money
{
private:
	int m_kopeika;
public:
	Money(int kop); // ����������� ����� � �������� (10 000 ������ = 100 ������)
	Money(int32_t rub, uint8_t kop);
    Money(int32_t rub, int kop); // ������� �� ������, ���� ��������� � �������
	Money(const Money& m);
	Money(double rub);
	Money();
	~Money(){} // �������� ����������

	//�������
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

