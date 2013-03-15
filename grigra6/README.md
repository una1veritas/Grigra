Grigra6
======

src/
------

### misc.h
STLのインクルードまとめ.

### point.h
点型のテンプレート.

### pointset.h
点集合型のテンプレート.

### table.h
テーブル型のテンプレート.

### layoutman.h
レイアウトアルゴリズムのテンプレート.

### layout.hpp
レイアウトアルゴリズムのインタフェース.  
* `GridLayout` - グリッドレイアウト関数
* `PointSetProxy` - グリッドレイアウト関数入力用のオブジェクト. 
    * `PointSetProxy( filename )` - 指定した名前のファイルから読み込む
    * `PointSetProxy( sIn )` - 指定した入力ストリームから読み込む
    * `PointSetProxy( pset, length )` - 指定した配列から読み込む
    * `print()` - 標準出力に書き出す
    * `print( sOut )` - 指定したストリームに書き出す
    * `print( out_p, maxlen )` - 指定した配列に書き出す

### layout.cpp
レイアウトアルゴリズムの定義.

### main.cpp
エントリーポイントの定義.

input
------
入力点集合は標準ストリームで、空白文字で区切られた数字列で与えること.

output
------
出力は、一行ごとにx,y成分を空白文字で区切った書式.

    x-1 y-1
    x-2 y-2
    x-3 y-3
    x-4 y-4

