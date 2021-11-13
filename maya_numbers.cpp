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
        cout <<  "\u25CF";
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
        //cout << innum <<", "<< plc << " places" << endl;

        // rem is what's still left to process, dividend is "vigit" in current plc, so print it
        print_vigit( innum / divor );
        innum %= divor;

        divor /= 20;
    }
}

int rand_num(int min, int max) {
    // assumes already seeded (srand) in main, range inclusive
    return min + (rand() % (max - min +1));
}

size_t gen_choices(int* choice_vals, int num_choices, int corr_choice) {
    // fills choice_vals arr and returns index of corr_choice
    size_t corr_ind = rand_num(0, num_choices-1);
    choice_vals[corr_ind] = corr_choice;

    // two random incorrect choices on [1/2 * correct, 3/2 * correct]
    int rand;
    bool is_repeat = false;
    for (int i=0; i < num_choices; i++)
    {
        // only filling in incorrect choices
        if (i != corr_ind)
        {
            do {
                // just round
                //cout << endl << "min " << (int)(0.5*corr_choice) <<", max " << (int)(1.5*corr_choice) << endl;
                rand = rand_num((int)(0.5*corr_choice), (int)(1.5*corr_choice));

                // check that not same as any others; at curr iter, others is only up to i
                for (int j=0; j < i; j++) {
                    if (rand == choice_vals[j])
                        { is_repeat = true; }
                }
            } while (is_repeat);

            choice_vals[i] = rand;
        }
    }

    /*
    cout << "choices: ";
    for (int i=0; i < 3; i++) {
        cout <<' '<< choice_vals[i];
    }
    cout << endl;
    */

    return corr_ind;
}

int get_usr_int(int thresh) {
    // with input checking, will keep prompting if invalid
    int inp=0;
    cout << "Enter your decimal integer >= 10, < 10 to exit: ";
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

char get_usr_MC() {
    // multiple choice a, b or c
    char inp;
    cout << "Enter your choice out of a, b or c: ";
    cin >> inp;

    while (!(cin) || (inp != 'a' && inp != 'b' && inp != 'c') )
    {
        cout << "Not 'a', 'b' or 'c'. Please enter one of them: ";
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> inp;
    } 
    return inp;
}

const int USR_NUM_MIN = 10;
const int RAND_NUM_MIN = 4;
const int NUM_CHOICES = 3;

int main() {
    // for later rand's
    srand(time(0));

    // vars for use in loop
    // generate random choices for user to guess
    int mult_choices [NUM_CHOICES];
    int right_decim = 0;
    size_t right_ind = 0;
    char choice;

    int usr_lim = 0;
    while (usr_lim != -1)
    {
        cout << "Welcome to Mayan Number Game!" << endl << "Here you will enter a number >= 10, the game will choose one <= your's, then you'll need to match it with the right Mayan numeral representation!" << endl;

        // if usr input < USR_NUM_MIN, get_usr_int() returned exit code is -1
        usr_lim = get_usr_int(USR_NUM_MIN);
        if (usr_lim == -1) {
            return 0;
        }

        // correct choice, range [const min, user-inputted limit] 
        right_decim = rand_num(RAND_NUM_MIN, usr_lim);
        cout << "Which is the correct Mayan representation of " << right_decim <<'?' << endl;

        right_ind = 0;
        //cout << "randomly generated right choice = " << right_decim << endl;
        right_ind = gen_choices(mult_choices, NUM_CHOICES, right_decim);

        // list out multiple choices, order already randomized by gen_choices()
        for (int i=0; i < NUM_CHOICES; i++) {
            // preceding choice letters, i.e. a, b, c
            cout << char('a'+i) <<". " << endl;
            printMayanNumber(mult_choices[i]);
            cout << endl;
        }
        choice = get_usr_MC();
        //cout << choice << endl;
        // check choice by matching "index" in multiple choices to correct choice index
        if (int(choice - 'a') == right_ind) {
            cout << "You are right!" << endl;
        }
        else {
            cout << "Sorry, not right." << endl;
        }
        cout << "The correct answer was " << right_decim <<", which is " << endl;
        printMayanNumber(right_decim);
        cout <<endl<< "Would you fancy another go?" << endl;

    } 
    //cout << num_places(usr_lim) << endl;
    /*
    int test [] = {0, 4, 5, 17};
    for (int num : test)
    {
        print_vigit(num);
    }
    */

    return 0;
}
