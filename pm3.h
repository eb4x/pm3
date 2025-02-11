#ifndef _PM3_H
#define _PM3_H

#include <stdint.h>

#define CLUB_IDX_MAX 244
#define HOME 0
#define AWAY 1

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
	} __attribute__ ((packed)) club_index;

	union {
		struct {
			struct { int16_t club_idx; int16_t hx; int16_t hw; int16_t hd; int16_t hl; int16_t hf; int16_t ha; int16_t ax; int16_t aw; int16_t ad; int16_t al; int16_t af; int16_t aa; int16_t xx; } __attribute__ ((packed)) premier_league[22];
			struct { int16_t club_idx; int16_t hx; int16_t hw; int16_t hd; int16_t hl; int16_t hf; int16_t ha; int16_t ax; int16_t aw; int16_t ad; int16_t al; int16_t af; int16_t aa; int16_t xx; } __attribute__ ((packed)) division_one[24];
			struct { int16_t club_idx; int16_t hx; int16_t hw; int16_t hd; int16_t hl; int16_t hf; int16_t ha; int16_t ax; int16_t aw; int16_t ad; int16_t al; int16_t af; int16_t aa; int16_t xx; } __attribute__ ((packed)) division_two[24];
			struct { int16_t club_idx; int16_t hx; int16_t hw; int16_t hd; int16_t hl; int16_t hf; int16_t ha; int16_t ax; int16_t aw; int16_t ad; int16_t al; int16_t af; int16_t aa; int16_t xx; } __attribute__ ((packed)) division_three[22];
			struct { int16_t club_idx; int16_t hx; int16_t hw; int16_t hd; int16_t hl; int16_t hf; int16_t ha; int16_t ax; int16_t aw; int16_t ad; int16_t al; int16_t af; int16_t aa; int16_t xx; } __attribute__ ((packed)) conference_league[22];
		} __attribute__ ((packed));

		struct { int16_t club_idx; int16_t hx; int16_t hw; int16_t hd; int16_t hl; int16_t hf; int16_t ha;
		                           int16_t ax; int16_t aw; int16_t ad; int16_t al; int16_t af; int16_t aa;
		                           int16_t xx;
		} __attribute__ ((packed)) all[114];
	} __attribute__ ((packed)) table;

	uint16_t data000;
	uint16_t data001;
	uint32_t data002;

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

	struct referee {
		char name[14];
		uint8_t magic : 3;
		uint8_t age   : 5;
		uint8_t var[7];
	} __attribute__ ((packed)) referee[64];


	union cuppy {
		struct {
			struct { struct { int16_t idx; int16_t goals; int32_t audience; } __attribute__ ((packed)) club[2]; } __attribute__ ((packed)) the_fa_cup[36];
			struct { struct { int16_t idx; int16_t goals; int32_t audience; } __attribute__ ((packed)) club[2]; } __attribute__ ((packed)) the_league_cup[28];
			struct { struct { int16_t idx; int16_t goals; int32_t audience; } __attribute__ ((packed)) club[2]; } __attribute__ ((packed)) data090[4];
			struct { struct { int16_t idx; int16_t goals; int32_t audience; } __attribute__ ((packed)) club[2]; } __attribute__ ((packed)) the_champions_cup[16];
			struct { struct { int16_t idx; int16_t goals; int32_t audience; } __attribute__ ((packed)) club[2]; } __attribute__ ((packed)) data091[16];
			struct { struct { int16_t idx; int16_t goals; int32_t audience; } __attribute__ ((packed)) club[2]; } __attribute__ ((packed)) the_cup_winners_cup[16];
			struct { struct { int16_t idx; int16_t goals; int32_t audience; } __attribute__ ((packed)) club[2]; } __attribute__ ((packed)) the_uefa_cup[32];
			struct { struct { int16_t idx; int16_t goals; int32_t audience; } __attribute__ ((packed)) club[2]; } __attribute__ ((packed)) the_charity_shield;
		} __attribute__ ((packed));
		struct cup_entry { struct { int16_t idx; int16_t goals; int32_t audience; } __attribute__ ((packed)) club[2]; } __attribute__ ((packed)) all[149];
	} __attribute__ ((packed)) cuppy;

	uint8_t data095[2240];

	struct {
		struct { int16_t idx; int16_t goals; int32_t audience; } __attribute__ ((packed)) club[2];
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
			struct { struct { int16_t idx; int16_t goals; int32_t audience; } __attribute__ ((packed)) club[2]; } __attribute__ ((packed)) the_fa_cup[0];
		};
		struct { struct { int16_t idx; int16_t goals; int32_t audience; } __attribute__ ((packed)) club[2]; } __attribute__ ((packed)) all[57];
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

	uint8_t data100[106];
	struct {
		int16_t player_idx;
		int16_t club_idx;
	} __attribute__ ((packed)) transfer_market[45];

	uint8_t data10z[208];

	struct {
		int16_t player_idx;
		int16_t from_club_idx;
		int16_t to_club_idx;
		int32_t fee;
	} __attribute__ ((packed)) transfer[6];

	uint8_t data101[20];
	int16_t retired_manager_club_idx;
	int16_t new_manager_club_idx;
	char manager_name[16];
	uint8_t data10w[8];
	uint16_t turn;
	uint16_t year;

	/* seems to be a collection of 16bit numbers. */
	uint16_t data10x[15];

	/* The players of the game */
	struct manager {
		char name[16];
		int16_t club_idx;
		int16_t division;
		uint16_t contract_length;

		struct {
			uint8_t league_match_seating;
			uint8_t league_match_terrace;
			uint8_t cup_match_seating;
			uint8_t cup_match_terrace;
		}__attribute__ ((packed)) price;

		uint32_t seating_history[23];
		uint32_t terrace_history[23];

		struct bank_statement {
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

		struct loan {
			uint32_t amount;
			uint8_t turn; //3 turns in a week, 42 weeks in a year?
			uint8_t year;
		} __attribute__ ((packed)) loan[4];

		struct employee {
			char name[14];
			uint8_t skill;
			uint8_t type : 4;
			uint8_t age  : 4;
		} __attribute__ ((packed)) employee[20];

		struct assistant_manager {
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

		uint8_t data147[3];

		struct scout {
			int8_t size;
			uint8_t skill;
			uint8_t rating;
			uint8_t division : 3;
			uint8_t foot : 5;
			uint8_t club;
			struct {
				int16_t ix1;
				int16_t ix2;
			} __attribute__ ((packed)) results[18];
			uint8_t other[5];
		} __attribute__ ((packed)) scout[4];

		uint8_t smnthn;
		uint32_t number1;
		uint32_t number2;
		uint32_t number3;
		uint32_t money_from_directors;
		uint8_t data149[20];

		struct news {
			int16_t type;
			int32_t amount;
			int16_t ix1;
			int16_t ix2;
			int16_t ix3;
		} __attribute__ ((packed)) news[8];

		int32_t minus_one;
		int16_t unknown_player_idx[2];
		uint8_t data150[576];

		struct stadium {
			struct {
				char name[20];
			} __attribute__ ((packed)) stand[4];

			struct {
				uint8_t level : 3;
				uint8_t time  : 5;
			} __attribute__ ((packed)) seating_build[4];

			struct {
				uint8_t level : 3; /* terraces, wooden seating, plastic seating */
				uint8_t time  : 5;
			} __attribute__ ((packed)) conversion[4];

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

			struct {
				uint16_t seating: 15;
				uint16_t terraces: 1;
			} __attribute__ ((packed)) capacity[4];

		} __attribute__ ((packed)) stadium;

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
		int16_t player3_idx;
		uint8_t magic4[4];
		int16_t player4_idx;
		uint8_t foot6[6];

		struct match_summary {
			struct club {
				uint16_t club_idx;
				uint16_t total_goals;
				uint16_t first_half_goals;
				uint8_t pattern6[6]; // 02 00 26 50 60 77
				uint8_t match_data[4];
				uint8_t corners;
				uint8_t throw_ins;
				uint8_t free_kicks;
				uint8_t penalties;

				struct lineup {
					int16_t player_idx;
					uint8_t data5[5];
					uint8_t fitness; // matches with benched players, but not onfield.
					uint8_t card;
					uint8_t shots_attempted;
					uint8_t shots_missed;
					uint8_t something;
					uint8_t tackles_attempted;
					uint8_t tackles_won;
					uint8_t passes_attempted;
					uint8_t passes_bad;
					uint8_t shots_saved; // these are for opposing club in the fax_match_summary
					uint8_t x[3];
				} __attribute__ ((packed)) lineup[14];

				struct goal {
					int16_t player_idx;
					int16_t time;
				} __attribute__ ((packed)) goal[8];

				uint16_t always_null;
				uint8_t substitutions_remaining;
				uint8_t other;
				uint16_t home_away_data; // home: 0x5738, away: 0x91f8
			} __attribute__ ((packed)) club[2]; // home + away club

			uint16_t weather;
			uint8_t referee_idx;
			uint8_t data156[4];
		/*
 * 1e fa_cup semi final
 * 1f fa_cup 4th/5th,
 * 20 fa_cup 3rd,
 * 21 league cup 2nd round 1, 4th round, quarter final
 * 22 league cup 2nd round 2, 3rd round
 * 23 champions cup 1st leg 1,
 * 24 cup_win_cup 2nd round 1/2/qfinal
 * 27 charity_shield
 * 28 premier
 * 29 home-friendly
 * 2b conference
		*/
			uint8_t match_type;
			uint8_t data157[6];
			uint32_t audience;
			uint8_t data158[92];
		} __attribute__ ((packed)) match_summary;

		struct league_history {
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
			uint8_t club_idx;
			uint8_t played;
			uint8_t won;
			uint8_t draw;
			uint16_t goals_f;
			uint16_t goals_a;
		} __attribute__ ((packed)) match_history[242];

		uint8_t data160[1794];

		struct {
			char name[20];
		} __attribute__ ((packed)) tactic[8];
	} __attribute__ ((packed)) manager[2];

	uint8_t data200[10];
	uint16_t inc_number1;
	uint16_t inc_number2;
	uint16_t inc_number3;

} __attribute__ ((packed));
extern struct gamea gamea;

struct gameb {
	struct club {
		char name[16];
		char manager[16];
		int32_t bank_account;
		char stadium[24];
		int32_t seating_avg;
		int32_t seating_max;
		uint8_t padding[8];
		int16_t player_index[24];

		uint8_t misc000[4];
		struct kit {
			uint8_t shirt_design;
			uint8_t shirt_primary_color_r : 4;
			uint8_t shirt_primary_color_g : 4;
			uint8_t shirt_primary_color_b : 4;

			uint8_t shirt_secondary_color_r : 4;
			uint8_t shirt_secondary_color_g : 4;
			uint8_t shirt_secondary_color_b : 4;

			uint8_t shorts_color_r : 4;
			uint8_t shorts_color_g : 4;
			uint8_t shorts_color_b : 4;

			uint8_t socks_color_r : 4;
			uint8_t socks_color_g : 4;
			uint8_t socks_color_b : 4;
		} __attribute__ ((packed)) kit[3]; // 0=Home, 1=Away1, 2=Away2

		uint8_t player_image;
		uint8_t weekly_league_position[46];
		uint8_t misc005[3];
		uint8_t league;

		struct timetable {
			struct week {
				struct day {

					uint8_t opponent_idx;

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

	} __attribute__ ((packed)) club[CLUB_IDX_MAX];

} __attribute__ ((packed));
extern struct gameb gameb;

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
} __attribute__ ((packed));
extern struct gamec gamec;

struct saves {
    struct game {
        uint16_t year;
        uint16_t turn;
        struct manager {
            char name[16];
            uint8_t club_idx;
        } __attribute__ ((packed)) manager[2];
        uint8_t misc000[162]; // Tactics files
    } __attribute__ ((packed)) game[8];
} __attribute__ ((packed));
extern struct saves saves;

struct prefs {
    struct league_reports {
        int16_t hide_premier_league;
        int16_t hide_division_one;
        int16_t hide_division_two;
        int16_t hide_division_three;
        int16_t hide_conference_league;
    } __attribute__ ((packed)) league_reports;
    struct cup_reports {
        int16_t hide_fa_cup;
        int16_t hide_league_cup;
        int16_t hide_champions_cup;
        int16_t hide_cup_winners_cup;
        int16_t hide_uefa_cup;
        int16_t hide_charity_shield;
    } __attribute__ ((packed)) cup_reports;
    int16_t hide_friendlies;
    struct view_screens {
        int16_t hide_results_monitor;
        int16_t hide_next_matches;
        int16_t hide_manager_of_the_month;
    } __attribute__ ((packed)) view_screens;
    struct interactive_matches {
        int16_t match_graphics; // 0 = None, 1 = Strips, 2 = Numbers
        int16_t unused1;
        int16_t show_match_pictures;
        int16_t speed; // Revered so 00 = 50, 31 = 1
        int16_t unk1;
        int16_t unused3;
    } __attribute__ ((packed)) interactive_matches;
    struct audio {
        int16_t mute_sound_effects;
        int16_t mute_music;
    } __attribute__ ((packed)) audio;
} __attribute__ ((packed));
extern struct prefs prefs;

void check_consistency();

struct gameb::club& get_club(int idx);
struct gamec::player& get_player(int16_t idx);

const char* determine_player_type(struct gamec::player &player);
void change_club(int new_club_idx, int player = 0);

void soup_up(int player = 0);

void load_binaries(int game_nr, const char *game_path);
void save_binaries(int game_nr, const char *game_path);

void load_metadata(const char *game_path);
void update_metadata(int game_nr);
void save_metadata(const char *game_path);

struct gamea *load_default_gamedata(const char *game_path);
struct gameb *load_default_clubdata(const char *game_path);
struct gamec *load_default_playdata(const char *game_path);

#endif
