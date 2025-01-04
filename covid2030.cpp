#include <windows.h>
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <conio.h>
#include <thread>
#include <chrono>
using namespace std;
class Colors
{
public:
    string RESET = "\033[0m";
    string GREEN = "\033[32m";
    string PURPLE = "\e[0;35m";
    string RED = "\e[0;31m";
    string YELLOW = "\e[0;33m";
    string BLUE = "\e[0;34m";
    string CYAN = "\e[0;36m";
};
void newGame();
void mainMenu();
class Player
{
public:
    int level = 1;
    int range = 5;
    int vaccine = 0;
    int credit = 0;
    int round = 1;
    int health = 3;
    int allAmmo = 3;
    int outTreasure = allAmmo - 3;
    int treasure = 3;
    int treasureCapacity = 3;

    int kills = 0;
    void printInfo()
    {
        cout << "Level: " << level << " ";
        cout << "Vaccine: " << vaccine << " ";
        cout << "Credit: " << credit << " ";
        cout << "Round: " << round << endl;
        cout << "Health: [";
        for (int i = 0; i < health; i++)
        {
            cout << " | ";
        }
        cout << "] ";
        cout << "Ammo: " << treasure << "/" << outTreasure;
        cout << " Kill: " << kills << endl;
    }
};
class UpgradeMenu
{

public:
    void printMenu(Player &player)
    {
        cout << "Upgrade Menu" << endl;
        cout << "0- Return to game" << endl;
        cout << "1- Upgrade capacity of magazine: 1 bullet" << endl;
        cout << "2- Upgrade range of shotgun: 1 times the size of the person himself (maximum is 10 times, now is 5)" << endl;
        cout << "3- Get an additional health. maximum is 5 -" << player.health << endl;
        cout << "Credit: " << player.credit << endl;
        cout << "Enter the number of the option: ";
    }

    void upgradeMagazineCapacity(Player &player)
    {
        int requiredCredit = player.treasure * (player.treasure / 2 + 1);
        if (player.credit >= requiredCredit && player.treasure < 7)
        {
            player.treasure++;
            player.credit -= requiredCredit;
            cout << "Upgrade done successfully. Your magazine capacity is now " << player.treasure << "." << endl;
        }
        else if (player.credit < requiredCredit)
        {
            cout << "Unfortunately, your credit is not enough to get this item. Please gain " << requiredCredit - player.credit << " more credit by playing." << endl;
        }
        else
        {
            cout << "The selected item is maximum." << endl;
        }
    }

    void upgradeShotgunRange(Player &player)
    {
        int requiredCredit = player.range + 1;
        if (player.credit >= requiredCredit && player.range < 10)
        {
            player.range++;
            player.credit -= requiredCredit;
            cout << "Upgrade done successfully. Your shotgun range is now " << player.range << "." << endl;
        }
        else if (player.credit < requiredCredit)
        {
            cout << "Unfortunately, your credit is not enough to get this item. Please gain " << requiredCredit - player.credit << " more credit by playing." << endl;
        }
        else
        {
            cout << "The selected item is maximum." << endl;
        }
    }

    void getAdditionalHealth(Player &player)
    {
        int requiredCredit = player.health * (player.health + 1);
        if (player.credit >= requiredCredit && player.health < 5)
        {
            player.health++;
            player.credit -= requiredCredit;
            cout << "Upgrade done successfully. Your health is now " << player.health << "." << endl;
        }
        else if (player.credit < requiredCredit)
        {
            cout << "Unfortunately, your credit is not enough to get this item. Please gain " << requiredCredit - player.credit << " more credit by playing." << endl;
        }
        else
        {
            cout << "The selected item is maximum." << endl;
        }
    }
    void displayMenu(Player &player)
    {
        int option;
        do
        {
            printMenu(player);
            cin >> option;

            switch (option)
            {
            case 0:
                cout << "Returning to game..." << endl;
                break;
            case 1:
                upgradeMagazineCapacity(player);
                break;
            case 2:
                upgradeShotgunRange(player);
                break;
            case 3:
                getAdditionalHealth(player);
                break;
            default:
                cout << "Please just enter the numbers in the menu." << endl;
            }

        } while (option != 0);
    }
};
class GameMenu
{
public:
    void displayMenu()
    {
        cout << "Game Menu:" << endl;
        cout << "0 - Return to game" << endl;
        cout << "1 - New Game" << endl;
        cout << "2 - Settings" << endl;
        cout << "3 - Exit" << endl;
    }

    void returnToGame()
    {
        cout << "Returning to the game..." << endl;
        Sleep(2000);
    }

    void startNewGame()
    {
        cout << "Starting a new game..." << endl;
        Sleep(2000);
        newGame();
    }

    void openSettings()
    {
        cout << "Opening settings..." << endl;
        Sleep(2000);

        cout << "Final level is: 20" << endl
             << "Sound is not activated!";
        Sleep(5000);
        mainMenu();
    }

    void exitGame()
    {
        cout << "Exiting the game..." << endl;
        Sleep(2000);
        exit(0);
    }

    void handleInvalidInput()
    {
        cout << "Please just enter the numbers in the menu:" << endl;
    }

    void navigateMenu()
    {
        int option;
        do
        {
            displayMenu();
            cin >> option;

            switch (option)
            {
            case 0:
                returnToGame();
                break;
            case 1:
                startNewGame();
                break;
            case 2:
                openSettings();
                break;
            case 3:
                exitGame();
                break;
            default:
                cout << "Please just enter the numbers in the menu." << endl;
            }

        } while (option != 0);
    }
};
class Spawns
{
private:
    const int width = 17;
    const int height = 19;
    vector<vector<bool>> coordinates;
    string gameBoard[17][19];
    bool isValidCoordinate(int x, int y)
    {
        return x >= 0 && x < width && y >= 0 && y < height && !coordinates[x][y];
    }

    pair<int, int> getRandomCoordinate()
    {
        int x = rand() % (width - 2) + 1;
        int y = rand() % (height - 2) + 1;
        while (!isValidCoordinate(x, y))
        {
            x = rand() % (width - 2) + 1;
            y = rand() % (height - 2) + 1;
        }
        return make_pair(x, y);
    }
    pair<int, int> getNonOverlapRandomCoordinate()
    {
        pair<int, int> coord = getRandomCoordinate();
        while (gameBoard[coord.first][coord.second] == "P" || gameBoard[coord.first][coord.second] == "D")
        {
            coord = getRandomCoordinate();
        }
        return coord;
    }

    pair<int, int> getZambieSpawnCoordinate()
    {
        pair<int, int> zambieCoord = getNonOverlapRandomCoordinate();
        pair<int, int> pCoord;
        for (int i = 0; i < width; ++i)
        {
            for (int j = 0; j < height; ++j)
            {
                if (gameBoard[i][j] == "P")
                {
                    pCoord.first = i;
                    pCoord.second = j;
                }
            }
        }

        while (abs(zambieCoord.first - pCoord.first) <= 1 || abs(zambieCoord.second - pCoord.second) <= 1)
        {
            zambieCoord = getNonOverlapRandomCoordinate();
        }
        return zambieCoord;
    }

public:
    Spawns()
    {
        coordinates.resize(width, vector<bool>(height, false));
        srand(static_cast<unsigned int>(time(nullptr)));

        for (int i = 0; i < width; ++i)
        {
            for (int j = 0; j < height; ++j)
            {
                if (i == 0 || i == width - 1 || j == 0 || j == height - 1)
                {
                    gameBoard[i][j] = (i == 0 || i == width - 1) ? "-" : "|";
                }
                else
                {
                    gameBoard[i][j] = " ";
                }
            }
        }

        gameBoard[1][1] = "P";
        gameBoard[width - 2][height - 2] = "D";
    }

    void moveZombiesTowardPlayer(Player &player)
    {
        int playerX, playerY;
        bool foundPlayer = false;

        for (int i = 0; i < width && !foundPlayer; ++i)
        {
            for (int j = 0; j < height && !foundPlayer; ++j)
            {
                if (gameBoard[i][j] == "P")
                {
                    playerX = i;
                    playerY = j;
                    foundPlayer = true;
                }
            }
        }

        for (int i = 0; i < width; ++i)
        {
            for (int j = 0; j < height; ++j)
            {
                if (gameBoard[i][j] == "Z")
                {
                    int dx = (i < playerX) ? 1 : ((i > playerX) ? -1 : 0);
                    int dy = (j < playerY) ? 1 : ((j > playerY) ? -1 : 0);

                    // Check if the new position is within bounds and not on the first or last column or row
                    int newX = i + dx;
                    int newY = j + dy;

                    // Check if the new position is not occupied by another zombie
                    if (newX > 0 && newX < width - 1 && newY > 0 && newY < height - 1 && gameBoard[newX][newY] != "P" && gameBoard[newX][newY] != "Z")
                    {
                        // Move the zombie
                        gameBoard[i][j] = " ";
                        gameBoard[newX][newY] = "Z";
                    }
                }
            }
        }
    }
    string &getGameBoardCell(int x, int y)
    {
        return gameBoard[x][y];
    }
    void zambieSpawn(int level)
    {
        for (int i = 0; i < level; ++i)
        {
            pair<int, int> zambieCoord = getZambieSpawnCoordinate();
            coordinates[zambieCoord.first][zambieCoord.second] = true;
            gameBoard[zambieCoord.first][zambieCoord.second] = "Z";
        }
    }

    void amooSpawn(int level)
    {
        for (int i = 0; i < level; ++i)
        {
            pair<int, int> amooCoord = getNonOverlapRandomCoordinate();
            coordinates[amooCoord.first][amooCoord.second] = true;
            gameBoard[amooCoord.first][amooCoord.second] = "A";
        }
    }

    void vaccineSpawn(int level)
    {
        for (int i = 0; i < level; ++i)
        {
            pair<int, int> vaccineCoord = getNonOverlapRandomCoordinate();
            coordinates[vaccineCoord.first][vaccineCoord.second] = true;
            gameBoard[vaccineCoord.first][vaccineCoord.second] = "V";
        }
    }
    string **printGameBoard()
    {
        Colors colors;
        string **result = new string *[width];
        for (int i = 0; i < width; ++i)
        {
            result[i] = new string[height];
            for (int j = 0; j < height; ++j)
            {
                result[i][j] = gameBoard[i][j];
                if (gameBoard[i][j] == "Z")
                {
                    cout << colors.RED << gameBoard[i][j] << colors.RESET;
                }
                else if (gameBoard[i][j] == "V")
                {
                    cout << colors.YELLOW << gameBoard[i][j] << colors.RESET;
                }
                else if (gameBoard[i][j] == "A")
                {
                    cout << colors.BLUE << gameBoard[i][j] << colors.RESET;
                }
                else if (gameBoard[i][j] == "P")
                {
                    cout << colors.GREEN << gameBoard[i][j] << colors.RESET;
                }
                else if (gameBoard[i][j] == "D")
                {
                    cout << colors.PURPLE << gameBoard[i][j] << colors.RESET;
                }
                else
                {
                    cout << gameBoard[i][j];
                }
            }
            cout << endl;
        }
        return result;
    }
    void moveShootStuff(Player &player, Spawns &spawns)
    {

        while (true)
        {
            char key = _getch();
            Colors colors;
            UpgradeMenu upgradeMenu;
            GameMenu gameMenu;
            player.round++;
            if (player.round % 2 == 0)
            {
                moveZombiesTowardPlayer(player);
            }
            switch (key)
            {
            case 'w':
                movePlayer(-1, 0, player);
                break;
            case 'a':
                movePlayer(0, -1, player);
                break;
            case 's':
                movePlayer(1, 0, player);
                break;
            case 'd':
                movePlayer(0, 1, player);
                break;
            case 't':
                shoot('t', player);
                break;
            case 'h':
                shoot('h', player);
                break;
            case 'g':
                shoot('g', player);
                break;
            case 'f':
                shoot('f', player);
                break;
            case 'r':
                reload(player);
                break;
            case 'e':
                exit(0);
                break;
            case 'u':
                upgradeMenu.displayMenu(player);
                break;
            case 'm':
                gameMenu.navigateMenu();
                break;
            }
            system("cls");
            player.printInfo();
            for (int i = 0; i < width; ++i)
            {
                for (int j = 0; j < height; ++j)
                {
                    if (gameBoard[i][j] == "Z")
                    {
                        cout << colors.RED << gameBoard[i][j] << colors.RESET;
                    }
                    else if (gameBoard[i][j] == "V")
                    {
                        cout << colors.YELLOW << gameBoard[i][j] << colors.RESET;
                    }
                    else if (gameBoard[i][j] == "A")
                    {
                        cout << colors.BLUE << gameBoard[i][j] << colors.RESET;
                    }
                    else if (gameBoard[i][j] == "P")
                    {
                        cout << colors.GREEN << gameBoard[i][j] << colors.RESET;
                    }
                    else if (gameBoard[i][j] == "D")
                    {
                        cout << colors.PURPLE << gameBoard[i][j] << colors.RESET;
                    }
                    else
                    {
                        cout << gameBoard[i][j];
                    }
                }
                cout << endl;
            }
            checkZombie(player, colors, spawns);
        }
    }
    void checkZombie(Player &player, Colors &colors, Spawns &spawns)
    {
        int currentX, currentY;
        bool foundPlayer = false;

        // Find the current position of the player
        for (int i = 0; i < width && !foundPlayer; ++i)
        {
            for (int j = 0; j < height && !foundPlayer; ++j)
            {
                if (gameBoard[i][j] == "P")
                {
                    currentX = i;
                    currentY = j;
                    foundPlayer = true;
                }
            }
        }

        if (gameBoard[currentX + 1][currentY] == "Z")
        {
            Sleep(1000);
            gameBoard[currentX + 1][currentY] = " ";
            system("cls");
            player.printInfo();
            for (int i = 0; i < width; ++i)
            {
                for (int j = 0; j < height; ++j)
                {
                    if (gameBoard[i][j] == "Z")
                    {
                        cout << colors.RED << gameBoard[i][j] << colors.RESET;
                    }
                    else if (gameBoard[i][j] == "V")
                    {
                        cout << colors.YELLOW << gameBoard[i][j] << colors.RESET;
                    }
                    else if (gameBoard[i][j] == "A")
                    {
                        cout << colors.BLUE << gameBoard[i][j] << colors.RESET;
                    }
                    else if (gameBoard[i][j] == "P")
                    {
                        cout << colors.GREEN << gameBoard[i][j] << colors.RESET;
                    }
                    else if (gameBoard[i][j] == "D")
                    {
                        cout << colors.PURPLE << gameBoard[i][j] << colors.RESET;
                    }
                    else
                    {
                        cout << gameBoard[i][j];
                    }
                }
                cout << endl;
            }
            cout << "The zombie is eating you! You lost one of your health!" << endl;
            player.health--;
            if (player.health == 0)
            {
                system("cls");
                player.printInfo();
                spawns.printGameBoard();
                cout << "You Died!" << endl
                     << "You Lose! Would you like to try again?(y/n)";
                char input;
                cin >> input;
                if (input == 'y')
                {
                    cout << "The game will restart in 5 seconds";
                    Sleep(5000);
                    newGame();
                }
                else if (input == 'n')
                {
                    system("cls");
                    mainMenu();
                }
            }

            Sleep(2000);
        }
        else if (gameBoard[currentX][currentY + 1] == "Z")
        {
            Sleep(1000);
            gameBoard[currentX][currentY + 1] = " ";
            system("cls");
            player.printInfo();
            for (int i = 0; i < width; ++i)
            {
                for (int j = 0; j < height; ++j)
                {
                    if (gameBoard[i][j] == "Z")
                    {
                        cout << colors.RED << gameBoard[i][j] << colors.RESET;
                    }
                    else if (gameBoard[i][j] == "V")
                    {
                        cout << colors.YELLOW << gameBoard[i][j] << colors.RESET;
                    }
                    else if (gameBoard[i][j] == "A")
                    {
                        cout << colors.BLUE << gameBoard[i][j] << colors.RESET;
                    }
                    else if (gameBoard[i][j] == "P")
                    {
                        cout << colors.GREEN << gameBoard[i][j] << colors.RESET;
                    }
                    else if (gameBoard[i][j] == "D")
                    {
                        cout << colors.PURPLE << gameBoard[i][j] << colors.RESET;
                    }
                    else
                    {
                        cout << gameBoard[i][j];
                    }
                }
                cout << endl;
            }
            cout << "The zombie is eating you! You lost one of your health!" << endl;
            player.health--;
            if (player.health == 0)
            {
                system("cls");
                player.printInfo();
                spawns.printGameBoard();

                cout << "You Died!" << endl
                     << "You Lose! Would you like to try again?(y/n)";
                char input;
                cin >> input;
                if (input == 'y')
                {
                    cout << "The game will restart in 5 seconds";
                    Sleep(5000);
                    newGame();
                }
                else if (input == 'n')
                {
                    system("cls");
                    mainMenu();
                }
            }

            Sleep(2000);
        }
        else if (gameBoard[currentX - 1][currentY] == "Z")
        {
            Sleep(1000);
            gameBoard[currentX - 1][currentY] = " ";
            system("cls");
            player.printInfo();
            for (int i = 0; i < width; ++i)
            {
                for (int j = 0; j < height; ++j)
                {
                    if (gameBoard[i][j] == "Z")
                    {
                        cout << colors.RED << gameBoard[i][j] << colors.RESET;
                    }
                    else if (gameBoard[i][j] == "V")
                    {
                        cout << colors.YELLOW << gameBoard[i][j] << colors.RESET;
                    }
                    else if (gameBoard[i][j] == "A")
                    {
                        cout << colors.BLUE << gameBoard[i][j] << colors.RESET;
                    }
                    else if (gameBoard[i][j] == "P")
                    {
                        cout << colors.GREEN << gameBoard[i][j] << colors.RESET;
                    }
                    else if (gameBoard[i][j] == "D")
                    {
                        cout << colors.PURPLE << gameBoard[i][j] << colors.RESET;
                    }
                    else
                    {
                        cout << gameBoard[i][j];
                    }
                }
                cout << endl;
            }
            cout << "The zombie is eating you! You lost one of your health!" << endl;
            player.health--;
            if (player.health == 0)
            {
                system("cls");
                player.printInfo();
                spawns.printGameBoard();
                cout << "You Died!" << endl
                     << "You Lose! Would you like to try again?(y/n)";
                char input;
                cin >> input;
                if (input == 'y')
                {
                    cout << "The game will restart in 5 seconds";
                    Sleep(5000);
                    newGame();
                }
                else if (input == 'n')
                {
                    system("cls");
                    mainMenu();
                }
            }

            Sleep(2000);
        }
        else if (gameBoard[currentX][currentY - 1] == "Z")
        {
            Sleep(1000);
            gameBoard[currentX][currentY - 1] = " ";
            system("cls");
            player.printInfo();
            for (int i = 0; i < width; ++i)
            {
                for (int j = 0; j < height; ++j)
                {
                    if (gameBoard[i][j] == "Z")
                    {
                        cout << colors.RED << gameBoard[i][j] << colors.RESET;
                    }
                    else if (gameBoard[i][j] == "V")
                    {
                        cout << colors.YELLOW << gameBoard[i][j] << colors.RESET;
                    }
                    else if (gameBoard[i][j] == "A")
                    {
                        cout << colors.BLUE << gameBoard[i][j] << colors.RESET;
                    }
                    else if (gameBoard[i][j] == "P")
                    {
                        cout << colors.GREEN << gameBoard[i][j] << colors.RESET;
                    }
                    else if (gameBoard[i][j] == "D")
                    {
                        cout << colors.PURPLE << gameBoard[i][j] << colors.RESET;
                    }
                    else
                    {
                        cout << gameBoard[i][j];
                    }
                }
                cout << endl;
            }
            cout << "The zombie is eating you! You lost one of your health!" << endl;
            player.health--;
            if (player.health == 0)
            {
                system("cls");
                player.printInfo();
                spawns.printGameBoard();
                cout << "You Died!" << endl
                     << "You Lose! Would you like to try again?(y/n)";
                char input;
                cin >> input;
                if (input == 'y')
                {
                    cout << "The game will restart in 5 seconds";
                    Sleep(5000);
                    newGame();
                }
                else if (input == 'n')
                {
                    system("cls");
                    mainMenu();
                }
            }

            Sleep(2000);
        }
    }
    void movePlayer(int x, int y, Player &player)
    {
        int currentX, currentY;
        bool foundPlayer = false;

        // Find the current position of the player
        for (int i = 0; i < width && !foundPlayer; ++i)
        {
            for (int j = 0; j < height && !foundPlayer; ++j)
            {
                if (gameBoard[i][j] == "P")
                {
                    currentX = i;
                    currentY = j;
                    foundPlayer = true;
                }
            }
        }

        int newX = currentX + x;
        int newY = currentY + y;

        if (newX >= 1 && newX < width - 1 && newY >= 1 && newY < height - 1)
        {

            if (gameBoard[newX][newY] == "Z")
            {
                cout << "The zombie is eating you! You lost one of your health!" << endl;
                player.health--;
                if (player.health == 0)
                {
                    gameBoard[currentX + 1][currentY] = " ";
                    system("cls");
                    player.printInfo();
                    Colors colors;
                    for (int i = 0; i < width; ++i)
                    {
                        for (int j = 0; j < height; ++j)
                        {
                            if (gameBoard[i][j] == "Z")
                            {
                                cout << colors.RED << gameBoard[i][j] << colors.RESET;
                            }
                            else if (gameBoard[i][j] == "V")
                            {
                                cout << colors.YELLOW << gameBoard[i][j] << colors.RESET;
                            }
                            else if (gameBoard[i][j] == "A")
                            {
                                cout << colors.BLUE << gameBoard[i][j] << colors.RESET;
                            }
                            else if (gameBoard[i][j] == "P")
                            {
                                cout << colors.GREEN << gameBoard[i][j] << colors.RESET;
                            }
                            else if (gameBoard[i][j] == "D")
                            {
                                cout << colors.PURPLE << gameBoard[i][j] << colors.RESET;
                            }
                            else
                            {
                                cout << gameBoard[i][j];
                            }
                        }
                        cout << endl;
                    }
                    cout << "You Died!" << endl
                         << "You Lose! Would you like to try again?(y/n)";
                    char input;
                    cin >> input;
                    if (input == 'y')
                    {
                        cout << "The game will restart in 5 seconds";
                        Sleep(5000);
                        newGame();
                    }
                    else if (input == 'n')
                    {
                        system("cls");
                        mainMenu();
                    }
                }
                gameBoard[newX][newY] = " ";

                gameBoard[currentX][currentY] = " ";
                gameBoard[newX][newY] = "P";

                Sleep(2000);
            }
            else if (gameBoard[newX][newY] == "A")
            {
                cout << "Ammo collected!" << endl;
                player.allAmmo++;
                player.outTreasure++;
                gameBoard[currentX][currentY] = " ";
                gameBoard[newX][newY] = "P";
                Sleep(2000);
            }
            else if (gameBoard[newX][newY] == "V")
            {
                cout << "Vaccine collected!" << endl;
                player.vaccine++;
                player.credit += player.level + 1;
                cout << player.level + 1 << " credit gained!";
                gameBoard[currentX][currentY] = " ";
                gameBoard[newX][newY] = "P";
                Sleep(2000);
            }
            else if (gameBoard[newX][newY] == "D")
            {
                int vaccineCounter = 0;
                for (int i = 0; i < 17; i++)
                {
                    for (int j = 0; j < 19; j++)
                    {
                        if (gameBoard[i][j] == "V")
                        {
                            vaccineCounter++;
                        }
                    }
                }
                if (vaccineCounter == 0)
                {
                    player.level++;
                    if (player.level == 21)
                    {
                        cout << "Congratulations! You have successfully collected all the vaccines! Now it is time to return to the Earth" << endl
                             << "Good Bye!";
                        Sleep(2000);
                        exit(0);
                    }
                    else
                    {
                        cout << "You Won! You have reached level " << player.level;
                        Sleep(2000);
                        Spawns spawns;
                        system("cls");
                        player.printInfo();
                        spawns.zambieSpawn(player.level);
                        spawns.amooSpawn(player.level);
                        spawns.vaccineSpawn(player.level);
                        spawns.printGameBoard();
                        spawns.moveShootStuff(player, spawns);
                    }
                }
                else
                {
                    cout << "First get all the vaccines.";
                    gameBoard[width - 2][height - 2] = "D";
                    Sleep(2000);
                }
            }
            else
            {
                gameBoard[currentX][currentY] = " ";
                gameBoard[newX][newY] = "P";
            }
        }
    }
    void shoot(char direction, Player &player)
    {
        int currentX, currentY;
        bool foundPlayer = false;
        if (player.treasure == 0)
        {
            cout << "No charged ammo!";
            Sleep(2000);
        }
        else
        {
            player.treasure--;
            for (int i = 0; i < width && !foundPlayer; ++i)
            {
                for (int j = 0; j < height && !foundPlayer; ++j)
                {
                    if (gameBoard[i][j] == "P")
                    {
                        currentX = i;
                        currentY = j;
                        foundPlayer = true;
                    }
                }
            }

            int range = player.range;

            if (direction == 't')
            {
                int counter = 0;
                for (int i = currentX - 1; i >= max(0, currentX - range); --i)
                {

                    if (gameBoard[i][currentY] == "Z")
                    {
                        gameBoard[i][currentY] = " ";
                        if (player.kills % 14 == 0)
                        {
                            cout << "First Blood" << endl;
                        }
                        else if (player.kills % 14 == 1)
                        {
                            cout << "Double Kill" << endl;
                        }
                        else if (player.kills % 14 == 2 && player.round % 2 == 0)
                        {
                            cout << "Triple Kill" << endl;
                        }
                        else if (player.kills % 14 == 2 && player.round % 2 == 1)
                        {
                            cout << "Hattrick" << endl;
                        }
                        else if (player.kills % 14 == 3)
                        {
                            cout << "Team Killer" << endl;
                        }
                        else if (player.kills % 14 == 4)
                        {
                            cout << "Headshot" << endl;
                        }
                        else if (player.kills % 14 == 5)
                        {
                            cout << "Rampage" << endl;
                        }
                        else if (player.kills % 14 == 6)
                        {
                            cout << "Killing Spree" << endl;
                        }
                        else if (player.kills % 14 == 7)
                        {
                            cout << "Unstoppable" << endl;
                        }
                        else if (player.kills % 14 == 8)
                        {
                            cout << "Monster Kill" << endl;
                        }
                        else if (player.kills % 14 == 9)
                        {
                            cout << "Multi Kill" << endl;
                        }
                        else if (player.kills % 14 == 10)
                        {
                            cout << "Ludicrouskill" << endl;
                        }
                        else if (player.kills % 14 == 11)
                        {
                            cout << "Ultra Kill" << endl;
                        }
                        else if (player.kills % 14 == 12)
                        {
                            cout << "Dominating" << endl;
                        }
                        else if (player.kills % 14 == 13)
                        {
                            cout << "Godlike" << endl;
                        }
                        player.kills++;
                        player.credit += player.level + 1;
                        cout << player.level + 1 << "credit gained!";
                        Sleep(2000);
                    }
                    else
                    {
                        counter++;
                        if (counter == player.range - 1)
                        {
                            cout << "Zombie is not in range! come closer.";
                            Sleep(2000);
                        }
                    }
                }
            }
            else if (direction == 'g')
            {
                int counter = 0;
                for (int i = currentX + 1; i <= min(width - 1, currentX + range); ++i)
                {
                    if (gameBoard[i][currentY] == "Z")
                    {
                        gameBoard[i][currentY] = " ";
                        if (player.kills % 14 == 0)
                        {
                            cout << "First Blood" << endl;
                        }
                        else if (player.kills % 14 == 1)
                        {
                            cout << "Double Kill" << endl;
                        }
                        else if (player.kills % 14 == 2 && player.round % 2 == 0)
                        {
                            cout << "Triple Kill" << endl;
                        }
                        else if (player.kills % 14 == 2 && player.round % 2 == 1)
                        {
                            cout << "Hattrick" << endl;
                        }
                        else if (player.kills % 14 == 3)
                        {
                            cout << "Team Killer" << endl;
                        }
                        else if (player.kills % 14 == 4)
                        {
                            cout << "Headshot" << endl;
                        }
                        else if (player.kills % 14 == 5)
                        {
                            cout << "Rampage" << endl;
                        }
                        else if (player.kills % 14 == 6)
                        {
                            cout << "Killing Spree" << endl;
                        }
                        else if (player.kills % 14 == 7)
                        {
                            cout << "Unstoppable" << endl;
                        }
                        else if (player.kills % 14 == 8)
                        {
                            cout << "Monster Kill" << endl;
                        }
                        else if (player.kills % 14 == 9)
                        {
                            cout << "Multi Kill" << endl;
                        }
                        else if (player.kills % 14 == 10)
                        {
                            cout << "Ludicrouskill" << endl;
                        }
                        else if (player.kills % 14 == 11)
                        {
                            cout << "Ultra Kill" << endl;
                        }
                        else if (player.kills % 14 == 12)
                        {
                            cout << "Dominating" << endl;
                        }
                        else if (player.kills % 14 == 13)
                        {
                            cout << "Godlike" << endl;
                        }
                        player.kills++;
                        player.credit += player.level + 1;
                        cout << player.level + 1 << "credit gained!";
                        Sleep(2000);
                    }
                    else
                    {
                        counter++;
                        if (counter == player.range - 1)
                        {
                            cout << "Zombie is not in range! come closer.";
                            Sleep(2000);
                        }
                    }
                }
            }
            else if (direction == 'f')
            {
                int counter = 0;
                for (int j = currentY - 1; j >= max(0, currentY - range); --j)
                {
                    if (gameBoard[currentX][j] == "Z")
                    {
                        gameBoard[currentX][j] = " ";
                        if (player.kills % 14 == 0)
                        {
                            cout << "First Blood" << endl;
                        }
                        else if (player.kills % 14 == 1)
                        {
                            cout << "Double Kill" << endl;
                        }
                        else if (player.kills % 14 == 2 && player.round % 2 == 0)
                        {
                            cout << "Triple Kill" << endl;
                        }
                        else if (player.kills % 14 == 2 && player.round % 2 == 1)
                        {
                            cout << "Hattrick" << endl;
                        }
                        else if (player.kills % 14 == 3)
                        {
                            cout << "Team Killer" << endl;
                        }
                        else if (player.kills % 14 == 4)
                        {
                            cout << "Headshot" << endl;
                        }
                        else if (player.kills % 14 == 5)
                        {
                            cout << "Rampage" << endl;
                        }
                        else if (player.kills % 14 == 6)
                        {
                            cout << "Killing Spree" << endl;
                        }
                        else if (player.kills % 14 == 7)
                        {
                            cout << "Unstoppable" << endl;
                        }
                        else if (player.kills % 14 == 8)
                        {
                            cout << "Monster Kill" << endl;
                        }
                        else if (player.kills % 14 == 9)
                        {
                            cout << "Multi Kill" << endl;
                        }
                        else if (player.kills % 14 == 10)
                        {
                            cout << "Ludicrouskill" << endl;
                        }
                        else if (player.kills % 14 == 11)
                        {
                            cout << "Ultra Kill" << endl;
                        }
                        else if (player.kills % 14 == 12)
                        {
                            cout << "Dominating" << endl;
                        }
                        else if (player.kills % 14 == 13)
                        {
                            cout << "Godlike" << endl;
                        }
                        player.kills++;
                        player.range += player.level + 1;
                        cout << player.level + 1 << "credit gained!";
                        Sleep(2000);
                    }
                    else
                    {
                        counter++;
                        if (counter == player.range - 1)
                        {
                            cout << "Zombie is not in range! Come closer." << endl;
                            Sleep(2000);
                        }
                    }
                }
            }
            else if (direction == 'h')
            {
                int counter = 0;
                for (int j = currentY + 1; j <= min(height - 1, currentY + range); ++j)
                {
                    if (gameBoard[currentX][j] == "Z")
                    {
                        gameBoard[currentX][j] = " ";
                        if (player.kills % 14 == 0)
                        {
                            cout << "First Blood" << endl;
                        }
                        else if (player.kills % 14 == 1)
                        {
                            cout << "Double Kill" << endl;
                        }
                        else if (player.kills % 14 == 2 && player.round % 2 == 0)
                        {
                            cout << "Triple Kill" << endl;
                        }
                        else if (player.kills % 14 == 2 && player.round % 2 == 1)
                        {
                            cout << "Hattrick" << endl;
                        }
                        else if (player.kills % 14 == 3)
                        {
                            cout << "Team Killer" << endl;
                        }
                        else if (player.kills % 14 == 4)
                        {
                            cout << "Headshot" << endl;
                        }
                        else if (player.kills % 14 == 5)
                        {
                            cout << "Rampage" << endl;
                        }
                        else if (player.kills % 14 == 6)
                        {
                            cout << "Killing Spree" << endl;
                        }
                        else if (player.kills % 14 == 7)
                        {
                            cout << "Unstoppable" << endl;
                        }
                        else if (player.kills % 14 == 8)
                        {
                            cout << "Monster Kill" << endl;
                        }
                        else if (player.kills % 14 == 9)
                        {
                            cout << "Multi Kill" << endl;
                        }
                        else if (player.kills % 14 == 10)
                        {
                            cout << "Ludicrouskill" << endl;
                        }
                        else if (player.kills % 14 == 11)
                        {
                            cout << "Ultra Kill" << endl;
                        }
                        else if (player.kills % 14 == 12)
                        {
                            cout << "Dominating" << endl;
                        }
                        else if (player.kills % 14 == 13)
                        {
                            cout << "Godlike" << endl;
                        }
                        player.kills++;
                        player.range += player.level + 1;
                        cout << player.level + 1 << "credit gained!";
                        Sleep(2000);
                    }
                    else
                    {
                        counter++;
                        if (counter == player.range - 1)
                        {
                            cout << "Zombie is not in range! Come closer." << endl;
                            Sleep(2000);
                        }
                    }
                }
            }
        }
    }
    void reload(Player &player)
    {
        int counter = 0;
        if (player.treasure == player.treasureCapacity)
        {
            cout << "The gun is already Charged";
            Sleep(2000);
        }
        while (player.treasure != player.treasureCapacity && player.outTreasure > 0)
        {

            counter++;

            if (player.allAmmo == 0 || player.outTreasure == 0)
            {
                cout << "No Ammo!";
                Sleep(2000);
            }
            else
            {
                if (counter == player.treasureCapacity - 1)
                {
                    cout << "Reloaded!";
                }
                player.treasure++;
                player.outTreasure--;
                Sleep(2000);
            }
        }
    }
};

void newGame()
{
    Colors colors;
    Spawns spawns;
    Player player;
    system("cls");
    player.allAmmo = 3;
    player.credit = 0;
    player.health = 3;
    player.kills = 0;
    player.level = 1;
    player.outTreasure = player.allAmmo - 3;
    player.range = 5;
    player.round = 0;
    player.treasure = 3;
    player.treasureCapacity = 3;
    player.vaccine = 0;
    player.printInfo();
    spawns.zambieSpawn(player.level);
    spawns.amooSpawn(player.level);
    spawns.vaccineSpawn(player.level);
    spawns.printGameBoard();
    spawns.moveShootStuff(player, spawns);
}
void mainMenu()
{
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    cout << " ██████╗ ██████╗ ██╗   ██╗██╗██████╗ ██████╗  ██████╗ ██████╗  ██████╗ " << endl;
    cout << "██╔════╝██╔═══██╗██║   ██║██║██╔══██╗╚════██╗██╔═████╗╚════██╗██╔═████╗" << endl;
    cout << "██║     ██║   ██║██║   ██║██║██║  ██║ █████╔╝██║██╔██║ █████╔╝██║██╔██║" << endl;
    cout << "██║     ██║   ██║╚██╗ ██╔╝██║██║  ██║██╔═══╝ ████╔╝██║ ╚═══██╗████╔╝██║" << endl;
    cout << "╚██████╗╚██████╔╝ ╚████╔╝ ██║██████╔╝███████╗╚██████╔╝██████╔╝╚██████╔╝" << endl;
    cout << " ╚═════╝ ╚═════╝   ╚═══╝  ╚═╝╚═════╝ ╚══════╝ ╚═════╝ ╚═════╝  ╚═════╝" << endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED); // سفید کردن رنگ
    cout << "Welcome to Covid 2030 game!" << endl
         << endl;
    cout << "1-New Game" << endl;
    cout << "2-Settings" << endl;
    cout << "3-Credits" << endl;
    cout << "4-Help" << endl;
    cout << "5-Exit" << endl;
    int choice;
    cin >> choice;
    if (choice == 1)
    {
        newGame();
    }
    else if (choice == 2)
    {
        cout << "Final level is: 20" << endl
             << "Sound is not activated!";
        Sleep(5000);
        mainMenu();
    }
    else if (choice == 3)
    {
        cout << "Written by Mohammad Sadegh Hemati,Seyed Mendi Amir Mousavi and Amir Hussein Rastgar";
        Sleep(5000);
        mainMenu();
    }
    else if (choice == 4)
    {
        cout << "Avoid from zombies and collect all the vaccines and arrive to the teleport";
        Sleep(5000);
        mainMenu();
    }
    else if (choice == 5)
    {
        exit(0);
    }
    else
    {
        system("cls");
        mainMenu();
    }
}

int main()
{
    mainMenu();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}