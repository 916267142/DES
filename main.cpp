#include <iostream>
#include <fstream>
#include <sstream>
#include "PassWord.h"
#include "Process.h"
using namespace std;

//This is a test sentence

int main()
{
    string inputName;
    string outputName;
    int pattern;
    char passWord[8];
    char plaintext[8];
    char chipertext[8];

    cout << "Please enter the input file name" << endl;
    cin >> inputName;
    cout << "Please enter the output file name" << endl;
    cin >> outputName;
    cout << "Please enter operation type 1. Encryption 2. Decryption" << endl;
    cin >> pattern;
    cout << "Please enter the password" << endl;
    for(int i = 0; i < 8; ++i) {
        cin >> passWord[i];
    }
    PassWord passWordSet(passWord);
    if(pattern == 2) {  ///If you want to perform decryption, simply reverse the password
        passWordSet.reversePwdSet();
    }
    ifstream cin1(inputName);
    ofstream cout1(outputName);
    Process process;   ///Read in without filtering whitespace or enter
    int counter;
    for(counter = 1; cin1 >> noskipws >> plaintext[counter - 1];) {
        if(counter == 8) {
            process.encryption(plaintext, chipertext, passWordSet);
            for(int i = 0; i < 8; ++i) {
                cout1 << chipertext[i];
            }
            counter = 1;
        } else {
            counter++;
        }
    }
    if(pattern == 1 && counter != 1) {
        for(int i = counter - 1; i < 8; ++i) {
            plaintext[i] = ' ';
        }
        process.encryption(plaintext, chipertext, passWordSet);
        for(int i = 0; i < 8; ++i) {
            cout1 << chipertext[i];
        }
    }
    cin1.close();
    cout1.close();
    return 0;
}

/*
This is the bit operation in C++
set i as 1: c |= (1 << i);
set i as 0: c &= ~(1<<i);
return the value: return (c >> i) & 1;
set the reserve value: c ^= (1 << i);


This is a example for input
plaintext.txt
chipertext.txt
1
qwer1234

chipertext.txt
plaintext2.txt
2
qwer1234
*/
