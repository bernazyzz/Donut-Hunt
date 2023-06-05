#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <string.h>
#include "main.h"

/*
typedef struct Item {
	char ch;
	char *name;
	char *buffDescription;
	char *lore;

	int rarity;
	int buff;
	int level;
	int ID;
} Item;
*/

Item * createRandomItem(Player * user) {
	Item * item;
    int ID = (rand() % 3) + 1; // 1 - 2
	//int randomItem = rand() % 10;


	int randomItem = itemsEquilibrium(user);
	//int ID = 1;
    if (ID == 1) { // create armor
        char ch = '@';

        char name[10][20] = {
			"Leather armor",
			"Stone armor",
			"Iron armor",
			"Steel armor",
			"Gold armor",
			"Tiago's armor",
			"Emerald armor",
			"Jhonny's armor",
			"Pedro's armor",
			"Monix's armor"
		};

		char buffDescription[10][75] = {
			"Useful protection against cuts, +3 defense (x3 floor)",
			"Simple protection against cuts, +5 defense (x3 floor)",
			"Good protection against sharp blades, +10 defense",
			"Excelent protection against any threat, +12 defense",
			"The beauty of this armor gives you strength, +20 defense",
			"Carequinha armor, +30 defense (x3 floor)",
			"Perfect protection, +45 defense (x3 floor)",
			"Pivot armor, +50 defense (x3 floor)",
			"Brazilian armor, +75 defense (x3 floor)",
			"A armadura mais util do jogo, +100 defense (x5 floor)"
		};

		char lore[10][200] = {
			"None",
			"None",
			"None",
			"None",
			"None",
			"Corte seu cabelo na Navalha do Fidalgo",
			"None",
			"None",
			"None",
			"Essa armadura veio dos primordios da antiguidade, a armadura dos deuses, todos desejam-na, mas somente os mais uteis possuem-na."
		};

		int rarity[10] = {
			1,
			1,
			2,
			2,
			3,
			3,
			4,
			4,
			5,
			5
		};

		int buff[10] = {
			13 + (user->dungeonFloor * 3),
			15 + (user->dungeonFloor * 3),
			20 + (user->dungeonFloor * 3),
			22 + (user->dungeonFloor * 3),
			30 + (user->dungeonFloor * 3),
			40 + (user->dungeonFloor * 3),
			55 + (user->dungeonFloor * 3),
			60 + (user->dungeonFloor * 3),
			85 + (user->dungeonFloor * 3),
			110 + (user->dungeonFloor * 5)
		};

		item = createItem(ch,name[randomItem],buffDescription[randomItem],lore[randomItem],rarity[randomItem],buff[randomItem],user->dungeonFloor,ID);
    } else if (ID == 2) {
		char ch = '|';

        char name[10][20] = {
			"Wood sword",
			"Stone hammer",
			"Steel sword",
			"Iron sword",
			"Dual blades",
			"Flame sword",
			"Light saber",
			"Quantum sword",
			"God's sword",
			"Monix's sword"
		};

		char buffDescription[10][75] = {
			"Usefull sword, +4 damage",
			"You can rock some monsters with this, +5 damage",
			"Good medieval era sword, +6 damage",
			"Medieval era sword, +7 damage",
			"The heat of this blades is dangerous, +14 damage",
			"May the force be with you, +25 damage",
			"Early's technological sword, +35 damage",
			"Advanced tech sword, +45 damage",
			"Judgement sword, +80 damage",
			"A espada mais util do jogo, +120 damage"
		};

		char lore[10][200] = {
			"None",
			"None",
			"None",
			"None",
			"None",
			"None",
			"None",
			"None",
			"None",
			"Essa espada veio dos primordios da antiguidade, a espada dos deuses, todos desejam-na, mas somente os mais uteis possuem-na."
		};

		int rarity[10] = {
			1,
			1,
			2,
			2,
			3,// piso 1-3
			4,
			4,
			4,// piso 4 - 8
			5,
			5 // piso 9 - 14
		};

		int buff[10] = {
			14 + (user->dungeonFloor * 3),
			15 + (user->dungeonFloor * 3),
			16 + (user->dungeonFloor * 3),
			17 + (user->dungeonFloor * 3),
			24 + (user->dungeonFloor * 3),
			35 + (user->dungeonFloor * 3),
			45 + (user->dungeonFloor * 3),
			55 + (user->dungeonFloor * 3),
			90 + (user->dungeonFloor * 3),
			130 + (user->dungeonFloor * 5)
		};

		item = createItem(ch,name[randomItem],buffDescription[randomItem],lore[randomItem],rarity[randomItem],buff[randomItem],user->dungeonFloor,ID);
	} else {
		char ch = 'O';

        char name[10][20] = {
			"Unlucky ring",
			"Lucky ring",
			"Blessing ring",
			"Curse ring",
			"Darkness ring",
			"Brightness ring",
			"Life ring",
			"Hard ring",
			"Blindness ring",
			"Developer's ring"
		};

		char buffDescription[10][75] = {
			"Monsters intelligence increased",
			"Your chances for better items increased",
			"Monsters deal less damage",
			"Monsters deal more damage",
			"Your vision decreased",
			"Your vision increased",
			"+100 Life points",
			"-25 Life points",
			"Just 3 blocks can be spotted in your radius :/",
			"Press <v> for debug mode"
		};

		char lore[10][200] = {
			"None",
			"None",
			"None",
			"None",
			"None",
			"None",
			"None",
			"None",
			"None",
			"None"
		};

		int rarity[10] = {
			1,
			1,
			2,
			2,
			3,
			3,
			4,
			4,
			5,
			5
		};

		int buff[10] = {
			1,
			-1,
			10,
			-5,
			-4, // decrease 4 radius
			4, // increase 4 radius
			100,
			-25,
			3,
			1
		};

		item = createItem(ch,name[randomItem],buffDescription[randomItem],lore[randomItem],rarity[randomItem],buff[randomItem],user->dungeonFloor,ID);
	}


	return item;
}