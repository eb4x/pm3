#include <cassert>
#include <getopt.h>
#include <cstdio>
#include <cstdlib>
#include "pm3/pm3.hh"

void dump_gamea();

void dump_gamea_manager(int player = 0);

void dump_gamea_match_summary();

void fax_match_summary();

void dump_gameb();

void dump_club(struct gameb::club &club);

void print_club_name(int16_t idx, bool newline = true);

void dump_gamec();

void dump_player(struct gamec::player &player);

void print_player_name(int16_t idx, bool newline = true);

void print_player_row(struct club_player &club_player);

void print_player_row(struct gamec::player &p, struct gameb::club &club);

void print_player_row_header();

void soup_up(int player = 0);

void dump_free_players();

pm3_game_type game_type;

void print_help(char *command) {
    fprintf(stderr, "Usage: %s -[abc] -g 1-8 [-f] [-t 0-113] [-l] [-s] [-h] /path/to/pm3/\n", command);
    fprintf(stderr, "\n");
    fprintf(stderr, "  -[abc]\n");
    fprintf(stderr, "    Dump game[abc]\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "  -g 1-8, --game=1-8\n");
    fprintf(stderr, "    Which savegame to work on\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "  --club[=0..243]\n");
    fprintf(stderr, "    Dump information on a single club within a savegame\n");
    fprintf(stderr, "      (defaults to the club of player0, if index not provided)\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "  -f\n");
    fprintf(stderr, "    Print out free players\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "  -t 0-113\n");
    fprintf(stderr, "    Change starting team to team ID\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "  -l\n");
    fprintf(stderr, "    Level aggression to 5 for all players in all teams\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "  -s\n");
    fprintf(stderr, "    Maximize all values for team\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "  -h\n");
    fprintf(stderr, "    Displays this help message\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "  /path/to/pm3/\n");
    fprintf(stderr, "    Path to PM3\n");
}

int main(int argc, char *argv[]) {
    int c, optindex = 0;
    int help = 0;
    int opt_dump_gamea = 0,
        opt_dump_gameb = 0,
        opt_dump_gamec = 0,
        opt_dump_free_players = 0,
        opt_level_aggression = 0,
        opt_verbose = 0;

    char *game_path = nullptr;
    int game_nr = -1, opt_soup_up = 0;
    int opt_new_club_idx = -1;
    int opt_club_idx = -2;

    static struct option long_options[] = {
            { "club",            optional_argument, &opt_club_idx, -1 },
            {"game",             required_argument, nullptr, 'g'},
            {"help",             no_argument,       nullptr, 'h'},
            {"team",             no_argument,       nullptr, 't'},
            {"level-aggression", no_argument,       nullptr, 'l'},
            {"soup-up",          no_argument,       nullptr, 's'},
            {"verbose",          no_argument,       nullptr, 'v'},
            {nullptr, 0,                            nullptr, 0}
    };

    while ((c = getopt_long(argc, argv, "abcfg:t:hsv", long_options, &optindex)) != -1) {
        switch (c) {
            case 0: // Long-options only
                if (0 == strcmp(long_options[optindex].name, "club") && optarg) {
                    opt_club_idx = atoi(optarg);
                    if (opt_club_idx < 0 || opt_club_idx >= CLUB_IDX_MAX) {
                        fprintf(stderr, "Invalid club index: %d\n", opt_club_idx);
                        print_help(argv[0]);
                        return EXIT_FAILURE;
                    }
                }
                break;
            case 'a': opt_dump_gamea = 1; break;
            case 'b': opt_dump_gameb = 1; break;
            case 'c': opt_dump_gamec = 1; break;
            case 'f': opt_dump_free_players = 1; break;
            case 'g':
                game_nr = atoi(optarg);
                if (game_nr < 1 || game_nr > 8) {
                    fprintf(stderr, "Invalid savegame number: %d\n", game_nr);
                    print_help(argv[0]);
                    return EXIT_FAILURE;
                }
                break;
            case 't':
                opt_new_club_idx = atoi(optarg);
                if (opt_new_club_idx < 0 || opt_new_club_idx >= 114) {
                    fprintf(stderr, "Invalid new club index: %d\n", opt_new_club_idx);
                    print_help(argv[0]);
                    return EXIT_FAILURE;
                }
                break;
            case 'h': help = 1;        break;
            case 'l': opt_level_aggression = 1; break;
            case 's': opt_soup_up = 1; break;
            case 'v': opt_verbose = 1; break;
            default:
                break;
        }
    }

    if (optind < argc) {
        game_path = argv[optind];
    } else {
        fprintf(stderr, "No game path provided\n");
        print_help(argv[0]);
        return EXIT_FAILURE;
    }

    if (help || argc == 1) {
        print_help(argv[0]);
        return EXIT_SUCCESS;
    }

    game_type = get_pm3_game_type(game_path);

    if (game_type == PM3_UNKNOWN) {
        fprintf(stderr, "Did not find %s or %s in %s\n", EXE_STANDARD_FILENAME, EXE_DELUXE_FILENAME, game_path);
        exit(EXIT_FAILURE);
    }

    if (opt_verbose) {
        fprintf(stderr, "sizeof (gamea)        = 0x%0zx\n", sizeof(struct gamea));
        fprintf(stderr, "sizeof (gameb.club)   = 0x%0zx\n", sizeof(struct gameb::club));
        fprintf(stderr, "sizeof (gamec.player) = 0x%0zx\n", sizeof(struct gamec::player));
    }

	assert(sizeof (struct gamea)         == 0x7372);
	assert(sizeof (struct gameb::club)   == 0x023A);
	assert(sizeof (struct gamec::player) == 0x0028);

    load_metadata(game_path);
    load_binaries(game_nr, game_path);

    if (opt_dump_gamea) {
        printf("GAME%dA\n", game_nr);
        dump_gamea();
    }

    if (opt_dump_gameb) {
        printf("GAME%dB\n", game_nr);
        dump_gameb();
    }

    if (opt_club_idx != -2) {
        if (opt_club_idx == -1)
            opt_club_idx = gamea.manager[0].club_idx;

        struct gameb::club &club = get_club(opt_club_idx);
        dump_club(club);
    }

    if (opt_dump_gamec) {
        printf("GAME%dC\n", game_nr);
        dump_gamec();
    }

    if (opt_dump_free_players) {
        printf("FREE PLAYERS\n");
        dump_free_players();
    }

    if (opt_level_aggression) {
        level_aggression();
        save_binaries(game_nr, game_path);
    }

    if (opt_soup_up) {
        soup_up();
        save_binaries(game_nr, game_path);
    }

    if (opt_new_club_idx != -1) {
        change_club(opt_new_club_idx, game_path);
        save_binaries(game_nr, game_path);
        update_metadata(game_nr);
        save_metadata(game_path);
    }

    return EXIT_SUCCESS;
}

void dump_gamea() {

    int correction = 0;
    for (int i = 0; i < 118; ++i) {
        switch (i) {
            case 0:
                correction = 0;
                printf("Premier league clubs\n");
                break;
            case 22:
                correction = 22;
                printf("\nDivision 1 clubs\n");
                break;
            case 46:
                correction = 46;
                printf("\nDivision 2 clubs\n");
                break;
            case 70:
                correction = 70;
                printf("\nDivision 3 clubs\n");
                break;
            case 92:
                correction = 92;
                printf("\nConference league clubs\n");
                break;
            case 114:
                correction = 114;
                printf("\nMisc clubs\n");
                break;
            default:
                break;
        }

        printf("%2d (%04x) %16.16s\n", i + 1 - correction,
               gamea.club_index.all[i],
               gameb.club[gamea.club_index.all[i]].name);
    }
    printf("\n");

    for (int i = 0; i < 114; ++i) {
        switch (i) {
            case 0:
                correction = 0;
                printf("Premier league home/away table\n");
                printf("Club              W  D  L  F  A   W  D  L  F  A\n");
                break;
            case 22:
                correction = 22;
                printf("\nDivision 1 home/away table\n");
                printf("Club              W  D  L  F  A   W  D  L  F  A\n");
                break;
            case 46:
                correction = 46;
                printf("\nDivision 2 home/away table\n");
                printf("Club              W  D  L  F  A   W  D  L  F  A\n");
                break;
            case 70:
                correction = 70;
                printf("\nDivision 3 home/away table\n");
                printf("Club              W  D  L  F  A   W  D  L  F  A\n");
                break;
            case 92:
                correction = 92;
                printf("\nConference league home/away table\n");
                printf("Club              W  D  L  F  A   W  D  L  F  A\n");
                break;
            default:
                break;
        }


        printf("%16.16s", gameb.club[gamea.table.all[i].club_idx].name);
        printf(" %2d %2d %2d %2d %2d  %2d %2d %2d %2d %2d, (%02x %02x %02x)\n",
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
               gamea.table.all[i].hx, gamea.table.all[i].ax, gamea.table.all[i].xx);
    }

    printf("\n");
    printf("data000: (0x%04x): %d\n", gamea.data000, gamea.data000);
    printf("data001: (0x%04x): %d\n", gamea.data001, gamea.data001);
    printf("data002: (0x%08x): %d\n", gamea.data002, gamea.data002);
    assert(gamea.data002 < 65536); // just remind me that this could be two 16bits.
    printf("\n");

    for (int i = 0; i < 75; ++i) {
        switch (i) {
            case 0:
                correction = 0;
                printf("Premier league top scorers\n");
                printf("Player       Rating       Club             PL SC\n");
                break;
            case 15:
                correction = 15;
                printf("\nDivision 1 top scorers\n");
                printf("Player       Rating       Club             PL SC\n");
                break;
            case 30:
                correction = 30;
                printf("\nDivision 2 top scorers\n");
                printf("Player       Rating       Club             PL SC\n");
                break;
            case 45:
                correction = 45;
                printf("\nDivision 3 top scorers\n");
                printf("Player       Rating       Club             PL SC\n");
                break;
            case 60:
                correction = 60;
                printf("\nConference league top scorers\n");
                printf("Player       Rating       Club             PL SC\n");
                break;
            default:
                break;
        }

        if (gamea.top_scorers.all[i].player_idx == -1)
            printf("skip\n");
        else
            printf("%12.12s %12.12s %16.16s %2d %2d\n",
                   gamec.player[gamea.top_scorers.all[i].player_idx].name, "",
                   gameb.club[gamea.top_scorers.all[i].club_idx].name,
                   gamea.top_scorers.all[i].pl, gamea.top_scorers.all[i].sc
            );
    }
    printf("\n");

    printf("Sorted numbers\n");
    for (int i = 0; i < 64; ++i) {
        printf("[%2d] %04x %16.16s\n", i, gamea.sorted_numbers[i], gameb.club[gamea.sorted_numbers[i]].name);
    }
    printf("\n");

    for (int i = 0; i < 64; ++i) {
        struct gamea::referee &referee = gamea.referee[i];
        printf("Referee: (%2d) %14.14s - %d : %d ",
               i, referee.name, 40 + referee.age, referee.magic);

        for (int j = 0; j < sizeof(referee.var); ++j)
            printf(" %02x", referee.var[j]);
        printf("\n");
    }
    printf("\n");

    for (int i = 0; i < 149; ++i) {
        switch (i) {
            case 0:
                printf("the f.a. cup\n");
                break;
            case 36:
                printf("the league cup\n");
                break;
            case 64:
                printf("data090\n");
                break;
            case 68:
                printf("the champions cup\n");
                break;
            case 84:
                printf("data091\n");
                break;
            case 100:
                printf("the cup winners cup\n");
                break;
            case 116:
                printf("the u.e.f.a. cup\n");
                break;
            case 148:
                printf("the charity sheld\n");
                break;
        }

        struct gamea::cuppy::cup_entry &cup_entry = gamea.cuppy.all[i];

        if (cup_entry.club[0].idx == -1 || cup_entry.club[1].idx == -1 ||
            cup_entry.club[0].idx >= 245 || cup_entry.club[1].idx >= 245) {
            printf("XXX: idx: %d, goals: %d, audience: %d - idx: %d, goals: %d, audience: %d\n",
                   cup_entry.club[0].idx, cup_entry.club[0].goals, cup_entry.club[0].audience,
                   cup_entry.club[1].idx, cup_entry.club[1].goals, cup_entry.club[1].audience);
            continue;
        }

        struct gameb::club &home_club = get_club(cup_entry.club[0].idx);
        struct gameb::club &away_club = get_club(cup_entry.club[1].idx);

        printf("%3.3s:%16.16s - %3.3s:%16.16s\nat %24.24s\n",
               "XXX", home_club.name,
               "XXX", away_club.name,
               home_club.stadium);
    }

/*
	printf(" idx, club, goals, home_supporters, total_supporters, away_supporters, goals, idx club, \n");
	for (int i = 0; i < 149; ++i) {
		if ( gamea.cuppy.all[i].club[0].idx == -1 || gamea.cuppy.all[i].club[1].idx == -1 ||
		     gamea.cuppy.all[i].club[0].idx > CLUB_IDX_MAX || gamea.cuppy.all[i].club[1].idx > CLUB_IDX_MAX ){
			printf("cuppy.all[%3d]: %04x %d %5d (%5d) %5d %d %04x\n", i,
				gamea.cuppy.all[i].club[0].idx, gamea.cuppy.all[i].club[0].goals, gamea.cuppy.all[i].club[0].audience,
				0,
				gamea.cuppy.all[i].club[1].audience, gamea.cuppy.all[i].club[1].goals, gamea.cuppy.all[i].club[1].idx
			);
			continue;
		}

		printf("cuppy.all[%3d]: (%04x) %16.16s %3d %5d (%5d) %5d %3d (%04x) %16.16s\n", i,
			gamea.cuppy.all[i].club[0].idx, gameb.club[ gamea.cuppy.all[i].club[0].idx ].name,
			gamea.cuppy.all[i].club[0].goals,           gamea.cuppy.all[i].club[0].audience,
			gamea.cuppy.all[i].club[0].audience +       gamea.cuppy.all[i].club[1].audience,
			gamea.cuppy.all[i].club[1].audience,        gamea.cuppy.all[i].club[1].goals,
			gamea.cuppy.all[i].club[1].idx, gameb.club[ gamea.cuppy.all[i].club[1].idx ].name
		);

	}
*/
    printf("\n--data095-- (i'm guessing cup turns are in here, mon week 7 = ~14-17)");
    for (int i = 0; i < sizeof(gamea.data095); ++i) {
        if (i % 16 == 0)
            printf("\n[%04d]", i);
        printf(" %02x", gamea.data095[i]);
    }
    printf("\n");

    printf("The charity shield history: (%04x) %16.16s : (%04x) %16.16s\n",
           gamea.the_charity_shield_history.club[0].idx, gameb.club[gamea.the_charity_shield_history.club[0].idx].name,
           gamea.the_charity_shield_history.club[1].idx, gameb.club[gamea.the_charity_shield_history.club[1].idx].name
    );
    printf("                             %5d %5d : %5d %5d\n",
           gamea.the_charity_shield_history.club[0].goals, gamea.the_charity_shield_history.club[0].audience,
           gamea.the_charity_shield_history.club[1].goals, gamea.the_charity_shield_history.club[1].audience
    );

    printf("\n--- some table ---\n");
    for (int i = 0; i < 11; ++i) {
        printf("(%04x) %16.16s %d %5d" " (%5d) "
               "%5d %d (%04x) %16.16s\n",
               gamea.some_table[i].club1_idx,
               gameb.club[gamea.some_table[i].club1_idx].name,
               gamea.some_table[i].club1_goals,
               gamea.some_table[i].club1_audience,
               gamea.some_table[i].club1_audience + gamea.some_table[i].club2_audience,
               gamea.some_table[i].club2_audience,
               gamea.some_table[i].club2_goals,
               gamea.some_table[i].club2_idx,
               gameb.club[gamea.some_table[i].club2_idx].name);
    }
    printf("\n");

    printf("Last results\n");
    for (int i = 0; i < 47; ++i) {
        if (gamea.last_results.all[i].club[0].idx == 0 && gamea.last_results.all[i].club[1].idx == 0) {
            printf("empty\n");
            continue;
        }
        printf("(%04x) %16.16s %d %5d (%5d) %5d %d (%04x) %16.16s\n",
               gamea.last_results.all[i].club[0].idx, gameb.club[gamea.last_results.all[i].club[0].idx].name,
               gamea.last_results.all[i].club[0].goals, gamea.last_results.all[i].club[0].audience,
               gamea.last_results.all[i].club[0].audience + gamea.last_results.all[i].club[1].audience,
               gamea.last_results.all[i].club[1].audience, gamea.last_results.all[i].club[1].goals,
               gamea.last_results.all[i].club[1].idx, gameb.club[gamea.last_results.all[i].club[1].idx].name
        );
    }
    printf("\n");

    for (int lg = 0; lg < 5; ++lg) {
        printf("Previous %s champions\n", division[lg]);
        for (int h = 0; h < 20; ++h) {
            if (gamea.league[lg].history[h].year == 0)
                continue;
            printf("%4d: (%04x) %16.16s",
                   gamea.league[lg].history[h].year,
                   gamea.league[lg].history[h].club_idx, gameb.club[gamea.league[lg].history[h].club_idx].name
            );

            for (int i = 0; i < sizeof(gamea.league[lg].history[h].data); ++i) {
                printf(" %02x", gamea.league[lg].history[h].data[i]);
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

    static const char *club_type_short[] = {
            "000",
            "ITA", //1
            "GER", //2
            "SPA", //3
            "HOL", //4
            "005",
            "RUS", //6
            "SCO", //7
            "BEL", //8
            "009",
            "010",
            "011",
            "012",
            "013",
            "014",
            "015",
            "016",
            "017",
            "018",
            "019",
            "PRM", //20
            "DV1", //21
            "DV2", //22
            "DV3", //23
            "CNF", //24
            "25",
            "26",
            "27",
            "28",
            "29",
            "30",
            "31",
            "PRM", //32
            "DV1", //33
            "DV2", //34
            "DV3", //35
            "CNF", //36
    };

    for (int cp = 0; cp < 6; ++cp) {
        printf("Previous %s finals\n", cup[cp]);
        for (int h = 0; h < 20; ++h) {
            if (gamea.cup[cp].history[h].year == 0)
                continue;

            printf("%4d: (%04x) %3.3s:%16.16s",
                   gamea.cup[cp].history[h].year,
                   gamea.cup[cp].history[h].club_idx_winner,
                   club_type_short[gamea.cup[cp].history[h].type_winner],
                   gameb.club[gamea.cup[cp].history[h].club_idx_winner].name
            );

            printf(" (%04x) %3.3s:%16.16s",
                   gamea.cup[cp].history[h].club_idx_runner_up,
                   club_type_short[gamea.cup[cp].history[h].type_runner_up],
                   gameb.club[gamea.cup[cp].history[h].club_idx_runner_up].name
            );
            printf(" %d %d", gamea.cup[cp].history[h].type_winner, gamea.cup[cp].history[h].type_runner_up);
            printf("\n");
        }
        printf("\n");
    }

    printf("Fixtures\n");
    for (int i = 0; i < 20; ++i) {
        printf("%2d: (%04x) %16.16s - (%04x) %16.16s\n", i,
               gamea.fixture[i].club_idx1, gameb.club[gamea.fixture[i].club_idx1].name,
               gamea.fixture[i].club_idx2, gameb.club[gamea.fixture[i].club_idx2].name
        );
    }
    printf("\n");

    printf("data100");
    for (int i = 0; i < sizeof(gamea.data100); ++i) {
        if (i % 16 == 0)
            printf("\n[%4d] ", i);
        printf("%02x ", gamea.data100[i]);
    }
    printf("\n");

    printf("--- transfer market ---\n");
    print_player_row_header();
    for (int i = 0; i < 45; ++i) {
        if (gamea.transfer_market[i].player_idx != -1) {
            struct gameb::club &club = get_club(gamea.transfer_market[i].club_idx);
            struct gamec::player &p = gamec.player[gamea.transfer_market[i].player_idx];
            print_player_row(p, club);
        }
        printf("\n");
    }

    printf("data10z");
    for (int i = 0; i < sizeof(gamea.data10z); ++i) {
        if (i % 16 == 0)
            printf("\n[%4d] ", i);
        printf("%02x ", gamea.data10z[i]);
    }
    printf("\n");

    printf("--- Transfer list ---\n");
    for (int i = 0; i < 6; ++i) {
        if (gamea.transfer[i].player_idx == -1)
            continue;

        printf("%12.12s was transferred from %16.16s\n"
               "to %16.16s for a fee of £%d\n",
               gamec.player[gamea.transfer[i].player_idx].name,
               gameb.club[gamea.transfer[i].from_club_idx].name,
               gameb.club[gamea.transfer[i].to_club_idx].name,
               gamea.transfer[i].fee);
    }

    for (int i = 0; i < sizeof(gamea.data101); ++i) {
        if (i % 16 == 0)
            printf("\n[%4d] ", i);
        printf("%02x ", gamea.data101[i]);
    }
    printf("\n");

    if (gamea.retired_manager_club_idx != -1) {
        printf("%16.16s has retired from (%04x) %16.16s\n",
               gamea.manager_name,
               gamea.retired_manager_club_idx,
               gameb.club[gamea.retired_manager_club_idx].name);
    }

    if (gamea.new_manager_club_idx != -1) {
        printf("%16.16s has become the new manager of\n(%04x) %16.16s\n",
               gameb.club[gamea.new_manager_club_idx].manager,
               gamea.new_manager_club_idx,
               gameb.club[gamea.new_manager_club_idx].name);
    }

    for (int i = 0; i < sizeof(gamea.data10w); ++i) {
        if (i % 16 == 0)
            printf("\n[%4d] ", i);
        printf("%02x ", gamea.data10w[i]);
    }
    printf("\n");

    printf("Year: %4d, Week: %2d, Day: %3.3s (turn: %3d)\n",
           gamea.year, (gamea.turn / 3) + 1, day[gamea.turn % 3], gamea.turn);

    for (int i = 0; i < sizeof(gamea.data10x); ++i) {
        printf("(%04x) %d", gamea.data10x[i], gamea.data10x[i]);

        switch (i) {
            case 10:
                printf(" cup matches");
        }

        printf("\n");
    }

    dump_gamea_manager(); // XXX don't care about second player

    for (int i = 0; i < sizeof(gamea.data200); ++i) {
        if (i % 16 == 0)
            printf("\n[%03d] ", i);
        printf("%02x ", gamea.data200[i]);
    }
    printf("\n");

    printf("inc_number1: %d\n", gamea.inc_number1);
    printf("inc_number2: %d\n", gamea.inc_number2);
    printf("inc_number3: %d\n", gamea.inc_number3);

}

void dump_gamea_manager(int player) {
    struct gamea::manager &manager = gamea.manager[player];
    printf("Manager: %16.16s\n", manager.name);

    // ONCE
    struct gameb::club &club = gameb.club[manager.club_idx];
    printf("Club: %16.16s\n", club.name);

    printf("League: %s\n", division[manager.division]);
    printf("Contract: %d\n", manager.contract_length);
    printf("League match: Seating..£%-2d\n"
           "League match: Terraces.£%-2d\n"
           "Cup match: Seating.....£%-2d\n"
           "Cup match: Terraces....£%-2d\n",
           manager.price.league_match_seating,
           manager.price.league_match_terrace,
           manager.price.cup_match_seating,
           manager.price.cup_match_terrace);

    for (int i = 0; i < 23; ++i) {
        printf("Seating%02d: %6d\n", i,
               manager.seating_history[i]);
    }

    for (int i = 0; i < 23; ++i) {
        printf("Terrace%02d: %6d\n", i,
               manager.terrace_history[i]);
    }


    for (int i = 0; i < 2; ++i) {
        if (i == 0)
            printf("daily bank statement\n");
        if (i == 1)
            printf("yearly bank statement\n");

        enum {
            DEBIT = 0, CREDIT = 1
        };
        struct gamea::manager::bank_statement &bs = manager.bank_statement[i];
        printf("gate receipts       = %8d %8d\n", bs.gate_receipts[0], bs.gate_receipts[1]);
        printf("club wages          = %8d %8d\n", bs.club_wages[0], bs.club_wages[1]);
        printf("transfer fees       = %8d %8d\n", bs.transfer_fees[0], bs.transfer_fees[1]);
        printf("club fines          = %8d %8d\n", bs.club_fines[0], bs.club_fines[1]);
        printf("grants for club     = %8d %8d\n", bs.grants_for_club[0], bs.grants_for_club[1]);
        printf("club bills          = %8d %8d\n", bs.club_bills[0], bs.club_bills[1]);
        printf("miscellaneous sales = %8d %8d\n", bs.miscellaneous_sales[0], bs.miscellaneous_sales[1]);
        printf("bank loan payments  = %8d %8d\n", bs.bank_loan_payments[0], bs.bank_loan_payments[1]);
        printf("ground improvements = %8d %8d\n", bs.ground_improvements[0], bs.ground_improvements[1]);
        printf("advertising boards  = %8d %8d\n", bs.advertising_boards[0], bs.advertising_boards[1]);
        printf("other items         = %8d %8d\n", bs.other_items[0], bs.other_items[1]);
        printf("account interest    = %8d %8d\n", bs.account_interest[0], bs.account_interest[1]);
        printf("\n");
    }

    for (int i = 0; i < 4; ++i) {
        struct gamea::manager::loan &loan = manager.loan[i];

        printf("Loan %d:£%-6d, due %d year%s %d turn%s\n",
               i + 1, loan.amount,
               loan.year, loan.year == 1 ? "" : "s",
               loan.turn, loan.turn == 1 ? "" : "s");
    }
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

    static const char *rating[] = {
            "Fair *",       //  0 -  4
            "Fair **",      //  5 -  9
            "Fair ***",     // 10 - 14
            "Fair ****",    // 15 - 19
            "Fair *****",   // 20 - 24
            "Good *",       // 25 - 29
            "Good **",      // 30 - 34
            "Good ***",     // 35 - 39
            "Good ****",    // 40 - 44
            "Good *****",   // 45 - 49
            "V.Good *",     // 50 - 54
            "V.Good **",    // 55 - 59
            "V.Good ***",   // 60 - 64
            "V.Good ****",  // 65 - 69
            "V.Good *****", // 70 - 74
            "Superb",       // 75 - 79
            "Outstanding",  // 80 - 84
            "World class",  // 85 - 89
            "Exceptional",  // 90 - 94
            "The ultimate", // 95 - 99
    };

    printf("Your employees Type       Rating       Wage  Ag\n");
    for (int i = 0; i < 20; ++i) {
        struct gamea::manager::employee &employee = manager.employee[i];

        if (i == 12)
            printf("\nVacancies      Type       Rating       Wage  Ag\n");

        printf("%14.14s %10.10s %-12.12s %5d %2d\n",
               employee.name,
               type[employee.type],
               rating[(employee.skill - (employee.skill % 5)) / 5],
               employee.skill, // needs to be a formula
               40 + employee.age);
    }

    static const char *nyn[] = {"N/A", "Yes", "No"};
    struct gamea::manager::assistant_manager &am = manager.assistant_manager;
    printf("Do training schedules.......: %s\n"
           "Treat injured players.......: %s\n"
           "Check sponsors boards.......: %s\n"
           "Hire and fire employees.....: %s\n"
           "Negotiate player contracts..: %s\n",
           nyn[am.do_training_schedules],
           nyn[am.treat_injured_players],
           nyn[am.check_sponsors_boards],
           nyn[am.hire_and_fire_employees],
           nyn[am.negotiate_player_contracts]);

    printf("\n\n%02x\n", manager.data120);

    static const char *skill[] = {"Handling", "Tackling", "Passing", "Shooting"};
    printf("Type of youth player required:%s\n",
           skill[manager.youth_player_type]);

    printf("%02x\n", manager.data121);

    if (manager.youth_player != -1)
        printf("Youth team player: %12.12s\n",
               gamec.player[manager.youth_player].name);

    for (int i = 0; i < sizeof(manager.data147); ++i) {
        if (i % 16 == 0)
            printf("\n[%3d] ", i);
        printf("%02x ", manager.data147[i]);
    }
    printf("\n");

    printf("Scouts\n");
    for (int i = 0; i < 4; ++i) {
        struct gamea::manager::scout &scout = manager.scout[i];
        printf("size: %d\n", scout.size);
        printf("%d Division: %s" "Club: %d Skill: %s\n"
               "Rating: %s\n"
               "Foot: %s\n",
               i, division[scout.division],
               scout.club,
               skill[scout.skill],
               rating[scout.rating],
               foot_long[scout.foot]);

        for (int j = 0; j < 18; ++j) {
            if (scout.results[j].ix1 == -1)
                continue;

            printf("  %12.12s %04x\n",
                   gamec.player[scout.results[j].ix1].name,
                   scout.results[j].ix2);
        }

        for (int j = 0; j < sizeof(scout.other); ++j) {
            printf("%02x ", scout.other[j]);
        }
        printf("\n");

        printf("\n");
    }

    printf("Number 1            :%d\n", manager.number1);
    printf("Number 2            :%d\n", manager.number2);
    printf("Number 3            :%d\n", manager.number3);
    printf("Money from directors:%d\n", manager.money_from_directors);

    for (int i = 0; i < sizeof(manager.data149); ++i) {
        if (i % 16 == 0)
            printf("\n[%3d] ", i);
        printf("%02x ", manager.data149[i]);
    }
    printf("\n");

    printf("--News--\n");
    for (int i = 0; i < 8; ++i) {
        struct gamea::manager::news &news = manager.news[i];
        switch (news.type) {
            case 1:
                printf("The V.A.T. demand has been payed to the department\n"
                       "of customs and excise\n");
                break;

            case 2:
                printf("Due to a mistake in your last tax return you have\n"
                       "received a bill of £%-7d from the taxman\n", news.amount);
                break;

            case 3:
                printf("You have exceeded your overdraft limit so you are\n"
                       "now liable for a higher rate of interest\n");
                break;

            case 9:
                printf("You have received a grant of £%-7d from the\n"
                       "F.A. for general ground improvements\n",
                       news.amount);
                break;

            case 10:
                printf("The club has been fined £%-7d for bringing the\n"
                       "game into disrepute\n", news.amount);
                break;

            case 12:
                printf("After receiving a complaint of poor hygiene the\n"
                       "health authority have fined you £%d\n", news.amount);
                break;

            case 16:
                printf("The board pays the shareholders £%d\n",
                       news.amount);
                break;

            case 17:
                printf("%12.12s is playing for his country today\n",
                       gamec.player[news.ix2].name);
                break;

            case 18:
                printf("A national TV station has payed your club £%d\n"
                       "for the live T.V. coverage of your last match\n",
                       news.amount);
                break;

            case 20:
                printf("%12.12s has now retired from football\n",
                       gamec.player[news.ix2].name);
                break;

            case 21:
                printf("%12.12s will be taking early retirement from\n"
                       "football in 4 weeks time\n",
                       gamec.player[news.ix2].name);
                break;

            case 22:
                printf("%12.12s has now taken early retirement for a\n"
                       "life of luxury in the Costa del Sol\n",
                       gamec.player[news.ix2].name);
                break;

            case 23:
                printf("%12.12s has retired due to an injury\n",
                       gamec.player[news.ix2].name);
                break;

            case 24:
                printf("A member of your staff has retired\n");
                break;

            case 25:
                printf("%12.12s has been injured while training\n",
                       gamec.player[news.ix2].name);
                break;

            case 26:
                printf("The youth team coach has found a youth player who\n"
                       "matches your requirements\n");
                break;

            case 27:
                printf("%12.12s due to having no contract left with\n"
                       "your club has now signed for %16.16s\n",
                       gamec.player[news.ix2].name,
                       gameb.club[news.ix1].name);
                break;

            case 29:
                printf("Phone me up %16.16s from %16.16s\n"
                       "Telephone No. 844444 (%12.12s)\n",
                       gameb.club[news.ix1].manager,
                       gameb.club[news.ix1].name,
                       gamec.player[news.ix2].name);
                break;

            case 30:
                printf("You have been voted manager of the month\n");
                break;

            case 31:
                printf("Your job application to become the manager of\n"
                       "%16.16s has been turned down\n", gameb.club[news.ix1].name);
                break;

            case 32:
                printf("The board of directors have given you a public\n"
                       "vote of confidence\n");
                break;

            default:
                printf("%3d, %d, (%d, %d, %d)\n",
                       news.type, news.amount,
                       news.ix1, news.ix2, news.ix3);
                break;
        }
    }

    assert(manager.minus_one == -1);

    for (int i = 0; i < 2; ++i) {
        if (manager.unknown_player_idx[i] == -1)
            printf("Unknown Player%d: %d\n", i, manager.unknown_player_idx[i]);
        else
            printf("Unknown Player%d: (%04x) %12.12s\n",
                   i, manager.unknown_player_idx[i],
                   gamec.player[manager.unknown_player_idx[i]].name
            );
    }

//		printf("d6 01, %d, %12.12s\n", 0x01d6, gamec.player[0x01d6].name);

    /* same 16bit numbers can show up multiple times in this data-pile.
     * suspect it's player (gamec) data somehow
     * */
    printf("\n--- data150 --- 0x01d6 = 365. repeats alot.\n");
    for (int i = 0; i < sizeof(manager.data150); ++i) {
        if (i % 16 == 0)
            printf("\n[%4d]", i);
        printf(" %02x", manager.data150[i]);
    }
    printf("\n");

    struct gamea::manager::stadium &stadium = manager.stadium;

    printf("Construction\n");
    for (int i = 0; i < 4; ++i) {
        printf("[%20.20s] expand_capacity = %d, %d\n",
               stadium.stand[i].name, stadium.seating_build[i].level, stadium.seating_build[i].time);
        printf("[%20.20s] convert_to_seating = %d, %d\n",
               stadium.stand[i].name, stadium.conversion[i].level, stadium.conversion[i].time);
        printf("[%20.20s] area_covering = %d, %d\n",
               stadium.stand[i].name, stadium.area_covering[i].level, stadium.area_covering[i].time);
        printf("\n");
    }

    printf("ground_facilities = %d, %d\n", stadium.ground_facilities.level, stadium.ground_facilities.time);
    printf("supporters_club   = %d, %d\n", stadium.supporters_club.level, stadium.supporters_club.time);
    printf("flood_lights      = %d, %d\n", stadium.flood_lights.level, stadium.flood_lights.time);
    printf("scoreboard        = %d, %d\n", stadium.scoreboard.level, stadium.scoreboard.time);
    printf("undersoil_heating = %d, %d\n", stadium.undersoil_heating.level, stadium.undersoil_heating.time);
    printf("changing_rooms    = %d, %d\n", stadium.changing_rooms.level, stadium.changing_rooms.time);
    printf("gymnasium         = %d, %d\n", stadium.gymnasium.level, stadium.gymnasium.time);
    printf("car_park          = %d, %d\n", stadium.car_park.level, stadium.car_park.time);

    printf("safety rating     =");
    for (int i = 0; i < sizeof(stadium.safety_rating); ++i)
        printf(" %02x", stadium.safety_rating[i]);
    printf("\n");

    for (int i = 0; i < 4; ++i) {
        printf("[%20.20s] capacity = %5d %s\n",
               stadium.stand[i].name, stadium.capacity[i].seating,
               stadium.capacity[i].terraces ? "terraces" : "seating");
    }

    printf("Numb01: %5d\nNumb02: %5d\nNumb03: %5d\nNumb04: %5d\n",
           manager.numb01, manager.numb02,
           manager.numb03, manager.numb04);
    printf("Managerial rating.....:%3d%% (%+2d%%)\n"
           "Directors confidence..:%3d%% (%+2d%%)\n"
           "Supporters confidence.:%3d%% (%+2d%%)\n",
           manager.managerial_rating_current,
           manager.managerial_rating_current - manager.managerial_rating_start,
           manager.directors_confidence_current,
           manager.directors_confidence_current - manager.directors_confidence_start,
           manager.supporters_confidence_current,
           manager.supporters_confidence_current - manager.supporters_confidence_start);


    printf("---- match data start ?----\n");

    for (int i = 0; i < sizeof(manager.head6); ++i) {
        if (i % 16 == 0)
            printf("\n[%03d] ", i);
        printf("%02x ", manager.head6[i]);
    }
    printf("\n");

    if (manager.player3_idx == -1)
        printf("NomPlayer1: %d ", manager.player3_idx);
    else
        printf("NomPlayer1: (%04x) %12.12s",
               manager.player3_idx,
               gamec.player[manager.player3_idx].name
        );

    for (int i = 0; i < sizeof(manager.magic4); ++i) {
        if (i % 16 == 0)
            printf("\n[%03d] ", i);
        printf("%02x ", manager.magic4[i]);
    }
    printf("\n");

    if (manager.player4_idx == -1)
        printf("NomPlayer2: %d ", manager.player4_idx);
    else
        printf("NomPlayer2: (%04x) %12.12s",
               manager.player4_idx,
               gamec.player[manager.player4_idx].name
        );

    for (int i = 0; i < sizeof(manager.foot6); ++i) {
        if (i % 16 == 0)
            printf("\n[%03d] ", i);
        printf("%02x ", manager.foot6[i]);
    }
    printf("\n");

/*
		printf("(%04x) %16.16s %d(%d)  (%04x) %16.16s %d(%d)\n",
			gamea.manager[nr].match[0].club,
			gameb.club[ gamea.manager[nr].match[0].club ].name,
			gamea.manager[nr].match[0].total_goals,
			gamea.manager[nr].match[0].first_half_goals,
			gamea.manager[nr].match[1].club,
			gameb.club[ gamea.manager[nr].match[1].club ].name,
			gamea.manager[nr].match[1].total_goals,
			gamea.manager[nr].match[1].first_half_goals
		);
*/

    printf("match summary\n");

    struct gamea::manager::match_summary &ms = manager.match_summary;
    for (int i = 0; i < 2; ++i) {
        struct gamea::manager::match_summary::club &club = ms.club[i];
        if (club.club_idx == -1) {
            printf("%s: %d", i ? "Away" : "Home",
                   club.club_idx);
            continue;
        }

        printf("%s: (%04x) %16.16s", i ? "Away" : "Home",
               club.club_idx, gameb.club[club.club_idx].name);

        printf(" Goals: %d(%d)\n",
               club.total_goals,
               club.first_half_goals
        );

        printf("Pattern:");
        for (int j = 0; j < sizeof(club.pattern6); ++j) {
            printf(" %02x", club.pattern6[j]);
        }
        printf("\n");

        for (int j = 0; j < sizeof(club.match_data); ++j) {
            if (j % 16 == 0)
                printf("\n[%03d]", j);
            printf(" %02x", club.match_data[j]);
        }
        printf("\n");

        printf("Corners...: %d\n", club.corners);
        printf("Throw ins.: %d\n", club.throw_ins);
        printf("Free kicks: %d\n", club.free_kicks);
        printf("Penalties.: %d\n", club.penalties);

        printf("Lineup\n");
        for (int j = 0; j < 14; ++j) {
            struct gamea::manager::match_summary::club::lineup &lineup = club.lineup[j];
            print_player_name(lineup.player_idx, false);

            for (int k = 0; k < sizeof(lineup.data5); ++k) {
                printf(" %02x", lineup.data5[k]);
            }

            printf(" [%d]", lineup.card); // 4 = red, 1 = yellow?

            for (int k = 0; k < sizeof(lineup.x); ++k) {
                printf(" %02x", lineup.x[k]);
            }
            printf("\n");
        }

        printf("Goals\n");
        for (int j = 0; j < 8; ++j) {
            struct gamea::manager::match_summary::club::goal &goal = club.goal[j];
            print_player_name(goal.player_idx, false);

            if (goal.player_idx == -1)
                printf(" time: %d",
                       goal.time);
            else
                printf(" %2d:%02d",
                       goal.time / 60,
                       goal.time % 60
                );
            printf("\n");
        }

        assert(club.always_null == 0);

        printf("always_null: %04x\n", club.always_null);
        printf("Substitutions remaining: %d\n", club.substitutions_remaining);
        printf("other remaining: %d\n", club.other);

        assert(club.substitutions_remaining < 3);

        printf("Home/Away magic: %04x\n",
               club.home_away_data);

        if (i == 0 && club.club_idx == 0x0062)
            assert(club.home_away_data == 0x5738);

        if (i == 1 && club.club_idx == 0x0062)
            assert(club.home_away_data == 0x91f8);
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

    printf("Weather: (%04x) %s\n", ms.weather, weather[ms.weather]);

    if (ms.referee_idx == -1)
        printf("Referee: %d", ms.referee_idx);
    else
        printf("Referee: (%02x) %14.14s\n",
               ms.referee_idx,
               gamea.referee[ms.referee_idx].name
        );

    for (int i = 0; i < sizeof(ms.data156); ++i) {
        if (i % 16 == 0)
            printf("\n[%03d] ", i);
        printf("%02x ", ms.data156[i]);
    }
    printf("\n");

    printf("Match type: (%02x)", ms.match_type);

    for (int i = 0; i < sizeof(ms.data157); ++i) {
        if (i % 16 == 0)
            printf("\n[%03d] ", i);
        printf("%02x ", ms.data157[i]);
    }
    printf("\n");

    printf("audience %d\n", ms.audience);

    for (int i = 0; i < sizeof(ms.data158); ++i) {
        if (i % 16 == 0)
            printf("\n[%03d] ", i);
        printf("%02x ", ms.data158[i]);
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
        struct gamea::manager::league_history &lh = manager.league_history[i];

        if (lh.year == 0)
            continue;

        printf("%4d %5.5s (%04x)%16.16s %2d %2d %2d %2d %2d %3d %3d",
               lh.year, div[lh.div], lh.club_idx, gameb.club[lh.club_idx].name,
               lh.ps, lh.p, lh.w, lh.d, lh.l, lh.gd, lh.pts);

        printf(" %02x %02x %02x %02x"
               " %02x %02x %02x %02x"
               " %02x %02x %02x %02x\n",
               lh.unk21, lh.unk22, lh.unk23, lh.unk24,
               lh.unk25, lh.unk26, lh.unk27, lh.unk28,
               lh.unk29, lh.unk30, lh.unk31, lh.unk32);
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
               manager.titles[i].won,
               manager.titles[i].yrs,

               match_type[5 + i],
               manager.titles[5 + i].won,
               manager.titles[5 + i].yrs
        );
    }
    printf("                        %-15.15s %3d %3d\n\n",
           match_type[10],
           manager.titles[10].won,
           manager.titles[10].yrs);

    printf("Match type       Play  Won Drew Lost   For   Agn\n");
    for (int i = 0; i < 11; ++i)
        printf("%-15.15s  %4d %4d %4d %4d  %4d  %4d\n",
               match_type[i],
               manager.manager_history[i].play,
               manager.manager_history[i].won,
               manager.manager_history[i].drew,
               manager.manager_history[i].lost,
               manager.manager_history[i].forx,
               manager.manager_history[i].agn);
    printf("\n");

    for (int i = 0; i < sizeof(manager.data159); ++i) {
        if (i % 16 == 0)
            printf("\n[%03d] ", i);
        printf("%02x ", manager.data159[i]);
    }
    printf("\n");

    printf("       Previous clubs   From To   Mngr Drct Sprt\n");
    for (int i = 0; i < 4; ++i) {
        printf("(%04x) %16.16s %4d %4d %3d%% %3d%% %3d%%\n",
               manager.previous_clubs[i].club_idx,
               gameb.club[manager.previous_clubs[i].club_idx].name,
               manager.previous_clubs[i].year_from,
               manager.previous_clubs[i].year_to,
               manager.previous_clubs[i].mngr,
               manager.previous_clubs[i].drct,
               manager.previous_clubs[i].sprt
        );
    }

    printf("Current club start year: %4d\n", manager.year_start_cur_club);

    printf("Manager of the month awards.%d\n",
           manager.manager_of_the_month_awards);

    printf("Manager of the year awards..%d\n",
           manager.manager_of_the_year_awards);

    printf("\n");

    printf("--- Previous Matches History ---\n");
    printf("Team             Division     P  W  D  L   F   A\n");
    for (int i = 0; i < 242; ++i)
        printf("%16.16s %-10.10s  %2d %2d %2d %2d %3d %3d\n",
               gameb.club[ manager.match_history[i].club_idx ].name,
               "FIXME", // premier, div 1-3, conference, non league and european
               manager.match_history[i].played,
               manager.match_history[i].won,
               manager.match_history[i].draw,
               manager.match_history[i].played - manager.match_history[i].won - manager.match_history[i].draw,
               manager.match_history[i].goals_f,
               manager.match_history[i].goals_a);
    printf("\n");


    for (int i = 0; i < sizeof(manager.data160); ++i) {
        if (i % 16 == 0)
            printf("\n[%03d] ", i);
        printf("%02x ", manager.data160[i]);
    }
    printf("\n");

    for (int i = 0; i < 8; ++i)
        printf("tactic[%d].name: %20.20s\n", i, manager.tactic[i].name);
    printf("\n");
}

void dump_gameb() {
    for (int i = 0; i < CLUB_IDX_MAX; ++i) {
        struct gameb::club &club = get_club(i);
        dump_club(club);
    }
}


void dump_club(struct gameb::club &club) {
    printf("Club   : %16.16s\n", club.name);
    printf("Manager: %16.16s\n", club.manager);
    printf("Bank account: %d\n", club.bank_account);
    printf("Stadium: %24.24s\n", club.stadium);
    printf("Seating avg: %d\n", club.seating_avg);
    printf("Seating max: %d\n", club.seating_max);

    printf("\n---\n");
    for (int i = 0; i < sizeof(club.padding); ++i) {
        printf("%02x ", club.padding[i]);
    }
    printf("\n---\n");


    for (int i = 0; i < 24; ++i) {
        struct gamec::player &p = gamec.player[club.player_index[i]];
        print_player_name(club.player_index[i]);
    }

    for (int i = 0; i < sizeof(club.misc000); ++i) {
        if (i % 16 == 0)
            printf("\n[%3d] ", i);
        printf("%02x ", club.misc000[i]);
    }
    printf("\n");
    printf("League: %d\n", club.league);
    printf("\n");

    for (int i = 0; i < 3; ++i) {
        printf("Kit[%d] - Shirt Design: %d Shirt Color1: (%d,%d,%d), Shirt Color2: (%d,%d,%d), Shorts Color: (%d,%d,%d), Socks Color: (%d,%d,%d)\n",
               i,
               club.kit[i].shirt_design,
               club.kit[i].shirt_primary_color_r,
               club.kit[i].shirt_primary_color_g,
               club.kit[i].shirt_primary_color_b,
               club.kit[i].shirt_secondary_color_r,
               club.kit[i].shirt_secondary_color_g,
               club.kit[i].shirt_secondary_color_b,
               club.kit[i].shorts_color_r,
               club.kit[i].shorts_color_g,
               club.kit[i].shorts_color_b,
               club.kit[i].socks_color_r,
               club.kit[i].socks_color_g,
               club.kit[i].socks_color_b
        );
    }
    printf("\n");


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
    static const char game[] = {
            'H', // home          0
            'H', // home_friendly 1
            'A', // away          2
            'A', // away_friendly 3
            '4',
            '5'
    };


    printf("Timetable for %16.16s\n", club.name);
    printf("Day:Wk Match type       G Scr Opponent\n");
    for (int w = 0; w < 41; ++w) {
        for (int d = 0; d < 3; ++d) {
            struct gameb::club::timetable::week::day &rnd = club.timetable.week[w].day[d];

            if (rnd.opponent_idx == 0xFF) {
                printf("%3s:%-2d %-16.16s %c %3s %16.16s",
                       day[d], w + 1, "None............", '.', "...", "................");
            } else if (rnd.result == -1) {
                struct gameb::club &opponent = get_club(rnd.opponent_idx);

                printf("%3s:%-2d %-16.16s %c %3.3s %16.16s",
                       day[d], w + 1, match_type[rnd.type], game[rnd.game], "...", opponent.name);
            } else {
                struct gameb::club &opponent = get_club(rnd.opponent_idx);

                printf("%3s:%-2d %-16.16s %c %d:%d %16.16s",
                       day[d], w + 1, match_type[rnd.type], game[rnd.game], rnd.home, rnd.away, opponent.name);
            }

            printf(" club: %02x, result: %02x b3: %02x\n",
                   (uint8_t) rnd.opponent_idx, (uint8_t) rnd.result, (uint8_t) rnd.b3);
        }
    }
}

void print_club_name(int16_t idx, bool newline) {
    assert(idx >= -1 && idx < CLUB_IDX_MAX);

    if (idx == -1)
        printf("Club: %d%s", idx, newline ? "\n" : "");
    else
        printf("Club: %16.16s%s", gameb.club[idx].name, newline ? "\n" : "");
}

void dump_gamec() {
    for (int i = 0; i < 3932; ++i) {
        struct gamec::player &player = get_player(i);
        dump_player(player);
    }
}

void dump_player(struct gamec::player &p) {

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
    static const char *intense[] = {"Low", "Medium", "Hard", "V.Hard"};

    printf("Player: %12.12s\n", p.name);
    printf("Age: %2d\n", p.age);
    printf("Wage: %5d\n", p.wage);
    printf("Insure: %d %5d\n", p.ins, p.ins_cost);
    printf("Handling : %2d\n", p.hn);
    printf("Tackling : %2d\n", p.tk);
    printf("Passing  : %2d\n", p.ps);
    printf("Shooting : %2d\n", p.sh);
    printf("Heading  : %2d\n", p.hd);
    printf("Control  : %2d\n", p.cr);
    printf("Fitness  : %2d\n", p.ft);
    printf("Aggr'sion: %2d\n", p.aggr);
    printf("Morale   : %2d\n", p.morl);
    printf("Foot     : %5.5s\n", foot_long[p.foot]);
    printf("\n");
    printf("Played  : %3d\n", p.played);
    printf("Scored  : %3d\n", p.scored);
    printf("Conceded: \n");
    printf("DPTS    :  %d\n", p.dpts);
    printf("Training : %7s, %6s\n", train[p.train], intense[p.intense]);

    printf("%d year contract\n", p.contract);
    printf("%02x %02x %02x %02x %02x %02x %02x\n",
           p.u13, p.u15, p.u17, p.u19, p.u21, p.u23, p.u25);
    printf("%02x %02x\n", p.unk2, p.unk5);

    char period_label[8];
    if (p.period_type == 0 || p.period_type == 1) {
        sprintf(period_label, "matches");
    } else {
        sprintf(period_label, "weeks");
    }
    printf("%s %d %s\n\n", period_types[p.period_type], (p.period + 3 - 1) / 3, period_label);
}

void print_player_row(struct club_player &club_player) {
    print_player_row(club_player.player, club_player.club);
}

void print_player_row(struct gamec::player &p, struct gameb::club &club) {
    printf("%16.16s %1c %12.12s %2d %2d %2d %2d %2d %2d %2d %1.1s %1d %1d %2d %5d\n", club.name,
           determine_player_type(p), p.name, p.hn, p.tk, p.ps, p.sh, p.hd, p.cr, p.ft, foot_short[p.foot], p.aggr,
           p.morl, p.age, p.wage);
}

void print_player_name(int16_t idx, bool newline) {
    assert(idx >= -1 && idx < 3932);

    if (idx == -1)
        printf("Player: %d%s", idx, newline ? "\n" : "");
    else
        printf("Player: (%04x) %12.12s%s",
               idx, gamec.player[idx].name, newline ? "\n" : "");
}

void fax_match_summary() {
    static const char *match_type[] = {
            "00",
            "01",
            "02",
            "03",
            "04",
            "05",
            "06",
            "07",
            "08",
            "09",
            "0a",
            "0b",
            "0c",
            "0d",
            "0e",
            "0f",
            "10",
            "11",
            "12",
            "13",
            "14",
            "15",
            "16",
            "17",
            "18",
            "19",
            "1a",
            "1b",
            "1c",
            "1d",
            "1e",
            "1f",
            "20",
            "21",
            "22",
            "23",
            "24",
            "25",
            "26",
            "charity shield",
            "28",
            "29",
            "2a",
            "2b",
            "2c",
            "2d",
            "2e",
            "2f",
    };

    static const char *weather[] = {
            "", /* 00 */
            "icy", /* 01 */
            "", /* 02 */
            "", /* 03 */
            "", /* 04 */
            "", /* 05 */
            "heavy rain    ", /* 06 */
            "high winds    ", /* 07 */
            "cold & sunny  ", /* 08 */
            "cold & raining", /* 09 */
            "cold & cloudy ", /* 0a */
            "cold & windy  ", /* 0b */
            "heavy rain    ", /* 0c */
            "high winds    ", /* 0d */
            "light rain    ", /* 0e */
            "overcast      ", /* 0f */
            "warm & raining", /* 10 */
            "warm & cloudy ", /* 11 */
            "raining       ", /* 12 */
            "windy & sunny ", /* 13 */
            "light winds   "  /* 14 */
    };

    struct {
        uint16_t shots_attempted = 0;
        uint16_t shots_missed = 0;
        uint16_t tackles_attempted = 0;
        uint16_t tackles_won = 0;
        uint16_t passes_attempted = 0;
        uint16_t passes_bad = 0;
        uint16_t shots_saved = 0;
        uint16_t something = 0;
    } club[2];

    for (int i = 0; i < 14; ++i) {
        for (int j = 0; j < 2; ++j) {
            club[j].shots_attempted += gamea.manager[0].match_summary.club[j].lineup[i].shots_attempted;
            club[j].shots_missed += gamea.manager[0].match_summary.club[j].lineup[i].shots_missed;
            club[j].tackles_attempted += gamea.manager[0].match_summary.club[j].lineup[i].tackles_attempted;
            club[j].tackles_won += gamea.manager[0].match_summary.club[j].lineup[i].tackles_won;
            club[j].passes_attempted += gamea.manager[0].match_summary.club[j].lineup[i].passes_attempted;
            club[j].passes_bad += gamea.manager[0].match_summary.club[j].lineup[i].passes_bad;
            club[j].shots_saved += gamea.manager[0].match_summary.club[j].lineup[i].shots_saved;
            club[j].something += gamea.manager[0].match_summary.club[j].lineup[i].something;
        }
    }

    printf("%s\n", match_type[gamea.manager[0].match_summary.match_type]);
    printf("%16.16s %d(%d)    %16.16s %d(%d)\n",
           gameb.club[gamea.manager[0].match_summary.club[0].club_idx].name,
           gamea.manager[0].match_summary.club[0].total_goals,
           gamea.manager[0].match_summary.club[0].first_half_goals,
           gameb.club[gamea.manager[0].match_summary.club[1].club_idx].name,
           gamea.manager[0].match_summary.club[1].total_goals,
           gamea.manager[0].match_summary.club[1].first_half_goals);
    printf("after full time\n");
    printf("%d at %s\n", gamea.manager[0].match_summary.audience, "some stadium");
    printf("weather: %s  referee: %14.14s\n",
           weather[gamea.manager[0].match_summary.weather],
           gamea.referee[gamea.manager[0].match_summary.referee_idx].name);
    printf("\n");
    printf("totals               home away\n");
    printf("possession time..... 50:40 39:20\n");
//	printf("yellow cards....... %5d %-5d\n", gamea.manager[0].match_summary.club[0].yellow_cards , gamea.manager[0].match[1].yellow_cards);
//	printf("red cards.......... %5d %-5d\n", gamea.manager[0].match[0]. , gamea.manager[0].match[1].);
//	printf("players injured.... %5d %-5d\n", gamea.manager[0].match[0]. , gamea.manager[0].match[1].);
    printf("\n");
    printf("corners............ %5d %-5d\n", gamea.manager[0].match_summary.club[0].corners,
           gamea.manager[0].match_summary.club[1].corners);
    printf("throw ins.......... %5d %-5d\n", gamea.manager[0].match_summary.club[0].throw_ins,
           gamea.manager[0].match_summary.club[1].throw_ins);
    printf("free kicks......... %5d %-5d\n", gamea.manager[0].match_summary.club[0].free_kicks,
           gamea.manager[0].match_summary.club[1].free_kicks);
    printf("penalties.......... %5d %-5d\n", gamea.manager[0].match_summary.club[0].penalties,
           gamea.manager[0].match_summary.club[1].penalties);
    printf("\n");
    printf("shots attempted.... %5d %-5d\n", club[0].shots_attempted, club[1].shots_attempted);
    printf("shots saved........ %5d %-5d\n", club[1].shots_saved, club[0].shots_saved);
    printf("shots missed....... %5d %-5d\n", club[0].shots_missed, club[1].shots_missed);
    printf("\n");
    printf("attempted tackles.. %5d %-5d\n", club[0].tackles_attempted, club[1].tackles_attempted);
    printf("tackles won........ %5d %-5d\n", club[0].tackles_won, club[1].tackles_won);
    printf("tackles lost....... %5d %-5d\n", club[0].tackles_attempted - club[0].tackles_won,
           club[1].tackles_attempted - club[1].tackles_won);
    printf("\n");
    printf("attempted passes... %5d %-5d\n", club[0].passes_attempted, club[1].passes_attempted);
//	printf("good passes........ %5d %-5d\n", gamea.manager[0].match[0]. , gamea.manager[0].match[1].);
//	printf("passes intercepted. %5d %-5d\n", gamea.manager[0].match[0]. , gamea.manager[0].match[1].);
    printf("bad passes......... %5d %-5d\n", club[0].passes_bad, club[1].passes_bad);
    printf("\n");
    printf("something.......... %5d %-5d\n", club[0].something, club[1].something);

}

void dump_gamea_match_summary() {
    printf("head6:");
    for (int i = 0; i < sizeof(gamea.manager[0].head6); ++i)
        printf(" %02x", gamea.manager[0].head6[i]);
    printf("\n");

    if (gamea.manager[0].player3_idx == -1)
        printf("player1_idx: %d\n", gamea.manager[0].player3_idx);
    else
        printf("player1_idx: (%04x) %12.12s\n",
               gamea.manager[0].player3_idx,
               gamec.player[gamea.manager[0].player3_idx].name
        );

    printf("magic4:");
    for (int i = 0; i < sizeof(gamea.manager[0].magic4); ++i)
        printf(" %02x", gamea.manager[0].magic4[i]);
    printf("\n");

    if (gamea.manager[0].player4_idx == -1)
        printf("player2_idx: %d\n", gamea.manager[0].player4_idx);
    else
        printf("player2_idx: (%04x) %12.12s\n",
               gamea.manager[0].player4_idx,
               gamec.player[gamea.manager[0].player4_idx].name
        );

    printf("foot6:");
    for (int i = 0; i < sizeof(gamea.manager[0].foot6); ++i)
        printf(" %02x", gamea.manager[0].foot6[i]);
    printf("\n");

    printf("---- match summary start ----\n");

    struct gamea::manager::match_summary &ms = gamea.manager[0].match_summary;

    for (int i = 0; i < 2; ++i) {
        printf("<%s club %d data>\n", i ? "away" : "home", i);

        if (ms.club[i].club_idx == -1) {
            printf("%d\n", ms.club[i].club_idx);
            continue;
        }

        printf("(%04x) %16.16s\n", ms.club[i].club_idx, gameb.club[ms.club[i].club_idx].name);

        printf(" Goals: %d(%d)\n",
               ms.club[i].total_goals,
               ms.club[i].first_half_goals
        );

        printf("Pattern:");
        for (int j = 0; j < sizeof(ms.club[i].pattern6); ++j)
            printf(" %02x", ms.club[i].pattern6[j]);
        printf("\n");

        printf("%02x %02x %02x %02x\n",
               ms.club[i].match_data[1],
               ms.club[i].match_data[2],
               ms.club[i].match_data[3],
               ms.club[i].match_data[4]);

        printf("Corners...: %d\n", ms.club[i].corners);
        printf("Throw ins.: %d\n", ms.club[i].throw_ins);
        printf("Free kicks: %d\n", ms.club[i].free_kicks);
        printf("Penalties.: %d\n", ms.club[i].penalties);

        int d0 = 0, d1 = 0, d2 = 0, d3 = 0, d4 = 0, ft = 0, cd = 0;
        int sa = 0, sm = 0, s2 = 0, ta = 0, tw = 0, pa = 0, pb = 0;
        int ss = 0, x0 = 0, x1 = 0, x2 = 0;

        printf("lineup: ( idx) player_name   d0  d1  d2  d3  d4  ft  cd  sa  sm  s2  ta  tw  pa  pb  ss  x0  x1  x2\n");
        for (int j = 0; j < 14; ++j) {
            print_player_name(ms.club[i].lineup[j].player_idx);

            for (int k = 0; k < sizeof(ms.club[i].lineup[j].data5); ++k)
                printf(" %03x", ms.club[i].lineup[j].data5[k]);

            printf(" %03d", ms.club[i].lineup[j].fitness);
            printf(" %03x", ms.club[i].lineup[j].card); // 4 = red, 1 = yellow?
            printf(" %03x", ms.club[i].lineup[j].shots_attempted);
            printf(" %03x", ms.club[i].lineup[j].shots_missed);
            printf(" %03x", ms.club[i].lineup[j].something);
            printf(" %03x", ms.club[i].lineup[j].tackles_attempted);
            printf(" %03x", ms.club[i].lineup[j].tackles_won);
            printf(" %03x", ms.club[i].lineup[j].passes_attempted);
            printf(" %03x", ms.club[i].lineup[j].passes_bad);
            printf(" %03x", ms.club[i].lineup[j].shots_saved);

            for (int k = 0; k < sizeof(ms.club[i].lineup[j].x); ++k)
                printf(" %03x", ms.club[i].lineup[j].x[k]);
            printf("\n");

            d0 += ms.club[i].lineup[j].data5[0];
            d1 += ms.club[i].lineup[j].data5[1];
            d2 += ms.club[i].lineup[j].data5[2];
            d3 += ms.club[i].lineup[j].data5[3];
            d4 += ms.club[i].lineup[j].data5[4];
            ft += ms.club[i].lineup[j].fitness;
            cd += ms.club[i].lineup[j].card;
            sa += ms.club[i].lineup[j].shots_attempted;
            sm += ms.club[i].lineup[j].shots_missed;
            s2 += ms.club[i].lineup[j].something;
            ta += ms.club[i].lineup[j].tackles_attempted;
            tw += ms.club[i].lineup[j].tackles_won;
            pa += ms.club[i].lineup[j].passes_attempted;
            pb += ms.club[i].lineup[j].passes_bad;
            ss += ms.club[i].lineup[j].shots_saved;
            x0 += ms.club[i].lineup[j].x[0];
            x1 += ms.club[i].lineup[j].x[1];
            x2 += ms.club[i].lineup[j].x[2];
        }
        printf("summary....................");
        printf(" %03x %03x %03x %03x %03x %03x %03x", d0, d1, d2, d3, d4, ft, cd);
        printf(" %03x %03x %03x %03x %03x %03x %03x", sa, sm, s2, ta, tw, pa, pb);
        printf(" %03x %03x %03x %03x\n", ss, x0, x1, x2);

        for (int j = 0; j < 8; ++j) {
            print_player_name(ms.club[i].goal[j].player_idx, false);

            if (ms.club[i].goal[j].player_idx == -1)
                printf(" time: %d\n", ms.club[i].goal[j].time);
            else
                printf(" %2d:%02d\n",
                       ms.club[i].goal[j].time / 60,
                       ms.club[i].goal[j].time % 60);
        }

        assert(ms.club[i].always_null == 0);
        printf("always_null: %04x\n", ms.club[i].always_null);

        assert(ms.club[i].substitutions_remaining < 3);
        printf("substitutions remaining: %d\n", ms.club[i].substitutions_remaining);

        printf("other remaining: %d\n", ms.club[i].other);

        printf("home/away magic: %04x\n",
               ms.club[i].home_away_data);

        if (ms.club[i].club_idx == 0x0062 && i == 0)
            assert(ms.club[i].home_away_data == 0x5738);
        if (ms.club[i].club_idx == 0x0062 && i == 1)
            assert(ms.club[i].home_away_data == 0x91f8);

        printf("</%s club %d data>\n", i ? "away" : "home", i);
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

    printf("weather: (%04x) %s\n", ms.weather, weather[ms.weather]);

    if (ms.referee_idx == -1)
        printf("referee: %d", ms.referee_idx);
    else
        printf("referee: (%02x) %14.14s\n",
               ms.referee_idx,
               gamea.referee[ms.referee_idx].name
        );

    for (int i = 0; i < sizeof(gamea.manager[0].match_summary.data156); ++i) {
        if (i % 16 == 0)
            printf("\n[%03d] ", i);
        printf("%02x ", gamea.manager[0].match_summary.data156[i]);
    }
    printf("\n");

    printf("Match type: (%02x)", gamea.manager[0].match_summary.match_type);

    for (int i = 0; i < sizeof(gamea.manager[0].match_summary.data157); ++i) {
        if (i % 16 == 0)
            printf("\n[%03d] ", i);
        printf("%02x ", gamea.manager[0].match_summary.data157[i]);
    }
    printf("\n");

    printf("audience %d\n", gamea.manager[0].match_summary.audience);

    for (int i = 0; i < sizeof(gamea.manager[0].match_summary.data158); ++i) {
        if (i % 16 == 0)
            printf("\n[%03d] ", i);
        printf("%02x ", gamea.manager[0].match_summary.data158[i]);
    }
    printf("\n\n");
}

void print_player_row_header() {
    printf("CLUB NAME        T PLAYER NAME  HN TK PS SH HD CR FT F M A AG  WAGES\n");
}

void soup_up(int player) {
    printf("Souping up!");

    struct gamea::manager &manager = gamea.manager[player];

    print_club_name(manager.club_idx);

    for (int i = 0; i < 20; ++i) {
        struct gamea::manager::employee &employee = manager.employee[i];
        printf("Employee: %14.14s\n", employee.name);
        employee.skill = 99;
        //employee.age = i % 16;
    }

    struct gameb::club &club = gameb.club[manager.club_idx];

    for (int p = 0; p < 24; ++p) {
        if (club.player_index[p] == -1)
            continue;

        print_player_name(club.player_index[p]);
        struct gamec::player &player = gamec.player[club.player_index[p]];

        player.hn = 97;
        player.tk = 97;
        player.ps = 97;
        player.sh = 97;

        switch (p) {
            case 0:
            case 11:
            case 15:
                player.hn = 99;
                break;

            case 1:
            case 2:
            case 4:
            case 5:
            case 12:
            case 16:
            case 19:
            case 22:
                player.tk = 99;
                break;

            case 3:
            case 10:
            case 13:
            case 17:
            case 20:
                player.ps = 99;
                break;

            case 6:
            case 7:
            case 8:
            case 9:
            case 14:
            case 18:
            case 21:
            case 23:
                player.sh = 99;
                break;

            default:
                break;
        }

        player.hd = 99;
        player.cr = 99;
        player.ft = 99;

        player.morl = 8;
    }
}


void dump_free_players() {
    print_player_row_header();
    std::vector<club_player> free_players = find_free_players();

    for (club_player &free_player: free_players) {
        print_player_row(free_player);
    }
}
