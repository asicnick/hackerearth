// seatingArrangement.cpp : Defines the entry point for the console application.
//

#include <stdio.h>

int main() {
	int num_tests;
	int *pseats;
	int pdiv;
	int pdiv_round;
	int pmod;
	int pmod4;
	int popp;
	char seat_type[3];
	char* p_seat_type;
	int opp_seat;

	scanf("%d", &num_tests);

	p_seat_type = seat_type;
	pseats = new int[num_tests];

	for (int i = 0; i<num_tests; i++) {
		scanf("%d", &pseats[i]);
	}

	for (int i = 0; i<num_tests; i++) {
		pdiv = pseats[i] / 3;
		pdiv_round = (pseats[i] > pdiv * 3) ? pdiv + 1 : pdiv;
		pmod = pseats[i] % 3;
		pmod4 = pdiv_round % 4;
		popp = (pmod4 == 3 || pmod4 == 0) ? 1 : 0;
		p_seat_type = "MS";
		// EVEN GROUP
		if (pdiv_round % 2 == 0){

			opp_seat = (!popp) ? pseats[i] + 3 : pseats[i] - 9;
			if (pmod == 0) {
				p_seat_type = "WS";
				opp_seat = !(popp) ? pseats[i] + 1 : pseats[i] - 11;
			}
			else if (pmod == 1) {
				p_seat_type = "AS";
				opp_seat = (!popp) ? pseats[i] + 5 : pseats[i] - 7;
			}


			// ODD GROUP
		}
		else {
			opp_seat = (!popp) ? pseats[i] + 9 : pseats[i] - 3;
			if (pmod == 0) {
				p_seat_type = "AS";
				opp_seat = (!popp) ? pseats[i] + 7 : pseats[i] - 5;
			}
			else if (pmod == 1) {
				p_seat_type = "WS";
				opp_seat = (!popp) ? pseats[i] + 11 : pseats[i] - 1;
			}

		}

		printf("%d %s\n", opp_seat, p_seat_type);
	}
}