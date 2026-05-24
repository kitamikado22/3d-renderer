# 3D Renderer

## 概要
ネイティブ C++ による **ソフトウェア 3D レンダラー** です。
目的は、3Dモデルを画面上にレンダリングする処理をネイティブに実装することで、その仕組みを理解することです。


## デモ動画（Youtube）
[![Watch the video](https://img.youtube.com/vi/Usq6r2-WRY4/maxresdefault.jpg)](https://www.youtube.com/watch?v=Usq6r2-WRY4)


---

## ソースコード概要
```
Source/
├── main.cpp           … エントリポイント・メインループ
├── Renderer.h/.cpp    … ラスタライズ・Z バッファ
├── Camera.h/.cpp      … ビュー / 射影行列・座標変換
├── World.h            … シーン管理
├── Model.h            … 位置・回転の基底クラス
├── MeshModel.h        … メッシュ付きモデル
├── GeometricModel.h   … 立方体・四面体の生成
├── MeshComponent.h    … 三角形データ
├── Triangle.h         … 三角形構造体
├── Vector3.h          … 3 次元ベクトル
├── Matrix4.h          … 4×4 行列
└── Rotator.h/.cpp     … オイラー角回転
```

## アピールポイント
- 外部のライブラリに頼らず、純粋なC++と描画システムのみを用いて3Dレンダリングを実装したこと
- `Vector3`や`Rotator`、`Matrix4`などの低レベルの数学的な機能も含めて実装していること
- 基本的なオブジェクト指向で設計していること

## プロジェクトのレポート資料
[ソフトウェア3Dレンダラーのレポート](report.pdf)

