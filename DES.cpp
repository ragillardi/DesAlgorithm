#include<iostream>
#include<algorithm>
#include<math.h>
#include<stdio.h>
#include<cstdlib>
using namespace std;

int shiftschedule[16]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

int ip[64]={
	58,50,42,34,26,18,10,2,
	60,52,44,36,28,20,12,4,
	62,54,46,38,30,22,14,6,
	64,46,48,40,32,24,16,8,
	57,49,41,33,25,17,9,1,
	59,51,43,35,27,19,11,3,
	61,53,45,37,29,21,13,5,
	63,55,47,39,31,23,15,7
};

int inverseip[64]{
	40,8,48,16,56,24,64,32,
	39,7,47,15,55,23,63,31,
	38,6,46,14,54,22,62,30,
	37,5,45,13,53,21,61,29,
	36,4,44,12,52,20,60,28,
	35,3,43,11,51,19,59,27,
	34,2,42,10,50,18,58,26,
	33,1,41,9,49,17,57,25
};

string sbox[4][16]={
	"1110",	"0100",	"1101",	"0001",	"0010",	"1111",	"1011",	"1000",	"0011",	"1010",	"0110",	"1100",	"0101",	"1001",	"0000",	"0111",
	"0000",	"1111",	"0111",	"0100",	"1110",	"0010",	"1101",	"0001",	"1010",	"0110",	"1100",	"1011",	"1001",	"0101",	"0011",	"1000",
	"0100",	"0001",	"1110",	"1000",	"1101",	"0110",	"0010",	"1011",	"1111",	"1100",	"1001",	"0111",	"0011",	"1010",	"0101",	"0000",
	"1111",	"1100",	"1000",	"0010",	"0100",	"1001",	"0001",	"0111",	"0101",	"1011",	"0011",	"1110",	"1010",	"0000",	"0110",	"1101"
};

int e_table[48]={
	32,	1,	2,	3,	4,	5,
	4,	5,	6,	7,	8,	9,
	8,	9,	10,	11,	12,	13,
	12,	13,	14,	15,	16,	17,
	16,	17,	18,	19,	20,	21,
	20,	21,	22,	23,	24,	25,
	24,	25,	26,	27,	28,	29,
	28,	29,	30,	31,	32,	1		
};

int pc1[56]={
	57,	49,	41,	33,	25,	17,	9,
	1,	58,	50,	42,	34,	26,	18,
	10,	2,	59,	51,	43,	35,	27,
	19,	11,	3,	60,	52,	44,	36,
	63,	55,	47,	39,	31,	23,	15,
	7,	62,	54,	46,	38,	30,	22,
	14,	6,	61,	53,	45,	37,	29,
	21,	13,	5,	28,	20,	12,	4	
};

int pc2[48]={
	14, 17, 11, 24, 1, 5, 3, 28,
	15, 6, 21, 10, 23, 19, 12, 4,
	26, 8, 16, 7, 27, 20, 13, 2,
	41, 52, 31, 37,47, 55, 30,40,
	41, 45, 33, 48, 44, 49, 39, 56,
	34, 53, 46, 42, 50, 36, 29, 32
};

int pbox[32]={
	16,7,20,21,29,12,28,17,
	1,15,23,26,5,18,31,10,
	2,8,24,14,32,27,3,9,
	19,13,30,6,22,11,4,25
};

string padding(string kalimat){
	while(kalimat.length()%8!=0){
		kalimat+='*';
	}
	return kalimat;
}

string converttobinary(int bilangan){
	string s;
	while(bilangan!=0){
		if(bilangan%2==0){
			s+="0";
		}
		else s+="1";
		bilangan=bilangan/2;
	}
	while (s.length()!=8) s+="0";
	string c = s;
	for (int i=0;i<s.length();i++){
		s[i]=c[s.length()-1-i];
	}
	return s;
}

int converttodec(string biner){
	int n=0;
	int c=biner.length()-1;
	for(int i=0;i<biner.length();i++){
		if(biner[i]=='1') n+=pow(2,c);
		c--;
	}
	return n;
}

void converttotext(string biner){
	int n = biner.length();
	int m = n/8;
	string s[m];
	for(int i=0;i<n;i=i+8){
		string t;
		t+=biner[i];t+=biner[i+1];t+=biner[i+2];t+=biner[i+3];
		t+=biner[i+4];t+=biner[i+5];t+=biner[i+6];t+=biner[i+7];
		s[i/8]=t;
	//	cout<<s[i/8]<<endl;
	}
	char u[m];
	for(int i=0;i<m;i++){
		u[i]=converttodec(s[i]);
		cout<<u[i];
	}
//	return u;	
}

string tobyte(string kata){
	string s;
	for(int i=0;i<kata.length();i++){
		s+=converttobinary(kata[i]);
		//s+=' ';
	}
	return s;
}

void split(string kata, string &kiri, string &kanan){
	int n=kata.length()/2;
	for(int i=0;i<n;i++){
		kiri+=kata[i];
		kanan+=kata[i+n];
	}
}

string permutation(int a[],int n,string s){
	string c;
	for(int i=0;i<n;i++){
		c+=s[a[i]-1];
	}
	return c;
}

string leftshift(string key, int round){
	int n = shiftschedule[round-1];
	int m = key.length();
	if(n==1){
		char temp = key[0];
		for(int j=0;j<m-1;j++){
			key[j]=key[j+1];
		}
		key[m-1]=temp;
	}
	else if(n==2){
		char temp1=key[0];
		char temp2=key[1];
		for(int j=0;j<m-2;j++){
			key[j]=key[j+2];
		}
		key[m-2]=temp1;
		key[m-1]=temp2;
	}
	return key;
}

string merge(string kiri, string kanan){
	return kiri + kanan;
}

string exor(string a, string b, int n){
	string temp;
	for(int i;i<n;i++){
		if(a[i]==b[i]){
			temp+="0";
		}
		else temp+="1";
	}
	return temp;
}

string s_box(string kata){
	string s;
	for(int i=0;i<48;i=i+6){
		string a,b;
		a=kata[i];a+=kata[i+5];
		int a1 = converttodec(a);
		b=kata[i+1];b+=kata[i+2];b+=kata[i+3];b+=kata[i+4];
		int b1 = converttodec(b);
		s+=sbox[a1][b1];
	}
	return s;
}

main(){
	string text;
	string key;
	cout<<"Text(<=8 karakter): ";cin>>text;
	cout<<"Key(8 karakter): ";cin>>key;
	string s = tobyte(padding(text));
	string s1= permutation(ip,64,s);
	key = tobyte(key);
	string k = permutation(pc1,56,key);
	cout<<"Plaintext\t"<<s<<endl;
	cout<<"I. Permuation\t"<<s1<<endl;
	cout<<"Key\t\t"<<k<<endl<<endl;
	string c, d;
	split(k,c,d);

	string l, r;
	split(s1,l,r);
	string m;
	string roundkey[16];
	cout<<"Enkripsi"<<endl;
	for(int i=0;i<16;i++){
		cout<<"Round "<<i+1<<endl;
		
		c=leftshift(c,i+1);
		d=leftshift(d,i+1);
		m=merge(c,d);
		roundkey[i]=m;
		
		cout<<"Round Key\t"<<m<<endl;
		m=permutation(pc2,48,m);
		cout<<"Permutation Key\t"<<m<<endl;
		string temp = r;
		
		r = permutation(e_table,48,r);
		cout<<"Expansion R \t"<<r<<endl;
		
		r = exor(m,r,48);
		cout<<"Xor R w/ Key\t"<<r<<endl;
		
		r= s_box(r);
		cout<<"SBox R\t\t"<<r<<endl;
		
		r= permutation(pbox,32,r);
		cout<<"Pbox R\t\t"<<r<<endl;
		r= exor(l,r,32);
		cout<<"Xor R w/ L\t"<<r<<endl;
		l= temp;
		cout<<"Replace L\t"<<l<<endl;
		cout<<"Round Result\t"<<l<<r<<endl<<endl;
	}
	
	string ciphertext = merge(l,r);
	ciphertext=permutation(inverseip,64,ciphertext);
//	cout<<"Ciphertext\t";
//	converttotext(ciphertext);
	string ciphertext1= ciphertext;
//	cout<<endl<<s<<endl<<ciphertext<<endl;
	
	system("PAUSE");
	system("CLS");
	cout<<"Dekripsi"<<endl;
	ciphertext=permutation(ip,64,ciphertext);
	split(ciphertext,l,r);
	for(int i=0;i<16;i++){
		cout<<"Round "<<i+1<<endl;
		
		cout<<"Round Key\t"<<roundkey[15-i]<<endl;
		//cout<<"ROund key\t"<<3-i<<endl;
		m=permutation(pc2,48,roundkey[15-i]);
		cout<<"Permutation Key\t"<<m<<endl;
		
		string temp = l;
		
		l = permutation(e_table,48,l);
		cout<<"Expansion L \t"<<r<<endl;
		
		l = exor(m,l,48);
		cout<<"Xor L w/ Key\t"<<r<<endl;
		
		l = s_box(l);
		cout<<"SBox L\t\t"<<r<<endl;
		
		l = permutation(pbox,32,l);
		cout<<"Pbox L\t\t"<<r<<endl;
		l = exor(l,r,32);
		cout<<"Xor L w/ R\t"<<r<<endl;
		r = temp;
		cout<<"Replace R\t"<<r<<endl;
		cout<<"Round Result\t"<<l<<r<<endl<<endl;
	}
	string plaintext= merge(l,r);
	plaintext = permutation(inverseip,64,plaintext);
	system("PAUSE");
	system("CLS");
	cout<<endl<<"Plaintext Awal\t";//cout<<s<<endl;
	//cout<<"\t\t";
	converttotext(s);cout<<endl;
	cout<<"Hasil Enkripsi\t";//cout<<ciphertext1<<endl;
	//cout<<"\t\t";
	converttotext(ciphertext1);cout<<endl;
	cout<<"Hasil Dekripsi\t";//cout<<plaintext<<endl;
	//cout<<"\t\t";
	converttotext(plaintext);cout<<endl;
}
