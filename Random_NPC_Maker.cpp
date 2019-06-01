// Ravnica People Maker

// For use with the DND 5E System.

// Generates one person per call, useful if you need a bunch of random NPC's.
// Have fun with Ted, names are random grab bag, add more from the guides if you wish.

#include <math.h>
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

struct die {
	const static int min=1;
	int max;
};

class NPC {
	private:
		string race;		//X
		string alignment;	//X
		string name;		//X
		string sex;
		string regligion;
		string clan;
		string guild;
		string char_class;				//Class is a reserved word, use char_class

		int level; 			//for xp pts  //X
		int strength;		//X
		int dexterity;		//X
		int constitution;	//X
		int intelligence; 	//X
		int wisdom;			//X
		int charisma;		//X

		int stren_mod;		//X
		int dex_mod;		//X
		int cont_mod;		//X
		int int_mod;		//X
		int wis_mod;		//X
		int cha_mod;		//X

		int HP;				//X
		int AC;				//X
		int initiative;
		int prof_bonus;
		int pass_percept;

		//bool skill_prof [];
		//bool save_throw [];
		int speed;			//X
		die dmg;			//X
		die hit_die;		//X

	public:
		NPC() {
			set_alignment();
			set_name();
			set_race();
			// Roll 4d6 record total of 3 highest 6 times.

			strength = stat_roll(1);
			dexterity = stat_roll(2);
			constitution = stat_roll(3);
			intelligence = stat_roll(4);
			wisdom = stat_roll(5);
			charisma = stat_roll(6);

			stren_mod = modifier(strength);
			dex_mod = modifier(dexterity);
			cont_mod = modifier(constitution);
			int_mod = modifier(intelligence);
			wis_mod = modifier(wisdom);
			cha_mod = modifier(charisma);

			srand(time(NULL));
			hit_die.max = rand() % 2 + 8;

			srand(time(NULL));
			level = rand() % 10 + 5;

			HP = hp_calc(level);
			AC = 10 + dex_mod;

			dmg.max = damage_inc();

			speed = 40;
		}

		NPC(int primary_skill) {
			set_alignment();

			vector <int> statrolls;
			for(int i=0; i<6; i++) {
				statrolls.push_back(stat_roll(i));
			}

			int highest = find_highest(statrolls);  // Returns the index for highest val.

			switch(primary_skill) {
				case 1: 
					strength = statrolls[highest];
					statrolls.erase(statrolls.begin() + (highest-1));
					assign_other(primary_skill, statrolls);
				case 2: 
					dexterity = statrolls[highest];
					statrolls.erase(statrolls.begin() + (highest-1));
					assign_other(primary_skill, statrolls);
				case 3: 
					constitution = statrolls[highest];
					statrolls.erase(statrolls.begin() + (highest-1));
					assign_other(primary_skill, statrolls);
				case 4: 
					intelligence = statrolls[highest];
					statrolls.erase(statrolls.begin() + (highest-1));
					assign_other(primary_skill, statrolls);
				case 5: 
					wisdom = statrolls[highest];
					statrolls.erase(statrolls.begin() + (highest-1));
					assign_other(primary_skill, statrolls);
				case 6: 
					charisma = statrolls[highest];
					statrolls.erase(statrolls.begin() + (highest-1));
					assign_other(primary_skill, statrolls);
				default: cerr << "Invalid value in NPC constructor switch";
			}

			stren_mod = modifier(strength);
			dex_mod = modifier(dexterity);
			cont_mod = modifier(constitution);
			int_mod = modifier(intelligence);
			wis_mod = modifier(wisdom);
			cha_mod = modifier(charisma);

			srand(time(NULL));
			hit_die.max = rand() % 2 + 8;

			srand(time(NULL));
			level = rand() % 10 + 5;

			HP = hp_calc(level);
			AC = 10 + dex_mod;

			dmg.max = damage_inc();

			speed = 40;
		}
		
		int stat_roll(int value) {
			vector <int> rolls;
			int sum = 0;

			for(int i=0; i < 4; i++) {
				srand(time(NULL) * value);
				rolls.push_back(rand() % 5 + 1);
			}

			int lowest = find_lowest(rolls);

			rolls.erase(rolls.begin() + (lowest-1));

			for(int j=0; j < rolls.size(); j++) {
				sum = sum + rolls[j];
			}

			return sum;
		}

		int find_highest(vector <int> list) {
			int start = 1;
			for(int i=1; i < list.size(); i++) {
				if(list[i] >= start) {
					start = i;
				}
			}
			return start;
		}

		int find_lowest(vector <int> list) {
			int start = 1;
			for(int i=1; i < list.size(); i++) {
				if(list[i] <= start){
					start = i;
				}
			}
			return start;
		}

		int modifier(int stat) {
			int mod = 0;
			if(stat >= 1 && stat <= 1) {
				mod = -5;
			}
			if(stat >= 2 && stat <= 3) {
				mod = -4;
			}
			if(stat >= 4 && stat <= 5) {
				mod = -3;
			}
			if(stat >= 6 && stat <= 7) {
				mod = -2;
			}
			if(stat >= 8 && stat <= 9) {
				mod = -1;
			}
			if(stat >= 10 && stat <= 11) {
				mod = 0;
			}
			if(stat >= 12 && stat <= 13) {
				mod = 1;
			}
			if(stat >= 14 && stat <= 15) {
				mod = 2;
			}
			if(stat >= 16 && stat <= 17) {
				mod = 3;
			}
			if(stat >= 18 && stat <= 19) {
				mod = 4;
			}
			if(stat >= 20 && stat <= 21) {
				mod = 5;
			}
			if(stat >= 22 && stat <= 23) {
				mod = 6;
			}
			return mod;
		}

		int hp_calc(int lvl) {
			int sum = 0;
			for(int i = 0; i<lvl; i++) {
				srand(time(NULL));
				sum = sum + (cha_mod + (rand() % (hit_die.max-1) + hit_die.min));
			}
			return sum;
		}

		int damage_inc() {
			//Select weapon
			srand(time(NULL));
			int weap = rand() % 8;
			switch(weap) {
				case 1: return 4;
				case 2: return 6;
				case 3: return 8;
				case 4: return 10;
				case 5: return 12;
				case 6: return 16;
				case 7: return 18;
				case 8: return 20;
				default: return 8;
			} 
		}

		void assign_other(int al_set, vector <int> val) {
			for(int i=0; i<val.size(); i++) {

				if( i != al_set ) { //Skip skill already set.
					switch(i) {
						case 1: 
							strength = val[i];
						case 2: 
							dexterity = val[i];
						case 3: 
							constitution = val[i];
						case 4: 
							intelligence = val[i];
						case 5: 
							wisdom = val[i];
						case 6: 
							charisma = val[i];
						default: cerr << "Invalid value in assign_other switch";
					}
				}
			}
		}

		void set_alignment() {
			srand(time(NULL));
			int val = rand() % 8 + 1;

			// Lawful, True, Chaotic
			// Good, Neutral, Evil

			switch(val) {
				case 1: alignment = "Lawful Good";
				case 2: alignment = "Lawful Neutral";
				case 3: alignment = "Lawful Evil";
				case 4: alignment = "True Good";
				case 5: alignment = "True Neutral";
				case 6: alignment = "True Evil";
				case 7: alignment = "Chaotic Good";
				case 8: alignment = "Chaotic Neutral";
				case 9: alignment = "Chaotic Evil";
				default: alignment = "True Neutral";
			}

		}

		void set_name() {

			string names[] = {"Ted the Omnipresent NPC", "Dave", "Gerald", "Frank", "Louis"};
			
			int size = sizeof(names)/sizeof(*names);
			srand(time(NULL));
			int val = rand() % (size-1);
			name = names[val];
		}

		void set_race() {

			string races[] = {"Minotaur", "Human", "Elf", "Dark Elf", "Centaur", "Gnome", "Halfling", "Dwarf", "Dragonborn", 
			"Gnome", "Half-Elf", "Half-Orc", "Tiefling"};
			
			int size = sizeof(races)/sizeof(*races);
			srand(time(NULL));
			int val = rand() % (size-1);
			race = races[val];
		}

		void print() {
			cout << "Name: " << name << endl;
			cout << "Race: " << race << endl;
			cout << "Alignment: " << alignment << endl;
			cout << endl;

			cout << "Level: " << level << endl;
			cout << "HP: " << HP << endl;	
			cout << "AC: " << AC << endl;	
			cout << "DmgDie: " << dmg.max << endl;	
			cout << "Speed: " << speed << endl;
			cout << endl;

			cout << "S: " << strength << endl;
			cout << "Sm: " << stren_mod << endl;

			cout << "D: " << dexterity << endl;
			cout << "Dm: " << dex_mod << endl;

			cout << "C: " << constitution << endl;
			cout << "Cm: " << cont_mod << endl;

			cout << "I: " << intelligence << endl;
			cout << "Im: " << int_mod << endl;

			cout << "W: " << wisdom << endl;
			cout << "Wm: " << wis_mod << endl;

			cout << "Ch: " << charisma << endl;
			cout << "Chm: " << cha_mod << endl;
			cout << endl;
		}

		~NPC() {}

};


int main () {
	NPC first;
	first.print();
	return 0;
}