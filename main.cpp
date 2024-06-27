#include <iostream>
#include <time.h>
#include <vector>
#include <conio.h>
#include <utility> 

using namespace std;

//czas
int game_time;
int old_game_time;
int game_speed = 400;

//map 
int map_x;
int map_y;
vector<vector<string>> map;

//game 
bool game_Start = true;

//Movement 
int ascii_Duration;
enum player_Direction_Options
{
	LEFT,TOP,RIGHT,BOTTOM
};
player_Direction_Options player_Direction;
player_Direction_Options last_Move;


//Gameplay
int player_X;
int player_Y;
int snake_lenght =5;

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

	
	for (int i = 0; i < snake_Body.size() - 1; ++i) {
		const auto& segment = snake_Body[i];
		map[segment.first][segment.second] = "o";
	}



	for (int y = 0; y < map_y; y++) {
		for (int x = 0; x < map_x;x++) {

			cout << map[y][x];

		}
		cout << "\n";
	}





	
}


void Input() {
	if (_kbhit()){
		//zapisuje sie czas interwalowy
		old_game_time = clock();



		ascii_Duration = _getch();
		if (ascii_Duration == 97 and player_Direction != RIGHT and last_Move!= RIGHT) {
			player_Direction = LEFT;
		}
		else if (ascii_Duration == 119 and player_Direction !=BOTTOM and last_Move!=BOTTOM) {
			player_Direction = TOP;
		}
		else if (ascii_Duration == 100 and player_Direction != LEFT and last_Move!= LEFT) {
			player_Direction = RIGHT;
		}
		else if (ascii_Duration == 115 and player_Direction != TOP and last_Move!= TOP) {
			player_Direction = BOTTOM;
		}
	}	
}


void Movement(){

	//usuwanie ogona 
	if (snake_Body.size() > snake_lenght) {
		map[snake_Body[0].first][snake_Body[0].second] = ".";
		snake_Body.erase(snake_Body.begin());
	}


	//przechodzenie przez sciany i chodzenie 
	if(player_Direction == LEFT){
		if (player_X != 0) {
			player_X -= 1;
		}
		else {
			player_X = map_x - 1;
		}

		map[player_Y][player_X] = "O";
		last_Move = LEFT;
		snake_Body.push_back(make_pair(player_Y,player_X));
	}

	else if (player_Direction == TOP) {
		if (player_Y != 0) {
			player_Y -= 1;
		}
		else {
			player_Y = map_y - 1;
		}
		map[player_Y][player_X] = "O";
		last_Move = TOP;
		snake_Body.push_back(make_pair(player_Y, player_X));
	}

	else if (player_Direction == RIGHT) {
		if (player_X != map_x - 1) {
			player_X += 1;
		}
		else {
			player_X = 0;
		}
		map[player_Y][player_X] = "O";
		last_Move = RIGHT;
		snake_Body.push_back(make_pair(player_Y, player_X));
	}

	else if (player_Direction == BOTTOM) {
		if (player_Y != map_y - 1) {
			player_Y += 1;
		}
		else {
			player_Y = 0;
		}
		map[player_Y][player_X] = "O";
		last_Move = BOTTOM;
		snake_Body.push_back(make_pair(player_Y, player_X));
	}

}

void Triger() {
	for (int i = 0; i < snake_Body.size() - 1; ++i) {
		const auto& segment = snake_Body[i];
		if (player_X == segment.second && player_Y == segment.first) {
			game_Start = false;
		}
	}

	/*cout << player_X << " " << player_Y << "\n";

	for (const auto& segment : snake_Body) {
		cout << segment.second << " " << segment.first << "||";
	}*/
}


void Apple() {
	cout << rand()%30;
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
			Apple();
			Triger();
			
		}
		if (game_Start == false) {
			cout << "GAME OVER";
		}
		
	}

	return 0;
}