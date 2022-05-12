#include<stdio.h>
#include<math.h>
#include<string.h>
#include<malloc.h>
#define testSetNumber 3 
#define trainingSetNumber 7
/*���������ڻ���ѧϰ���������Ӻ����ÿμ�P28ҳ��������10����ǵ������������ٶ����Խ϶࣬���������ݽ���һ���򵥵Ĵ��� 
���������ֲ��䣬ǰ7��Ϊѵ��������3��Ϊ���Լ���������������Ϊ�����⣬���⣬ţ�⣬ţ��
���������д�������������Ƚ�ԭ10�������е�6��������� 8����������*/ 
typedef struct node
{
	int jirou,zhurou,niurou,niunai; 
	int attribute[4];
	char type[10];//��ǩ 
}node;
node trainingSet[trainingSetNumber],testSet[testSetNumber]; 

/*������ѡȡID3�㷨��Ϊ���ѱ�׼�����ù̶��ӽڵ�����ĺ��Ӵ洢�ṹ*/
typedef struct treeNode
{
	int flag;
	int option; 
	char attribute[10];
	struct treeNode *child1,*child2,*parent;		
}treeNode;
treeNode *root,*father; 

/*���غ���*/
float E(float p)
{
	float E;
	if(p==0)
	{
		E=0;
	}
	else
	{
		E=-p*log(p)/log(2);	
	}
	return E;
}

/*���Ѻ��������ѱ�׼��ID3�㷨*/
int divide(node *trainingSet,int N,int *jirou0,int *jirou1,int *zhurou0,int *zhurou1,int *niurou0,int *niurou1,int *niunai0,int *niunai1)
{
	/*����Ϣ����*/
	int i,numYes,numNo;
	i=numYes=numNo=0;
	int num=N/sizeof(node);
	for(node *p=trainingSet;i<num;p++)
	{
		if(!strcmp(p->type,"ȱ��")) numYes++;
		else if(!strcmp(p->type,"��ȱ��")) numNo++;
		i++;
	}
	float E_all=E(numYes*1.0/num)+E(numNo*1.0/num);
	printf("%f\n",E_all);
	/*������Ե���*/
	/*����*/
	float E_jirou,E_jirou_0,E_jirou_1;
	E_jirou=E_jirou_0=E_jirou_1=0;
	if(trainingSet[0].attribute[0])
	{
		int numJirou[2][3]={0};
		i=0; 
		for(node *p=trainingSet;i<num;p++)
		{
			if(p->jirou == 0) 
			{
				numJirou[0][0]++;
				if(!strcmp(p->type,"ȱ��")) numJirou[0][1]++;
				else if(!strcmp(p->type,"��ȱ��")) numJirou[0][2]++; 
			}
			else if(p->jirou == 1)
			{
				numJirou[1][0]++;
				if(!strcmp(p->type,"ȱ��")) numJirou[1][1]++;
				else if(!strcmp(p->type,"��ȱ��")) numJirou[1][2]++; 
			}
			i++;
		}
		*jirou0=numJirou[0][0];
		*jirou1=numJirou[1][0];
		E_jirou_0=E(numJirou[0][1]*1.0/numJirou[0][0])+E(numJirou[0][2]*1.0/numJirou[0][0]);
		E_jirou_1=E(numJirou[1][1]*1.0/numJirou[1][0])+E(numJirou[1][2]*1.0/numJirou[1][0]);
		E_jirou=E_all-(numJirou[0][0]*1.0/num)*E_jirou_0-(numJirou[1][0]*1.0/num)*E_jirou_1;
		printf("%f %f %f\n",E_jirou_0,E_jirou_1,E_jirou);		
	}
	/*����*/
	float E_zhurou,E_zhurou_0,E_zhurou_1;
	E_zhurou=E_zhurou_0=E_zhurou_1=0;
	if(trainingSet[0].attribute[1])
	{
		int numZhurou[2][3]={0};
		i=0; 
		for(node *p=trainingSet;i<num;p++)
		{
			if(p->zhurou == 0) 
			{
				numZhurou[0][0]++;
				if(!strcmp(p->type,"ȱ��")) numZhurou[0][1]++;
				else if(!strcmp(p->type,"��ȱ��")) numZhurou[0][2]++; 
			}
			else if(p->zhurou == 1)
			{
				numZhurou[1][0]++;
				if(!strcmp(p->type,"ȱ��")) numZhurou[1][1]++;
				else if(!strcmp(p->type,"��ȱ��")) numZhurou[1][2]++; 
			}
			i++;
		}
		*zhurou0=numZhurou[0][0];
		*zhurou1=numZhurou[1][0];
		E_zhurou_0=E(numZhurou[0][1]*1.0/numZhurou[0][0])+E(numZhurou[0][2]*1.0/numZhurou[0][0]);
		E_zhurou_1=E(numZhurou[1][1]*1.0/numZhurou[1][0])+E(numZhurou[1][2]*1.0/numZhurou[1][0]);
		E_zhurou=E_all-(numZhurou[0][0]*1.0/num)*E_zhurou_0-(numZhurou[1][0]*1.0/num)*E_zhurou_1;
		printf("%f %f %f\n",E_zhurou_0,E_zhurou_1,E_zhurou);		
	}
	/*ţ��*/
	float E_niurou,E_niurou_0,E_niurou_1;
	E_niurou=E_niurou_0=E_niurou_1=0;
	if(trainingSet[0].attribute[2])
	{
		int numNiurou[2][3]={0};
		i=0; 
		for(node *p=trainingSet;i<num;p++)
		{
			if(p->niurou == 0) 
			{
				numNiurou[0][0]++;
				if(!strcmp(p->type,"ȱ��")) numNiurou[0][1]++;
				else if(!strcmp(p->type,"��ȱ��")) numNiurou[0][2]++; 
			}
			else if(p->niurou == 1)
			{
				numNiurou[1][0]++;
				if(!strcmp(p->type,"ȱ��")) numNiurou[1][1]++;
				else if(!strcmp(p->type,"��ȱ��")) numNiurou[1][2]++; 
			}
			i++;
		}
		*niurou0=numNiurou[0][0];
		*niurou1=numNiurou[1][0];
		E_niurou_0=E(numNiurou[0][1]*1.0/numNiurou[0][0])+E(numNiurou[0][2]*1.0/numNiurou[0][0]);
		E_niurou_1=E(numNiurou[1][1]*1.0/numNiurou[1][0])+E(numNiurou[1][2]*1.0/numNiurou[1][0]);
		E_niurou=E_all-(numNiurou[0][0]*1.0/num)*E_niurou_0-(numNiurou[1][0]*1.0/num)*E_niurou_1;
		printf("%f %f %f\n",E_niurou_0,E_niurou_1,E_niurou);		
	}
	/*ţ��*/
	float E_niunai,E_niunai_0,E_niunai_1;
	E_niunai=E_niunai_0=E_niunai_1=0;
	if(trainingSet[0].attribute[3])
	{
		int numNiunai[2][3]={0};
		i=0; 
		for(node *p=trainingSet;i<num;p++)
		{
			if(p->niunai == 0) 
			{
				numNiunai[0][0]++;
				if(!strcmp(p->type,"ȱ��")) numNiunai[0][1]++;
				else if(!strcmp(p->type,"��ȱ��")) numNiunai[0][2]++; 
			}
			else if(p->niunai == 1)
			{
				numNiunai[1][0]++;
				if(!strcmp(p->type,"ȱ��")) numNiunai[1][1]++;
				else if(!strcmp(p->type,"��ȱ��")) numNiunai[1][2]++; 
			}
			i++;
		}
		*niunai0=numNiunai[0][0];
		*niunai1=numNiunai[1][0];
		E_niunai_0=E(numNiunai[0][1]*1.0/numNiunai[0][0])+E(numNiunai[0][2]*1.0/numNiunai[0][0]);
		E_niunai_1=E(numNiunai[1][1]*1.0/numNiunai[1][0])+E(numNiunai[1][2]*1.0/numNiunai[1][0]);
		E_niunai=E_all-(numNiunai[0][0]*1.0/num)*E_niunai_0-(numNiunai[1][0]*1.0/num)*E_niunai_1;
		printf("%f %f %f\n",E_niunai_0,E_niunai_1,E_niunai);		
	}
	/*�Ƚ�*/
	float max=0;
	int b;
	if(E_jirou>max) max=E_jirou;
	if(E_zhurou>max) max=E_zhurou;
	if(E_niurou>max) max=E_niurou;
	if(E_niunai>max) max=E_niunai;	
	if(max==E_jirou) b=1;
	else if(max==E_zhurou) b=2;
	else if(max==E_niurou) b=3;
	else if(max==E_niunai) b=4;
	printf("%d\n",b);
	return b;
}

/*ѵ��������ͨ���ݹ����ʵ�־������Ĵ���*/
void train(node *trainingSet,int N,int zzz,int xxx)
{
	int jirou0,jirou1,zhurou0,zhurou1,niurou0,niurou1,niunai0,niunai1;
	/*ͨ��divide������ýڵ�ֵ*/
	int attribute=divide(trainingSet,N,&jirou0,&jirou1,&zhurou0,&zhurou1,&niurou0,&niurou1,&niunai0,&niunai1);
	/*�����ڵ�*/
	treeNode *p=(treeNode *)malloc(sizeof(treeNode));
	if(zzz==0) 
	{
		p->parent=father;
		p->flag=1;
		p->option=xxx;
		if(xxx==1) father->child2 = p;		
		else if(xxx==0) father->child1 = p;
	}
	if(zzz==1)//�������ڵ� 
	{
		root=p;
		root->parent=NULL;
		root->flag=1;
	}
	father=p;
	int length=N/sizeof(node);
	int child1Length,child2Length;
	/*��ԭѵ�����ֳ�������ѵ����*/
	switch(attribute)
	{
		case 1 :
			child1Length=jirou0;child2Length=jirou1;break;
		case 2 :
			child1Length=zhurou0;child2Length=zhurou1;break;
		case 3 :
			child1Length=niurou0;child2Length=niurou1;break;
		case 4 :
			child1Length=niunai0;child2Length=niunai1;break;
	}
	node child1[child1Length];int j=0;
	node child2[child2Length];int k=0;
	switch(attribute)
	{
		case 1 :
			strcpy(p->attribute,"����");
			for(int i=0;i<length;i++)
			{
				trainingSet[i].attribute[0]=0;
				if(trainingSet[i].jirou==0)
				{
					for(int l=0;l<4;l++)
					{
						child1[j].attribute[l]=trainingSet[i].attribute[l];
					}
					child1[j].jirou=trainingSet[i].jirou;
					child1[j].zhurou=trainingSet[i].zhurou;
					child1[j].niurou=trainingSet[i].niurou;
					child1[j].niunai=trainingSet[i].niunai;
					strcpy(child1[j].type,trainingSet[i].type);
					j++;
				}
				else if(trainingSet[i].jirou==1)
				{
					for(int l=0;l<4;l++)
					{
						child2[k].attribute[l]=trainingSet[i].attribute[l];
					}
					child2[k].jirou=trainingSet[i].jirou;
					child2[k].zhurou=trainingSet[i].zhurou;
					child2[k].niurou=trainingSet[i].niurou;
					child2[k].niunai=trainingSet[i].niunai;
					strcpy(child2[k].type,trainingSet[i].type);
					k++;					
				}
			}
			break;
		case 2:
			strcpy(p->attribute,"����");
			for(int i=0;i<length;i++)
			{
				trainingSet[i].attribute[1]=0;
				if(trainingSet[i].zhurou==0)
				{
					for(int l=0;l<4;l++)
					{
						child1[j].attribute[l]=trainingSet[i].attribute[l];
					}
					child1[j].jirou=trainingSet[i].jirou;
					child1[j].zhurou=trainingSet[i].zhurou;
					child1[j].niurou=trainingSet[i].niurou;
					child1[j].niunai=trainingSet[i].niunai;
					strcpy(child1[j].type,trainingSet[i].type);
					j++;
				}
				else if(trainingSet[i].zhurou==1)
				{
					for(int l=0;l<4;l++)
					{
						child2[k].attribute[l]=trainingSet[i].attribute[l];
					}
					child2[k].jirou=trainingSet[i].jirou;
					child2[k].zhurou=trainingSet[i].zhurou;
					child2[k].niurou=trainingSet[i].niurou;
					child2[k].niunai=trainingSet[i].niunai;
					strcpy(child2[k].type,trainingSet[i].type);
					k++;					
				}
			}
			break;
		case 3:
			strcpy(p->attribute,"ţ��"); 
			for(int i=0;i<length;i++)
			{
				trainingSet[i].attribute[2]=0;
				if(trainingSet[i].niurou==0)
				{
					for(int l=0;l<4;l++)
					{
						child1[j].attribute[l]=trainingSet[i].attribute[l];
					}
					child1[j].jirou=trainingSet[i].jirou;
					child1[j].zhurou=trainingSet[i].zhurou;
					child1[j].niurou=trainingSet[i].niurou;
					child1[j].niunai=trainingSet[i].niunai;
					strcpy(child1[j].type,trainingSet[i].type);
					j++;
				}
				else if(trainingSet[i].niurou==1)
				{
					for(int l=0;l<4;l++)
					{
						child2[k].attribute[l]=trainingSet[i].attribute[l];
					}
					child2[k].jirou=trainingSet[i].jirou;
					child2[k].zhurou=trainingSet[i].zhurou;
					child2[k].niurou=trainingSet[i].niurou;
					child2[k].niunai=trainingSet[i].niunai;
					strcpy(child2[k].type,trainingSet[i].type);
					k++;					
				}
			}
			break;
		case 4:
			strcpy(p->attribute,"ţ��");
			for(int i=0;i<length;i++)
			{
				trainingSet[i].attribute[3]=0;
				if(trainingSet[i].niunai==0)
				{
					for(int l=0;l<4;l++)
					{
						child1[j].attribute[l]=trainingSet[i].attribute[l];
					}
					child1[j].jirou=trainingSet[i].jirou;
					child1[j].zhurou=trainingSet[i].zhurou;
					child1[j].niurou=trainingSet[i].niurou;
					child1[j].niunai=trainingSet[i].niunai;
					strcpy(child1[j].type,trainingSet[i].type);
					j++;
				}
				else if(trainingSet[i].niunai==1)
				{
					for(int l=0;l<4;l++)
					{
						child2[k].attribute[l]=trainingSet[i].attribute[l];
					}
					child2[k].jirou=trainingSet[i].jirou;
					child2[k].zhurou=trainingSet[i].zhurou;
					child2[k].niurou=trainingSet[i].niurou;
					child2[k].niunai=trainingSet[i].niunai;
					strcpy(child2[k].type,trainingSet[i].type);
					k++;					
				}
			}
			break;
	}
	/*��������ѵ���������жϴ��������ǩͳһ�����ֱ����ΪҶ�ӽ��*/
	/*�Ӽ�1*/
	int num=0; 
	for(int i=0;i<child1Length;i++)
	{
		num=num+strcmp(child1[i].type,"��ȱ��"); 		
	}
	if(num==0)
	{
		treeNode *q=(treeNode *)malloc(sizeof(treeNode));
		q->option=0;
		q->flag=1;
		q->child1=NULL;
		q->child2=NULL;
		q->parent=p;
		p->child1=q;
		strcpy(q->attribute,"��ȱ��");
	}
	else if(num==child1Length)
	{
		treeNode *q=(treeNode *)malloc(sizeof(treeNode));
		q->option=0;
		q->flag=1;
		q->child1=NULL;
		q->child2=NULL;
		q->parent=p;
		p->child1=q;
		strcpy(q->attribute,"ȱ��");		
	}
	else if((child1[0].attribute[0]+child1[0].attribute[1]+child1[0].attribute[2]+child1[0].attribute[3])==0)
	{
		treeNode *q=(treeNode *)malloc(sizeof(treeNode));
		q->option=0;
		q->flag=1;
		q->child1=NULL;
		q->child2=NULL;
		q->parent=p;
		p->child1=q;
		if(num>(child1Length/2)) strcpy(q->attribute,"ȱ��");
		else strcpy(q->attribute,"��ȱ��");	
	}
	else train(child1,sizeof(child1),0,0); 
	/*���Ӽ�*/ 
	for(int i=0;i<child2Length;i++)
	{
		num=num+strcmp(child2[i].type,"��ȱ��"); 	
	}
	if(num==0)
	{
		treeNode *q=(treeNode *)malloc(sizeof(treeNode));
		q->option=1;
		q->flag=1;
		q->child1=q->child2=NULL;
		q->parent=p;
		p->child2=q;
		strcpy(q->attribute,"��ȱ��");
	}
	else if(num==child2Length)
	{
		treeNode *q=(treeNode *)malloc(sizeof(treeNode));
		q->option=1;
		q->flag=1;
		q->child1=q->child2=NULL;
		q->parent=p;
		p->child2=q;
		strcpy(q->attribute,"ȱ��");		
	}
	else if((child2[0].attribute[0]+child2[0].attribute[1]+child2[0].attribute[2]+child2[0].attribute[3])==0)
	{
		treeNode *q=(treeNode *)malloc(sizeof(treeNode));
		q->option=1;
		q->flag=1;
		q->child1=q->child2=NULL;
		q->parent=p;
		p->child2=q;
		if(num>(child2Length/2)) strcpy(q->attribute,"ȱ��");
		else strcpy(q->attribute,"��ȱ��");
	}
	else train(child2,sizeof(child2),0,1);
}

/*����������,�����������*/
void view(treeNode *root)
{
	char data[20][10];
	strcpy(data[0],root->attribute);
	root->flag=0;
	treeNode *p=root;
	int i=1;
	do
	{
		if(p->child1!=NULL&&p->child1->flag==1)
		{
			strcpy(data[i],p->child1->attribute);
			i++;
			p=p->child1;
			p->flag=0;
		}
		else if(p->child2!=NULL&&p->child2->flag==1)
		{
			strcpy(data[i],p->child2->attribute);
			i++;
			p=p->child2;
			p->flag=0;
		}
		else break;
		while(p->child1==NULL&&p->child2==NULL&&p->parent!=NULL)
		{
			p=p->parent;
		}
		while(p->child1->flag==0&&p->child2->flag==0&&p->parent!=NULL)
		{
			p=p->parent;
		}
		if(p->child1->flag==0&&p->child2->flag==0&&p->parent==NULL) break;
	}while(1);
	int j=0;
	printf("\n");
	do
	{
		printf("%s ",data[j]);
		j++;
	}while((strcmp(data[j],"����")*strcmp(data[j],"����")*strcmp(data[j],"ţ��")*strcmp(data[j],"ţ��")*strcmp(data[j],"ȱ��")*strcmp(data[j],"��ȱ��"))==0);
	printf("\n\n");	
} 

/*���Ժ���*/
void test(node *testExample)
{
	treeNode *p=root;
	do{
		if(!strcmp(p->attribute,"����"))
		{
			if(testExample->jirou==p->child1->option) p=p->child1;
			else if(testExample->jirou==p->child2->option) p=p->child2;
		}
		else if(!strcmp(p->attribute,"����"))
		{
			if(testExample->zhurou==p->child1->option) p=p->child1;
			else if(testExample->zhurou==p->child2->option) p=p->child2;
		}
		else if(!strcmp(p->attribute,"ţ��"))
		{
			if(testExample->niurou==p->child1->option) p=p->child1;
			else if(testExample->niurou==p->child2->option) p=p->child2;
		}
		else if(!strcmp(p->attribute,"ţ��"))
		{
			if(testExample->niunai==p->child1->option) 
			{
				p=p->child1;	
			}
			else if(testExample->niunai==p->child2->option) 
			{
				p=p->child2;	
			}
		}		
	}while((strcmp(p->attribute,"ȱ��")*strcmp(p->attribute,"��ȱ��")) != 0 );
	strcpy(testExample->type,p->attribute);
} 

int main()
{
	/*����ѵ����*/
	FILE *fp=NULL;
	fp=fopen("ѵ����.txt","r");
	for(int i=0;i<trainingSetNumber;i++)
	{
		trainingSet[i].attribute[0]=trainingSet[i].attribute[1]=trainingSet[i].attribute[2]=trainingSet[i].attribute[3]=1;
		fscanf(fp,"%d %d %d %d %s",&trainingSet[i].jirou,&trainingSet[i].zhurou,&trainingSet[i].niurou,&trainingSet[i].niunai,&trainingSet[i].type);
	}
	fclose(fp);
	/*������Լ�*/
	fp=fopen("���Լ�.txt","r");
	for(int i=0;i<testSetNumber;i++)
	{
		testSet[i].attribute[0]=testSet[i].attribute[1]=testSet[i].attribute[2]=testSet[i].attribute[3]=1;
		fscanf(fp,"%d %d %d %d %s",&testSet[i].jirou,&testSet[i].zhurou,&testSet[i].niurou,&testSet[i].niunai,&testSet[i].type);
	}
	fclose(fp);
	/*ѵ��*/
	train(trainingSet,sizeof(trainingSet),1,0);
	view(root);
	/*����*/
	printf("��ʼ���ԣ�\n");
	for(int i=0;i<testSetNumber;i++)
	{
		test(&testSet[i]);
		printf("��������%d:%s\n",i+1,testSet[i].type);
	}
}

/**
1���������ݽṹ�洢ѵ�����Ͳ��Լ� 
2����ѵ����ʵ�־�����
   ��ID3�㷨��Ϊ�б��׼����һ������ʵ�־����� 
3���ڲ��Լ�����֤������ 
**/ 
