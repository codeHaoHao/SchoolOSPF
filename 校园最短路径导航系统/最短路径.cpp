#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#define MAX_VERTEX 20
#define INFINITY 65535

typedef char Arr[100];
typedef int Patharc[MAX_VERTEX];//���ڴ洢���·���±������ 
typedef int ShortPathTable[MAX_VERTEX];//���ڴ洢���������·����Ȩֵ�� 
int password =123;
int *thePassword=&password;
Arr arr[MAX_VERTEX]={
	"���ſ�","����¥","����","һ�Ž�ѧ¥","���Ž�ѧ¥","ʵ��¥","���Ž�ѧ¥",
	"ͼ���","��ˮ��","����","��ܰԷ","ϴԡ����","����Է","�ۺ�¥","��Ӿ��",
	"���ﾶ��","�ۺ������" 
	};
Arr arr2[MAX_VERTEX]={
	"����ѧУ�ıؾ�֮·",
	"ѧУ�����ɵĽ���֮һ",
	"��ʵѵ���ģ����м��ž�����ʷ��ɣ�еĽ���",
	"��Ҫ��С���ң�������Ӣ��κ�רҵ��",
	"��Ҫ������רҵ�Σ�����¥��������",
	"ѧ���ϸ���ʵ��εĵص�",
	"�д���ң�һ�㰲�������ϻ�����",
	"ѧУΪͬѧ���ṩѧϰ����ϰ�ĵط���Ҳ��ѧУ�Ĳ������ĵط�",
	"ѧУΨһһ��Ϊͬѧ�ṩ��ˮ�ĵص�",
	"ѧУΨһһ�����ͳ��У�����������򵽸���������Ʒ",
	"�����Ϻõ�ѧ��ʳ�ã�������Ϊ��Ů����Ԣ�Ͻ����������ʳ��Ů���϶�",
	"�������о��ǹ�ģ̫С��ÿ�춼�ǹ���Ӧ��",
	"��Ҫ��Ӫ��ʳ����У������������ʳ��,λ��������Ԣ�����󲿷������ڴ˾Ͳ�",
	"��ʷ��Ϊ�ƾõ�һ����ѧ¥���Ա���ѧ���ڶ����ֲ���ѧУ����ᶼ���������",
	"��һѧ������Ӿ�εĵص�",
	"��׼��400m�ܵ���ѧ�������������εĵص�",
	"�����������εĵط������½��ɵĽ�Ϊ����"
	};
typedef struct{
	int number;// �ڼ������� 
	char *spotInformation;//����Ľ�����Ϣ 
	char *sight;//��������� 
}VertexType;//�������Ϣ 

typedef struct {
	VertexType vex[MAX_VERTEX];//�����洢������Ϣ 
	int arcs[MAX_VERTEX][MAX_VERTEX];//�ڽӾ��������洢ͼ 
	int vexnum;//ͼ�ж���ĸ��� 
	int edgnum;//ͼ�бߵĸ��� 
}LGraph;//ͼ�洢������  
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
		printf("1.�ο�\n");
		printf("2.����Ա\n"); 
		printf("0.�˳�\n");
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
				printf("�������˴����ѡ��\n");
		}
	}
	
	return 0;
}

void createLGraph(LGraph *H){
	int i,j;
	H->vexnum=17;//����ĸ���Ϊ17 
	
	//��Ϊ�����������ֱ�洢�˶�������ƺͶ���Ľ��ܣ�
	//��������Ҫѭ��ΪVertexType vex[MAX_VERTEX]�е���Ϣ��ֵ 
	for(i=0;i<17;i++){ 
	//��Ϊ�ҵ�spotInformationΪһ��ָ�룬�Ұ�spotInformationָ����arr2��Ӧ��λ��
		H->vex[i].spotInformation=arr2[i]; 
		//sightҲָ����arr����Ӧ����Ϣ��λ��
		H->vex[i].sight = arr[i]; 
		H->vex[i].number = i;
	}
	for(j=0;j<H->vexnum;j++){
		for(i=0;i<H->vexnum;i++){
			H->arcs[j][i]=INFINITY;//ѭ���Ƚ�����������ֵ��ֵΪINFINITY������û��·�� 
		}
	}
	//��ʱ�ٰ���·���Ľ��и�ֵ��initializeArray()������ʵ��·����ͨ 
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
	//��Ϊ�����õ�����ͼ�����Դ���һ��·�����ھ����д洢ʱ��Ҫ�������θ�ֵ 
	H->edgnum++;
	H->arcs[x-1][y-1] = num;
	H->arcs[y-1][x-1] = num;
}
void shortPath(LGraph *H,int v0,Patharc *P,ShortPathTable *D){
	int v,w,k,min;
	int final[MAX_VERTEX];//final[w]=1��ʾ��ö���v0��vw�����·��
	
	// ��ʼ������
	for(v=0;v<H->vexnum;v++){
		final[v]=0;//ȫ�������ʼ��Ϊδ֪���·��״̬ 
		(*D)[v]=H->arcs[v0][v];//����v0�������ߵĶ������Ȩֵ 
		(*P)[v]=0;
	}
	(*D)[v0] = 0;//v0��v0��·��Ϊ0
	final[v0] = 1;
	
	//��ʼ��ѭ����ÿ�����v0��ĳ����������·��
	for(v=1;v<H->vexnum;v++){
		min = INFINITY;//��ǰ��֪��v0������������
		for(w=0;w<H->vexnum;w++){
			if(!final[w]&&(*D)[w]<min){//final[w]=1��ʾ��v0��w�����·���Ѿ���� 
				k=w;//k�洢��ʱ��Сֵ���±� 
				min = (*D)[w];//min��if�������ִ�к�Ϊ��С 
			}
		}
		final[k]=1;//��Ŀǰ�ҵ�����Ķ�����Ϊ1
		
		
		//������ǰ���·��������
		for(w=0;w<H->vexnum;w++){
			//�������v�����·������������·���ĳ��ȶ̵Ļ� 
			if(!final[w]&&(min+H->arcs[k][w]<(*D)[w])){
				//˵���ҵ��˸��̵�·�����޸�D[w]��P[w]
				(*D)[w] = min+H->arcs[k][w];//�޸ĵ�ǰ·������ 
				(*P)[w] = k;
			}
		} 		
	} 
}
void displayTwoPonitShortest(LGraph *H){
	int position1,position2,j=0,i=0,temp;
	int arr[MAX_VERTEX];
	Patharc P;//���·�����±� 
	ShortPathTable D;//��ĳ��������·����Ȩֵ 
	printf("��������Ҫ��ѯ��������������к�\n");
	scanf("%d%d",&position1,&position2);
	shortPath(H,position1-1,&P,&D);
	arr[0]=position2-1;
	j = position2-1;
	
	while(P[j]!=0){
        arr[i]=P[j];
        i++;
        j=P[j];
    }
    printf("��%s��%s�����·��Ϊ��\n",H->vex[position1-1].sight,H->vex[position2-1].sight);
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
		printf("1.������Ϣ��ѯ\n");
		printf("2.��ѯ��������·��\n");
		printf("3.��ʾУ԰��ͼ\n");
		printf("4.����\n");
		printf("0.�˳�\n");
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
				printf("�������˴����ѡ��\n");
		}	
	}
	
}
void administrator(LGraph *H){
	int inputPassword,select;
	printf("���������룺\n");
	scanf("%d",&inputPassword);
	while(true){
		if(inputPassword!=*thePassword){
			printf("��������������!\n");
			return;
		}
		printf("1.�޸ĵ�¼����\n");
		printf("2.����µĶ���\n");
		printf("3.�޸ľ�����Ϣ\n");
		printf("4.�½�����·��\n");
		printf("5.����\n");
		printf("0.�˳�\n");
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
				printf("�������˴����ѡ�");
		}
	}
}
void addNewPath(LGraph *H){
	int num,x,y,weight;
	printf("��������Ҫ�������µ�·���ĸ�����\n");
	scanf("%d",&num);
	printf("��������Ҫ��ӵ���·��(��ʽΪ������1�����к�  ����2�����к�   ֮��ľ���)��\n");
	for(int i=0;i<num;i++){
		scanf("%d%d%d",&x,&y,&weight);
		if(x<1||x>H->vexnum||y<1||y>H->vexnum){
			printf("������Ķ��㲻���ڣ�");
			return ;
		}
		initializeArray(H,x,y,weight);
	}
	
}
void editSpotInformation(LGraph *H){
	int num;
	printf("��������Ҫ�޸ĵľ�����Ϣ�����кţ�\n");
	scanf("%d",&num);
	printf("%s�ľ�����Ϣ�� ��%s\n",H->vex[num-1].sight,H->vex[num-1].spotInformation);
	printf("�������޸ĺ�ľ�����Ϣ��\n");
	scanf("%s",H->vex[num-1].spotInformation);
	printf("�޸ĳɹ�,��ϢΪ��\n");
	printf("%d   %s  :  %s\n",H->vex[num-1].number+1,H->vex[num-1].sight,H->vex[num-1].spotInformation);
}
void addNewSpot(LGraph *H){
	int num,y,weight,i;
	if(H->vexnum>=20){
		printf("��ǰ�Ķ�������Ϊ��󶥵���������������ˣ�\n");
		return;
	}
	printf("�������¶�������ƣ�\n");
	scanf("%s",&arr[H->vexnum]);//���µĶ�����Ϣ��ӽ������� 
	printf("�������¶���Ľ��ܣ�\n");
	scanf("%s",&arr2[H->vexnum]);//���µĶ���Ľ����������Ӧ������ 
	H->vex[H->vexnum].number=H->vexnum; 
	H->vex[H->vexnum].sight=arr[H->vexnum];//��Ӧָ��ָ����Ӧ�Ķ�����Ϣλ��
	H->vex[H->vexnum].spotInformation=arr2[H->vexnum]; //��Ӧָ��ָ����Ӧ�Ķ��������Ϣλ��
	H->vexnum++;//��������һ 
	printf("��������Ҫ�´�����·���ĸ�����\n");
	scanf("%d",&num);
	printf("���´����Ķ���Ϊ��%d�����봴������·��(��ʽΪ:���ӵĶ������  ������Ȩֵ)��\n",H->vexnum);
	for(i=0;i<H->vexnum;i++){
		H->arcs[H->vexnum-1][i]=INFINITY;//�Ƚ��µĶ��㵽���������·����ʼ��ΪINFINITY
		H->arcs[i][H->vexnum-1]=INFINITY;//�Ƚ��µĶ��㵽���������·����ʼ��ΪINFINITY
	}
	for(i=0;i<num;i++){
		scanf("%d%d",&y,&weight);
		initializeArray(H,H->vexnum,y,weight);//���µĶ��㸳ֵ·����·����Ȩֵ 
	}
}
void changePassword(){
	int rePassword;
	printf("������ԭ���룺\n");
	scanf("%d",&rePassword);
	if(rePassword!=*thePassword){
		printf("�������������ԭ���벻ͬ��\n");
		return ;
	}else{
		printf("��������Ҫ�޸ĵ����룺\n");
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
	printf("                         |-----------------------15��Ӿ��  \n");
	printf("                         |                            |    \n");
	printf("                         |                            |    \n");
	printf(" 12ϴԡ����---------13����Է                     16���ﾶ��\n");
	printf("       |                 |                            |    \n");
	printf("       |                 |                            |    \n");
	printf("10����---11��ܰԷ        |                            |    \n");
	printf("   |         |       14�ۺ�¥------------------17�ۺ������\n");
	printf("   |         |                                        |    \n");
	printf("9��ˮ��      |-------8ͼ���--------------------------|    \n");
	printf("   |                    |                             |    \n");
	printf("   |                    |                             |    \n");
	printf("   |                    |                             |    \n");
	printf("   |-------6ʵ��¥------|-------7���Ž�ѧ¥           |    \n");
	printf("              |         |           |                 |    \n");
	printf("              |         |           |                 |    \n");
	printf("              |         |           |                 |    \n");
	printf("        4һ�Ž�ѧ¥-----|------5���Ž�ѧ¥            |    \n");
	printf("                        |                             |    \n");
	printf("                        |                             |    \n");
	printf("                        |                             |    \n");
	printf("                        |------2����¥--------------3����  \n");
	printf("                        |                                  \n");
	printf("                        |                                  \n");
	printf("                        |                                  \n");
	printf("                     1���ſ�                               \n");
	printf("\n");
	printf("***********��ӭʹ�ú��ϲƾ�������ѧ����ͼϵͳ**************\n");
}













