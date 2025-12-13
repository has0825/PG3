#include <iostream>
#include <cstdio>


long long recursiveHourlyWage(int h) {
	if (h <= 1) {
		return 100;
	}
	return recursiveHourlyWage(h - 1) * 2 - 50;
}

void compareWageSystems() {
	long long standardTotalWage = 0;
	long long recursiveTotalWage = 0;
	const int STANDARD_HOURLY_WAGE = 1226;
	int hours = 0;


	printf("Hour | Standard Total | Recursive Hourly | Recursive Total\n");
	printf("----------------------------------------------------------\n");

	while (true) {
		hours++;
		standardTotalWage += STANDARD_HOURLY_WAGE;

		long long currentRecursiveHourly = recursiveHourlyWage(hours);
		recursiveTotalWage += currentRecursiveHourly;


		printf("%4d | %14lld | %16lld | %15lld\n",
			hours, standardTotalWage, currentRecursiveHourly, recursiveTotalWage);

		if (recursiveTotalWage > standardTotalWage) {
			break;
		}
	}

	printf("----------------------------------------------------------\n");
	printf("After %d hours, the recursive wage system becomes more profitable.\n", hours);
}

int main() {
	compareWageSystems();
	return 0;
}