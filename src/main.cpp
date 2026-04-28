#include <M5Unified.h>
#include <SPIFFS.h>

// --- 設定 ---
const char* LOGO_PATH = "/logo.jpg"; 

// テキストは各行に分けて配列にすると行間調整がしやすいです
const char* INTRO_LINES[] = {
    u8"関西春ロボコンは、2018年より",
    u8"毎年３月に開催されている",
    u8"新人向けロボット競技大会です。",
    u8"学生たちがロボットを製作して",
    u8"競い合います！"
};
const int LINE_COUNT = 5;

void drawLogo();
void drawIntro();
void drawQRCodes();
void drawBattery(bool forceUpdate);

void setup() {
    auto cfg = M5.config();
    M5.begin(cfg);

    if (!SPIFFS.begin(true)) {
        Serial.println("SPIFFS mount failed");
    }

    M5.Display.setRotation(0); 
    M5.Display.fillScreen(TFT_WHITE);
    M5.Display.setTextColor(TFT_BLACK);
    
    // 初回描画
    drawLogo();
    drawIntro();
    drawQRCodes();
    drawBattery(true);

    M5.Display.display();
}

void loop() {
    M5.update();
    if (M5.BtnPWR.wasPressed()) {
        M5.Display.fillScreen(TFT_WHITE);
        drawLogo();
        drawIntro();
        drawQRCodes();
        drawBattery(true);
        M5.Display.display();
    }
    delay(100);
}

void drawLogo() {
    int logoWidth = 460; 
    int yPos = 60; 
    int xPos = (M5.Display.width() - logoWidth) / 2;

    File f = SPIFFS.open(LOGO_PATH, "r");
    if (f) {
        size_t size = f.size();
        uint8_t* buf = (uint8_t*)malloc(size);
        if (buf) {
            f.read(buf, size);
            f.close();
            M5.Display.drawJpg(buf, size, xPos, yPos, logoWidth, 0);
            free(buf);
            return;
        }
        f.close();
    }
    // Fallback
    M5.Display.setFont(&fonts::efontJA_24);
    M5.Display.setTextDatum(top_center);
    M5.Display.drawString(u8"関西春ロボコン", M5.Display.width()/2, yPos + 30);
}

void drawIntro() {
    M5.Display.setFont(&fonts::efontJA_24_b); 
    M5.Display.setTextSize(1.2);      // 文字の大きさ
    M5.Display.setTextDatum(top_center); // 中央揃えに設定
    
    int startY = 320;  // 開始位置
    int lineHeight = 55; // ★ここを調整すると行間が変わります（フォントサイズ＋余白）

    for (int i = 0; i < LINE_COUNT; i++) {
        // 画面中央（M5.Display.width() / 2）を基準に描画
        M5.Display.drawString(INTRO_LINES[i], M5.Display.width() / 2, startY + (i * lineHeight));
    }
}

void drawQRCodes() {
    int qrSize = 210;  // QRコードのサイズ
    int yPos = 650;    // 紹介文との間隔を開けるために少し下げました
    
    // --- 中央揃えのための計算 ---
    int totalQrWidth = qrSize * 2;             // QR2個分の幅 (420px)
    int gap = (M5.Display.width() - totalQrWidth) / 3; // 隙間を均等に配分 (40px)
    
    int xLeft = gap;                           // 左側の開始位置 (40px)
    int xRight = gap + qrSize + gap;           // 右側の開始位置 (290px)

    M5.Display.setTextSize(1.0);
    M5.Display.setTextDatum(top_center); // 文字も中央揃え
    M5.Display.setFont(&fonts::efontJA_24_b);

    // --- 左側: 公式サイト ---
    M5.Display.qrcode("https://kaisai-harurobo.org/", xLeft, yPos, qrSize, 7);
    // 文字はQRコードの「中心座標」を指定して描画
    M5.Display.drawString(u8"公式サイト", xLeft + (qrSize / 2), yPos + qrSize + 10);

    // --- 右側: 公式X ---
    M5.Display.qrcode("https://x.com/kansai_robocon", xRight, yPos, qrSize, 7);
    // 文字はQRコードの「中心座標」を指定して描画
    M5.Display.drawString(u8"公式X(Twitter)", xRight + (qrSize / 2), yPos + qrSize + 10);
}

void drawBattery(bool forceUpdate) {
    int battery = M5.Power.getBatteryLevel();
    M5.Display.setFont(&fonts::efontJA_12);
    M5.Display.setTextSize(1.0);
    M5.Display.setTextDatum(top_right); // バッテリーは右上で固定
    M5.Display.setCursor(M5.Display.width() - 10, 15);
    M5.Display.printf("Bat: %d%%", battery);
}