// zombies.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the trivial
// functions (marked TRIVIAL).  Then get Island::display going.  That gives
// you more flexibility in the order you tackle the rest of the functionality.
// As you finish implementing each TODO: item, remove its TODO: comment.

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;             // max number of rows on the island
const int MAXCOLS = 40;             // max number of columns on the island
const int MAXZOMBIES = 180;         // max number of zombies allowed

const int UP    = 0;
const int DOWN  = 1;
const int LEFT  = 2;
const int RIGHT = 3;

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Island;  // This is needed to let the compiler know that Island is a
               // type name, since it's mentioned in the Zombie declaration.

class Zombie
{
  public:
        // Constructor
    Zombie(Island* ip, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;

        // Mutators
    void move();

  private:
    Island* m_island;
    int     m_row;
    int     m_col;
};

class Player
{
  public:
        // Constructor
    Player(Island *ip, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    bool isDead() const;

        // Mutators
    string takeComputerChosenTurn();
    void   stand();
    void   move(int dir);
    bool   shoot(int dir);
    void   setDead();

  private:
    Island* m_island;
    int     m_row;
    int     m_col;
    int     m_age;
    bool    m_dead;
};

class Island
{
  public:
        // Constructor/destructor
    Island(int nRows, int nCols);
    ~Island();

        // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     zombieCount() const;
    int     nZombiesAt(int r, int c) const;
    void    display(string msg) const;

        // Mutators
    bool   addZombie(int r, int c);
    bool   addPlayer(int r, int c);
    bool   destroyZombie(int r, int c);
    bool   moveZombies();

  private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Zombie* m_zombies[MAXZOMBIES];
    int     m_nZombies;
};

class Game
{
  public:
        // Constructor/destructor
    Game(int rows, int cols, int nZombies);
    ~Game();

        // Mutators
    void play();

  private:
    Island* m_island;
};

///////////////////////////////////////////////////////////////////////////
//  Zombie implementation
///////////////////////////////////////////////////////////////////////////

Zombie::Zombie(Island* ip, int r, int c)
{
    if (ip == NULL)
    {
        cout << "***** A zombie must be on some Island!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ip->rows()  ||  c < 1  ||  c > ip->cols())
    {
        cout << "***** Zombie created with invalid coordinates (" << r << ","
             << c << ")!" << endl;
        exit(1);
    }
    m_island = ip;
    m_row = r;
    m_col = c;
}

int Zombie::row() const
{
    return m_row;
}

int Zombie::col() const
{
    // TODO: TRIVIAL:  return what column the Zombie is at
    return 1;  // this is wrong -- replace it
}

void Zombie::move()
{
      // Attempt to move in a random direction; if we can't move, don't move
    switch (rand() % 4)
    {
      case UP:
        // TODO:  Move the zombie up one row if possible.
        break;
      case DOWN:
      case LEFT:
      case RIGHT:
        // TODO:  Implement the other movements.
        break;
    }
}

///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

Player::Player(Island* ip, int r, int c)
{
    if (ip == NULL)
    {
        cout << "***** The player must be on some Island!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ip->rows()  ||  c < 1  ||  c > ip->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
             << "," << c << ")!" << endl;
        exit(1);
    }
    m_island = ip;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_dead = false;
}

int Player::row() const
{
    // TODO:  TRIVIAL:  return the row the player is at
    return 1;  // this is wrong -- replace it
}

int Player::col() const
{
    // TODO:  TRIVIAL:  return the column the player is at
    return 1;  // this is wrong -- replace it
}

int Player::age() const
{
    // TODO:  TRIVIAL:  return the player's age
    return 0;  // this is wrong -- replace it
}

string Player::takeComputerChosenTurn()
{
    // TODO:  replace this implementation:
        stand();
        return "Stood";
    // Your replacement implementation should do something intelligent
    // and return a string that describes what happened.  When you've
    // decided what action to take, take it by calling move, shoot, or stand.
    // This function must return one of the following four strings:
    //     "Moved."
    //     "Shot and hit!"
    //     "Shot and missed!"
    //     "Stood."

    // Here's one possible strategy:
    //   If moving in some direction would put me in less immediate danger
    //     than standing, then move in that direction.
    //   else shoot in the direction of the nearest zombie I can hit.

    // A more aggressive strategy is possible, where you hunt down zombies.
}

void Player::stand()
{
    m_age++;
}

void Player::move(int dir)
{
    m_age++;
    switch (dir)
    {
      case UP:
        // TODO:  Move the player up one row if possible.
        break;
      case DOWN:
      case LEFT:
      case RIGHT:
        // TODO:  Implement the other movements.
        break;
    }
}

bool Player::shoot(int dir)
{
    m_age++;

    if (rand() % 3 != 0)  // miss with 2/3 probability
        return false;

    // TODO:  destroy the nearest zombie in direction dir
    return false;  // this is wrong -- replace it
}

bool Player::isDead() const
{
    // TODO:  TRIVIAL:  return whether the player is dead
    return false;  // this is wrong -- replace it
}

void Player::setDead()
{
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Island implementations
///////////////////////////////////////////////////////////////////////////

Island::Island(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Island created with invalid size " << nRows << " by "
             << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = NULL;
    m_nZombies = 0;
}

Island::~Island()
{
    // TODO:  delete the player and all remaining dynamically allocated zombies
}

int Island::rows() const
{
    // TODO:  TRIVIAL:  return the number of rows in the island
    return 1;  // this is wrong -- replace it
}

int Island::cols() const
{
    // TODO:  TRIVIAL:  return the number of columns in the island
    return 1;  // this is wrong -- replace it
}

Player* Island::player() const
{
    return m_player;
}

int Island::zombieCount() const
{
    return m_nZombies;
}

int Island::nZombiesAt(int r, int c) const
{
    // TODO:  return the number of zombies at row r, column c
    return 0;  // this is wrong -- replace it
}

void Island::display(string msg) const
{
      // Position (row,col) in the island coordinate system is represented in
      // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
        // Fill the grid with dots
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';

        // Indicate each zombie's position
    // TODO:  If one zombie is at some grid point, set the char to 'Z'.
    //        If it's 2 though 8, set it to '2' through '8'.
    //        For 9 or more, set it to '9'.

        // Indicate player's position
    if (m_player != NULL)
    {
          // Set the char to '@', unless there's also a zombie there,
          // in which case set it to '*'.
        char& gridChar = grid[m_player->row()-1][m_player->col()-1];
        if (gridChar == '.')
            gridChar = '@';
        else
            gridChar = '*';
    }

        // Draw the grid
    clearScreen();
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;

        // Write message, zombie, and player info
    cout << endl;
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << zombieCount() << " zombies remaining." << endl;
    if (m_player == NULL)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isDead())
            cout << "The player is dead." << endl;
    }
}

bool Island::addZombie(int r, int c)
{
    // If MAXZOMBIES have already been added, return false.  Otherwise,
    // dynamically allocate a new zombie at coordinates (r,c).  Save the
    // pointer to the newly allocated zombie and return true.
      // TODO:  Implement this
    return false;  // this is wrong -- replace it
}

bool Island::addPlayer(int r, int c)
{
      // Don't add a player if one already exists
    if (m_player != NULL)
        return false;

      // Dynamically allocate a new Player and add it to the island
    m_player = new Player(this, r, c);
    return true;
}

bool Island::destroyZombie(int r, int c)
{
    // TODO:  destroy one zombie at row r, column c
    return false;  // this is wrong -- replace it
}

bool Island::moveZombies()
{
    for (int k = 0; k < m_nZombies; k++)
    {
      // TODO:  Have the k-th zombie on the island make one move.
      //        If that move results in that zombie being in the same
      //        position as the player, the player dies.
    }

      // return true if the player is still alive, false otherwise
    return ! m_player->isDead();
}

///////////////////////////////////////////////////////////////////////////
//  Game implementations
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nZombies)
{
    if (nZombies > MAXZOMBIES)
    {
        cout << "***** Trying to create Game with " << nZombies
             << " zombies; only " << MAXZOMBIES << " are allowed!" << endl;
        exit(1);
    }

        // Create island
    m_island = new Island(rows, cols);

        // Add player
    int rPlayer = 1 + rand() % rows;
    int cPlayer = 1 + rand() % cols;
    m_island->addPlayer(rPlayer, cPlayer);

      // Populate with zombies
    while (nZombies > 0)
    {
        int r = 1 + rand() % rows;
        int c = 1 + rand() % cols;
          // Don't put a zombie where the player is
        if (r == rPlayer  &&  c == cPlayer)
            continue;
        m_island->addZombie(r, c);
        nZombies--;
    }
}

Game::~Game()
{
    delete m_island;
}

void Game::play()
{
    Player* p = m_island->player();
    if (p == NULL)
    {
        m_island->display("");
        return;
    }
    string msg = "";
    do
    {
        m_island->display(msg);
        msg = "";
        cout << endl;
        cout << "Move (u/d/l/r/su/sd/sl/sr/c//q): ";
        string action;
        getline(cin,action);
        if (action.size() == 0)
            p->stand();
        else
        {
            switch (action[0])
            {
              default:   // if bad move, nobody moves
                cout << '\a' << endl;  // beep
                continue;
              case 'q':
                return;
              case 'c':  // computer moves player
                msg = p->takeComputerChosenTurn();
                break;
              case 'u':
              case 'd':
              case 'l':
              case 'r':
                p->move(decodeDirection(action[0]));
                break;
              case 's':
                if (action.size() < 2)  // if no direction, nobody moves
                {
                    cout << '\a' << endl;  // beep
                    continue;
                }
                switch (action[1])
                {
                  default:   // if bad direction, nobody moves
                    cout << '\a' << endl;  // beep
                    continue;
                  case 'u':
                  case 'd':
                  case 'l':
                  case 'r':
                    if (p->shoot(decodeDirection(action[1])))
                        msg = "Hit!";
                    else
                        msg = "Missed!";
                    break;
                }
                break;
            }
        }
        m_island->moveZombies();
    } while ( ! m_island->player()->isDead()  &&  m_island->zombieCount() > 0);
    m_island->display(msg);
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir)
{
    switch (dir)
    {
      case 'u':  return UP;
      case 'd':  return DOWN;
      case 'l':  return LEFT;
      case 'r':  return RIGHT;
    }
    return -1;  // bad argument passed in!
}

#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                                                        &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <cstring>

void clearScreen()
{
    static const char* term = getenv("TERM");
    static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
    if (term == NULL  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
}

#endif

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

int main()
{
      // Initialize the random number generator.  (You don't need to
      // understand how this works.)
    srand(static_cast<unsigned int>(time(0)));

      // Create a game
      // Use this instead to create a mini-game:   Game g(3, 3, 2);
    Game g(15, 18, 100);

      // Play the game
    g.play();
}