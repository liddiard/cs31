// zombies.cpp

// Portions you are to complete are marked with a TO-DO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the trivial
// functions (marked TRIVIAL).  Then get Island::display going.  That gives
// you more flexibility in the order you tackle the rest of the functionality.
// As you finish implementing each TO-DO: item, remove its TO-DO: comment.

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
    void adjacentZombies(int r, int c, int output[4]) const; //user-added
    int sumAdjacent(int adjacentZombies[4]) const; //user-added

        // Mutators
    string takeComputerChosenTurn();
    void   stand();
    void   move(int dir);
    bool   shoot(int dir);
    void   setDead();
    bool shootNearestZombie(); //user-added

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
    bool    isValidPos(int r, int c) const; //user-added;

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
    // DONE: TRIVIAL:  return what column the Zombie is at
    return m_col;  // this is wrong -- replace it
}

void Zombie::move()
{
      // Attempt to move in a random direction; if we can't move, don't move
    switch (rand() % 4)
    {
      case UP:
        // DONE:  Move the zombie up one row if possible.
        if (this->row() > 0) {
            this->m_row--; //move up
        }
        break;
      case DOWN:
        if (this->row() < m_island->rows()-1) {
            this->m_row++; //move down
        }
          break;
      case LEFT:
        if (this->col() > 0) {
            this->m_col--; //move left
        }
          break;
      case RIGHT:
        if (this->col() < m_island->cols()-1) {
            this->m_col++; //move right
        }
          break;
        // DONE:  Implement the other movements.
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
    // DONE:  TRIVIAL:  return the row the player is at
    return m_row; 
}

int Player::col() const
{
    // DONE:  TRIVIAL:  return the column the player is at
    return m_col;
}

int Player::age() const
{
    // DONE:  TRIVIAL:  return the player's age
    return m_age;
}

void Player::adjacentZombies(int r, int c, int output[4]) const {
    //build an array of zombies adjacent to the player
    for (int i = 0; i < 4; i++) {
        output[i] = 0;
    }
    
    //top
    if (r > 1) { // if one up from the player is a valid position
        output[0] = m_island->nZombiesAt(r-1-1, c-1);
    } else {output[0] = -1;}
    
    //right
    if (c < m_island->cols()) { // if one right of the player is a valid position
        output[1] =  m_island->nZombiesAt(r-1, c+1-1);
    } else {output[1] = -1;}
    
    //down
    if (r < m_island->rows()) { // if one down from the player is a valid position
        output[2] =  m_island->nZombiesAt(r+1-1, c-1);
    } else {output[2] = -1;}
    
    //left
    if (c > 1) { // if one right of the player is a valid position
        output[3] =  m_island->nZombiesAt(r-1, c-1-1);
    } else {output[3] = -1;}
    
}

bool Player::shootNearestZombie() {
    int closestZombieInDir[4] = {1024,1024,1024,1024};

    //up
    for (int i = this->row(); i > 0; i--) {
        if (m_island->nZombiesAt(i, this->col()-1)) {
            closestZombieInDir[0] = abs(i - this->row());
            break;
        }
    }

    //down
    for (int i = this->row(); i <= m_island->rows(); i++) { //FLAG: might need to be changed to '<'
        if (m_island->nZombiesAt(i, this->col()-1)) {
            closestZombieInDir[1] = abs(i - this->row());
            break;
        }
    }

    //left
    for (int i = this->col(); i > 0; i--) {
        if (m_island->nZombiesAt(this->row()-1, i)) {
            closestZombieInDir[2] = abs(i - this->col());
            break;
        }
    }

    //right
    for (int i = this->col(); i <= m_island->cols(); i++) { //FLAG: might need to be changed to '<'
        if (m_island->nZombiesAt(this->row()-1, i)) {
            closestZombieInDir[3] = abs(i - this->col());
            break;
        }
    }
    
    /* DEBUG
    for (int i = 0; i < 4; i++) {
        cerr << closestZombieInDir[i] << ", ";
    }
    */
    
    if (closestZombieInDir[0] < closestZombieInDir[1] && closestZombieInDir[0] < closestZombieInDir[2] && closestZombieInDir[0] < closestZombieInDir[3]) {
        return this->shoot(UP);
    } else if (closestZombieInDir[1] < closestZombieInDir[0] && closestZombieInDir[1] < closestZombieInDir[2] && closestZombieInDir[1] < closestZombieInDir[3]) {
        return this->shoot(DOWN);
    } else if (closestZombieInDir[2] < closestZombieInDir[0] && closestZombieInDir[2] < closestZombieInDir[1] && closestZombieInDir[2] < closestZombieInDir[3]) {
        return this->shoot(LEFT);
    } else {
        return this->shoot(RIGHT);
    }
}

int Player::sumAdjacent(int adjacentZombies[4]) const {
    int totalAdjacent = 0;
    for (int i = 0; i < 4; i++) {
        if (adjacentZombies[i] != -1)
            totalAdjacent += adjacentZombies[i];
    }
    return totalAdjacent;
}

string Player::takeComputerChosenTurn()
{
    int adjacentZombies[4] = {0,0,0,0};
    this->adjacentZombies(this->row(), this->col(), adjacentZombies);
    
    //if there aren't any adjacent zombies, blast the nearest one
    if (!sumAdjacent(adjacentZombies)) {
        bool hit;
        hit = this->shootNearestZombie();
        if (hit) {
            return "Shot and hit!";
        } else {
            return "Shot and missed!";
        }
    } else {
        int scope[4] = {1024,1024,1024,1024};
        int adjacentZombiesTop[4] = {8,8,8,8};
        int adjacentZombiesRight[4] = {8,8,8,8};
        int adjacentZombiesDown[4] = {8,8,8,8};
        int adjacentZombiesLeft[4] = {8,8,8,8};
        
        //top
        if (m_island->isValidPos(this->row()-1, this->col())) {
            this->adjacentZombies(this->row()-1, this->col(), adjacentZombiesTop);
            scope[0] = this->sumAdjacent(adjacentZombiesTop);
        }
        
        //right
        if (m_island->isValidPos(this->row(), this->col()+1)) {
            this->adjacentZombies(this->row(), this->col()+1, adjacentZombiesRight);
            scope[1] = this->sumAdjacent(adjacentZombiesRight);
        }
        
        //down
        if (m_island->isValidPos(this->row()+1, this->col())) {
            this->adjacentZombies(this->row()+1, this->col(), adjacentZombiesDown);
            scope[2] = this->sumAdjacent(adjacentZombiesDown);
        }
        
        //left
        if (m_island->isValidPos(this->row(), this->col()-1)) {
            this->adjacentZombies(this->row(), this->col()-1, adjacentZombiesLeft);
            scope[3] = this->sumAdjacent(adjacentZombiesLeft);
        }
        
        /* DEBUG
        for (int i = 0; i < 4; i++) {
            cerr << scope[i] << ", ";
        }
        */
        
        if (scope[0] <= scope[1] && scope[0] <= scope[2] && scope[0] <= scope[3]) {
            this->move(UP);
        } else if (scope[1] <= scope[0] && scope[1] <= scope[2] && scope[1] <= scope[3]) {
            this->move(DOWN);
        } else if (scope[2] <= scope[0] && scope[2] <= scope[1] && scope[2] <= scope[3]) {
            this->move(LEFT);
        } else {
            this->move(RIGHT);
        }
        
        return "Moved.";
    }
        
    // DONE:  replace this implementation.
    
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
    return "Busted a move.";
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
        // DONE:  Move the player up one row if possible.
        if (this->row() > 1) {
            this->m_row--; //move up
        }
          break;
      case DOWN:
        if (this->row() < m_island->rows()) {
            this->m_row++; //move down
        }
          break;
      case LEFT:
        if (this->col() > 1) {
            this->m_col--; //move left
        }
          break;
      case RIGHT:
        if (this->col() < m_island->cols()) {
            this->m_col++; //move right
        }
          break;
        // DONE:  Implement the other movements.
    }
}

bool Player::shoot(int dir)
{
    m_age++;

    if (rand() % 3 != 0)  // miss with 2/3 probability
        return false;
    switch(dir) {
        case UP:
            for (int i = this->row(); i > 0; i--) {
                if (m_island->nZombiesAt(i, this->col()-1)) {
                    m_island->destroyZombie(i, this->col()-1);
                    return true;
                }
            }
            return false;
        case DOWN:
            for (int i = this->row(); i <= m_island->rows(); i++) { //FLAG: might need to be changed to '<'
                if (m_island->nZombiesAt(i, this->col()-1)) {
                    m_island->destroyZombie(i, this->col()-1);
                    return true;
                }
            }
            return false;
        case LEFT:
            for (int i = this->col(); i > 0; i--) {
                if (m_island->nZombiesAt(this->row()-1, i)) {
                    m_island->destroyZombie(this->row()-1, i);
                    return true;
                }
            }
            return false;
        case RIGHT:
            for (int i = this->col(); i <= m_island->cols(); i++) { //FLAG: might need to be changed to '<'
                if (m_island->nZombiesAt(this->row()-1, i)) {
                    m_island->destroyZombie(this->row()-1, i);
                    return true;
                }
            }
            return false;
    }
    // DONE:  destroy the nearest zombie in direction dir
    return false;
}

bool Player::isDead() const
{
    // DONE:  TRIVIAL:  return whether the player is dead
    return this->m_dead;
}

void Player::setDead()
{
    m_dead = true; //DONE: set this back to true after debugging
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
    delete m_player; //should this be a pointer?
    for (int i = 0; i < this->m_nZombies; i++) {
        delete m_zombies[i]; //should this be a pointer?
    }
    // DONE:  delete the player and all remaining dynamically allocated zombies
}

int Island::rows() const
{
    // DONE:  TRIVIAL:  return the number of rows in the island
    return m_rows;  // this is wrong -- replace it
}

int Island::cols() const
{
    // DONE:  TRIVIAL:  return the number of columns in the island
    return m_cols;  // this is wrong -- replace it
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
    // DONE:  return the number of zombies at row r, column c
    int count = 0;
    for (int i = 0; i < this->zombieCount(); i++) {
        if (m_zombies[i]->row() == r && m_zombies[i]->col() == c) {
            count++;
        }
    }
    return count;  // this is wrong -- replace it
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
    // DONE:  If one zombie is at some grid point, set the char to 'Z'.
    //        If it's 2 though 8, set it to '2' through '8'.
    //        For 9 or more, set it to '9'.
    int zombiesAtPoint = 0;
    for (r = 0; r < rows(); r++) {
        for (c = 0; c < cols(); c++) {
            zombiesAtPoint = nZombiesAt(r,c);
            if (zombiesAtPoint < 1) {
                grid[r][c] = '.';
            } else if (zombiesAtPoint == 1) {
                grid[r][c] = 'Z';                
            } else if (zombiesAtPoint < 9) {
                grid[r][c] = '0' + zombiesAtPoint;
            } else {
                grid[r][c] = '9';
            }
        }
    }

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
      // DONE:  Implement this
    if (this->zombieCount() >= MAXZOMBIES)
        return false;
    else {
        m_zombies[this->zombieCount()] = new Zombie(this, r, c);
        m_nZombies++;
        return true;
    }
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
    // DONE:  destroy one zombie at row r, column c
    for (int i = 0; i < m_nZombies; i++) {
        if (m_zombies[i]->row() == r && m_zombies[i]->col() == c) {
            delete m_zombies[i];
            m_zombies[i] = m_zombies[m_nZombies-1];
            m_zombies[m_nZombies-1] = 0;
            m_nZombies--;
            return true;
        }
    }
    return false;
}

bool Island::moveZombies()
{
    for (int k = 0; k < this->zombieCount(); k++)
    {
        this->m_zombies[k]->move();
        if (m_zombies[k]->row()+1 == m_player->row() && m_zombies[k]->col()+1 == m_player->col()) {
            this->m_player->setDead();
        }   
      // DONE:  Have the k-th zombie on the island make one move.
      //        If that move results in that zombie being in the same
      //        position as the player, the player dies.
    }


      // return true if the player is still alive, false otherwise
    return (!m_player->isDead());
}

bool Island::isValidPos(int r, int c) const {
    if (r > 0 && r <= this->rows() && c > 0 && c <= this->cols()) {
        return true;
    } else {
        return false;
    } 
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