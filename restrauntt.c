#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include<string.h>

 struct items
 {
	char item[20];
	float price;
	int Qty;
};
struct Orders
{
	char customer[50];
	int date[50];
	int noofitems;
struct items itm[50];
};
    void generatebillheader(char name[50],char date[50]){
	printf("\t-------HB Restaurant--------");
	printf("\n\t-----------------------------");
	printf("\nDate: %s",date);
	printf("\nInvoice to: %s",name);
	printf("\n");
	printf("-----------------------------\n");
	printf("Items\t\t");
	printf("Qty\t\t");
	printf("Total\t\t");
	printf("\n-----------------------------");
	printf("\n\n");
}

void generatebillbody(char item[50],int Qty,float price)
{
	printf("%s\t\t",item);
	printf("%d\t\t",Qty);
	printf("%f\t\t",Qty*price);
	printf("\n");
}
void generatebillfooter(float total)
{
	printf("\n");
	float dis=0.1*total;
	float nettotal=total-dis;
	float Cgst=0.09*nettotal;
	float grandtotal=2*Cgst+nettotal;
	printf("\n-------------------------------\n");
	printf("\nSub total :\t\t\t%.2f",total);
	printf("\nDiscount@10%s\t\t\t%.2f","%",dis);
	printf("\n");
	printf("\nNet total\t\t\t%.2f",nettotal);
	printf("\nCgst@9 %s\t\t\t%.2f","%",Cgst);
	printf("\nSgst@9 %s\t\t\t%.2f","%",Cgst);
	printf("\n------------------------------\n");
	printf("\nGrand total\t\t\t%.2f",grandtotal);
	printf("\n-------------------------------\n");
}


int main()
{
    float total;
	int opt,n,invoiceFound;
	int x;
	struct Orders ord;
	struct  Orders order;
	char savebill='y',contflag='y';
	char name[50];
	int noofitems;
	FILE*ptr;
    while(contflag=='y')
        {
            float total = 0;
      int  invoiceFound=0;
	printf("\t\t============HB RESTAURANT=============\n");
	printf("\n\t\t----------------------------------------\n");
	printf("\n Please enter your preferred operation\n");
	printf("1.Generate Invoice\n");
	printf("2.Show all invoices\n");
	printf("3.Search Invoice\n");
	printf("4.Exit\n");
	printf("\n\n");
	printf("Your choice :");
	scanf("%d",&x);
	fgetc(stdin);
	switch(x)
	{
	    case 1:
	    printf("\nPlease enter the name of the customer:\t");
		fgets(ord.customer,50,stdin);

		printf("Enter the date :");
		fgets(ord.date,50,stdin);

		printf("Please enter the number of items\t\n");
		scanf("%d",&n);
		ord.noofitems=n;
		for(int i=0;i<n;i++)
            {
            fgetc(stdin);
            printf("\n\n");
            printf("Please enter the item[name] %d :\n",i+1);
            fgets(ord.itm[i].item,20,stdin);
            ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
            printf("Please enter the quantity\t\n");
            scanf("%d",&ord.itm[i].Qty);
            printf("Please enter the unit price\t\n");
            scanf("%f",&ord.itm[i].price);
            total=total+(ord.itm[i].Qty*ord.itm[i].price);
		}

		generatebillheader(ord.customer,ord.date);
		for(int i=0;i<ord.noofitems;i++)
            {
            generatebillbody(ord.itm[i].item,ord.itm[i].Qty,ord.itm[i].price);
		}
		generatebillfooter(total);

		printf("\n Do you want to save the invoice[y/n]:");
		scanf("%s",&savebill);
		if(savebill=='y')
		{
            ptr=fopen("kd.txt","a+");
            fwrite(&ord,sizeof(struct Orders),1,ptr);
            if(fwrite!=0)
                printf("\nSuccessfully saved\n");
            else
                printf("\nError saving\n");
            fclose(ptr);
		}
            break;


    case 2 :
        ptr=fopen("kd.txt","r");
        printf("\n **Your previous invoices are** " );
        while(fread(&order,sizeof(struct Orders),1,ptr))
        {
            float tot=0;
            generatebillheader(order.customer,order.date);
        for(int i=0;i<order.noofitems;i++){
            generatebillbody(order.itm[i].item,order.itm[i].Qty,order.itm[i].price);
            tot=tot +(order.itm[i].Qty*order.itm[i].price);
        }

        generatebillfooter(tot);
        }
	fclose(ptr);

	break;

    case 3:
        printf("\n name of the customer :");

        fgets(name,51,stdin);

        ptr=fopen("kd.txt","r");
        printf("\n*Invoice of %s **",name);
        while(fread(&order,sizeof(struct Orders),1,ptr))
        {
            float tot=0;
            if( !strcmp(order.customer,name))
            {
            generatebillheader(order.customer,order.date);
        for(int i=0;i<order.noofitems;i++)
        {
            generatebillbody(order.itm[i].item,order.itm[i].Qty,order.itm[i].price);
            tot=tot +(order.itm[i].Qty*order.itm[i].price);
        }

        generatebillfooter(tot);
        invoiceFound=1;
        }
        }
        if(!invoiceFound)
        {
            printf("sorry the invoice for %s doesnot exist\n ",name);
        }
	fclose(ptr);

	break;

    case 4:
        printf("\n\t\tBYE BYE \n");
        exit(0);
        break;

    default:
        printf("Sorry invalid Option\n");

          break;
          }
           printf("Do you want to perform another operation[y/n]\n");
          scanf("%s",&contflag);
}
         printf("BYEE BYEEEEEE");
          return 0;
}

