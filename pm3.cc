#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pm3.h"

#define DEFAULT_MANAGER_NAME "J.Smith         "

struct gamea gamea;
struct gameb gameb;
struct gamec gamec;

void check_consistency() {
	int all[3932];
	for (int i = 0; i < 3932; ++i)
		all[i] = -1;

	for (int c = 0; c < CLUB_IDX_MAX; ++c) {
		fprintf(stderr, "Club[%3d]\n", c);
		for (int p = 0; p < 24; ++p) {
			if ( gameb.club[c].player_index[p] == -1 )
				continue;

			if (all[ gameb.club[c].player_index[p] ] == -1) {

				all[ gameb.club[c].player_index[p] ] = c;
				printf("Added %d %12.12s to %16.16s\n",
					gameb.club[c].player_index[p],
					gamec.player[    gameb.club[c].player_index[p] ].name,
					gameb.club[c].name);

			} else {
				printf("Duplicate. %4d %12.12s plays for\n"
					"%16.16s AND %16.16s\n",
					gameb.club[c].player_index[p],
					gamec.player[    gameb.club[c].player_index[p] ].name,
					gameb.club[ all[ gameb.club[c].player_index[p] ] ].name,
					gameb.club[c].name);
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

struct gameb::club& get_club(int idx) {
	return gameb.club[idx];
}

struct gamec::player& get_player(int16_t idx) {
	return gamec.player[idx];
}

const char* determine_player_type(struct gamec::player &p) {
	if (p.hn > p.tk && p.hn > p.ps && p.hn > p.sh) {
		return "G";
	} else if (p.tk > p.hn && p.tk > p.ps && p.tk > p.sh) {
		return "D";
	} else if (p.ps > p.hd && p.ps > p.tk && p.ps > p.sh) {
		return "M";
	}

	return "A";
}

void change_club(int new_club_idx, int player) {
	struct gamea::manager &manager = gamea.manager[player];
	int old_club_idx = manager.club_idx;
	manager.club_idx = new_club_idx;

	switch (manager.club_idx) {
		case 0 ... 21:
			manager.unk_number = 0;
			manager.stadium.ground_facilities.level = 3;
			manager.stadium.supporters_club.level = 3;
			manager.stadium.flood_lights.level = 2;
			manager.stadium.scoreboard.level = 3;
			manager.stadium.undersoil_heating.level = 1;
			manager.stadium.changing_rooms.level = 2;
			manager.stadium.gymnasium.level = 3;
			manager.stadium.car_park.level = 2;

			for (int i = 0; i < sizeof (manager.stadium.safety_rating); ++i) {
				manager.stadium.safety_rating[i] = 4;
			}

			for (int i = 0; i < 4; ++i) {
				manager.stadium.capacity[i].seating = 10000;
				manager.stadium.capacity[i].terraces = 0;
				manager.stadium.conversion[i].level= 2;
				manager.stadium.area_covering[i].level= 3;
			}

			manager.price.league_match_seating = 15;
			manager.price.league_match_terrace = 13;
			manager.price.cup_match_seating = 18;
			manager.price.cup_match_terrace = 15;

			break;
		case 22 ... 45:
			manager.unk_number = 1;
			manager.stadium.ground_facilities.level = 2;
			manager.stadium.supporters_club.level = 2;
			manager.stadium.flood_lights.level = 2;
			manager.stadium.scoreboard.level = 2;
			manager.stadium.undersoil_heating.level = 1;
			manager.stadium.changing_rooms.level = 2;
			manager.stadium.gymnasium.level = 2;
			manager.stadium.car_park.level = 2;

			for (int i = 0; i < sizeof (manager.stadium.safety_rating); ++i) {
				manager.stadium.safety_rating[i] = 3;
			}

			for (int i = 0; i < 4; ++i) {
				manager.stadium.capacity[i].seating = 5000;
				manager.stadium.capacity[i].terraces = 0;
				manager.stadium.conversion[i].level = 2;
				manager.stadium.area_covering[i].level = 2;
			}

			manager.price.league_match_seating = 13;
			manager.price.league_match_terrace = 11;
			manager.price.cup_match_seating = 16;
			manager.price.cup_match_terrace = 13;

			break;
		case 46 ... 69:
			manager.unk_number = 2;
			manager.stadium.ground_facilities.level = 2;
			manager.stadium.supporters_club.level = 2;
			manager.stadium.flood_lights.level = 1;
			manager.stadium.scoreboard.level = 2;
			manager.stadium.undersoil_heating.level = 0;
			manager.stadium.changing_rooms.level = 1;
			manager.stadium.gymnasium.level = 2;
			manager.stadium.car_park.level = 1;

			for (int i = 0; i < sizeof (manager.stadium.safety_rating); ++i) {
				manager.stadium.safety_rating[i] = 2;
			}

			for (int i = 0; i < 4; ++i) {
				manager.stadium.capacity[i].seating = 2500;
				manager.stadium.capacity[i].terraces = 0;
				manager.stadium.conversion[i].level = 1;
				manager.stadium.area_covering[i].level = 1;
			}

			manager.price.league_match_seating = 11;
			manager.price.league_match_terrace = 9;
			manager.price.cup_match_seating = 14;
			manager.price.cup_match_terrace = 11;

			break;
		case 70 ... 91:
			manager.unk_number = 3;
			manager.stadium.ground_facilities.level = 1;
			manager.stadium.supporters_club.level = 1;
			manager.stadium.flood_lights.level = 1;
			manager.stadium.scoreboard.level = 1;
			manager.stadium.undersoil_heating.level = 0;
			manager.stadium.changing_rooms.level = 1;
			manager.stadium.gymnasium.level = 1;
			manager.stadium.car_park.level = 1;

			for (int i = 0; i < sizeof (manager.stadium.safety_rating); ++i) {
				manager.stadium.safety_rating[i] = 1;
			}

			for (int i = 0; i < 4; ++i) {
				manager.stadium.capacity[i].seating = 1000;
				manager.stadium.capacity[i].terraces = 1;
				manager.stadium.conversion[i].level = 0;
				manager.stadium.area_covering[i].level = 0;
			}

			manager.price.league_match_seating = 9;
			manager.price.league_match_terrace = 7;
			manager.price.cup_match_seating = 12;
			manager.price.cup_match_terrace = 9;

			break;
		case 92 ... 113:
			manager.unk_number = 4;
			manager.stadium.ground_facilities.level = 1;
			manager.stadium.supporters_club.level = 1;
			manager.stadium.flood_lights.level = 0;
			manager.stadium.scoreboard.level = 1;
			manager.stadium.undersoil_heating.level = 0;
			manager.stadium.changing_rooms.level = 0;
			manager.stadium.gymnasium.level = 1;
			manager.stadium.car_park.level = 0;

			for (int i = 0; i < sizeof (manager.stadium.safety_rating); ++i) {
				manager.stadium.safety_rating[i] = 0;
			}

			for (int i = 0; i < 4; ++i) {
				manager.stadium.capacity[i].seating = 500;
				manager.stadium.capacity[i].terraces = 1;
				manager.stadium.conversion[i].level = 0;
				manager.stadium.area_covering[i].level = 0;
			}

			manager.price.league_match_seating = 7;
			manager.price.league_match_terrace = 5;
			manager.price.cup_match_seating = 10;
			manager.price.cup_match_terrace = 7;

			break;
		default:
			fprintf(stderr, "Invalid Club index (%i)\n", new_club_idx);
			exit(EXIT_FAILURE);
	}

	strncpy(gameb.club[new_club_idx].manager, gameb.club[old_club_idx].manager, 16);
	strncpy(gameb.club[old_club_idx].manager, DEFAULT_MANAGER_NAME, 16);
}

void soup_up(int player) {

	struct gamea::manager &manager = gamea.manager[player];

	for (int i = 0; i < 20; ++i) {
		struct gamea::manager::employee &employee = manager.employee[i];
		printf("Employee: %14.14s\n", employee.name);
		employee.skill = 99;
		//employee.age = i % 16;
	}

	struct gameb::club &club = gameb.club[ manager.club_idx ];

	for (int p = 0; p < 24; ++p) {
		if (club.player_index[p] == -1)
			continue;

		struct gamec::player &player = gamec.player[ club.player_index[p] ];

		player.hn = 97;
		player.tk = 97;
		player.ps = 97;
		player.sh = 97;

		switch ( p ) {
			case  0:
			case 11:
			case 15:
				player.hn = 99; break;

			case  1:
			case  2:
			case  4:
			case  5:
			case 12:
			case 16:
			case 19:
			case 22:
				player.tk = 99; break;

			case  3:
			case 10:
			case 13:
			case 17:
			case 20:
				player.ps = 99; break;

			case  6:
			case  7:
			case  8:
			case  9:
			case 14:
			case 18:
			case 21:
			case 23:
				player.sh = 99; break;

			default: break;
		}

		player.hd = 99;
		player.cr = 99;
		player.ft = 99;

		player.morl = 8;
	}
}
