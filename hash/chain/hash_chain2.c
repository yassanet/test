/*
	hash(chain).
	key is string.
	data is string.
*/

#include <stdio.h>
#include <stdlib.h>

#include "myio.h"

#define TABLE_SIZE (100)  /* ハッシュ表の大きさ */

/* バケット */
struct cell
{
	int inuse;		/* 使用しているか */
	char key[128];            /* キー */
	char data[256];           /* データ */
	struct cell* next;  /* 次のセルへのチェイン */
};
struct cell *table[TABLE_SIZE];  /* ハッシュ表 */

/* プロトタイプ宣言 */
int hash(int key);
int add(int key, int data);
int* search(int key);
void clear(void);

int main(void)
{
	char command;
	char buffer[128];
	char key[128]
	char data[256];
	int* p;
	int i;
	
	do
	{
		puts( "コマンドを入力して下さい" );
		puts( "データを格納：a" );
		puts( "データを探索：b" );
		puts( "データをクリア：c" );
		puts( "終了：q" );
		myfgets(buffer, 2);
		sscanf(buffer, "%c", &command);
		
		switch( command )
		{
		case 'a':  /* データを格納 */
			puts( "キーを入力して下さい" );
			myfgets(buffer, 128);
			sscanf(buffer, "%d", &key);
			puts( "データを入力して下さい" );
			myfgets(buffer, 100);
			sscanf(buffer, "%d", &data);

			i = add( key, data );
			switch( i )
			{
			case 0:
				puts( "はじめての作成" );
				break;
			case 1:
				puts( "チェイン作成" );
				break;
			default:
				puts( "error" );
				break;
			}
			break;
			
		case 'b':  /* データを探索 */
			puts( "キーを入力して下さい" );
			myfgets(buffer, 4);
			sscanf(buffer, "%d", &key);
			
			p = search( key );
			if( p != NULL )
			{
				printf( "キー%dに対応するのは%d\n", key, *p );
			}
			else
			{
				printf( "キー%dに対応するデータはありません\n", key );
			}
			break;
			
		case 'c':  /* クリア */
			clear();
			break;
		
		case 'q':
			break;
			
		default:
			puts( "コマンドが正しくありません" );
			break;
		}
		
		printf( "\n\n" );
	}while( command != 'q' );
	
	/* ハッシュ表をクリア */
	clear();
	
	return 0;
}

/* ハッシュ関数 */
long hash(char *key)
{
	int i;
	long h = 0;
	int len = strlen(key);

	for(i = 0; i < len; i++) {
		h = h * 37 + key[i];
	}

	return labs(h);
}

/* ハッシュ表にデータを追加する */
int add(int key, int data)
{
	struct cell* p;
	struct cell* cell;
	int bucket;
	
	/* チェインのための領域を確保する */
	p = malloc( sizeof(struct cell) );
	if( p == NULL )
	{
		puts( "メモリ不足" );
		exit( 1 );  /* エラー終了 */
	}
	
	bucket = hash( key );  /* 追加位置を生成する */

	/* first instert */
	if( table[bucket] == NULL) {	
		p->key = key;
		p->data = data;
		p->inuse = 1;
		p->next = NULL;
		table[bucket] = p;

		return 0;
	}

	/* create chain */
	cell=table[bucket];
	while( cell != NULL ) {
		if( cell->next == NULL) {
			p->key = key;
			p->data = data;
			p->inuse = 1;
			p->next = NULL;
			cell->next = p;
			
			return 1;
		} else {
			cell = cell->next;
		}
	} 

	return -1;
}

/* ハッシュ表からデータを探索する */
int* search(int key)
{
	struct cell* p;
	int bucket;
	
	bucket = hash( key );  /* 追加位置を生成する */
	
	/* 連結リストを辿る */
	for( p=table[bucket]; p!=NULL; p=p->next )
	{
		if( key == p->key )
		{
			printf("search %d, ", p->data);
		}
	}
	

	/* 連結リストを辿る */
	for( p=table[bucket]; p!=NULL; p=p->next )
	{
		if( key == p->key )
		{
			return &p->data;
		}
	}
	
	return NULL;
}

/* ハッシュ表を空にする */
void clear(void)
{
	struct cell* p;
	struct cell* q;
	int i;

	/* malloc関数で領域が確保されていたら、解放する */
	for( i=0; i<TABLE_SIZE; ++i )
	{
		p = table[i];

		/* next を辿ってから、領域を解放しなければならない */
		while( p != NULL ){
			q = p;
			p = p->next;
			free( q );
		}

		table[i] = NULL;
	}
}
