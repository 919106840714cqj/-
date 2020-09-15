#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<algorithm>
#include <cstring>
#include<iomanip>
//char 1为大王 2为小王 3为红心 4为方块 5为梅花 6是红桃 
using namespace std; 

bool cmp(int x,int y)
{
	return x%13>y%13;//按牌的点数降序排列
}

struct oncard
{
	int data;
	struct oncard* next;    //数据结构 
	struct oncard* last; 
};

void givecard(int (*player)[27])
{
	srand(time(0));
	int i;
	int poker[108];//存0~103表示的数字牌，104~107表示4张王牌 
	for(i=0;i<108;i++)
	{
		poker[i]=i;
	}
//从poker数组中，每次随机取出1张牌，按顺序发给4个玩家
	for(i=0;i<108;i++)
	{
		int idx = rand()%(108-i); //随机取一张牌
		if(i/27==0) (*player)[i]=poker[idx];
		if(i/27==1) (*player)[i]=poker[idx];
		if(i/27==2) (*player)[i]=poker[idx];
		if(i/27==3) (*player)[i]=poker[idx];
//取得牌依次为第1个人第1张，第2个人第1张，第3个人第1张，第4个人第1张
		poker[idx]=poker[107-i];//取完牌把最后一个牌移到前面避免随机数重复 
//1个人第2张，2个人第2张，3个人第2张 ………………
	}
}

void input(oncard *&b, int *a)
{
	oncard* end;					
	b=(oncard*)malloc(sizeof(oncard));			
    end=b;
    for (int j=0;j<27;j++)
	{
        oncard* tmp=(oncard*)malloc(sizeof(oncard));  //每次都新分配一个内存空间 
        tmp->data=a[j];					
        end->next=tmp;
        tmp->last=end;
		end=tmp;
    }
    end->next=b;
    b->last=NULL;
}

void output(oncard *b, char *p)
{ 
		char flower[6]={1,2,3,4,5,6};
		cout<<endl;
		oncard *gamer=b->next;
		int k1,k2,k3,k4;
		k1=k2=k3=k4=0;
		int fo[27]={0}; //梅花 
		int rh[27]={0}; //红心
		int bk[27]={0};	//方块 
		int rp[27]={0};	//红桃 
		while(gamer!=b)   //char 1为大王 2为小王 3为红心 4为方块 5为梅花 6是黑桃  
		{ 		
			if (gamer->data==106||gamer->data==107) cout<<flower[0]<<endl;
			else if (gamer->data==104||gamer->data==105) cout<<flower[1]<<endl;
			gamer=gamer->next;		
		}
		gamer=b->next;
		while(gamer!=b)
		{  //黑桃 方块 红心 梅花 
			if (gamer->data<104&&(gamer->data/13==2||gamer->data/13==6))
			{
				cout<<flower[2]<<p[gamer->data%13]<<' '; //红心 
			} 
			else if (gamer->data<104&&(gamer->data/13==1||gamer->data/13==5))
			{
				cout<<flower[3]<<p[gamer->data%13]<<' '; //方块 
			} 
			else if (gamer->data<104&&(gamer->data/13==3||gamer->data/13==7))
			{
				cout<<flower[4]<<p[gamer->data%13]<<' '; //梅花 
			} 
			else if (gamer->data<104&&(gamer->data/13==0||gamer->data/13==4))
			{
				cout<<flower[5]<<p[gamer->data%13]<<' '; //黑桃 
			} 
		gamer=gamer->next;		//gamer指向b的下一个的下一个 
		}cout<<endl;
}

void  deletep(oncard *b,char *cs,char *n,int &outcard)
{ 
	int k1,k2,num;
	int a=0;
	int sp=0;
	int zh1[30]={ };
	int zh2[30]={ };
	if(strlen(cs)==0)
	{
		cout<<"出牌不符合规则，请玩家重新出牌"<<endl;
		outcard=0;
	} 
	for(int j=0;j<strlen(cs);j=j+3)
	{
		if (cs[j]=='x'&&cs[j+1]=='w')
		{
			k1=104;
			k2=105;
		}
		else if(cs[j]=='d'&&cs[j+1]=='w')
		{
			k1=106;
			k2=107;
		}
		else num=cs[j]-97;
		for (int i=0;i<13;i++)
		{
			if (cs[j+1]==n[i])
			{	
				
				k1=i+(num)*13;
				k2=i+(num+4)*13; 
			}
		}
		zh1[a]=k1;
		zh2[a]=k2;
		a++;
	}
		
		for(int j=0;j<a;j++)
			{	
				for (oncard* i=b->next;i!=b;i=i->next)
				{
					if (i->data==zh1[j]||i->data==zh2[j])
					{ 
						sp=1;
						break;
					}sp=0;
				}
				if(sp==0)
				{
					cout<<"出牌不符合规则，请玩家重新出牌"<<endl;
					outcard=0;
		    	break;
				}
			}
		if(sp==1)
			{	
				for(int j=0;j<a;j++)
				{
					for (oncard* i=b->next;i!=b;i=i->next)
					{
						if(i->data==zh1[j]||i->data==zh2[j])
						{
							i->last->next=i->next;
							i->next->last=i->last;
							free(i);
							break;
						}
					}
				}	
			}			
}

void search_stat(oncard *b,char *p,char *flower)
{
	oncard *gamer=b->next;
	oncard *search=b->next;
	char k1,k2,k3,k4,k5;
	int  c1;
	int point;
	int jishu=0;
	int change; 
	for(;gamer!=b;gamer=gamer->next)
	{
		point=gamer->data%13;
		k1=p[gamer->data%13];
		c1=gamer->data/13;
		if(c1==0||c1==4) change=5; //黑桃 
		if(c1==1||c1==5) change=3; //方块 
		if(c1==2||c1==6) change=2; //红心 
		if(c1==3||c1==7) change=4; //梅花 
		if(c1>0) c1=c1-4;
	
		for(;search!=b;search=search->next)
		{
			if((search->data%13-point==1||point-search->data%13==12)&&(search->data/13==c1||search->data/13==c1+4))
			{
				k2=p[search->data%13];
				break;	
			}
			else k2=0;
		}search=b->next;
		for(;search!=b;search=search->next)
		{
			if((search->data%13-point==2||point-search->data%13==11)&&(search->data/13==c1||search->data/13==c1+4))
			{
				k3=p[search->data%13];
				break;	
			}
			else k3=0;
		}search=b->next;
		for(;search!=b;search=search->next)
		{
			if((search->data%13-point==3||point-search->data%13==10)&&(search->data/13==c1||search->data/13==c1+4))
			{
				k4=p[search->data%13];
				break;	
			}
			else k4=0;
		}search=b->next;
		for(;search!=b;search=search->next)
		{
			if((search->data%13-point==4||point-search->data%13==9)&&(search->data/13==c1||search->data/13==c1+4))
			{
				k5=p[search->data%13];
				break;	
			}
			else k5=0;
		}search=b->next;
		if(k2!=0&&k3!=0&&k4!=0&&k5!=0)
		{
			if(k1=='J'||k1=='Q'||k1=='K') break;
			cout<<flower[change]<<k1<<k2<<k3<<k4<<k5<<endl;
			jishu=1;
		}
	}
	if(jishu==0) cout<<"无同花顺"<<endl;
	cout<<endl;
}

void shuchu(oncard *a, oncard *b, oncard *c, oncard *d,char *p,char *flower)
{
	cout<<endl;
	cout<<"玩家一";                          
    output(a, p);
    cout<<"对于玩家一：" ;
	search_stat(a,p,flower);
    cout<<endl<<"玩家二";
    output(b, p);
	cout<<"对于玩家二：" ;
	search_stat(b,p,flower);
    cout<<endl<<"玩家三";
    output(c, p);
    cout<<"对于玩家三：" ;
	search_stat(c,p,flower);
    cout<<endl<<"玩家四";
    output(d, p);
    cout<<"对于玩家四：" ;
	search_stat(d,p,flower);
}

void second(int *rank,int *team,int *add)
{
	int t=0;
	int cord1=team[0];
	int cord2=team[1];
	if(rank[0]==1&&rank[1]==3)
	{
		cout<<"第一名为玩家1" <<endl;
		cout<<"第二名为玩家3" <<endl;
		cout<<"玩家一三双下" <<endl; 
		t=1;
		add[0]=add[0]+3;
	}
	if(rank[0]==3&&rank[1]==1)
	{
		cout<<"第一名为玩家3" <<endl;
		cout<<"第二名为玩家1" <<endl;
		cout<<"玩家一三双下" <<endl; 
		t=1;
		add[0]=add[0]+3;
	}
	if(rank[0]==2&&rank[1]==4)
	{
		cout<<"第一名为玩家2" <<endl;
		cout<<"第二名为玩家4" <<endl;
		cout<<"玩家二四双下" <<endl; 
		t=1;
		add[1]=add[1]+3;
	}
	if(rank[0]==4&&rank[1]==2)
	{
		cout<<"第一名为玩家4" <<endl;
		cout<<"第二名为玩家2" <<endl;
		cout<<"玩家二四双下" <<endl; 
		t=1;
		add[1]=add[1]+3;
	}
	if(t==0)
	{
	int a[3];
	for(int j=0;j<3;j++){
		a[j]=rank[j];
	}
	sort(a,a+3);
	if(a[2]<4)
	rank[3]=4;
	if(a[0]>1)
	rank[3]=1;
	if(a[2]-a[1]==2)
	rank[3]=3;
	if(a[1]-a[0]==2)
	rank[3]=2;
	cout<<"第一名为玩家" <<rank[0]<<endl; 
	cout<<"第二名为玩家" <<rank[1]<<endl; 
	cout<<"第三名为玩家" <<rank[2]<<endl; 
	cout<<"第四名为玩家" <<rank[3]<<endl; 
	}
	if(rank[0]==1&&rank[2]==3) add[0]=add[0]+2;
	if(rank[0]==1&&rank[3]==3) add[0]=add[0]+1;
	if(rank[0]==3&&rank[2]==1) add[0]=add[0]+2;
	if(rank[0]==3&&rank[3]==1) add[0]=add[0]+1;
	if(rank[0]==2&&rank[2]==4) add[1]=add[1]+2;
	if(rank[0]==2&&rank[3]==4) add[1]=add[1]+1;
	if(rank[0]==4&&rank[2]==2) add[1]=add[1]+2;
	if(rank[0]==4&&rank[3]==2) add[1]=add[1]+1;
	
	team[0]=team[0]+add[0];
	team[1]=team[1]+add[1];
	if(team[0]!=cord1&&team[1]==cord2) cout<<"该局结束，玩家一三胜利，进"<<add[0]<<"点"<<endl;
	if(team[1]!=cord2&&team[0]==cord1) cout<<"该局结束，玩家二四胜利，进"<<add[1]<<"点"<<endl;
}

void repeat(int *team,int *add,char *p)
{
	char n1[13]={'2','4','5','6','7','8','9','T','J','Q','K','A','3'};  //打3 
	char n2[13]={'2','3','5','6','7','8','9','T','J','Q','K','A','4'}; 	//打4 
	char n3[13]={'2','3','4','6','7','8','9','T','J','Q','K','A','5'}; 	//打5 
	char n4[13]={'2','3','4','5','7','8','9','T','J','Q','K','A','6'}; 	//打6 
	char n5[13]={'2','3','4','5','6','8','9','T','J','Q','K','A','7'}; 	//打7 
	char n6[13]={'2','3','4','5','6','7','9','T','J','Q','K','A','8'}; 	//打8 
	char n7[13]={'2','3','4','5','6','7','8','T','J','Q','K','A','9'}; 	//打9 
	char n8[13]={'2','3','4','5','6','7','8','9','J','Q','K','A','T'}; 	//打T 
	char n9[13]={'2','3','4','5','6','7','8','9','T','Q','K','A','J'}; 	//打J 
	char n10[13]={'2','3','4','5','6','7','8','9','T','J','K','A','Q'}; //打Q
	char n11[13]={'2','3','4','5','6','7','8','9','T','J','Q','A','K'}; //打K 
	char n12[13]={'2','3','4','5','6','7','8','9','T','J','Q','K','A'}; //打A 
	if((team[0]==1&&add[0]!=0)||(team[1]==1&&add[1]!=0)) strcpy(p,n1);
	if((team[0]==2&&add[0]!=0)||(team[1]==2&&add[1]!=0)) strcpy(p,n2);
	if((team[0]==3&&add[0]!=0)||(team[1]==3&&add[1]!=0)) strcpy(p,n3);
	if((team[0]==4&&add[0]!=0)||(team[1]==4&&add[1]!=0)) strcpy(p,n4);
	if((team[0]==5&&add[0]!=0)||(team[1]==5&&add[1]!=0)) strcpy(p,n5);
	if((team[0]==6&&add[0]!=0)||(team[1]==6&&add[1]!=0)) strcpy(p,n6);
	if((team[0]==7&&add[0]!=0)||(team[1]==7&&add[1]!=0)) strcpy(p,n7);
	if((team[0]==8&&add[0]!=0)||(team[1]==8&&add[1]!=0)) strcpy(p,n8);
	if((team[0]==9&&add[0]!=0)||(team[1]==9&&add[1]!=0)) strcpy(p,n9);
	if((team[0]==10&&add[0]!=0)||(team[1]==10&&add[1]!=0)) strcpy(p,n10);
	if((team[0]==11&&add[0]!=0)||(team[1]==11&&add[1]!=0)) strcpy(p,n11);
	if((team[0]==12&&add[0]!=0)||(team[1]==12&&add[1]!=0)) strcpy(p,n12);
	
	add[0]=add[1]=0;
}

void onetime(oncard *p1, oncard *p2, oncard *p3, oncard *p4,char *p,char *flower,int *team,int *add)
{
	
	int card1=27,card2=27,card3=27,card4=27,people; //people表示打牌的人
	int cord=0;
	int rank[4]={0};
	char kong[1]={ };
  	cin.getline(kong,1);
  	people=rand()%4;
    for(;(card1||card3)&&(card2||card4);people+=1)
	{   
		char cs[100]={ };
    	int number=0; //d是梅花，c是红心，b是方块 ，a是黑桃
    	cout<<"提示："<<"dw是"<<flower[0]<<' ';
    	cout<<"xw是"<<flower[1]<<' ';
    	cout<<"d是"<<flower[4]<<' ';
		cout<<"c是"<<flower[2]<<' ';
		cout<<"b是"<<flower[3]<<' ';
		cout<<"a是"<<flower[5]<<' '<<endl;
    	if (people%4==1)
		{
			if(card1==0)
			{
				rank[cord]=1;
				cord++;
				cout<<"该玩家已经走完，请下一家出牌"<<endl;
				continue; 	
			} 
    		
    		if(card1!=0)
			{
    		cout<<"玩家一出牌:"<<endl;
    		cin.getline(cs,100);
    		if(cs[0]=='n'&&cs[1]=='o')
			{
				cout<<"玩家一不要，到下一家"<<endl;
				continue; 
			}
    		for(int i=0;i<100;i++)
			{
				if(cs[i]==32) number++;
			}
			int outcard;	
			outcard=number+1;
			deletep(p1,cs,p,outcard);
    		card1-=outcard;
    		if (outcard==0) people-=1;
    		else shuchu(p1,p2,p3,p4,p,flower);
    		cout<<endl;
    		continue;
			}
		}
		
		if (people%4==2)
		{  		
    		if(card2==0)
			{	
				rank[cord]=2;
				cord++;
				cout<<"该玩家已经走完，请下一家出牌"<<endl;
				continue; 	
			} 
			if(card2!=0)
			{
    		cout<<"玩家二出牌:"<<endl;
    		cin.getline(cs,100);
    		if(cs[0]=='n'&&cs[1]=='o')
			{
				cout<<"玩家二不要，到下一家"<<endl;
				continue; 
			}
    		for(int i=0;i<100;i++)
			{
				if(cs[i]==32) number++;
			}
    		int outcard;
    		outcard=number+1;
    		card2-=outcard;
    		deletep(p2,cs,p,outcard);
    		if (outcard==0) people-=1;
    		else shuchu(p1,p2,p3,p4,p,flower);
    		cout<<endl;
    		continue;
			}
		}
		
		if (people%4==3)
		{
    		if(card3==0)
			{
				rank[cord]=3;
				cord++;
				cout<<"该玩家已经走完，请下一家出牌"<<endl;
				continue; 	
			} 
			if(card3!=0)
			{
				
    		cout<<"玩家三出牌:"<<endl;
    		cin.getline(cs,100);
    		if(cs[0]=='n'&&cs[1]=='o')
			{
				cout<<"玩家三不要，到下一家"<<endl;
				continue; 
			}
    		for(int i=0;i<100;i++)
			{
				if(cs[i]==32) number++;
			}
    		int outcard;
    		outcard=number+1;
    		card3-=outcard;
    		deletep(p3,cs,p,outcard);
    		if (outcard==0) people-=1;
    		else shuchu(p1,p2,p3,p4,p,flower);
    		cout<<endl;
    		continue;
			}
		}
		
		if (people%4==0)
		{
    		if(card4==0)
			{	
				rank[cord]=4;
				cord++;
				cout<<"该玩家已经走完，请下一家出牌"<<endl;
				continue;	
			} 
			if(card4!=0)
			{
    		cout<<"玩家四出牌:"<<endl;
    		cin.getline(cs,100);
    		if(cs[0]=='n'&&cs[1]=='o')
			{
				cout<<"玩家四不要，到下一家"<<endl;
				continue; 
			}
    		for(int i=0;i<100;i++)
			{
				if(cs[i]==32) number++;
			}
    		int outcard;
    		outcard=number+1;
			deletep(p4,cs,p,outcard);
    		card4-=outcard;
    		if (outcard==0) people-=1;
    		else shuchu(p1,p2,p3,p4,p,flower);
    		cout<<endl;
    		continue;
			}
		}
	}second(rank,team,add);
}

void auto_out(oncard *b,int *a,int i)
{
	int k;
	int outcard;
	k=rand()%25;
	int nu=a[i];
	a[i]=nu-k; 
	for(int i=0;i<k;i++)
	{
		for(oncard *t=b->next;t!=b;t++)
		{
				t->last->next=t->next;
				t->next->last=t->last;
				free(t);
				break;	
		}
	}	
}

void status(oncard *p1, oncard *p2, oncard *p3, oncard *p4,char *p,char *flower,int *team,int *add)
{
	int pause;
	int a[4]={27,27,27,27};
	int tt1=0;
	int tt2=0;
	int tt3=0;
	int tt4=0;
	char kk[13]={'2','3','4','5','6','7','8','9','T','J','Q','K','A'};
	
	
	cout<<"请输入相应按键实现相应功能"<<endl;;
	cout<<"0代表出牌,开始牌局" <<endl; 
	cout<<"1代表自动随机出牌" <<endl;
	cout<<"2查询两队各打到几"<<endl; 
	cin>>pause; 
	
	int rank[4]={0};
	int num=0;
	
	if(pause==0)
	{ 
	onetime(p1,p2,p3,p4,p,flower,team,add);
	int anjian;
	int play_A=0;
	int play_A1=0;
	int pp1=0;
	int pp2=0;
	while(1)
	{
		cout<<"请输入相应按键实现相应功能"<<endl;
		cout<<"3代表开始下一轮发牌"<<endl;
		cout<<"4代表结束游戏" <<endl;
		if(team[0]>=12)
		{
			team[0]=12;
			if(pp1!=0)
			{
				if(add[0]==1) play_A++;
				if(add[0]>1)
				{
					cout<<"玩家一，三胜利"<<endl;
					break;
				}
				if(play_A==3)
				{
					team[0]=0;
					play_A=0;
				}
			}pp1++;
		}
	
		if(team[1]>=12)
		{
			team[1]=12;
			if(pp2!=0)
			{
				if(add[1]==1) play_A1++;
				if(add[1]>1)
				{
					cout<<"玩家二，四胜利"<<endl;
					break;
				}
				if(play_A1>=3) 
				{
					team[1]=0;
					play_A1=0;
				}
			}pp2++;
		}
		cin>>anjian;
	
		if(anjian==3)
		{
			oncard *p1, *p2, *p3, *p4;
			char flower[6]={1,2,3,4,5,6};
			int i,j,k;
			int player[4][27];//存4个玩家的牌
	
			givecard(player);
	
			sort(player[0],player[0]+27,cmp);
			sort(player[1],player[1]+27,cmp);
			sort(player[2],player[2]+27,cmp);
			sort(player[3],player[3]+27,cmp);

			input(p1,player[0]);
			input(p2,player[1]);
			input(p3,player[2]);
			input(p4,player[3]);
	
			repeat(team,add,p);
			shuchu(p1,p2,p3,p4,p,flower);
	
			cout<<endl;
	
			status(p1,p2,p3,p4,p,flower,team,add);
		}		
		if(anjian==4)	break;
	}
	} 
	
	
	if(pause==1)
	{
		while(1)
		{
		int people=rand()%4;
		
		if(people%4==0)
		{
		people++;
		auto_out(p1,a,0);
		shuchu(p1,p2,p3,p4,p,flower);
		if(tt1==0&&a[0]<=0){
			rank[num]=1;
			num++;
			tt1++;
		} 
		if(a[0]<=0&&a[2]<=0) break;
		if(a[1]<=0&&a[3]<=0) break;
		}	
		
		if(people%4==1)
		{
		people++;
		auto_out(p2,a,1);
		shuchu(p1,p2,p3,p4,p,flower);
		if(tt2==0&&a[1]<=0){
			rank[num]=2;
			num++;
			tt2++;
		}
		if(a[0]<=0&&a[2]<=0) break;
		if(a[1]<=0&&a[3]<=0) break;
		}
		
		if(people%4==2)
		{
		people++;
		auto_out(p3,a,2);
		shuchu(p1,p2,p3,p4,p,flower);
		if(tt3==0&&a[2]<=0){
			rank[num]=3;
			num++;
			tt3++;
		}
		if(a[0]<=0&&a[2]<=0) break;
		if(a[1]<=0&&a[3]<=0) break;
		}
		
		if(people%4==3)
		{
		people++;
		auto_out(p4,a,3);
		shuchu(p1,p2,p3,p4,p,flower);
		if(tt4==0&&a[3]<=0){
			rank[num]=4;
			num++;
			tt4++;
		}
		if(a[0]<=0&&a[2]<=0) break;
		if(a[1]<=0&&a[3]<=0) break;	
		}
		}second(rank,team,add);
	}
	if(pause==2)
	{
		cout<<"玩家一，三队打到"<<kk[team[0]]<<endl;
		cout<<"玩家二，四队打到"<<kk[team[1]]<<endl;
		cout<<endl;
		status(p1,p2,p3,p4,p,flower,team,add);
	} 
}
     
void next(char *p,int *team,int *add)
{
	oncard *p1, *p2, *p3, *p4;
	char flower[6]={1,2,3,4,5,6};
	int i,j,k;
	int player[4][27];//存4个玩家的牌
	
	givecard(player);
	
	sort(player[0],player[0]+27,cmp);
	sort(player[1],player[1]+27,cmp);
	sort(player[2],player[2]+27,cmp);
	sort(player[3],player[3]+27,cmp);

	input(p1,player[0]);
	input(p2,player[1]);
	input(p3,player[2]);
	input(p4,player[3]);
	
	repeat(team,add,p);
	shuchu(p1,p2,p3,p4,p,flower);
	
	cout<<endl;
	
	status(p1,p2,p3,p4,p,flower,team,add);
}

int main()
{
	char p[13]={'3','4','5','6','7','8','9','T','J','Q','K','A','2'}; 
	oncard *p1, *p2, *p3, *p4;
	char flower[6]={1,2,3,4,5,6};
	int i,j,k;
	int player[4][27];//存4个玩家的牌
	int anjian;
	int team[2]={0};
	int add[2]={0};
	int play_A=0;
	int play_A1=0;
	int pp1=0;
	int pp2=0;
	
	givecard(player); 

	sort(player[0],player[0]+27,cmp);
	sort(player[1],player[1]+27,cmp);
	sort(player[2],player[2]+27,cmp);
	sort(player[3],player[3]+27,cmp);

	input(p1,player[0]);
	input(p2,player[1]);
	input(p3,player[2]);
	input(p4,player[3]);
	
	repeat(team,add,p);
	shuchu(p1,p2,p3,p4,p,flower);
	
	cout<<endl;
	
	status(p1,p2,p3,p4,p,flower,team,add);
	
	cout<<endl;
	while(1)
	{
	cout<<"请输入相应按键实现相应功能"<<endl;
	cout<<"3代表开始下一轮发牌"<<endl;
	cout<<"4代表结束游戏" <<endl;
	if(team[0]>=12)
	{
		team[0]=12;
		if(pp1!=0)
		{
			if(add[0]==1) play_A++;
			if(add[0]>1)
			{
				cout<<"玩家一，三胜利"<<endl;
				break;
			}
			if(play_A==3)
			{
				team[0]=0;
				play_A=0;
			}
		}pp1++;
	}
	
	if(team[1]>=12)
	{
		team[1]=12;
		if(pp2!=0)
		{
			if(add[1]==1) play_A1++;
			if(add[1]>1)
			{
				cout<<"玩家二，四胜利"<<endl;
				break;
			}
			if(play_A1>=3) 
			{
				team[1]=0;
				play_A1=0;
			}
		}pp2++;
	}
	
	cin>>anjian;
	if(anjian==3)	next(p,team,add);		
	if(anjian==4)	return 0;
	}
	return 0;
}
