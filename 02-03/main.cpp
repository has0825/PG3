#include <stdio.h>      
#include <time.h>       
#include <windows.h>    


void ShowResult(int roll, int userGuess) {

	int rollParity = roll % 2;

	printf("出目は%d\n", roll);

	if (userGuess == rollParity) {
		printf("正解\n");
	} else {
		printf("不正解\n");
	}
}


void DelayReveal(void (*fn)(int, int), unsigned int delayMs, int roll, int userGuess) {
	printf("...3秒後に結果を表示...\n");

	Sleep(delayMs);

	fn(roll, userGuess);
}



int main() {

	srand((unsigned)time(NULL));

	int userGuess;

	printf("サイコロの出目は「奇数」か「偶数」か？\n");
	printf("予想を入力してください (奇数=1, 偶数=0):");

	scanf_s("%d", &userGuess);

	int roll = rand() % 6 + 1;

	DelayReveal(ShowResult, 3000, roll, userGuess);

	return 0;
}