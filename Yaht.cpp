// Yaht.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Program.h"
extern "C" {
#include "magidoor/MagiDoor.h"
}
int main(int argc, char** argv)
{

	Program p;

	if (argc < 2) {
		std::cout << "USAGE Yaht /path/to/dropfile [SOCKET]" << std::endl;
		std::cout << "  -  Supports door.sys and door32.sys" << std::endl;
		return 0;
	}


	md_init(argv[1], (argc < 3 ? -1 : atoi(argv[2])));

	md_exit(p.run());

	return 0;
}
