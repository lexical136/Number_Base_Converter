#include <iostream>
#include <vector>
#include <string>

using namespace std;
static string convertFunc(int base, int newBase, string input);
static string convertToNew(int newBase, long long int input);


int main()
{
    //vars for the base and new base
    int base, newBase;

    //var for the main number
    string input = "";

    //user input
    cin >> base;
    cin >> newBase;
    cin >> input;
    
    //printing the return string
    cout << convertFunc(base, newBase, input);
}

//Converts to base 10. Easy on the brain
static string convertFunc(int base, int newBase, string input) {
    //a number that gets multiplied by the base each loop. Represents the true value of a position in a number like the 2 in 120 being 2 10s. 
    //for example with 100 at base 16 the 3rd place (the 1) would have a movingBase of 256 and we have 1 of them so the total value is 256.
    long long int movingBase = 1;

    //Big number for storing the result. A long in java will probaly do. With the constraints you would need to be able to hold 100000000000000.
    long long int result = 0;

    //looping through the input string. Starting from the right.
    for (int i = input.length() - 1; i >= 0; i--) {

        //if the ascii value is within [48,57]. This means its a num else its a letter representing a number.
        if ((int)input[i] >= 48 && (int)input[i] <= 57) {
            //converts the char to an int by subtracting the ascii code for '0' from the ascii code for the char
            //then multiple by the movingBase and add to result
            result = result + (movingBase * (input[i] - '0'));
        }
        else {
            //removes 87 from the char value. This would make a = 10 due to a being 97. Idk why I didnt just use the number instead. Thats a capital btw.
            result = result + (movingBase * (input[i] - 'W'));
        }

        movingBase = movingBase * base;
    }

    return convertToNew(newBase, result);
}

//Converts from base 10 to desired base
//Method I used here https://www.wikihow.com/Convert-from-Decimal-to-Octal yes wikihow
static string convertToNew(int newBase, long long int input) {
    //stores result
    string result = "";

    int highestValidPower = 0;
    //Finds the highest power that will let the base^pow <= to the input. It'll over shoot by 1 so I -1.
    while (pow(newBase, highestValidPower) <= input) {
        highestValidPower++;
    }
    highestValidPower--;

    //highestValidPower shows the number of spaces the number will take. for 213 base 10 to base 20 the highest valid power would be 20 because 1.. 20.. 400. 400 is too big
    //so we start at 2 because 20 is the second.
    while (highestValidPower >= 0) {

        //if the newBase^highestValidPower is less than in the remaining input add a '0'
        if (pow(newBase, highestValidPower) <= input) {

            //temp is how many times the newBase^highestValidPower goes into the input. This results in the value for this space
            long long int temp = (input / (long long int)pow(newBase, highestValidPower));
            
            //if a true number else its a letter
            if (temp < 10) {
                result.append(1, temp + '0');
            }
            else {
                result.append(1, temp + 87); //I used the number instead of the capital 'W'
            }

            //subtract newBase^HP from total
            input = input - (long long int)pow(newBase, highestValidPower) * (input / (long long int)pow(newBase, highestValidPower));
        }
        else {
            result.append(1, '0');
        }

        highestValidPower--;
    }

    return result;
}
