ぐりとぐら
======
Grid Graph Layout AlgorithmのC++による実装.

Grigra5
------
古い実装(非推奨).

Grigra6
------
安定版の実装.

### 構成
* src/ - プログラムソース
* Makefile - メイクファイル

### 動作確認環境
* MinGW32-g++
* Visual Studio 2012 C++

Grigra7
------
Grigra6の再実装版.  
日本語(utf-8)によるコメント付.

### 構成
* include/ - インクルードファイル
* src/ - プログラムソース
* Makefile - メイクファイル
* obj/ - 中間オブジェクト
* bin/ - 出力先
    * layout.exe - レイアウトコマンド(使い方参照)
    * gridlayout.so - 共有ライブラリ

### 動作確認環境
* MinGW32-g++

slide
------
卒業論文発表時のスライド.

thesis(SJIS)2
------
卒業論文のtexデータ.

コンパイル方法
------
### Grigra6 (MinGW32-g++)
    cd ./Grigra/Grigra6/
    make

### Grigra6 (Visual Studio 2012)
* 新しいプロジェクトを作成
* src/ 以下のファイルをコピー
* build

### Grigra7 (MinGW32-g++)
    cd ./Grigra/Grigra7/
    make

使い方
------
### Grigra6
    layout.exe gridsize [input-filename] < input > output
* gridsizeは整数値で指定
* input-filenameを省略した場合は、標準入力から読み込む
* 出力は標準出力にされるので、必要であればリダイレクトする

### Grigra7
    bin/layout.exe gridsize fixed-point [input-filename] [output-filename]
* gridsizeは整数値で指定
* fixed-pointは入出力の数値が小数の場合、固定小数の桁数を指定する
    * 0の場合は入力は整数値として扱われる
* input-filenameを省略した場合は、標準入力から読み込む
* output-filenameを省略した場合は、標準出力に書き出す
* input-filenameを省略してoutput-filenameを与えることはできない
    * いずれコマンドオプション化します

