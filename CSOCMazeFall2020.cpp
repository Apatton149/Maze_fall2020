// CSOCMazeFall2020.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <array>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

class Character
{
public:
    Character(const std::string& i_name,
              const int&         i_range,
              const int&         i_x,
              const int&         i_y);
    ~Character();

    std::string              m_name;         // player character class
    unsigned int             m_range;        // how close to a monster you have to be to hit it
    unsigned int             m_x;            // player x position 
    unsigned int             m_y;            // player y position
    unsigned int             m_gold;         // treasure
    unsigned int             m_rubies;       // treasure
    std::vector<std::string> m_magicalItems; // treasure


};

Character::Character(const std::string& i_name,
                     const int&         i_range,
                     const int&         i_x,
                     const int&         i_y):
    m_name(i_name),
    m_range(i_range),
    m_x(i_x),
    m_y(i_y),
    m_gold(0),
    m_rubies(0),
    m_magicalItems()
{
}

Character::~Character()
{
}


// Maze arrays 5x5 10x10 15x15 and 20x20
const char maze5x5[20][20] = { {'#',' ','#','#','#','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                               {'#',' ',' ',' ','#','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                               {'#','#','#',' ','#','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                               {'#',' ','T',' ','#','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                               {'#','E','#','#','#','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                               {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                               {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                               {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                               {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                               {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                               {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                               {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                               {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                               {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                               {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                               {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                               {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                               {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                               {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                               {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'} };

const char maze10x10[20][20] = { {' ','#','#','#','#','#','#','#','#','#','$','$','$','$','$','$','$','$','$','$'},
                                 {' ',' ',' ','#','#','#','#','#','#','#','$','$','$','$','$','$','$','$','$','$'},
                                 {'#','#',' ','#',' ',' ',' ',' ','T','#','$','$','$','$','$','$','$','$','$','$'},
                                 {'#','#',' ',' ',' ','#','#','#',' ','#','$','$','$','$','$','$','$','$','$','$'},
                                 {'#','#',' ','#','#','#','#','#','E','#','$','$','$','$','$','$','$','$','$','$'},
                                 {'#','M',' ','#','#','#','#','#','#','#','$','$','$','$','$','$','$','$','$','$'},
                                 {'#',' ','#','#','#','#','#','#','#','#','$','$','$','$','$','$','$','$','$','$'},
                                 {'#',' ',' ',' ','#','#','#','#','#','#','$','$','$','$','$','$','$','$','$','$'},
                                 {'#','#','#','*','*','#','#','#','#','#','$','$','$','$','$','$','$','$','$','$'},
                                 {'#','#',' ',' ','#','#','#','#','#','#','$','$','$','$','$','$','$','$','$','$'},
                                 {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                                 {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                                 {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                                 {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                                 {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                                 {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                                 {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                                 {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                                 {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                                 {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'} };

const char maze15x15[20][20] = { {'#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','$','$','$','$','$'},
                                 {'#',' ','#','#','#','#','#','#','#','#','#','#','#','T','#','$','$','$','$','$'},
                                 {'#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#','$','$','$','$','$'},
                                 {'#',' ',' ','#','#','#','#','#','#','#','#',' ',' ',' ','#','$','$','$','$','$'},
                                 {'#','M',' ',' ','#','#','#','#','#','#','#',' ','#','#','#','$','$','$','$','$'},
                                 {'#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','$','$','$','$','$'},
                                 {'#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','$','$','$','$','$'},
                                 {'#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','$','$','$','$','$'},
                                 {'#',' ',' ',' ','#','#','#','#','#','M',' ',' ',' ',' ','E','$','$','$','$','$'},
                                 {'#',' ','#',' ','#','#','#','#','#',' ','#','#','#','#','#','$','$','$','$','$'},
                                 {'#',' ','#',' ',' ',' ','#','#','#',' ','#','#','#','#','#','$','$','$','$','$'},
                                 {'#','#','#','#','#',' ','#','#','#',' ','#','#','#','#','#','$','$','$','$','$'},
                                 {'#','#','#','#','#',' ','#','#','#',' ','#','#','#','#','#','$','$','$','$','$'},
                                 {'#','#','#','#','#',' ',' ',' ',' ',' ','#','#','#','#','#','$','$','$','$','$'},
                                 {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','$','$','$','$','$'},
                                 {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                                 {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                                 {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                                 {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
                                 {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'} };

const char maze20x20[20][20] = { {'#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
                                 {'#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#'},
                                 {'#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#'},
                                 {'#',' ',' ','#','#','#','#','#','#','#','#','#','#','#','#',' ',' ',' ','#','#'},
                                 {'#',' ',' ',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#'},
                                 {'#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','M','#','#','#','#'},
                                 {'#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#'},
                                 {'#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#'},
                                 {'#','#','#','M','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ','#','#','#','#'},
                                 {'#','#','#',' ','#','#','#','#','#',' ','#','#','#','#','#',' ','#','#','#','#'},
                                 {'#','#','#',' ',' ',' ','#','#','#',' ','#','#','#','#','#',' ','#','#','#','#'},
                                 {'#','#','#','#','#',' ','#','#','#',' ','#','#','#','#','#',' ','#','#','#','#'},
                                 {'#','#','#','#','#',' ','#','#','#',' ','#','#','#','#','#','T',' ',' ','#','#'},
                                 {'#','#','#','#','#',' ',' ',' ',' ',' ','#','#','#','#','#','#','#',' ','#','#'},
                                 {'#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#','#'},
                                 {'#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#','#'},
                                 {'#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#','#'},
                                 {'#','#','#','#','#','#',' ',' ','#','#','#','#','#','#','#','#',' ',' ','#','#'},
                                 {'#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','T','#','#','#'},
                                 {'#','#','#','#','#','#','E','#','#','#','#','#','#','#','#','#','#','#','#','#'} };


int main()
{


    bool play = true;
    while (play)
    {
        // Title screen for player to choose a character type, and maze size. 

        std::cout << R"(
   *                                          (                           
 (  `                                (        )\ )                        
 )\))(       )          (            )\ )    (()/(                   )    
((_)()\   ( /(   (     ))\      (   (()/(     /(_))    (     (      (     
(_()((_)  )(_))  )\   /((_)     )\   /(_))   (_))_     )\    )\     )\  ' 
|  \/  | ((_)_  ((_) (_))      ((_) (_) _|    |   \   ((_)  ((_)  _((_))  
| |\/| | / _` | |_ / / -_)    / _ \  |  _|    | |) | / _ \ / _ \ | '  \() 
|_|  |_| \__,_| /__| \___|    \___/  |_|      |___/  \___/ \___/ |_|_|_| 

Character Selection: Please type in a number and press enter.
1.) Fighter
2.) Archer 
                                                                          
)" << std::endl;
        // while loop for when they reach the end of the maze

        // validiating character selection
        int  userCharacter;
        bool userCharacterValid = false;
        std::string userCharacterClass = "";
        int         userCharacterRange = 0;

        while (not userCharacterValid)
        {
            cin >> userCharacter;
            if (userCharacter == 1)
            {
                std::cout << "You have chosen to be a Fighter!" << endl;
                userCharacterValid = true;
                userCharacterClass = "Fighter";
                userCharacterRange = 1;
            }
            else if (userCharacter == 2)
            {
                std::cout << "You have chose to be a Archer!" << endl;
                userCharacterValid = true;
                userCharacterClass = "Archer";
                userCharacterRange = 1;
            }
            else // need this to loop back to the select screen
            {
                std::cout << "You have chosen and invalid ooption, please try again." << endl;
            }
        }

        // validating maze selection
        std::cout << "Please select a maze level 1 through 4, and press enter." << std::endl;
        int mazeLevel;
        bool mazeLevelValid = false;
        int  mazeSize = 0;
        int  mazeStartX = 0;
        int  mazeStartY = 0;
        char maze[20][20];

        while (not mazeLevelValid)
        {
            cin >> mazeLevel;
            if (mazeLevel == 1)
            {
                std::cout << "You have chosen maze 1!" << endl;
                mazeLevelValid = true;
                mazeSize = 5;
                mazeStartX = 1;
                std::copy(&maze5x5[0][0], &maze5x5[0][0] + 20 * 20, &maze[0][0]);
            }
            else if (mazeLevel == 2)
            {
                std::cout << "You have chosen maze 2!" << endl;
                mazeLevelValid = true;
                mazeSize = 10;
                std::copy(&maze10x10[0][0], &maze10x10[0][0] + 20 * 20, &maze[0][0]);
            }
            else if (mazeLevel == 3)
            {
                std::cout << "You have chosen maze 3!" << endl;
                mazeLevelValid = true;
                mazeSize = 15;
                mazeStartX = 1;
                std::copy(&maze15x15[0][0], &maze15x15[0][0] + 20 * 20, &maze[0][0]);
            }
            else if (mazeLevel == 4)
            {
                std::cout << "You have chosen maze 4!" << endl;
                mazeLevelValid = true;
                mazeSize = 20;
                mazeStartX = 1;
                std::copy(&maze20x20[0][0], &maze20x20[0][0] + 20 * 20, &maze[0][0]);
            }
            else
            {
                std::cout << "You have chosen an invalid option, please try again." << endl;
            }
        }

        // create character
        Character player(userCharacterClass, userCharacterRange, mazeStartX, mazeStartY);

        // print each row of maze
        while (maze[player.m_y][player.m_x] != 'E')
        {
            for (int y = 0; y < mazeSize; ++y)
            {
                // print each column of maze
                for (int x = 0; x < mazeSize; ++x)
                {
                    // Printing player location in the maze
                    if ((player.m_x == x) and (player.m_y == y))
                    {
                        std::cout << "P";
                    }
                    // Printing the maze
                    else
                    {
                        std::cout << maze[y][x];
                    }
                }

                // print newline after each row
                std::cout << std::endl;
            }

            //Player controls
            std::cout << "Please use 'A' 'W' 'S' or 'D' to move player icon. K for attack, O to open treasure, and E to exit the maze!" << std::endl;

            char playerControl;

            std::cin >> playerControl;


            //Assigning keys for player controls

            int newPlayerLocationX = player.m_x;
            int newPlayerLocationY = player.m_y;
            bool openTreasure = false;
            bool attack = false;
            bool exitMaze = false;

            switch (playerControl) //movement
            {
            case 'A':
            case 'a':
                newPlayerLocationX -= 1; // subtracts and set the new player location variable
                break;
            case 'S':
            case 's':
                newPlayerLocationY += 1;
                break;
            case 'D':
            case 'd':
                newPlayerLocationX += 1;
                break;
            case 'W':
            case 'w':
                newPlayerLocationY -= 1;
                break;
            case 'O':
            case 'o':
                openTreasure = true;
                break;
            case 'K':
            case'k':
                attack = true;
                break;
            case 'E':
            case 'e':
                exitMaze = true; //takes player to the title screen
            }


            // comparing cases with array walls for valid moves using mazeSize

            if ((newPlayerLocationX < 0) or (newPlayerLocationX > mazeSize) or (newPlayerLocationY < 0) or (newPlayerLocationY > mazeSize))
            {
                std::cout << "Invalid entry, please try again." << std::endl;
            }

            // Checking to see if a player hits a wall
            else if (maze[newPlayerLocationY][newPlayerLocationX] == '#')
            {
                std::cout << "You hit a wall, try again." << std::endl;
            }

            // Checking to see if a player has run into a monster
            else if (maze[newPlayerLocationY][newPlayerLocationX] == 'M')
            {
                std::cout << "You've found a monster! Hit K to attack it or else you can't leave the maze!" << std::endl;
            }
            // checking to see if player has found treasure
            else if (maze[newPlayerLocationY][newPlayerLocationX] == 'T')
            {
                std::cout << "You've found some treasure! It may be useful later! Press O to open it!" << std::endl;
            }
            //checking if the player has found the exit
            else if (maze[newPlayerLocationY][newPlayerLocationX] == 'E')
            {
                std::cout << "You have found the exit, press E to leave." << std::endl;
            }

            //Assuming all unallowable moves were caught, then move must be allowable.
            else
            {
                player.m_x = newPlayerLocationX;
                player.m_y = newPlayerLocationY;
            }

            // Checking for treasure by checking the surrounding locations for 'T'
            if (openTreasure)
            {
                char blankChar = ' ';

                // Checking below the player
                if (player.m_y + 1 < mazeSize)
                {
                    if (maze[player.m_y + 1][player.m_x + 0] == 'T')
                    {
                        std::cout << "You found 10 gold!" << std::endl;
                        player.m_gold += 10;
                        // replacing 'T' with a ' ' to "remove" treasure.
                        std::memcpy(&maze[player.m_y + 1][player.m_x + 0], &blankChar, 1);
                    }
                }

                // Checking above player
                if (player.m_y - 1 >= 0)
                {
                    if (maze[player.m_y - 1][player.m_x + 0] == 'T')
                    {
                        std::cout << "You found 10 gold!" << std::endl;
                        player.m_gold += 10;
                        std::memcpy(&maze[player.m_y - 1][player.m_x + 0], &blankChar, 1);
                    }
                }

                // Checking to the right the player
                if (player.m_x + 1 < mazeSize)
                {
                    if (maze[player.m_y + 0][player.m_x + 1] == 'T')
                    {
                        std::cout << "You found 10 gold!" << std::endl;
                        player.m_gold += 10;
                        std::memcpy(&maze[player.m_y + 0][player.m_x + 1], &blankChar, 1);
                    }
                }

                //Checking to the left the player
                if (player.m_x - 1 >= 0)
                {
                    if (maze[player.m_y + 0][player.m_x - 1] == 'T')
                    {
                        std::cout << "You found 10 gold!" << std::endl;
                        player.m_gold += 10;
                        std::memcpy(&maze[player.m_y + 0][player.m_x - 1], &blankChar, 1);
                    }
                }// follow the same process for attacking and then figure out how to loop back to the title screen. Tell player what the found in the maze. 
            }
            //checking for Monsters by checking the surrounding locations for 'M' NEED TO FIX RANGE FOR ARCHER TO TWO
            if (attack)
            {
                char blankChar = ' ';

                if (player.m_y + 1 < mazeSize)
                {
                    // checking below the character FIGHTER
                    if (maze[player.m_y + 1][player.m_x + 0] == 'M')
                    {
                        std::cout << "You killed the monster! He was just minding his own business though." << std::endl;
                        std::memcpy(&maze[player.m_y - 1][player.m_x + 0], &blankChar, 1);
                    }
                }
                if (player.m_y - 1 >= 0)
                {
                    if (maze[player.m_y - 1][player.m_x + 0] == 'M')
                    {
                        std::cout << "You killed the monster! He was just minding his own business though." << std::endl;
                        std::memcpy(&maze[player.m_y - 1][player.m_x + 0], &blankChar, 1);
                    }
                }

                // Checking to the right the player
                if (player.m_x + 1 < mazeSize)
                {
                    if (maze[player.m_y + 0][player.m_x + 1] == 'M')
                    {
                        std::cout << "You killed the monster! He was just minding his own business though." << std::endl;
                        std::memcpy(&maze[player.m_y + 0][player.m_x + 1], &blankChar, 1);
                    }
                }

                //Checking to the left the player
                if (player.m_x - 1 >= 0)
                {
                    if (maze[player.m_y + 0][player.m_x - 1] == 'M')
                    {
                        std::cout << "You killed the monster! He was just minding his own business though." << std::endl;
                        std::memcpy(&maze[player.m_y + 0][player.m_x - 1], &blankChar, 1);
                    }

                }

            }
            if (exitMaze)
            {
                char blankChar = ' ';

                if (player.m_y + 1 < mazeSize)
                {
                    // checking below the character for the exit
                    if (maze[player.m_y + 1][player.m_x + 0] == 'O')
                    {
                        std::cout << "You survived the maze!" << std::endl;
                        std::memcpy(&maze[player.m_y - 1][player.m_x + 0], &blankChar, 1);
                    }
                }
                if (player.m_y - 1 >= 0)
                {
                    if (maze[player.m_y - 1][player.m_x + 0] == 'O')
                    {
                        std::cout << "You survived the maze!" << std::endl;
                        std::memcpy(&maze[player.m_y - 1][player.m_x + 0], &blankChar, 1);
                    }
                }

                // Checking to the right the player
                if (player.m_x + 1 < mazeSize)
                {
                    if (maze[player.m_y + 0][player.m_x + 1] == 'O')
                    {
                        std::cout << "You survived the maze!" << std::endl;
                        std::memcpy(&maze[player.m_y + 0][player.m_x + 1], &blankChar, 1);
                    }
                }

                //Checking to the left the player
                if (player.m_x - 1 >= 0)
                {
                    if (maze[player.m_y + 0][player.m_x - 1] == 'O')
                    {
                        std::cout << "You survived the maze!" << std::endl;
                        std::memcpy(&maze[player.m_y + 0][player.m_x - 1], &blankChar, 1);
                    }

                }

            }
        }
        // loop to determine if the player wants to play again or not. 
        bool validContCheck = false; 
        while (!validContCheck)
        {
            std::cout << "Do you want to play again? type Y or N then press enter." << std::endl;
            std::string playerContinue;
            std::cin >> playerContinue;

            if (playerContinue == "N" or playerContinue == "n")
            {
                play = false;
                validContCheck = true;
            }
            else if (playerContinue == "Y" or playerContinue == "y")
            {
                play = true;
                validContCheck = true;
            }
            else
            {
                std::cout << "You can't follow directions! Try again. Or else." << std::endl;
            }
        }
    }



     

    return 0;
}



