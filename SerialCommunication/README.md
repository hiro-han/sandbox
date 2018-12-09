# Raspberry Pi - Arduino シリアル通信

## 概要
Raspberry PiとArduino間のシリアル通信のサンプルコードです。
Python, C++, Processingの３種類で作成しました。

Python, C++はRaspberry Piで、ProcessingはPC(Ubuntu)で動作確認済みです。

コードは、Raspberry Pi/PCから文字列を送信し、Arduinoでは受信した文字列に文字を加えて送り返す、という内容になります。

## 環境
- Arduino
    - Arduino Uno
    - Arduino 1.8.9
- Raspberry Pi
    - Raspberry Pi B Model B++
    - Raspbian 9.3
    - Python 3.5
    - GCC 6.3.0
    - cmake 3.5.1
- PC
    - Ubuntu 16.04
    - Processing 3.3.7
- その他
    - Raspberry Pi-Aruduino, PC-Arduino間はUSBで接続

## 使い方
### 準備
__Arudino IDEで__ `(git repository)/apps/SerialCommunication/Aruduino/serial.ino`をArduinoに書き込む

### Raspberry Pi
#### Python  
1. 実行
    ```
    $ cd (git repository)/apps/SerialCommunication/RaspberryPi/Python
    $ python serial.py
    ```
1. コンソール上で送信文字列を入力する
1. コンソールに`Arduino Receive = (送信文字列)`と表示されたら成功

#### C++
1. ビルド
    ```
    $ cd (git repository)/apps/SerialCommunication/RaspberryPi/C++
    $ cmake CMakeList.txt
    $ make
    ```
1. 実行
    ```
    $ ./SerialCommunication
    ```
    1. コンソール上で送信文字列を入力する
    1. コンソールに`Arduino Receive = (送信文字列)`と表示されたら成功


#### PC
1. __Processing IDE__ で`(git repository)/apps/SerialCommunication/RaspberryPi/Processing/serial.pde`を開いて実行する
1. 表示された画面をフォーカス?し、送信文字列を入力する
1. 画面に`Arduino Receive = (送信文字列)`と表示されたら成功
