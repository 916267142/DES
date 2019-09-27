#include "Process.h"

void Process::encryption(char plaintext[], char chipertext[], PassWord passWordSet)
{
    ///Convert char to int format
    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            this->plaintext[i * 8 + j] = (plaintext[i] >> j) & 1;
        }
    }
    initialPermutation(this->plaintext);
    for(int i = 0; i < 16; ++i) {
        roundFunction(this->plaintext, passWordSet.pwdSet[i]);
    }
    for(int i = 0; i < 32; ++i) {
        swap(this->plaintext[i], this->plaintext[i + 32]);
    }
    inverseInitialPermutation(this->plaintext);
    ///Conver int to char format
    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            if(this->plaintext[i * 8 + j]) {
                chipertext[i] |= (1 << j);
            } else {
                chipertext[i] &= ~(1 << j);
            }
        }
    }
}

void Process::initialPermutation(int plaintext[])
{
    int temp[64];
    for(int i = 0; i < 64; ++i) {
        temp[i] = plaintext[IP_Table[i]];
    }
    copy(plaintext, plaintext + 64, temp);
}

void Process::inverseInitialPermutation(int plaintext[])
{
    int temp[64];
    for(int i = 0; i < 64; ++i) {
        temp[i] = plaintext[IPInverse_Table[i]];
    }
    copy(plaintext, plaintext + 64, temp);
}

///The total number of round is 16.This is one round.
void Process::roundFunction(int plaintext[], int password[])
{
    int newL[32];
    int newR[32];
    int oldL[32];
    int oldR[32];
    copy(this->plaintext, this->plaintext + 32, oldL);
    copy(this->plaintext + 32, this->plaintext + 64, oldR);
    copy(oldR, oldR + 32, newL); ///no need. just convenient for comprehend
    int RE[48];
    for(int i = 0; i < 48; ++i) {   ///Expand 32 bits to 48 bits
        RE[i] = oldR[E_Table[i] - 1];
    }
    for(int i = 0; i < 48; ++i) {  ///Substiution 48 bits to 32 bits
        RE[i] ^= password[i];
    }
    for(int i = 0; i < 8; ++i) {  ///S-box operation
        int row = 2 * RE[i * 6] + RE[i * 6 + 5];
        int col = 8 * RE[i * 6 + 1] + 4 * RE[i * 6 + 2]
                  + 2 * RE[i * 6 + 3] + RE[i * 6 + 4];
        int answer = S_Table[i][row * 16 + col];
        for(int j = 0; j < 4; ++j) {
            oldR[i * 4 + 3 - j] = answer % 2;
            answer /= 2;
        }
    }
    for(int i = 0; i < 32; ++i) {
        newR[i] = oldR[P_Table[i] - 1];
        newR[i] ^= oldL[i];
    }
    copy(newL, newL + 32, this->plaintext);
    copy(newR, newR + 32, this->plaintext + 32);
}
