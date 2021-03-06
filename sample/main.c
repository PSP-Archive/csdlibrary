/******************************************************************************
 *                                                                            *
 *      main.c                                                                *
 *                                                                            *
 *      メイン                                                                *
 *                                                                            *
 ******************************************************************************/

#include "main.h"
#include "process.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ *
		データ型宣言
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

typedef unsigned char	u_char;
typedef unsigned short	u_short;
typedef unsigned int	u_int;
typedef unsigned long	u_long;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ *
		プロトタイプ宣言
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ *
		グローバル定数定義
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ *
		グローバル変数定義
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/******************************************************************************
 *
 * 関 数 名：xmain / メイン
 *
 * 呼出形式：#include "main.h"
 *           int xmain(int argc, char *argv);
 *
 * 解    説：メインの処理をします。
 *
 * 戻 り 値：0を返します。
 *
 ******************************************************************************/

int xmain(int argc, char *argv)
{
	int step = 0;

	init();									// 初期設定
	procinit(argv);							// プロセス初期設定

	while ( 1 ) {
		if ( procloop(&step) == 1 ) break;	// プロセスループ処理
	}

	procend();								// プロセス終了処理
	end();									// 終了処理

	return 0;
}

/******************************************************************************
 *
 * 関 数 名：init / 初期設定
 *
 * 呼出形式：#include "main.h"
 *           void init(void);
 *
 * 解    説：初期設定をします。
 *
 * 戻 り 値：ありません。
 *
 ******************************************************************************/

void init(void)
{
}

/******************************************************************************
 *
 * 関 数 名：end / 終了処理
 *
 * 呼出形式：#include "main.h"
 *           void end(void);
 *
 * 解    説：終了処理をします。
 *
 * 戻 り 値：ありません。
 *
 ******************************************************************************/

void end(void)
{
}

