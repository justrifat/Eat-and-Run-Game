#include<bits/stdc++.h>
#include<Windows.h>



using namespace std;
char tmp_map[18][32];
int pts;
char life;
int life_20, life_50, life_100;
int chance;
int id;

void gotoxy(short int x, short int y)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = {x,y};

    SetConsoleCursorPosition(hStdout, position);
}

//playfield
char maze[18][32] =
{
    "###############################",
    "#                             #",
    "#                             #",
    "#### ########## ##   ##########",
    "#                             #",
    "# # #### #  #           #     #",
    "# #      #  # ####  #   #  #  #",
    "#   ######  # #      ## #     #",
    "# #           ####  #      #  #",
    "# ###### ###         ##       #",
    "#          ######  ####### ####",
    "#                             #",
    "## ### ####      ###   ########",
    "#                             #",
    "#                             #",
    "####    ##############    #####",
    "#                             #",
    "###############################"
};






//print playfield
void ShowMap()
{
    system("COLOR 9");
    for(int j = 0; j <= 100; j++)
    {
        for(int i = 0; i <= 100; i++)
        {
            if(maze[j][i] == '#')
                maze[j][i] = 219;
        }
    }

    for(int i = 0; i < 18; i++)
    {
        printf("%s\n",maze[i]);
    }


    life = 3;
    id = 0;

    for(int i = 0; i < chance; i++){
        gotoxy(id, 18);
        cout << life;
        id += 2;

    }

}




struct walk
{
    int walk_count;
    int x;
    int y;
    int Back;
};

struct target
{
    int x;
    int y;
};

struct user
{
    string name[20];
    int high_score[20];
};

vector<target>walk_arr;
vector<walk>Array;



void AddArray(int x, int y, int wc, int Back)
{
    if(tmp_map[y][x] == ' ' || tmp_map[y][x] == '.')
    {
        tmp_map[y][x] = '#';
        walk tmp;
        tmp.x = x;
        tmp.y = y;
        tmp.walk_count = wc;
        tmp.Back = Back;
        Array.push_back(tmp);
    }
}

void FindPath(int sx, int sy, int x, int y)
{
    memcpy(tmp_map, maze, sizeof(maze));
    Array.clear();
    walk tmp;
    tmp.x = sx;
    tmp.y = sy;
    tmp.walk_count = 0;
    tmp.Back = -1;
    Array.push_back(tmp);

    int i = 0;
    while(i < Array.size())
    {
        if(Array[i].x == x && Array[i].y == y)
        {
            walk_arr.clear();
            target tmp2;
            while(Array[i].walk_count != 0)
            {
                tmp2.x = Array[i].x;
                tmp2.y = Array[i].y;
                walk_arr.push_back(tmp2);
                i = Array[i].Back;
            }

            break;
        }

        AddArray(Array[i].x+1,Array[i].y,Array[i].walk_count+1,i);
        AddArray(Array[i].x-1,Array[i].y,Array[i].walk_count+1,i);
        AddArray(Array[i].x,Array[i].y+1,Array[i].walk_count+1,i);
        AddArray(Array[i].x,Array[i].y-1,Array[i].walk_count+1,i);

        i++;
    }

    Array.clear();
}


void welcome()
{
    printf("\n                                            Welcome to Eat and Run Game\n");
    printf("Instruction:\n1. Arrow Keys to move your hero\n2. Eat the dots produced by the Eater to gain points\n3. Don't get caught by the Enemy\n");
}

void choose_level()
{
    printf("Please choose your difficulty: \n");
    printf("H -> Hard\nM -> Medium\nE -> Easy\n\nChoose Difficulty : ");

}

void Run(char diffi)
{

    //int player = 2;



    bool running = true;
    int x = 15; // hero x
    int y = 16; // hero y
    int old_x;
    int old_y;


    int ex = 1; //enemy x
    int ey = 1; //enemy y


    int speedmod = 3;




    if(diffi == 'M')
    {
        speedmod = 2;
    }
    else if(diffi == 'H')
    {
        speedmod = 1;
    }


    ShowMap();


    gotoxy(x, y);


    int frame = 0;

    FindPath(ex,ey,x,y);

    while(running)
    {
        gotoxy(x, y);
        cout << " ";


        old_x = x;
        old_y = y;

        if(GetAsyncKeyState(VK_UP))
        {
            if(maze[y-1][x] == '.')
            {
                maze[y - 1][x] = ' ';
                y--;
                pts++;

            }
            else if(maze[y-1][x] == ' ')
                y--;
        }
        if(GetAsyncKeyState(VK_DOWN))
        {
            if(maze[y+1][x] == '.')
            {
                maze[y + 1][x] = ' ';
                y++;
                pts++;

            }
            else if(maze[y+1][x] == ' ')
                y++;
        }
        if(GetAsyncKeyState(VK_LEFT))
        {
            if(maze[y][x-1] == '.')
            {
                maze[y][x - 1] = ' ';
                x--;
                pts++;

            }
            else if( maze[y][x-1] == ' ')
                x--;
        }
        if(GetAsyncKeyState(VK_RIGHT))
        {
            if(maze[y][x+1] == '.')
            {
                maze[y][x + 1] = ' ';
                x++;
                pts++;

            }
            else if(maze[y][x+1] == ' ')
                x++;
        }

        if(old_x != x || old_y != y)
        {
            FindPath(ex,ey,x,y);
        }


        gotoxy(x,y);
        char ch = 2;//player

        cout << ch;


        maze[ey][ex] = '.';
        gotoxy(ex,ey);

        printf(".");

        if(frame % speedmod == 0 && walk_arr.size() != 0)
        {
            ex = walk_arr.back().x;
            ey = walk_arr.back().y;
            walk_arr.pop_back();
        }

        gotoxy(ex,ey);

        char ch1 = 4;//enemy

        cout << ch1;

        if(ex == x && ey == y)
        {
            break;
        }

        gotoxy(32, 18);
        gotoxy(32, 1);
        cout << pts;
        if(pts >= 80 and life_20 == 0){
            life_20++;
            chance++;
            gotoxy(id, 18);
            id += 2;
            cout << life;
        }
        else if(pts >= 50 and pts < 80 and life_50 == 0){
            life_50++;
            chance++;
            gotoxy(id, 18);
            id += 2;
            cout << life;
        }

        Sleep(100);
        frame++;

    }

    //system("cls");



}


void reset()
{
    for(int i = 0; i < 18; i++)
    {
        for(int j = 0; j < 32; j++)
        {
            if(maze[i][j] == '.')
                maze[i][j] = ' ';
        }
    }

}



int main()
{
    life_20 = 0;
    life_50 = 0;
    life_100 = 0;
    system("COLOR A");
    gotoxy(50,2);
    cout << "Eat and Run";
    gotoxy(52,3);
    cout << "Loading";
    for(int k = 30; k <= 80; k++)
    {
        gotoxy(k,7);
        cout << '.';
    }
    for(int k = 30; k <= 80; k++)
    {
        gotoxy(k,7);
        cout << '<';
        Sleep(100);
        gotoxy(k,7);
        cout << ' ';
    }

    system("cls");


    welcome();
    choose_level();
    char diffi;
    cin >> diffi;
    system("cls");
    pts = 0;


    chance = 3;

    while(chance > 0)
    {

        system("cls");
        Run(diffi);
        reset();
        chance--;






    }
    system("cls");

    cout << "Game over \nFinal Score is : " << pts << endl;
    Sleep(10000);



    return 0;
}




