#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <string>
using std::string;
using std::getline;

#include <algorithm>
using std::transform;

#include <cctype>
using std::tolower;

#include <limits>

void print_man(int remaining_trys) {

	int backslash = 92; //Used to account for compiler warnings with printing "\\\|"


	switch(remaining_trys) {
	
		case 7:
			cout << "    ----" << endl;
			cout << "    |  |" << endl;
			cout << "    |   " << endl;
			cout << "    |   " << endl;
			cout << "    |   " << endl;
			cout << "    |   " << endl;
			cout << "    |   " << endl;
			cout << "---------" << endl;
			break;

		case 6:
			cout << "    ----" << endl;
			cout << "    |  |" << endl;
			cout << "    |  O " << endl;
			cout << "    |   " << endl;
			cout << "    |   " << endl;
			cout << "    |   " << endl;
			cout << "    |   " << endl;
			cout << "---------" << endl;
			break;
		
		case 5:
			cout << "    ----" << endl;
			cout << "    |  |" << endl;
			cout << "    |  O " << endl;
			cout << "    |  | " << endl;
			cout << "    |   " << endl;
			cout << "    |   " << endl;
			cout << "    |   " << endl;
			cout << "---------" << endl;
			break;

		case 4:
			cout << "    ----" << endl;
			cout << "    |  |" << endl;
			cout << "    |  O " << endl;
			cout << "    | " << (char) backslash << "| " << endl;
			cout << "    |   " << endl;
			cout << "    |   " << endl;
			cout << "    |   " << endl;
			cout << "---------" << endl;
			break;

		case 3:
			cout << "    ----" << endl;
			cout << "    |  |" << endl;
			cout << "    |  O " << endl;
			cout << "    | " << (char) backslash << "|/" << endl;
			cout << "    |   " << endl;
			cout << "    |   " << endl;
			cout << "    |   " << endl;
			cout << "---------" << endl;
			break;

		case 2:
			cout << "    ----" << endl;
			cout << "    |  |" << endl;
			cout << "    |  O " << endl;
			cout << "    | " << (char) backslash << "|/" << endl;
			cout << "    |  |" << endl;
			cout << "    |   " << endl;
			cout << "    |   " << endl;
			cout << "---------" << endl;
			break;

		case 1:
			cout << "    ----" << endl;
			cout << "    |  |" << endl;
			cout << "    |  O " << endl;
			cout << "    | " << (char) backslash << "|/" << endl;
			cout << "    |  |" << endl;
			cout << "    | /  " << endl;
			cout << "    |   " << endl;
			cout << "---------" << endl;
			break;

		case 0:
			cout << "    ----" << endl;
			cout << "    |  |" << endl;
			cout << "    |  O " << endl;
			cout << "    | " << (char) backslash << "|/" << endl;
			cout << "    |  |" << endl;
			cout << "    | / " << (char) backslash << endl;
			cout << "    |   " << endl;
			cout << "---------" << endl;
			break;
	}
}

string word_to_guess(bool has_played) {
	
	string mystery_word;
	if(has_played) { //if player is playing again, clear buffer
		cin.clear();
		cin.ignore(1000, '\n');
	}

	cout << "Enter a word or phrase for another player to guess!: ";
	getline(cin, mystery_word);

	return mystery_word;
}

//Used with convert_lowercase()
struct to_lower {
	int operator() (int ch) {
		return tolower(ch);
	}
};

//Used with struct to_lower
//Converts a string to all lowercase letters
string convert_lowercase(string word){
	transform(word.begin(), word.end(), word.begin(), to_lower());

	return word;
}

//Counts letters minus spaces and grammatical markings
int word_length(string word) {
	
	int length = word.length();

	for(string::size_type i = 0; i < word.length(); i++) {
		if((int) word[i] < 97 || (int) word[i] > 122)
			length--;
	}

	return length;	
}

struct element {
	int letter; //REMEMBER: convert to ASCII first before using
	bool chosen; //bool for if letter has been previously chosen
	bool in_phrase; //bool for if the letter is present in the mystery phrase
};

void fill_element(element *data, string word) {

	int ascii = 97; //lowercase "a" on ASCII chart

	for(int i = 0; i < 26; i++) {
		data[i].letter = ascii;
		data[i].chosen = false;
		data[i].in_phrase = false;
		for(int j = 0; j < word.length(); j++) {
			if((int) word[j] == ascii) {
				data[i].in_phrase = true;
				break;
			}
		}
		ascii++;
	}
}

int error_check(char letter, int ascii) {
	
	if(ascii >=65 && ascii <= 90) //if uppercase, make lowercase
		ascii += 32;
	
	while(ascii < 97 || ascii > 122) { //Check if a letter
		cout << "Enter a letter only: ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> letter;
		ascii = (int) letter;
		if(ascii >=65 && ascii <= 90) //if uppercase, make lowercase
			ascii += 32;
	}
	
	return ascii;
}

void check_chosen(int &ascii, element *data) {
	
	char letter;	

	while(data[ascii - 97].chosen) {
		cout << "You've already selected " << (char) ascii
		     << ", choose another letter: ";
		cin >> letter;
		ascii = error_check(letter, (int) letter);
	}
}

int choose_letter(element *data) {
	
	char letter;
	int ascii;	

	cout << endl << "Choose a letter: ";
	cin >> letter;

	ascii = error_check(letter, (int) letter); //converts to ASCII and error checks

	check_chosen(ascii, data); //checks if letter was already picked
	data[ascii - 97].chosen = true; //letter has been chosen

	return ascii;
}

void is_present(int ascii, element *data, int &remaining_trys, bool &is_correct) {
	
	if(data[ascii - 97].in_phrase) {
		is_correct = true;
	}
	else {
		is_correct = false;
		remaining_trys--;
	}
}

void print_stats(element *data, int remaining_trys) {
	
	cout << "Remaining Trys: " << remaining_trys << endl;

	cout << "Chosen letters: ";
	for(int i = 0; i < 26; i++) {
		if(data[i].chosen)
			cout << (char) data[i].letter << " ";
	}
	cout << endl;
}

void print_phrase(string word, element *data) {

	for(int i = 0; i < word.length(); i++) {
		if((int) word[i] >= 97 && (int) word[i] <= 122) { //if a letter
			if(data[(int) word[i] - 97].chosen) //if letter has been chosen
				cout << word[i]; //print the letter
			else
				cout << "_ "; //otherwise print an underscore
		}
		else
			cout << word[i]; //spaces and grammar markings
	}
	
	cout << endl;
}

void check_win(bool &win_game, element *data, string word) {
	
	for(int i = 0; i < word.length(); i++) { //cycle through each letter in phrase
		if((int) word[i] >= 97 && (int) word[i] <= 122) { //if a letter
			if(data[(int) word[i] - 97].chosen != data[(int) word[i] - 97].in_phrase) //if player hasn't selected a letter that is in the phrase
				return;
		}
	}
	win_game = true; //All letters in phrase have been selected
}

void print_correct(bool is_correct) {
	
	if(is_correct)
		cout << "Nice guess!" << endl << endl;
	else
		cout << "Incorrect" << endl << endl;
}

//Handles spacing
void aesthetics(bool &first_turn, bool is_correct) {

	if(first_turn) {
		first_turn = false;
		cout << endl << endl;
	}
	else
		print_correct(is_correct);
}

void game_engine() {

	bool play_again = false;
	bool has_played = false;
	bool is_correct;

	do {
		int remaining_trys = 7;
		int letter; //letter's ASCII value
		bool win_game = false;
		bool first_turn = true;

		system("clear");

		string mystery_word = word_to_guess(has_played); //set word
		string lo_mystery_word = convert_lowercase(mystery_word); //make it lowercase
		element *data = new element[26]; //array of structs for each letter
		fill_element(data, lo_mystery_word); //fills each struct value in the array

		do {
			system("clear");

			//print to screen
			aesthetics(first_turn, is_correct);
			print_stats(data, remaining_trys);
			print_man(remaining_trys);
			print_phrase(lo_mystery_word, data);

			check_win(win_game, data, lo_mystery_word);
			if(win_game)
				break;
			letter = choose_letter(data); //Player chooses letter
			is_present(letter, data, remaining_trys, is_correct);

		} while(remaining_trys != 0);

		

		if(win_game)
			cout << "Congrats, you win!!!" << endl;
		else {
			system("clear");
			print_correct(is_correct);
			print_stats(data, remaining_trys);
			print_man(remaining_trys);
			print_phrase(lo_mystery_word, data);
			cout << "The correct word/phrase was: " << mystery_word << endl; 
			cout << "Sorry, you lose :(" << endl;
		}

		cout << endl;
		cout << "Would you like to play again? (1 - yes, 0 - no): ";
		cin >> play_again;

		if(play_again)
			has_played = true;

		delete[] data;

	} while(play_again);

	cout << endl << "Goodbye!" << endl << endl;

}

int main() {

	game_engine();

	//Some future ideas:
	//TODO clear buffer of extra letters in choose_letter
	//TODO randomly select a word from a text file for the phrase

	return 0;
}
