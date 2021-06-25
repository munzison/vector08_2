#if 1
#include"libOne.h"
void gmain() {
    window(1920, 1080, full);
    int kotatuImg = loadImage("assets\\kotatu0.png");
    int mikanImg = loadImage("assets\\mikan.png");
    int backImg = loadImage("assets\\back.png");

    float kpx = width / 2;
    float kpy = height / 2;

    struct MIKAN {
        float px, py;
        float tx, ty;
    };
    const int totalnum = 10;//10個のMIKANを用意する
    struct MIKAN m[totalnum];
    int curnum = 0;
    while (notQuit) {
        if (isTrigger(MOUSE_LBUTTON)) {  //左クリックしたらミカンを表示
            if (curnum < totalnum) {
                m[curnum].px = mouseX;
                m[curnum].py = mouseY;
                curnum++;
            }
        }
        clear(220);
        rectMode(CENTER);
        image(kotatuImg, kpx, kpy);
        for (int i = 0; i < curnum; i++) {
            image(mikanImg, m[i].px, m[i].py);
        }
        image(mikanImg, mouseX, mouseY);
        textSize(50);
        fill(0);
        text(mouseX - kpx, 0, 50);
        text(mouseY - kpy, 0, 100);
    }
}

//使用画像へのリンク
//http://illust-hp.com/img/nekotatu.html
#else







































#include"libOne.h"
void gmain() {
    window(1920, 1080, full);
    //画像読み込み
    int backImg = loadImage("assets\\back.png");
    int kotatuImg = loadImage("assets\\kotatu0.png");
    int kotatuColorImg = loadImage("assets\\kotatu1.png");
    int mikanImg = loadImage("assets\\mikan.png");
    //こたつデータ
    int kimg = kotatuImg;
    float kpx = width / 2;
    float kpy = height / 2+250;
    //みかんデータ
    const int totalNum = 15;
    struct MIKAN { float px, py, tx, ty; } m[totalNum];
    for (int i = 0; i < totalNum; i++) {
        m[i].tx = kpx - 176;
        m[i].ty = kpy - 42 - 50 * i;
    }
    int curNum = 0;
    float speed = 20;
    int last = totalNum - 1;
    //メインループ
    while (notQuit) {
        //みかん発射
        if (isTrigger(MOUSE_LBUTTON)) {
            if (curNum < totalNum) {
                m[curNum].px = mouseX;
                m[curNum].py = mouseY;
                curNum++;
            }
        }
        //リセット
        if (isTrigger(MOUSE_RBUTTON)) {
            curNum = 0;
            m[last].px = 0;
        }
        //みかん移動
        for (int i = 0; i < curNum; i++) {
            float vx = m[i].tx - m[i].px;
            float vy = m[i].ty - m[i].py;
            float mag = sqrt(vx * vx + vy * vy);
            m[i].px = mag > speed ? (m[i].px + vx / mag * speed) : m[i].tx;
            m[i].py = mag > speed ? (m[i].py + vy / mag * speed) : m[i].ty;
        }
        //こたつ画像切り替え
        if (m[last].px == m[last].tx) {
            kimg = kotatuColorImg;
        }
        else {
            kimg = kotatuImg;
        }
        //画面クリア
        clear(220);
        rectMode(CENTER);
        //背景描画
        if (m[last].px == m[last].tx) {
            image(backImg, kpx, height / 2);
        }
        //こたつ描画
        image(kimg, kpx, kpy);
        //みかん描画
        for (int i = 0; i < curNum; i++) {
            image(mikanImg, m[i].px, m[i].py);
        }
    }
}
#endif