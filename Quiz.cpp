#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <thread>
#include <chrono>
#include <string.h>
#include <random>
using namespace std;

const int MIN_ADDITION_AND_SUBTRACTION_NUMBER = 1110;
const int MAX_ADDITION_AND_SUBTRACTION_NUMBER = 7890;
const int MIN_MULTIPLY_NUMBER = 21;
const int MAX_MULTIPLY_NUMBER = 47;
// In miliseconds -> times 1000 to get seconds
const int QUIZ_TIME = 120000;

random_device rd;
mt19937 generator(rd());
uniform_int_distribution<> operationDistr(1, 3);

enum Operator {
	ADDITION = 1,
	SUBTRACT = 2,
	MULTIPLY = 3
};

struct Question {
	int leftOperand, rightOperand, answer;
	Operator opr;
};

bool doQuiz = true;

void wait(int milliseconds){
	this_thread::sleep_for(chrono::milliseconds(milliseconds));
	doQuiz = false;
}

int getRandomNumber(int min, int max){
	return (min + (rand() % (max - min + 1)));
}

Question generateQuestion(){
	Question newQuestion;
	newQuestion.opr = (Operator)operationDistr(generator);
	
	switch(newQuestion.opr){
		case ADDITION:
			newQuestion.leftOperand = getRandomNumber
				(MIN_ADDITION_AND_SUBTRACTION_NUMBER, MAX_ADDITION_AND_SUBTRACTION_NUMBER);
			newQuestion.rightOperand = getRandomNumber
				(MIN_ADDITION_AND_SUBTRACTION_NUMBER, MAX_ADDITION_AND_SUBTRACTION_NUMBER);
			newQuestion.answer = newQuestion.leftOperand + newQuestion.rightOperand;
			break;
		case SUBTRACT:
			newQuestion.leftOperand = getRandomNumber
				(MIN_ADDITION_AND_SUBTRACTION_NUMBER, MAX_ADDITION_AND_SUBTRACTION_NUMBER);
			newQuestion.rightOperand = getRandomNumber
				(MIN_ADDITION_AND_SUBTRACTION_NUMBER, MAX_ADDITION_AND_SUBTRACTION_NUMBER);
			newQuestion.answer = newQuestion.leftOperand - newQuestion.rightOperand;
			break;
		case MULTIPLY:
			newQuestion.leftOperand = getRandomNumber
				(MIN_MULTIPLY_NUMBER, MAX_MULTIPLY_NUMBER);
			newQuestion.rightOperand = getRandomNumber
				(MIN_MULTIPLY_NUMBER, MAX_MULTIPLY_NUMBER);
			newQuestion.answer = newQuestion.leftOperand * newQuestion.rightOperand;
			break;
	}
	return newQuestion;
}

void printQuestion(Question question){
	char operation;
	switch(question.opr){
		case ADDITION:
			operation = '+';
			break;
		case SUBTRACT:
			operation = '-';
			break;
		case MULTIPLY:
			operation = '*';
			break;
	}
	printf("%d %c %d = ", question.leftOperand, operation, question.rightOperand);
}

bool validateAnswer(int answer, int correctAnswer){
	if (answer == correctAnswer){
//		printf("Correct\n");
		return true;
	}
	else {
//		printf("False\n");
		return false;
	}
}

void printMenu(){
	printf("Welcome to my quick math quiz!\n");
	printf("Answer the question correctly to get a point!\n");
	printf("You won't be penalized if you get any questions wrong!\n");
	printf("You have 2 minutes to answer as many questions as possible!\n");
	printf("Included questions:\n");
	printf("- Addition and Subtraction [%d - %d]\n",
		MIN_ADDITION_AND_SUBTRACTION_NUMBER, MAX_ADDITION_AND_SUBTRACTION_NUMBER);
	printf("- Multiplication [%d - %d]\n", MIN_MULTIPLY_NUMBER, MAX_MULTIPLY_NUMBER);
	printf("Good Luck!\n");
	printf("Press Enter to continue...");
	getchar();
	system("cls");
}

void printQuizResult(int correct, int wrong){
	system("cls");
	printf("====================\n");
	printf("    YOUR RESULTS    \n");
	printf("====================\n");
	printf("Wrong Answer = %d\n", wrong);
	printf("Total Answered = %d\n", (correct + wrong));
	printf("Total Points = %d\n", correct);
	printf("====================\n");
}

int main(){
	srand((unsigned) time(0));
	int correct = 0, wrong = 0;
	
	printMenu();
	thread timer(wait, QUIZ_TIME);
	while(doQuiz){
		int answer = 0;
		Question question = generateQuestion();
		printQuestion(question);
		scanf("%d", &answer); getchar();
		if (validateAnswer(answer, question.answer))
			correct++;
		else
			wrong++;
	}
	printQuizResult(correct, wrong);
	timer.join();
	getchar();
	return 0;
}
