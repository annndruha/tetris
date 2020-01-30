#pragma once
void first_draw(int i, int j)
{
	bool possible = true;
	for (int k = 0; k <5; k++)
	{
		for (int u = 0; u < 5; u++)
		{
			if (tetrimino.arr[k][u] == 1)
			{
				field.previous_position[i + k - 2][j + u - 2] = 1;
				field.el[i + k - 2][j + u - 2] = 1;
				field.color[i + k - 2][j + u - 2] = tetrimino.color;
			}
		}
	}
}

bool down_shift_possible(int i, int j)
{
	bool possible = true;
	for (int k = 0; k < 5; k++)
	{
		for (int u = 4; u >= 0; u--)
		{
			if ((tetrimino.arr[k][u] == 1) && (tetrimino.arr[k][u + 1] == 0))
			{
				if ((field.el[i + k - 2][j + u - 2 + 1] == 1) || (j + u - 2 > 18))
					possible = false;
			}
		}
	}
	return possible;
}

bool right_shift_possible(int i, int j)
{
	bool possible = true;
	for (int k = 4; k >= 0; k--)
	{
		for (int u = 0; u < 5; u++)
		{
			if ((tetrimino.arr[k][u] == 1) && (tetrimino.arr[k + 1][u] == 0))
			{
				if ((field.el[i + k - 2 + 1][j + u - 2] == 1) || (i + k - 2 > 8))
				{
					possible = false;
				}
			}
		}
	}
	return possible;
}

bool left_shift_possible(int i, int j)
{
	bool possible = true;
	for (int k = 4; k >= 0; k--)
	{
		for (int u = 0; u < 5; u++)
		{
			if ((tetrimino.arr[k][u] == 1) && (tetrimino.arr[k - 1][u] == 0))
			{
				if ((field.el[i + k - 2 - 1][j + u - 2] == 1) || (i + k - 2 < 1))
				{
					possible = false;
				}
			}
		}
	}
	return possible;
}

void right_shift(int i, int j)
{
	bool possible = true;
	for (int k = 4; k >= 0; k--)
	{
		for (int u = 0; u < 5; u++)
		{
			if (tetrimino.arr[k][u] == 1)
			{
				field.previous_position[i + k - 1][j + u - 2] = 1;
				field.el[i + k - 1][j + u - 2] = 1;
				field.color[i + k - 1][j + u - 2] = tetrimino.color;
			}
		}
	}
}

void left_shift(int i, int j)
{
	for (int k = 0; k < 5; k++)
	{
		for (int u = 0; u < 5; u++)
		{
			if (tetrimino.arr[k][u] == 1)
			{
				field.previous_position[i + k - 3][j + u - 2] = 1;
				field.el[i + k - 3][j + u - 2] = 1;
				field.color[i + k - 3][j + u - 2] = tetrimino.color;
			}
		}
	}
}

void down_shift(int i, int j)
{
	for (int k = 0; k < 5; k++)
	{
		for (int u = 4; u >= 0; u--)
		{
			if (tetrimino.arr[k][u] == 1)
			{
				field.previous_position[i + k - 2][j + u - 1] = 1;
				field.el[i + k - 2][j + u - 1] = 1;
				field.color[i + k - 2][j + u - 1] = tetrimino.color;
			}
		}
	}
}

bool rotate_possible(int i, int j)
{
	bool possible = true;
	int recover_r = tetrimino.r;

	field.clear_previous_el();
	tetrimino.rotate();

	for (int k = 0; k < 5; k++)
	{
		for (int u = 0; u < 5; u++)
		{
			if (tetrimino.arr[k][u] == 1)
			{
				if ((field.el[i + k - 2][j + u - 2] == 1) || (i + k - 2 < 0) || (i + k - 2 > 9) || (j + u - 2 > 19))
				{
					possible = false;
				}
			}
		}
	}

	while (tetrimino.r != recover_r) { tetrimino.rotate(); }

	for (int k = 0; k < 5; k++)
	{
		for (int u = 0; u < 5; u++)
		{
			if (tetrimino.arr[k][u] == 1)
			{
				field.previous_position[i + k - 2][j + u - 2] = 1;
				field.el[i + k - 2][j + u - 2] = 1;
			}
		}
	}
	return possible;
}

void rotate_tetrimino(int i, int j)
{
	tetrimino.rotate();
	for (int k = 0; k < 5; k++)
	{
		for (int u = 0; u < 5; u++)
		{
			if (tetrimino.arr[k][u] == 1)
			{
				field.previous_position[i + k - 2][j + u - 2] = 1;
				field.el[i + k - 2][j + u - 2] = 1;
				field.color[i + k - 2][j + u - 2] = tetrimino.color;
			}
		}
	}
}

bool can_i_delite_line(int n)
{
	bool can = true;
	for (int i = 0; i < 10; i++)
	{
		if (field.el[i][n] != 1) can = false;
	}
	return can;
}

void delite_line(int n)
{
	for (int i = 0; i < 10; i++)
	{
		field.el[i][n] = 0;
	}

	for (n; n > 0; n--)
	{
		for (int i = 0; i < 10; i++)
		{
			field.el[i][n] = field.el[i][n - 1];
		}
	}
}