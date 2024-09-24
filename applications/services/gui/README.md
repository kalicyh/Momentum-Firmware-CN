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

## 正则表达式

```
"([^\u4e00-\u9fa5"]*)"
```

方便搜索未修改的内容

## 目前字库内容

中文需要放在符号之前，中文的符号需要放在ABCD之前

```
一万上下不与丢个中为主之乐习书了二于些交产亮仅介他以仪件份仿休会伤伪位住何余作你使例供保信值停储儿允充先光入全公六关其内册写军决准凑出分切列删别到制刻前剩剪功加动助勿包化匹区匿十升协单卡卸厂压原发取受变只可右号吃同名后向否含听启呀告命和品哎商器回因围固图在地址坏块型域基堆增声壳处备复外多天失头夹好如始姓字存学安完定实容密对将小少尝局屏展左已布常幕并序应度延建开弃式引当录形彩影待得循心必志忘忙快忽态怒性总恢息您情愤憩成我或所扇手打执扩扫投护报拔拟择持挂按损据捷掉接控描提插搜操擦收改放效数整文断新方无日旧时明是显景暂更最有期未本机杂束来析柠查标栈栏栗样核格框桌档桥检棕榄模橄橙次止正此步段母比气水永池汽没法波注洋活流测浏海消深添清源满激照片版牌牙特状率环现理生用电画界留略白的监盖盘目真眠着睡知短码硬确示禁秒称移程空符等签管箭类粉粘糕糟系索紧紫繁红级纵线绍经结绕绝统继续维绿缀编置群翻而耗背能脚自般色节英范菜蓝蔚藏虚虹行表被装要规视览解警计认议记许设证试误请读调豚贴资超跟跳踪车载辑输边过运返这进远连迟退送选透通速造道遥部配里重量钟钥钮锁错键长闪闭问闲间阅阈限除陪随隐隔需震青静面音页项须频题颜额风饱验高黄黑默！：？
```
