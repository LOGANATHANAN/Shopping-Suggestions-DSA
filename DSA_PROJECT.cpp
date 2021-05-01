#include<iostream>
#include<string.h>
#include<stdbool.h>
#include<stdio.h>
#include<math.h>
#include<bits/stdc++.h>
using namespace std;
			    /* Vellore Institute of Technology, Vellore */
			    
                   /*19BCT0081  A.N.LOGANATHAN  DSA PROJECT "SHOPPING SUGGESTIONS"*/
           
/*class item defined below is a singly linked list to store purchase details of the user*/                           
class item{
public:
	char *str=(char*)malloc(15*sizeof(char));
	item *next;
	};

/*below pushitem() function is to push an Chosen Item into singly linked list "item"*/

void pushitem(item **head,char s[]){
	item* new_item= new item();
	new_item->str=s;
	new_item->next=(*head);
	(*head)=new_item;
	}

/*below updateitem() function is to update an item if user prefer to update*/

void updateitem(item **head,int position,char s[]){
	if(*head==NULL){
	return;
	}
	for(int i=0;i<position-2;i++){
	(*head)=(*head)->next;
	}
	(*head)->str=s;
	}

/*below deleteitem() function is to delete an item if user prefer to delete*/
	
void deleteitem(item **head,int position){
	if(*head==NULL){
	return;
	}
	item *temp=new item();
	temp=*head;
	if(position==0){
	*head=temp->next;
	free(temp);
	return;
	}
	
	for(int i=0;i<position-1 && temp!=NULL;i++){
	temp=temp->next;
	}
	
	if(temp==NULL || temp->next==NULL){
	return;
	}
	
	item *next=new item();
	next=temp->next->next;
	
	free(temp->next);
	temp->next=next;
}

/*below insertitem() function is to insert an item in a particular position*/

void insertitem(item *prev,char s[]){
	if(prev==NULL){
	return;
	}
	item *insert_item=new item();
	insert_item->str=s;
	insert_item->next=prev->next;
	prev->next=insert_item;
	}	

/*below printitem() function is to display the items chosen for purchase*/
	
void printitem(item *head){
	item *item=head;
	int i=0;
	cout<<"\n\t********* Chosen Items **********";
	while(item!=NULL){
	cout<<"\n\t* item no: "<<i+1<<" "<<item->str;
	item=item->next;
	i++;
	}
	cout<<"\n\t*********************************";
	}

/*class suggestitems defined below is a linked list to store the items that may be suggested*/

class suggestitems{
public:
	char *str=(char*)malloc(15*sizeof(char));
	float weight,discount;
	int frequency;
	suggestitems *next;
	suggestitems(){
	frequency=0;
	weight=0;
	discount=0;
	}
	};

/*below pushsuggestitems() function is to push an item into to suggestitems list*/

void pushsuggestitems(suggestitems **S,char s[]){
	suggestitems *temp=new suggestitems();
	temp->str=s;
	temp->frequency+=1;
	temp->next=(*S);
	(*S)=temp;
	}

/*below printsuggestthread() function is to display items that may be suggested*/
		
void printsuggestthread(suggestitems *S){
	suggestitems *temp=new suggestitems;
	temp=S;
	while(temp!=NULL){
	cout<<"-->"<<temp->str<<">"<<temp->frequency<<" ";
	temp=temp->next;
	}
	cout<<endl;
	}

/*struct source is an array like structure used to store items purchased in each and every 
purchase*/

struct source{
	int link_no;
	item *head;
	};

/*struct alpha is an array like structure containing 26 nodes representing every 
alphabet in the english */

/*items purchased are mapped into the struct alpha using hashing*/

/*hashing is used to reduce the search time for an object*/
			
struct alpha{
	char X='_';
	int n=0,freqsum=0;
	float variance=0,freqavg=0;
	suggestitems *ptr=NULL;
	bool flag=false;
	};

/*below struct temp alpha is an array like structure used for statistical analysis*/

/*tempalpha also contains 26 nodes each for every alphabet*/

struct tempalpha{
	char X;
	float freqavg,variance;
};

/* struct offerstack is a stack data structure used to store the offers
given by the shop keeper*/
	
struct offerstack{
	char *str=(char*)malloc(15*sizeof(char));
	float discount;
	struct offerstack *next;
	};
struct offerstack *top;

/*below pushoffer() function is to push an offer into the offerstack*/

void pushoffer(char s[],float discount){
	struct offerstack* temp;
	temp= new offerstack();
	temp->str=s;
	temp->discount=discount;
	temp->next=top;
	top=temp;
	}
	
/*below peektopofferitem() function returns the top item in the stack*/

char peektopofferitem(){
	if(top!=NULL){
	return *(top->str);
	}
	else{
	exit(1);
	}
}

/*below peektopofferdiscount() function returns the top item's discount*/

float peektopofferdiscount(){
	if(top!=NULL){
	return top->discount;
	}
	else{
	exit(1);
	}
	}

/*below popoffer() function pops out the top most node in the offerstack*/

void popoffer(){
	struct offerstack* temp;
	if(top==NULL){
	cout<<"\nStack Empty!";
	}
	else{
	temp=top;
	top=top->next;
	temp->next=NULL;
	free(temp);
	}

}	

/*below displayofferstack() function is to display the content of offerstack*/

void displayofferstack(){
	struct offerstack* temp;
	if(top==NULL){
	cout<<"\nStack Empty!";
	}
	else{
	temp=top;
	while(temp!=NULL){
	cout<<temp->str<<" "<<temp->discount<<"->";
	temp=temp->next;
	}
	}
}

/*struct offerbox is an array like structure which contains finalized offeritems*/

struct offerbox{
	char *str=(char*)malloc(15*sizeof(char));
	float discount;
};

/*below varfunc() function is used to calculate the variance of frequency */
 	
float varfunc(suggestitems *S,struct alpha a[],int i){
	suggestitems *temp=S;
	float var=0;
	while(temp!=NULL){
	var+=pow(((temp->frequency)-(a[i].freqavg)),2)/a[i].n;
	temp=temp->next;
	}
	return var;
	}
	
/*below hashfunc() function is used for hashing into the alpha structure*/

int hashfunc(char A){
	int temp=A;
	return (temp-65)%26;
	}

/*below searchitem() function is used to search for particular item in the 
suggestitems linked list*/

int searchitem(suggestitems *S,char s[]){
	int i=1;
	while(S!=NULL){
	if(strcmp(S->str,s)==0){
	break;
	}
	else{
	i++;
	S=S->next;
	}
	}
	return i;
	}

/*below frequencyinc() function is used to increase frequency of an item in the
suggestitems list if that item is repeated*/

void frequencyinc(suggestitems **head,int n){
	suggestitems *temp=(*head);
	for(int i=1;i<n;i++){
	(*head)=(*head)->next;
	}
	(*head)->frequency+=1;
	(*head)=temp;
	}	

/*below insert() function is used to map the purchased items into the alpha struture
using HASHING*/

void insert(item *head,struct alpha a[]){
	
	while(head!=NULL){
	char *Str=head->str;
	char s=*(Str+0);
	int temp=hashfunc(s);
	
	if(a[temp].flag==false){
	a[temp].X=s;
	a[temp].n+=1;
	pushsuggestitems(&a[temp].ptr,head->str);
	a[temp].flag=true;
	a[temp].freqsum+=1;
	}
	
	else{
	a[temp].X=s;
	int I=searchitem(a[temp].ptr,head->str);
	
	if(I>a[temp].n){
	a[temp].n+=1;
	pushsuggestitems(&a[temp].ptr,head->str);
	a[temp].freqsum+=1;
	}
	
	else{
	frequencyinc(&a[temp].ptr,I);
	a[temp].freqsum+=1;
	}
	}
	a[temp].freqavg=((float)a[temp].freqsum/(float)a[temp].n);
	a[temp].variance=varfunc(a[temp].ptr,a,temp);
	head=head->next;
	}
	}

/*below structure suggestnode is a singly linked list used to store items that are
gonna be suggested*/

struct suggestnode{
	char *str=(char*)malloc(15*sizeof(char));
	int frequency;
	struct suggestnode *next;
};
struct suggestnode *head=NULL;

/*below pushsuggestnode() function is used to push an suggested item into the suggestnode
linked list*/

void pushsuggestnode(char s[],int f){
	struct suggestnode *new_node=(struct suggestnode*)malloc(sizeof(struct suggestnode));
	new_node->str=s;
	new_node->frequency=f;
	new_node->next=head;
	head=new_node;
}

/*below delsuggestnode() function is used to delete a node*/

void delsuggestnode(char s[]){
	struct suggestnode *temp=head,*prev;
	if(temp!=NULL && strcmp(temp->str,s)==0){
	head=temp->next;
	free(temp);
	return;
	}
	
	while(temp!=NULL && strcmp(temp->str,s)!=0){
	prev=temp;
	temp=temp->next;
	}
	
	if(temp==NULL){
	return;
	}
	
	prev->next=temp->next;
	free(temp);
}

/*below printsuggestnode() function displays the suggestions to the user*/

void printsuggestnode(){
	struct suggestnode *temp=head;
	cout<<"\n\n\t\t\tSuggested Items";
	cout<<"\n\t  ********************************************";
	int i=0;
	while(temp!=NULL){
	int s=strlen(temp->str);
	if(i%2==0){
	cout<<"\n\t  *    "<<temp->str;
	for(int i=0;i<(22-s);i++){
	cout<<" ";
	}
	}
	else{
	cout<<" "<<temp->str;
	}
	i++;
	temp=temp->next;
	}
	cout<<"\n\t  ********************************************";
}

/*below inserttosuggestnode() function is used to insert selected nodes of alpha structure
into the temporary tempalpha structure*/

void inserttosuggestnode(struct tempalpha b[],struct alpha a[]){
	int i=0,flag=0;
	while(b[i].freqavg!=0){
	int index=(int)b[i].X-65;
	suggestitems *temp=new suggestitems;
	temp=a[index].ptr;
	while(temp!=NULL){
	flag++;
	pushsuggestnode(temp->str,temp->frequency);
	temp=temp->next;
	}
	if(flag>15){
	break;
	}
	i++;
	}
}

/*below suggestbox() function is used to delete an item in the suggestnode linked list 
if that item has been selected already by the user*/

void suggestbox(struct source S[],int c){
	item *temp=new item();
	temp=S[c].head;
	while(temp!=NULL){
	delsuggestnode(temp->str);
	temp=temp->next;
	}
}

/*below freesuggestbox() function will delete all the nodes in the suggestnode linked list*/

void freesuggestbox(){
	struct suggestnode *current=head;
	struct suggestnode *next;
	
	while(current!=NULL){
	next=current->next;
	free(current);
	current=next;
	}
	
	head=NULL;

}

/*below assigntempalpha() function is used to assign necessary values of alpha into
the tempalpha for statistical analysis*/

void assigntempalpha(struct alpha a[],struct tempalpha b[]){
	for(int i=0;i<26;i++){
	b[i].X=(char)(i+65);
	b[i].freqavg=a[i].freqavg;
	b[i].variance=a[i].variance;
	}
}

/*below sorttempalpha() function is used to sort the tempalpha based on the variance of
frequency and average of frequency */

void sorttempalpha(struct tempalpha b[]){
	for(int i=0;i<25;i++){
	for(int j=0;j<25-i;j++){
	if(b[j].variance!=0 && b[j+1].variance!=0){
	if((b[j].freqavg/b[j].variance)<(b[j+1].freqavg/b[j+1].variance)){
	
	struct tempalpha temp;
	temp.X=b[j].X;
	temp.freqavg=b[j].freqavg;
	temp.variance=b[j].variance;
	
	b[j].X=b[j+1].X;
	b[j].freqavg=b[j+1].freqavg;
	b[j].variance=b[j+1].variance;
	
	b[j+1].X=temp.X;
	b[j+1].freqavg=temp.freqavg;
	b[j+1].variance=temp.variance;
	
	}
	}
	}
	}
	
	for(int i=0;i<25;i++){
	for(int j=0;j<25-i;j++){
	if(b[j].variance==0 || b[j+1].variance==0){
	if(b[j].freqavg<b[j+1].freqavg){
	
	struct tempalpha temp;
	temp.X=b[j].X;
	temp.freqavg=b[j].freqavg;
	temp.variance=b[j].variance;
	
	b[j].X=b[j+1].X;
	b[j].freqavg=b[j+1].freqavg;
	b[j].variance=b[j+1].variance;
	
	b[j+1].X=temp.X;
	b[j+1].freqavg=temp.freqavg;
	b[j+1].variance=temp.variance;
	
	}
	}
	}
	}
	
}

int offersuggest(item *head,struct offerbox O[]){
	int inc=0;
	item *itemtemp=head;

	while(1){
	if(top==NULL){
	break;
	}
	else{
	while(itemtemp!=NULL){
	if(strcmp(top->str,itemtemp->str)==0){
	popoffer();
	break;
	}
	itemtemp=itemtemp->next;
	if(itemtemp==NULL){
	O[inc].str=top->str;
	O[inc].discount=top->discount;
	inc++;
	popoffer();
	}
	}
	itemtemp=head;
	}
	
	}
	return inc-1;
}

/*below analysis() function displays the statistical details of purchases until now*/

void analysis(struct alpha a[]){
	printf("\n\n  ***************************************************************");
	  printf("\n  * StartLetter|  N  | Avg.freq | freq.Varaince | Items_List");
	printf("\n  ***************************************************************");
	  for(int i=0;i<26;i++){
printf("\n  *     %c      |  %d  |   %.2f   |     %.2f      |  |",a[i].X,a[i].n,a[i].freqavg,a[i].variance); 
	printsuggestthread(a[i].ptr);
	}
	printf("\n  ***************************************************************");
}

/*below shopkeeperoffer() is for shop keeper portal*/

void shopkeeperoffer(int c,struct source S[]){
	printf("\n\n\t**************************************************");
	printf("\n\t*\n\t*\tShopkeeper portal: Choose the Action");
	int choice,n;
	
	printf("\n\t*\t*****************************************");
	printf("\n\t*\t*Enter 1 for Offers\tEnter 0 for Exit*");
	printf("\n\t*\t*****************************************");
	printf("\n\t*\tEnter the choice:");
	cin>>choice;
	switch(choice){
	case 1:
	{
	printf("\n\t*\tEnter Number of items have offers: ");
	cin>>n;
	for(int i=0;i<n;i++){
	char *Str=(char*)malloc(15*sizeof(char));
	float d;
	printf("\n\t*\tItem no. %d",i+1);
	printf("\n\t*\t\tItem: ");
	cin>>Str;
	printf("\n\t*\t\tDiscount: ");
	cin>>d;
	pushoffer(Str,d);
	}
	break;
	}
	case 0:
	{
	break;
	}
	}
	printf("\n\t**************************************************");
	struct offerbox O[20];
	int r=offersuggest(S[c].head,O);
	printf("\n\n\t\t\tOffer Suggestions");
 	printf("\n  ************************************************************");
 	printf("\n  * Item             Discount  |  Item             Discount  *");
	for(int i=0;i<=r;i++){
	int s=strlen(O[i].str);
	if(i%2==0){
	 cout<<"\n  * "<<O[i].str;
	 for(int i=0;i<(19-s);i++){
	 cout<<" ";
	 }
	 cout<<O[i].discount<<"         ";
	}
	else{
	 cout<<O[i].str;
	 for(int i=0;i<(19-s);i++){
	 cout<<" ";
	 }
	 cout<<O[i].discount;
	}
	}
	printf("\n  ************************************************************");
}

/*below inputandsuggestions() function is the major function that handles input from
users and processing the data*/
				
int inputandsuggestions(struct source S[],struct alpha a[],struct tempalpha b[]){
	int i=0,flag=0,n;
	while(i<=100){
	S[i].head=NULL;
	int item_no;
	int choice;
	printf("\n\n\t Choose the Action  Purchase Number: %d",i+1);
	printf("\n***********************************************************************");
	printf("\n* Purchase Items->Enter 1| Purchase Analysis->Enter 2| Exit->Enter 3 *");
	printf("\n***********************************************************************");
	printf("\nEnter the choice:");
	cin>>choice;
	switch(choice){
	
	case 1:
	{
	printf("\nEnter number of items gonna purchase:");
	cin>>n;
	for(int j=0;j<n;j++){
	printf("\nItem %d: ",j+1);
	char *Str=(char*)malloc(15*sizeof(char));
	cin>>Str;
	pushitem(&S[i].head,Str);
	}
	
	printf("\n\t**********************************************");
	printf("\n\tUpdate item->Enter 1 | Delete an item->Enter 2");
	printf("\n\t\t\tExit-->Enter 0"); 
	printf("\n\t**********************************************");
	printf("\n\tEnter the choice:");
	cin>>choice;
	switch(choice){
	case 0:
	{
	break;
	}
	
	case 1:
	{
	if(S[i].head==NULL){
	break;
	}
	else{
	printf("\nEnter the item number to be updated:");
	cin>>item_no;
	char *Str=(char*)malloc(15*sizeof(char));
	printf("\nEnter the item:");
	cin>>Str;
	updateitem(&S[i].head,n-item_no+1,Str);
	}
	}
	break;
	case 2:
	{
	if(S[i].head==NULL){
	break;
	}
	else{
	printf("\nEnter the item no to be deleted:");
	cin>>item_no;
	deleteitem(&S[i].head,n-item_no);
	}
	}
	break;
	}
	insert(S[i].head,a);
	
	printitem(S[i].head);
	
	shopkeeperoffer(i,S);
	
	assigntempalpha(a,b);
	
	sorttempalpha(b);
	
	inserttosuggestnode(b,a);

	suggestbox(S,i);
	
	printsuggestnode();
	
	freesuggestbox();
	
	i++;
	}
	break;
	
	case 2:
	{
	analysis(a);
	break;
	}
	
	case 3:
	{
	flag=1;
	break;
	}
	}
	if(flag==1){
	break;
	}
	}
	return i-1;
}

//main() function

int main(){
	struct source S[100];
	struct alpha a[26];
	struct tempalpha b[26];
	
	inputandsuggestions(S,a,b);
	
	return 0;
	}
