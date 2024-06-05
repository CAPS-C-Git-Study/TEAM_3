/*
문제 2 : BlackJack 게임 구현

알고리즘 설명 : BlackJack 게임은 딜러와 플레이어가 카드를 받아가며 21에 가까운 수를 만드는 게임이다.
카드는 52장의 카드를 사용하며, 각 카드는 2~10까지의 숫자를 가지고 있다. 그림 카드(J,Q,K)는 10으로 계산하며, A는 1 또는 11로 계산한다.
딜러와 플레이어는 각각 2장의 카드를 받아서 시작하며, 플레이어는 카드를 계속 받을지(HIT), 그만 받을지(STAND)를 선택할 수 있다.
카드를 계속 받다가 21을 초과하면(BURST) 패배하게 되며, 21에 가까운 수를 만들면 승리하게 된다.
플레이어가 승리하면, 배팅 금액의 2배를 받게 되며, 패배하면 배팅 금액을 잃는다.
플레이어가 처음 두 장의 카드로 블랙잭(21)을 만들면, 배팅 금액의 1.5배를 받게 된다.
딜러는 17이상의 수를 만들 때까지 카드를 계속 받아야 한다.
구현의 편의를 위해, 스플릿, 인슈런스의 기능은 구현하지 않는다.
다만, 더블 다운 기능은 구현한다.

더블 다운 이란 : 플레이어가 처음에 받은 2장의 카드의 합이 9, 10, 11일 때 선택할 수 있는 기능으로, 카드를 한 장 더 받고 배팅 금액을 2배로 늘릴 수 있다.
이후에는 카드를 받을 수 없으며, 딜러와 비교하여 승패를 결정한다.

문제 : BlackJack 게임을 구현하시오.
게임은 1명의 플레이어와 1명의 딜러로 진행된다.
초기 금액은 10000원으로 시작하며, 게임을 진행하면서 금액을 변동시킨다.
입금, 출금, 게임을 진행하는 기능을 구현한다.
플레이어의 이름, 전화번호를 입력받는 기능을 구현한다.
덱은 52장의 카드로 구성되며, 카드는 2~10, J, Q, K, A로 구성된다.
카드는 무작위로 섞여서 나오며, 카드는 중복되어 나오지 않는다.
카드를 나눠주는 기능, 카드를 받는 기능, 카드의 합을 계산하는 기능을 구현한다.
52장의 카드를 모두 사용하면, 다시 52장의 카드를 사용한다.
플레이어가 HIT, STAND, DOUBLE DOWN을 선택할 수 있도록 구현한다.

사용하는 자료 구조 : 구조체, 배열, 포인터
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS
#define NAME_SIZE 20
#define DECK_SIZE 52
#define BLACKJACK 21
#define START_BALANCE 10000
#define DEALER_STAND 17

typedef struct player {
	char name[NAME_SIZE];
	char phoneNumber[20];
	double balance;
} Player;

typedef struct deck {
	int cardValues[DECK_SIZE];
	int cardIndex;
} Deck;

void initialize_Player(Player* player);//player 초기화
void initialize_Deck(Deck* deck);//deck 초기화
void shuffle_Deck(Deck* deck);//deck 섞기
void deal_Card(Deck* deck, Player* player);//card 나눠주기
void play_Blackjack(Player* player, Player* dealer, Deck* deck);//blackjack 시작

int main(void)
{
	Player player;
	Player dealer;
	Deck deck;

	initialize_Player(&player);
	getchar();
	initialize_Player(&dealer);
	getchar();
	initialize_Deck(&deck);

	play_Blackjack(&player, &dealer, &deck);

	return 0;
}
void initialize_Player(Player* player)
{
	printf("Enter a Player Name: ");
	scanf_s("%[^\n]", player->name, sizeof(player->name));


	printf("Enter a Player Phone Number: ");
	scanf_s("%s", player->phoneNumber, sizeof(player->phoneNumber));

	player->balance = START_BALANCE;
}
void initialize_Deck(Deck* deck)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			deck->cardValues[i * 13 + j] = (j >= 9) ? 10 : j + 2; // J,Q,K , 2~10
		}
	}
	deck->cardValues[48] = deck->cardValues[49] = deck->cardValues[50] = deck->cardValues[51] = 11;//A
	deck->cardIndex = 0;

	shuffle_Deck(deck);
}
void shuffle_Deck(Deck* deck)
{
	srand((unsigned)time(NULL));
	for (int i = DECK_SIZE - 1; i > 0; i--)
	{
		int j = rand() % (i + 1);
		int temp = deck->cardValues[i];
		deck->cardValues[i] = deck->cardValues[j];
		deck->cardValues[j] = temp;
	}
}
void deal_Card(Deck* deck, Player* player)
{
	if (deck->cardIndex >= DECK_SIZE)
	{
		initialize_Deck(deck);
	}
}
void play_Blackjack(Player* player, Player* dealer, Deck* deck)
{
	int card_num_player = 0;
	int player_val = 0;
	int card_num_dealer = 0;
	int dealer_val = 0;

	deal_Card(deck, player);
	card_num_player++;
	player_val += deck->cardValues[card_num_player - 1];
	player->balance -= 100;
	deal_Card(deck, dealer);
	card_num_dealer++;
	dealer_val += deck->cardValues[card_num_dealer - 1];
	deal_Card(deck, player);
	card_num_player++;
	player_val += deck->cardValues[card_num_player - 1];
	deal_Card(deck, dealer);
	card_num_dealer++;
	dealer_val += deck->cardValues[card_num_dealer - 1];


	printf("player`s value: %d", player_val);
	printf("dealer`s value: %d", dealer_val);

	while (player_val < 21)
	{
		char action;
		printf("Choose action (HIT, STAND, DOUBLE DOWN): ");
		scanf("%c", action);

		if ((action = 'H') || (action = 'h'))
		{
			deal_Card(deck, player);
			card_num_player++;
			player_val += deck->cardValues[card_num_player - 1];
			printf("player`s value: %d", player_val);

			if (player_val > 21)
			{
				printf("Burst! %s loses.\n", player->name);
				return;
			}
		}
		else if ((action = 'S') || (action = 's'))
		{
			break;
		}
		else if ((action = 'D') || (action = 'd') && (player_val > 8) && (player_val < 12))
		{
			player->balance -= 100; // 더블 다운 시 두 배
			deal_Card(deck, player);
			card_num_player++;
			player_val += deck->cardValues[card_num_player - 1];
			printf("player`s value: %d", player_val);
		}
		else
		{
			printf("Wrong action !");
			continue;
		}
	}


}