#pragma once
#include <vector>
#include <cstdint>
#pragma pack(push)
struct score_t {
	uint32_t score;
	char name[32];
};
#pragma pack(pop)

class Dice;

class Program
{
public:
	bool is_there_a(int a);
	std::vector<Dice *> dice;
	bool load_dice();
	int play_game();
	int run();
	void add_score(int score);
	void show_scores();
	std::vector<struct score_t> load_scores();
	void save_scores(std::vector<struct score_t> scores);
};

