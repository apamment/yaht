#include "Program.h"
#include "DiceSide.h"
#include "Dice.h"
#include <fstream>
#include <string>
#include <cstdio>

extern "C" {
#include "magidoor/MagiDoor.h"
}

bool Program::load_dice() {
	std::ifstream file("ansi/dice.ans");
	std::string line;
	Dice ref_dice;
	if (!file.good()) {
		return false;
	}
	for (int i = 0; i < 6; i++) {
		DiceSide d;
		for (int y = 0; y < 5; y++) {
			if (!std::getline(file, line)) {
				file.close();
				return false;
			}
			d.ansi.push_back(line);
		}
		d.value = i + 1;
		ref_dice.sides.push_back(d);
	}
	file.close();
	ref_dice.keep = false;

	dice.push_back(new Dice(ref_dice));
	dice.push_back(new Dice(ref_dice));
	dice.push_back(new Dice(ref_dice));
	dice.push_back(new Dice(ref_dice));
	dice.push_back(new Dice(ref_dice));

	return true;
}

bool Program::is_there_a(int a) {
	for (int i = 0; i < 5; i++) {
		if (dice.at(i)->active->value == a) {
			return true;
		}
	}

	return false;
}

int Program::play_game() {
	int ones = -1;
	int twos = -1;
	int threes = -1;
	int fours = -1;
	int fives = -1;
	int sixes = -1;
	int upperbonus = 0;
	int threeofakind = -1;
	int fourofakind = -1;
	int fullhouse = -1;
	int smallstraight = -1;
	int largestraight = -1;
	int yahtzee = -1;
	int chance = -1;
	int yahtzeecount = 0;
	
	md_clr_scr();
	md_sendfile("ansi/back.ans", 0);
	while (true) {
		for (int turn = 0; turn < 3; turn++) {
			for (int i = 0; i < 5; i++) {
				if (dice.at(i)->keep == false) {
					dice.at(i)->roll();
					dice.at(i)->display(8, i * 10 + 3);
				}
			}
			md_set_cursor(14, 7);
			md_printf("`bright cyan`1`white`");

			md_set_cursor(14, 17);
			md_printf("`bright cyan`2`white`");

			md_set_cursor(14, 27);
			md_printf("`bright cyan`3`white`");

			md_set_cursor(14, 37);
			md_printf("`bright cyan`4`white`");

			md_set_cursor(14, 47);
			md_printf("`bright cyan`5`white`");

			md_set_cursor(16, 13);
			md_printf("`bright white`Keep which dice? (`bright cyan`1 - 5`bright white`)");
			md_set_cursor(17, 18);
			md_printf("`bright cyan`SPACE`bright white` to roll.`white`");

			md_set_cursor(18, 20);

			bool done = false;

			if (turn < 2) {
				while (!done) {
					char c = md_get_answer((char*)"12345qQ ");
					if (c == ' ') {
						done = true;
					}
					else if (c == 'q' || c == 'Q') {
						// quit;
						return 0;
					}
					else {
						dice.at(c - '0' - 1)->keep = !dice.at(c - '0' - 1)->keep;
						md_set_cursor(7, 10 * (c - '0' - 1) + 3);
						if (dice.at(c - '0' - 1)->keep) {
							md_printf("`bright green`   KEEP  `white`");
						}
						else {
							md_printf("        ");
						}
					}
				}
			}
		}
		// score
		// draw score options;

		char buffer[28];
		char* ptr = buffer;

		if (ones == -1) {
			md_set_cursor(2, 78);
			md_printf("`white bright cyan`1`white`");
			*ptr = '1';
			ptr++;
			*ptr = '\0';
		}
		if (twos == -1) {
			md_set_cursor(3, 78);
			md_printf("`white bright cyan`2`white`");
			*ptr = '2';
			ptr++;
			*ptr = '\0';

		}
		if (threes == -1) {
			md_set_cursor(4, 78);
			md_printf("`white bright cyan`3`white`");
			*ptr = '3';
			ptr++;
			*ptr = '\0';

		}
		if (fours == -1) {
			md_set_cursor(5, 78);
			md_printf("`white bright cyan`4`white`");
			*ptr = '4';
			ptr++;
			*ptr = '\0';

		}
		if (fives == -1) {
			md_set_cursor(6, 78);
			md_printf("`white bright cyan`5`white`");
			*ptr = '5';
			ptr++;
			*ptr = '\0';

		}
		if (sixes == -1) {
			md_set_cursor(7, 78);
			md_printf("`white bright cyan`6`white`");
			*ptr = '6';
			ptr++;
			*ptr = '\0';

		}

		if (threeofakind == -1) {
			md_set_cursor(12, 78);
			md_printf("`white bright cyan`A`white`");
			*ptr = 'A';
			ptr++;
			*ptr = 'a';
			ptr++;
			*ptr = '\0';

		}
		if (fourofakind == -1) {
			md_set_cursor(13, 78);
			md_printf("`white bright cyan`B`white`");
			*ptr = 'B';
			ptr++;
			*ptr = 'b';
			ptr++;
			*ptr = '\0';

		}

		if (fullhouse == -1) {
			md_set_cursor(14, 78);
			md_printf("`white bright cyan`C`white`");
			*ptr = 'C';
			ptr++;
			*ptr = 'c';
			ptr++;
			*ptr = '\0';

		}
		if (smallstraight == -1) {
			md_set_cursor(15, 78);
			md_printf("`white bright cyan`D`white`");
			*ptr = 'D';
			ptr++;
			*ptr = 'd';
			ptr++;
			*ptr = '\0';

		}
		if (largestraight == -1) {
			md_set_cursor(16, 78);
			md_printf("`white bright cyan`E`white`");
			*ptr = 'E';
			ptr++;
			*ptr = 'e';
			ptr++;
			*ptr = '\0';

		}
		if (yahtzee == -1) {
			md_set_cursor(17, 78);
			md_printf("`white bright cyan`F`white`");
			*ptr = 'F';
			ptr++;
			*ptr = 'f';
			ptr++;
			*ptr = '\0';

		}
		if (chance == -1) {
			*ptr = 'G';
			ptr++;
			*ptr = 'g';
			ptr++;
			*ptr = '\0';

			md_set_cursor(18, 78);
			md_printf("`white bright cyan`G`white`");
		}

		*ptr = 'Q';
		ptr++;
		*ptr = 'q';
		ptr++;
		*ptr = '\0';

		md_set_cursor(16, 13);
		md_printf("                       ");
		md_set_cursor(17, 18);
		md_printf("              ");

		md_set_cursor(16, 13);
		md_printf("  `bright white`Score as (`bright cyan`1-6,A-G,Q`bright white`): `white`");

		char scoreas = toupper(md_get_answer(buffer));

		if (scoreas == '1') {
			ones = 0;
			int counter = 0;
			for (int j = 0; j < 5; j++) {
				if (dice.at(j)->active->value == 1) {
					ones = ones + 1;
					counter = counter + 1;
				}
			}

			if (counter == 5) {
				yahtzeecount++;
			}
			md_set_cursor(2, 72);
			md_printf("`white red`%d", ones);
		}
		else if (scoreas == '2') {
			twos = 0;
			int counter = 0;
			for (int j = 0; j < 5; j++) {
				if (dice.at(j)->active->value == 2) {
					twos = twos + 2;
					counter = counter + 1;
				}
			}

			if (counter == 5) {
				yahtzeecount++;
			}
			md_set_cursor(3, 72);
			md_printf("`white red`%d", twos);
		}
		else if (scoreas == '3') {
			threes = 0;
			int counter = 0;
			for (int j = 0; j < 5; j++) {
				if (dice.at(j)->active->value == 3) {
					threes = threes + 3;
					counter = counter + 1;
				}
			}

			if (counter == 5) {
				yahtzeecount++;
			}
			md_set_cursor(4, 72);
			md_printf("`white red`%d", threes);
		}
		else if (scoreas == '4') {
			fours = 0;
			int counter = 0;
			for (int j = 0; j < 5; j++) {
				if (dice.at(j)->active->value == 4) {
					fours = fours + 4;
					counter = counter + 1;
				}
			}

			if (counter == 5) {
				yahtzeecount++;
			}
			md_set_cursor(5, 72);
			md_printf("`white red`%d", fours);
		}
		else if (scoreas == '5') {
			fives = 0;
			int counter = 0;
			for (int j = 0; j < 5; j++) {
				if (dice.at(j)->active->value == 5) {
					fives = fives + 5;
					counter = counter + 1;
				}
			}

			if (counter == 5) {
				yahtzeecount++;
			}
			md_set_cursor(6, 72);
			md_printf("`white red`%d", fives);
		}
		else if (scoreas == '6') {
			sixes = 0;
			int counter = 0;
			for (int j = 0; j < 5; j++) {
				if (dice.at(j)->active->value == 6) {
					sixes = sixes + 6;
					counter = counter + 1;
				}
			}

			if (counter == 5) {
				yahtzeecount++;
			}
			md_set_cursor(7, 72);
			md_printf("`white red`%d", sixes);
		}
		else if (scoreas == 'A') {
			int counter;
			for (int j = 0; j < 6; j++) {
				counter = 0;
				for (int k = 0; k < 5; k++) {
					if (dice.at(k)->active->value == j + 1) {
						counter++;
					}
				}
				if (counter >= 3) {
					break;
				}
			}

			if (counter >= 3) {
				threeofakind = dice.at(0)->active->value + dice.at(1)->active->value + dice.at(2)->active->value + dice.at(3)->active->value + dice.at(4)->active->value;
			}
			else {
				threeofakind = 0;
			}

			if (counter == 5) {
				yahtzeecount++;
			}
			md_set_cursor(12, 72);
			md_printf("`white red`%d", threeofakind);
		}
		else if (scoreas == 'B') {
			int counter;
			for (int j = 0; j < 6; j++) {
				counter = 0;
				for (int k = 0; k < 5; k++) {
					if (dice.at(k)->active->value == j + 1) {
						counter++;
					}
				}
				if (counter >= 4) {
					break;
				}
			}

			if (counter >= 4) {
				fourofakind = dice.at(0)->active->value + dice.at(1)->active->value + dice.at(2)->active->value + dice.at(3)->active->value + dice.at(4)->active->value;
			}
			else {
				fourofakind = 0;
			}

			if (counter == 5) {
				yahtzeecount++;
			}
			md_set_cursor(13, 72);
			md_printf("`white red`%d", fourofakind);
		}
		else if (scoreas == 'C') {
			int counter;
			int counter1;
			for (int j = 0; j < 6; j++) {
				counter = 0;
				for (int k = 0; k < 5; k++) {
					if (dice.at(k)->active->value == j + 1) {
						counter++;
					}
				}
				if (counter == 5) {
					break;
				}
				else if (counter == 3) {
					for (int k = 0; k < 6; k++) {
						if (k != j) {
							counter1 = 0;
							for (int l = 0; l < 5; l++) {
								if (dice.at(l)->active->value == k + 1) {
									counter1++;
								}
							}
							if (counter1 == 2) {
								break;
							}
						}
					}
					break;
				}

			}
			if (counter == 5 || (counter == 3 && counter1 == 2)) {
				fullhouse = 25;
			}
			else {
				fullhouse = 0;
			}
			if (counter == 5) {
				yahtzeecount++;
			}
			md_set_cursor(14, 72);
			md_printf("`white red`%d", fullhouse);
		}
		else if (scoreas == 'D') {
			smallstraight = 0;
			if ((is_there_a(1) && is_there_a(2) && is_there_a(3) && is_there_a(4)) || (is_there_a(2) && is_there_a(3) && is_there_a(4) && is_there_a(5)) || (is_there_a(3) && is_there_a(4) && is_there_a(5) && is_there_a(6))) {
				smallstraight = 30;
			}
			else if ((dice.at(0)->active->value == dice.at(1)->active->value) && (dice.at(1)->active->value == dice.at(2)->active->value) && (dice.at(2)->active->value == dice.at(3)->active->value) && (dice.at(3)->active->value == dice.at(4)->active->value)) {
				smallstraight = 30;
				yahtzeecount++;
			}
			md_set_cursor(15, 72);
			md_printf("`white red`%d", smallstraight);
		}
		else if (scoreas == 'E') {
			largestraight = 0;
			if ((is_there_a(1) && is_there_a(2) && is_there_a(3) && is_there_a(4) && is_there_a(5)) || (is_there_a(2) && is_there_a(3) && is_there_a(4) && is_there_a(5) && is_there_a(6))) {
				largestraight = 40;
			}
			else if ((dice.at(0)->active->value == dice.at(1)->active->value) && (dice.at(1)->active->value == dice.at(2)->active->value) && (dice.at(2)->active->value == dice.at(3)->active->value) && (dice.at(3)->active->value == dice.at(4)->active->value)) {
				largestraight = 30;
				yahtzeecount++;
			}
			md_set_cursor(16, 72);
			md_printf("`white red`%d", largestraight);
		}
		else if (scoreas == 'F') {
			if ((dice.at(0)->active->value == dice.at(1)->active->value) && (dice.at(1)->active->value == dice.at(2)->active->value) && (dice.at(2)->active->value == dice.at(3)->active->value) && (dice.at(3)->active->value == dice.at(4)->active->value)) {
				yahtzee = 50;
				yahtzeecount++;
			}
			else {
				yahtzee = 0;
			}
			md_set_cursor(17, 72);
			md_printf("`white red`%d", yahtzee);
		}
		else if (scoreas == 'G') {
			chance = dice.at(0)->active->value + dice.at(1)->active->value + dice.at(2)->active->value + dice.at(3)->active->value + dice.at(4)->active->value;
			if ((dice.at(0)->active->value == dice.at(1)->active->value) && (dice.at(1)->active->value == dice.at(2)->active->value) && (dice.at(2)->active->value == dice.at(3)->active->value) && (dice.at(3)->active->value == dice.at(4)->active->value)) {
				yahtzeecount++;
			}
			md_set_cursor(18, 72);
			md_printf("`white red`%d", chance);
		}

		int uscore = 0;

		if (ones >= 0) {
			uscore += ones;
		}
		if (twos >= 0) {
			uscore += twos;
		}
		if (threes >= 0) {
			uscore += threes;
		}
		if (fours >= 0) {
			uscore += fours;
		}
		if (fives >= 0) {
			uscore += fives;
		}
		if (sixes >= 0) {
			uscore += sixes;
		}

		if (uscore > 67) {
			upperbonus = 35;
		}

		md_set_cursor(8, 72);
		md_printf("`white bright black`......`white blue`");
		md_set_cursor(8, 72);
		md_printf("%d", uscore);

		md_set_cursor(9, 72);
		md_printf("`white bright black`......`white blue`");
		md_set_cursor(9, 72);
		md_printf("%d", upperbonus);

		md_set_cursor(10, 72);
		md_printf("`white bright black`......`white blue`");
		md_set_cursor(10, 72);
		md_printf("%d", upperbonus + uscore);

		int ybonus = 0;

		if (yahtzeecount > 1 && yahtzee > 0) {
			ybonus = (yahtzeecount - 1) * 100;
		}

		md_set_cursor(19, 72);
		md_printf("`white bright black`......`white blue`");
		md_set_cursor(19, 72);
		md_printf("%d", ybonus);

		int lscore = 0;
		if (threeofakind >= 0) {
			lscore += threeofakind;
		}
		if (fourofakind >= 0) {
			lscore += fourofakind;
		}
		if (fullhouse >= 0) {
			lscore += fullhouse;
		}

		if (smallstraight >= 0) {
			lscore += smallstraight;
		}
		if (largestraight >= 0) {
			lscore += largestraight;
		}
		if (chance >= 0) {
			lscore += chance;
		}

		if (yahtzee >= 0) {
			lscore += yahtzee;
		}

		md_set_cursor(20, 72);
		md_printf("`white bright black`......`white blue`");
		md_set_cursor(20, 72);
		md_printf("%d", ybonus + lscore);

		md_set_cursor(22, 72);
		md_printf("`white bright black`......`white blue`");
		md_set_cursor(22, 72);
		md_printf("%d", ybonus + lscore + uscore + upperbonus);

		for (int i = 0; i < 5; i++) {
			dice.at(i)->keep = false;
			md_set_cursor(7, 10 * i + 3);
			md_printf("`white`         ");
		}

		md_set_cursor(2, 78);
		md_printf("`white black` `white`");
		md_set_cursor(3, 78);
		md_printf("`white black` `white`");
		md_set_cursor(4, 78);
		md_printf("`white black` `white`");
		md_set_cursor(5, 78);
		md_printf("`white black` `white`");
		md_set_cursor(6, 78);
		md_printf("`white black` `white`");
		md_set_cursor(7, 78);
		md_printf("`white black` `white`");

		md_set_cursor(12, 78);
		md_printf("`white black` `white`");
		md_set_cursor(13, 78);
		md_printf("`white black` `white`");
		md_set_cursor(14, 78);
		md_printf("`white black` `white`");
		md_set_cursor(15, 78);
		md_printf("`white black` `white`");
		md_set_cursor(16, 78);
		md_printf("`white black` `white`");
		md_set_cursor(17, 78);
		md_printf("`white black` `white`");
		md_set_cursor(18, 78);
		md_printf("`white black` `white`");


		if (threeofakind >= 0 && fourofakind >= 0 && smallstraight >= 0 && largestraight >= 0 && fullhouse >= 0 && yahtzee >= 0 && chance >= 0 && ones >= 0 && twos >= 0 && threes >= 0 && fours >= 0 && fives >= 0 && sixes >= 0) {
			return ybonus + lscore + uscore + upperbonus;
		}
	}
	return 0;
}




std::vector<struct score_t> Program::load_scores() {
	FILE* fptr;

	std::vector<struct score_t> ret;

	fptr = fopen("scores.dat", "rb");

	if (!fptr) {
		for (int i = 0; i < 10; i++) {
			struct score_t s;
			snprintf(s.name, 32, "No-One");
			s.score = 0;

			ret.push_back(s);
		}
	}
	else {
		for (int i = 0; i < 10; i++) {
			struct score_t s;
			fread(&s, sizeof(struct score_t), 1, fptr);
			ret.push_back(s);
		}
		fclose(fptr);
	}
	return ret;
}

void Program::save_scores(std::vector<struct score_t> scores) {
	FILE* fptr;
	fptr = fopen("scores.dat", "wb");

	if (fptr) {
		for (int i = 0; i < 10; i++) {
			fwrite(&scores.at(i), sizeof(struct score_t), 1, fptr);
		}
		fclose(fptr);
	}
}

void Program::add_score(int score) {
	std::vector<struct score_t> scores = load_scores();
	for (size_t i = 0; i < scores.size(); i++) {
		if (score > scores.at(i).score) {
			for (size_t j = i; j < scores.size() - 1; j++) {
				scores.at(j + 1) = scores.at(j);
			}
			scores.at(i).score = score;
			snprintf(scores.at(i).name, 32, "%s %s", mdcontrol.user_firstname, mdcontrol.user_lastname);
			save_scores(scores);
			return;
		}
	}
}

void Program::show_scores() {
	md_clr_scr();
	md_sendfile("ansi/high.ans", 0);
	std::vector<struct score_t> scores = load_scores();

	for (size_t i = 0; i < scores.size(); i++) {
		md_set_cursor(9 + i, 20);
		md_printf("`bright cyan`%2d. `bright white`%-32.32s `bright yellow`%d", i + 1, scores.at(i).name, scores.at(i).score);
	}
	md_getc();
}

int Program::run() {
	if (!load_dice()) {
		return -1;
	}
	srand(time(NULL));

	while (true) {
		md_clr_scr();
		md_sendfile("ansi/menu.ans", 0);

		char c = md_get_answer((char *)"123Qq");

		switch (tolower(c)) {
		case '1':
			add_score(play_game());
			break;
		case '2':
			show_scores();
			break;
		case '3':
			md_clr_scr();
			md_sendfile("ansi/instruct.ans", 0);
			md_getc();
			break;
		case 'q':
			return 0;
		}
	}
}