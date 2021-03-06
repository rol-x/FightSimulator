#include "fighter.h"
#include "fightersTeam.h"

#include "pch.h"

#define TEAM_SIZE 5
#define TEAM_NAME "Gladiators"
#define FIGHTER_POINTS 1000

enum ATTACK_TYPES
{
	CRITICAL,
	BALANCED,
	BLOCK
};

typedef struct _Attack
{
	int hitValue;
	int blockValue;
} Attack;

typedef struct _Fighter
{
	std::string name;
	int currentHP;
	int maxHP;
	int minStrength;
	int maxStrength;
	Attack attack;
} Fighter;

typedef struct _FightersTeam
{
	std::string teamName;
	Fighter fighters[TEAM_SIZE];
} FightersTeam;

Fighter setFighterStats(std::string name, int health, int minStrength, int maxStrength)
{
	Fighter createdFighter;
	createdFighter.name = name;
	createdFighter.maxHP = health;
	createdFighter.currentHP = health;
	createdFighter.minStrength = minStrength;
	createdFighter.maxStrength = maxStrength;
	createdFighter.attack.hitValue = 0;
	createdFighter.attack.blockValue = 0;
	return createdFighter;
}

std::string ordinalIndicator(int n)
{
	if ((n % 100) > 10 && (n % 100) < 20)		//11, 12, 13, ... - 'teens' end with th
		return "th";
	switch (n % 10)								//everything except 'teens' follows: 0th, 1st, 2nd, 3rd, 4th, 5th, 6th, ...
	{
	case 1:
		return "st";
		break;
	case 2:
		return "nd";
		break;
	case 3:
		return "rd";
		break;
	default:
		return "th";
		break;
	}
	return "";									//failsafe
}

void initializeFightersTeam(FightersTeam &team)
{
	std::string name;
	int health, minStrength, maxStrength;
	team.teamName = TEAM_NAME;
	for (int i = 0; i < TEAM_SIZE; i++)
	{
		system("cls");
		std::cout << "Name " << i + 1 << ordinalIndicator(i + 1) << " member of " << TEAM_NAME << ": ";
		std::cin >> name;
		std::cout << "Stats generated for " << name << std::endl;

		health = (rand() % FIGHTER_POINTS*0.4 + 1) + FIGHTER_POINTS*0.4;
		minStrength = (FIGHTER_POINTS - health) * 0.3;
		maxStrength = (FIGHTER_POINTS - health) * 0.7;

		std::cout << "Health: " << health << std::endl;
		std::cout << "Minimal strength: " << minStrength << std::endl;
		std::cout << "Maximal strength: " << maxStrength << std::endl;

		team.fighters[i] = setFighterStats(name, health, minStrength, maxStrength);

		std::cout << std::endl << std::endl;
		system("pause");
	}
}

double maximum(double a, double b)
{
	return (a >= b) ? a : b;
}

bool isDead(Fighter fighter)
{
	return fighter.currentHP > 0 ? false : true;
}

void showHP(Fighter fighter)
{
	std::cout << fighter.name << "'s HP is " << fighter.currentHP << "!\t(Attack: " << fighter.attack.hitValue << ", block: " << fighter.attack.blockValue << ")";
	graphHP(fighter.currentHP, fighter.maxHP);
	std::cout << std::endl;
}

void prepareAttack(Fighter &fighter)
{
	int attackValue = rand() % (fighter.maxStrength - fighter.minStrength + 1) + fighter.minStrength;		//100, 800: 800-100+1 = 701 => 0-700 + 100 = 100-800
	ATTACK_TYPES attackType = static_cast<ATTACK_TYPES>((rand() % 10000) % 3);

	fighter.attack.hitValue = 0;
	fighter.attack.blockValue = 0;

	switch (attackType)
	{
	case CRITICAL:
		fighter.attack.hitValue = 0.9*attackValue;
		break;
	case BALANCED:
		fighter.attack.hitValue = 0.6*attackValue;
		fighter.attack.blockValue = 0.5*attackValue;
		break;
	case BLOCK:
		fighter.attack.blockValue = attackValue;
		break;
	}
}

void fight(Fighter &user, FightersTeam &team)
{
	int fighterNumber = 0;
	do
	{
		system("cls");

		prepareAttack(user);
		prepareAttack(team.fighters[fighterNumber]);

		showHP(user);
		showHP(team.fighters[fighterNumber]);

		Sleep(200);
		system("cls");

		user.currentHP -= maximum(team.fighters[fighterNumber].attack.hitValue - user.attack.blockValue, 0);
		showHP(user);

		if (isDead(user))
		{
			std::cout << team.fighters[fighterNumber].name << " from " << team.teamName << " is the winner!\n";
			break;
		}

		team.fighters[fighterNumber].currentHP -= maximum(user.attack.hitValue - team.fighters[fighterNumber].attack.blockValue, 0);
		showHP(team.fighters[fighterNumber]);

		if (isDead(team.fighters[fighterNumber]))
		{
			fighterNumber++;
			if(fighterNumber != TEAM_SIZE)
				system("pause");
			continue;
		}

		Sleep(300);
	} while (fighterNumber < TEAM_SIZE);

	if (user.currentHP > 0)
		std::cout << user.name << " is the winner!\n";
}

int main()
{
	srand(time(0));

	std::string userName;
	std::cout << "Type your name: ";
	std::cin >> userName;
	Fighter user = setFighterStats(userName, 0.5*FIGHTER_POINTS*5, 0.15*FIGHTER_POINTS, 0.25*FIGHTER_POINTS);			//for optimal gameplay HP = 5*100000/averageAttackValue, e.g. 2500HP, 150 min, 250 max

	FightersTeam gladiators;
	initializeFightersTeam(gladiators);

	fight(user, gladiators);

	std::cout << std::endl;
	system("pause");
	return 0;
}