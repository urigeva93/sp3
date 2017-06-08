/*
 * main.c
 *
 *  Created on: 5 ביוני 2017
 *      Author: uri
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "SPMiniMax.h"
#include "SPFIARParser.h"
#include "SPMainAux.h"

#define historySize 10

int main() {

	setvbuf(stdout, NULL, _IONBF, 0);
	int difficulty = initGame(), cmd = 0;
	if(difficulty == -1)// the user entered quit during init
		exit(0);
	bool winflag = false;
	char winner = ' ';
	SPFiarGame* game = spFiarGameCreate(historySize);
	while (true) {
		spFiarGamePrintBoard(game);
		cmd = playturn(game, difficulty, winflag);
		if (cmd == QUIT)
			exit(0);

		if (cmd == RESTART) {
			spFiarGameDestroy(game);
			difficulty = initGame();
			if(difficulty == -1)// the user entered quit during init
				exit(0);
			game = spFiarGameCreate(historySize);
			winflag = false;
			continue;
		}

		if (cmd == ADD_DISC) {
			winflag = false;
			winner = spFiarCheckWinner(game);
			if (winner != '\0') {
				winnerDeclaration(winner);
				winflag = true;
				continue;
			}
			compPlay(game, difficulty);
			winner = spFiarCheckWinner(game);
			if (winner != '\0') {
				winnerDeclaration(winner);
				winflag = true;
				continue;
			}
		}
		if (cmd == NO_CHANGED)
			continue;
		if (cmd == UNDO_MOVE) {
			winflag = false;
			continue;
		}
	}
}
//
//int main() {

// main for tests
//	SPFiarGame* src = spFiarGameCreate(10);
//	char symbol1 = SP_FIAR_GAME_PLAYER_1_SYMBOL;
//	//char symbol2 = SP_FIAR_GAME_PLAYER_2_SYMBOL;
//	spFiarGamePrintBoard(src);
//	int col = spMinimaxSuggestMove(src, 3);
//	src->gameBoard[0][col] = symbol1;
//	spFiarGamePrintBoard(src);
//	spFiarGameDestroy(src);
//}

