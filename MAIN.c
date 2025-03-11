/*
NAME: B SAI CHARAN REDDY
DATE: 11/10/2024
DESCRIPTION: ADDRESS BOOK
*/
#include <stdio.h>
#include<stdio_ext.h>
#include <string.h>
void add_details();
void copying(FILE *,FILE *);
void search_details();
void edit_details();
void delete_details();
void print_details();
struct Address
{
        char name[20];
        char mobile[15];
        char email[30];
        char address[100];
};
int main()
{
        int repeat=1;
        while(repeat)
        {
                printf("1.Add Details\n2.Search Details\n3.Edit Details\n4.Delete Details\n5.Print Details\n6.Exit\n");
                int choice=0;
                printf("Enter the choice: ");
                scanf("%d",&choice);
                switch (choice)
                {
                        case 1:
                                //ADD Contacts
                                add_details();
                                break;
                        case 2:
                                //Search Details
                                search_details();
                                break;
                        case 3:
                                //Edit Details
                                edit_details();
                                break;
                        case 4:
                                //Delete Details
                                delete_details();
                                break;
                        case 5:
                                //Print Details
                                print_details();
                                break;
                        case 6:
                                return 0;
                        default:
                                printf("Invalid option, Please enter correct option\n");
                                break;
                }
        printf("Do you want continue(y/Y): ");
        __fpurge(stdin);
        char ch;
        scanf("%c",&ch);
        ch=='y'||ch=='Y'?(repeat=1):(repeat=0);
        }

}
void add_details()
{
    FILE *fptr = fopen("data.csv", "r");
    FILE *fptr1 = fopen("temp.csv", "w");
    struct Address details;
    struct Address cdetails;

    int count;
    fscanf(fptr, "%d\n", &count);
    count++;
    fprintf(fptr1, "%d\n", count);

    for (int i = 0; i < count - 1; i++)
    {
        fscanf(fptr, " %[^,],%[^,],%[^,],%[^\n]\n", details.name, details.mobile, details.email, details.address);
        fprintf(fptr1, "%s,%s,%s,%s\n", details.name, details.mobile, details.email, details.address);
    }

    printf("Enter the name: ");
    scanf(" %[^\n]", details.name);

    int n = 1;
    while (n)
    {
        printf("Enter the mobile number: ");
        scanf(" %[^\n]", details.mobile);
        if (strlen(details.mobile) >= 10)
        {
            n = 0;
            for (int i = 0; i < strlen(details.mobile); i++)
            {
                if (details.mobile[i] < '0' || details.mobile[i] > '9')
                {
                    n = 1;
                    printf("Invalid mobile number!!\n");
                    break;
                }
            }
        }
        else
        {
        printf("You Entered is less than 10 digits, Please enter correct mobile number\n");
        }
        if (n == 0)
        {
            rewind(fptr);
            fscanf(fptr, "%d\n", &count);
            n = 0;
            for (int i = 0; i < count; i++)
            {
                fscanf(fptr, " %[^,],%[^,],%[^,],%[^\n]\n", cdetails.name, cdetails.mobile, cdetails.email, cdetails.address);
                if (strcmp(details.mobile, cdetails.mobile) == 0)
                {
                    n = 1;
                    printf("Mobile number already existed\n");
                    break;
                }
            }
        }
    }

    int m = 1, found;
    while (m)
    {
        m = 0, found = 0;
        printf("Enter the email: ");
        scanf(" %[^\n]", details.email);
        rewind(fptr);
        fscanf(fptr, "%d\n", &count);
        for (int i = 0; i < count; i++)
        {
            fscanf(fptr, " %[^,],%[^,],%[^,],%[^\n]\n", cdetails.name, cdetails.mobile, cdetails.email, cdetails.address);
            if (strcmp(details.email, cdetails.email) == 0)
            {
                printf("Email already exists!!\n");
                m = 1;
                found = 1;
                break;
            }
        }
        if (m == 0)
        {
            for (int i = 0; i < strlen(details.email); i++)
            {
                if (details.email[i] == '@')
                {
                    for (int j = i; j < strlen(details.email); j++)
                    {
                        if (details.email[j] == '.' && details.email[j + 1] == 'c' &&
                            details.email[j + 2] == 'o' && details.email[j + 3] == 'm')
                        {
                            found = 1;
                        }
                    }
                }
            }
        }
        if (found == 0)
        {
            printf("Invalid Email ID\n");
            m = 1;
        }
    }
    printf("Enter the address: ");
    scanf(" %[^\n]", details.address);
    fprintf(fptr1, "%s,%s,%s,%s\n", details.name, details.mobile, details.email, details.address);
    fclose(fptr);
    fclose(fptr1);
    fptr = fopen("data.csv", "w");
    fptr1 = fopen("temp.csv", "r");
    copying(fptr, fptr1);
    fclose(fptr);
    fclose(fptr1);
}

void copying(FILE *fptr,FILE *fptr1)
{
    char ch;
    while((ch=fgetc(fptr1))!=EOF)
    {
        fputc(ch,fptr);
    }
}
void print_details()
{
    FILE *fptr=fopen("data.csv","r");
    int count;
    fscanf(fptr,"%d\n",&count);
    struct Address details[count];
    if(count==0)
    {
            printf("Addressbook is Empty\n");
            fclose(fptr);
            return;
    }
    for (int i = 0; i < count; i++)
    {
        fscanf(fptr, " %[^,],%[^,],%[^,],%[^\n]\n", details[i].name, details[i].mobile, details[i].email, details[i].address);
    }
    fclose(fptr);
    printf("**Menu**\n");
    printf("1. Print in a-z order\n2. Print in z-a order\n3. Print in normal order\n");
    int option;
    printf("Enter the option: ");
    scanf("%d", &option);
    switch (option) 
    {
        case 1:  // a-z order
            for (int i = 0; i < count - 1; i++)
            {
                for (int j = 0; j < count-i-1; j++) 
                {
                    if (strcmp(details[j].name, details[j+1].name) > 0)
                    {
                        struct Address temp = details[j];
                        details[j] = details[j+1];
                        details[j+1] = temp;
                    }
                }
            }
            break;
        case 2:  // z-a order
            for (int i = 0; i < count - 1; i++)
            {
                for (int j = 0; j < count-i-1; j++)
                {
                    if (strcmp(details[j].name, details[j+1].name) < 0) 
                    {
                        struct Address temp = details[j];
                        details[j] = details[j+1];
                        details[j+1] = temp;
                    }
                }
            }
            break;
        case 3:  // normal order
            break;
        default:
            printf("Invalid option\n");
            return;
    }
    for (int i = 0; i < count; i++) 
    {
        printf("*******Contact %d*******\n", i + 1);
        printf("Name: %s\n", details[i].name);
        printf("Mobile No: %s\n", details[i].mobile);
        printf("E-mail: %s\n", details[i].email);
        printf("Address: %s\n", details[i].address);
    }

}
void search_details()
{
    int found=0,ffound=0;
    FILE *fptr=fopen("data.csv","r");
    struct Address details;
    char search[30];
    printf("**Menu**\n");
    printf("1.Search by Name\n2.Search by Mobile No\n3.Search by Email\n4.Search by Address\n");
    int eoption;
    printf("Enter the option: ");
    scanf("%d",&eoption);
    switch(eoption)
            {
                case 1:
                        printf("Enter the name: ");
                        scanf(" %[^\n]",search);
                        break;
                case 2: printf("Enter the mobile: ");
                        scanf(" %[^\n]",search);
                        break;
                case 3: printf("Enter the email: ");
                        scanf(" %[^\n]",search);
                        break;
                case 4: printf("Enter the address: ");
                        scanf(" %[^\n]",search);
                        break;
                default:
                        printf("Invalid option, Please enter correct option\n");
                        return;


            }
    int count;
    fscanf(fptr,"%d\n",&count);
    int record=0;
    for(int i=0;i<count;i++)
    {
        fscanf(fptr," %[^,],%[^,],%[^,],%[^\n]\n",details.name,details.mobile,details.email,details.address);
        if(eoption==1&&strcmp(details.name,search)==0||eoption==2&&strcmp(details.mobile,search)==0||
            eoption==3&&strcmp(details.email,search)==0||eoption==4&&strcmp(details.address,search)==0)
        {
            found=i;
            record++;
        }
    }
    if(record>1)
    {
            switch(eoption)
            {
                case 1: printf("Multiple Contacts found with same name--\n");
                        break;
                case 2: printf("Multiple Contacts found with same mobile--\n");
                        break;
                case 3: printf("Multiple Contacts found with same email--\n");
                        break;
                case 4: printf("Multiple Contacts found with same Address--\n");
                        break;
                default: return;
            }
            printf("Search by Mobile or Mail\n");
            int option;
            char insearch[30];
            printf("1.Mobile\n2.Email\nEnter the option:");
            scanf("%d",&option);
            switch(option)
            {
                case 1: printf("Enter the mobile: ");
                        scanf(" %[^\n]",insearch);
                        break;
                case 2: printf("Enter the email: ");
                        scanf(" %[^\n]",insearch);
                        break;
                default:printf("Invalid option\n");
                        return;
            }
            rewind(fptr);
            fscanf(fptr,"%d\n",&count);
            for(int i=0;i<count;i++)
            {
                fscanf(fptr," %[^,],%[^,],%[^,],%[^\n]\n",details.name,details.mobile,details.email,details.address);
                if(option==1&&strcmp(details.mobile,insearch)==0||option==2&&strcmp(details.email,insearch)==0)
                {
                 found=i;
                 ffound=1;
                 break;
                }
            }

    }
    else if(record==1)
    {
        ffound=1;
    }
    if(ffound)
    {
        rewind(fptr);
        fscanf(fptr,"%d\n",&count);
        for(int i=0;i<count;i++)
        {
            fscanf(fptr," %[^,],%[^,],%[^,],%[^\n]\n",details.name,details.mobile,details.email,details.address);
            if(found==i)
            {
                printf("*******Contact Found*******\n");
                printf("Name: %s\n",details.name);
                printf("Mobile  No: %s\n",details.mobile);
                printf("E-mail: %s\n",details.email);
                printf("Address: %s\n",details.address);
            }
        }
    }
    else
    {
        printf("Contact not found\n");
    }
    fclose(fptr);

}
void edit_details()
{
    FILE *fptr=fopen("data.csv","r");
    FILE *fptr1=fopen("temp.csv","w");
    char edit[10];
    struct Address details;
    struct Address cdetails;
    printf("**Menu**\n");
    printf("1.Edit by Name\n2.Edit by Mobile No\n3.Edit by Email\n4.Edit by Address\n");
    int eoption;
    printf("Enter the option: ");
    scanf("%d",&eoption);
    switch(eoption)
    {
        case 1: printf("Enter the name: ");
                scanf(" %[^\n]",edit);
                break;
        case 2: printf("Enter the mobile: ");
                scanf(" %[^\n]",edit);
                break;
        case 3: printf("Enter the email: ");
                scanf(" %[^\n]",edit);
                break;
        case 4: printf("Enter the address: ");
                scanf(" %[^\n]",edit);
                break;
        default:
                printf("Invalid option, Please enter correct option\n");
                return;
    }
    int count,flag=0,found;
    fscanf(fptr,"%d\n",&count);
    int record=0;
    for(int i=0;i<count;i++)
    {
        fscanf(fptr," %[^,],%[^,],%[^,],%[^\n]\n",details.name,details.mobile,details.email,details.address);
        if(eoption==1&&strcmp(details.name,edit)==0||eoption==2&&strcmp(details.mobile,edit)==0||
                eoption==3&&strcmp(details.email,edit)==0||eoption==4&&strcmp(details.address,edit)==0)
        {
            found=i;
            record++;
        }
    }
    if(record>1)
    {
        switch(eoption)
            {
                case 1: printf("Multiple Contacts found with same name--\n");
                        break;
                case 2: printf("Multiple Contacts found with same mobile--\n");
                        break;
                case 3: printf("Multiple Contacts found with same email--\n");
                        break;
                case 4: printf("Multiple Contacts found with same Address--\n");
                        break;
                default:
                        return;
            }
            printf("Edit by Mobile or Mail\n");
            int option;
            char inedit[30];
            printf("1.Mobile\n2.Email\nEnter the option:");
            scanf("%d",&option);
            switch(option)
            {
                case 1: printf("Enter the mobile: ");
                        scanf(" %[^\n]",inedit);
                        break;
                case 2: printf("Enter the email: ");
                        scanf(" %[^\n]",inedit);
                        break;
                default:printf("Invalid option\n");
                        return;
            }
            rewind(fptr);
            fscanf(fptr,"%d\n",&count);
            for(int i=0;i<count;i++)
            {
                fscanf(fptr," %[^,],%[^,],%[^,],%[^\n]\n",details.name,details.mobile,details.email,details.address);
                if(option==1&&strcmp(details.mobile,inedit)==0||option==2&&strcmp(details.email,inedit)==0)
                {
                 flag=1;
                 found=i;
                 break;
                }
            }
        
    }
    else if(record==1)
    {
        flag=1;
    }
    int ffound=0;
    if(flag)
    {
            rewind(fptr);
            fscanf(fptr,"%d\n",&count);
            fprintf(fptr1,"%d\n",count);
            for(int i=0;i<count;i++)
            {
                fscanf(fptr," %[^,],%[^,],%[^,],%[^\n]\n",details.name,details.mobile,details.email,details.address);
                if(found==i)
                {
                    ffound=1;
                    printf("**Menu**\n");
                    printf("1.Name\n2.Mobile No\n3.Email\n4.Address\n");
                    int eeoption;
                    printf("Enter the option: ");
                    scanf("%d",&eeoption);
                    switch(eeoption)
                    {
                        case 1:
                            printf("Enter the name: ");
                            scanf(" %[^\n]",details.name);
                            break;
                        case 2:
                            printf("Enter the mobile: ");
                            scanf(" %[^\n]",details.mobile);
                            break;
                        case 3:
                            printf("Enter the mail: ");
                            scanf(" %[^\n]",details.email);
                            break;
                        case 4: 
                            printf("Enter the address: ");
                            scanf(" %[^\n]",details.address);
                            break;
                        default:
                            printf("Invalid option, Please enter correct option\n");
                            return;
                    }
                }
                fprintf(fptr1,"%s,%s,%s,%s\n",details.name,details.mobile,details.email,details.address);
            }
    }
    fclose(fptr);
    fclose(fptr1);
    if(ffound)
    {
        fptr=fopen("data.csv","w");
        fptr1=fopen("temp.csv","r");
        copying(fptr,fptr1);
        fclose(fptr);
        fclose(fptr1);
        printf("Details edited sucessfully\n");
    }
    else
    {
        printf("Contact not found\n");
    }


}
void delete_details()
{
    FILE *fptr=fopen("data.csv","r");
    FILE *fptr1=fopen("temp.csv","w");
    char delete[30];
    struct Address details;
    printf("**Menu**\n");
    printf("1.Delete by Name\n2.Delete by Mobile No\n3.Delete by Email\n4.Delete by Address\n");
    int eoption;
    printf("Enter the option: ");
    scanf("%d",&eoption);
    switch(eoption)
    {
        case 1: printf("Enter the name: ");
                scanf(" %[^\n]",delete);
                break;
        case 2: printf("Enter the mobile: ");
                scanf(" %[^\n]",delete);
                break;
        case 3: printf("Enter the email: ");
                scanf(" %[^\n]",delete);
                break;
        case 4: printf("Enter the address: ");
                scanf(" %[^\n]",delete);
                break;
        default:
                printf("Invalid option, Please enter correct option\n");
                return;
    }
    int count,record=0,flag=0,found=0;
    fscanf(fptr,"%d\n",&count);
    for(int i=0;i<count;i++)
    {
        fscanf(fptr," %[^,],%[^,],%[^,],%[^\n]\n",details.name,details.mobile,details.email,details.address);
       if(eoption==1&&strcmp(details.name,delete)==0||eoption==2&&strcmp(details.mobile,delete)==0||
       eoption==3&&strcmp(details.email,delete)==0||eoption==4&&strcmp(details.address,delete)==0)
        {
            found=i;
            record++;

        }
    }
    if(record>1)
    {
        switch(eoption)
            {
                case 1: printf("Multiple Contacts found with same name--\n");
                        break;
                case 2: printf("Multiple Contacts found with same mobile--\n");
                        break;
                case 3: printf("Multiple Contacts found with same email--\n");
                        break;
                case 4: printf("Multiple Contacts found with same Address--\n");
                        break;
                default: printf("Invalid option\n");
                         return;
            }
            printf("Delete by Mobile or Mail\n");
            int option;
            char indelete[30];
            printf("1.Mobile\n2.Email\nEnter the option:");
            scanf("%d",&option);
            switch(option)
            {
                case 1: printf("Enter the mobile: ");
                        scanf(" %[^\n]",indelete);
                        break;
                case 2: printf("Enter the email: ");
                        scanf(" %[^\n]",indelete);
                        break;
                default:printf("Invalid option\n");
                        return;
            }
            rewind(fptr);
            fscanf(fptr,"%d\n",&count);
            for(int i=0;i<count;i++)
            {
                fscanf(fptr," %[^,],%[^,],%[^,],%[^\n]\n",details.name,details.mobile,details.email,details.address);
                if(option==1&&strcmp(details.mobile,indelete)==0||option==2&&strcmp(details.email,indelete)==0)
                {
                 flag=1;
                 found=i;
                 break;
                }
            }
        
    }
    else if(record==1)
    {
        flag=1;
    }
    int ffound=0;
    if(flag)
    {
            rewind(fptr);
            fscanf(fptr,"%d\n",&count);
            fprintf(fptr1,"%d\n",count-1);
            for(int i=0;i<count;i++)
            {
                fscanf(fptr," %[^,],%[^,],%[^,],%[^\n]\n",details.name,details.mobile,details.email,details.address);
                if(found==i)
                {
                    ffound=1;
                    continue;
                }
                fprintf(fptr1,"%s,%s,%s,%s\n",details.name,details.mobile,details.email,details.address);
            }
    }
    
    fclose(fptr);
    fclose(fptr1);
    if(ffound)
    {
        char cchoice;
        printf("Do you want to delete this contact(y/Y): ");
        scanf(" %c",&cchoice);
        if(cchoice=='y'||cchoice=='Y')
        {
                fptr=fopen("data.csv","w");
                fptr1=fopen("temp.csv","r");
                copying(fptr,fptr1);
                fclose(fptr);
                fclose(fptr1);
                printf("Details deleted sucessfully\n");
        }
        else
        {
                printf("Contact not deleted \n");
        }

    }
    else
    {
        printf("Contact not found\n");
    }
} 
