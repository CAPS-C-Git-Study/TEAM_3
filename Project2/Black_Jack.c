/*
���� 2 : BlackJack ���� ����

�˰��� ���� : BlackJack ������ ������ �÷��̾ ī�带 �޾ư��� 21�� ����� ���� ����� �����̴�.
ī��� 52���� ī�带 ����ϸ�, �� ī��� 2~10������ ���ڸ� ������ �ִ�. �׸� ī��(J,Q,K)�� 10���� ����ϸ�, A�� 1 �Ǵ� 11�� ����Ѵ�.
������ �÷��̾�� ���� 2���� ī�带 �޾Ƽ� �����ϸ�, �÷��̾�� ī�带 ��� ������(HIT), �׸� ������(STAND)�� ������ �� �ִ�.
ī�带 ��� �޴ٰ� 21�� �ʰ��ϸ�(BURST) �й��ϰ� �Ǹ�, 21�� ����� ���� ����� �¸��ϰ� �ȴ�.
�÷��̾ �¸��ϸ�, ���� �ݾ��� 2�踦 �ް� �Ǹ�, �й��ϸ� ���� �ݾ��� �Ҵ´�.
�÷��̾ ó�� �� ���� ī��� ����(21)�� �����, ���� �ݾ��� 1.5�踦 �ް� �ȴ�.
������ 17�̻��� ���� ���� ������ ī�带 ��� �޾ƾ� �Ѵ�.
������ ���Ǹ� ����, ���ø�, �ν������� ����� �������� �ʴ´�.
�ٸ�, ���� �ٿ� ����� �����Ѵ�.

���� �ٿ� �̶� : �÷��̾ ó���� ���� 2���� ī���� ���� 9, 10, 11�� �� ������ �� �ִ� �������, ī�带 �� �� �� �ް� ���� �ݾ��� 2��� �ø� �� �ִ�.
���Ŀ��� ī�带 ���� �� ������, ������ ���Ͽ� ���и� �����Ѵ�.

���� : BlackJack ������ �����Ͻÿ�.
������ 1���� �÷��̾�� 1���� ������ ����ȴ�.
�ʱ� �ݾ��� 10000������ �����ϸ�, ������ �����ϸ鼭 �ݾ��� ������Ų��.
�Ա�, ���, ������ �����ϴ� ����� �����Ѵ�.
�÷��̾��� �̸�, ��ȭ��ȣ�� �Է¹޴� ����� �����Ѵ�.
���� 52���� ī��� �����Ǹ�, ī��� 2~10, J, Q, K, A�� �����ȴ�.
ī��� �������� ������ ������, ī��� �ߺ��Ǿ� ������ �ʴ´�.
ī�带 �����ִ� ���, ī�带 �޴� ���, ī���� ���� ����ϴ� ����� �����Ѵ�.
52���� ī�带 ��� ����ϸ�, �ٽ� 52���� ī�带 ����Ѵ�.
�÷��̾ HIT, STAND, DOUBLE DOWN�� ������ �� �ֵ��� �����Ѵ�.

����ϴ� �ڷ� ���� : ����ü, �迭, ������
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

void initialize_Player(Player* player);//player �ʱ�ȭ
void initialize_Deck(Deck* deck);//deck �ʱ�ȭ
void shuffle_Deck(Deck* deck);//deck ����
void deal_Card(Deck* deck, Player* player);//card �����ֱ�
void play_Blackjack(Player* player, Player* dealer, Deck* deck);//blackjack ����

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
			player->balance -= 100; // ���� �ٿ� �� �� ��
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