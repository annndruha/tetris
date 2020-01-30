#pragma once
//Класс создания графического окна и слоёв внутри него
class display
{
private:
	String MY_NAME;
	block* my_p_next;
	matrix* my_p_matrix;

	Mat background = Mat::zeros(600, 400, CV_8UC3);
	Mat draw = Mat::zeros(background.rows, background.cols, CV_8UC3);
	Mat out = Mat::zeros(background.rows, background.cols, CV_8UC3);
public:
	display(String my_name, block* p_block, matrix* p_matrix);
	void draw_background(Scalar color, Scalar color_lines);
	void draw_pieces();
	void draw_mini_pieces();
	void draw_info(int score, int lines, int speed);
	void merge(Mat* p_down, Mat* p_up);
	void update(int score, int lines, int speed);
	void end_screen(int score, int lines, int speed);
};

//Конструктор создания объекта графического окна
display::display(String my_name, block* p_block, matrix* p_matrix) : MY_NAME(my_name), my_p_next(p_block), my_p_matrix(p_matrix)
{
	namedWindow(my_name);
	moveWindow(my_name, 750, 150);
}
//Отрисовка заднего фона
void display::draw_background(Scalar color, Scalar color_lines)
{
	rectangle(background, Point(-1, -1), Point(background.cols, background.rows), color, -1, LINE_AA);

	for (int i = 0; i < 301; i = i + 30)
	{
		line(background, Point(i, -2), Point(i, background.rows), color_lines, 1, LINE_AA);
	}
	for (int i = 0; i < 601; i = i + 30)
	{
		line(background, Point(-2, i), Point(301, i), color_lines, 1, LINE_AA);
	}
}
//Отрисовка элементов на поле
void display::draw_pieces()
{
	matrix& field = *my_p_matrix;
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 20; y++)
		{
			if (field.el[x][y] == 1)
			{
				rectangle(draw, Point(30 * x + 3, 30 * y + 3), Point(30 * x + 27, 30 * y + 27), field.color[x][y], -1, LINE_AA);
			}
		}
	}
}
//Отрисовка следующей тетримино
void display::draw_mini_pieces()
{
	block& next_tetrimino = *my_p_next;
	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			if (next_tetrimino.arr[x][y] == 1)
			{
				rectangle(draw, Point(15 * x + 1 + 312, 15 * y + 51), Point(15 * x + 14 + 312, 15 * y + 14 + 50), next_tetrimino.color, -1, LINE_AA);
			}
		}
	}
}
//Отрисовка информации о счёте, линиях и скорости
void display::draw_info(int score, int lines, int speed)
{
	String k = "Next";
	putText(draw, k, Point(310, 60), FONT_HERSHEY_SIMPLEX, 0.6, white, 1, LINE_AA, false);
	k = "Speed=";
	putText(draw, k, Point(310, 150), FONT_HERSHEY_SIMPLEX, 0.6, white, 1, LINE_AA, false);
	k = std::to_string(speed);
	putText(draw, k, Point(310, 170), FONT_HERSHEY_SIMPLEX, 0.6, white, 1, LINE_AA, false);
	k = "Score=";
	putText(draw, k, Point(310, 350), FONT_HERSHEY_SIMPLEX, 0.6, white, 1, LINE_AA, false);
	k = std::to_string(score);
	putText(draw, k, Point(310, 370), FONT_HERSHEY_SIMPLEX, 0.6, white, 1, LINE_AA, false);
	k = "Lines= ";
	putText(draw, k, Point(310, 420), FONT_HERSHEY_SIMPLEX, 0.6, white, 1, LINE_AA, false);
	k = std::to_string(lines);
	putText(draw, k, Point(310, 440), FONT_HERSHEY_SIMPLEX, 0.6, white, 1, LINE_AA, false);
	k = "Tetris";
	putText(draw, k, Point(310, 560), FONT_HERSHEY_SIMPLEX, 0.6, tetrimino_color(54), 1, LINE_AA, false);
	k = "by Andrey";
	putText(draw, k, Point(310, 580), FONT_HERSHEY_SIMPLEX, 0.5, white, 1, LINE_AA, false);
}
//Объединение заднего фона с динамичным фоном
void display::merge(Mat* p_down, Mat* p_up)
{
	Mat down = *p_down;
	Mat up = *p_up;
	int chanals = 3;
	for (int i = 0; i < down.rows; i++)
	{
		uchar* ptr_up = (uchar*)(up.data + i * up.step);
		uchar* ptr_down = (uchar*)(down.data + i * down.step);
		for (int j = 0; j < down.cols; j++)
		{
			if ((ptr_up[chanals * j + 0] != 0) || (ptr_up[chanals * j + 1] != 0) || (ptr_up[chanals * j + 2] != 0))
			{
				ptr_down[chanals * j + 0] = ptr_up[chanals * j + 0];
				ptr_down[chanals * j + 1] = ptr_up[chanals * j + 1];
				ptr_down[chanals * j + 2] = ptr_up[chanals * j + 2];
				ptr_down[chanals * j + 3] = ptr_up[chanals * j + 3];
			}
		}
	}
}
//Обновление кадра
void display::update(int score, int lines, int speed)
{
	merge(&out, &background);
	draw_pieces();
	draw_mini_pieces();
	draw_info(score, lines, speed);
	merge(&out, &draw);

	imshow(MY_NAME, out);
	int bag = waitKey(1);
	draw = NULL;
	out = NULL;
}
//Слайд окончания игры
void display::end_screen(int score, int lines, int speed)
{
	if (score < 3000)
	{
		merge(&out, &background);
		draw_pieces();
		draw_mini_pieces();
		draw_info(score, lines, speed);
		rectangle(draw, Point(0, 125), Point(400, 325), red, -1, LINE_AA);
		putText(draw, "Game over!", Point(20, 250), FONT_HERSHEY_SIMPLEX, 2, white, 5, LINE_AA, false);
		merge(&out, &draw);
		imshow(MY_NAME, out);
	}
	else
	{
		merge(&out, &background);
		draw_pieces();
		draw_mini_pieces();
		draw_info(score, lines, speed);

		rectangle(draw, Point(0, 125), Point(400, 325), violet, -1, LINE_AA);
		putText(draw, "Game over!", Point(60, 170), FONT_HERSHEY_SIMPLEX, 1.5, white, 2, LINE_AA, false);

		for (double a = 0; a < 2.5; a = a + 0.2)
		{
			int x = int(70 * cos(a));
			int y = int(-70 * sin(a));
			arrowedLine(draw, Point(200, 260), Point(200 + x, 260 + y), gray, 2, LINE_AA, 0, 0.1);
		}

		circle(draw, Point(200, 260), 50, gray, -1, LINE_AA, 0);
		rectangle(draw, Point(130, 250), Point(200, 260), gray, -1, LINE_AA);
		circle(draw, Point(130, 255), 10, black, -1, LINE_AA, 0);
		circle(draw, Point(170, 240), 3, black, -1, LINE_AA, 0);//eay


		rectangle(draw, Point(0, 260), Point(400, 325), violet, -1, LINE_AA);
		putText(draw, "104 Forever!", Point(100, 300), FONT_HERSHEY_SIMPLEX, 1, green, 2, LINE_AA, false);
		merge(&out, &draw);
		imshow(MY_NAME, out);
	}
}