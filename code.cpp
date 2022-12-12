#include<iostream>
#include<stdio.h>
#include<string>
#include<cstdlib>
#include<stdint.h>
#include<vector>
using namespace std;
string mixcolumn(string s);
string invmixcolumn(string s);
string GF(string s1,string s2,string s3,string s4,int i,uint8_t matrix[4][4]);
uint8_t multi(uint8_t a,uint8_t b);
unsigned int atoh(char *ap);
string htoa(uint8_t a);
string invmixcolumn(string ori);
uint8_t encrypt[4][4]={{0x2,0x3,0x1,0x1},{0x1,0x2,0x3,0x1},{0x1,0x1,0x2,0x3},{0x3,0x1,0x1,0x2}};
uint8_t decrypt[4][4]={{0xe,0xb,0xd,0x9},{0x9,0xe,0xb,0xd},{0xd,0x9,0xe,0xb},{0xb,0xd,0x9,0xe}};

int main(){
	string s;
	cin>>s;
//	s="87f24d976e4c90ec46e74AC3A68CD895";
	s=mixcolumn(s);
	cout<<"------after mixcolumns------"<<endl;
	cout<<s<<endl;
	s=invmixcolumn(s);
	cout<<"------after invmixcolumns------"<<endl;
	cout<<s<<endl;
}
string invmixcolumn(string ori){
	string s_mat[4][4]={{"","","",""},{"","","",""},{"","","",""},{"","","",""}};
	string res_mat[4][4]={{"","","",""},{"","","",""},{"","","",""},{"","","",""}};
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			s_mat[i][j]=ori.substr((i*4+j)*2,2);
		}
	}
	string res;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			res_mat[i][j]=GF(s_mat[0][j],s_mat[1][j],s_mat[2][j],s_mat[3][j],i,decrypt);
			res+=res_mat[i][j];
		}
	}
	return res;
}
string mixcolumn(string ori){
	string s_mat[4][4]={{"","","",""},{"","","",""},{"","","",""},{"","","",""}};
	string res_mat[4][4]={{"","","",""},{"","","",""},{"","","",""},{"","","",""}};
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			s_mat[i][j]=ori.substr((i*4+j)*2,2);
		}
	}
	string res;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			res_mat[i][j]=GF(s_mat[0][j],s_mat[1][j],s_mat[2][j],s_mat[3][j],i,encrypt);
			res+=res_mat[i][j];
		}
	}
	return res;
}
string GF(string s1,string s2,string s3,string s4,int row, uint8_t matrix[4][4]){
	uint8_t a = atoh(const_cast<char*>(s1.c_str()));
	uint8_t b = atoh(const_cast<char*>(s2.c_str()));
	uint8_t c = atoh(const_cast<char*>(s3.c_str()));
	uint8_t d = atoh(const_cast<char*>(s4.c_str()));
	uint8_t t1,t2,t3,t4;
	t1=multi(matrix[row][0],a);
	t2=multi(matrix[row][1],b);
	t3=multi(matrix[row][2],c);
	t4=multi(matrix[row][3],d);
	uint8_t T = t1^t2^t3^t4;
	return htoa(T);
}
uint8_t multi(uint8_t a,uint8_t b){
	uint8_t res,x8=0x1b,x9=(x8<<1),x10=(x8<<2);
	uint16_t temp=0x0;
	if(a==0xe){
		temp=(b<<1)^(b<<2)^(b<<3);
		if(temp>0x400)
			temp=(temp-0x0400)^x10;
		if(temp>0x200)
			temp=(temp-0x0200)^x9;
		if(temp>0x100)
			temp=(temp-0x0100)^x8;
		res=temp;	
	}
	else if(a==0xb){
		temp=(b<<3)^(b<<1)^b;
		if(temp>0x400)
			temp=(temp-0x0400)^x10;
		if(temp>0x200)
			temp=(temp-0x0200)^x9;
		if(temp>0x100)
			temp=(temp-0x0100)^x8;
		res=temp;
	}
	else if(a==0xd){
		temp=(b<<3)^(b<<2)^b;
		if(temp>0x400)
			temp=(temp-0x0400)^x10;
		if(temp>0x200)
			temp=(temp-0x0200)^x9;
		if(temp>0x100)
			temp=(temp-0x0100)^x8;
		res=temp;
	}
	else if(a==0x9){
		temp=(b<<3)^b;
		if(temp>0x400)
			temp=(temp-0x0400)^x10;
		if(temp>0x200)
			temp=(temp-0x0200)^x9;
		if(temp>0x100)
			temp=(temp-0x0100)^x8;
		res=temp;
		
	}
	else if(a==0x3){
		temp=(b<<1)^b;
		if(temp>=0x0100)
			temp=(temp-0x0100)^x8;
		res=temp;
	}
	else if(a==0x2){
		temp=(b<<1);
		if(temp>=0x0100)
			temp=(temp-0x0100)^x8;
		res=temp;
	}
	else{
		res=b;
	}
	return res;
}
string htoa(uint8_t num){
	string res;
	char buffer [33];
	itoa(num,buffer,16);
	res=buffer;
	return res;
}
unsigned int atoh(char *ap){
	register char *p;
	register unsigned int n;
	register int digit,lcase;
	p = ap;
	n = 0;
	while(*p == ' ' || *p == '	')
		p++;
	if(*p == '0' && ((*(p+1) == 'x') || (*(p+1) == 'X')))
		p+=2;

	while ((digit = (*p >= '0' && *p <= '9')) ||
		(lcase = (*p >= 'a' && *p <= 'f')) ||
		(*p >= 'A' && *p <= 'F')) {
		n *= 16;
		if (digit)	n += *p++ - '0';
		else if (lcase)	n += 10 + (*p++ - 'a');
		else		n += 10 + (*p++ - 'A');
	}
	return(n);
}
