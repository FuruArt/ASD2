//*********************************************************************************************
//		Autor:				Marcin Jastrzêbski												***
//		Kontakt:			jaczomb@gmail.com												***
//		Data:				21.03.2017														***
//		Nazwa:				HASHTABLE														***
//		wersja:				.v2							ob³uga cin, cout					***											***
//*********************************************************************************************

#include <iostream>
#include <string>

using namespace std;


class Object
{
public:
	//zmienne
	long key_;
	string txt_;
	char flag_; //{'E', 'F', 'C'} ::: 'E' = empty, 'F'= field, 'C' =chain

	//metody
	//konstruktor, destruktor
	Object(long _k, string _s, char _f = 'F');
	Object();
	~Object();
};

class Hashtable
{
public:
	//zmienne
	Object * tab_;
	Object * tab2_;
	long size_;
	long n_; 

	//metody
	void Size(long _size);
	void Add(Object& _object);
	void Delete(long _k);
	void Print();

	//kostruktor, destruktor
	Hashtable();
	~Hashtable();
};
//*********************************************************************************************
//*********************************************************************************************
int main()
{
	//zmienne
	char bufer[16];
	long lon; //zmienna do petli while
	string s; //zmienna do petli while
	bool petla = true;

	//*******

	cin >> bufer;
	long przypadki = atol(bufer);

	for (int i = 0; i < przypadki; i++)
	{
		Hashtable h_;
		while (petla)
		{
			//Hashtable h_;
			cin >> bufer;

			if (string(bufer) == "size")
			{
				cin >> bufer;
				lon = atol(bufer);
				h_.Size(lon);
			}
			if (string(bufer) == "add")
			{
				cin >> bufer;
				lon = atol(bufer);
				cin >> bufer;
				s = string(bufer);
				Object o(lon, s);
				h_.Add(o);
			}
			if (string(bufer) == "delete")
			{
				cin >> bufer;
				lon = atol(bufer);
				h_.Delete(lon);
			}
			if (string(bufer) == "print")
			{
				h_.Print();
			}
			if (string(bufer) == "stop")
			{
				delete[]h_.tab_;
				delete[]h_.tab2_;
				break;
			}
		}
	}

	//system("PAUSE");
	return 0;
}
//*********************************************************************************************
//*********************************************************************************************
//***************************************************************
Object::Object(long _k, string _s, char _f) :key_(_k), txt_(_s), flag_(_f)
{

}
//***************************************************************
Object::Object()
{
}
//***************************************************************
Object::~Object()
{
}
//***************************************************************
void Hashtable::Size(long _size)
{
	//budowanie tablicy i czyszczenie
	size_ = _size;
	tab_ = new Object[_size];

	tab2_ = new Object[_size];

	for (int i = 0; i < _size; i++)
	{
		tab_[i] = { NULL, "NULL", 'E' };
		tab2_[i] = { NULL, "NULL", 'E'};
	}
}
//***************************************************************
void Hashtable::Add(Object& _object)
{
	n_ = _object.key_%size_;
	//tab1
	for (int i = n_; i < size_; i++)
	{
		if (tab_[i].flag_=='E')
		{
			// je¿eli flaga jest empty to wpisuje od razu
			tab_[i] = { _object.key_, _object.txt_, _object.flag_ };
			
			if(tab_[i-1].key_%size_==n_ && tab_[i-1].flag_=='F')
				tab_[i-1].flag_ = 'C';
			
			//pêtla siê przerywa w momencie wpisania do tablicy wszystkich wartosci
			break;
		}

		//tutaj else if nie przypisalo nigdzie to od nowa sprawdzanie petli
		else if (i == size_ -1)
		{
			//tab_[i+1].flag_ = 'C';
			for (int j = 0; j < size_; j++)
			{
				if (tab_[j].flag_ == 'E')
				{
					// je¿eli flaga jest empty to wpisuje od razu
					tab_[j] = { _object.key_, _object.txt_, _object.flag_ };
					
					if (j > 0 && tab_[j - 1].key_%size_ == n_ && tab_[j].flag_ == 'F')
					{
						tab_[j - 1].flag_ = 'C';
					}

					//przypadek dla flagi z ostatniego miejsca w tablicy
					if (j == 0 && tab_[j].key_%size_ != j)
					{
						tab_[i].flag_ = 'C';
					}
					//pêtla siê przerywa w momencie wpisania do tablicy wszystkich wartosci
					break;
				}

				//jak nie przypasuje w odpowiednim miejscu to zmienia tylko flage na C
				else
				{
					tab_[j].flag_ = 'C';
				}
			}
		}

		else
		{
			//jak nie przypasuje w odpowiednim miejscu to zmienia tylko flage na C
			tab_[i].flag_ = 'C';
		}

	}
	//tab2
	for (int i = 0; i < size_; i++)
	{
		if (tab2_[i].flag_ == 'E')
		{
			tab2_[i] = { _object.key_, _object.txt_, _object.flag_ };
			break;
		}
	}
}
//***************************************************************
void Hashtable::Delete(long _k)
{
	//czyszczenie wpisu w tab2
	n_ = _k%size_;
	for (int i = 0; i < size_; i++)
	{
		if (tab2_[i].key_ == _k)
		{
			//usuwam wpis
			tab2_[i] = { NULL, "NULL", 'E' };
		}

	}

	//czyszczenie calej tab1
	for (int i = 0; i < size_; i++)
	{
		tab_[i] = { NULL, "NULL", 'E' };
	}

	//wysortowanie tablicy pomocniczej pod wzgledem dodania
	for (int i = 0; i < size_; i++)
	{
		if (tab2_[i].flag_ == 'E')
		{
			for (int j = i; j < size_; j++)
			{
				if (tab2_[j].flag_ != 'E')
				{
					tab2_[i] = tab2_[j];
					tab2_[j] = { NULL, "NULL", 'E' };
					break;
				}
			}
		}
	}

	////przepisanie
	for (int k = 0; k < size_; k++)
	{
		n_ = tab2_[k].key_%size_;
		
		if (tab2_[k].flag_ != 'E')
		{
			for (int i = n_; i < size_; i++)
			{
				if (tab_[i].flag_ == 'E')
				{
					// je¿eli flaga jest empty to wpisuje od razu
					tab_[i] = tab2_[k];/*{ tab2_[k].key_, tab2_[k].txt_, tab2_[k].flag_ };*/

					if (tab_[i - 1].key_%size_ == n_ && tab_[i - 1].flag_ == 'F')
						tab_[i - 1].flag_ = 'C';
					//pêtla siê przerywa w momencie wpisania do tablicy wszystkich wartosci
					break;
				}

				//tutaj else if nie przypisalo nigdzie to od nowa sprawdzanie petli
				//moze jesli i==size
				else if (i == size_ - 1)
				{
					for (int j = 0; j < size_; j++)
					{
						if (tab_[j].flag_ == 'E')
						{
							// je¿eli flaga jest empty to wpisuje od razu
							tab_[j] = tab2_[k];/* { _object.key_, _object.txt_, _object.flag_ };*/

							if (j > 0 && tab_[j - 1].key_%size_ == n_ && tab_[j].flag_ == 'F')
								tab_[j - 1].flag_ = 'C';

							//przypadek dla flagi z ostatniego miejsca w tablicy
							if (j == 0 && tab_[j].key_%size_ != j)
							{
								tab_[i].flag_ = 'C';
							}
							//pêtla siê przerywa w momencie wpisania do tablicy wszystkich wartosci
							break;
						}
						//jak nie przypasuje w odpowiednim miejscu to zmienia tylko flage na C
						else
						{
							tab_[j].flag_ = 'C';
						}
					}
				}

				else
				{
					//jak nie przypasuje w odpowiednim miejscu to zmienia tylko flage na C
					tab_[i].flag_ = 'C';
				}

			}
		}
	}

}
//***************************************************************
void Hashtable::Print()
{
	for (int i = 0; i < size_; i++)
	{
		if (tab_[i].key_ != NULL)
		{
			cout << i << " " << tab_[i].key_ << " " << tab_[i].txt_ << endl; //bez flag		//COUT
		}
		//cout << i << " " << tab_[i].key_ << " " << tab_[i].txt_ << " " << tab_[i].flag_ << " " << endl; // z flagami
	}
	cout << endl;																				//COUT

	////tablica pomocnicza
	//for (int i = 0; i < size_; i++)
	//{
	//	cout << i << " " << tab2_[i].key_ << " " << tab2_[i].txt_ << " " << tab2_[i].flag_ << " " << endl;
	//}
	//cout << endl;
}
//***************************************************************
Hashtable::Hashtable()
{
}
//***************************************************************
Hashtable::~Hashtable()
{
}
//***************************************************************