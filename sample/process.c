/******************************************************************************
 *                                                                            *
 *      process.c                                                             *
 *                                                                            *
 *      プロセス                                                              *
 *                                                                            *
 ******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "process.h"
#include "inifile.h"
#include "pg.h"
#include "ThreadManForUser.h"
#include "LoadExecForUser.h"
#include "sceCtrl.h"
#include "scePower.h"

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

static int exitcallback(void);
static void powercallback(int unknown, int pwrflags);
static int callbackthread(void *arg);
static int setupcallbacks(void);
static void iniread(void);
static void iniwrite(void);
// ----> デバッグ INIファイル -------------------------------------------------
static int dbgprintf(unsigned long x, unsigned long y, unsigned long color, const char *format, ...);
static void dbgstart(void);
static void dbgread(void);
static void dbgwrite(void);
static void dbgdata(void);
// <---- デバッグ INIファイル -------------------------------------------------

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ *
		グローバル定数定義
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ *
		グローバル変数定義
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static char path_exe[256];					// 実行パス
static char fname_ini[256];					// INIファイル名
static int end_flag;						// 終了フラグ

static int screen_mode;
static int screen_left;
static int screen_top;

static int keycfg_select;
static int keycfg_start;
static int keycfg_up;
static int keycfg_right;
static int keycfg_down;
static int keycfg_left;
static int keycfg_ltrigger;
static int keycfg_rtrigger;
static int keycfg_triangle;
static int keycfg_circle;
static int keycfg_cross;
static int keycfg_square;

static char graph_bmp[256];
static long graph_fgcolor;
static long graph_bgcolor;

static int sound_enabled;
static int sound_sbits;
static long sound_srate;

static char file_path[256];
static char file_filter[256];

/******************************************************************************
 *
 * 関 数 名：procinit / プロセス初期設定
 *
 * 呼出形式：#include "process.h"
 *           void procinit(char *argv);
 *
 * 解    説：プロセスの初期設定をします。
 *
 * 戻 り 値：ありません。
 *
 ******************************************************************************/

void procinit(char *argv)
{
	char *p;								// ポインタ

	setupcallbacks();
	pgInit();
	pgScreenFrame(2,0);
	sceCtrlInit(0);
	sceCtrlSetAnalogMode(0);

	strcpy(path_exe, argv);
	if ( ( p = strrchr(path_exe, '/') ) != NULL ) {
		p++;
	}
	else {
		p = path_exe;
	}
	*p = '\0';

	strcpy(fname_ini, path_exe);
	strcat(fname_ini, "sample.ini");

	end_flag = 0;
}

/******************************************************************************
 *
 * 関 数 名：procloop / プロセスループ処理
 *
 * 呼出形式：#include "process.h"
 *           int procloop(int *step);
 *
 * 解    説：プロセスのループ処理をします。処理後はstepに示されるステップが更新
 *           されます。
 *
 * 戻 り 値：続行する場合は0を返します。終了する場合は1を返します。
 *
 ******************************************************************************/

int procloop(int *step)
{
	if ( end_flag == 1 ) return 1;

	switch ( *step ) {
	case 0:
// ----> デバッグ INIファイル -------------------------------------------------
		dbgstart();
// <---- デバッグ INIファイル -------------------------------------------------
		*step = 1;
		break;

	case 1:
		iniread();							// INIファイル読み込み
// ----> デバッグ INIファイル -------------------------------------------------
		dbgread();
// <---- デバッグ INIファイル -------------------------------------------------
		*step = 2;
		break;

	case 2:
		iniwrite();							// INIファイル書き込み
// ----> デバッグ INIファイル -------------------------------------------------
		dbgwrite();
// <---- デバッグ INIファイル -------------------------------------------------
		*step = 3;
		break;

	case 3:
		break;
	}

	return 0;
}

/******************************************************************************
 *
 * 関 数 名：procend / プロセス終了処理
 *
 * 呼出形式：#include "process.h"
 *           void procend(void);
 *
 * 解    説：プロセスの終了処理をします。
 *
 * 戻 り 値：ありません。
 *
 ******************************************************************************/

void procend(void)
{
	sceKernelExitGame();
}

/******************************************************************************
 *
 * 関 数 名：exitcallback / 脱出コールバック
 *
 * 呼出形式：static
 *           int exitcallback(void);
 *
 * 解    説：HOMEボタン押下時のコールバック処理をします。
 *
 * 戻 り 値：0を返します。
 *
 ******************************************************************************/

static int exitcallback(void)
{
	end_flag = 1;

	return 0;
}

/******************************************************************************
 *
 * 関 数 名：powercallback / 電源コールバック
 *
 * 呼出形式：static
 *           void powercallback(int unknown, int pwrflags);
 *
 * 解    説：電源スライド時のコールバック処理をします。
 *
 * 戻 り 値：ありません。
 *
 ******************************************************************************/

static void powercallback(int unknown, int pwrflags)
{
}

/******************************************************************************
 *
 * 関 数 名：callbackthread / コールバックスレッド
 *
 * 呼出形式：static
 *           int callbackthread(void *arg);
 *
 * 解    説：コールバックスレッドを作成して、コールバックのポーリングを開始しま
 *           す。
 *
 * 戻 り 値：0を返します。
 *
 ******************************************************************************/

static int callbackthread(void *arg)
{
	int cbid;								// コールバックID

	cbid = sceKernelCreateCallback("Exit Callback", exitcallback);
	sceKernelRegisterExitCallback(cbid);
	cbid = sceKernelCreateCallback("Power Callback", powercallback);
	scePowerRegisterCallback(0, cbid);

	sceKernelPollCallbacks();

	return 0;
}

/******************************************************************************
 *
 * 関 数 名：setupcallbacks / コールバック設定
 *
 * 呼出形式：static
 *           int setupcallbacks(void);
 *
 * 解    説：コールバックを設定します。
 *
 * 戻 り 値：設定したコールバックのスレッドIDを返します。
 *
 ******************************************************************************/

static int setupcallbacks(void)
{
	int thid = 0;

	if ( ( thid = sceKernelCreateThread("Update Thread", (pg_threadfunc_t)callbackthread, 0x11, 0xFA0, 0, 0) ) < 0 ) return thid;

	sceKernelStartThread(thid, 0, 0);

	return thid;
} 

/******************************************************************************
 *
 * 関 数 名：iniread / INIファイル読み込み
 *
 * 呼出形式：static
 *           void iniread(void);
 *
 * 解    説：INIファイルから設定値を読み込みます。
 *
 * 戻 り 値：ありません。
 *
 ******************************************************************************/

static void iniread(void)
{
	ini_open(fname_ini);

	screen_mode = ini_readinteger("Screen", "Mode", 2);
	screen_left = ini_readinteger("Screen", "Left", 112);
	screen_top = ini_readinteger("Screen", "Top", 16);

	keycfg_select = ini_readinteger("KeyConfig", "Select", 1);
	keycfg_start = ini_readinteger("KeyConfig", "Start", 2);
	keycfg_up = ini_readinteger("KeyConfig", "Up", 3);
	keycfg_right = ini_readinteger("KeyConfig", "Right", 4);
	keycfg_down = ini_readinteger("KeyConfig", "Down", 5);
	keycfg_left = ini_readinteger("KeyConfig", "Left", 6);
	keycfg_ltrigger = ini_readinteger("KeyConfig", "LTrigger", 7);
	keycfg_rtrigger = ini_readinteger("KeyConfig", "RTrigger", 8);
	keycfg_triangle = ini_readinteger("KeyConfig", "Triangle", 9);
	keycfg_circle = ini_readinteger("KeyConfig", "Circle", 10);
	keycfg_cross = ini_readinteger("KeyConfig", "Cross", 11);
	keycfg_square = ini_readinteger("KeyConfig", "Square", 12);

	ini_readstring("Graphics", "BMP", "sample.bmp", graph_bmp);
	graph_fgcolor = ini_readlong("Graphics", "FGColor", 0);
	graph_bgcolor = ini_readlong("Graphics", "BGColor", 0x7fff);

	sound_enabled = ini_readinteger("Sound", "Enabled", 1);
	sound_sbits = ini_readinteger("Sound", "SampleBits", 8);
	sound_srate = ini_readlong("Sound", "SampleRate", 44100);

	ini_readstring("File", "Path", "ms0:/File", file_path);
	ini_readstring("File", "Filter", "TXT", file_filter);

	ini_close();
}

/******************************************************************************
 *
 * 関 数 名：iniwrite / INIファイル書き込み
 *
 * 呼出形式：static
 *           void iniwrite(void);
 *
 * 解    説：INIファイルに設定値を書き込みます。
 *
 * 戻 り 値：ありません。
 *
 ******************************************************************************/

static void iniwrite(void)
{
	ini_open(fname_ini);

	ini_writeinteger("Screen", "Mode", screen_mode);
	ini_writeinteger("Screen", "Left", screen_left);
	ini_writeinteger("Screen", "Top", screen_top);

	ini_writeinteger("KeyConfig", "Select", keycfg_select);
	ini_writeinteger("KeyConfig", "Start", keycfg_start);
	ini_writeinteger("KeyConfig", "Up", keycfg_up);
	ini_writeinteger("KeyConfig", "Right", keycfg_right);
	ini_writeinteger("KeyConfig", "Down", keycfg_down);
	ini_writeinteger("KeyConfig", "Left", keycfg_left);
	ini_writeinteger("KeyConfig", "LTrigger", keycfg_ltrigger);
	ini_writeinteger("KeyConfig", "RTrigger", keycfg_rtrigger);
	ini_writeinteger("KeyConfig", "Triangle", keycfg_triangle);
	ini_writeinteger("KeyConfig", "Circle", keycfg_circle);
	ini_writeinteger("KeyConfig", "Cross", keycfg_cross);
	ini_writeinteger("KeyConfig", "Square", keycfg_square);

	ini_writestring("Graphics", "BMP", graph_bmp);
	ini_writelong("Graphics", "FGColor", graph_fgcolor);
	ini_writelong("Graphics", "BGColor", graph_bgcolor);

	ini_writeinteger("Sound", "Enabled", sound_enabled);
	ini_writeinteger("Sound", "SampleBits", sound_sbits);
	ini_writelong("Sound", "SampleRate", sound_srate);

	ini_writestring("File", "Path", file_path);
	ini_writestring("File", "Filter", file_filter);

	ini_close();
}

// ----> デバッグ INIファイル -------------------------------------------------

static int dbgprintf(unsigned long x, unsigned long y, unsigned long color, const char *format, ...)
{
	va_list argp;
	char buff[1024];
	int len;

	va_start(argp, format);
	len = vsprintf(buff, format, argp);
	va_end(argp);

	pgPrint(x, y, color, buff);

	return len;
}

static void dbgstart(void)
{
	pgFillvram(0);
	dbgprintf(0, 0, 0xffff, "csd library sample Start");
	pgScreenFlipV();
	pgWaitVn(10);
}

static void dbgread(void)
{
	pgFillvram(0);
	dbgprintf(0, 0, 0xffff, "csd library sample Read");
	dbgdata();
	pgScreenFlipV();
	pgWaitVn(300);
}

static void dbgwrite(void)
{
	pgFillvram(0);
	dbgprintf(0, 0, 0xffff, "csd library sample Write");
	dbgdata();
	pgScreenFlipV();
	pgWaitVn(10);
}

static void dbgdata(void)
{
	dbgprintf(0, 2, 0xffff, "%-15s = %d", "screen mode", screen_mode);
	dbgprintf(0, 3, 0xffff, "%-15s = %d", "screen left", screen_left);
	dbgprintf(0, 4, 0xffff, "%-15s = %d", "screen top", screen_top);

	dbgprintf(0, 6, 0xffff, "%-15s = %d", "keycfg select", keycfg_select);
	dbgprintf(0, 7, 0xffff, "%-15s = %d", "keycfg start", keycfg_start);
	dbgprintf(0, 8, 0xffff, "%-15s = %d", "keycfg up", keycfg_up);
	dbgprintf(0, 9, 0xffff, "%-15s = %d", "keycfg right", keycfg_right);
	dbgprintf(0, 10, 0xffff, "%-15s = %d", "keycfg down", keycfg_down);
	dbgprintf(0, 11, 0xffff, "%-15s = %d", "keycfg left", keycfg_left);
	dbgprintf(0, 12, 0xffff, "%-15s = %d", "keycfg ltrigger", keycfg_ltrigger);
	dbgprintf(0, 13, 0xffff, "%-15s = %d", "keycfg rtrigger", keycfg_rtrigger);
	dbgprintf(0, 14, 0xffff, "%-15s = %d", "keycfg triangle", keycfg_triangle);
	dbgprintf(0, 15, 0xffff, "%-15s = %d", "keycfg circle", keycfg_circle);
	dbgprintf(0, 16, 0xffff, "%-15s = %d", "keycfg cross", keycfg_cross);
	dbgprintf(0, 17, 0xffff, "%-15s = %d", "keycfg square", keycfg_square);

	dbgprintf(0, 19, 0xffff, "%-15s = %s", "graph bmp", graph_bmp);
	dbgprintf(0, 20, 0xffff, "%-15s = %ld", "graph fgcolor", graph_fgcolor);
	dbgprintf(0, 21, 0xffff, "%-15s = %ld", "graph bgcolor", graph_bgcolor);

	dbgprintf(0, 23, 0xffff, "%-15s = %d", "sound enabled", sound_enabled);
	dbgprintf(0, 24, 0xffff, "%-15s = %d", "sound sbits", sound_sbits);
	dbgprintf(0, 25, 0xffff, "%-15s = %ld", "sound srate", sound_srate);

	dbgprintf(0, 27, 0xffff, "%-15s = %s", "file path", file_path);
	dbgprintf(0, 28, 0xffff, "%-15s = %s", "file filter", file_filter);
}

// <---- デバッグ INIファイル -------------------------------------------------

