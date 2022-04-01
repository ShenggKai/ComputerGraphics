#include "main.h"

/*
    Xay dung cau truc stack - dung trong to mau theo duong bien
*/
Stack::Stack(int size)
{
    
    n = 0;
    x = new int[size];
    y = new int[size];
}

Stack::~Stack()
{
    delete[] x;
    delete[] y;
}

// Them phan tu vao dau danh sach
void Stack::Push(int xc, int yc, int size)
{
    if (IsFull(size) == true)
        printf("\nStack is full\n");
    else 
    {
        x[n] = xc;
        y[n] = yc;
        n++;
    }
}

// Lay phan tu dau tien ra khoi danh sach
void Stack::Pop(int& xc, int& yc)
{
    if (IsEmpty() == true) 
    {
        printf("\nStack is empty!\n");
    }
    else
    {
        --n;
        xc = x[n];
        yc = y[n];
    }
}

bool Stack::IsEmpty()
{
    if (n == 0)
        return true;
    return false;
}

bool Stack::IsFull(int size)
{
    if (n >= size - 1) 
        return true;
    else
        return false;
}
//**********Ket thuc dinh nghia cac ham cho lop Stack**********


/*
    Xay dung cau truc CPolygon dung trong scan line fill
*/
void CPolygon::Read()
{
    int i;

    do
    {
        cout << "Nhap so dinh cua da giac: ";
        cin >> v;

        if (v <= 2)
        {
            cout << "\nSo dinh khong hop le (<= 2) !!!\n\n";
        }

    } while (v <=2);

    for (i = 0; i < v; i++) //ACCEPT THE VERTICES
    {
            cout << "\nNhap dinh thu " << i + 1 << " :";
            cout << "\n\tx" << (i + 1) << " = ";
            cin >> p[i].x;
            cout << "\ty" << (i + 1) << " = ";
            cin >> p[i].y;
     }

     p[i].x = p[0].x;
     p[i].y = p[0].y;
     xmin = xmax = p[0].x;
     ymin = ymax = p[0].y;
}

// Ham tim kiem
void CPolygon::Calcs()
{ //MAX,MIN
    for (int i = 0; i < v; i++)
    {
        if (xmin > p[i].x)
            xmin = p[i].x;
        if (xmax < p[i].x)
            xmax = p[i].x;
        if (ymin > p[i].y)
            ymin = p[i].y;
        if (ymax < p[i].y)
            ymax = p[i].y;
    }
}

void CPolygon::Ints(float z) 
{
    int x1, x2, y1, y2, temp;
    c = 0;
    for (int i = 0; i < v; i++)
    {
        x1 = p[i].x;
        y1 = p[i].y;
        x2 = p[i + 1].x;
        y2 = p[i + 1].y;
        if (y2 < y1)
        {
            temp = x1;
            x1 = x2;
            x2 = temp;
            temp = y1;
            y1 = y2;
            y2 = temp;
        }
        if (z <= y2 && z >= y1)
        {
            if ((y1 - y2) == 0)
                x = x1;
            else // used to make changes in x. so that we can fill our polygon after cerain distance
            {
                x = ((x2 - x1) * (z - y1)) / (y2 - y1);
                x = x + x1;
            }
            if (x <= xmax && x >= xmin)
                inter[c++] = x;
        }
    }
}

// Ham sap xep
void CPolygon::Sort(int z)
{
    int temp, j, i;

    for (i = 0; i < v; i++)
    {
        // ve da giac rong
        line(p[i].x, p[i].y, p[i + 1].x, p[i + 1].y);
    }
    delay(100);
    for (i = 0; i < c; i += 2)
    {
        delay(100);
        // to mau da giac bang duong thang
        line(inter[i], z, inter[i + 1], z); 
    }
}

void CPolygon::Xuly()
{
    float s;

    s = ymin + 0.01;
    delay(100);
    cleardevice();
    while (s <= ymax)
    {
        Ints(s);
        Sort(s);
        s++;
    }

}
//**********Ket thuc dinh nghia cac ham cho CPolygon**********


// Ham ve ngoi sao
void Star(int xc, int yc, int R, int n, int color)
{
    setcolor(color);
    float r = R * sin(M_PI / (2 * n)) / sin(M_PI - 3 * M_PI / (2 * n));
    int* x = new int[2 * n];
    int* y = new int[2 * n];

    float alpha = -M_PI / 2;
    float const1 = M_PI / n;
    float const2 = 2 * M_PI / n;

    int i;
    for (i = 0; i < 2 * n; i += 2)
    {
        x[i] = R * cos(alpha) + xc;
        y[i] = R * sin(alpha) + yc;
 
        x[i + 1] = r * cos(alpha + const1) + xc; 
        y[i + 1] = r * sin(alpha + const1) + yc;

        alpha += const2;
    }

    for (i = 0; i < 2 * n - 1; ++i)
        line(x[i], y[i], x[i + 1], y[i + 1]);
    line(x[2 * n - 1], y[2 * n - 1], x[0], y[0]);
}


// Ve 4 diem cho thuat thoan Midpoint
void VeDiem(int xc, int yc, int x, int y, int color)
{
    putpixel(xc + x, yc + y, color);
    putpixel(xc - x, yc + y, color);
    putpixel(xc + x, yc - y, color);
    putpixel(xc - x, yc - y, color);
}


// Ham ve Ellips bang thuat toan Midpoint
void EllipseMidpoint(int xc, int yc, int a, int b, int color)
{
    int x, y, fx, fy, a2, b2, p;
    x = 0;
    y = b;
    a2 = a * a;
    b2 = b * b;
    fx = 0;
    fy = 2 * a2 * y;

    VeDiem(xc, yc, x, y, color);
    //p=b2 - a2*b +a2/4
    p = round(b2 - (a2 * b) + (0.25 * a2));

    while (fx < fy)
    {
        x++;
        fx += 2 * b2;
        delay(50);

        if (p < 0)
        {
            p += b2 * (2 * x + 3);//p=p + b2*(2x +3)
        }
        else
        {
            y--;
            p += b2 * (2 * x + 3) + a2 * (2 - 2 * y);//p=p +b2(2x +3) +a2(2-2y)
            fy -= 2 * a2;
        }

        VeDiem(xc, yc, x, y, color);
    }

    p = round(b2 * (x + 0.5) * (x + 0.5) + a2 * (y - 1) * (y - 1) - a2 * b2);
    
    while (y > 0)
    {
        y--;
        fy -= 2 * a2;
        delay(50);

        if (p >= 0)
        {
            //p=p +a2(3-2y)
            p += a2 * (3 - 2 * y);
        }
        else
        {
            x++;
            fx += 2 * b2;
            //p=p+ b2(2x +2) + a2(3-2y)
            p += b2 * (2 * x + 2) + a2 * (3 - 2 * y);
        }

        VeDiem(xc, yc, x, y, color);
    }
}


// Ham to mau su dung thuat toan Boundary Fill khu de quy
void BoundaryFillEnhanced(int x, int y, int FillColor, int BoundaryColor)
{
    Stack store(1024);
    store.Push(x, y, 1024);

    int left, right;
    int curentColor;

    while (!store.IsEmpty())
    {
        store.Pop(x, y);
        putpixel(x, y, FillColor);

        //To trai nhat co the
        left = x - 1;
        while (getpixel(left, y) != BoundaryColor)
        {
            putpixel(left, y, FillColor);
            --left;
        }

        //To phai nhat co the
        right = x + 1;
        while (getpixel(right, y) != BoundaryColor)
        {
            putpixel(right, y, FillColor);
            ++right;
        }


        ++left;
        --right;
        for (x = left; x <= right; ++x)
        {
            //xet ben tren dong dang to
            curentColor = getpixel(x, y + 1);
            //chua to va khog phai bien
            if ((curentColor != FillColor) && (curentColor != BoundaryColor))
                //Diem trai dau tien
                if ((x == left) || (getpixel(x - 1, y + 1) == BoundaryColor)) 
                    store.Push(x, y + 1, 1024);

            //xet ben duoi dong dang to
            curentColor = getpixel(x, y - 1);
            // chua to va khog phai bien
            if ((curentColor != FillColor) && (curentColor != BoundaryColor))
                if ((x == left) || (getpixel(x - 1, y - 1) == BoundaryColor))
                    store.Push(x, y - 1, 1024);
        }
    }
}


// Ham hien thi Menu chon lua dau tien
void Display1()
{
    
    int choice;
    bool isExit = false;

    int midx = getmaxx() / 2;
    int midy = getmaxy() / 2;

    int FillColor = LIGHTCYAN;
    int BoundaryColor = YELLOW;

    do
    {
        cout << "**********  MENU  **********";
        cout << "\n\n\t1. Boundary Fill";
        cout << "\n\n\t2. Scan line Fill";
        cout << "\n\n\t3. Thoat chuong trinh";
        cout << "\n\nLua chon cua ban: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            system("cls");
            Display2(midx, midy, FillColor, BoundaryColor);
            
            // Cho 5 giay de quan sat ket qua
            delay(5000);
            // Xoa man hinh de ve hinh khac
            cleardevice();
            system("cls");
            break;
        }
        case 2:
        {
            system("cls");
            cout << "**********  SCAN LINE FILL  **********";
            cout << "\n\n\tBat dau ve da giac\n\n";
            CPolygon x;
            x.Read();
            x.Calcs();
            cleardevice();

            setcolor(FillColor);

            cout << "\nwaiting...\n";
            x.Xuly();
            delay(5000);
            system("cls");

            break;
        }
        case 3:
        {
            isExit = true;
            exit(0);
        }

        default:
            cout << "\nLua chon khong hon le!!!\n" << endl;
        }

    } while (!isExit);
}


//Ham hien thi Menu chon lua thu hai
void Display2(int x, int y, int FillColor, int BoundaryColor)
{
    int choice;
    bool isExit = false;

    int midx = getmaxx() / 2;
    int midy = getmaxy() / 2;

    do
    {
        cout << "**********  BOUNDARY FILL  **********";
        cout << "\n\n\t1. Ve ellips";
        cout << "\n\n\t2. Ve ngoi sao co n canh ";
        cout << "\n\n\t3. Quay lai menu";
        cout << "\n\nLua chon cua ban: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            system("cls");
            cleardevice();

            int a, b; // do dai a, b cua ellipse

            cout << "**********  BOUNDARY FILL  **********";
            cout << "\n\n\tBat dau ve ellipse\n\n";
            cout << "Nhap a = ";
            cin >> a;
            cout << "Nhap b = ";
            cin >> b;

            // Ve ellipse x ^ 2 / a ^ 2 + y ^ 2 / b ^ 2 = 1
            cout << "\nwaiting...\n";
            EllipseMidpoint(midx, midy, a, b, BoundaryColor);
            BoundaryFillEnhanced(midx, midy, FillColor, BoundaryColor);

            isExit = true;
            break;
        }
        case 2:
        {
            int ncanh;
            int r;

            system("cls");
            cleardevice();

            cout << "**********  BOUNDARY FILL  **********";
            cout << "\n\n\tBat dau ve ngoi sao\n\n";

            cout << "Nhap so canh cua ngoi sao = ";
            cin >> ncanh;
            cout << "Nhap ban kinh = ";
            cin >> r;

            // Ve ngoi sao n canh
            cout << "\nwaiting...\n";
            Star(midx, midy, r, ncanh, BoundaryColor);
            BoundaryFillEnhanced(midx, midy, FillColor, BoundaryColor);

            isExit = true;
            break;
        }
        case 3:
        {
            isExit = true;
            break;
        }
        default:
            cout << "\nLua chon khong hon le!!!\n" << endl;
        }

    } while (!isExit);

}