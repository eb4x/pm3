#include <assert.h>
#include <ctype.h>
#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct gamea {

	union {
		struct {
			int16_t premier_league[22];
			int16_t division_one[24];
			int16_t division_two[24];
			int16_t division_three[22];
			int16_t conference_league[22];
			int16_t misc[4];
		} __attribute__ ((packed));
		int16_t all[118];
	} __attribute__ ((packed)) teams;

	union {
		struct {
			struct { int16_t club_idx; uint8_t data[26]; } __attribute__ ((packed)) premier_league[22];
			struct { int16_t club_idx; uint8_t data[26]; } __attribute__ ((packed)) division_one[24];
			struct { int16_t club_idx; uint8_t data[26]; } __attribute__ ((packed)) division_two[24];
			struct { int16_t club_idx; uint8_t data[26]; } __attribute__ ((packed)) division_three[22];
			struct { int16_t club_idx; uint8_t data[26]; } __attribute__ ((packed)) conference_league[22];
		} __attribute__ ((packed));
		struct { int16_t club_idx; int16_t hx; int16_t hw; int16_t hd; int16_t hl; int16_t hf; int16_t ha;
		                           int16_t ax; int16_t aw; int16_t ad; int16_t al; int16_t af; int16_t aa;
		                           int16_t xx;
		} __attribute__ ((packed)) all[114];
	} __attribute__ ((packed)) table;
		

	uint8_t data000[8]; //3200

	union {
		struct {
			struct { int16_t player_idx; int16_t club_idx; int8_t pl; int8_t sc; } __attribute__ ((packed)) premier_league[15];
			struct { int16_t player_idx; int16_t club_idx; int8_t pl; int8_t sc; } __attribute__ ((packed)) division_one[15];
			struct { int16_t player_idx; int16_t club_idx; int8_t pl; int8_t sc; } __attribute__ ((packed)) division_two[15];
			struct { int16_t player_idx; int16_t club_idx; int8_t pl; int8_t sc; } __attribute__ ((packed)) division_three[15];
			struct { int16_t player_idx; int16_t club_idx; int8_t pl; int8_t sc; } __attribute__ ((packed)) conference_league[15];
		} __attribute__ ((packed));
		struct { int16_t player_idx; int16_t club_idx; int8_t pl; int8_t sc; } __attribute__ ((packed)) all[75];
	} __attribute__ ((packed)) top_scorers; //450

	uint16_t sorted_numbers[64];

	struct {
		char name[14];
		uint8_t magic : 3;
		uint8_t age   : 5;
		uint8_t var[7];
	} __attribute__ ((packed)) referee[64];


	union {
		struct {
			struct { struct { int16_t idx; int16_t goals; int32_t audience; } __attribute__ ((packed)) team[2]; } __attribute__ ((packed)) the_fa_cup[36];
			struct { struct { int16_t idx; int16_t goals; int32_t audience; } __attribute__ ((packed)) team[2]; } __attribute__ ((packed)) the_league_cup[28];
			struct { struct { int16_t idx; int16_t goals; int32_t audience; } __attribute__ ((packed)) team[2]; } __attribute__ ((packed)) data090[4];
			struct { struct { int16_t idx; int16_t goals; int32_t audience; } __attribute__ ((packed)) team[2]; } __attribute__ ((packed)) the_champions_cup[16];
			struct { struct { int16_t idx; int16_t goals; int32_t audience; } __attribute__ ((packed)) team[2]; } __attribute__ ((packed)) data091[16];
			struct { struct { int16_t idx; int16_t goals; int32_t audience; } __attribute__ ((packed)) team[2]; } __attribute__ ((packed)) the_cup_winners_cup[16];
			struct { struct { int16_t idx; int16_t goals; int32_t audience; } __attribute__ ((packed)) team[2]; } __attribute__ ((packed)) the_uefa_cup[32];
			struct { struct { int16_t idx; int16_t goals; int32_t audience; } __attribute__ ((packed)) team[2]; } __attribute__ ((packed)) the_charity_shield;
//			struct { struct { int16_t idx; int16_t goals; int32_t audience; } __attribute__ ((packed)) team[2]; } __attribute__ ((packed)) data094[8];
//			struct { struct { int16_t idx; int16_t goals; int32_t audience; } __attribute__ ((packed)) team[2]; } __attribute__ ((packed)) the_charity_shield_fixtures[2];
		};
		struct { struct { int16_t idx; int16_t goals; int32_t audience; } __attribute__ ((packed)) team[2]; } __attribute__ ((packed)) all[149];
	} __attribute__ ((packed)) cuppy;
		
//	uint8_t data095[2080];
	uint8_t data095[2240];

	struct {
		int16_t club1_idx;
		int16_t club1_goals;
		int32_t club1_audience;
		int16_t club2_idx;
		int16_t club2_goals;
		int32_t club2_audience;
	} __attribute__ ((packed)) the_charity_shield_history; // history?

	struct {
		int16_t club1_idx;
		int16_t club1_goals;
		int32_t club1_audience;
		int16_t club2_idx;
		int16_t club2_goals;
		int32_t club2_audience;
	} __attribute__ ((packed)) some_table[16]; // history?

	union {
		struct {
			struct { struct { int16_t idx; int16_t goals; int32_t audience; } __attribute__ ((packed)) team[2]; } __attribute__ ((packed)) the_fa_cup[0];
		};
		struct { struct { int16_t idx; int16_t goals; int32_t audience; } __attribute__ ((packed)) team[2]; } __attribute__ ((packed)) all[57];
	} __attribute__ ((packed)) last_results;

	struct {
		struct {
			int16_t year;
			int16_t club_idx;
			uint8_t data[12];
		} __attribute__ ((packed)) history[20];
	} __attribute__ ((packed)) league[5];

	struct {
		struct {
			int16_t year;
			int16_t club_idx_winner;
			int16_t club_idx_runner_up;
			uint8_t type_winner;
			uint8_t type_runner_up;
		} __attribute__ ((packed)) history[20];
	} __attribute__ ((packed)) cup[6];

	struct {
		int16_t club_idx1;
		int16_t club_idx2;
	} __attribute__ ((packed)) fixture[20];

	uint8_t data100[494];

	struct {
		int16_t ix_player;
		int16_t ix_team1;
		int16_t ix_team2;
		int32_t fee;
	} __attribute__ ((packed)) transfer[6];

	uint8_t data101[20];
	int16_t retired_manager_club_idx;
	int16_t new_manager_club_idx;
	char manager_name[16];
	uint8_t data10w[8];
	uint16_t turn;
	uint16_t year;
	uint8_t data10x[30];

	struct player {
		char manager[16]; //manager 1?
		int16_t club_idx;
		int16_t unk_number;
		uint16_t contract_length;

		struct {
			uint8_t league_match_seating;
			uint8_t league_match_terrace;
			uint8_t cup_match_seating;
			uint8_t cup_match_terrace;
		}__attribute__ ((packed)) price;

		uint32_t seating_history[23]; //history
		uint32_t terrace_history[23];
//		uint8_t data103[128];

		struct {
			int32_t gate_receipts[2];
			int32_t club_wages[2];
			int32_t transfer_fees[2];
			int32_t club_fines[2];
			int32_t grants_for_club[2];
			int32_t club_bills[2];
			int32_t miscellaneous_sales[2];
			int32_t bank_loan_payments[2];
			int32_t ground_improvements[2];
			int32_t advertising_boards[2];
			int32_t other_items[2];
			int32_t account_interest[2];
		} __attribute__ ((packed)) bank_statement[2];

		struct {
			uint32_t amount;
			uint8_t turn; //3 turns in a week, 42 weeks in a year?
			uint8_t year;
		} __attribute__ ((packed)) loan[4];

		struct {
			char name[14];
			uint8_t skill;
			uint8_t type : 4;
			uint8_t age  : 4;
		} __attribute__ ((packed)) employee[20];

		struct {
			uint8_t do_training_schedules;
			uint8_t treat_injured_players;
			uint8_t check_sponsors_boards;
			uint8_t hire_and_fire_employees;
			uint8_t negotiate_player_contracts;
		} __attribute__ ((packed)) assistant_manager;

		uint8_t data120;
		uint8_t youth_player_type;
		uint8_t data121;

		int16_t youth_player;

		uint8_t data147[4];

		struct {
			uint8_t skill;
			uint8_t rating;
			uint8_t division : 3;
			uint8_t foot : 5;
			uint8_t team;
			struct {
				int16_t ix1;
				int16_t ix2;
			} __attribute__ ((packed)) results[18];
			uint8_t other[6];
		} __attribute__ ((packed)) scout[4];

		uint32_t number1;
		uint32_t number2;
		uint32_t number3;
		uint32_t money_from_directors;
		uint8_t data149[20];

		struct {
			int16_t type;
			int32_t amount;
			int16_t ix1;
			int16_t ix2;
			int16_t ix3;
		} __attribute__ ((packed)) news[8];

		int32_t minus_one;
		int16_t player_idx;
		uint8_t data150[578];

		struct {
			char string[20];
		} __attribute__ ((packed)) stadium[4];

		struct {
			uint8_t level : 3;
			uint8_t time  : 5;
		} __attribute__ ((packed)) seating_build[4];

		struct {
			uint8_t level : 3;
			uint8_t time  : 5;
		} __attribute__ ((packed)) seating[4];

		struct {
			uint8_t level : 3;
			uint8_t time  : 5;
		} __attribute__ ((packed)) area_covering[4];

		struct {
			uint32_t level :  3;
			uint32_t time  : 29;
		} __attribute__ ((packed)) ground_facilities;

		struct {
			uint32_t level :  3;
			uint32_t time  : 29;
		} __attribute__ ((packed)) supporters_club;

		struct {
			uint32_t level :  3;
			uint32_t time  : 29;
		} __attribute__ ((packed)) flood_lights;

		struct {
			uint32_t level :  3;
			uint32_t time  : 29;
		} __attribute__ ((packed)) scoreboard;

		struct {
			uint32_t level :  3;
			uint32_t time  : 29;
		} __attribute__ ((packed)) undersoil_heating;

		struct {
			uint32_t level :  3;
			uint32_t time  : 29;
		} __attribute__ ((packed)) changing_rooms;

		struct {
			uint32_t level :  3;
			uint32_t time  : 29;
		} __attribute__ ((packed)) gymnasium;

		struct {
			uint32_t level :  3;
			uint32_t time  : 29;
		} __attribute__ ((packed)) car_park;

		uint8_t safety_rating[4];

		uint16_t seating_capacity[4];

		int16_t numb01;
		int16_t numb02;
		int16_t numb03;
		int16_t numb04;

		uint8_t managerial_rating_start;
		uint8_t managerial_rating_current;
		uint8_t directors_confidence_start;
		uint8_t directors_confidence_current;
		uint8_t supporters_confidence_start;
		uint8_t supporters_confidence_current;

		uint8_t head6[6];
		int16_t player_idx1;
		uint8_t magic4[4];
		int16_t player_idx2;
		uint8_t foot6[6];

		struct { 
			uint16_t club;
			uint16_t total_goals;
			uint16_t first_half_goals;
			uint8_t pattern6[6]; // 02 00 26 50 60 77
			uint8_t match_data1[4];
			uint8_t corners;
			uint8_t throw_ins;
			uint8_t free_kicks;
			uint8_t penalties;

			struct {
				int16_t player_idx;
				uint8_t data6[6];
				uint8_t red_card;
				uint8_t data11[11];
			} __attribute__ ((packed)) lineup[14];

			struct {
				int16_t player_idx;
				int16_t time;
			} __attribute__ ((packed)) goal[8];

			uint16_t always_null;
			uint8_t substitutions_remaining;
			uint8_t other;
			uint16_t home_away_data; // home: 0x5738, away: 0x91f8
		} __attribute__ ((packed)) match[2]; // home + away team

		uint16_t weather;
		uint8_t referee;
		uint8_t data156[4];
		/*
 * 1e fa_cup semi final
 * 1f fa_cup 4th/5th,
 * 20 fa_cup 3rd,
 * 21 league cup 2nd round 1, 4th round, quarter final
 * 22 league cup 2nd round 2, 3rd round
 * 23 champions cup 1st leg 1,
 * 24 cup_win_cup 2nd round 1/2/qfinal
 * 28 premier
 * 2b conference
		*/
		uint8_t match_type;
		uint8_t data157[6];
		uint32_t audience;
		uint8_t data158[92];

		struct {
			uint16_t year;
			uint16_t div;
			uint16_t club_idx;
			uint16_t ps;
			uint16_t p;
			uint16_t w;
			uint16_t d;
			uint16_t l;
			uint16_t gd;
			uint16_t pts;
			uint8_t unk21;
			uint8_t unk22;
			uint8_t unk23;
			uint8_t unk24;
			uint8_t unk25;
			uint8_t unk26;
			uint8_t unk27;
			uint8_t unk28;
			uint8_t unk29;
			uint8_t unk30;
			uint8_t unk31;
			uint8_t unk32;
		} __attribute__ ((packed)) league_history[20];

		struct {
			uint16_t won;
			uint16_t yrs;
		} __attribute__ ((packed)) titles[11];

		struct {
			uint16_t play;
			uint16_t won;
			uint16_t drew;
			uint16_t lost;
			uint16_t forx;
			uint16_t agn;
		} __attribute__ ((packed)) manager_history[11];

		uint8_t data159[12];

		struct {
			int16_t year_from;
			int16_t year_to;
			uint8_t club_idx;
			uint8_t mngr;
			uint8_t drct;
			uint8_t sprt;
		} __attribute__ ((packed)) previous_clubs[4];

		int16_t year_start_cur_club;

		uint16_t manager_of_the_month_awards;
		uint16_t manager_of_the_year_awards;

		struct { //1936
			uint8_t team;
			uint8_t played;
			uint8_t won;
			uint8_t u3;
			uint8_t goals_f;
			uint8_t u5;
			uint8_t goals_a;
			uint8_t u7;
		} __attribute__ ((packed)) match_history[242];

		uint8_t data160[1794];

		struct {
			char name[20];
		} __attribute__ ((packed)) tactic[8];
	} __attribute__ ((packed)) player[2];

	uint8_t data200[16];

} __attribute__ ((packed)) gamea;

struct gameb {
	struct team {
		char name[16];
		char manager[16];
		int32_t bank_account;
		char stadium[24];
		int32_t seating_avg;
		int32_t seating_max;
		uint8_t padding[8];
		int16_t player_index[24];

		uint8_t misc000[76];

		struct {
			struct {
				struct {

					uint8_t team;

					union {
						struct {
							uint8_t home: 4;
							uint8_t away: 4;
						} __attribute__ ((packed));
						int8_t result;
					};

					union {
						struct {
							uint8_t type: 5;
							uint8_t game: 3;
						} __attribute__ ((packed));
						uint8_t b3;
					};

				} __attribute__ ((packed)) day[3];
			} __attribute__ ((packed)) week[41];
			uint8_t end;
		} __attribute__ ((packed)) timetable;

	} __attribute__ ((packed)) team[244];

} __attribute__ ((packed)) gameb;

struct gamec {
	struct player {
		char name[12];

		uint8_t u13;
		uint8_t hn;
		uint8_t u15;
		uint8_t tk;
		uint8_t u17;
		uint8_t ps;
		uint8_t u19;
		uint8_t sh;
		uint8_t u21;
		uint8_t hd;
		uint8_t u23;
		uint8_t cr;
		uint8_t u25;
		uint8_t ft;

		uint8_t morl : 4;
		uint8_t aggr : 4;

		uint8_t ins : 2;
		uint8_t age : 6;

		uint8_t foot : 2;
		uint8_t dpts : 6;

		uint8_t played;
		uint8_t scored;
		uint8_t unk2;
		uint16_t wage;
		uint16_t ins_cost;
		uint8_t inj_away;

		uint8_t unk4: 5;
		uint8_t contract : 3;

		uint8_t unk5;

		uint8_t train   : 4;
		uint8_t intense : 4;

	} __attribute__ ((packed))player[3932];
} __attribute__ ((packed)) gamec;

void dump_gamea(struct gamea *ga);
void dump_gameb(struct gameb *gb);
void dump_gamec(struct gamec *gc);

void dump_team(struct gameb::team *t);
void dump_player(struct gamec::player *p, int32_t idx);

int main(int argc, char *argv[])
{
	int c, optindex = 0;
	int aopt = 0, bopt = 0, copt = 0, soup = 0;

	static struct option long_options[] = {
		{ "help", 0, 0, 'h' },
		{ "soup-up", 0, 0, 's' },
		{ "version", 0, 0, 'v' },
		{ 0, 0, 0, 0 }
	};

	while ((c = getopt_long(argc, argv, "abc", long_options, &optindex)) != -1) {

		switch (c) {
			case 'a': aopt = 1; break;
			case 'b': bopt = 1; break;
			case 'c': copt = 1; break;
			case 's': soup = 1; break;
			default: break;
		}
	}

	if (optind >= argc) {
		fprintf(stderr, "Usage: %s GAME<d>[ABC]>\n", argv[0]);
		fprintf(stderr, "Try '%s --help' for more information.\n", argv[0]);
		return EXIT_FAILURE;
	}

	char gamexa[7];
	char gamexb[7];
	char gamexc[7];

	assert(isdigit(argv[optind][0]));

	sprintf(gamexa, "GAME%.1dA", atoi(argv[optind]));
	sprintf(gamexb, "GAME%.1dB", atoi(argv[optind]));
	sprintf(gamexc, "GAME%.1dC", atoi(argv[optind]));

	printf("%s, %s, %s\n", gamexa, gamexb, gamexc);

	printf("sizeof(gamea)        = 0x%0zx\n", sizeof( struct gamea ));
	printf("sizeof(gameb.team)   = 0x%0zx\n", sizeof( struct gameb::team ));
	printf("sizeof(gamec.player) = 0x%0zx\n", sizeof( struct gamec::player ));

	assert( sizeof( struct gamea )         == 0x7372);
	assert( sizeof( struct gameb::team   ) == 0x023A );
	assert( sizeof( struct gamec::player ) == 0x0028 );

	FILE *fga = fopen(gamexa, "r");
	if (fga == NULL) {
		printf("Could not open file: %s\n", gamexa);
		exit(EXIT_FAILURE);
	}
	fread(&gamea, sizeof (struct gamea), 1, fga);
	fclose(fga);

	FILE *fgb = fopen(gamexb, "r");
	if (fgb == NULL) {
		printf("Could not open file: %s\n", gamexb);
		exit(EXIT_FAILURE);
	}
	fread(&gameb, sizeof (struct gameb), 1, fgb);
	fclose(fgb);

	FILE *fgc = fopen(gamexc, "r");
	if (fgb == NULL) {
		printf("Could not open file: %s\n", gamexc);
		exit(EXIT_FAILURE);
	}
	fread(&gamec, sizeof (struct gamec), 1, fgc);
	fclose(fgc);

// -- * -- * -- //
	if ( aopt ) {
		printf("GAME%dA\n", atoi(argv[argc-1]));
		dump_gamea(&gamea);
	}

	if ( bopt ) {
		printf("GAME%dB\n", atoi(argv[argc-1]));
		dump_gameb(&gameb);
	}

	if ( copt ) {
		printf("GAME%dC\n", atoi(argv[argc-1]));
		dump_gamec(&gamec);
	}

	if ( soup ) {
		printf("Souping up GAME%d\n", atoi(argv[argc-1]));
		int16_t club_idx = gamea.player[0].club_idx;

		for (int p = 0; p < 24; ++p) {
			int16_t player_idx = gameb.team[ club_idx ].player_index[p];

			if ( player_idx == -1)
				continue;

			gamec.player[ player_idx ].hn = 97;
			gamec.player[ player_idx ].tk = 97;
			gamec.player[ player_idx ].ps = 97;
			gamec.player[ player_idx ].sh = 97;

			switch ( p ) {
				case  0:
				case 11:
				case 15:
					gamec.player[ player_idx ].hn = 99; break;

				case  1:
				case  2:
				case  4:
				case  5:
				case 12:
				case 16:
				case 19:
				case 22:
					gamec.player[ player_idx ].tk = 99; break;

				case  3:
				case 10:
				case 13:
				case 17:
				case 20:
					gamec.player[ player_idx ].ps = 99; break;

				case  6:
				case  7:
				case  8:
				case  9:
				case 14:
				case 18:
				case 21:
				case 23:
					gamec.player[ player_idx ].sh = 99; break;

				default: break;
			}

			gamec.player[ player_idx ].hd = 99;
			gamec.player[ player_idx ].cr = 99;
			gamec.player[ player_idx ].ft = 99;
		}

		FILE *fga2 = fopen(gamexa, "w+");
		fwrite(&gamea, sizeof (struct gamea), 1, fga2);
		fclose(fga2);

		FILE *fgb2 = fopen(gamexb, "w+");
		fwrite(&gameb, sizeof (struct gameb), 1, fgb2);
		fclose(fgb2);

		FILE *fgc2 = fopen(gamexc, "w+");
		if (fgc2 == NULL) {
			printf("Could not open file: %s\n", "GAME9C");
			exit(EXIT_FAILURE);
		}
		fwrite(&gamec, sizeof (struct gamec), 1, fgc2);
		fclose(fgc2);
	}

	return EXIT_SUCCESS;
}

void check_consistency()
{
	int all[3932];
	for (int i = 0; i < 3932; ++i)
		all[i] = -1;

	for (int t = 0; t < 244; ++t) {
		fprintf(stderr, "Team[%3d]\n", t);
		for (int p = 0; p < 24; ++p) {
			if ( gameb.team[t].player_index[p] == -1 )
				continue;

			if (all[ gameb.team[t].player_index[p] ] == -1) {

				all[ gameb.team[t].player_index[p] ] = t;
				printf("Added %d %12.12s to %16.16s\n",
					                 gameb.team[t].player_index[p],
					gamec.player[    gameb.team[t].player_index[p] ].name,
					gameb.team[t].name);

			} else {
				printf("Duplicate. %4d %12.12s plays for\n"
					"%16.16s AND %16.16s\n",
					                 gameb.team[t].player_index[p],
					gamec.player[    gameb.team[t].player_index[p] ].name,
					gameb.team[ all[ gameb.team[t].player_index[p] ] ].name,
					gameb.team[t].name);
			}
		}
	}

	for (int i = 0; i < sizeof(all); ++i) {
		if ( all[i] != -1)
			continue;

		fprintf(stderr, "%4d %12.12s is without a club.\n",
			i, gamec.player[i].name);
	}
}

void dump_gamea(struct gamea *ga) {

	int correction = 0;
	for (int i = 0; i < 118; ++i) {
		switch (i) {
			case   0: correction =   0; printf("Premier league teams\n");      break;
			case  22: correction =  22; printf("\nDivision 1 teams\n");        break;
			case  46: correction =  46; printf("\nDivision 2 teams\n");        break;
			case  70: correction =  70; printf("\nDivision 3 teams\n");        break;
			case  92: correction =  92; printf("\nConference league teams\n"); break;
			case 114: correction = 114; printf("\nMisc teams\n");              break;
			default: break;
		}

		printf("%2d (%04x) %16.16s\n", i + 1 - correction,
			           gamea.teams.all[i], 
			gameb.team[gamea.teams.all[i]].name);
	}
	printf("\n");

	printf("XXX Testing XXX\n");
	for (int i = 0; i <  22; ++i) {
		printf("%16.16s\n", gameb.team[ gamea.table.premier_league[i].club_idx ].name );
	}

	for (int i = 0; i < 114; ++i) {
		switch (i) {
			case   0:
				correction =   0;
				printf("Premier league home/away table\n");
			   printf("Club              W  D  L  F  A   W  D  L  F  A\n");
				break;
			case  22:
				correction =  22;
				printf("\nDivision 1 home/away table\n");
			   printf("Club              W  D  L  F  A   W  D  L  F  A\n");
				break;
			case  46:
				correction =  46;
				printf("\nDivision 2 home/away table\n");
			   printf("Club              W  D  L  F  A   W  D  L  F  A\n");
				break;
			case  70:
				correction =  70;
				printf("\nDivision 3 home/away table\n");
			   printf("Club              W  D  L  F  A   W  D  L  F  A\n");
				break;
			case  92:
				correction =  92;
				printf("\nConference league home/away table\n");
			   printf("Club              W  D  L  F  A   W  D  L  F  A\n");
				break;
			default:
				break;
		}

		printf("%16.16s", gameb.team[gamea.table.all[i].club_idx].name);
		printf(" %2d %2d %2d %2d %2d  %2d %2d %2d %2d %2d, (%02x %02x %02x)",
			gamea.table.all[i].hw,
			gamea.table.all[i].hd,
			gamea.table.all[i].hl,
			gamea.table.all[i].hf,
			gamea.table.all[i].ha,
			gamea.table.all[i].aw,
			gamea.table.all[i].ad,
			gamea.table.all[i].al,
			gamea.table.all[i].af,
			gamea.table.all[i].aa,
			gamea.table.all[i].hx, gamea.table.all[i].ax, gamea.table.all[i].xx );
/*
		for (int j = 0; j < 2; ++j) {
			printf(" %2d %2d %2d %2d %2d",
			gamea.table.all[i].homeaway[j].w,
			gamea.table.all[i].homeaway[j].d,
			gamea.table.all[i].homeaway[j].l,
			gamea.table.all[i].homeaway[j].f,
			gamea.table.all[i].homeaway[j].a);
			printf(" ");
		}
*/
		printf("\n");
	
	}

	for (int i = 0; i < sizeof (ga->data000); ++i) {
		if ( i % 16 == 0 )
			printf("\n[%04d] ", i);
		printf("%02x ", ga->data000[i]);
	}
	printf("\n\n");

	for (int i = 0; i < 75; ++i) {
		switch (i) {
			case   0: correction =   0; printf("Premier league top scorers\n");
				printf("Player       Rating       Club             PL SC\n"); break;
			case  15: correction =  15; printf("\nDivision 1 top scorers\n");
				printf("Player       Rating       Club             PL SC\n"); break;
			case  30: correction =  30; printf("\nDivision 2 top scorers\n");
				printf("Player       Rating       Club             PL SC\n"); break;
			case  45: correction =  45; printf("\nDivision 3 top scorers\n");
				printf("Player       Rating       Club             PL SC\n"); break;
			case  60: correction =  60; printf("\nConference league top scorers\n");
				printf("Player       Rating       Club             PL SC\n"); break;
			default: break;
		}
		
		if ( gamea.top_scorers.all[i].player_idx == -1 )
			printf("skip\n");
		else
			printf("%12.12s %12.12s %16.16s %2d %2d\n",
				gamec.player[ gamea.top_scorers.all[i].player_idx ].name, "",
				gameb.team[   gamea.top_scorers.all[i].club_idx ].name,
				gamea.top_scorers.all[i].pl, gamea.top_scorers.all[i].sc
			);
	}
	printf("\n");

	printf("Sorted numbers\n");
	for (int i = 0; i < 64; ++i) {
		printf("[%2d] %04x %16.16s\n", i, gamea.sorted_numbers[i], gameb.team[ gamea.sorted_numbers[i] ].name );
	}
	printf("\n");

	for (int i = 0; i < 64; ++i) {
		printf("Referee: (%02x)%14.14s - %d : %d ", i, ga->referee[i].name, 40 + ga->referee[i].age, ga->referee[i].magic);

		for (int j = 0; j < sizeof(ga->referee[i].var); ++j)
			printf("%02x ", ga->referee[i].var[j]);
		printf("\n");
	}
	printf("\n");

	printf("Cuppy!\n");
//	for (int i = 0; i < 149; ++i) {
	for (int i = 0; i < 149; ++i) {
		if ( gamea.cuppy.all[i].team[0].idx == -1 || gamea.cuppy.all[i].team[1].idx == -1 ||
		     gamea.cuppy.all[i].team[0].idx > 244 || gamea.cuppy.all[i].team[1].idx > 244 ){
			printf("cuppy.all[%3d]: %04x %d %5d (%5d) %5d %d %04x\n", i,
				gamea.cuppy.all[i].team[0].idx, gamea.cuppy.all[i].team[0].goals, gamea.cuppy.all[i].team[0].audience,
				0,
 				gamea.cuppy.all[i].team[1].audience, gamea.cuppy.all[i].team[1].goals, gamea.cuppy.all[i].team[1].idx
			);
			continue;
		}

		printf("cuppy.all[%3d]: (%04x) %16.16s %d %5d (%5d) %5d %d (%04x) %16.16s\n", i,
			gamea.cuppy.all[i].team[0].idx, gameb.team[ gamea.cuppy.all[i].team[0].idx ].name,
			gamea.cuppy.all[i].team[0].goals,           gamea.cuppy.all[i].team[0].audience,
			gamea.cuppy.all[i].team[0].audience +       gamea.cuppy.all[i].team[1].audience,
			gamea.cuppy.all[i].team[1].audience,        gamea.cuppy.all[i].team[1].goals, 
			gamea.cuppy.all[i].team[1].idx, gameb.team[ gamea.cuppy.all[i].team[1].idx ].name
		);

	}

	for (int i = 0; i < sizeof( ga->data095 ); ++i) {
		if ( i % 16 == 0 )
			printf("\n[%04d] ", i);
		printf("%02x ", ga->data095[i]);
	}
	printf("\n");

	printf("The charity shield history: (%04x) %16.16s : (%04x) %16.16s\n",
			ga->the_charity_shield_history.club1_idx, gameb.team[ ga->the_charity_shield_history.club1_idx ].name,
			ga->the_charity_shield_history.club2_idx, gameb.team[ ga->the_charity_shield_history.club2_idx ].name
	);
	printf("                                 %5d %5d : %5d %5d\n",
		ga->the_charity_shield_history.club1_goals, ga->the_charity_shield_history.club1_audience,
		ga->the_charity_shield_history.club2_goals, ga->the_charity_shield_history.club2_audience
	);

	for (int i = 0; i < 11; ++i) {
		printf("(%04x) %16.16s %d %5d" " (%5d) "
		       "%5d %d (%04x) %16.16s\n",
			ga->some_table[i].club1_idx,
			gameb.team[ga->some_table[i].club1_idx].name,
			ga->some_table[i].club1_goals,
			ga->some_table[i].club1_audience,
			ga->some_table[i].club1_audience + ga->some_table[i].club2_audience,
			ga->some_table[i].club2_audience,
			ga->some_table[i].club2_goals,
			ga->some_table[i].club2_idx,
			gameb.team[ga->some_table[i].club2_idx].name);
	}
	printf("\n");

	printf("Last results\n");
	for (int i = 0; i < 47; ++i) {
		if ( gamea.last_results.all[i].team[0].idx == 0 && gamea.last_results.all[i].team[1].idx == 0 ) {
			printf("empty\n");
			continue;
		}
		printf("(%04x) %16.16s %d %5d (%5d) %5d %d (%04x) %16.16s\n",
			gamea.last_results.all[i].team[0].idx, gameb.team[ gamea.last_results.all[i].team[0].idx ].name,
			gamea.last_results.all[i].team[0].goals,           gamea.last_results.all[i].team[0].audience,
			gamea.last_results.all[i].team[0].audience +       gamea.last_results.all[i].team[1].audience,
			gamea.last_results.all[i].team[1].audience,        gamea.last_results.all[i].team[1].goals, 
			gamea.last_results.all[i].team[1].idx, gameb.team[ gamea.last_results.all[i].team[1].idx ].name
		);
	}
	printf("\n");

	static const char *division_num[] = {
		"Premier league",
		"Division 1",
		"Division 2",
		"Division 3",
		"Conference league"
	};

	for (int lg = 0; lg < 5; ++lg) {
		printf("Previous %s champions\n", division_num[lg]);
		for (int h = 0; h < 20; ++h) {
			if (ga->league[lg].history[h].year == 0)
				continue;
			printf("%4d: (%04x) %16.16s",
				ga->league[lg].history[h].year,
				ga->league[lg].history[h].club_idx, gameb.team[ ga->league[lg].history[h].club_idx ].name
			);
	
			for (int i = 0; i < sizeof( ga->league[lg].history[h].data ); ++i) {
				printf(" %02x", ga->league[lg].history[h].data[i]);
			}
			printf("\n");
		}
		printf("\n");
	}

	static const char *cup[] = {
		"F.A. cup",
		"League cup",
		"Champions cup",
		"Cup winners cup",
		"U.E.F.A. cup",
		"Charity shield",
	};

	static const char *team_type_short[] = {
		"",
		"ITA", //1
		"GER", //2
		"SPA", //3
		"HOL", //4
		"",
		"RUS", //6
		"SCO", //7
		"", //
		"", //
		"", //
		"", //
		"", //
		"", //
		"", //
		"", //
		"", //
		"", //
		"", //
		"", //
		"PRM", //20
		"DV1", //21
		"DV2", //22
		"DV3", //23
		"CNF"  //24
	};

	for (int cp = 0; cp < 6; ++cp) {
		printf("Previous %s finals\n", cup[cp]);
		for (int h = 0; h < 20; ++h) {
			if (ga->cup[cp].history[h].year == 0)
				continue;
			printf("%4d: (%04x) %s:%16.16s",
				ga->cup[cp].history[h].year,
				ga->cup[cp].history[h].club_idx_winner,
				team_type_short[ ga->cup[cp].history[h].type_winner ],
				gameb.team[ ga->cup[cp].history[h].club_idx_winner ].name
			);

			printf(" (%04x) %s:%16.16s",
				ga->cup[cp].history[h].club_idx_runner_up,
				team_type_short[ ga->cup[cp].history[h].type_runner_up ],
				gameb.team[ ga->cup[cp].history[h].club_idx_runner_up ].name
			);
			printf("\n");
		}
		printf("\n");
	}

	printf("Fixtures\n");
	for (int i = 0; i < 20; ++i) {
		printf("%d: (%04x) %16.16s - (%04x) %16.16s\n", i,
			ga->fixture[i].club_idx1, gameb.team[ ga->fixture[i].club_idx1 ].name,
			ga->fixture[i].club_idx2, gameb.team[ ga->fixture[i].club_idx2 ].name
		);
	}

	printf("data100\n");
	for (int i = 0; i < sizeof( ga->data100 ); ++i) {
		if ( i % 16 == 0 )
			printf("\n[%4d] ", i);
		printf("%02x ", ga->data100[i]);
	}
	printf("\n");

	printf("--- Transfer list ---\n");
	for (int i = 0; i < 6; ++i) {
		if ( ga->transfer[i].ix_player == -1 )
			continue;

		printf("%12.12s was transfered from %16.16s\n"
			"to %16.16s for a fee of £%d\n",
		gamec.player[ga->transfer[i].ix_player].name,
		gameb.team[ga->transfer[i].ix_team1].name,
		gameb.team[ga->transfer[i].ix_team2].name,
		ga->transfer[i].fee);
	}

	for (int i = 0; i < sizeof( ga->data101 ); ++i) {
		if ( i % 16 == 0 )
			printf("\n[%4d] ", i);
		printf("%02x ", ga->data101[i]);
	}
	printf("\n");

	if ( ga->retired_manager_club_idx != -1 ) {
		printf("%16.16s has retired from (%04x) %16.16s\n",
			ga->manager_name,
			ga->retired_manager_club_idx,
			gameb.team[ ga->retired_manager_club_idx ].name);
	}

	if ( ga->new_manager_club_idx != -1 ) {
		printf("%16.16s has become the new manager of\n(%04x) %16.16s\n",
			gameb.team[ ga->new_manager_club_idx ].manager,
			ga->new_manager_club_idx,
			gameb.team[ ga->new_manager_club_idx ].name);
	}

	for (int i = 0; i < sizeof( ga->data10w ); ++i) {
		if ( i % 16 == 0 )
			printf("\n[%4d] ", i);
		printf("%02x ", ga->data10w[i]);
	}
	printf("\n");

	printf("Year: %4d, Turn: %2d\n", ga->year, ga->turn);

	for (int i = 0; i < sizeof( ga->data10x ); ++i) {
		if ( i % 16 == 0 )
			printf("\n[%4d] ", i);
		printf("%02x ", ga->data10x[i]);
	}
	printf("\n");

	for ( int nr = 0; nr < 1; ++nr ) { // XXX don't care about second player
		printf("Manager: %16.16s\n", ga->player[nr].manager);

		printf("(%04x)Club: %16.16s\n", ga->player[nr].club_idx, gameb.team[ ga->player[nr].club_idx ].name);
		printf("Unk number: %d\n",ga->player[nr].unk_number);
		printf("Contract: %d\n", ga->player[nr].contract_length);
		printf("League match: Seating..£%-2d\n"
		       "League match: Terraces.£%-2d\n"
		       "Cup match: Seating.....£%-2d\n"
		       "Cup match: Terraces....£%-2d\n",
			ga->player[nr].price.league_match_seating,
			ga->player[nr].price.league_match_terrace,
			ga->player[nr].price.cup_match_seating,
			ga->player[nr].price.cup_match_terrace);

		for (int i = 0; i < sizeof(ga->player[nr].seating_history) / sizeof(ga->player[nr].seating_history[0]); ++i) {
			printf("Seating%02d: %5d\n", i,
				ga->player[nr].seating_history[i]);
		}

		for (int i = 0; i < sizeof(ga->player[nr].terrace_history) / sizeof(ga->player[nr].terrace_history[0]); ++i) {
			printf("Terrace%02d: %5d\n", i,
				ga->player[nr].terrace_history[i]);
		}


		for (int i = 0; i < 2; ++i) {
			if ( i == 0 )
				printf("daily bank statement\n");
			if ( i == 1 )
				printf("yearly bank statement\n");

			printf("gate receipts       = %8d %8d\n", ga->player[nr].bank_statement[i].gate_receipts[0],       ga->player[nr].bank_statement[i].gate_receipts[1]);
			printf("club wages          = %8d %8d\n", ga->player[nr].bank_statement[i].club_wages[0],          ga->player[nr].bank_statement[i].club_wages[1]);
			printf("transfer fees       = %8d %8d\n", ga->player[nr].bank_statement[i].transfer_fees[0],       ga->player[nr].bank_statement[i].transfer_fees[1]);
			printf("club fines          = %8d %8d\n", ga->player[nr].bank_statement[i].club_fines[0],          ga->player[nr].bank_statement[i].club_fines[1]);
			printf("grants for club     = %8d %8d\n", ga->player[nr].bank_statement[i].grants_for_club[0],     ga->player[nr].bank_statement[i].grants_for_club[1]);
			printf("club bills          = %8d %8d\n", ga->player[nr].bank_statement[i].club_bills[0],          ga->player[nr].bank_statement[i].club_bills[1]);
			printf("miscellaneous sales = %8d %8d\n", ga->player[nr].bank_statement[i].miscellaneous_sales[0], ga->player[nr].bank_statement[i].miscellaneous_sales[1]);
			printf("bank loan payments  = %8d %8d\n", ga->player[nr].bank_statement[i].bank_loan_payments[0],  ga->player[nr].bank_statement[i].bank_loan_payments[1]);
			printf("ground improvements = %8d %8d\n", ga->player[nr].bank_statement[i].ground_improvements[0], ga->player[nr].bank_statement[i].ground_improvements[1]);
			printf("advertising boards  = %8d %8d\n", ga->player[nr].bank_statement[i].advertising_boards[0],  ga->player[nr].bank_statement[i].advertising_boards[1]);
			printf("other items         = %8d %8d\n", ga->player[nr].bank_statement[i].other_items[0],         ga->player[nr].bank_statement[i].other_items[1]);
			printf("account interest    = %8d %8d\n", ga->player[nr].bank_statement[i].account_interest[0],    ga->player[nr].bank_statement[i].account_interest[1]);
			printf("\n");
		}

		for (int i = 0; i < 4; ++i)
			printf("Loan %d:£%-6d, due %d year%s %d turn%s\n",
				i, ga->player[nr].loan[i].amount,
				ga->player[nr].loan[i].year, ga->player[nr].loan[i].year == 1 ? "" : "s",
				ga->player[nr].loan[i].turn, ga->player[nr].loan[i].turn == 1 ? "" : "s");
		printf("\n");

		static const char *type[] = {
			"Assistant",
			"Youth team",
			"Physio",
			"Scout",
			"4", "5", "6",
			"Head coach",
			"Coach [HN]",
			"Coach [TK]",
			"Coach [PS]",
			"Coach [SH]",
		};

		for (int i = 0; i < 20; ++i) {
			printf("Employee: %14.14s (%d), %2d %s\n",
				ga->player[nr].employee[i].name,
				ga->player[nr].employee[i].age + 40,
				ga->player[nr].employee[i].skill,
				type[ ga->player[nr].employee[i].type ] );

			if (ga->player[nr].employee[i].skill)
				ga->player[nr].employee[i].skill = 99;
		}
/*
		memcpy(
			&(ga->player[nr].employee[16]),
			&(ga->player[nr].employee[12]),
			sizeof(ga->player[nr].employee[0]) * 4);
*/ //memset?

		static const char *nyn[] = { "N/A", "Yes", "No" };

		printf("Do training schedules.......: %s\n"
		       "Treat injured players.......: %s\n"
		       "Check sponsors boards.......: %s\n"
		       "Hire and fire employees.....: %s\n"
		       "Negotiate player contracts..: %s\n",
			nyn[ ga->player[nr].assistant_manager.do_training_schedules      ],
			nyn[ ga->player[nr].assistant_manager.treat_injured_players      ],
			nyn[ ga->player[nr].assistant_manager.check_sponsors_boards      ],
			nyn[ ga->player[nr].assistant_manager.hire_and_fire_employees    ],
			nyn[ ga->player[nr].assistant_manager.negotiate_player_contracts ]);

		printf("\n%02x\n", ga->player[nr].data120);

		static const char *skill[] = { "Handling", "Tackling", "Passing", "Shooting" };
		printf("Type of youth player required:%s\n",
			skill[ ga->player[nr].youth_player_type ]);

		printf("%02x\n", ga->player[nr].data121);

		if ( ga->player[nr].youth_player != -1 )
			printf("Youth team player: %12.12s\n", 
				gamec.player[ ga->player[nr].youth_player ].name);

		for (int i = 0; i < sizeof( ga->player[nr].data147 ); ++i) {
			if ( i % 16 == 0 )
				printf("\n[%3d] ", i);
			printf("%02x ", ga->player[nr].data147[i]);
		}
		printf("\n");

		static const char *division[] = {
			"Premier league",
			"Division one",
			"Division two",
			"Division three",
			"Conference league"
		};

		static const char *foot[] = {
			"Left",
			"Right",
			"Both",
			"Any"
		};

		static const char *rating[] = {
			"Fair *",
			"Fair **",
			"Fair ***",
			"Fair ****",
			"Fair *****",
			"Good *",
			"Good **",
			"Good ***",
			"Good ****",
			"Good *****",
			"V.Good *",
			"V.Good **",
			"V.Good ***",
			"V.Good ****",
			"V.Good *****"
		};

		for (int i = 0; i < 4; ++i) {
			printf("Scout[%d]\n"
				"Division: %s\n"
				"Club: %d\n"
				"Skill: %s\n"
				"Rating: %s\n"
				"Foot: %s\n",
				i, division[ ga->player[nr].scout[i].division ],
				ga->player[nr].scout[i].team,
				skill[ ga->player[nr].scout[i].skill ],
				rating[ ga->player[nr].scout[i].rating ],
				foot[ ga->player[nr].scout[i].foot ]);
			
			for (int j = 0; j < 18; ++j) {
				if ( ga->player[nr].scout[i].results[j].ix1 == -1)
					continue;

				printf("  %12.12s %04x\n",
					gamec.player[ ga->player[nr].scout[i].results[j].ix1 ].name,
					ga->player[nr].scout[i].results[j].ix2);
			}

			for (int j = 0; j < sizeof( ga->player[nr].scout[i].other ); ++j) {
				printf("%02x ", ga->player[nr].scout[i].other[j]);
			}
			printf("\n");

			printf("\n");
		}
	
		printf("Number 1            :%d\n", ga->player[nr].number1);
		printf("Number 2            :%d\n", ga->player[nr].number2);
		printf("Number 3            :%d\n", ga->player[nr].number3);
		printf("Money from directors:%d\n", ga->player[nr].money_from_directors);

		for (int i = 0; i < sizeof( ga->player[nr].data149 ); ++i) {
			if ( i % 16 == 0 )
				printf("\n[%3d] ", i);
			printf("%02x ", ga->player[nr].data149[i]);
		}
		printf("\n");

		printf("--News--\n");
		for ( int i = 0; i < 8; ++i ) {
			switch ( ga->player[nr].news[i].type ) {
				case 1:
					printf("The V.A.T. demand has been payed to the department\n"
						"of customs and excise\n");
					break;

				case 2:
					printf("Due to a mistake in your last tax return you have\n"
						"received a bill of £%-7d from the taxman\n", ga->player[nr].news[i].amount);
					break;

				case 3:
					printf("You have exceeded your overdraft limit so you are\n"
						"now liable for a higher rate of interest\n");
					break;

				case 9:
					printf("You have received a grant of £%-7d from the\n"
						"F.A. for general ground improvements\n",
						ga->player[nr].news[i].amount);
					break;

				case 10:
					printf("The club has been fined £%-7d for bringing the\n"
						"game into disrepute\n", ga->player[nr].news[i].amount);
					break;

				case 12:
					printf("After receiving a complaint of poor hygiene the\n"
						"health authority have fined you £%d\n", ga->player[nr].news[i].amount);
					break;

				case 16:
					printf("The board pays the shareholders £%d\n",
						ga->player[nr].news[i].amount);
					break;

				case 17:
					printf("%12.12s is playing for his country today\n",
						gamec.player[ ga->player[nr].news[i].ix2 ].name);
					break;

				case 18:
					printf("A national TV station has payed your club £%d\n"
						"for the live T.V. coverage of your last match\n", 
						ga->player[nr].news[i].amount);
					break;

				case 20:
					printf("%12.12s has now retired from football\n",
						gamec.player[ ga->player[nr].news[i].ix2 ].name);
					break;

				case 21:
					printf("%12.12s will be taking early retirement from\n"
					       "football in 4 weeks time\n",
						gamec.player[ ga->player[nr].news[i].ix2 ].name);
					break;

				case 22:
					printf("%12.12s has now taken early retirement for a\n"
					       "life of luxury in the Costa del Sol\n",
						gamec.player[ ga->player[nr].news[i].ix2 ].name);
					break;

				case 23:
					printf("%12.12s has retired due to an injury\n",
						gamec.player[ ga->player[nr].news[i].ix2 ].name);
					break;

				case 24:
					printf("A member of your staff has retired\n");
					break;

				case 25:
					printf("%12.12s has been injured while training\n",
						gamec.player[ ga->player[nr].news[i].ix2 ].name);
					break;

				case 26:
					printf("The youth team coach has found a youth player who\n"
						"matches your requirements\n");
					break;

				case 27:
					printf("%12.12s due to having no contract left with\n"
						"your club has now signed for %16.16s\n",
						gamec.player[ ga->player[nr].news[i].ix2 ].name,
						gameb.team[ ga->player[nr].news[i].ix1 ].name);
					break;

				case 29:
					printf("Phone me up %16.16s from %16.16s\n"
						"Telephone No. 84444 (%12.12s)\n",
						gameb.team[ ga->player[nr].news[i].ix1 ].manager,
						gameb.team[ ga->player[nr].news[i].ix1 ].name,
						gamec.player[ ga->player[nr].news[i].ix2 ].name);
						break;

				case 30:
					printf("You have been voted manager of the month\n");
					break;

				case 31:
					printf("Your job application to become the manager of\n"
						"%16.16s has been turned down\n", gameb.team[ ga->player[nr].news[i].ix1 ].name);
					break;

				case 32:
					printf("The board of directors have given you a public\n"
						"vote of confidence\n");
					break;

				default:
					printf("%3d, %d, (%d, %d, %d)\n",
						ga->player[nr].news[i].type,
						ga->player[nr].news[i].amount,
						ga->player[nr].news[i].ix1,
						ga->player[nr].news[i].ix2,
						ga->player[nr].news[i].ix3);
					break;
			}
		}

		assert(ga->player[nr].minus_one == -1);

		if ( ga->player[nr].player_idx == -1 )
			printf("NewsPlayer1: %d ", ga->player[nr].player_idx);
		else
			printf("NewsPlayer1: (%04x) %12.12s",
				ga->player[nr].player_idx,
				gamec.player[ ga->player[nr].player_idx ].name
			);

		for (int i = 0; i < sizeof( ga->player[nr].data150 ); ++i) {
			if ( i % 16 == 0 )
				printf("\n[%4d] ", i);
			printf("%02x ", ga->player[nr].data150[i]);
		}
		printf("\n");

		for ( int i = 0; i < 4; ++i )
			printf("stadium[%d].string: %20.20s\n", i, ga->player[nr].stadium[i].string);
		printf("\n");

		printf("seating_build[north] = %d, %d\n", ga->player[nr].seating_build[0].level, ga->player[nr].seating_build[0].time);
		printf("seating_build[east ] = %d, %d\n", ga->player[nr].seating_build[1].level, ga->player[nr].seating_build[1].time);
		printf("seating_build[south] = %d, %d\n", ga->player[nr].seating_build[2].level, ga->player[nr].seating_build[2].time);
		printf("seating_build[west ] = %d, %d\n", ga->player[nr].seating_build[3].level, ga->player[nr].seating_build[3].time);

		printf("seating[north] = %d, %d\n", ga->player[nr].seating[0].level, ga->player[nr].seating[0].time);
		printf("seating[east ] = %d, %d\n", ga->player[nr].seating[1].level, ga->player[nr].seating[1].time);
		printf("seating[south] = %d, %d\n", ga->player[nr].seating[2].level, ga->player[nr].seating[2].time);
		printf("seating[west ] = %d, %d\n", ga->player[nr].seating[3].level, ga->player[nr].seating[3].time);

		printf("area_covering[north] = %d, %d\n", ga->player[nr].area_covering[0].level, ga->player[nr].area_covering[0].time);
		printf("area_covering[east ] = %d, %d\n", ga->player[nr].area_covering[1].level, ga->player[nr].area_covering[1].time);
		printf("area_covering[south] = %d, %d\n", ga->player[nr].area_covering[2].level, ga->player[nr].area_covering[2].time);
		printf("area_covering[west ] = %d, %d\n", ga->player[nr].area_covering[3].level, ga->player[nr].area_covering[3].time);

		printf("ground_facilities = %d, %d\n", ga->player[nr].ground_facilities.level, ga->player[nr].ground_facilities.time);
		printf("supporters_club   = %d, %d\n", ga->player[nr].supporters_club.level,   ga->player[nr].supporters_club.time);
		printf("flood_lights      = %d, %d\n", ga->player[nr].flood_lights.level,      ga->player[nr].flood_lights.time);
		printf("scoreboard        = %d, %d\n", ga->player[nr].scoreboard.level,        ga->player[nr].scoreboard.time);
		printf("undersoil_heating = %d, %d\n", ga->player[nr].undersoil_heating.level, ga->player[nr].undersoil_heating.time);
		printf("changing_rooms    = %d, %d\n", ga->player[nr].changing_rooms.level,    ga->player[nr].changing_rooms.time);
		printf("gymnasium         = %d, %d\n", ga->player[nr].gymnasium.level,         ga->player[nr].gymnasium.time);
		printf("car_park          = %d, %d\n", ga->player[nr].car_park.level,          ga->player[nr].car_park.time);

		printf("safety rating     = ");
		for (int i = 0; i < sizeof( ga->player[nr].safety_rating ); ++i)
			printf("%02x ", ga->player[nr].safety_rating[i]);
		printf("\n");

		printf("seating_capacity[north] = %5d\n", ga->player[nr].seating_capacity[0]);
		printf("seating_capacity[east ] = %5d\n", ga->player[nr].seating_capacity[1]);
		printf("seating_capacity[south] = %5d\n", ga->player[nr].seating_capacity[2]);
		printf("seating_capacity[west ] = %5d\n", ga->player[nr].seating_capacity[3]);

		printf("Numb01: %5d\nNumb02: %5d\nNumb03: %5d\nNumb04: %5d\n",
			ga->player[nr].numb01, ga->player[nr].numb02,
			ga->player[nr].numb03, ga->player[nr].numb04);
		printf("Managerial rating.....:%3d\% (%+2d\%)\n"
		       "Directors confidence..:%3d\% (%+2d\%)\n"
		       "Supporters confidence.:%3d\% (%+2d\%)\n",
			ga->player[nr].managerial_rating_current,
			ga->player[nr].managerial_rating_current - ga->player[nr].managerial_rating_start,
			ga->player[nr].directors_confidence_current,
			ga->player[nr].directors_confidence_current - ga->player[nr].directors_confidence_start,
			ga->player[nr].supporters_confidence_current,
			ga->player[nr].supporters_confidence_current - ga->player[nr].supporters_confidence_start);


		printf("---- match data start ?----\n");

		for (int i = 0; i < sizeof( ga->player[nr].head6 ); ++i) {
			if ( i % 16 == 0 )
				printf("\n[%03d] ", i);
			printf("%02x ", ga->player[nr].head6[i]);
		}
		printf("\n");

		if ( ga->player[nr].player_idx1 == -1 )
			printf("NomPlayer1: %d ", ga->player[nr].player_idx1);
		else
			printf("NomPlayer1: (%04x) %12.12s",
				ga->player[nr].player_idx1,
				gamec.player[ ga->player[nr].player_idx1 ].name
			);

		for (int i = 0; i < sizeof( ga->player[nr].magic4 ); ++i) {
			if ( i % 16 == 0 )
				printf("\n[%03d] ", i);
			printf("%02x ", ga->player[nr].magic4[i]);
		}
		printf("\n");

		if ( ga->player[nr].player_idx2 == -1 )
			printf("NomPlayer2: %d ", ga->player[nr].player_idx2);
		else
			printf("NomPlayer2: (%04x) %12.12s",
				ga->player[nr].player_idx2,
				gamec.player[ ga->player[nr].player_idx2 ].name
			);

		for (int i = 0; i < sizeof( ga->player[nr].foot6 ); ++i) {
			if ( i % 16 == 0 )
				printf("\n[%03d] ", i);
			printf("%02x ", ga->player[nr].foot6[i]);
		}
		printf("\n");

/*
		printf("(%04x) %16.16s %d(%d)  (%04x) %16.16s %d(%d)\n",
			ga->player[nr].match[0].club,
			gameb.team[ ga->player[nr].match[0].club ].name,
			ga->player[nr].match[0].total_goals,
			ga->player[nr].match[0].first_half_goals,
			ga->player[nr].match[1].club,
			gameb.team[ ga->player[nr].match[1].club ].name,
			ga->player[nr].match[1].total_goals,
			ga->player[nr].match[1].first_half_goals
		);
*/		
		for (int i = 0; i < 2; ++i) {
			printf("---- team data ----\n");
			if ( ga->player[nr].match[i].club == -1 )
				printf("%d", ga->player[nr].match[i].club);
			else
				printf("%s: (%04x) %16.16s", i ? "Away" : "Home", ga->player[nr].match[i].club, gameb.team[ ga->player[nr].match[i].club ].name);

			printf(" Goals: %d(%d)\n",
				ga->player[nr].match[i].total_goals,
				ga->player[nr].match[i].first_half_goals
			);

			printf("Pattern:");
			for (int j = 0; j < sizeof( ga->player[nr].match[i].pattern6 ); ++j) {
				printf(" %02x", ga->player[nr].match[i].pattern6[j]);
			}
//			printf("\n");

			for (int j = 0; j < sizeof( ga->player[nr].match[i].match_data1 ); ++j) {
				if ( j % 16 == 0 )
					printf("\n[%03d] ", j);
				printf("%02x ", ga->player[nr].match[i].match_data1[j]);
			}
			printf("\n");

			printf("Corners...: %d\n", ga->player[nr].match[i].corners);
			printf("Throw ins.: %d\n", ga->player[nr].match[i].throw_ins);
			printf("Free kicks: %d\n", ga->player[nr].match[i].free_kicks);
			printf("Penalties.: %d\n", ga->player[nr].match[i].penalties);

			for (int j = 0; j < 14; ++j) {
				if ( ga->player[nr].match[i].lineup[j].player_idx == -1 )
					printf("lineup: %d ", ga->player[nr].match[i].lineup[j].player_idx);
				else
					printf("lineup: (%04x) %12.12s",
						ga->player[nr].match[i].lineup[j].player_idx,
						gamec.player[ ga->player[nr].match[i].lineup[j].player_idx].name
					);

				for (int k = 0; k < sizeof( ga->player[nr].match[i].lineup[j].data6 ); ++k) {
					printf(" %02x", ga->player[nr].match[i].lineup[j].data6[k]);
				}
				printf(" [%d]", ga->player[nr].match[i].lineup[j].red_card); // 4 = red, 1 = yellow?
				for (int k = 0; k < sizeof( ga->player[nr].match[i].lineup[j].data11 ); ++k) {
					printf(" %02x", ga->player[nr].match[i].lineup[j].data11[k]);
				}
				printf("\n");
			}

			for (int j = 0; j < 8; ++j) {
				if ( ga->player[nr].match[i].goal[j].player_idx == -1 )
					printf("goal: %d, magic: %d\n",
						ga->player[nr].match[i].goal[j].player_idx,
						ga->player[nr].match[i].goal[j].time);
				else
					printf("goal: (%04x) %12.12s, %2d:%02d\n",
						ga->player[nr].match[i].goal[j].player_idx,
						gamec.player[ ga->player[nr].match[i].goal[j].player_idx].name,
						ga->player[nr].match[i].goal[j].time / 60,
						ga->player[nr].match[i].goal[j].time % 60
					);
			}

			//assert(ga->player[nr].match[i].always_null == 0);
			printf("always_null: %04x\n", ga->player[nr].match[i].always_null);
			printf("Substitutions remaining: %d\n", ga->player[nr].match[i].substitutions_remaining);
			printf("other remaining: %d\n", ga->player[nr].match[i].other);
			assert(ga->player[nr].match[i].substitutions_remaining < 3);

			printf("Home/Away magic: %04x\n",
				ga->player[nr].match[i].home_away_data);

			if (ga->player[nr].match[i].club == 0x0062 && i == 0)
				assert(ga->player[nr].match[i].home_away_data == 0x5738);
			if (ga->player[nr].match[i].club == 0x0062 && i == 1)
				assert(ga->player[nr].match[i].home_away_data == 0x91f8);

			printf("---- /team data ----\n");
			printf("\n");

		}

		static const char *weather[] = {
			"", /* 00 */
			"icy", /* 01 */
			"", /* 02 */
			"", /* 03 */
			"", /* 04 */
			"", /* 05 */
			"heavy rain", /* 06 */
			"high winds", /* 07 */
			"cold & sunny", /* 08 */
			"cold & raining", /* 09 */
			"cold & cloudy", /* 0a */
			"cold & windy", /* 0b */
			"heavy rain", /* 0c */
			"high winds", /* 0d */
			"light rain", /* 0e */
			"overcast", /* 0f */
			"warm & raining", /* 10 */
			"warm & cloudy",  /* 11 */
			"raining", /* 12 */
			"windy & sunny", /* 13 */
			"light winds" /* 14 */
		};

		printf("Weather: (%04x) %s\n", ga->player[nr].weather, weather[ga->player[nr].weather]);

		if (ga->player[nr].referee == -1)
			printf("Referee: %d", ga->player[nr].referee);
		else
			printf("Referee: (%02x)%14.14s\n",
				ga->player[nr].referee,
				ga->referee[ ga->player[nr].referee ].name
			);

		for (int i = 0; i < sizeof( ga->player[nr].data156 ); ++i) {
			if ( i % 16 == 0 )
				printf("\n[%03d] ", i);
			printf("%02x ", ga->player[nr].data156[i]);
		}
		printf("\n");

		printf("Match type: (%02x)", ga->player[nr].match_type);

		for (int i = 0; i < sizeof( ga->player[nr].data157 ); ++i) {
			if ( i % 16 == 0 )
				printf("\n[%03d] ", i);
			printf("%02x ", ga->player[nr].data157[i]);
		}
		printf("\n");

		printf("audience %d\n", ga->player[nr].audience);

		for (int i = 0; i < sizeof( ga->player[nr].data158 ); ++i) {
			if ( i % 16 == 0 )
				printf("\n[%03d] ", i);
			printf("%02x ", ga->player[nr].data158[i]);
		}
		printf("\n\n");

		static const char *div[] = {
			"Prem.",
			"Div 1",
			"Div 2",
			"Div 3",
			"Conf."
		};

		printf("Year Div   (0000)Club             PS PL  W  D  L  GD PTS\n");
		for (int i = 0; i < 20; ++i) {
			if (ga->player[nr].league_history[i].year == 0)
				continue;
			printf(
				"%4d %5.5s (%04x)%16.16s %2d %2d %2d %2d %2d %3d %3d "
				"%02x %02x %02x %02x %02x %02x %02x %02x "
				"%02x %02x %02x %02x\n",
				ga->player[nr].league_history[i].year,
				div[ ga->player[nr].league_history[i].div ],
				ga->player[nr].league_history[i].club_idx,
				gameb.team[ ga->player[nr].league_history[i].club_idx ].name,
				ga->player[nr].league_history[i].ps,
				ga->player[nr].league_history[i].p,
				ga->player[nr].league_history[i].w,
				ga->player[nr].league_history[i].d,
				ga->player[nr].league_history[i].l,
				ga->player[nr].league_history[i].gd,
				ga->player[nr].league_history[i].pts,
				ga->player[nr].league_history[i].unk21,
				ga->player[nr].league_history[i].unk22,
				ga->player[nr].league_history[i].unk23,
				ga->player[nr].league_history[i].unk24,
				ga->player[nr].league_history[i].unk25,
				ga->player[nr].league_history[i].unk26,
				ga->player[nr].league_history[i].unk27,
				ga->player[nr].league_history[i].unk28,
				ga->player[nr].league_history[i].unk29,
				ga->player[nr].league_history[i].unk30,
				ga->player[nr].league_history[i].unk31,
				ga->player[nr].league_history[i].unk32);
		}

		static const char *match_type[] = {
			"Premier league",
			"Division one",
			"Division two",
			"Division three",
			"Conference",
			"F.A. cup",
			"League cup",
			"Champions cup",
			"Cup winners cup",
			"U.E.F.A. cup",
			"Charity shield"
		};

		printf("League titles  Won Yrs  Cup titles      Won Yrs\n");
		for (int i = 0; i < 5; ++i) {
			printf("%-14.14s %3d %3d  %-15.15s %3d %3d\n",
				match_type[i],
				ga->player[nr].titles[i].won,
				ga->player[nr].titles[i].yrs,

				match_type[5 + i],
				ga->player[nr].titles[5 + i].won,
				ga->player[nr].titles[5 + i].yrs
			);
		}
		printf("                        %-15.15s %3d %3d\n\n",
			match_type[10],
			ga->player[nr].titles[10].won,
			ga->player[nr].titles[10].yrs);

		printf("Match type       Play  Won Drew Lost   For   Agn\n");
		for (int i = 0; i < 11; ++i)
			printf("%-15.15s  %4d %4d %4d %4d  %4d  %4d\n",
				match_type[i],
				ga->player[nr].manager_history[i].play,
				ga->player[nr].manager_history[i].won,
				ga->player[nr].manager_history[i].drew,
				ga->player[nr].manager_history[i].lost,
				ga->player[nr].manager_history[i].forx,
				ga->player[nr].manager_history[i].agn);
		printf("\n");

		for (int i = 0; i < sizeof( ga->player[nr].data159 ); ++i) {
			if ( i % 16 == 0 )
				printf("\n[%03d] ", i);
			printf("%02x ", ga->player[nr].data159[i]);
		}
		printf("\n");

		printf("       Previous clubs   From To   Mngr Drct Sprt\n");
		for (int i = 0; i < 4; ++i) {
			printf("(%04x) %16.16s %4d %4d %3d%% %3d%% %3d%%\n",
				ga->player[nr].previous_clubs[i].club_idx,
				gameb.team[ga->player[nr].previous_clubs[i].club_idx].name,
				ga->player[nr].previous_clubs[i].year_from,
				ga->player[nr].previous_clubs[i].year_to,
				ga->player[nr].previous_clubs[i].mngr,
				ga->player[nr].previous_clubs[i].drct,
				ga->player[nr].previous_clubs[i].sprt
			);
		}

		printf("Current club start year: %4d\n", ga->player[nr].year_start_cur_club);

		printf("Manager of the month awards.%d\n",
			ga->player[nr].manager_of_the_month_awards);

		printf("Manager of the year awards..%d\n",
			ga->player[nr].manager_of_the_year_awards);

		for (int i = 0; i < 242; ++i)
			printf("(%04x)%16.16s %2d %2d %2d %2d %2d %2d %2d\n",
				ga->player[nr].match_history[i].team,
				gameb.team[ ga->player[nr].match_history[i].team ].name,
				ga->player[nr].match_history[i].played,
				ga->player[nr].match_history[i].won,
				ga->player[nr].match_history[i].u3,
				ga->player[nr].match_history[i].goals_f,
				ga->player[nr].match_history[i].u5,
				ga->player[nr].match_history[i].goals_a,
				ga->player[nr].match_history[i].u7);
		printf("\n");


		for (int i = 0; i < sizeof( ga->player[nr].data160 ); ++i) {
			if ( i % 16 == 0 )
				printf("\n[%03d] ", i);
			printf("%02x ", ga->player[nr].data160[i]);
		}
		printf("\n");

		for ( int i = 0; i < 8; ++i )
			printf("tactic[%d].name: %20.20s\n", i, ga->player[nr].tactic[i].name);
		printf("\n");

	}

	for (int i = 0; i < sizeof( ga->data200 ); ++i) {
		if ( i % 16 == 0 )
			printf("\n[%03d] ", i);
		printf("%02x ", ga->data200[i]);
	}
	printf("\n");
}

void dump_gameb(struct gameb *gb) {
	for (int i = 0; i < 244; ++i)
		dump_team(&gb->team[i]);
}

void dump_gamec(struct gamec *gc) {
	for (int i = 0; i < 3932; ++i)
		dump_player(&gc->player[i], i);

}

void dump_team(struct gameb::team *t) {
	printf("Team   : %16.16s\n", t->name);
	printf("Manager: %16.16s\n", t->manager);
	printf("Bank account: %d\n", t->bank_account);
	printf("Stadium: %24.24s\n", t->stadium);
	printf("Seating avg: %d\n", t->seating_avg);
	printf("Seating max: %d\n", t->seating_max);

	printf("\n---\n");
	for (int i = 0; i < sizeof(t->padding); ++i) {
		printf("%02x ", t->padding[i]);
	}
	printf("\n---\n");


	for (int i = 0; i < 24; ++i) {
		if ( t->player_index[i] == -1 )
			continue;

		printf("Player%02d: (%04x) %12.12s\n",
		i, t->player_index[i],
		gamec.player[ t->player_index[i] ].name );
	}
/*
		struct gamec::player * p = &(gamec.player[ t->player_index[i] ]);
		
	
		dump_player(p, t->player_index[i]);


		p->hn = 97;
		p->tk = 97;
		p->ps = 97;
		p->sh = 97;

		switch ( i ) {
			case 0:
			case 11:
				p->hn = 99; break;
			case 1:
			case 2:
			case 4:
			case 5:
			case 12:
				p->tk = 99; break;
			case 3:
			case 6:
			case 10:
			case 13:
				p->ps = 99; break;
			case 7:
			case 8:
			case 9:
			case 14:
				p->sh = 99; break;
		}

		p->hd = 99;
		p->cr = 99;
		p->ft = 99;
		p->aggr = 9;
		p->morl = 9;

		p->wage = 1000;
		p->contract = 5;

	}
*/

	for (int i = 0; i < sizeof( t->misc000 ); ++i) {
		if ( i % 16 == 0 )
			printf("\n[%3d]", i);
		printf("%02x ", t->misc000[i]);
	}
	printf("\n");


	static const char *day[] = { "mon", "wed", "sat" };
	static const char *match_type[] = {
		"0",
		"1", 
		"Division 2 match",
		"Division 3 match",
		"Conference match",
		"5",
		"6",
		"Division 2 delay",
		"Division 3 delay",
		"Conference delay",
		"F.A. cup match",
		"League cup match",
		"12",
		"Cup winners cup",
		"14",
		"Charity shield",
		"16",
		"17",
		"18",
		"Friendly",
		"20", "21", "22", "23", "24", "25",
		"26", "27", "28", "29", "30", "31"
	};

	enum game { home = 0, home_friendly = 1, away = 2, away_friendly = 3 };

/*
	for (int w = 0; w < 41; ++w) {
		for (int d = 0; d < 3; ++d) {
			if (t->timetable.week[w].day[d].team == 0xFF)
				printf("%02x %02x %02x - %s:%-2d None............ G ... ................\n",
					t->timetable.week[w].day[d].team,
					(uint8_t) t->timetable.week[w].day[d].result,
					t->timetable.week[w].day[d].b3,
					day[d], w+1);
*/
/*
			else if (t->timetable.week[w].day[d].result == -1)
				printf("%02x %02x %02x - %s:%-2d %-16.16s %x ... %16.16s\n",
					t->timetable.week[w].day[d].team,
					(uint8_t) t->timetable.week[w].day[d].result,
					t->timetable.week[w].day[d].b3,
					day[d], w+1,
					type[t->timetable.week[w].day[d].type],
					t->timetable.week[w].day[d].game,
					gameb.team[ t->timetable.week[w].day[d].team ].name);
*/
/*
			else
				printf("%02x %02x %02x - %s:%-2d %-16.16s %x %x-%x %16.16s\n",
					t->timetable.week[w].day[d].team,
					(uint8_t) t->timetable.week[w].day[d].result,
					t->timetable.week[w].day[d].b3,
					day[d], w+1,
					match_type[ t->timetable.week[w].day[d].type ],
					t->timetable.week[w].day[d].game,
					t->timetable.week[w].day[d].home,
					t->timetable.week[w].day[d].away,
					gameb.team[ t->timetable.week[w].day[d].team ].name);
		}
		printf("\n");
	}
*/
}

void dump_player(struct gamec::player *p, int32_t idx) {

	static const char *foot[] = { "Left", "Right", "Both" };
	static const char *train[] = {
		"None",
		"Handle",
		"Tackles",
		"Passes",
		"Shots",
		"Headers",
		"Control",
		"Fitness",
		"General"
	};
	static const char *intense[] = { "Low", "Medium", "Hard", "V.Hard" };

	printf("Player: (%04x) %12.12s %2d\n", idx, p->name, p->age);
/*
	printf("Wage: %5d\n", p->wage);
	printf("Insure: %d", p->ins); printf("%5d\n", p->ins_cost);
	printf("\n");
	printf("Handling : %2d\n", p->hn);
	printf("Tackling : %2d\n", p->tk);
	printf("Passing  : %2d\n", p->ps);
	printf("Shooting : %2d\n", p->sh);
	printf("Heading  : %2d\n", p->hd);
	printf("Control  : %2d\n", p->cr);
	printf("Fitness  : %2d\n", p->ft);
	printf("Aggr'sion: %2d\n", p->aggr);
	printf("Morale   : %2d\n", p->morl);
	printf("Foot     : %5.5s\n", foot[p->foot]);
	printf("\n");
	printf("Played  : %3d\n", p->played);
	printf("Scored  : %3d\n", p->scored);
	printf("Conceded: \n");
	printf("DPTS    :  %d\n", p->dpts);
	printf("Training : %7s, %6s\n", train[p->train], intense[p->intense]);
*/

	printf("%d year contract\n", p->contract);
	printf("%02x %02x %02x %02x %02x %02x %02x\n",
		p->u13, p->u15, p->u17, p->u19, p->u21, p->u23, p->u25);
	printf("%02x %02x %02x\n",
		p->unk2, p->unk4, p->unk5);

	printf("%d weeks\n\n", (p->inj_away + 3 - 1) / 3);
}
