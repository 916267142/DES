#include "PassWord.h"

PassWord::PassWord(char passWord[]) {
    int pwd64[64];
    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            pwd64[i * 8 + j] = (passWord[i] >> j) & 1;
        }
    }
    int pwd56[56];
    permutedChoice1(pwd64, pwd56);
    for(int i = 0; i < 16; ++i) {
        leftCircularShift(i, pwd56);
        permutedChoice2(i, pwd56);
    }
}

void PassWord::leftCircularShift(int time, int pwd56[]) {
    int pwd56tmp[56];
    for(int i = 0; i < 56; ++i) {
        pwd56tmp[i] = pwd56[(i - LeftShfitTable[time] + 56) % 56];
    }
    copy(pwd56tmp, pwd56tmp + 56, pwd56);
}

void PassWord::permutedChoice2(int time, int pwd56[]) {
    for(int i = 0; i < 48; ++i) {
        pwdSet[time][i] = pwd56[PC2Table[i] - 1];
    }
}

void PassWord::permutedChoice1(int pwd64[], int pwd56[]) {
    for(int i = 0; i < 56; ++i) {
        pwd56[i] = pwd64[PC1Table[i] - 1];
    }
}

void PassWord::reversePwdSet() {
    for(int i = 0; i < 8; ++i) {
        swap(pwdSet[i], pwdSet[15 - i]);
    }
}
