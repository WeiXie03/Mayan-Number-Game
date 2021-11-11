/* Game in which players guess the correct Mayan numeral representation of random numbers within a range set by the player.
 * Author: Tom Xie, 2021
*/

#include <iostream>
#include <ios>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

int num_places(int dec) {
    // counts the total number of places in the decimal number
    int plcs = 0;
    while (dec > 0)
    {
        dec /= 10;
        plcs++;
    }
    return plcs;
}

/*
int place_multiple(int num, int base, int place) {
    // returns the multiple/digit of the specified place in the input number of specified base system
    return num ;
}
*/

void print_fives(int num) {
    for (int i=0; i < num; ++i)
    {
        // 6 black char blocks make bar
        for (int j=0; j < 6; ++j) {
            cout << "\u2580";
        }
        cout << endl;
    }
}

void print_ones(int num) {
    for (int i=0; i < num; ++i)
    {
        cout <<  " O";
    }
    cout << endl;
}

void print_vigit(int num) {
    // prints one Mayan "block", a vigesimal digit
    if (num == 0) {
        cout << '@' << endl;
    }
    else
    {
        // divide as many 5's then 1's as possible
        int fives = num / 5;
        int ones = num % 5;
        print_ones(ones);
        print_fives(fives);
    }
    // horiz divider
    cout << string(8, '_') << endl;
}

void printMayanNumber(int dec) {
    // convert to base 20, by successively dividing by 20
    int plc = 0;
    while (dec > 0)
    {
        dec /= 20;
        
        plc++;
    }
}

int main() {
    /*
    int innum;
    cout << "Enter decimal number: ";
    cin >> innum;
    */

    //cout << num_places(innum) << endl;
    int test [] = {0, 4, 5, 17};
    for (int num : test)
    {
        print_vigit(num);
    }

    return 0;
}
