#include "Dice.h"
extern "C" {
#include "magidoor/MagiDoor.h"
}
void Dice::display(int y, int x) {
	for (int i = 0; i < 5; i++) {
		md_set_cursor(y + i, x);
		md_printf("%s", active->ansi.at(i).c_str());
	}
}

int Dice::roll() {
	int ret;

	ret = rand() % 6 + 1;

	active = &sides.at(ret - 1);
	return ret;
}