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

int num_places(int num, int base) {
    // counts the total number of places in the number in the specified base system
    int plcs = 0;
    while (num > 0)
    {
        num /= base;
        plcs++;
    }
    return plcs;
}

/*
int place_multiple(int num, int base, int place) {
    // returns the multiple/digit of the specified place in the input number of specified base system, ones place is 0th
    // "trim" preceding digits
    num %= (int) pow(base, place+1);
    // "trim" trailing digits
    num /= pow(base, place);
    return num;
}
*/

void printMayanNumber(int innum) {
    // go through vigesimal "vigits", greatest to least place
    int plc = num_places(innum, 20);
    int divor = pow(20, plc);

    // initial check, should not print a zero at start/top
    if (innum/divor == 0) {
        plc--;
        divor /= 20;
    }

    for ( ; plc >= 0; plc--)
    {
        // start with the vigit
        //divid = place_multiple(innum, 20, plc);
        cout << innum <<", "<< plc << " places" << endl;

        // rem is what's still left to process, dividend is "vigit" in current plc, so print it
        print_vigit( innum / divor );
        innum %= divor;

        divor /= 20;
    }
}

int get_usr_int(int thresh) {
    // with input checking, will keep prompting if invalid
    int inp=0;
    cout << "Enter your decimal integer >= 10: ";
    cin >> inp;

    while (!(cin))
    {
        cout << "Not an integer. Please enter an integer: ";
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> inp;
    } 

    if (inp < thresh) {
        // alert/error code
        return -1;
    }

    return inp;
}

const int USR_NUM_MIN = 10;

int main() {
    int innum;
    innum = get_usr_int(USR_NUM_MIN);
    if (innum == -1) {
        // returned exit code
        return 0;
    }

    printMayanNumber(innum);

    //cout << num_places(innum) << endl;
    /*
    int test [] = {0, 4, 5, 17};
    for (int num : test)
    {
        print_vigit(num);
    }
    */

    return 0;
}
