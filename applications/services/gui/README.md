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
一万上下不东丢个中丸为主么之乐习书了二于些产亮亲人什仅今介他以仪们件份仿休伙会伤伪但位住何余作你使例供保信值储像儿允充先光入全公六关其内册再写军决准凑出分切列刚删别到制前剩剪功加动助勿包化匹区匿十升协单卡卸厂压原去友发取受只可右号吃同名后向吗否含听启呀告呢命和品哎哥哪商嘿器回因围固图在地址坏块型域基堆增声壳备复外多天失头夹好如始姓字存学安完定实容密对将小少尝就局屏展工左已布希常幕干并应度建开弄式引当录形彩影待很得循心必志忘忙快忽态怒总恢息您情想意感愤成我或所扇手打执扩扫找投折护报拔拟择持挂按损据捷掉接控描提插搜操擦收改效数整文新方无日旧时明是显景更最有朋望期未本机杂来析柠查标栈栏栗样核格框桌档桥梦检棕榄模橄橙次正此步死段母每比气水永池汽没法波注泳洋活测浏海消深添清游源满激点照爱片版牌牙特状率玩环现理生用电画界留略白的监盖盘目直看真眠眼睡知短码硬确示禁离秒称移程空笑符等签管箭类粉粘糕糟系索紧紫红级纵线绍经绕给绝统继维绿缀编置翻而耗背能脚自舞般色节英范药菜蓝蔚藏虚虹行表被装西要见规视览觉解警计认议记许设证试话误请读谁调谢豚贴资走起超跟跳踪蹈车转载辈辑输边过运返这进远连选透通速造道遥部都配醒里重量钟钥钮锁错键长闪闭问闲间阅阈限除陪随隐隔需震青静面音项须预频题颜额风饱验高鱼黄黑默！：？
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
elements_button_left
```
