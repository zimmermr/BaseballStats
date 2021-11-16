// Michael Zimmerman
// July 28, 2020
// Final project - Baseball stat sorter
// This program accepts several batting statistics for a month, and
// gives the user options to either display the box score for the entire month or
// find the best and worst player in four of those categories.

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

// Function prototypes for calculating lowest and highest stats, showing the box score, the menu, and
// making sure user entries are more than one
void minStat(int, int);
void maxStat(int, int);
void boxscore(int, int, string []);
void checkNum(double &);
int menu();

int main()
{
    cout << "This program will calculate on base percentage (OBP), Total Bases (TB)\n";
    cout << "Slugging Percentage (SLG), and OPS for the month, and give you several options\n";
    cout << "to display your monthly stats.\n\n";

    // Constant to hold the number of stat categories
    const int NUM_STATS = 21;

    // Declare variables to take the number of batters, and hold a player name.
    string playerName;
    int numBatters,
        menuChoice;

    // Declare a multi-dimensional vector to hold user-defined number of items
    vector < vector <double> > stats;
    vector <string> vectPlayerNames;

    // Array to hold the headings for the box score. Can also be passed to display for the min and max functions.
    string arrHeader[22] = { "Name", "G", "PA", "AB", "R", "H", "1B", "2B", "3B", "HR", "RBI", "SB",
                      "BB", "HBP", "SO", "SF", "SH", "TB", "AVG", "OBP", "SLG", "OPS" };
        
    // Declare variables for each stat category
    double games, pa, ab, r, h, sing, doub, trip, hr, rbi, sb,
        bb, so, sacFly, sacHit, hbp, avg, obp, tb, slg, ops;

    // Declare ofstream variables to hold names and stats
    ofstream nameFile, statFile;

    // Ask the user for how many batters to enter stats for
    cout << "How many batters went to the plate this month?\n";
    cin >> numBatters;
    cout << endl;

    // Create a file to hold player names
    nameFile.open("Players.txt");

    // Loop to accept statistics for the number of batters entered
    for (int batCount = 0; batCount < numBatters; batCount++)
    {
        // Take the first name from user
        cout << "Enter name for player " << (batCount + 1) << ":\n";
        cin.ignore();
        getline(cin, playerName);

        // Send name to file
        nameFile << playerName << endl;

        cout << "Enter stats for " << playerName << ":\n";

        // These next several statements accept the user entries for each stat category
        cout << "Games played: ";
        cin >> games;

        // This function and the if statement validate the entry
        checkNum(games);
        if (games < 1)
        {
            cout << "Any player entered must have played at least one game this month.\n";
            cin >> games;
            checkNum(games);
        }

        cout << "Plate appearances: ";
        cin >> pa;
        checkNum(pa);

        cout << "At bats: ";
        cin >> ab;
        checkNum(ab);
        while (ab > pa)
        {
            cout << "Player cannot have more at-bats than plate appearances.\nEnter the number of at-bats: ";
            cin >> ab;
        }

        cout << "Runs: ";
        cin >> r;
        checkNum(r);
        while (r > pa)
        {
            cout << "Player cannot have more runs than plate appearances.\nEnter the number of runs: ";
            cin >> r;
        }

        cout << "Singles: ";
        cin >> sing;
        checkNum(sing);

        cout << "Doubles: ";
        cin >> doub;
        checkNum(doub);

        cout << "Triples: ";
        cin >> trip;
        checkNum(trip);

        cout << "Home runs: ";
        cin >> hr;
        checkNum(hr);

        cout << "RBI: ";
        cin >> rbi;
        checkNum(rbi);
        // The most RBIs a player can have per plate appearance is four (a grand slam).
        // This makes sure the number entered isn't higher than four times the plate appearances.
        if (rbi > (pa * 4))
        {
            cout << "That's too many RBIs for " << playerName << "'s plate appearances. Double-check and enter again:\n";
            cin >> rbi;
        }

        cout << "Stolen bases: ";
        cin >> sb;
        checkNum(sb);


        cout << "Walks: ";
        cin >> bb;
        checkNum(bb);
        while (bb > pa)
        {
            cout << "Player cannot have more walks than plate appearances.\nEnter the number of walks: ";
            cin >> bb;
        }

        cout << "Strike outs: ";
        cin >> so;
        checkNum(so);
        while (so > ab)
        {
            cout << "Player cannot have more strikeouts than at-bats.\nEnter the number of strikeouts: ";
            cin >> so;
        }

        cout << "Hit by pitch: ";
        cin >> hbp;
        checkNum(hbp);
        while (hbp > pa)
        {
            cout << "Player cannot have more hit-by-pitches than plate appearances.\nEnter the number of HBP: ";
            cin >> hbp;
        }

        cout << "Sacrifice flies: ";
        cin >> sacFly;
        checkNum(sacFly);
        while (sacFly > pa)
        {
            cout << "Player cannot have more sacrifice flies than plate appearances.\nEnter the number of sac flies: ";
            cin >> sacFly;
        }

        cout << "Sacrifice hits(bunts): ";
        cin >> sacHit;
        checkNum(sacHit);
        while (sacHit > pa)
        {
            cout << "Player cannot have more sacrifice hits than plate appearances.\nEnter the number of sac hits: ";
            cin >> ab;
        }


        // These formulas fill in the other calculated stats from the user entered values.
        h = (sing + doub + trip + hr);

        avg = h / ab;

        obp = (h + bb + hbp) / (ab + bb + hbp + sacFly);

        tb = (sing + (2 * doub) + (3 * trip) + (4 * hr));

        slg = tb / ab;

        ops = obp + slg;

        // Push each value into a temporary vector
        vector<double>temp;
        temp.push_back(games);
        temp.push_back(pa);
        temp.push_back(ab);
        temp.push_back(r);
        temp.push_back(h);
        temp.push_back(sing);
        temp.push_back(doub);
        temp.push_back(trip);
        temp.push_back(hr);
        temp.push_back(rbi);
        temp.push_back(sb);
        temp.push_back(bb);
        temp.push_back(hbp);
        temp.push_back(so);
        temp.push_back(sacFly);
        temp.push_back(sacHit);
        temp.push_back(tb);
        temp.push_back(avg);
        temp.push_back(obp);
        temp.push_back(slg);
        temp.push_back(ops);

        // Push a row of values from the temp vector into the stats vector
        stats.push_back(temp);
 
        cout << endl;

    }

    // Close the file of player names.
    nameFile.close();

    // Create a file to hold the statistics
    statFile.open("Stats.txt");

    // Send values from stat vector into the file
    for (int i = 0; i < numBatters; i++)
    {
        for (int j = 0; j < NUM_STATS; j++)
        {
            cout << setprecision(0);

            if (stats[i][j] == static_cast<int>(stats[i][j]))
            {
                statFile << setprecision(0) << stats[i][j] << " ";
            }
            else {
                statFile << setprecision(3) << fixed << stats[i][j] << " ";
            }
        }
        statFile << endl;
    }

    // Close the stat file
    statFile.close();

    // Call function to display menu
    menuChoice = menu();

    // Call a function to display a switch for the menu choice
    while (menuChoice >= 1 && menuChoice <= 3)
    {
        switch (menuChoice)
        {
        // Each selection calls a function, and sends similar variables from main into the function
        case 1: boxscore(numBatters, NUM_STATS, arrHeader);
            break;
        case 2: maxStat(numBatters, NUM_STATS);
            break;
        case 3: minStat(numBatters, NUM_STATS);
            break;
        // Ends the program with any choice other than 1, 2, or 3
        default: return 0;
            break;
        }
    // Repeats the menu choice in the loop. I could've done this menu in a do while loop.
    menuChoice = menu();
    }

    return 0;
}

void checkNum(double &stat) // This function makes sure the entered number is more than zero. No stats can be negative.
{
    while (stat < 0)
    {
        cout << "You cannot enter a negative number.\nPlease enter a postive number or zero:";
        cin >> stat;
    }
}

int menu() // Displays the main menu for user to choose what to see
{
    int choice;
    cout << "\nWhat would you like to see?\n";
    cout << "Enter 1 to see a full box score for all the month's batters.\n";
    cout << "Enter 2 to see who had the highest of a stat category.\n";
    cout << "Enter 3 to see who had the lowest of a stat category.\n";
    cout << "Enter any other number to quit.\n";

    cin >> choice;
    // The choice gets returned to the main function here
    return choice;
}

void boxscore(int numPlayers, int numStats, string header[]) // Reads info from files into new vectors, and displays the vector of statistics
{
    // Creates a multidimensional vector to hold stats for several players
    vector< vector<double> > stats;
    vector<double> row;

    // Variable to temporarily hold values before sending to the vector
    double count;

    // Create ifstream objects to read from files created in main: one for stats and one for names
    ifstream inputStats;
    ifstream inputNames;

    inputStats.open("Stats.txt");

    // Loop that reads each number from stats.txt into the vector stats
    for (int i = 0; i < (numStats / numPlayers); i++)
    {
        for (int j = 0; j < (numStats); j++)
        {
            inputStats >> count;
            // Each number is pushed to the row vector
            row.push_back(count);
        }
    // After each row vector is sent to the stats vector, it's cleared for the next iteration of the loop
    stats.push_back(row);
    row.clear();
    }

    inputNames.open("Players.txt");

    // Display the headers
    for (int x = 0; x <= numStats; x++)
    {
        if (x == 0)
        {
            cout << setw(20) << left << header[x] << " ";
        }
        else if (x > 0 && x <= 18)
        {
            cout << setw(3) << right << header[x] << " ";
        }
        else if (x > 18)
        {
            cout << setw(6) << right << header[x] << " ";
        }
    }

    cout << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------\n";

    // Reads the first file in each row from names, then loops through each stat for each player
    for (int i = 0; i < numPlayers; i++)
    {
        string name;
        inputNames >> name;
        cout << setw(20) << left << name << " ";

        for (int j = 0; j < numStats; j++)
        {
            if (j >= 0 && j < 18)
            {
                // Need to set the width of the field, since these won't be decimal numbers
                cout << setw(3) << right << stats[i][j] << " ";
            }
            else if (j >= 18)
            {
                // The last few stats are decimals to three points
                cout << setw(6) << setprecision(3) << right << stats[i][j] << " ";
            }
            
        }
        cout << endl;
    }

    inputNames.close();
    inputStats.close();

}

void maxStat(int numPlayers, int numStats) // Allow the user to choose a category and show the top player in that category
{
    // This is copied from previous function (to write info from files into vector
    vector< vector<double> > stats;
    vector<double> row;
    vector<string> playerNames;

    // Variable for the internal menu choice
    int menuChoice;

    // Variables to store the name and statistic of the best-performing player
    double max;
    string maxPlayer;

    // Temp variable to fill string vector with player names
    string tempName;

    double count;

    ifstream inputStats;
    ifstream inputNames;

    inputStats.open("Stats.txt");

    for (int i = 0; i < (numStats / numPlayers); i++)
    {
        for (int j = 0; j < (numStats); j++)
        {
            inputStats >> count;
            row.push_back(count);
        }
        stats.push_back(row);
        row.clear();
    }

    inputStats.close();

    inputNames.open("Players.txt");
    
    for (int b = 0; b < numPlayers; b++)
    {
        inputNames >> tempName;
        playerNames.push_back(tempName);
    }

    inputNames.close();


    // Menu to choose which stat to show
    cout << "Choose from the following stats to show the month leader in that category:\n";
    cout << "1. Home Runs\n2. Batting average\n3. Slugging percentage\n4. OPS\n";
    cout << "Enter the number of your choice, or enter any other number to return to the previous menu.\n";

    cin >> menuChoice;

    cout << endl;

    // Loop to keep menu cycling for users to select multiple categories.
    while (menuChoice >= 1 && menuChoice <= 4)
    {
        switch (menuChoice)
        {
        // Each switch case performs the same if statement inside a for loop to find the highest player in that category
        case 1:
            max = stats[0][8];
            maxPlayer = playerNames[0];
            for (int w = 0; w < numPlayers; w++)
            {
                if (stats[w][8] > max)
                {
                    max = stats[w][8];
                    maxPlayer = playerNames[w];
                }
            }
            cout << "The player with the most home runs this month was " << maxPlayer << " with " << max << " HRs.\n\n";
            break;

        case 2:
            max = stats[0][17];
            maxPlayer = playerNames[0];
            for (int r = 0; r < numPlayers; r++)
            {
                if (stats[r][17] > max)
                {
                    max = stats[r][17];
                    maxPlayer = playerNames[r];
                }
            }
            cout << "The player with the highest average this month was " << maxPlayer << " with " << max << endl << endl;
            break;

        case 3:
            max = stats[0][19];
            maxPlayer = playerNames[0];
            for (int q = 0; q < numPlayers; q++)
            {
                if (stats[q][19] > max)
                {
                    max = stats[q][19];
                    maxPlayer = playerNames[q];
                }
            }
            cout << "The player with the highest slugging percentage this month was " << maxPlayer << " with " << max << endl<< endl;
            break;

        case 4:
            max = stats[0][20];
            maxPlayer = playerNames[0];
            for (int m = 0; m < numPlayers; m++)
            {
                if (stats[m][20] > max)
                {
                    max = stats[m][20];
                    maxPlayer = playerNames[m];
                }
            }
            cout << "The player with the highest OPS this month was " << maxPlayer << " with " << max << endl << endl;
            break;

        default:
            return;
        }

        cout << "Choose from the following stats to show the month leader in that category:\n";
        cout << "1. Home Runs\n2. Batting average\n3. Slugging percentage\n4. OPS\n";
        cout << "Enter the number of your choice, or enter any other number to return to the previous menu.\n";

        cin >> menuChoice;

        cout << endl;
    }
   

}

void minStat(int numPlayers, int numStats) // This function is a copy of the previous one, with changes to show minimum instead of maximum
{
    vector< vector<double> > stats;
    vector<double> row;
    vector<string> playerNames;

    int menuChoice;

    double min;
    string minPlayer;

    string tempName;

    double count;

    ifstream inputStats;
    ifstream inputNames;

    inputStats.open("Stats.txt");

    for (int i = 0; i < (numStats / numPlayers); i++)
    {
        for (int j = 0; j < (numStats); j++)
        {
            inputStats >> count;
            row.push_back(count);
        }
        stats.push_back(row);
        row.clear();
    }

    inputStats.close();

    inputNames.open("Players.txt");

    for (int b = 0; b < numPlayers; b++)
    {
        inputNames >> tempName;
        playerNames.push_back(tempName);
    }

    inputNames.close();


    // Menu to choose which stat
    cout << "Choose from the following stats to show the worst monthly performer in that category:\n";
    cout << "1. Home Runs\n2. Batting average\n3. Slugging percentage\n4. OPS\n";
    cout << "Enter the number of your choice, or enter any other number to return to the previous menu.\n";

    cin >> menuChoice;

    cout << endl;

    while (menuChoice >= 1 && menuChoice <= 4)
    {
        switch (menuChoice)
        {
        case 1:
            min = stats[0][8];
            minPlayer = playerNames[0];
            for (int w = 0; w < numPlayers; w++)
            {
                if (stats[w][8] < min)
                {
                    min = stats[w][8];
                    minPlayer = playerNames[w];
                }
            }
            cout << "The player with the fewest home runs this month was " << minPlayer << " with " << min << " HRs.\n\n";
            break;

        case 2:
            min = stats[0][17];
            minPlayer = playerNames[0];
            for (int r = 0; r < numPlayers; r++)
            {
                if (stats[r][17] < min)
                {
                    min = stats[r][17];
                    minPlayer = playerNames[r];
                }
            }
            cout << "The player with the lowest average this month was " << minPlayer << " with " << min << endl << endl;
            break;

        case 3:
            min = stats[0][19];
            minPlayer = playerNames[0];
            for (int q = 0; q < numPlayers; q++)
            {
                if (stats[q][19] < min)
                {
                    min = stats[q][19];
                    minPlayer = playerNames[q];
                }
            }
            cout << "The player with the lowest slugging percentage this month was " << minPlayer << " with " << min << endl << endl;
            break;

        case 4:
            min = stats[0][20];
            minPlayer = playerNames[0];
            for (int m = 0; m < numPlayers; m++)
            {
                if (stats[m][20] < min)
                {
                    min = stats[m][20];
                    minPlayer = playerNames[m];
                }
            }
            cout << "The player with the lowest OPS this month was " << minPlayer << " with " << min << endl << endl;
            break;

        default:
            return;
        }

        cout << "Choose from the following stats to show the worst monthly performer in that category:\n";
        cout << "1. Home Runs\n2. Batting average\n3. Slugging percentage\n4. OPS\n";
        cout << "Enter the number of your choice, or enter any other number to return to the previous menu.\n";

        cin >> menuChoice;

        cout << endl;
    }


}