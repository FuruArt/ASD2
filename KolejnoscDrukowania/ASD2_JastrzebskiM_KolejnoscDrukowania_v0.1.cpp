/**********************************************************************************************
**		Autor:				Marcin Jastrzêbski												 **
**		Kontakt:			jaczomb@gmail.com												 **
**		Data:				23.04.2017														 **
**		Nazwa:				Kolejnoœæ Drukowania											 **
**		Link:		http://www.wfis.uni.lodz.pl/staff/tgwizdalla/files/asd2_2017_zzw3.pdf	 **
**___________________________________________________________________________________________**
**	Data			| Wersja			| Zmiany											 **
**	23.04.2017		| .v0.1				| dzia³a, ba³agan w nazwach i printach				 **
**********************************************************************************************/
#include <iostream>
#include <string>

using namespace std;

class Object
{
public:
	//zmienne
	int m_priorytet;
	char m_flag;
	//konstruktory, destruktory
	Object();
	Object(int _priorytet, char _flag = 'E');
	~Object();
};
class KD
{
public:
	//zmienne
	long m_size;
	Object *m_tab;
	//metody
	void Size(long _size);
	void Add(long _liczba);
	void DoIt();
	void Print();
	//konstruktory sestruktory
	KD();
	~KD();
};

int main()
{
	long testy, size, index, liczba;
	cin >> testy;
	testy = testy;
	for (int i = 0; i < testy; i++)
	{
		cin >> size;
		cin >> index;
		KD a;
		a.Size(size);
		for (int j = 0; j < size; j++)
		{
			cin >> liczba;
			a.Add(liczba);
			if (j == index)
			{
				a.m_tab[j].m_flag = 'C';
			}
		}
		a.DoIt();
		delete[] a.m_tab;
	}
	return 0;
}
void KD::Size(long _size)
{
	m_size = _size;
	m_tab = new Object[m_size];

	for (int i = 0; i < m_size; i++)
	{
		m_tab[i] = { 10,'E' };
	}
}
void KD::Add(long _liczba)
{
	for (int i = 0; i < m_size; i++)
	{
		if (m_tab[i].m_flag == 'E')
		{
			m_tab[i].m_priorytet = _liczba;
			m_tab[i].m_flag = 'F';
			break;
		}
	}
}
void KD::DoIt()
{
	bool flag;
	long index, prior;
	long m, w, licz;
	long sizetab;
	Object pom, pom2;
	licz = 0;
	long indexpom = 0;
	sizetab = m_size;
	do
	{
		flag = true;
		indexpom++;
		//licz = 0;
		//wyciagam najmniejszy i najwiekszy priorytet
		for (int i = 0; i < m_size; i++)
		{
			/*if (m_tab[i].m_priorytet < 10)
			licz++;*/
			if (i == 0)
			{
				m = m_tab[i].m_priorytet;
				w = m_tab[i].m_priorytet;
			}
			if (m_tab[i].m_priorytet > w&&m_tab[i].m_priorytet<10)
				w = m_tab[i].m_priorytet;
			if (m_tab[i].m_priorytet<m)
				m = m_tab[i].m_priorytet;
		}
		//cout << m << " " << w <<"\tindexpom: "<<indexpom<< endl;

		//wlasciwa petla sprawdzajaca
		//czy wchodzaca liczba nadaje sie do skasowania
		for (int i = 0; i < sizetab; i++)
		{
			if (m_tab[i].m_priorytet < w)
			{
				pom = m_tab[sizetab - 1];
				pom2 = m_tab[i];

				for (int j = 0; j < sizetab - 1; j++)
				{
					m_tab[j] = m_tab[j + 1];
				}
				m_tab[sizetab - 1] = pom2;
				m_tab[sizetab - 2] = pom;
				break;
			}
			else
			{
				for (int j = 0; j < sizetab - 1; j++)
				{
					m_tab[j] = m_tab[j + 1];
				}
				m_tab[sizetab - 1] = { 10, 'E' };
				sizetab--;
				licz++;
				break;
			}
		}
		for (int i = 0; i < sizetab + 1; i++)
		{
			if (m_tab[i].m_flag == 'C')
			{
				flag = true;
				break;
			}
			else
				flag = false;
		}

		////test print 
		//for (int i = 0; i < m_size; i++)
		//{
		//	cout << m_tab[i].m_priorytet << " " << m_tab[i].m_flag << "\t";
		//}
		//cout << endl;
	} while (flag != false);
	cout /*<<"minuty"*/ << licz << endl;
}
void KD::Print()
{
	for (int i = 0; i < m_size; i++)
	{
		cout << m_tab[i].m_priorytet << " " << m_tab[i].m_flag << "\t";
	}
	cout << endl;
}
Object::Object()
{
}
Object::Object(int _priorytet, char _flag) :m_priorytet(_priorytet), m_flag(_flag)
{
}
Object::~Object()
{
}
KD::KD()
{
}
KD::~KD()
{
}