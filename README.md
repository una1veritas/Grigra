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

### Grigra7
    bin/layout.exe gridsize fixed-point [input-filename] [output-filename]


