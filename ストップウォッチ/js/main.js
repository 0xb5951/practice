//現在時刻から開始時刻を一定時間ごとにひくことでタイマーを実装

(function() {
  'use strict';

  //変数宣言部
  var timer = document.getElementById('timer');
  var start = document.getElementById('start');
  var stop = document.getElementById('stop');
  var reset = document.getElementById('reset');

  var starttime; //スタート時の時刻を表す
  var elapsedtime = 0; //経過時刻を表す
  var timerId; //タイマーIDを指定して、時間をクリアする用
  var timeToAdd = 0; //通算時刻を保存する変数
  var isRunning = false; //タイマの状態を表す

  //関数部
  // ミリ秒を時間や分に直す関数
  function updateTimerText() {
    //135200 -> 02:15.200
    // 60秒 = 60000
    var m = Math.floor(elapsedtime/60000);
    var s = Math.floor(elapsedtime%60000 /1000);
    var ms = Math.floor(elapsedtime%1000);

    // 桁数を常に整える
    // 表示する値が合っていれば文字列でも問題ないので、文字列を使う
    // scriptには、文字列と数値を連結させると文字列になるという性質がある.

    //0と連結させて末尾２桁を取り出す
    m = ('0' + m).slice(-2);
    s = ('0' + s).slice(-2);
    ms = ('00' + ms).slice(-3);
    timer.textContent = m + ':' + s + '.' + ms;
  }

  //時間経過を表す関数
  function countup() {
    //setTimeout(関数, 時間, データ) 一定時間経過後に任意の関数を実行する
    // 関数　：実行したい関数　時間：関数を実行するまでの待機時間　データ：関数の引数

    //10ミリ秒ごとに経過時刻を取得
    timerId = setTimeout(function() {
      elapsedtime = Date.now() - starttime + timeToAdd;
      updateTimerText();
      countup();
    }, 10);

  }

  // 初期状態
  // start.className = 'btn';
  // stop.className = 'btn cantPush';
  // reset.className = 'btn cantPush';

  //ボタンの見た目を変える関数
  function updateButtonState(startButtonState, stopButtonState, resetButtonState) {
    start.className = startButtonState ? 'btn' : 'btn cantPush';
    stop.className = stopButtonState ? 'btn' : 'btn cantPush';
    reset.className = resetButtonState ? 'btn' : 'btn cantPush';
  }

  updateButtonState(true, false,false);

  //startボタンがクリックされたときの処理
  start.addEventListener('click', function() {
    //現在時刻を取得する.（協定世界時1970/1/1 00:00から経過した現在の時間をミリ秒で取得する）
    if(isRunning == true){
      return;
    }
    starttime = Date.now();

    updateButtonState(false, true, false);

    isRunning = true;
    //カウントアップする関数
    countup();
  });

  //stopボタンがクリックされたときの処理
  stop.addEventListener('click', function() {
    // clearTimepout(timeputID) 引数に指定したタイマの値を停止する
    //タイマを停止させるにはIDを付ける必要がある
    timeToAdd = elapsedtime;
    isRunning = false;
    clearTimeout(timerId);

    updateButtonState(true, false, true);

  });

  //resetボタンがクリックされたときの処理
  reset.addEventListener('click', function() {
    // clearTimepout(timeputID) 引数に指定したタイマの値をクリアする
    if(isRunning == true){
      return;
    }
    elapsedtime = 0;
    timeToAdd = 0;

    updateButtonState(true, false, false);

    updateTimerText();

  });

}) ();
