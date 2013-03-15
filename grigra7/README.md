Grigra7
======

include/
------
### gridlayout.hpp
ライブラリ用のincludeのまとめファイル.

### point.hpp
点型および点集合型の宣言.

### table.hpp
添え字列型およびテーブル型の宣言.

### layout.hpp
レイアウトアルゴリズム関数の宣言.

### reader.hpp
点集合の外部表現入力関数の宣言.

### printer.hpp
点集合の外部表現出力関数の宣言.

src/
------
### point.cpp
点型および点集合型のメソッドの定義.

### table.cpp
添え字列型およびテーブル型の定義.

### layout.cpp
レイアウトアルゴリズム関数の定義.

### reader.cpp
点集合の外部表現入力関数の定義.

### printer.cpp
点集合の外部表現出力関数の定義.

### main.cpp
bin/layout.exe のエントリーポイントの定義.

readerについて
-------
点は空白文字で区切られた数字列で与えること.  
奇数個与えた場合、末尾は切り捨てる.
    x-1 y-1
    x-2 y-2
    x-3 y-3
    x-4 y-4

printerについて
------
点毎にx,y成分を空白区切りで一行ずつ出力する.  
区切り文字を変えたい場合や、行末に文字列を追加したい場合は、
`pset_raw_delimiter`や`pset_col_delimiter`を変更する.

