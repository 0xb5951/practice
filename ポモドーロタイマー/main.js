(function(){
  'use strict';

  var time = document.getElementById('time');
  var start = document.getElementById('start');
  var reset = document.getElementById('reset');

  var starttime = 0; //開始時刻を保存
  var lefttime = 0;  //残り時間を保存
  var timeTocountdown = 0; //タイマーの時間
  var timerId; //タイマーを停止するためのID
  var isRunning = false; //ボタンの状況によってstartとstopを切り替える

  //文字出力を担当する
  function updateTimerText(count) {
    //135200 -> 02:15.200
    // 60秒 = 60000
    var d = new Date(count); //引数に対応する時間の数値を返す
    var m = d.getMinutes(); //オブジェクトの分を返す
    var s = d.getSeconds(); //オブジェクトの秒を返す
    var ms = d.getMilliseconds(); //オブジェクトのミリ秒を返す

    //0と連結させて末尾２桁を取り出す
    m = ('0' + m).slice(-2);
    s = ('0' + s).slice(-2);
    ms = ('00' + ms).slice(-3);
    time.textContent = m + ':' + s + '.' + ms;
  }

  function countDown() {
    timerId = setTimeout(function() {
      // elapsedtime = Date.now() -starttime;
      lefttime = timeTocountdown - (Date.now() - starttime);
      if(lefttime < 0){
        isRunning = false;
        start.textContent = 'Start';
        clearTimeout(timerId);
        lefttime = 0;
        timeTocountdown = 0;
        updateTimerText(lefttime);
        return;
      }
      updateTimerText(lefttime);
      countDown();
    },10);
  }

  // start.addEventListener('click', function(){
  //   starttime = Date.now();
  //   countDown();
  // });

  min.addEventListener('click', function(){
    if(isRunning == true){
      return;
    }
    if(timeTocountdown >= 60 * 60 * 1000){
      alert('これ以上は入力できません');
      timeTocountdown = 58 * 60 * 1000 + 59 *1000;
    }
    timeTocountdown += 60 * 1000; //1分
    updateTimerText(timeTocountdown);
  });

  sec.addEventListener('click', function(){
    if(isRunning == true){
      return;
    }
    if(timeTocountdown >= 60 * 60 * 1000){
      alert('これ以上は入力できません');
      timeTocountdown = 58 * 60 * 1000 + 59 *1000;
    }
    timeTocountdown += 1 * 1000; //1秒
    updateTimerText(timeTocountdown);

  });

  //startとstopは共用
  start.addEventListener('click', function(){
    if(isRunning == false){
      isRunning = true;
      start.textContent = 'Stop';
      starttime = Date.now();
      countDown();
    } else {
      isRunning = false;
      start.textContent = 'Start';
      timeTocountdown = lefttime;
      clearTimeout(timerId);
    }
  });

  reset.addEventListener('click', function(){
    lefttime = 0;
    timeTocountdown = 0;
    updateTimerText(timeTocountdown);
  });


})();
