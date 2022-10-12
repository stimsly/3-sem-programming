#include "conio.h"
#include "dos.h"

//global variables
int x1 = 10;
int y1 = 5;
int x2 = 70;
int y2 = 15;
int T = 300;
int num_colors = 16;

void scroll(int direction, int lines, char l_row, char l_col, char r_row, char r_col, char attr)
{
	union REGS r;
	if (direction)
	{
		r.h.al = lines;
		r.h.ah = direction;
	}
	else
	{
		r.h.al = lines;
		r.h.ah = 6;
	}
	r.h.ch = l_row;
	r.h.cl = l_col;
	r.h.dh = r_row;
	r.h.dl = r_col;
	r.h.bh = attr;
	int86(0x10, &r, &r);
}


int main ()
{
	window(x1, y1, x2, y2);

	for (int i = 0; i < num_colors / 2; i++)
	{
		textbackground(i);
		for (int j = 0; j < num_colors; j++)
		{
			textcolor(j);
			cprintf("\r\n%d %c", i + 1, char(j + 65));
		       //	scroll(6,1, y1 - 1, x1 - 1, y2 - 1, x2 - 1, (i * 16|j));
			delay(T);
		}
	}
	getch();
	return 0;
}
