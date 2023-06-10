// === Region: Headers ===
// iostream and cstring are included.
// Do not include extra header files
// =======================
#include <iostream>
#include <cstring>
using namespace std;

// === Region: Constants ===
// Useful constants are defined for this project assignment
// =======================
const int MAX_ROWS = 20;
const int MAX_COLS = 30;
const int MAX_NUM_BLOCKS = 26;
const char CHAR_EMPTY = '.';
const char CHAR_WALL = '#';
const char CHAR_TARGET = '*';
const char CHAR_END_INPUT = '!';
const char DIRECTION_EAST = 'e';
const char DIRECTION_WEST = 'w';
const char DIRECTION_SOUTH = 's';
const char DIRECTION_NORTH = 'n';

// === Region: function declarations ===
// The function declarations.
// The implementation is done in the function definitions
// =====================================

/**
 * function: readInput reads the game map, the number of rows, and the number of columns
 * @param map:     a 2D character array storing the game map
 * @param mapRows: the number of rows of the game map. Note: it is pass by reference.
 * @param mapCols: the number of columns of the game map. Note: it is pass by reference.
 *
 * Note: This function is given. You don't need to implement this function
 */
void readInput(char map[MAX_ROWS][MAX_COLS], int &mapRows, int &mapCols);

/**
 * function: displayMap displays the current game map
 * @param map:     a 2D character array storing the game map
 * @param mapRows: the number of rows of the game map
 * @param mapCols: the number of columns of the game map
 *
 * Note: This function is given. You don't need to implement this function
 */
void displayMap(const char map[MAX_ROWS][MAX_COLS], const int mapRows, const int mapCols);

/**
 * function: isValidBlockLetter checks whether a block letter is valid
 * @param map:    a 2D character array storing the game map
 * @param mapRows: the number of rows of the game map
 * @param mapCols: the number of columns of the game map
 * @param letter:  the block letter
 *
 * @return true if letter is between A to Z (capital letter, inclusive) and the letter can be found inside the map.
 * Otherwise, return false.
 *
 * For example, if the letter is C (capital letter, and is between A..Z) but cannot be found in the game map, you should return false
 */
bool isValidBlockLetter(const char map[MAX_ROWS][MAX_COLS], const int mapRows, const int mapCols, const char letter);

/**
 * function: isValidDirectionLetter checks whether the letter is a valid direction letter
 * @param letter: the direction letter
 *
 * @return true if the direction letter is valid. Otherwise, return false
 *
 * Note: You can use constants DIRECTION_XXX defined above
 */
bool isValidDirectionLetter(const char letter);

/**
 * function: countBlocksInMap counts the number of blocks in the game map
 * @param: map: a 2D character array storing the game map
 * @param mapRows: the number of rows of the game map
 * @param mapCols: the number of columns of the game map
 *
 * @return the numbers of blocks in the game map
 */
int countBlocksInMap(const char map[MAX_ROWS][MAX_COLS], const int mapRows, const int mapCols);

/**
 * function: updateMapReturnArrival updates the game map based on the blockLetter and the direction letter
 * @param: map: a 2D character array storing the game map
 * @param mapRows: the number of rows of the game map
 * @param mapCols: the number of columns of the game map
 * @param blockLetter: a block letter. The block letter needs to be valid
 * @param directionLetter: a direction letter. The direction letters needs to be valid
 *
 * Note: This function will update the game map
 *
 * @return true if the block arrives one of the targets. Otherwise, return false.
 *
 */
bool updateMapReturnArrival(char map[MAX_ROWS][MAX_COLS], const int mapRows, const int mapCols,
                            char blockLetter, char directionLetter);

/**
 * function: updateBlockArrivalHistory updates the arrival history (i.e., a 1D character array)
 * @param blockArrivalHistory: a 1D array storing the block arrival history
 * @param blockLetter: a block letter. The block letter needs to be valid
 * @param totalArrivalBlock: the total number of blocks arrived so far. Note: it is pass by reference.
 *
 */
void updateBlockArrivalHistory(char blockArrivalHistory[MAX_NUM_BLOCKS],
                               const char blockLetter,
                               int &totalArrivalBlock);

/**
 * function: the main function
 *
 * Note: The main function is given. Do not modify anything inside
 */
int main()
{

    char map[MAX_ROWS][MAX_COLS];
    char blockLetter, directionLetter;
    int mapRows, mapCols, totalArrivalBlock, i;
    bool checkBlockLetter, checkDirectionLetter, isArrived;
    char blockArrivalHistory[MAX_NUM_BLOCKS];

    readInput(map, mapRows, mapCols);

    totalArrivalBlock = 0;

    cout << "The original map: " << endl;
    displayMap(map, mapRows, mapCols);

    while (true)
    {
        cin >> blockLetter >> directionLetter;
        if (blockLetter == CHAR_END_INPUT && directionLetter == CHAR_END_INPUT)
            break;

        checkBlockLetter = isValidBlockLetter(map, mapRows, mapCols, blockLetter);
        checkDirectionLetter = isValidDirectionLetter(directionLetter);

        if (checkBlockLetter == false && checkDirectionLetter == false)
        {
            cout << "Both block letter " << blockLetter << " and direction letter " << directionLetter << " are invalid" << endl;
        }
        else if (checkBlockLetter == false)
        {
            cout << "Block letter " << blockLetter << " is invalid" << endl;
        }
        else if (checkDirectionLetter == false)
        {
            cout << "Direction letter " << directionLetter << " is invalid" << endl;
        }
        else
        {
            cout << "Move block " << blockLetter << " to the direction " << directionLetter << endl;
            isArrived = updateMapReturnArrival(map, mapRows, mapCols, blockLetter, directionLetter);
            if (isArrived)
            {
                updateBlockArrivalHistory(blockArrivalHistory, blockLetter, totalArrivalBlock);
            }
            displayMap(map, mapRows, mapCols);
        }
    }

    cout << "=== Game Ended ===" << endl;
    cout << countBlocksInMap(map, mapRows, mapCols) << " block(s) remain(s) in the map" << endl;
    if (totalArrivalBlock > 0)
    {
        cout << "The escape order is ";
        for (i = 0; i < totalArrivalBlock; i++)
            cout << blockArrivalHistory[i];
        cout << endl;
    }
    else
    {
        cout << "No blocks escape the map" << endl;
    }

    return 0;
}

void updateBlockArrivalHistory(char blockArrivalHistory[MAX_NUM_BLOCKS],
                               const char blockLetter,
                               int &totalArrivalBlock)
{

    blockArrivalHistory[totalArrivalBlock++] = blockLetter;
}

bool findBlockInMap(const char map[MAX_ROWS][MAX_COLS],
                    const int mapRows,
                    const int mapCols,
                    char letter, int &row, int &col)
{

    int r, c;
    for (r = 0; r < mapRows; r++)
        for (c = 0; c < mapCols; c++)
            if (map[r][c] == letter)
            {
                row = r;
                col = c;
                return true;
            }
    return false;
}

bool isValidBlockLetter(
    const char map[MAX_ROWS][MAX_COLS],
    const int mapRows,
    const int mapCols,
    const char letter)
{

    int r, c;
    if (letter >= 'A' && letter <= 'Z' && findBlockInMap(map, mapRows, mapCols, letter, r, c))
        return true;

    return false;
}

bool isValidDirectionLetter(const char letter)
{
    return letter == DIRECTION_EAST ||
           letter == DIRECTION_NORTH ||
           letter == DIRECTION_WEST ||
           letter == DIRECTION_SOUTH;
}

int countBlocksInMap(const char map[MAX_ROWS][MAX_COLS], const int mapRows, const int mapCols)
{
    int r, c, count = 0;
    for (r = 0; r < mapRows; r++)
        for (c = 0; c < mapCols; c++)
            if (map[r][c] >= 'A' && map[r][c] <= 'Z')
                count++;
    return count;
}

bool isInsideMap(const int mapRows, const int mapCols, int row, int col)
{
    return row >= 0 && col >= 0 && row < mapRows && col < mapCols;
}

bool updateMapReturnArrival(char map[MAX_ROWS][MAX_COLS], const int mapRows, const int mapCols,
                            char blockLetter, char directionLetter)
{

    int curRow, curCol;
    int deltaRow, deltaCol;
    int newRow, newCol;

    if (findBlockInMap(map, mapRows, mapCols, blockLetter, curRow, curCol))
    {

        deltaRow = deltaCol = 0;
        switch (directionLetter)
        {
        case DIRECTION_EAST:
            deltaCol = 1;
            break;
        case DIRECTION_WEST:
            deltaCol = -1;
            break;
        case DIRECTION_NORTH:
            deltaRow = -1;
            break;
        case DIRECTION_SOUTH:
            deltaRow = 1;
            break;
        }

        // Keep moving the block based on the direction
        while (true)
        {

            newRow = curRow + deltaRow;
            newCol = curCol + deltaCol;

            if (isInsideMap(mapRows, mapCols, newRow, newCol))
            {

                //  hits the target?
                if (map[newRow][newCol] == CHAR_TARGET)
                {
                    map[curRow][curCol] = CHAR_EMPTY; // remove the block
                    return true;                      //  successfully arrived
                }
                // hits the wall or another block
                else if (map[newRow][newCol] == CHAR_WALL ||
                         (map[newRow][newCol] >= 'A' && map[newRow][newCol] <= 'Z'))
                {
                    break; // terminate the loop, and not moving anymore
                }
                else
                {
                    // move the block
                    map[curRow][curCol] = CHAR_EMPTY;
                    map[newRow][newCol] = blockLetter;
                    curRow = newRow;
                    curCol = newCol;
                }
            }
            else
            {
                break; // cannot move outside the map
            }
        }
    }

    return false; // cannot arrive the target
}

void readInput(char map[MAX_ROWS][MAX_COLS], int &mapRows, int &mapCols)
{
    int r, c;
    char line[MAX_COLS + 1]; // character array to store each line
    cin >> mapRows >> mapCols;
    cin.ignore(); // ignore the end line character in the first line
    for (r = 0; r < mapRows; r++)
    {
        cin.getline(line, MAX_COLS + 1);
        for (c = 0; c < mapCols; c++)
            map[r][c] = line[c];
    }
}

void displayMap(const char map[MAX_ROWS][MAX_COLS], const int mapRows, const int mapCols)
{
    int r, c;
    for (r = 0; r < mapRows; r++)
    {
        for (c = 0; c < mapCols; c++)
            cout << map[r][c] << " ";
        cout << endl;
    }
}