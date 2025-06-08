#include"homework.h"

void monoalphabeticCipher() {
	char secretKey[27];
	char text[100];

	printf("\n��������Կ������0ʹ��������:\n");
	cin >> secretKey;
	if (secretKey[0] == '0') {
		strcpy(secretKey, "jqschwartzflungdvpilemybox");
	}

	puts("\n��ĸ�滻������");
	puts("abcdefghijklmnopqrstuvwxyz");
	cout << secretKey;
	getchar();
	getchar();

	for (char opt ; ; ) {
		puts("\n----------------------");
		puts("��ѡ�����");
		puts("1 ����");
		puts("2 ����");
		puts("3 �������˵�");
		puts("----------------------\n");

		cin >> opt;
		switch(opt) {
			case '1':
				printf("\n����������\n");
				scanf("%s", text);

				printf("\n���ܵ�����Ϊ\n");
				for (int i = 0 ; i < strlen(text) ; i++) {
					putchar(secretKey[text[i] - 'a']);
				}
				getchar();
				getchar();
				break;
			case '2':
				printf("\n����������\n");
				scanf("%s", text);

				printf("\n���ܵ�����Ϊ\n");
				for (int i = 0 ; i < strlen(text) ; i++) {
					for (int j = 0 ; j < 26 ; j ++)
						if (secretKey[j] == text[i])
							putchar('a' + j);
				}
				getchar();
				getchar();
				break;
			case '3':
				return;
		}
	}
}

void cipherTextOnlyAttack() {
	while(getchar()!='\n');
	puts("\n����������(����0ʹ������):");
	gets(cipherText);
	if (cipherText[0] == '0') {
		strcpy(cipherText,sampleCipherText);
		printf("\n%s\n\n", cipherText);
	}
	cipherTextLength = strlen(cipherText);
	memset(match, '/', sizeof match);
	memset(rematch, '/', sizeof rematch);

	for (char opt ; ; ) {
		puts("----------------------");
		puts("��ѡ�����");
		puts("1 Ƶ�ʷ���");
		puts("2 �����ķ���");
		puts("3 ָ����Կ��");
		puts("4 ��ʾ��ǰ���");
		puts("5 �������˵�");
		puts("----------------------\n");

		cin >> opt;
		switch(opt) {
			case'1':
				frequencyAnalysis();
				break;
			case'2':
				contextualAnalysis();
				break;
			case'3':
				addMatch();
				break;
			case'4':
				showResult();
				break;
			case'5':
				return;
		}

		getchar();
		getchar();
	}
}

int main() {
	for (char opt ; ; ) {
		puts("----------------------");
		puts("   ���������������");
		puts("----------------------");
		puts("��ѡ����");
		puts("1 ����������ܺͽ���");
		puts("2 �������뵥���������");
		puts("3 �˳�");
		puts("----------------------\n");

		cin >> opt;
		switch(opt) {
			case'1':
				monoalphabeticCipher();
				break;
			case'2':
				cipherTextOnlyAttack();
				break;
			case'3':
				return 0;
		}

		getchar();
		getchar();
	}
}
