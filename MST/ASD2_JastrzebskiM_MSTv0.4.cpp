/**********************************************************************************************
**		Autor:				Marcin Jastrzêbski												 **
**		Kontakt:			jaczomb@gmail.com												 **
**		Data:				16.04.2017														 **
**		Nazwa:				MST																 **
**___________________________________________________________________________________________**
**	Data			| Wersja			| Zmiany											 **
**	13.04.2017		| .v0.1				| dziala dla wierzcholkow numerowanych od 1			 **
**	14.04.2017		| .v0.2				| dziala dla wierzcholkow numerowanych				 **
**					|					| w caly swiat										 **
**	16.04.2017		| .v0.3				| skrocony DoIt(), dostosowany Print() do polecenia, **
**					|					| usuniêty using namespace std,						 **
**	16.04.2017		| .v0.4				| poprawione nazwy zmiennych						 **
**********************************************************************************************/

#include <iostream>
#include <string>

class Object
{
public:
	//zmienne
	long m_vertex;
	std::string m_vname;
	long m_index;
	//kostruktory destruktory
	Object(long _ver, std::string _nam, long _ind = 0);
	Object();
	~Object();
};
class Longi
{
public:
	long m_a;
	long m_b;
	long m_c;
	Longi(long _a, long _b, long _c);
	Longi();
	~Longi();
};
class MST
{
public:
	//zmienne
	Object *m_nameboard;				//Tablica (wierzcholek, nazwa)
	Longi *m_vertexboard;				//Tablica (wierzcholek, wierzcholek, dlugosc)
	Longi *m_MSTboard;					//Tablica (wierzcholek, wierzcholek, dlugosc) po MST
	long m_size, m_sizelongi;
	//metody
	void Size(long _size);
	void SizeL(long _size);
	void Add(Object& _object);
	void Add(Longi& _longi);
	void Sort();						//Sortowanie
	void DoIt();						//Metoda tworz¹ca MST
	void Print();						//Metoda drukuj¹ca
										//kostruktory, destruktory
	MST();
	~MST();
};

int main()
{
	int ilosc_wierzch;
	long l1, l2, l3;
	char buffer[16];
	long liczba;
	long kraw;
	std::string name;
	std::cin >> ilosc_wierzch;
	//TRORZENIE TABLICY WIERZCHOLKOW
	MST m;
	m.Size(ilosc_wierzch);
	for (int i = 0; i < ilosc_wierzch; i++)
	{
		std::cin >> buffer;
		liczba = atol(buffer);
		std::cin >> buffer;
		name = std::string(buffer);
		Object o(liczba, name, i);
		m.Add(o);
	}

	//TWORZENIE TABLICY DLUGOSCI
	std::cin >> buffer;
	kraw = atol(buffer);
	m.SizeL(kraw);
	for (int i = 0; i < kraw; i++)
	{
		std::cin >> buffer;
		l1 = atol(buffer);
		std::cin >> buffer;
		l2 = atol(buffer);
		std::cin >> buffer;
		l3 = atol(buffer);
		Longi n(l1, l2, l3);
		m.Add(n);
	}
	m.Sort();
	m.DoIt();
	m.Print();

	delete[] m.m_vertexboard;
	delete[] m.m_MSTboard;
	delete[] m.m_nameboard;

	return 0;
}
void MST::Size(long _size)
{
	//Tworzê tablice do przechowywania nazwy i nr wierzcholkow 
	m_size = _size;
	m_nameboard = new Object[_size];

	for (int i = 0; i < _size; i++)
	{
		m_nameboard[i] = { NULL, "NULL", 'E' };
	}
}
void MST::SizeL(long _size)
{
	//Tworzê tablice do przechowywania nr'ow i dlugosci miedzy wierzcholkami
	m_sizelongi = _size;
	m_vertexboard = new Longi[_size];
	m_MSTboard = new Longi[_size];

	for (int i = 0; i < _size; i++)
	{
		m_vertexboard[i] = { NULL, NULL, NULL };
		m_MSTboard[i] = { NULL, NULL, NULL };
	}
}
void MST::Add(Object& _object)
{
	for (int i = 0; i < m_size; i++)
	{
		if (m_nameboard[i].m_vname == "NULL")
		{
			m_nameboard[i] = { _object.m_vertex, _object.m_vname, _object.m_index };
			break;
		}
	}
}
void MST::Add(Longi & _longi)
{
	for (int i = 0; i < m_sizelongi; i++)
	{
		if (m_vertexboard[i].m_a == NULL&& m_vertexboard[i].m_b == NULL&&m_vertexboard[i].m_c == NULL)
			//zabezpieczenie przed podwojnym 0
		{
			m_vertexboard[i] = { _longi.m_a, _longi.m_b , _longi.m_c };
			break;
		}
	}
}
void MST::Sort()
{
	Longi wez, pom;
	int indexw;
	long wieksza;
	int rozmiar;
	rozmiar = m_sizelongi;
	//zaczynam od koñca
	for (int i = rozmiar - 1; i >= 0; i--)
	{
		//znajduje najwieksza wartosc oraz index najwyzszej wartosci
		for (int j = 0; j < rozmiar; j++)
		{
			if (j == 0)
			{
				wieksza = m_vertexboard[j].m_c;
				indexw = j;
			}
			else
			{
				if (m_vertexboard[j].m_c > wieksza)
				{
					wieksza = m_vertexboard[j].m_c;
					indexw = j;
				}
			}
		}
		//podmieniam aktualna wartosc [i] z najwiekszym znalezionym [j]
		wez = m_vertexboard[indexw];
		pom = m_vertexboard[i];
		m_vertexboard[i] = wez;
		m_vertexboard[indexw] = pom;
		rozmiar--;
	}
}
void MST::DoIt()
{
	//metoda do wyszukiwania MST
	int indexm, indexw;
	for (int i = 0; i < m_sizelongi; i++)
	{
		//flagi
		//ustalam numery indeksow flag wchodzacej pary liczb
		for (int j = 0; j < m_size; j++)
		{
			//szukam mniejszego indexu flagi i wiekszego
			if (m_vertexboard[i].m_a > m_vertexboard[i].m_b)
			{
				if (m_vertexboard[i].m_a == m_nameboard[j].m_vertex)
					indexw = m_nameboard[j].m_index;
				if (m_vertexboard[i].m_b == m_nameboard[j].m_vertex)
					indexm = m_nameboard[j].m_index;
			}
			else
			{
				if (m_vertexboard[i].m_a == m_nameboard[j].m_vertex)
					indexm = m_nameboard[j].m_index;
				if (m_vertexboard[i].m_b == m_nameboard[j].m_vertex)
					indexw = m_nameboard[j].m_index;
			}
		}

		//Zerowy przesortowany element wchodzi do tablicy bez regu³
		if (i == 0)
		{
			m_MSTboard[i] = m_vertexboard[i];
			for (int j = 0; j < m_size; j++)
			{
				//jesli znajde w tablicy wierzcholek z wiekszym indexem zmieniam go na mniejszy.
				if (m_nameboard[j].m_index == indexw)
					m_nameboard[j].m_index = indexm;
			}
		}

		//dla reszty elementow
		else if (indexm != indexw)
		{
			m_MSTboard[i] = m_vertexboard[i];
			for (int j = 0; j < m_size; j++)
			{
				//jesli znajde w tablicy wiekszy index zmieniam go na mniejszy.
				if (m_nameboard[j].m_index == indexw)
					m_nameboard[j].m_index = indexm;
			}
		}

		///PRINT STRUKTURA POMOCNICZA
		/*for (int j = 0; j < m_size; j++)
		{
		std::cout << m_nameboard[j].m_vertex << " " << m_nameboard[j].m_vname << "\t" << m_nameboard[j].m_index << std::endl;
		}
		std::cout << std::endl;
		std::cout << m_MSTboard[i].m_a << " " << m_MSTboard[i].m_b << " " << m_MSTboard[i].m_c << " " << std::endl << std::endl;*/
	}

}
void MST::Print()
{
	std::string n1, n2;
	///TABLICA (wierzcho³ek, nazwa)
	/*for (int i = 0; i < m_size; i++)
	{
	std::cout << m_nameboard[i].m_vertex << " " << m_nameboard[i].m_vname<<"\t"<<m_nameboard[i].m_index << std::endl;
	}
	std::cout << std::endl;*/

	///TABLICA (wierzcholek, wierzcholek, dlugosc)
	/*for (int i = 0; i < m_sizelongi; i++)
	{
	std::cout << m_vertexboard[i].m_a << " " << m_vertexboard[i].m_b << " " << m_vertexboard[i].m_c << " " << std::endl;
	}
	std::cout << std::endl;*/

	for (int i = 0; i < m_sizelongi; i++)
	{
		if (m_MSTboard[i].m_c != NULL)
		{
			for (int j = 0; j < m_size; j++)
			{
				if (m_MSTboard[i].m_a == m_nameboard[j].m_vertex)
					n1 = m_nameboard[j].m_vname;
				if (m_MSTboard[i].m_b == m_nameboard[j].m_vertex)
					n2 = m_nameboard[j].m_vname;
			}
			std::cout << n1 << " " << n2 << " " << m_MSTboard[i].m_c << " " << std::endl;
		}
	}
	std::cout << std::endl;
}
Object::Object(long _ver, std::string _nam, long _ind) : m_vertex(_ver), m_vname(_nam), m_index(_ind)
{
}
Object::Object()
{
}
Object::~Object()
{
}
Longi::Longi(long _a, long _b, long _c) : m_a(_a), m_b(_b), m_c(_c)
{
}
Longi::Longi()
{
}
Longi::~Longi()
{
}
MST::MST()
{
}
MST::~MST()
{
}