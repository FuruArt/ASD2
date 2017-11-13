#include <iostream>
#include <Windows.h>
#include <time.h>

using namespace std;

class tabgrah
{
public:
	//zmienne
	double m_x;
	double m_y;
	double m_kat;
	//metody

	//konstruktory, destruktory
	tabgrah();
	~tabgrah();
};
class Graham
{
public:
	//zmienne
	tabgrah *tablica;
	tabgrah m_minimum;
	int m_size;
	//metody
	void size(int _size);
	void wypelnij();
	void znajdz();
	void przesun();
	void sortuj();
	//konstruktory, destruktory
	Graham();
	~Graham();
};

int main()
{
	Graham zad;
	zad.size(20);
	zad.wypelnij();
	zad.znajdz();
	zad.przesun();
	zad.sortuj();

	system("pause");
	return 0;
}
void Graham::size(int _size)
{
	tablica = new tabgrah[_size];
	m_size = _size;
}
void Graham::wypelnij()
{
	cout << "Przed sortowaniem wylosowane: " << endl;
	//srand(time(NULL));
	for (int i = 0; i < m_size; i++)
	{
		tablica[i].m_x = (((rand() % 20) - 10) / 0.5)*0.65;
		tablica[i].m_y = (((rand() % 20) - 10) / 0.5)*0.75;
		tablica[i].m_kat = 0;
		cout <<"x "<< tablica[i].m_x<<"\t\ty: "<< tablica[i].m_y <<
			"\t\tkat: "<<tablica[i].m_kat<<endl;
	}
	cout << "-------------------------------------" << endl;
}
void Graham::znajdz()
{
	for (int i = 0; i < m_size; i++)
	{
		if (i == 0)
			m_minimum = tablica[i];
		else
		{
			if (tablica[i].m_y<m_minimum.m_y)
				m_minimum = tablica[i];
			else if (tablica[i].m_y == m_minimum.m_y)
			{
				if (tablica[i].m_x<m_minimum.m_x)
					m_minimum = tablica[i];
			}
		}
	}
	cout << "Najmniejszy punkt to" << endl;
	cout << "x " << m_minimum.m_x << "\t\ty: " << m_minimum.m_y <<
		"\t\tkat: " << m_minimum.m_kat << endl;
	cout << "-------------------------------------" << endl;
}
void Graham::przesun()
{
	cout << "Po przesunieciu: " << endl;
	for (int i = 0; i < m_size; i++)
	{
		tablica[i].m_x -= m_minimum.m_x;
		tablica[i].m_y -= m_minimum.m_y;

		cout << "x " << tablica[i].m_x << "\t\ty: " << tablica[i].m_y <<
			"\t\tkat: " << tablica[i].m_kat << endl;
	}
	cout << "-------------------------------------" << endl;

}
void Graham::sortuj()
{
	tabgrah wez, pom;
	double wieksza;
	int indexw;
	int rozmiar;
	rozmiar = m_size;
	for (int i = rozmiar-1; i >=0; i--)
	{
		for (int j = 0; j < rozmiar; j++)
		{
			if (j == 0)
			{
				wieksza = tablica[j].m_x;
				indexw = j;
			}
			else
			{
				if (tablica[j].m_y > wieksza)
				{
					wieksza = tablica[j].m_y;
					indexw = j;
				}
			}
		}
		//podmieniam aktualna wartosc [i] z najwiekszym znalezionym [j]
		wez = tablica[indexw];
		pom = tablica[i];
		tablica[i] = wez;
		tablica[indexw] = pom;
		rozmiar--;
	}

	cout << "Po sortowaniu: " << endl;
	for (int i = 0; i < m_size; i++)
	{
		cout << "x " << tablica[i].m_x << "\t\ty: " << tablica[i].m_y <<
			"\t\tkat: " << tablica[i].m_kat << endl;
	}
	cout << "-------------------------------------" << endl;
}
tabgrah::tabgrah()
{
}

tabgrah::~tabgrah()
{
}

Graham::Graham()
{
}

Graham::~Graham()
{
	delete[] tablica;
}
