#include <iostream>
#include <time.h>
#include <vector>
#include <conio.h>
#include <utility> 

#include <filesystem>
#include <fstream>
#include <string>
namespace fs = std::filesystem;



using namespace std;



//time
int game_time;
int old_game_time;
int game_speed = 100;

//map 
int map_x;
int map_y;
vector<vector<string>> map;


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
bool game_Start;
bool game_Over_flag;
int game_score = 0;
vector<pair<int, int>> snake_Body;
vector<pair<int, int>> walls;


//file system
vector<string> map_List;
string choosen_Map;


//player may choose custom map or load from txt file 
int Player_choose() {
	int choose;
	while (true) {
		system("CLS");
		cout << "custom_map - 1 \n" << "map - 2 \n" ;
		cin >> choose;
		if (choose == 1 || choose == 2) {
			return choose;
		}
	}
}

//load txt files from maps dir 
void get_Map_List() {
	string path = "./maps";
	map_List = {};
	for (const auto& entry : fs::directory_iterator(path)) {
		map_List.push_back(entry.path().string());
	}
}

//player may choose which map he want to play 
void choose_Map() {
	bool wybor = false;


	while (!wybor) {
		int i = 0;
		int amount_of_maps = map_List.size();
		int choose;
		system("CLS");


		cout << "select map \n";
		for (auto ele : map_List) {
			cout << i << ": " << ele << "\n";
			i += 1;
		}
		cin >> choose;

		if (choose >= 0 && choose < amount_of_maps) {
			system("CLS");
			choosen_Map = map_List[choose];
			wybor = true;
		}

		
	}


}


void load_map() {

	string row;
	vector<string> row_to_push;
	string znak;

	ifstream loading_Map(choosen_Map);
	
	while ( getline(loading_Map, row) ){
		
		for (int i=0;i < row.size();i++) {
			znak = row[i];
			row_to_push.push_back(znak);
		}
		map.push_back(row_to_push);

		row_to_push = {};
	}
	


	loading_Map.close();
}

//checking txt map file has a good format to load a map 
void validate_map_format() {
	int validate_columns = map[0].size();
	int counter_columns = 0;

	bool columns_ok = true;


	for (int y = 0; y < map.size(); y++) {
		counter_columns = map[y].size();

		if (counter_columns != validate_columns) {
			columns_ok = false;
		}
	
	}

	if (columns_ok) {
		map_x = validate_columns;
		map_y = map.size();

		player_X = map_x / 2;
		player_Y = map_y / 2;

		game_Start = true;
	}
	else {
		system("CLS");
		cout << "BAD MAP FORMAT";
	}

}

//upload all walls which are in map in to walls vector 
void set_walls() {
	for (int y = 0; y < map_y; y++) {
		for (int x = 0; x < map_x;x++) {

			if (map[y][x] == "M") {
				walls.push_back(make_pair(y, x));
			}
		}
	}
}


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
	int decision = Player_choose();

	system("CLS");
	cout << "choose your game speed \nthe lower the number, the faster the game \npreferably choose more than 100 \n";
	cin >> game_speed;


	if (decision == 1) {
		system("CLS");
		cout << "enter the x and y: \n x:";
		cin >> map_x;
		cout << " y:";
		cin >> map_y;

		player_X = map_x / 2;
		player_Y = map_y / 2;

		CreateMap();
		game_Start = true;
	}
	
	else if (decision == 2) {

		get_Map_List();
		choose_Map();
		load_map();
		validate_map_format();
		set_walls();
	}
	
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

	cout << "SCORE: " << game_score << "\n";

	if (game_Start == false) {
		cout << "GAME OVER";
	}
	

}


void Input() {
	if (_kbhit()){
		//zapisuje sie czas interwalowy
		
		ascii_Duration = _getch();
		if (ascii_Duration == 97 && player_Direction != RIGHT && last_Move!= RIGHT) {
			player_Direction = LEFT;
		}
		else if (ascii_Duration == 119 && player_Direction !=BOTTOM && last_Move!=BOTTOM) {
			player_Direction = TOP;
		}
		else if (ascii_Duration == 100 && player_Direction != LEFT && last_Move!= LEFT) {
			player_Direction = RIGHT;
		}
		else if (ascii_Duration == 115 && player_Direction != TOP && last_Move!= TOP) {
			player_Direction = BOTTOM;
		}
	}	

}


void Movement(){

	//deleting tail 
	if (snake_Body.size() > snake_lenght) {
		map[snake_Body[0].first][snake_Body[0].second] = ".";
		snake_Body.erase(snake_Body.begin());
	}


	//walking through walls
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
			game_Over_flag = true;
		}
	}
	//action after eat apple 
	if (player_X == apple_X && player_Y == apple_Y && apple_Exist == true) {
		apple_Exist = false;
		game_score += 10;
		snake_lenght += 1;
	}

	for (auto w : walls) {
		if (player_Y == w.first && player_X == w.second) {
			game_Start = false;
			game_Over_flag = true;
		}
	}
}


void Apple() {
	while (!apple_Exist) {
		srand(time(0));
		apple_X = rand() % map_x;
		apple_Y = rand() % map_y;
		int suitablePlace = true;

		for (auto segment : snake_Body) {
			if (apple_X == segment.second && apple_Y == segment.first) {
				suitablePlace = false;
			}
		}

		for (auto segment : walls) {
			if (apple_X == segment.second && apple_Y == segment.first) {
				suitablePlace = false;
			}
		}

		if (suitablePlace) {
			map[apple_Y][apple_X] = "X";
			apple_Exist = true;
		}

	}

}


void game_Over() {
	string cos;
	cout << "\n type whatever to continue :)";
	cin >> cos;

	game_Over_flag == false;
	snake_lenght = 1;
	apple_Exist = false;
	game_score = 0;

	map = {};
	snake_Body = {};
	walls = {};



	Start();
}





int main() {
	
	Start();

	while (true) {
		//all time 
		game_time = clock()/game_speed;

		Input();
		
		//intervals 
		if (game_time != old_game_time && game_Start) {
			old_game_time = game_time;

			Movement();
			Apple();
			Triger();
			Build();
		}
		else if(game_Over_flag==true && game_Start == false){
			game_Over();
		}
	}
	



	

	
	
	




}