#include<stdio.h>
#include<conio.h>
#include<string.h>
struct product
{
	char name[30];
	int id;
	float price;
};
struct bill
{
	char nameofcustomer[30];
	char nameofproduct[10][30];
	int idofproduct[10];
	float priceofproduct[10];
	int quantity[10];
	float netcost;
	int billid;
	int numberofitem;
};

int additem();	
int generateBill();
int displayBill();

void main()
{
	int choose=1;
	while(choose==1)
	{	
		int select=0;
		printf("LPU Bakery Billing");
		printf("\n press 1 to ADD PRODUCT ");
		printf("\n press 2 to GENERATE A BILL ");
		printf("\n press 3 to DISPLAY A BILL ");
		printf("\n press 4 to CLOSE ");
		printf("\nPRESS CORRESPONDING KEYS TO PERFORM THE OPERATIONS:  ");   
		scanf("%d",&select);
		switch(select)
		{
			case 1:
				choose=additem();
				break;
			case 2:
				choose=generateBill();
				break;
			case 3:
				choose=displayBill();
				break;
			default:
				choose=0;
		}
	}
	getch();
}
int additem()
{
	struct product p;
	FILE *addproductpt;
	int choice;
	int id;
	int addfuntionchoice=1;
	id=99;
	addproductpt=fopen("productfile","rb");
	if(addproductpt!=0)
	{
		while(fread(&p,sizeof(p),1,addproductpt)==1)
		{
			if(id<p.id)
			id=p.id;
		}
	}
	fclose(addproductpt);
	while(addfuntionchoice==1)
	{
		printf("ENTER PRODUCT NAME: ");
		fflush(stdin);
		gets(p.name);
		printf("ENTER PRODUCT PRICE: ");
		scanf("%f",&p.price);
		p.id=(++id);
		addproductpt=fopen("productfile","ab");
		fwrite(&p,sizeof(p),1,addproductpt);
		fclose(addproductpt);
		printf("YOUR PRODUCT WITH ID %d IS ADDED SUCCESSFULLY",p.id);
		printf("\n PRESS 1 TO ADD NEW PRODUCT OR ANY KEY TO EXIT: ");
		scanf("%d",&addfuntionchoice);
	}
	printf("\n PRESS 1 TO GO TO MAIN MENU AND 0 TO EXIT: ");
	scanf("%d",&choice);
	return choice;
}

int generateBill()
{
	struct product p;
	struct bill b;
	FILE *productpt;
	FILE *billpt;
	int b_id,p_id;
	int choice,genfunctionchoice=1;
	int i=-1, j=0;
	int genfunctionchoice2=0;
	b_id=999;
	billpt=fopen("billfile","rb");
	if(billpt!=0)
	{
		while(fread(&b,sizeof(b),1,billpt)==1)
		{
			if(b_id<b.billid)
				b_id=b.billid;
		}
	}
	fclose(billpt);
	printf("\n ENTER PRODUCT ID OF BUYING PRODUCT TO CALCULATE BILL \n");
	b.netcost=0;
	while(genfunctionchoice==1)
	{
		printf("\n ENTER PRODUCT ID: ");
		scanf("%d",&p_id);
		productpt=fopen("productfile","rb");
		if(productpt!=0)
		{
			while(fread(&p,sizeof(p),1,productpt)!=0)
				{
					if(p.id==p_id)
					{
						i++;
						printf(" PRODUCT NAME- %s    PRODUCT PRICE- %.2f",p.name,p.price);
						strcpy(b.nameofproduct[i],p.name);
						b.priceofproduct[i]=p.price;
						b.idofproduct[i]=p.id;
						printf("\n ENTER QUANTITY OF PRODUCT- ");
						scanf("%d",&b.quantity[i]);
						b.netcost =b.netcost+(b.quantity[i]*b.priceofproduct[i]);
						break;
					}
				}
		}
		fclose(productpt);	
		printf("\n PRESS 1 TO ADD MORE PRODUCT OTHERWISE 0 TO GO TO BILL PAGE: ");
		scanf("%d",&genfunctionchoice);
	}
	printf("\n PUT DOWN CUSTOMER DETAILS: \n CUSTOMER NAME: ");
	fflush(stdin);
	gets(b.nameofcustomer);
	b.billid=++b_id;
	b.numberofitem=i+1;
	billpt=fopen("billfile","ab");
	fwrite(&b,sizeof(b),1,billpt);
	fclose(billpt);
	printf("\n PRESS 1 TO GENERATE A BILL: ");
	scanf("%d",&genfunctionchoice2);
	fflush(stdin);
	if(genfunctionchoice2==1)
	{
		printf("\n		BAKERY BILLING \n");
		printf("\n Customer Name: %s	Bill ID %ld	  ",b.nameofcustomer,b.billid);
		printf("\n Sr No        Item Name      Price  Quantity    Total");
		for(j=0;j<b.numberofitem;j++)
		printf("\n %d    %s    %f  %d    %f",j+1,b.nameofproduct[j],b.priceofproduct[j],b.quantity[j],b.priceofproduct[j]*b.quantity[j]);
		printf("\n Total Bill- %f",b.netcost);
	}
	printf("\n PRESS 1 TO GO TO MAIN MENU AND 0 TO EXIT:  ");
	scanf("%d",&choice);
	return choice;
}
int displayBill()
{
	struct bill b;
	FILE *displaypointer;
	int choice;
	int id;
	int j=0;
	int f=0;
	
	printf("\n PLEASE ENTER YOUR BILL ID- ");
	scanf("%d",&id);
	displaypointer=fopen("billfile","rb");
	if(displaypointer!=0)
	{
		while(fread(&b,sizeof(b),1,displaypointer)!=0)
		{
			if(b.billid==id)
			{
				printf("\n 		BAKERY BILLING");
				printf("\n Customer Name: %s	Bill ID %ld	",b.nameofcustomer,b.billid);
				printf("\n Sr No        Item Name      ProductID      Price  Quantity    Total");
				for(j=0;j<b.numberofitem;j++)
				printf("\n %d    %s    %d    %f  %d    %f",j+1,b.nameofproduct[j],b.idofproduct[j],b.priceofproduct[j],b.quantity[j],b.priceofproduct[j]*b.quantity[j]);
				printf(" \n Total Bill- %f",b.netcost);
				break;
			}
		}
	}
	fclose(displaypointer);	
	printf("\n PRESS 1 TO GO TO MAIN MENU AND 0 TO EXIT:  ");
	scanf("%d",&choice);
	return choice;
}
