#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

int size_of_image(FILE *fp1)
{
	int width, height;

	fseek(fp1, 0x12, SEEK_SET);	//Seek to the Width position
	fread(&width, sizeof(int), 1, fp1);	//Reading Width
	fread(&height, sizeof(int), 1, fp1);	//Read height
	printf("Dimensions of the Image is %d x %d \n", width, height);
	fseek(fp1, 0L, SEEK_SET);	//Seek to the start position

	return ((width * height * 3) / 8);
}

int my_get_bit(char byte, int bit)
{
	return ((byte >> 8 - bit) & 1);
}

//encription of message
void stega_encrypt(FILE *fp1, FILE *fp2, FILE *fp3)
{
	char file_buff = 0, msg_buff = 0, ch;	//temp var for one byte from file and msg
	int i;
	int bit_msg;
	while((msg_buff = fgetc(fp2)) != EOF)
	{
		for(i = 1; i <= 8; i++)
		{
			file_buff = fgetc(fp1);

			int file_byte_lsb = (file_buff & 1);

			bit_msg = my_get_bit(msg_buff, i);

			if(file_byte_lsb == bit_msg)
			{
				fputc(file_buff, fp3);
			}
			else
			{
				if(file_byte_lsb == 0)
					file_buff = (file_buff | 1);
				else
					file_buff = (file_buff ^ 1);

				fputc(file_buff, fp3);
			}
		}
	}

	/*copying rest of data */
	while(!feof(fp1))
	{
		char tmp_cpy = fgetc(fp1);
		fputc(tmp_cpy,fp3);

	}

	if(msg_buff == EOF)
		printf("\n*** Secret Message Encrypted Successfully ***\n");
	else
		printf("\n*** Failed Encrypting ***\n");
}

void secret_text(FILE *fp2, char *a)
{
    int i = 0;
	while (a[i] != '\0')
	{
		putc(a[i],fp2);	//puts secret text to file
        i++;
	}
}

int encryption()
{
    char c[50], msg[200];
    printf("Enter name of the image file : ");
    scanf("%s", c);

    FILE *ip, *op;
    if((ip = fopen(c, "r+")) == NULL) 
	{
		printf("Could not open file %s.\nAborting\n", c);
		return 1;
	}

    int size_img = size_of_image(ip);
    printf("Total %d characters can be strored in %s", size_img, c);
    
    do
    {
        printf("\nEnter the message to be hidden : ");
        scanf("%s", msg);
        if(strlen(msg) > size_img)
            printf("Enter characters less than %d", size_img);
    } while (strlen(msg) > size_img);
    FILE *secret;
    secret = fopen("secret.txt", "w+");
    if(secret == NULL)
    {
        fprintf(stderr, "Cannot create output file secret.txt\n");
		exit(1);
    }
    secret_text(secret, msg);

    op = fopen("img-secret-in-c.bmp", "w+");
	if (op == NULL) 
	{
		fprintf(stderr, "Cannot create output file img-secret-in-c.bmp\n");
		exit(1);
	}

    //copying 54 header file
	int i, count = 0;
	char tmp_cpy;
	rewind(ip);	//Goes back to the beginning of the file
	for(i = 0;i < 54; i++)
	{
		tmp_cpy = fgetc(ip);
		fputc(tmp_cpy,op);
		count++;
	} 

    if(i == count)
		printf("\n*** Sucessfully copied 54 header bytes ***\n");
	else
	{
		printf("\n*** Failed to copy 54 header bytes ***\n");
		return 0;
	}

    stega_encrypt(ip,secret,op);

    fclose(secret);
    fclose(op);
    fclose(ip);
}

void size_decryption(FILE *pf1, int *size_txt)
{
	int file_buff = 0, i;
	int ch, bit_msg;
	for (i = 0; i < 8; i++)
	{
		ch = fgetc(pf1);
		bit_msg = (ch & 1);
		if (bit_msg)
		{
			file_buff = (file_buff << 1) | 1;
		}
		else
		{
			file_buff = file_buff << 1;
		}
	}
	*size_txt = file_buff;
}

void secret_decryption(int size_txt, FILE *pf1, FILE *pf2)
{
	int file_buff=0, i, j = 0, k = 0;
	int ch,bit_msg;
	char output[250] = {0};
	for (i = 0; i < (size_txt * 8); i++)
	{
		j++;
		ch = fgetc(pf1);
		bit_msg = (ch & 1);
		if (bit_msg)
		{
			file_buff = (file_buff << 1) | 1;
		}
		else
		{
			file_buff = file_buff << 1;
		}

		if (j == 8)
		{
			putc(file_buff, pf2);
			output[k++] = file_buff;
			j = 0;
			file_buff = 0;
		}
	}
	printf("\n*** Secret Text Is ==> %s\n\n", output);
}

int decryption()
{
	FILE *ip, *op;
	if((ip = fopen("img-secret-in-c.bmp", "r+")) == NULL) 
	{
		printf("Could not open file img-secret-in-c.bmp.\nAborting\n");
		return 1;
	}
	fseek(ip,54,SEEK_SET);
	if((op = fopen("img-decrypt.txt", "w+")) == NULL) 
	{
		printf("Could not open file img-decrypt.txt.\nAborting\n");
		return 1;
	}
	int size_txt;
	size_decryption(ip, &size_txt);
	secret_decryption(size_txt, ip, op);

	printf("*** The Secret Text Is Copied To ==> img-decrypt.txt\n\n");

	fclose(ip);
	fclose(op);
}

int main()
{
	char ch;
	int n;
	do
	{
		printf("1. Encrypt data in image\n2. Decrypt data from image\n3. Exit\n");
		scanf("%d", &n);
		switch (n)
		{
			case 1: if(encryption() == 1)
					{
						printf("Error Exitting !!\n");
						exit(0);
					}
					break;
			case 2: if(decryption() == 1)
					{
						printf("Error Exitting !!\n");
						exit(0);
					}
					break;
			case 3: printf("Exiting !!\n");
					exit(0);
			default:printf("Please enter a correct choice!\n");
					break;
		}
		printf("Do you want to try again [y/N]: ");
		scanf(" %c", &ch);
	} while (ch == 'y' || ch == 'Y');
    return 0;
}