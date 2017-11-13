/**********************************************************************************************
**		Autor:				Marcin Jastrzêbski												 **
**		Kontakt:			jaczomb@gmail.com												 **
**		Data:				29.03.2017														 **
**		Nazwa:				HEAPSORT														 **
**___________________________________________________________________________________________**
**	Data			| Wersja			| Zmiany											 **
**	29.03.2017		| .v1				| kopcuje, sortuje									 **											***
**********************************************************************************************/
#include <iostream>
#include <string>

class Heapsort
{
public:
	//zmienne
	long *m_tab, *m_tab2, *m_Htab;
	long m_size;
	long m_liczba;
	static int licznik;

	//metody
	void Size(long _size);
	void Add(long l);
	void Print();
	void Sort();

	//kostruktory, destruktory
	Heapsort();
	~Heapsort();
};

int Heapsort::licznik = 0;

int main()
{
	int przypadki;
	int rozmiar;
	long l;
	bool petla = true;

	std::cin >>przypadki;
	for (int i = 0; i < przypadki; i++)
	{
		Heapsort h_;

			std::cin >> rozmiar;
			h_.Size(rozmiar);
			for (int j = 0; j < rozmiar; j++)
			{
				std::cin >> h_.m_tab[j];
				h_.licznik++;
			}
			h_.licznik = 0;
			h_.Sort();
			h_.Print();
			delete[]h_.m_tab;
			delete[]h_.m_Htab;
	}

	//system("PAUSE");

	return 0;
}

void Heapsort::Size(long _size)
{
	m_size = _size;
	m_tab = new long[_size];
	m_Htab = new long[_size];

	for (int i = 0; i < _size; i++)
	{
		m_tab[i] = { NULL };
		m_Htab[i] = { NULL };
	}
}

void Heapsort::Sort()
{
	long index, indexm;
	long pom, szukana;
	long roz;
	
	roz = m_size;

	do
	{
		//przepisanie + kopcowanie
		for (int i = 0; i < roz; i++)
		{
			index = i;
			indexm = (int)((index - 1) / 2);
			// dla 0 indexu
			if (index == 0)
			{
				m_Htab[i] = m_tab[i];
			}
			//dla reszty
			else
			{
				szukana = m_tab[index]; //wyjmuje liczbe z tablicy pomocniczej
				do
				{
					if (szukana > m_Htab[indexm])
					{
						pom = m_Htab[indexm];
						m_Htab[indexm] = szukana;
						m_Htab[index] = pom;
						index = indexm;
						indexm = (int)((index - 1) / 2);
					}
					else //(tab2[index] =< tab[indexm])
					{
							m_Htab[index] = szukana;
							index = 0;
					}

				} while (index != 0); //rob dopoki index jest rozny od 0

			}
		}
		//sprawdzenie
		for (int j = 0; j < roz; j++)
		{
			//cout << m_tab[j] << " ";
			std::cout << m_Htab[j] << " ";
		}
		std::cout << std::endl;

		pom = m_Htab[0];
		m_Htab[0] = m_Htab[roz-1];
		m_Htab[roz-1] = pom;

		//czyszczenie i przepisanie
		if (roz != 2)
		{
			for (int j = 0; j < roz-1; j++)
			{
				m_tab[j] = m_Htab[j];
				m_Htab[j] = NULL;
			}
		}
		roz--;

	} while (roz != 1);
}

void Heapsort::Add(long l)
{
	int index, indexm, szukana, pom;

	index = licznik;
	indexm = (int)((licznik - 1) / 2);
	szukana = l;

	do
	{
		if (licznik == 0)
		{
			m_tab[licznik] = szukana;
			index = indexm;
			indexm = (int)((index - 1) / 2);
		}
		else if (szukana > m_tab[indexm])
		{
			pom = m_tab[indexm];
			m_tab[indexm] = szukana;
			m_tab[index] = pom;
			index = indexm;
			szukana = m_tab[index];
			indexm = (int)((index - 1) / 2);
		}
		else //(tab2[index] < tab[indexm])
		{
			m_tab[index] = szukana;
			index = 0;
		}
	} while (index != 0); //rob dopoki index jest rozny od 0
}

void Heapsort::Print()
{
	for (int j = 0; j < m_size; j++)
	{
		//cout << m_tab[j] << " ";
		std::cout << m_Htab[j] << " ";
	}
	std::cout << std::endl << std::endl;
}

Heapsort::Heapsort()
{
}

Heapsort::~Heapsort()
{
}