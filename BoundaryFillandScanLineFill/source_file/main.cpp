/*
	Ho va ten: Nguyen Quoc Dat
	MSSV: 19521338

	Day la file chinh chua ham 'main'. Chuong trinh se bat dau va ket thuc tai day.
*/

#include "main.h"


int main()
{
	/* request autodetection */
	int gdriver = DETECT, gmode;
	initgraph(&gdriver, &gmode, "");

	cleardevice();

	Display1();
	
	getch();
	closegraph();

	return 0;
}