#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#define MAX_VERTEX 20
#define INFINITY 65535

typedef char Arr[100];
typedef int Patharc[MAX_VERTEX];//用于存储最短路径下标的数组 
typedef int ShortPathTable[MAX_VERTEX];//用于存储到各点最短路径的权值和 
int password =123;
int *thePassword=&password;
Arr arr[MAX_VERTEX]={
	"大门口","行政楼","北区","一号教学楼","二号教学楼","实验楼","三号教学楼",
	"图书馆","开水房","超市","榴馨苑","洗浴中心","骊绣苑","综合楼","游泳馆",
	"主田径馆","综合文体馆" 
	};
Arr arr2[MAX_VERTEX]={
	"出入学校的必经之路",
	"学校最气派的建筑之一",
	"金工实训中心，还有几排具有历史沧桑感的教室",
	"主要有小教室，用来上英语课和专业课",
	"主要用来上专业课，五六楼有语音室",
	"学生上各种实验课的地点",
	"有大教室，一般安排用来上基础课",
	"学校为同学们提供学习和自习的地方，也是学校的藏书最多的地方",
	"学校唯一一个为同学提供热水的地点",
	"学校唯一一个中型超市，在这里可以买到各种生活用品",
	"环境较好的学生食堂，这里因为离女生公寓较近，所以这个食堂女生较多",
	"环境还行就是规模太小，每天都是供不应求",
	"主要经营面食。我校的物美价廉的食堂,位于男生公寓区，大部分男生在此就餐",
	"历史较为悠久的一栋教学楼，旁边有学生第二俱乐部，学校的晚会都在这里举行",
	"大一学生上游泳课的地点",
	"标准的400m跑道，学生上室外体育课的地点",
	"上室内体育课的地方，是新建成的较为气派"
	};
typedef struct{
	int number;// 第几个顶点 
	char *spotInformation;//顶点的介绍信息 
	char *sight;//顶点的名称 
}VertexType;//顶点的信息 

typedef struct {
	VertexType vex[MAX_VERTEX];//用来存储顶点信息 
	int arcs[MAX_VERTEX][MAX_VERTEX];//邻接矩阵用来存储图 
	int vexnum;//图中顶点的个数 
	int edgnum;//图中边的个数 
}LGraph;//图存储的声明  
void createLGraph(LGraph *H);
void initializeArray(LGraph *H,int x,int y,int num);
void shortPath(LGraph *H,int v0,Patharc *P,ShortPathTable *D);
void displayTwoPonitShortest(LGraph *H);
void user(LGraph *H);
void administrator(LGraph *H);
void Information(LGraph *H);
void displayAllSpotGuide();
void changePassword();
void addNewSpot(LGraph *H);
void editSpotInformation(LGraph *H);
void addNewPath(LGraph *H);


int main(){
	LGraph *H=(LGraph*)malloc(sizeof(LGraph));
	createLGraph(H);
	int select;
	while(true){
		displayAllSpotGuide();
		printf("1.游客\n");
		printf("2.管理员\n"); 
		printf("0.退出\n");
		scanf("%d",&select);
		switch(select){
			case 1:
				user(H);
				break;
			case 2:
				administrator(H);
				break;
			case 0:
				exit(1);
				break;
			default:
				printf("你输入了错误的选项\n");
		}
	}
	
	return 0;
}

void createLGraph(LGraph *H){
	int i,j;
	H->vexnum=17;//顶点的个数为17 
	
	//因为我用另个数组分别存储了顶点的名称和顶点的介绍，
	//所以我需要循环为VertexType vex[MAX_VERTEX]中的信息赋值 
	for(i=0;i<17;i++){ 
	//因为我的spotInformation为一个指针，我把spotInformation指向了arr2相应的位置
		H->vex[i].spotInformation=arr2[i]; 
		//sight也指向了arr中相应的信息的位置
		H->vex[i].sight = arr[i]; 
		H->vex[i].number = i;
	}
	for(j=0;j<H->vexnum;j++){
		for(i=0;i<H->vexnum;i++){
			H->arcs[j][i]=INFINITY;//循环先将矩阵各个点的值赋值为INFINITY，即都没有路径 
		}
	}
	//此时再把有路径的进行赋值，initializeArray()函数是实现路径互通 
	initializeArray(H,1,2,255);
	initializeArray(H,1,4,501);
	initializeArray(H,1,5,535);
	initializeArray(H,1,6,705);
	initializeArray(H,1,7,722);
	initializeArray(H,1,8,790);
	initializeArray(H,2,3,314);
	initializeArray(H,2,4,450);
	initializeArray(H,2,5,484);
	initializeArray(H,2,6,654);
	initializeArray(H,2,7,663);
	initializeArray(H,2,8,748);
	initializeArray(H,3,17,1054);
	initializeArray(H,4,5,272);
	initializeArray(H,4,6,178);
	initializeArray(H,4,7,442);
	initializeArray(H,4,8,527);
	initializeArray(H,5,7,187);
	initializeArray(H,5,8,561);
	initializeArray(H,6,7,289);
	initializeArray(H,6,8,374);
	initializeArray(H,6,9,520);
	initializeArray(H,7,8,382);
	initializeArray(H,8,11,365);
	initializeArray(H,8,17,1096);
	initializeArray(H,9,10,297);
	initializeArray(H,10,11,178);
	initializeArray(H,10,12,331);
	initializeArray(H,11,12,400);
	initializeArray(H,12,13,383);
	initializeArray(H,13,14,340);
	initializeArray(H,13,15,1003);
	initializeArray(H,13,16,833);
	initializeArray(H,14,17,646);
	initializeArray(H,15,16,714);
	initializeArray(H,16,17,688); 
}
 
void initializeArray(LGraph *H,int x,int y,int num){
	//因为咱们用的无向图，所以存在一条路径即在矩阵中存储时需要进行两次赋值 
	H->edgnum++;
	H->arcs[x-1][y-1] = num;
	H->arcs[y-1][x-1] = num;
}
void shortPath(LGraph *H,int v0,Patharc *P,ShortPathTable *D){
	int v,w,k,min;
	int final[MAX_VERTEX];//final[w]=1表示求得顶点v0到vw的最短路径
	
	// 初始化数据
	for(v=0;v<H->vexnum;v++){
		final[v]=0;//全部顶点初始化为未知最短路径状态 
		(*D)[v]=H->arcs[v0][v];//将与v0点有连线的顶点加上权值 
		(*P)[v]=0;
	}
	(*D)[v0] = 0;//v0至v0的路径为0
	final[v0] = 1;
	
	//开始主循环，每次求得v0到某个顶点的最短路径
	for(v=1;v<H->vexnum;v++){
		min = INFINITY;//当前所知离v0顶点的最近距离
		for(w=0;w<H->vexnum;w++){
			if(!final[w]&&(*D)[w]<min){//final[w]=1表示从v0到w的最短路径已经求得 
				k=w;//k存储此时最小值的下标 
				min = (*D)[w];//min最if条件语句执行后为最小 
			}
		}
		final[k]=1;//将目前找到的最经的顶点置为1
		
		
		//修正当前最短路径及距离
		for(w=0;w<H->vexnum;w++){
			//如果经过v顶点的路径比现在这条路径的长度短的话 
			if(!final[w]&&(min+H->arcs[k][w]<(*D)[w])){
				//说明找到了更短的路径，修改D[w]和P[w]
				(*D)[w] = min+H->arcs[k][w];//修改当前路径长度 
				(*P)[w] = k;
			}
		} 		
	} 
}
void displayTwoPonitShortest(LGraph *H){
	int position1,position2,j=0,i=0,temp;
	int arr[MAX_VERTEX];
	Patharc P;//最短路径的下标 
	ShortPathTable D;//到某顶点的最短路径的权值 
	printf("请输入你要查询的两个景点的序列号\n");
	scanf("%d%d",&position1,&position2);
	shortPath(H,position1-1,&P,&D);
	arr[0]=position2-1;
	j = position2-1;
	
	while(P[j]!=0){
        arr[i]=P[j];
        i++;
        j=P[j];
    }
    printf("从%s到%s的最短路径为：\n",H->vex[position1-1].sight,H->vex[position2-1].sight);
    printf("%s -> ",H->vex[position1-1].sight);
    for(int t=i-1;t>=0;t--){
    	printf("%s -> ",H->vex[arr[t]].sight);
	}
	printf("%s",H->vex[position2-1].sight);
}
void user(LGraph *H){
	int select;
	displayAllSpotGuide();
	while(true){
		printf("\n");
		printf("\n");
		printf("\n");
		printf("1.景点信息查询\n");
		printf("2.查询景点的最短路径\n");
		printf("3.显示校园导图\n");
		printf("4.返回\n");
		printf("0.退出\n");
		scanf("%d",&select);
		switch(select){
			case 1:
				Information(H);break;
			case 2:
				displayTwoPonitShortest(H);break;
			case 3:
				displayAllSpotGuide();break;
			case 4:
				return;
			case 0:
				exit(1);
				break;
			default:
				printf("你输入了错误的选项\n");
		}	
	}
	
}
void administrator(LGraph *H){
	int inputPassword,select;
	printf("请输入密码：\n");
	scanf("%d",&inputPassword);
	while(true){
		if(inputPassword!=*thePassword){
			printf("你输入的密码错误!\n");
			return;
		}
		printf("1.修改登录密码\n");
		printf("2.添加新的顶点\n");
		printf("3.修改景点信息\n");
		printf("4.新建顶点路径\n");
		printf("5.返回\n");
		printf("0.退出\n");
		scanf("%d",&select);
		switch(select){
			case 1:
				changePassword();
				break;
			case 2:
				addNewSpot(H);
				break;
			case 3:
				editSpotInformation(H);
				break;
			case 4:
				addNewPath(H);
				break;
			case 5:
				return;
			case 0:
				exit(1);
			default:
				printf("你输入了错误的选项！");
		}
	}
}
void addNewPath(LGraph *H){
	int num,x,y,weight;
	printf("请输入你要创建的新的路径的个数：\n");
	scanf("%d",&num);
	printf("请输入你要添加的新路径(格式为：顶点1的序列号  顶点2的序列号   之间的距离)：\n");
	for(int i=0;i<num;i++){
		scanf("%d%d%d",&x,&y,&weight);
		if(x<1||x>H->vexnum||y<1||y>H->vexnum){
			printf("你输入的顶点不存在！");
			return ;
		}
		initializeArray(H,x,y,weight);
	}
	
}
void editSpotInformation(LGraph *H){
	int num;
	printf("请输入你要修改的景点信息的序列号：\n");
	scanf("%d",&num);
	printf("%s的景点信息是 ：%s\n",H->vex[num-1].sight,H->vex[num-1].spotInformation);
	printf("输入你修改后的景点信息：\n");
	scanf("%s",H->vex[num-1].spotInformation);
	printf("修改成功,信息为：\n");
	printf("%d   %s  :  %s\n",H->vex[num-1].number+1,H->vex[num-1].sight,H->vex[num-1].spotInformation);
}
void addNewSpot(LGraph *H){
	int num,y,weight,i;
	if(H->vexnum>=20){
		printf("当前的顶点数已为最大顶点数，不能再添加了！\n");
		return;
	}
	printf("请输入新顶点的名称：\n");
	scanf("%s",&arr[H->vexnum]);//把新的顶点信息添加进数组中 
	printf("请输入新顶点的介绍：\n");
	scanf("%s",&arr2[H->vexnum]);//把新的顶点的介绍添加入相应数组中 
	H->vex[H->vexnum].number=H->vexnum; 
	H->vex[H->vexnum].sight=arr[H->vexnum];//相应指针指向相应的顶点信息位置
	H->vex[H->vexnum].spotInformation=arr2[H->vexnum]; //相应指针指向相应的顶点介绍信息位置
	H->vexnum++;//顶点数加一 
	printf("请输入你要新创建的路径的个数：\n");
	scanf("%d",&num);
	printf("你新创建的顶点为第%d个，请创建它的路径(格式为:链接的顶点序号  顶点间的权值)：\n",H->vexnum);
	for(i=0;i<H->vexnum;i++){
		H->arcs[H->vexnum-1][i]=INFINITY;//先将新的顶点到其他顶点的路径初始化为INFINITY
		H->arcs[i][H->vexnum-1]=INFINITY;//先将新的顶点到其他顶点的路径初始化为INFINITY
	}
	for(i=0;i<num;i++){
		scanf("%d%d",&y,&weight);
		initializeArray(H,H->vexnum,y,weight);//给新的顶点赋值路径和路径的权值 
	}
}
void changePassword(){
	int rePassword;
	printf("请输入原密码：\n");
	scanf("%d",&rePassword);
	if(rePassword!=*thePassword){
		printf("你输入的密码与原密码不同！\n");
		return ;
	}else{
		printf("请输入你要修改的密码：\n");
		scanf("%d",&rePassword);
		*thePassword = rePassword;
	}
}
void Information(LGraph *H){
	for(int i=0;i<H->vexnum;i++){
		printf("%d   %s  :  %s\n",H->vex[i].number+1,H->vex[i].sight,H->vex[i].spotInformation);
	}
}
void displayAllSpotGuide(){
	printf("                                                           \n");
	printf("                         |-----------------------15游泳池  \n");
	printf("                         |                            |    \n");
	printf("                         |                            |    \n");
	printf(" 12洗浴中心---------13骊绣苑                     16主田径场\n");
	printf("       |                 |                            |    \n");
	printf("       |                 |                            |    \n");
	printf("10超市---11榴馨苑        |                            |    \n");
	printf("   |         |       14综合楼------------------17综合文体馆\n");
	printf("   |         |                                        |    \n");
	printf("9开水房      |-------8图书馆--------------------------|    \n");
	printf("   |                    |                             |    \n");
	printf("   |                    |                             |    \n");
	printf("   |                    |                             |    \n");
	printf("   |-------6实验楼------|-------7三号教学楼           |    \n");
	printf("              |         |           |                 |    \n");
	printf("              |         |           |                 |    \n");
	printf("              |         |           |                 |    \n");
	printf("        4一号教学楼-----|------5二号教学楼            |    \n");
	printf("                        |                             |    \n");
	printf("                        |                             |    \n");
	printf("                        |                             |    \n");
	printf("                        |------2行政楼--------------3北区  \n");
	printf("                        |                                  \n");
	printf("                        |                                  \n");
	printf("                        |                                  \n");
	printf("                     1大门口                               \n");
	printf("\n");
	printf("***********欢迎使用河南财经政法大学导航图系统**************\n");
}













