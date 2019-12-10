#include<stdio.h>
#include<stdlib.h>
char pizza[1000][1000];
int s[1000][1000]={0};
int R,C,L,H,p1=0;
int V[1000][4];
// we addthe slice to the linked list if it meets the given conditions and 
//we pop it if we are appled to get an optimal solution by making an another slice.
// used for storing the starting and the ending of the slices

typedef struct node{
	int R1;
	int C1;
	int R2;
	int C2;
	struct node *next;
}node;

struct node* head=NULL;

//returns the size of the slice

int size(int r1,int r2,int c1,int c2){
	return ((r2-r1+1)*(c2-c1+1));
}

// storing the slice details in the vector V	

void slice(int a,int b,int c,int d){

	V[p1][0]=a,V[p1][1]=b,V[p1][2]=c,V[p1][3]=d;
	p1++;
}


// checking whether the the slice pair (r1,c1;r2,c2) meets the given condition

int check(int r1,int r2,int c1,int c2){
	int T=0,M=0;
	for(int i=r1;i<=r2;i++){
		for(int j=c1;j<=c2;j++){
			if(pizza[i][j]=='T')
				T++;
			else
				M++;
		}
	}
	if(T>=L && M>=L && (T+M)<=H)
		return 1;
	else
		return 0;
}

//checking for the slice and adding to the linked list
	
int solvecol(int r1,int r2){
	head=NULL;
	int c1=0,sum=0;
	
	while(c1<=C){
	int c2=c1;
	int prev=0;
	
	while(c2<=C){
	
		if(check(r1,r2,c1,c2))
			prev=1;
		else if(prev){

			struct node* new;
			new=(node*)malloc(sizeof(node));
			new->R1=r1;
			new->C1=c1;
			new->R2=r2;
			new->C2=c2-1;
			new->next=NULL;
		if (head==NULL)		
		head=new;	
		else
			{
				struct node*p=NULL;
				p=head;
				while(p->next!=NULL){
					p=p->next;
				}
				p->next=new;
			}

		sum+=size(r1,r2,c1,c2-1);
		break;
		}
		c2++;
	}
	if(!prev)
		c1++;
	else
		c1=c2;
	}
	return sum;
}




void solve(){
int r1=0;

while(r1<R){
	int r2=r1,best=-1;
        struct node* at=NULL;

while(r2<R){
       
        
        
	int r=solvecol(r1,r2);

		if(r<best){
			r2--;
			break;
}
	
	
	best=r;

	at=head;
r2++;
}
r1=r2+1;
     while(at !=NULL){
	slice(at->R1,at->C1,at->R2,at->C2);
	at=at->next;
}

}
}




void main()

{


    FILE *fptr;

    char filename[15];

    printf("Enter the filename to be opened ( remove the h ,c ,l ,r row in  the file) \n");

    scanf("%s", filename);

    fptr = fopen(filename, "r");

    if (fptr == NULL)

    {
        printf("Cannot open file \n");

        exit(0);

    }
//manually have to enter this

R=3,C=5,L=2,H=3;
 
printf("%d %d  %d %d \n",R,C,L,H);
char a;
int count=0;
for(int i=0;i<R;i++){
for(int j=0;j<C;j++){
	a=fgetc(fptr);
	pizza[i][j]=a;
   if(a=='\n'){
      pizza[i][j]=fgetc(fptr);
     
}
   
}
}

// reading the input and filling the matrix accordingly

for(int i=0;i<R;i++){
for(int j=0;j<C;j++){
s[i][j]=pizza[i][j]=='T' ?1:0;
}
}


for(int i=0;i<R;i++){
for(int j=0;j<C;j++){
	s[i][j]=s[i][j]+(i ? s[i-1][j] :0)+(j ? s[i][j-1]:0);
}
}

for(int i=0;i<R;i++){
for(int j=0;j<C;j++){
   
      printf("%d",s[i][j]);
     
}
  printf("\n");
}



// to solve 
solve();

printf("the best is %d\n",p1);
for(int i=0;i<p1;i++){
for(int j=0;j<4;j++){
	printf("%d ",V[i][j]);
}
	printf("\n");
}
 fclose(fptr);

}
