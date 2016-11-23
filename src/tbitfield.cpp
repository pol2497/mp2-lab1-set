// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

TBitField::TBitField(int len)
{
	if (len <= 0) throw len;

	BitLen = len;
	MemLen = (len + 31) >> 5;
	pMem = new TELEM[MemLen];
	if (pMem != NULL)
		for (int i = 0; i < MemLen; i++) pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if (pMem != NULL)
		for (int i = 0; i < MemLen; i++)  pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
	pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n > -1) && (n < BitLen)) return n >> 5;
	else throw n;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n > -1) && (n < BitLen)) return 1 << (n & 31);
	else throw n;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n > -1) && (n < BitLen))
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	else throw n;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n > -1) && (n < BitLen))
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	else throw n;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n > -1) && (n < BitLen))
		return pMem[GetMemIndex(n)] & GetMemMask(n);
	else throw n;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	if (MemLen != bf.MemLen)
	{
		MemLen = bf.MemLen;
		if (pMem != NULL) delete[]pMem;
		pMem = new TELEM[MemLen];
	}
	if (pMem != NULL)
	{
		for (int i = 0; i<MemLen; i++) pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int res = 1;
	if (BitLen != bf.BitLen) res = 0;
	else
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i])
			{
				res = 0;
				break;
			}
	return res;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int i, len = BitLen;
	if (bf.BitLen > len) len = bf.BitLen;
	TBitField temp(len);
	for (i = 0; i < MemLen; i++) temp.pMem[i] = pMem[i];
	for (i = 0; i < bf.MemLen; i++) temp.pMem[i] |= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int i, len = BitLen;
	if (bf.BitLen > len) len = bf.BitLen;
	TBitField temp(len);
	for (i = 0; i < MemLen; i++) temp.pMem[i] = pMem[i];
	for (i = 0; i < bf.MemLen; i++) temp.pMem[i] &= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField a = *this;
	for (int i = 0; i < BitLen; i++)
	{
		if (a.GetBit(i)) a.ClrBit(i);
		else a.SetBit(i);
	}
	return a;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i = 0;
	char ch;
	do { istr >> ch; } while (ch != ' ');
	while (1)
	{
		if (ch == '0') bf.ClrBit(i++);
		else if (ch == '1') bf.SetBit(i++);
		else break;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int len = bf.GetLength();
	for (int i = 0; i < len; i++)
		if (bf.GetBit(i)) ostr << '1';
		else ostr << '1';
		return ostr;
}
