// c言語で10パズルを解くプログラム
/* 0000～9999までの数字の組み合わせと四則演算を用いて、10を作る
逆ポーランド記号を用いたアプローチで問題を解く。以下にフローチャートを書く。
1.すべての数の組み合わせを作る
2.作成した組み合わせから1つを選び、逆ポーランド記号で正しい式となるすべてのパターンを生成する
3.それを計算し、結果が10になるものを解として表示する。
4.生成した全てのパターンにおいて10にならなければ、その数字の組み合わせの解は存在しない。
5.生成したすべてのパターンにおいて2～4を繰り返す

逆ポーランド記号
12+　→　1+2
これを使うとカッコを使わずに計算の順序を表すことができる
ex.
5×(8÷(3+1)) → 5831+/*
この処理はスタックで実装する.必要な処理は以下の2つ。
1.数字が表れたら、スタックに積む
2.演算子が現れたらスタックの上から２つの数字を取り出し、対応した加減乗除を行い、結果をスタックに積む

また今回は1桁ずつの数に対象を限定し、計算も四則演算に限定する。
本来ならスタックはリストを用いて実装するが、今回は入力される数は４桁なので、
配列を用いる。
*/

/*
逆ポーランド記号の計算部
#include <stdio.h>
#include <stdlib.h>

//仮想分数のリスト
typedef struct tagBUNSUU {
  int bunbo;
  int bunsi;
} BUNSUU;

BUNSUU stack_array[10];

// スタックの上限は10
int stack_top = 0;

void stack_push(BUNSUU *value) {
  //スタックのBUNSUUをプッシュする
  if(stack_top != 10) {
    stack_array[stack_top].bunbo = value->bunbo;
    stack_array[stack_top].bunsi = value->bunsi;
    stack_top++;
  } else {
    printf("スタックオーバーフローです。数字が多すぎます");
    exit(EXIT_FAILURE);
  }
}

// スタックからBUNSUUをとってくる
void stack_pop(BUNSUU *ret) {
  stack_top--;
  if(stack_top >= 0) {
    ret->bunbo = stack_array[stack_top].bunbo;
    ret->bunsi = stack_array[stack_top].bunsi;
    return;
  } else {
    printf("スタックアンダーフローです。モウムリ...");
    exit(EXIT_FAILURE);
  }
}

int main() {
  char line[256];
  int c;
  BUNSUU st1, st2;

  printf("逆ポーランド記号で数式を入力してください:");
  scanf("%s", line);

  c = 0;
  //ヌル文字が入力されたら終了
  while(line[c] != '\0') {
    //数字が入力されたらそのままスタックに入れる
    if(line[c] >= '0' && line[c] <= '9') {
      st1.bunbo = 1;
      st1.bunsi = line[c] - '0';
      stack_push(&st1);
    } else { //数字じゃない場合はスタックの上２つの数字をとってきて演算する
      stack_pop(&st1);
      stack_pop(&st2);
      if(line[c] == '+') {
        st2.bunsi = st2.bunsi * st1.bunbo +st1.bunsi *st2.bunbo;
        st2.bunbo = st1.bunbo * st2.bunbo;
        stack_push(&st2);
      }
      else if(line[c] == '-') {
        st2.bunsi = st2.bunsi * st1.bunbo - st1.bunsi *st2.bunbo;
        st2.bunbo = st1.bunbo * st2.bunbo;
        stack_push(&st2);
      }
      else if(line[c] == '*') {
        st2.bunsi = st2.bunsi * st1.bunsi;
        st2.bunbo = st1.bunbo * st2.bunbo;
        stack_push(&st2);
      }
      else if(line[c] == '/') {
        st2.bunsi = st2.bunsi * st1.bunbo;
        st2.bunbo = st1.bunbo * st2.bunsi;
        if(st2.bunbo == 0) {
          printf("0で除算しました\n");
          exit(EXIT_FAILURE);
        }
        stack_push(&st2);
      }
      else {
        printf("無効な文字が入力されています");
        exit(EXIT_FAILURE);
      }
    }
    c++;
  }
  stack_pop(&st1);
  if(stack_top != 0) {
    // この場合、スタックに数字が残っている
    printf("正しくない数式です.数字が多すぎます\n");
    exit(EXIT_FAILURE);
  }
  printf("解は%lfです", (double)st1.bunsi / (double)st1.bunbo);

  return;
}


4つの数からすべての数式を作りだすプログラム
#include <stdio.h>
#include <stdlib.h>

//与えられた数
char number = "1234";
char created_num[8];

// RPNを作成する再帰関数
void make_rpn(int num, int exp) {
  static int isused[4] = {0};
  int i;

  //全体で7文字であれば表示
  if(num + exp == 7) {
    created_num[7] = '\n';
    printf("%s\n", created_num);
    return;
  } else {
    //数字が演算子より2つ多ければ演算子を入れてもいい
    if(num - exp >= 2) {
      created_num[num + exp] = '+';
      make_rpn(num, exp + 1);

      created_num[num + exp] = '-';
      make_rpn(num, exp + 1);

      created_num[num + exp] = '/';
      make_rpn(num, exp + 1);

      created_num[num + exp] = '*';
      make_rpn(num, exp + 1);
    }
    //数字が3つ以下であれば数字を入れてもいい
    if(num <= 3) {
      for(i = 0; i < 4; i++) {
        if(isused[i] == 0) {
          isused[i] = 1;
          created_num[num + exp] = number[i];
          make_rpn(num + 1, exp);
          isused[i] = 0;
        }
      }
    }
  }
}

int main() {
  make_rpn(0, 0);
  return 0;
}*/


/*10パズル本体*/
#include <stdio.h>
#include <stdlib.h>

// make_numによって作られた４つの数字
char created_num[5];

// make_rpnによって作られたrpn
char created_rpn[8];

//solveに使えわれる仮想分数構造体
//仮想分数のリスト
typedef struct tagBUNSUU {
  int bunbo;
  int bunsi;
} BUNSUU;

//スタックの上限は４
BUNSUU stack_array[4];

int stack_top = 0;
void stack_push(BUNSUU *value) {
  //スタックのBUNSUUをプッシュする
  stack_array[stack_top].bunbo = value->bunbo;
  stack_array[stack_top].bunsi = value->bunsi;
  stack_top++;
}

// スタックからBUNSUUをとってくる
void stack_pop(BUNSUU *ret) {
  stack_top--;
  ret->bunbo = stack_array[stack_top].bunbo;
  ret->bunsi = stack_array[stack_top].bunsi;
  return;
}

int solve() {
  int c;
  BUNSUU st1, st2;

  stack_top = 0;
  c = 0;
  //ヌル文字が入力されたら終了
  while(created_rpn[c] != '\0') {
    //数字が入力されたらそのままスタックに入れる
    if(created_rpn[c] >= '0' && created_rpn[c] <= '9') {
      st1.bunbo = 1;
      st1.bunsi = created_rpn[c] - '0';
      stack_push(&st1);
    } else { //数字じゃない場合はスタックの上２つの数字をとってきて演算する
      stack_pop(&st1);
      stack_pop(&st2);
      if(created_rpn[c] == '+') {
        st2.bunsi = st2.bunsi * st1.bunbo +st1.bunsi *st2.bunbo;
        st2.bunbo = st1.bunbo * st2.bunbo;
        stack_push(&st2);
      }
      else if(created_rpn[c] == '-') {
        st2.bunsi = st2.bunsi * st1.bunbo - st1.bunsi *st2.bunbo;
        st2.bunbo = st1.bunbo * st2.bunbo;
        stack_push(&st2);
      }
      else if(created_rpn[c] == '*') {
        st2.bunsi = st2.bunsi * st1.bunsi;
        st2.bunbo = st1.bunbo * st2.bunbo;
        stack_push(&st2);
      }
      else if(created_rpn[c] == '/') {
        st2.bunsi = st2.bunsi * st1.bunbo;
        st2.bunbo = st2.bunbo * st1.bunsi;
        if(st2.bunbo == 0) {
          return 0;
        }
        stack_push(&st2);
      }
    }
    c++;
  }
  stack_pop(&st1);

  if(st1.bunbo*10 == st1.bunsi) {
    return 1;
  }

  return 0;
}

// RPNを作成する再帰関数
int make_rpn(int num, int exp) {
  static int isused[4] = {0,0,0,0};
  int i;

  //全体で7文字であれば表示
  if(num + exp == 7) {
    created_rpn[7] = '\0';
    //printf("%s\n", created_rpn);
    if(solve()) {
      return 1;
    }
    return 0;
  } else {
    //数字が演算子より2つ多ければ演算子を入れてもいい
    if(num - exp >= 2) {
      created_rpn[num + exp] = '+';
      if(make_rpn(num, exp + 1)) {
        return 1;
      }

      created_rpn[num + exp] = '-';
      if(make_rpn(num, exp + 1)) {
        return 1;
      }

      created_num[num + exp] = '*';
      if(make_rpn(num, exp + 1)) {
        return 1;
      }

      created_num[num + exp] = '/';
      if(make_rpn(num, exp + 1)) {
        return 1;
      }

    }
    //数字が3つ以下であれば数字を入れてもいい
    if(num <= 3) {
      for(i = 0; i < 4; i++) {
        if(isused[i] == 0) {
          isused[i] = 1;
          created_rpn[num + exp] = created_num[i];
          if(make_rpn(num + 1, exp)){
            isused[i] = 0;
            return 1;

          }
          isused[i] = 0;
        }
      }
    }
  }
  return 0;
}

//数の組み合わせを作る再帰関数
void make_num(int keta, int num) {
  int i;
  if(keta == 4) {
    created_num[4] = '\0';
    //数が4桁になったらRPNを作成する
    if(make_rpn(0,0)) {
      printf("%s:%s\n", created_num, created_rpn);
    } else {
      printf("%s:解けません\n", created_num);
    }
    return;
  }
  for(i = num; i <= 9; i++) {
    created_num[keta] = i + '0';
    make_num(keta + 1, i);
  }
}

int main() {
  make_num(0,0);
  return 0;
}
