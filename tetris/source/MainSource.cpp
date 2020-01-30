#include <Windows.h>
#include <chrono>
#include <thread>

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;
using namespace chrono;
#include "../headers/Colors.h"
#include "../headers/Data.h"
#include "../headers/Display.h"


block tetrimino;
block next_tetrimino;
matrix field;
display window("Tetris",  &next_tetrimino, &field );

#include "../headers/Functions.h"

int score = 0, lines = 0, speed = 1, current_delay = 160; bool game_over = false;

void check_and_delite_lines(matrix* pmatrix)
{
	matrix &field = *pmatrix;
	bool check_another_lines = true;
	while (check_another_lines == true)
	{
		check_another_lines = false;
		for (int n = 19; n >= 0; n--)
		{
			if (can_i_delite_line(n) == true)
			{
				score += 100;
				lines += 1;
				delite_line(n);
				window.update(score, lines, speed);
				this_thread::sleep_for(400ms);
				check_another_lines = true;
			}
		}
	}
}


int main()
{
	srand((unsigned int)time(NULL));
	window.draw_background(black, gray);
	next_tetrimino.create(rand() % 7);
	while (game_over==false)
	{
		int i = 5, j = -1;
		check_and_delite_lines(&field);
		tetrimino = next_tetrimino;
		first_draw(i, j);
		next_tetrimino.create(rand()%7);

		if (score >= 3000)	window.draw_background(darkdarkred, gray);

		if (speed < 19) { speed = score / 150; }
		current_delay = 160 - speed * 7;
		int touch = 0;
		while (touch==0)
		{
			window.update(score, lines, speed);
			for (int h = 0; h < current_delay; h++)
			{
				int key = waitKeyEx(1);
				if (key != -1)
				{
					if ((key == 65) || (key == 97) || (key == 212) || (key == 244) || (key == 2424832))
					{
						if (left_shift_possible(i, j) == true)
						{
							field.clear_previous_el();
							left_shift(i, j);
							i--;
						}
					}
					if ((key == 68) || (key == 100) || (key == 194) || (key == 226) || (key == 2555904))
					{
						if (right_shift_possible(i, j) == true)
						{
							field.clear_previous_el();
							right_shift(i, j);
							i++;
						}
					}
					if ((key == 83) || (key == 115) || (key == 219) || (key == 251) || (key == 2621440))
					{
						if (down_shift_possible(i, j) == true)
						{
							field.clear_previous_el();
							down_shift(i, j);
							j++;
						}
					}
					if ((key == 87) || (key == 119) || (key == 214) || (key == 246) || (key==2490368))
					{
						if (rotate_possible(i, j) == true)
						{
							field.clear_previous_el();
							rotate_tetrimino(i, j);
						}
					}
					if (key == 27) return 0;
					window.update(score, lines, speed);
				}
				this_thread::sleep_for(2ms);
			}


			if (down_shift_possible(i, j) == true)
			{
				field.clear_previous_el();
				down_shift(i, j);
				j++;
			}
			else
			{
				field.clear_previous_position();
				touch = 1; 
				if (j < 1)  { game_over = true; }
				window.update(score, lines, speed);
			}
			//Обновление экрана при движении детали вниз
		}
		score += 10;
	}
	
	window.end_screen(score, lines, speed);
	while (waitKey(10) != 27){}
	return 0;
}