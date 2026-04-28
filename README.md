# M5-Paper-S3 関西春ロボコン表示システム

M5Stack Paper S3 用于显示关西春Robocon大赛信息的电子看板。

## 概要

このプロジェクトは、M5Stack Paper S3 电子纸显示屏用于显示关西春Robocon大赛的以下信息：

- 大会ロゴ
- 大会介绍文案
- QR码（HP・X）
- 电池状态

## 硬件

| 項目         | 仕様                        |
| ------------ | --------------------------- |
| ボード       | M5Stack Paper S3 (ESP32-S3) |
| ディスプレイ | 电子纸 4.7英寸              |
| 解像度       | 540×960                     |

## 软件

| 項目       | バージョン |
| ---------- | ---------- |
| PlatformIO | 6.10.0     |
| Framework  | Arduino    |
| M5Unified  | 0.2.5      |
| M5GFX      | 0.2.6      |

## ビルド

```bash
# ビルド
pio run

# アップロード
pio run -t upload

# モニター表示
pio device monitor
```

## ファイル構成

```
├── platformio.ini    # PlatformIO設定
├── src/
│   └── main.cpp      # メインソースコード
├── data/             # SPIFFS用画像ファイル
│   ├── logo.jpg      # 大会ロゴ
│   ├── logo.png
│   ├── HP.png        # HP用QRコード
│   └── X.png         # X(Twitter)用QRコード
├── include/          # ヘッダーファイル用ディレクトリ
├── lib/              # ライブラリ用ディレクトリ
└── test/             # テスト用ディレクトリ
```

## 機能

### 画面構成

1. **ロゴ表示** - 上部に大会ロゴを表示
2. **紹介文表示** - 関西春ロボコンの説明を5行で表示
3. **QRコード表示** - HPとXのQRコードを画面下部に表示
4. **バッテリー表示** - 現在のバッテリー残量を表示

### 操作

- **電源ボタン** - 画面を更新

## 開発者

- 作成者: 関西春ロボコン実行委員会
- GitHub: [HidetoNiwa/M5-paper-S3](https://github.com/HidetoNiwa/M5-paper-S3)

## ライセンス

MIT License

## ビルドステータス

![PlatformIO CI](https://github.com/HidetoNiwa/M5-paper-S3/actions/workflows/platformio.yml/badge.svg)