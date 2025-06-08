#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;

const int P = 193;
int hash[193];
int cipherTextLength;
char match[26], rematch[26];
char cipherText[1000], lastCipherText[1000];
char sampleCipherText[1000] = "HZSRNQC KLYY WQC FLO MFLWF OL ZQDN NSOZNJ WSKN LJ XZSRBJNF,WZSXZ GQV ZQHHNF OL OZN GLCO ZLFNCO HNHRN;NSOZNJ JNRQOSDNC LJ FNQJ KJSNFBC,WZSXZ SC XNJOQSFRV GLJN EFECEQR.ZN RSDNB QRLFN SF ZSC ZLECN SF CQDSRRN JLW,WZSOZNJ FLFN HNFNOJQONB.Q CSFYRN BLGNCOSX CEKKSXNB OL CNJDN ZSG.ZN PJNQMKQCONB QFB BSFNB QO OZN XREP,QO ZLEJC GQOZNGQOSXQRRV KSANB,SF OZN CQGN JLLG,QO OZN CQGN OQPRN,FNDNJ OQMSFY ZSC GNQRC WSOZ LOZNJ GNPNJC,GEXZ RNCC PJSFYSFY Q YENCO WSOZ ZSG;QFB WNFO ZLGN QO NAQXORV GSBFSYZO,LFRV OL JNOSJN QO LFXN OL PNB.ZN FNDNJ ECNB OZN XLCV XZQGPNJC WZSXZ OZN JNKLJG HJLDDSNC KLJ SOC KQDLEJNB GNPNJC.ZN HQCCNB ONF ZLEJC LEO LK OZN OWNFOV-KLEJSF CQDSRRN JLW,NSOZNJ SF CRNHSFY LJ GQMSFY ZSC OLSRNO.";
char dic[8][50][8]= {{},
	{"a","i","0"},
	{"am","an","as","at","do","if","in","is","it","me","no","of","to","0"},
	{"and","but","can","not","the","was","you","0"},
	{"also","ever","this","that","what","very","your","0"},
	{"after","could","there","where","which","0"},
	{"before","really","though","unless","0"},
	{"because","0"}
};

bool isUpperCase(char ch) {
	return (ch >= 'A' && ch <= 'Z');
}

int getHash(char ch[]) {
	int res = 0;
	for (int i = 0 ; i < strlen(ch) ; i ++) {
		res = (res * 27 + ch[i] - 'A')%P;
	}
	return res;
}

void frequencyAnalysis() {
	puts("\n-------------");
	puts("频率分析建议");
	puts("-------------");

	int letterSum = 0;
	int letters[26];
	double letterFrequency[26];
	memset(letterFrequency, 0, sizeof letterFrequency);
	for (int i = 0 ; i < cipherTextLength ; i ++) {
		if (isUpperCase(cipherText[i])) {
			letterSum ++;
			letterFrequency[cipherText[i] - 'A'] ++;
		}
	}
	for (int i = 0 ; i < 26 ; i ++) {
		letters[i] = i;
		letterFrequency[i] = letterFrequency[i] / (double)letterSum;
	}
	for (int i = 0 ; i < 26 ; i ++)
		for (int j = 0 ; j < i ; j ++) {
			if (letterFrequency[i] > letterFrequency[j]) {
				swap(letterFrequency[i],letterFrequency[j]);
				swap(letters[i],letters[j]);
			}
		}

	puts("字母频率统计");
	for (int i = 0 ; i < 26 ; i ++) {
		printf("%c:%.3lf\t", 'A' + letters[i], letterFrequency[i]);
		if ((i + 1) % 7 == 0) puts("");
	}
	puts("\n");

	puts("英文字母频率参考：e t a o i n s h r d l c u m w f g y p b v k j x q z");
	printf("高频字母%c可能对应e\n", 'A' + letters[0]);
	for (int i = 1 ; letterFrequency[i] > 0.08 || i < 3; i ++) {
		printf("%c", 'A' + letters[i]);
		if (letterFrequency[i + 1] > 0.08 || i < 2) cout <<',';
	}
	printf("可能对应t/a/o");
}

void matchDictionary(char word[]) {
	int len = strlen(word);
	int matchCount = 0;
	bool firstMatch = true;
	char line[100] = "";

	for (int i = 0 ; dic[len][i][0] != '0'; i ++) {
		bool isMatch = true;

		for (int j = 0 ; j < len ; j ++) {
			if (match[word[j] - 'A'] != '/' && match[word[j] - 'A'] != dic[len][i][j]) {
				isMatch = false;
				break;
			}
			if (rematch[dic[len][i][j] - 'a'] != '/' && rematch[dic[len][i][j] - 'a'] != word[j]) {
				isMatch = false;
				break;
			}
		}
		if (isMatch) {
			matchCount ++;
			if (matchCount > 4) return;
			if (firstMatch) {
				strcat(line, word);
				strcat(line, "可能为");
				strcat(line, dic[len][i]);
				firstMatch = false;
			} else {
				strcat(line, "、");
				strcat(line, dic[len][i]);
			}
		}
	}
	if (!firstMatch) puts(line);
}

void contextualAnalysis() {
	puts("\n--------------");
	puts("上下文分析建议");
	puts("--------------");

	memset(hash, 0, sizeof hash);

	for (int i = 0, j ; i < cipherTextLength ; i = j + 1) {
		char word[20] = "";
		while(!isUpperCase(cipherText[i]) && i < cipherTextLength) i ++;
		for (j = i + 1 ; isUpperCase(cipherText[j]) && j < cipherTextLength; j ++);
		strncpy(word, cipherText + i, j - i);

		if (hash[getHash(word)]) continue;
		else {
			hash[getHash(word)] = true;
			matchDictionary(word);
		}
	}
}

void addMatch() {
	puts("\n--------------");
	puts("请输入指定密钥");
	puts("--------------");
	puts("注：格式如A a，第二个字符为/表示取消该密钥字的指定");
	puts("输入0表示结束、输入/清除所有指定");

	char x, y;
	cin >> x;
	while(x != '0') {
		if (x == '/') {
			memset(match, '/', sizeof match);
			break;
		}
		cin >> y;
		match[x - 'A'] = y;
		rematch[y - 'a'] = x;
		cin >> x;
	}
}

void showResult() {
	for (int i = 0 ; i < cipherTextLength ; i ++) {
		if (isUpperCase(cipherText[i]) && match[cipherText[i] - 'A'] != '/') {
			cout << match[cipherText[i] - 'A'];
		} else cout << cipherText[i];
	}
	puts("");
}

