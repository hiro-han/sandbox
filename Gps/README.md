NMEA-0183フォーマットのGPSデータを、シリアルで受信し使いやすいよう変換するソフトです。

# 内容
```
GPS
 |- CMakeLists.txt  # CMakeファイル
 |- Common.h        # 文字列->数値の変換
 |- Error.h         # エラーコード定義
 |- GpsSentences.h  # GPSデータ構造対定義
 |- main.cpp        # main関数、シリアルでデータを受信し変換処理を呼び出す
 |- NEMAParser.cpp  # NEMAフォーマットのデータを使いやすいよう変換する
 `- NEMAParser.h    # 同上
```

# 使い方
```
$ cmake .
$ make
$ ./Gps
```

同じディレクトリに`log.txt`というファイルが出力され、受信したデータが出力されます。
