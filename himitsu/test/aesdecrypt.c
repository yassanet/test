#include        <string.h>
#include        <stdio.h>
#include        <stdlib.h>
#include        <openssl/evp.h>
#include        <openssl/aes.h>

int main(int argc, char *argv[])
{
EVP_CIPHER_CTX  de;
char    *key,*data,*ptr;
char    buf[80];
int     datasize,c;
int     p_len,f_len=0;
char    *plaintext;

        if(argc<=2){
                fprintf(stderr,"aesdecrypt key data\n");
                return(-1);
        }
        key=argv[1];
        if(strlen(key)!=EVP_CIPHER_key_length(EVP_aes_128_ecb())){
                fprintf(stderr,"key length must be %d\n",EVP_CIPHER_key_length(EVP_aes_128_ecb()));
                return(-1);
        }

        data=malloc(strlen(argv[2]));
        for(ptr=argv[2],c=0;*ptr!='\0';ptr+=2,c++){
                buf[0]=*ptr;
                buf[1]=*(ptr+1);
                buf[2]='\0';
                data[c]=strtol(buf,NULL,16);
        }
        datasize=c;

        EVP_CIPHER_CTX_init(&de);
        EVP_DecryptInit_ex(&de,EVP_aes_128_ecb(),NULL,(unsigned char *)key,NULL);

        p_len=datasize;
        plaintext=calloc(p_len+1,sizeof(char));

        EVP_DecryptUpdate(&de,(unsigned char *)plaintext,&p_len,(unsigned char *)data,datasize);
        EVP_DecryptFinal_ex(&de,(unsigned char *)(plaintext+p_len),&f_len);

        plaintext[p_len+f_len]='\0';
        printf("[%s]\n",plaintext);

        EVP_CIPHER_CTX_cleanup(&de);

        free(plaintext);

        free(data);

        return(0);
}
