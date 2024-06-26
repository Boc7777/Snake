#include <iostream>
#include <time.h>
#include <vector>
#include <conio.h>
#include <utility> 

using namespace std;

//czas
int game_time;
int old_game_time;
int game_speed = 200;

//map 
int map_x;
int map_y;
vector<vector<string>> map;

//game 
bool game_Start = false;

//Movement 
int ascii_Duration;
enum player_Direction_Options
{
	LEFT,TOP,RIGHT,BOTTOM
};
player_Direction_Options player_Direction;


//Gameplay
int player_X;
int player_Y;
int snake_lenght;

vector<pair<int, int>> snake_Body;


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


void Start()
{
	/*cout << "podaj x i y twojej plaszy: \n x:";
	cin >> map_x;
	cout << " y:";
	cin >> map_y;
	cout << "nacisnij WSAD";*/

	map_x = 20;
	map_y = 15;

	player_X = map_x / 2;
	player_Y = map_y / 2;

	CreateMap();
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
	if (_kbhit()){
		//po pierwszym nacisnieciu gra sie zaczyna 
		game_Start = true;
		//zapisuje sie czas interwalowy
		old_game_time = clock();



		ascii_Duration = _getch();
		if (ascii_Duration == 97 and player_Direction != RIGHT) {
			player_Direction = LEFT;
		}
		else if (ascii_Duration == 119 and player_Direction !=BOTTOM ) {
			player_Direction = TOP;
		}
		else if (ascii_Duration == 100 and player_Direction != LEFT) {
			player_Direction = RIGHT;
		}
		else if (ascii_Duration == 115 and player_Direction != TOP) {
			player_Direction = BOTTOM;
		}
	}	
}


void Movement(){

	//przechodzenie przez sciany i chodzenie 
	if(player_Direction == LEFT){
		if (player_X != 0) {
			player_X -= 1;
		}
		else {
			player_X = map_x - 1;
		}

		map[player_Y][player_X] = "O";
		/*snake_Body.push_back(make_pair(player_Y,player_X));*/
	}

	else if (player_Direction == TOP) {
		if (player_Y != 0) {
			player_Y -= 1;
		}
		else {
			player_Y = map_y - 1;
		}
		map[player_Y][player_X] = "O";
	}

	else if (player_Direction == RIGHT) {
		if (player_X != map_x - 1) {
			player_X += 1;
		}
		else {
			player_X = 0;
		}
		map[player_Y][player_X] = "O";
	}

	else if (player_Direction == BOTTOM) {
		if (player_Y != map_y - 1) {
			player_Y += 1;
		}
		else {
			player_Y = 0;
		}
		map[player_Y][player_X] = "O";
	}

}


int main() {
	
	Start();

	while (true) {
		//caly czas
		game_time = clock();

		Input();
		
		//wlacza sie co game_speed 
		if (game_time == old_game_time + game_speed and game_Start == true) {
			old_game_time = game_time;

			Movement();
			Build();
			
		}
		
	}

	return 0;
}