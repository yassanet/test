#include        <string.h>
#include        <stdio.h>
#include        <stdlib.h>
#include        <openssl/evp.h>
#include        <openssl/aes.h>

int main(int argc,char *argv[])
{
EVP_CIPHER_CTX  en;
char    *key,*data;
int     datasize;
int     i,c_len,f_len=0;
unsigned char   *ciphertext;

        if(argc<=2){
                fprintf(stderr,"aesencrypt key data\n");
                return(-1);
        }
        key=argv[1];
        if(strlen(key)!=EVP_CIPHER_key_length(EVP_aes_128_ecb())){
                fprintf(stderr,"key length must be %d\n",EVP_CIPHER_key_length(EVP_aes_128_ecb()));
                return(-1);
        }

        data=argv[2];
        datasize=strlen(data);

        EVP_CIPHER_CTX_init(&en);
        EVP_EncryptInit_ex(&en,EVP_aes_128_ecb(),NULL,(unsigned char *)key,NULL);

        c_len=datasize+EVP_MAX_BLOCK_LENGTH;
        ciphertext=calloc(c_len,sizeof(char));

        EVP_EncryptUpdate(&en,(unsigned char *)ciphertext,&c_len,(unsigned char *)data,datasize);
        EVP_EncryptFinal_ex(&en,(unsigned char *)(ciphertext+c_len),&f_len);

        for(i=0;i<c_len+f_len;i++){
                printf("%02x",ciphertext[i]);
        }
        putchar('\n');

        free(ciphertext);

        EVP_CIPHER_CTX_cleanup(&en);

        return(0);
}
