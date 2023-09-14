---
description: PLC模块 V1.0版本
---
# 说明

主控 STM32F103C8T6 128Kb+20Kb 72MHz，开发环境CubeMx配置工程，IAR9.30.1开发环境，DAP-link仿真器

## 资源清单

| 类型     | IO            | 说明 |
| -------- | ------------- | ---- |
| MCU      | STM32F103C8T6 |      |
| 晶振     | 8M            |      |
| 光耦输入 | X0~X14        |      |
| 光耦输出 | Y0~Y10        |      |
| 模拟输入 | ADC           |      |
| 电机控制 | O11,O12       |      |
| 通信     | RS485         |      |

## 工程目录说明

```bash
.
├── 20230914_mcu_slave.ioc  # Cubemx生成工程配置文件
├── Core					# 用户源码文件
├── Drivers					# MCU驱动文件
├── EWARM					# IAR工程文件
├── docs					# 本工程的相关资料文件
└── readme.md				# 本说明文档
```

