#include <iostream>
#include <cstdlib>
#include <time.h>

const int M = 10;
const int N = 10;

using namespace std;

class field
{
	bool mine;
	bool covered;
	bool flague;
public:
	field();
	void place_mine();
	void Uncover();
	void change_flague();
	void info();
	bool isflag();
	bool iscovered();
	bool ismine();
};

field::field()
{
	mine = false;
	covered = true;
	flague = false;
}

void field::info() // tylko do debugowania
{
	cout << "[" << mine << !covered << flague << "]";
}


class Plansza
{
	field tab[M][N];
public:
	Plansza();
	void deploy_mines(int n, bool random);
	void show_plansza();
	bool hasMine(int x, int y);
	int count_mines(int x, int y);
	void display();
	void debug_display();
	void reveal(int x, int y);
	bool iscovered(int x, int y);
	void change_flague(int x, int y);
};

Plansza::Plansza()
{
	;
}

void saper(Plansza pole);

int main()
{
	srand(time(0)); //umozliwia losowe rozmieszczenie za karzdym uruchomieniem programu
	Plansza pole;
	pole.deploy_mines(1, 1);
	pole.display();
	saper(pole);
	system("pause");

	return 0;
}

void saper(Plansza pole)
{
	int x, y;
	int ilosc_min = 0;
	for (int i = 0;i < M;i++) //zliczam miny na planszy
	{
		for (int j = 0;j < N;j++)
		{
			if (pole.hasMine(i, j))
				ilosc_min++;
		}
	}
	bool koniec_gry = false;
	bool sukces = false;
	while (!koniec_gry)
	{
		system("cls");
		pole.display();
		int ilosc_zakrytych = 0;
		cout << "1. odkryj pole x,y" << endl;
		cout << "2. zmien flage x,y" << endl;
		int akcja;
		cin >> akcja;
		switch (akcja) // menu z 2 opcjami
		{
		case 1:
		{
			cout << "Podaj pole 'x' do odkrycia: ";
			cin >> x;
			cout << "Podaj pole 'y' do odkrycia: ";
			cin >> y;
			pole.reveal(x, y);
			if (pole.hasMine(x, y)) //jezeli odkryjemy pole z mina nastepuje koniec gry
			{
				koniec_gry = true;
			}
		}
		break;
		case 2:
		{
			cout << "Podaj pole 'x' do zmiany flagi: ";
			cin >> x;
			cout << "Podaj pole 'y' do zmiany flagi: ";
			cin >> y;
		}
		pole.change_flague(x, y);
		break;
		default:
			cout << "Brak takiej opcji!" << endl;
			system("pause");
			break;
		}
		for (int i = 0;i < M;i++) // zliczam zawsze od nowa ilosc zakrytych
		{
			for (int j = 0;j < N;j++)
			{
				if (pole.iscovered(i, j))
					ilosc_zakrytych++;
			}
		}
		if (ilosc_min == ilosc_zakrytych) // jezeli jest tyle samo zakrytych co min koncze gre i wygrywam
		{
			koniec_gry = true;
			sukces = true;
		}
	}
	system("cls");
	if (sukces)
		cout << "Wygrana"<<endl;
	else
		pole.display();

}

void Plansza::change_flague(int x, int y)
{
	tab[x][y].change_flague();
}

bool Plansza::iscovered(int x, int y)
{
	return tab[x][y].iscovered();
}

void field::place_mine() //umieszcza mine na polu
{
	mine = true;
}

void field::Uncover() // odkrywa pole
{
	covered = false;
}

void field::change_flague() // zmienia flage na polu
{
	if (!flague)
		flague = true;
	else
		flague = false;
}


void Plansza::reveal(int x, int y)
{
	tab[x][y].Uncover();
	//	if(x<0||x>=M||)
	if (!count_mines(x, y))
	{
		int i = 0; //zmienne ktore beda pomocne przy ilosci pol w zaleznosci od tego ktore pole odkrywamy (6 przy krawedzi, 4 w rogu, 9 w srodku)
		int j = 0;
		int i_max = 3;
		int j_max = 3;
		if (x == 0) //dzieki tym zmiennym moge wszystkie mozliwosci wykonac w jednej petli
		{
			i = 1;
		}
		if (y == 0)
		{
			j = 1;
		}
		if (x == M - 1)
		{
			i_max = 2;
		}
		if (y == N - 1)
		{
			j_max = 2;
		}
		for (int i_pom = i;i_pom < i_max;i_pom++) //jestem w stanie przeszukiwac 3x3,2x3,3x2,1x3,3x1,1x2,2x1 i 1x1
		{
			for (int j_pom = j;j_pom < j_max;j_pom++) //dzieki i_pom i j_pom jestem w stanie korygowac i ustawiac wczesniej zadana wartosc
			{
				//tab[x-1+i_pom][y-1+j_pom].Uncover(); //stara opcja
				if (tab[x - 1 + i_pom][y - 1 + j_pom].iscovered()) //nowa lepsza jezeli pobliskie pole jest zakryte to rekurenkcyjnie wywoluja ta funkcje na tamtym polu
					reveal(x - 1 + i_pom, y - 1 + j_pom);
			}
		}
	}
}

int Plansza::count_mines(int x, int y)
{
	int ile_min = 0;
	int i = 0; //zmienne ktore beda pomocne przy ilosci pol w zaleznosci od tego ktore pole odkrywamy (6 przy krawedzi, 4 w rogu, 9 w srodku)
	int j = 0;
	int i_max = 3;
	int j_max = 3;
	if (x == 0) //dzieki tym zmiennym moge wszystkie mozliwosci wykonac w jednej petli
	{
		i = 1;
	}
	if (y == 0)
	{
		j = 1;
	}
	if (x == M - 1)
	{
		i_max = 2;
	}
	if (y == N - 1)
	{
		j_max = 2;
	}
	for (int i_pom = i;i_pom < i_max;i_pom++) //jestem w stanie przeszukiwac 3x3,2x3,3x2,1x3,3x1,1x2,2x1 i 1x1
	{
		for (int j_pom = j;j_pom < j_max;j_pom++) //dzieki i_pom i j_pom jestem w stanie korygowac i ustawiac wczesniej zadana wartosc
		{
			if (hasMine(x - 1 + i_pom, y - 1 + j_pom))
				ile_min++;
		}
	}
	return ile_min;
}

bool field::ismine() //sprawdza czy pole ma mine
{
	if (mine)
		return true;
	else
		return false;
}

bool Plansza::hasMine(int x, int y) // sprawdza czy konkretne pole ma mine
{
	if (tab[x][y].ismine())
		return true;
	else
		return false;
}

void Plansza::display() //wywietlanie planszy
{
	for (int i = 0;i < M;i++)
	{
		for (int j = 0;j < N;j++)
		{
			if (tab[i][j].iscovered() && !tab[i][j].isflag()) //gdy pole jest zakryte i nie ma flagi
				cout << "[.]";
			else if (tab[i][j].iscovered() && tab[i][j].isflag()) //gdy pole jest zakryte i ma flage
				cout << "[?]";
			else if (!tab[i][j].iscovered() && !count_mines(i, j)) //gdy pole jest odkryte i nie ma w poblizu min
				cout << "[ ]";
			else if (!tab[i][j].iscovered() && count_mines(i, j) && !hasMine(i, j)) //gdy pole jest odkryte ale w poblizu sa miny
				cout << "[" << count_mines(i, j) << "]";
			else if (!tab[i][j].iscovered() && hasMine(i, j)) //gdy pole jest odkryte i ma mine
				cout << "[x]";
		}
		cout << endl;
	}

}

void Plansza::debug_display()
{
	for (int i = 0;i < M;i++)
	{
		for (int j = 0;j < N;j++)
			tab[i][j].info();
	}
}

bool field::iscovered() //sprawdzam czy jest zakryte
{
	return covered;
}

bool field::isflag() //sprawdzam czy ma flage
{
	return flague;
}

void Plansza::deploy_mines(int n, bool random)
{
	bool good = true;
	if (n > M*N) // sprawdzam czy nie jest za duzo min
	{
		good = false;
		cout << "Za duzo min" << endl;
	}
	if (random&&good) // jezeli wybralismy rozmieszczenie losowe rozmieszczamy miny z rozna szansa do momentu skonczenia sie min
	{
		while (good && n > 0)
		{
			for (int i = 0; i < M; i++)
			{
				for (int j = 0; j < N; j++)
				{
					if (n>0 && !tab[i][j].ismine()) // jezeli nie ma miny losujemy
						if (rand() % 10 == 0)
						{
							tab[i][j].place_mine();
							n--;
						}

				}
			}
		}
	}
	else if (!random) //jezeli wylaczymy random miny sa ukladane po przekatnej
	{
		int i = 0;
		int j = 0;
		while (i < M && j < N)
		{
			tab[i][j].place_mine();
			i++;
			j++;

		}
	}
}
