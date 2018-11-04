#include "pch.h"
#include "health.h"

void graphHP(int currentHP, int maxHP)
{
	//int granularity = 40;
	printf("\n");
	if (100 * currentHP / maxHP > 30)
		printf("\x1b[32m");
	else
		printf("\x1b[31m");
	//for (int i = maxHP - currentHP; i < maxHP; i += (maxHP / granularity))
	for (int i = maxHP - currentHP; i < maxHP; i+= 40)
	{
		printf("#");
	}
	printf("\x1b[0m");
}
