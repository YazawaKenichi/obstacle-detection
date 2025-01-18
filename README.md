# obstacle-detection

Raspberry Pi Pico + micro-ROS を用いてポテンショメータの値をパブリッシュする Raspberry Pi Pico 向けの組み込みプログラム

# 使い方
`obstacle_detection.uf2` を書き込む

``` cmd
ros2 run micro_ros_agent micro_ros_agent serial -b 115200 --dev /dev/ttyACM0 -v6
```

Raspberry Pi Pico を PC に刺す

ポテンショメータと PICO をつなぐ

# ポイント
- `ROS_DOMAIN_ID` は明示的に指定しないほうがいい（指定する方法は現在調査中）
- `ROS_LOCLHOST_ONLY` は `0`

