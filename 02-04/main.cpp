#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>       
#include <windows.h>    

void DelayReveal(void (*fn)(int, int), unsigned int delayMs, int roll, int userGuess) {
    printf("...3秒後に結果を表示します...\n"); 
    Sleep(delayMs);
    fn(roll, userGuess);
}

int main() {
    srand((unsigned)time(NULL));
    int userGuess;
    printf("サイコロの出目は「奇数」か「偶数」か？\n");
    printf("予想を入力してください (奇数=1, 偶数=0): ");
    scanf_s("%d", &userGuess);
    int roll = rand() % 6 + 1;
    DelayReveal(
        [](int r, int ug) {
            
            int rollParity = r % 2; 

            printf("出目は %d でした。\n", r);

            if (ug == rollParity) {
                printf("正解\n");
            } else {
                printf("不正解\n");
            }
        },
        3000,       
        roll,      
        userGuess   
    );
    return 0;
}