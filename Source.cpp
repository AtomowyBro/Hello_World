#include <iostream>
#include <cstdlib>
#include <time.h>

const int M = 6;
const int N = 5;

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
	bool mina();
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
	void reveal(int x, int y);
};

Plansza::Plansza()
{
	;
}


int main()
{
	srand((0)); //umozliwia losowe rozmieszczenie za karzdym uruchomieniem programu
	Plansza pole;
	pole.deploy_mines(5, 1);
	pole.reveal(0, 0); //popsute
	pole.display();
	cout << pole.count_mines(5, 0) << endl;
	system("pause");
	return 0;
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
	if (!count_mines(x,y))
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
				tab[x-1+i_pom][y-1+j_pom].Uncover();
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

bool field::mina() //sprawdza czy pole ma mine
{
	if (mine)
		return true;
	else
		return false;
}

bool Plansza::hasMine(int x, int y) // sprawdza czy konkretne pole ma mine
{
	if (tab[x][y].mina())
		return true;
	else
		return false;
}

void Plansza::display() //wywietlanie planszy do debugowania
{
	for (int i = 0;i < M;i++)
	{
		for (int j = 0;j < N;j++)
			tab[i][j].info();
		cout << endl;
	}

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
					if (n>0 && !tab[i][j].mina()) // jezeli nie ma miny losujemy
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
