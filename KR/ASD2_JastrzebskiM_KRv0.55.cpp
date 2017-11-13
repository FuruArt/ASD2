/**********************************************************************************************
**		Autor:				Marcin Jastrzêbski												 **
**		Kontakt:			jaczomb@gmail.com												 **
**		Data:				22.05.2017														 **
**		Nazwa:				KR		v0.4													 **
**___________________________________________________________________________________________**
**	Data			| Wersja			| Zmiany											 **
**	09.05.2017		| .v0.1				| dziala dla liczb 0-9								 **
**	22.05.2017		| .v0.2				| dziala dla liczb i cyfr							 **
**	22.05.2017		| .v0.3				| dodane modulo we wzorze							 **
**	22.05.2017		| .v0.4				| wlasna funkcja potegujaca							 **
**	22.05.2017		| .v0.5				| skasowac cmath, namespace std; sprobowac gdzies wsadzic wskazniki i zmienne **
**********************************************************************************************/

#include <iostream>
#include <string>
//#include <cmath>									//pow()
#include <fstream>

using namespace std;
class KR
{
public:
	//zmienne
	string m_txt;									// wczytany plik
	string m_substring;								// wczytany poszukiwany string
	const long long m_modulo = 46337;				// modulo
	const int m_podstawa = 256;						// wsadzic do wzoru
	long long m_hw;
	long long m_h0;
	long long m_hn;
	long long m_ww;
	bool m_porownanie;

	//metody
	void hwh0();
	void karp();
	long long powl(int _liczba, int _stopien);
	long long hasz(int _start);
	bool porownaj(int _start);
	//konstruktory, destruktory
	KR();
	~KR();
};

fstream g_plik;

int main()
{
	string buffer;
	string x;
	string nazwa;
	long ile_razy;
	//cin >> buffer2;
	getline(cin, buffer);
	ile_razy = stol(buffer);

	for (int i = 0; i < ile_razy; i++)
	{
		KR m;
		//zaladowanie nazwy pliku
		getline(cin, nazwa);
		g_plik.open(nazwa, ios::in);
		//zaladowanie poszukiwanej frazy/zdania
		getline(cin, m.m_substring);
		//wczytanie calego pliku do stringa
		while (getline(g_plik, x))
		{
			m.m_txt = m.m_txt + x + "\n";
		}
		//testprint
		//cout << "Przeszukiwany tekst: " << m.m_txt << endl;
		cout << "Szukany podciag: " << m.m_substring << endl;
		//porownywanie
		m.karp();
		//zamykam
		g_plik.close();
	}
	return 0;
}
void KR::hwh0()
{
	int dlugosc = m_substring.length();
	m_hw = NULL;
	m_hn = NULL;
	/*cout << "HW: DLUGOSC " << dlugosc <<" dla : "<<m_substring<<endl;*/
	for (int i = 0; i <m_substring.length(); i++)
	{
		//USTALAM HW
		//m_hw += m_substring[i] * powl(m_podstawa, dlugosc - 1);
		m_hw += ((m_substring[i] + m_modulo) % m_modulo) * (long(powl(m_podstawa, dlugosc - 1)) % m_modulo);
		m_hw = m_hw%m_modulo;

		//USTALAM HN
		//m_hn += m_txt[i] * powl(m_podstawa, dlugosc - 1);
		m_hn += m_txt[i] * (long(powl(m_podstawa, dlugosc - 1)) % m_modulo);
		m_hn = m_hn%m_modulo;

		//zmniejszam dlugosc do motody potegujacej w nast iteracji
		dlugosc--;
	}
	m_ww = m_txt[0];
	m_h0 = m_hn;
}
long long KR::hasz(int _start)
{
	int dlugosc = m_substring.length();
	for (int i = _start; i <m_substring.length() + _start; i++)
	{
		////testowe drukowanie
		//cout << "H"<<_start<<" : DLUGOSC " << dlugosc <<" dla : ";
		//for (int j = _start; j < m_substring.length() + _start; j++)
		//{
		//	cout << m_txt[j];
		//}
		//cout << endl;
		//wlasciwa funkcja
		if (_start == 0)
		{
			break;
		}
		else
		{
			/*m_hn = (m_h0 - (m_ww * powl(m_podstawa, dlugosc - 1)))*m_podstawa
			+ m_txt[dlugosc + _start - 1];*/
			m_hn = (((((m_h0%m_modulo) - (long(m_ww * powl(m_podstawa, dlugosc - 1)) % m_modulo)) + m_modulo) % m_modulo)
				*(m_podstawa%m_modulo))
				+ m_txt[dlugosc + _start - 1];
			m_hn = m_hn%m_modulo;
			m_ww = m_txt[_start];
			/*cout << "Hasz wynosi : " << m_hn << endl;*/
			break;
		}
		/*cout << "Hasz wynosi : " << m_hn << endl;*/
	}
	m_h0 = m_hn;
	return m_hn;
}
bool KR::porownaj(int _start)
{
	int licznik = 0;
	int j = 0;
	for (int i = _start; i < m_substring.length() + _start; i++)
	{
		if (m_substring[j] == m_txt[i])
		{
			licznik++;
			j++;
		}
		else
			break;
	}
	if (licznik == m_substring.length())
		return m_porownanie = 1;
	else
		return m_porownanie = 0;
}
long long KR::powl(int _liczba, int _stopien)
{
	long long wynik;
	for (int i = 0; i <= _stopien; i++)
	{
		if (i == 0)
			wynik = 1;
		else if (i == 1)
			wynik = _liczba;
		else
			wynik = (wynik*_liczba);
		wynik = wynik%m_modulo;
	}
	return wynik;
}
void KR::karp()
{
	//METODA KARP RABIN
	//1. Wyznaczam H0 i Hw
	//2. Porownuje Hasz(i) z Hw	

	hwh0(); //1;

	//Dokladne
	cout << "Dokladne" << endl;
	for (int i = 0; i < m_txt.length() - m_substring.length(); i++)
	{
		if (hasz(i) == m_hw)
		{
			porownaj(i);
			if (m_porownanie == 1)
			{
				cout << i << " ";
				m_porownanie = 0;
			}
		}
	}
	cout << endl << endl;

	////Niedokladne
	//cout << "Niedokladne" << endl;
	//for (int i = 0; i < m_txt.length() - m_substring.length(); i++)
	//{
	//	if (hasz(i) == m_hw)
	//	{
	//		cout << i << " ";
	//	}
	//}
	//cout << endl << endl;
}
KR::KR()
{
}
KR::~KR()
{
}