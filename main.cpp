#include <iostream>
#include <time.h>
#include <vector>
#include <conio.h>
#include <utility> 


using namespace std;



//time
int game_time;
int old_game_time;
int game_speed = 100;

//map 
int map_x;
int map_y;
vector<vector<string>> map;

//game 


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
int snake_lenght=1;
int apple_X;
int apple_Y;
bool apple_Exist = false;
bool game_Start = true;
int game_score = 0;

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

	//start game time 
	old_game_time = clock()/game_speed;

}


void Start()
{
	/*cout << "enter the x and yszy: \n x:";
	cin >> map_x;
	cout << " y:";
	cin >> map_y;*/

	map_x = 20;
	map_y = 15;

	player_X = map_x / 2;
	player_Y = map_y / 2;

	CreateMap();
}


void Build() {
	system("CLS");

	//build snake tail
	for (int i = 0; i < snake_Body.size() - 1; ++i) {
		const auto& segment = snake_Body[i];
		map[segment.first][segment.second] = "o";
	}

	//build map and score
	for (int y = 0; y < map_y; y++) {
		for (int x = 0; x < map_x;x++) {

			cout << map[y][x];

		}
		cout << "\n";
	}

	cout << "SCORE: " << game_score << " | GAME TIME: "<< game_time/10<<"\n";

	if (game_Start == false) {
		cout << "GAME OVER";
	}
	

}


void Input() {
	if (_kbhit()){
		//zapisuje sie czas interwalowy
		
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
	//end game after collision with a snake tail   
	for (int i = 0; i < snake_Body.size() - 1; ++i) {
		const auto& segment = snake_Body[i];
		if (player_X == segment.second && player_Y == segment.first) {
			game_Start = false;
		}
	}
	//action after eat apple 
	if (player_X == apple_X and player_Y == apple_Y and apple_Exist == true) {
		apple_Exist = false;
		game_score += 10;
		snake_lenght += 1;
	}
}


void Apple() {
	while (!apple_Exist) {
		srand(time(0));
		apple_X = rand() % map_x;
		apple_Y = rand() % map_y;
		int suitablePlace = true;
		for (auto segment : snake_Body) {
			if (apple_X == segment.second and apple_Y == segment.first) {
				suitablePlace = false;
			}
		}

		if (suitablePlace) {
			map[apple_Y][apple_X] = "X";
			apple_Exist = true;
		}

	}

}


int main() {
	
	Start();

	while (true) {
		//all time 
		game_time = clock()/game_speed;

		Input();
		
		//intervals 
		if (game_time != old_game_time and game_Start) {
			old_game_time = game_time;

			
			Movement();
			Apple();
			Triger();
			Build();
		}
	}



	return 0;
}