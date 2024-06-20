#include<iostream>
#include<cstdlib>
#include<time.h>
using namespace std;

// 1. Get Deposit
// 2. Get number of lines as input
// 3. Get Bet Amount
// 4. Decide symbols and assign values to them
// 5. Spin the slot machine
// 6. Increment the Deposit if the symbols match
// 7. Decrement the Deposit if it's a mismatch
// 8. End the game if the Deposit becomes 0
// 9. Play again

int getDeposit() {
	int deposit = 0;

	do {
		cout << "Enter your deposit amount: " << endl;
		cin >> deposit;

		if (deposit <= 0)
			cout << "Deposit cannot be zero or negative. Please enter again." << endl;

	} while (deposit <= 0);

	return deposit;
}

int getBetAmount() {
	int betAmount = 0;

	do {
		cout << "Enter your bet amount: " << endl;
		cin >> betAmount;

		if (betAmount <= 0)
			cout << "Bet amount cannot be zero or negative. Please enter again." << endl;

	} while (betAmount <= 0);

	return betAmount;
}

int getNumOfLines() {
	int num = 0;

	do {
		cout << "Enter the number of lines (1-3):" << endl;
		cin >> num;

		if (num <= 0 || num > 3) 
			cout << "INVALID CHOICE! Please Enter Again.\n" << endl;

	} while (num <= 0 || num > 3);

	return num;
}

void spinSlotMachine(char slotMachine[3][3]) {
	srand(time(0));

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			slotMachine[i][j] = (65 + rand() % 3);
		}
	}
}

char checkMatchMismatch(char slotMachine[3][3], int numOfLines) {
	bool flag = true;
	char symbol = '\0';

	for (int i = 0; i < numOfLines; i++) {
		bool flag = true; // to check for match in each line
	
		for (int j = 1; j < 3; j++) {
			if (slotMachine[i][j] != slotMachine[i][j - 1]) {
				flag = false; // mismatch occurred in that line
				break;
			}
		}

		// match occurred
		if (flag) {
			symbol = slotMachine[i][0]; // to save the symbol that matched
			break;
		}
	}

	return symbol;
}

int incrementDeposit(int betAmount, int symbolValue) {
	return (betAmount * symbolValue);
}

int decrementDeposit(int betAmount, int numOfLines) {
	return (betAmount * numOfLines);
}

int valueOfSymbol(char symbol) {
	if (symbol == 'A')
		return 4;

	else if (symbol == 'B')
		return 6;

	else
		return 2;
}

void displaySlotMachine(char slotMachine[3][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << slotMachine[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {
	char slotMachine[3][3]{ '\0' }, symbol = '\0';
	int deposit = 0, betAmount = 0, numOfLines = 0, choice = 0;

	deposit = getDeposit();
	
	while (1) {
		if (deposit == 0) {
			cout << "NO MORE MONEY LEFT!" << endl;
			exit(0);
		}

		betAmount = getBetAmount();
		numOfLines = getNumOfLines();
		
		cout << "Spinning the Slot Machine..." << endl;
		spinSlotMachine(slotMachine);
		displaySlotMachine(slotMachine);

		symbol = checkMatchMismatch(slotMachine, numOfLines);

		if (symbol != '\0') {
			cout << "\nMatch Occurred!" << endl;
			deposit += incrementDeposit(betAmount, valueOfSymbol(symbol));
			cout << "Your new deposit is: " << deposit << endl;
		}
		
		else {
			cout << "\nNo Match Occurred :(" << endl;
			deposit -= decrementDeposit(betAmount, numOfLines);
			cout << "Your new deposit is: " << deposit << endl;
		}

		cout << "\nPress 1 to continue playing or any other key to exit" << endl;
		cin >> choice;

		if (choice != 1)
			exit(0);
	}
}