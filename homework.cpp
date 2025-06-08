#include"homework.h"

void monoalphabeticCipher() {
	char secretKey[27];
	char text[100];

	printf("\n请输入密钥（输入0使用样例）:\n");
	cin >> secretKey;
	if (secretKey[0] == '0') {
		strcpy(secretKey, "jqschwartzflungdvpilemybox");
	}

	puts("\n字母替换表如下");
	puts("abcdefghijklmnopqrstuvwxyz");
	cout << secretKey;
	getchar();
	getchar();

	for (char opt ; ; ) {
		puts("\n----------------------");
		puts("请选择操作");
		puts("1 加密");
		puts("2 解密");
		puts("3 返回主菜单");
		puts("----------------------\n");

		cin >> opt;
		switch(opt) {
			case '1':
				printf("\n请输入明文\n");
				scanf("%s", text);

				printf("\n加密得密文为\n");
				for (int i = 0 ; i < strlen(text) ; i++) {
					putchar(secretKey[text[i] - 'a']);
				}
				getchar();
				getchar();
				break;
			case '2':
				printf("\n请输入密文\n");
				scanf("%s", text);

				printf("\n解密得明文为\n");
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
	puts("\n请输入密文(输入0使用样例):");
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
		puts("请选择操作");
		puts("1 频率分析");
		puts("2 上下文分析");
		puts("3 指定密钥字");
		puts("4 显示当前结果");
		puts("5 返回主菜单");
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
		puts("   单表代换辅助工具");
		puts("----------------------");
		puts("请选择功能");
		puts("1 单表代换加密和解密");
		puts("2 辅助破译单表代换密文");
		puts("3 退出");
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
