#include<stdio.h>

typedef struct node{
    int key;
    struct node* left;
    struct node* right;
    float weight;
    char code[10];
}node;
node* heaparr[26];
float aux[26];  //for storing frequencies from file
char arrint[10];

char arr[26][10];
void writecode(node* ,char [],int);
node* mallocnode( void );
void insheap(node* heaparr[],int i,node* );
node* delheap(node* heaparr[],int i);

int main( void )
{
   int i,counter;
   int top;
   char ch;
   top=0;
   FILE* fr= fopen("huffin.txt","r");  //input txt file
   if(fr == NULL)
   {
      printf("Cannot open file to read\n");
      return 1;
   }
	
   fscanf(fr,"%c",&ch);
   while( ch != '-' )
   {
      aux[ch-97]++;
      fscanf(fr,"%c",&ch);
   }
	
   fclose( fr );

   printf("Written auxillary.\n");
   FILE *fr2=fopen("huffin.txt","r");  //again the same input txt file
   FILE* fw= fopen("huffbin.txt","w");  //encoding text wirtten to this file
   if( fw == NULL )
   {
      printf("Cannot open file to write\n");
      return 2;
   }
	
	
   for(i=0,counter=0; i < 26 ;i++)
   {
       if( aux[i] != 0)
       {
           node* var=mallocnode();
           var->key = i+97;
           var->weight= aux[i];
           insheap(heaparr,counter,var);
           counter++;
       }
   }
   for(i=counter;i > 1;i--)
     {
       node* newn=mallocnode();
       newn->left= delheap(heaparr,i);
       newn->right=delheap(heaparr,i-1);
       newn->weight=newn->left->weight+ newn->right->weight;
       insheap(heaparr,i-2,newn);
     }
     node* root= heaparr[1];
     printf("Tree success.\n");

     writecode(root,arrint,top);
     fscanf(fr2,"%c",&ch);
     while( ch != '-' )
     {
        fprintf(fw,"%s",arr[ch-97]);
        fscanf(fr2,"%c",&ch);
     }
     fprintf(fw,"-");
     fclose(fr2 );
     fclose( fw);
     FILE* fr3= fopen("huffbin.txt","r"); //encoded file containing 0 & 1
     FILE* fw2=fopen("huffdecode.txt","w");  //decoded output file
     fscanf(fr3,"%c",&ch);
     node* ptr= root;
     while( ch != '-')
     {
        if(ch == '0')
          ptr=ptr->left;
        else if(ch == '1')
          ptr=ptr->right;
        if(ptr->left == NULL && ptr->right == NULL)
        {
          fprintf(fw2,"%c",ptr->key);
          ptr=root;
        }
        fscanf(fr3,"%c",&ch);
     }
     fclose(fw2);
     fclose(fr3);
     return 0;
}

void writecode(node* treeroot,char arrcode[],int top)
{
    if( treeroot->left != NULL )
    {
       arrcode[top]='0';
       writecode(treeroot->left,arrcode,top+1);
    }
    if(treeroot->right != NULL )
    {
       arrcode[top]='1';
       writecode(treeroot->right,arrcode,top+1);
    }
    if(treeroot->left== NULL && treeroot->right == NULL)
    {
        int i,ch;
        ch=treeroot->key;
       for(i=0;i< top;i++)
       {
          arr[ch - 97][i]=arrcode[i];
          treeroot->code[i]=arrcode[i];
       }
       arr[ch- 97][i]=treeroot->code[i]='\0';
    }
}
node* mallocnode(void )
{
    node* new=malloc(sizeof(node));
    new->left=new->right=NULL;
    return new;
}

void insheap(node* heaparr[],int i,node* item)
{
   int par,ptr;
   i++;
   ptr=i;
   while(ptr > 1)
   {
       par=ptr/2;
       if(heaparr[par]->weight <= item->weight)
       {
           heaparr[ptr] = item;
           return;
       }
       heaparr[ptr]=heaparr[par];
       ptr=par;
   }
   heaparr[1] = item;
   return;
}
node* delheap(node* heaparr[],int i)
{
   int ptr,left,right;
   node* last,*item;
   item=heaparr[1];
   last= heaparr[i];
   i--;
   ptr=1;
   left=2;
   right=3;
   while(right <= i)
   {
      if(last->weight < heaparr[left]->weight && last->weight < heaparr[right]->weight)
      {
          heaparr[ptr] = last;
          return;
      }
      else if(heaparr[left]->weight < heaparr[right]->weight)
      {
          heaparr[ptr]=heaparr[left];
          ptr=left;
      }
      else
      {
         heaparr[ptr]=heaparr[right];
         ptr=right;
      }
      left= 2* ptr;
      right=left+1;
   }
   if( left == i && heaparr[left]->weight < last->weight)
   {
       heaparr[ptr]= heaparr[left];
       ptr=left;
   }
   heaparr[ptr] = last;
   return item;
}
