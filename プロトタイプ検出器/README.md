# プロトタイプ検出器の解析等で使用するプログラムのまとめ

## 各プログラム名と使用用途の説明


### ehistnew190711.cpp
- 計測データよりコインシデンスしたイベントを解析するプログラム(現在ではこのプログラム内でthresholdを決定)

### ehistnew190711_xyhalf.cpp
- 計測データよりコインシデンスしたイベントを解析するプログラム
- 検出面の解像度をxy両方向で半分にしている

### data_analysis_pre1.cpp
- 計測データの全イベントを解析するプログラム


### attenuation_histogram_experiment.cpp
- 減衰率を導出するプログラム

### attenuation_histogram_experiment_xyhalf.cpp
- 減衰率を導出するプログラム


### ehistnew191115.cpp
- 計測データよりコインシデンスしたイベントを解析するプログラム(現在ではこのプログラム内でthresholdを決定)
　タイムスタンプを押した新たな計測に対応している。


重要なのはdata_analysis_pre1.cppとehistnew190711.cpp。
ehistnew190711.cppさえあればコインシデンス後のベクトルプロット
をだしてくれる。
data_analysis_pre1.cppはコインシデンス前の各MPPCのスペクトルを画面に表示
