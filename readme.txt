********************************************************************************

csd library for PSP

********************************************************************************

概要

  PSP開発用に作成した関数のライブラリです。

********************************************************************************

ライブラリ

  ライブラリの関数は以下のようになっています。

  ------------------------------------------------------------------------------

  Cライブラリ

    lib_c.a                             文字関数（ctype）
                                        標準入出力関数（stdioの一部）
                                        標準ライブラリ関数（stdlibの一部）
                                        メモリ・文字列関数（stringの一部）

  ------------------------------------------------------------------------------

  csdライブラリ

    libcsd.a                            メモリースティック入出力関数
                                        INIファイル処理関数
                                        日本語処理関数
                                        メモリ・文字列処理関数

********************************************************************************

フォルダ構成

  フォルダ構成は以下のようになっています。

  ------------------------------------------------------------------------------

  全体

    +- csdlibrary
      +- api-include
      +- bin
      +- doc
        +- lib_c
        +- libcsd
      +- include
      +- lib
      +- sample

  ------------------------------------------------------------------------------

  api-include

    API関数を呼び出すヘッダーファイルがあるフォルダです。

  ------------------------------------------------------------------------------

  bin

    サンプルプログラムのバイナリがあるフォルダです。
    サンプルプログラムをビルドすると新しいバイナリが置かれます。

  ------------------------------------------------------------------------------

  doc

    ドキュメントがあるフォルダです。

  ------------------------------------------------------------------------------

  lib_c

    Cライブラリの関数リファレンスがあるフォルダです。

  ------------------------------------------------------------------------------

  libcsd

    csdライブラリの関数リファレンスがあるフォルダです。

  ------------------------------------------------------------------------------

  include

    ライブラリの関数を呼び出すヘッダーファイルがあるフォルダです。

  ------------------------------------------------------------------------------

  lib

    ライブラリがあるフォルダです。

  ------------------------------------------------------------------------------

  sample

    サンプルプログラムがあるフォルダです。

********************************************************************************

開発環境

  私の現在の開発環境は以下のようになっています。

  ------------------------------------------------------------------------------

  PS2Dev
    PS2toolchain → PS2Dev_Setup.exe
    PS2toolchain → ps2dev-toolchain-mingw32-20050504.zip

  ------------------------------------------------------------------------------

  ツール
    Saturn Expedition Committee → outpatch.exe
    Internal RealiTy → elf2pbp.exe

  ------------------------------------------------------------------------------

  フォルダ構成

  +- D
    +- Program Files
      +- PS2Dev                         インストーラにより作成
        +- gcc                          インストーラにより作成
        +- ps2lib                       インストーラにより作成
        +- share                        インストーラにより作成
        +- tool                         追加

  D:\Program Files\PS2Dev
    PS2Dev_Setup.exeでインストール後、ps2dev-toolchain-mingw32-20050504.zipを
    上書きする。
    PS2Dev_Setup.exeのインストール中に環境変数を追加するか問い合わせがあるが、
    後述のmk.batを使用すれば環境変数を設定してビルドできるので追加しない。

  D:\Program Files\PS2Dev\tool
    outpatch.exe, elf2pbp.exeを追加する。

********************************************************************************

サンプルプログラム

  サンプルプログラムはsample.iniを読み込み、読み込んだデータを表示後、sample.ini
  に書き込みます。

  ------------------------------------------------------------------------------

  ビルド

    上記開発環境のようにPS2Devのインストールとツールの追加がされ、csdlibrary
    フォルダのmk.batの環境変数が正しく設定されていれば、mk.batの実行によりビルド
    できます。
    ビルドしてできたEBOOT.PBPはbinフォルダに作成されます。

  ------------------------------------------------------------------------------

  実行方法

    メモリーステッィクの\PSP\GAME\の下に適当にフォルダを作ってbinフォルダの中に
    あるEBOOT.PBPを入れてください。
    PSPのGAME → メモリースティック → csd library sampleを実行して下さい。
    設定 → 本体設定 → 本体情報を実行して「システムソフトウェア バージョン
    1.00」と表示されるPSP専用です。
    1.50以降のバージョンでは動作しません。

--------------------------------------------------------------------------------

自作プログラムへの組み込み方

  ライブラリのリンクはsampleフォルダのMakefile、csdlibraryフォルダの
  Makefile.globalを、プログラムはサンプルプログラムを参考にしてください。
  libcsd.aはCライブラリの関数を使用しますので、lib_c.aと一緒にリンクするか、
  ビルドでエラーとなった関数を自作するかしてください。
  ※リンクはlib_c.aより先にlibcsd.aを記述しないとエラーとなります。
  各関数の使用方法についてはdocフォルダ以下の関数リファレンスを参照してください。

********************************************************************************

お願い

  作成および移植しただけでテストしていない関数が多々あります。
  不具合を報告して頂けると有り難いです。

********************************************************************************

謝辞

  Hello World, PSP! を始め、開発者の方に感謝致します。

********************************************************************************

免責

  自己責任で使用してください。

********************************************************************************

更新履歴

  verup.txt参照

