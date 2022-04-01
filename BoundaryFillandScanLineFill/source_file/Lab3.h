#pragma once

void EllipseMidpoint(int, int, int, int, int);
void BoundaryFillEnhanced(int, int, int, int);
void VeDiem(int, int, int, int, int);
void Star(int, int, int, int, int);
void Display1();
void Display2(int, int, int, int);


/*
	Lop: Stack
	Mo ta: Cai dat cau truc Stack dung de khu de quy
*/
class Stack
{
public:
	Stack(int size); //Khoi tao stack voi kich thuoc la size
	~Stack();

	void Push(int xc, int yc, int size);
	void Pop(int& xc, int& yc);

	bool IsEmpty();
	bool IsFull(int size);

private:
	int n;
	int size;
	int* x;
	int* y;
};
//**********Ket thuc dinh nghia Stack**********


/*
	Lop: Point
	Mo ta: Cai dat cau truc Point de bieu dien diem trong da giac
*/
class Point
{
public:
	int x, y;
};
//**********Ket thuc dinh nghia Point**********


/*
	Lop: CPolygon
	Mo ta: Cai dat cau truc CPolygon de bieu dien da giac
*/
class CPolygon
{
public:
	int c;
	void Read();
	void Calcs();
	void Ints(float);
	void Sort(int);
	void Xuly();

private:
	Point p[20];
	int inter[20], x, y;
	int v, xmin, ymin, xmax, ymax;
};
//**********Ket thuc dinh nghia CPolygon**********