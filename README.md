| Supported Targets | XIAO ESP32-C3 | XIAO ESP32-C6 | XIAO ESP32-S3 | XIAO ESP32-S3 (Sense) |
| ----------------- | ------------- | ------------- | ------------- | --------------------- |


## How to use
A recommended way is to follow the instructions on a [wiki-page](https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html#start-a-new-project).   

Below is short explanation of remaining files in the project folder.

```
├── CMakeLists.txt
├── components
│   ├── air_quality_sensor_v1_3
│   │   ├── include
│   │   └── air_quality_sensor_v1_3.h
│   ├── Kconfig
│   ├── CMakeLists.txt
│   └── air_quality_sensor_v1_3.c
├── main
│   ├── CMakeLists.txt
│   └── main.c
└── README.md                  This is the file you are currently reading
```

