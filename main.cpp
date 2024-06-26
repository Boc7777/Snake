#include <iostream>
#include <time.h>
#include <vector>
#include <conio.h>

using namespace std;

//czas
int game_time;
int old_game_time;
int game_speed = 300;

//map 
int map_x;
int map_y;
vector<vector<string> > map;

//game 
bool game_Start = false;


void CreateMap() {
	vector<string> row; 

	for (int y = 0; y < map_y; y++) {
		for (int x = 0; x < map_x;x++) {
			row.push_back(".");
		}
		map.push_back(row);
		row = {};
	}

}


void Build() {
	system("CLS");

	for (int y = 0; y < map_y; y++) {
		for (int x = 0; x < map_x;x++) {

			cout << map[y][x];

		}
		cout << "\n";
	}
}



void Input() {
	/*cout << _getch();*/
}



void Move() {

}








int main() {
	//tylko raz
	cout << "podaj x i y twojej plaszy: \n ";
	cin >> map_x;
	cin >> map_y;

	old_game_time = clock();
	CreateMap();

	game_Start = true;
	while (game_Start) {
		//caly czas
		game_time = clock();

		Input();

		//wlacza sie co game_speed 
		if (game_time == old_game_time + game_speed) {
			old_game_time = game_time;


			Build();
			



		}
		
	}

	return 0;
}