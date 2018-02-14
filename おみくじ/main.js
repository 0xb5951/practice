(function() {
  'use strict';

  var btn = document.getElementById('btn');

  // クリックした時の動作
  btn.addEventListener('click', function(){
    var results = ['大凶', '凶', '小凶', '末吉', '小吉', '中吉', '大吉', '絶望']
    var n = Math.floor(Math.random() * results.length); /*ランダムな整数を生成*/
    this.textContent = results[n];
    // switch (n) {
    //   case 0:
    //     this.textContent = '大凶';
    //     break;
    //   case 1:
    //     this.textContent = '大吉';
    //     break;
    //   case 2:
    //     this.textContent = '中吉';
    //     break;
    //   case 3:
    //     this.textContent = '小吉';
    //     break;
    //   case 4:
    //     this.textContent = '末吉';
    //     break;
    //   case 5:
    //     this.textContent = '凶';
    //     break;
    //   case 6:
    //     this.textContent = '絶望';
    //     break;
    //   default:
    //     this.textContent = "はずれ";
    //     break;
    // }
    // this.textContent = n;
  });

  // クリックされている間の動作
  btn.addEventListener('mousedown', function(){
    this.className = 'pushed';/*クラスを定義*/
  });

  // ホールドをやめた時の動作
  btn.addEventListener('mouseup', function(){
    this.className = '';
  });
})();
