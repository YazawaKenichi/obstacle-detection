# obstacle-detection

地面に棒状の器具を当て、ロボットが走行不能となりうる凹凸・起伏・障害物を検知するパッケージ

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

