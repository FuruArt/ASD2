#include <iostream>

using namespace std;
class AL
{
public:
	long m_a, m_b, m_c;

	AL();
	~AL();
};
class Alchemia
{
public:
	long m_finalsize;
	AL * m_altab;
	AL **m_finaltab;
	long m_size;
	void size(long _size, long _finalsize);
	void sort();
	void add(long _a, long _b, long _c);
	void findAllWays();
	Alchemia();
	~Alchemia();
};



int main()
{
	long testy, metale, *tab_met, alchemia, *tab_alchem;
	long a, b, c;
	cin >> testy;

	for (int i = 0; i < testy; i++)
	{
		Alchemia al;
		//tabela cen metali
		cin >> metale;
		tab_met = new long[metale];
		for (int j = 0; j < metale; j++)
		{
			cin >> tab_met[j];
		}
		//tabela  procesow alchemicznych
		cin >> alchemia;
		al.size(alchemia, metale);
		for (int j = 0; j < alchemia; j++)
		{
			cin >> a >> b >> c;
			al.add(a, b, c);
		}
		//sortuje
		al.sort();
		//dzialam
		al.findAllWays();



		//testprint
		for (int j = 0; j < metale; j++)
		{
			cout << tab_met[j] << endl;
		}
		for (int i = 0; i < al.m_size; i++)
		{
			cout << al.m_altab[i].m_a << " " << al.m_altab[i].m_b << " " << al.m_altab[i].m_c << endl;
		}
		for (int i = 0; i < al.m_size; i++)
		{
			for (int j = 0; j < al.m_finalsize; j++)
			{
				cout << al.m_finaltab[i][j].m_a << " " << al.m_finaltab[i][j].m_b << " " << al.m_finaltab[i][j].m_c << endl;
			}
			cout << endl;
		}

	}
	return 0;
}
void Alchemia::size(long _size, long _finalsize)
{
	m_size = _size;
	m_finalsize = _finalsize;
	m_altab = new AL[_size];
	m_finaltab = new AL *[_size];
	for (int i = 0; i < _size; i++)
	{
		m_finaltab[i] = new AL[_finalsize];
		for (int j = 0; j < _finalsize; j++)
		{
			m_finaltab[i][j].m_a = NULL;
			m_finaltab[i][j].m_b = NULL;
			m_finaltab[i][j].m_c = NULL;
		}
		m_altab[i].m_a = NULL;
		m_altab[i].m_b = NULL;
		m_altab[i].m_c = NULL;
	}
}
void Alchemia::add(long _a, long _b, long _c)
{
	for (int i = 0; i < m_size; i++)
	{
		if (m_altab[i].m_c == NULL)
		{
			m_altab[i].m_a = _a;
			m_altab[i].m_b = _b;
			m_altab[i].m_c = _c;
			break;
		}
	}
}
void Alchemia::sort()
{
	AL pom;
	int index, w;
	for (int i = m_size-1; i >=0; i--)
	{
		w = m_altab[i].m_a;
		index = i;
		for (int j = 0; j < i; j++)
		{
			if (m_altab[j].m_a > w)
			{
				w = m_altab[j].m_a;
				index = j;
			}

		}
		pom = m_altab[i];
		m_altab[i] = m_altab[index];
		m_altab[index] = pom;
	}
}
void Alchemia::findAllWays()
{
	AL pom;
	int a, b;
	int ii = 0;
	/*
	mam
	*/
	while (m_altab[ii].m_a < 2)
	{
		a = m_altab[ii].m_a;
		b = m_altab[ii].m_b;
		for (int i = 0; i < m_size; i++)
		{
			for (int j = 0; j < m_finalsize; j++)
			{
				if (a != m_finaltab[i][j].m_a&& b != m_finaltab[i][j].m_b)
					m_finaltab[i][j] = m_altab[i];
				ii++;
				break;

			}

		}

	}
}
AL::AL()
{
}
AL::~AL()
{
}
Alchemia::Alchemia()
{
}
Alchemia::~Alchemia()
{
}