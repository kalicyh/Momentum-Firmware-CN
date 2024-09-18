## 汉化方式

### 一、大部分内容汉化

#### （1）、生成字库数据

利用[u8g2_cn_tools](https://github.com/kalicyh/u8g2_cn_tools)

#### （2）、挂载字库

创建导入的文件`kalicyh_font.h`和`kalicyh_font.c`便于维护

修改`canvas.c`文件

添加以下代码
```C
#include "kalicyh_font.h"
canvas_set_custom_u8g2_font(canvas, kalicyh);
```

##### 示例：
```C
#include "kalicyh_font.h"

void canvas_draw_str(Canvas* canvas, int32_t x, int32_t y, const char* str) {
    canvas_set_custom_u8g2_font(canvas, kalicyh);
    furi_check(canvas);
    if(!str) return;
    x += canvas->offset_x;
    y += canvas->offset_y;
    u8g2_DrawUTF8(&canvas->fb, x, y, str);
}
```

### 二、部分特殊汉化

#### 设置内的APP列表

修改`Momentum-Firmware\applications\settings`目录内的`*.fam`的`name`字段

修改`scripts\fbt\elfmanifest.py`内的`self.name.encode("UTF-8")`

```PY
@dataclass
class ElfManifestV1:
    stack_size: int
    app_version: int
    name: str = ""
    icon: bytes = field(default=b"")

    def as_bytes(self):
        return struct.pack(
            "<hI32s?32s",
            self.stack_size,
            self.app_version,
            bytes(self.name.encode("UTF-8")),
            bool(self.icon),
            self.icon,
        )
```

## 目前字库内容

中文需要放在符号之前，中文的符号需要放在ABCD之前

```
心情最高等级关闭设备开启文件夹在前显示隐藏内部标签收超时默认选择资产包加载更新清单检查写入闪存验证无线固卸安装核正忙项字节份配置恢复理目录解压源动画面重中错误报告待卡取消对所有之的将被除完成蓝牙损坏模式只要这个我绝不会因为你陪而生气禁用返回保持主应外打多操作移快捷键上下右左按桌您改丢失长类型确定输当码已匹试到箭头激活请记住或来秒分钟自锁间乐一步准使符号忘能通过整阅读档如何般未知监听比度背光亮音量匿震儿电池机升需进行维护可助于决些问题效信息闲好吃充哎呀得耗满限制休眠数据基测挂尝插格化了擦出厂储和次法名称虚拟总计剩余现以块全容警调跟踪公英手旧版随方向位日期志别波特率堆栈睡命图形菜屏状态栏浏览器界协议杂幕海豚伪介绍列表本是否允许扩展范围照系统地拔掉小速循环提透明纵紧凑样添少边框景经值愤怒程受伤橙色红深黄橄榄青绿水蔚军紫洋粉棕白静彩虹隔饱此硬颜真实黑翻盖壳仅含母留空姓栗柠品例跳频后绕区域段必须先引脚缀析仪？！：ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 !"#$%&'()*+,-./:;<=>?@[\]^_`{|}~
```

## 可用函数

```
dialog_ex_set_right_button_text
elements_multiline_text
desktop_view_pin_input_set_label_secondary
elements_button_left
desktop_view_pin_input_set_label_primary
submenu_set_header
submenu_add_item
其他不一一列举了...
```

### 已知bug

暂时没找到方法实现中文的函数

```
snprintf
furi_string_cat_printf
dialog_ex_set_header
dialog_ex_set_text
elements_multiline_text_aligned
popup_set_header
popup_set_text
```

能中文但是显示异常

```
dialog_ex_set_left_button_text
dialog_ex_set_center_button_text
elements_button_right
desktop_view_pin_input_set_label_button
```
