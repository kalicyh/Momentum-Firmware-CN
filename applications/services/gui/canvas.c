#include "canvas_i.h"
#include "icon_animation_i.h"

#include <furi.h>
#include <furi_hal.h>
#include <stdint.h>
#include <u8g2_glue.h>
#include <momentum/asset_packs_i.h>
#include <momentum/settings.h>

const uint8_t kalicyh[1753] =
    "z\0\3\2\4\4\3\4\5\13\15\0\376\10\376\12\377\1a\2\317\4\30 \5\0L\13!\7\221F"
    "\213S\0\42\7\64}\213\310\24#\16\226\304\233\250eX\242^\206%j\1$\17\245<\253l\251("
    "\231\250%Je\213\0%\20\226<\233(\351\242%a\232DI\27-\1&\16\205D\253,\211\222\254"
    "\62%Q\244\4'\6\61\376\212\1(\13\263=\253$J\242nQ\26)\14\263=\213,\312\242.Q"
    "\22\1*\14uD\253J\345\240,M\21\0+\13wD\274\270\66\14Y\134\3,\7\62>\13E\1"
    "-\6\25d\213A.\6!\306\12\1/\14\304<\273\246\254\224\225\262\32\0\60\12\205D\233%\363-"
    "Y\0\61\11\205D\213\261O\203\0\62\13\205D\233%\13km\203\0\63\14\205D\213!\15\223\65\14"
    "\7\5\64\16\206\304;-\211\272d\311\60\246\11\0\65\15\205D\213!\11\303!\15\303A\1\66\15\205"
    "D\233%\14\207$\263%\13\0\67\13\205D\213A\254\205YX\2\70\15\205D\233%\323\222%\263%"
    "\13\0\71\15\205D\233%\263%C\250%\13\0:\6aD\11I;\11\202>\213!V\24\0<\10"
    "\225D\313\254k\7=\10\65\134\213A\35\4>\11\225D\213\264[G\0\77\15\225D\233%\323\302H"
    "\313\241\60\2@\24\247<\254\255\222HZ\42)JE\251H\211\222e\23\0A\16\207D\274\70M\302"
    "$+\15J\252\6B\15\206\304\213A\11\305a\11\215\303\2C\14\206\304\233!\11\325\216\311\220\0D"
    "\15\207D\214A\12\223\324c\62H\0E\12\205D\213c\70\214\305AF\13\205D\213c\70$a#"
    "\0G\15\206\304\233!\11\325\332(&\203\0H\13\206\304\213\320\70\14\242c\0I\10\203D\212%\352"
    "eJ\10\243\64\252\376\264\0K\15\205D\213LJJ\232\226D\225,L\11\205D\213\260\217\203\0M"
    "\20\207D\14m\310\226\212R\221\42)R\325\0N\15\206\304\213pS\42)\321Fc\0O\14\207D"
    "\254\255\222\272&Y\66\1P\14\205D\213!\311l\203\22\26\1Q\16\227<\254\255\222\272&Y\266\3"
    "\11\0R\20\206\304\213!\312\222,\311\222!jK\302\0S\14\205D\233AL\327\60\34\24\0T\11"
    "\207D\214C\26\367\15U\12\206\304\213\320\217\311\220\0V\17\207D\214TM\262(\253\204I\32g\0"
    "W\21\211D\215,\323\62\255\322)iJ\332\212Y\4X\15\206\304\213PL\242L\213ZB\61Y\13"
    "\207D\214\64\311*i\334\15Z\12\207D\214C\332\347a\10[\11\263>\213!\352O\3\134\14\245<"
    "\213\60\15\323\60\15\323\60]\11\263=\213\251\77\15\1^\10\65t\253,\251\5_\6\25<\213A`"
    "\7\62\375\212$\12a\14eD\233%K\6MK\206\0b\14\205D\213\60\34\222\314mP\0c\10"
    "d\304\232!k\34d\13\205D\313\312\240\271%C\0e\13eD\233%\33\206\60\35\2f\11\203D"
    "\232i\210:\1g\14\205\64\233AsK\206\60Y\0h\13\205D\213\60\34\222\314[\0i\7\201D"
    "\211d\30j\10\242\264\231,\351ek\15\205D\213\260\224\224\264$\252d\1l\7\201D\211\203\0m"
    "\16gD\214E\211\42)\222\42)\222\12n\11eD\213!\311\274\5o\12eD\233%sK\26\0"
    "p\14\205\64\213!\311\334\6%\14\1q\13\205\64\233AsK\206\260\0r\10cD\212!\352\4s"
    "\14eD\233%K\324$K\26\0t\12\203D\212(\32\242\66\1u\11eD\213\314[\62\4v\14"
    "eD\213LKJI\26F\0w\16gD\214(\222\42\245\242t\213\262\4x\13eD\213,\251U"
    "jZ\0y\15\205\64\213LKJI\26fa\6z\12eD\213A\314\332\6\1{\13\243<\252$"
    "\252dQ[\0|\7\261\276\212\7\1}\13\243<\212,\252%QK\4~\7&\334\33\311\2\200\17"
    "\225D+\251\222\15Q\66Da\24)\0\0\0\0\4\377\377N\216\27\273<\236\341\234c\71\226\16\7"
    "\65\307r,\307r,GV\0Qe\30\273<>\35\314\261\34\313\241$G\352@\26gi-\7\222"
    "\34\12Qh\31\273<\336\34Jr KK\312\240\250\71\226#\203\216\344X<\134\0Qs\27\273<"
    "\256\264\26\16\347\34K\207C\234CI\16diI\7\4Q\231\34\273<\236\341\220\344\210\224\206\303\232"
    "c\303\220c\321\60$\71\226\3I\16e\0Q\373\26\273<\336\34\213\207s\216\245\303A\215\263RV"
    "\312J\303\5R\237\32\273<~ \307\262AJ\243a\12\243bT\214\242%\33\263\64\314,\0S:"
    "\32\272=\216\227\34J\302\250\26eI\26\326\222,\312\242$\214rh\70\4Ss\36\272=\216A\31"
    "\264$\32\226HK\242a\211\264$R\262H\212\24\245\213\224\344P\6T\15\31\272<\276\34\32\206,"
    "\314\222(\313t$\7\36\324,\315\322l\30\2V\336\30\272=\216\7\35\321\21i\210\244\222T\222\206"
    "H*\351\310\360\216\4Y\7\31\273<\276\34\33F-\214v$Q\305\341\61*\16C\30\25\207!\2"
    "[\211\30\273<\336x\70$\71\242\205i<\34\264\252\226\3;\22i\253\0[\214\33\273<\336x\70"
    "$\71\42\15J\16\17\207\60\311\201(\7\242,\312*\351\20[\306\32\273<\336tx\253\364\26\65&"
    "Q\62$\203\222\346@T\214\212\303\20\1b\20\33\273<\356$G\242h\70$a\32\246C\22\265D"
    "-\265\250\245\224$b&g:\34\273<\256\34\213\206\60*\15S\30\325\226(S\244J\324\22\25\223"
    ",\211\304\1g\345\31\273<\336t\70hI\65*\15\7)\15\207!L\303a\310\341\341 p\271\30"
    "\273<\336\34\313\261A\316\201C\230\206i\70\14\71!\211*YTw\13\32\273<\236\341\34\17\203\34"
    "\17\7-\14\207!K\302(\32\326\60\35&\0\213\276\32\273<\236l\10\243:\20\305\331\260c\311\260"
    "EYK\250\245Y\222n\2\217\324\35\273<\236\34\220\242!\214rl\70iQ\245\26\25\223(\311\42"
    "-\251\3\331\60\4\224\245 \273<\236pP\302,\31\222L\35\16I\26e\331\260\14RVJj\221"
    "\22%Q\22&\0\226\217 \273<\216\61K\224aH\32\265A\251EIrH:%R\62$Y\22"
    "%\231\32E\203\0\227b\30\272=\216\207\60G\342\341 \225\244!\222J\322\20I\245\341\35\11\230u"
    "\31\273<\216\7\65\7\16a\32F\305\250\30\25#%\216\342P\222\23\0\0";

const CanvasFontParameters canvas_font_params[FontTotalNumber] = {
    [FontPrimary] = {.leading_default = 12, .leading_min = 11, .height = 8, .descender = 2},
    [FontSecondary] = {.leading_default = 11, .leading_min = 9, .height = 7, .descender = 2},
    [FontKeyboard] = {.leading_default = 11, .leading_min = 9, .height = 7, .descender = 2},
    [FontBigNumbers] = {.leading_default = 18, .leading_min = 16, .height = 15, .descender = 0},
    [FontBatteryPercent] = {.leading_default = 11, .leading_min = 9, .height = 6, .descender = 0},
};

Canvas* canvas_init(void) {
    Canvas* canvas = malloc(sizeof(Canvas));
    canvas->compress_icon = compress_icon_alloc(ICON_DECOMPRESSOR_BUFFER_SIZE);

    // Initialize mutex
    canvas->mutex = furi_mutex_alloc(FuriMutexTypeNormal);

    // Initialize callback array
    CanvasCallbackPairArray_init(canvas->canvas_callback_pair);

    // Setup u8g2
    u8g2_Setup_st756x_flipper(&canvas->fb, U8G2_R0, u8x8_hw_spi_stm32, u8g2_gpio_and_delay_stm32);
    canvas->orientation = CanvasOrientationHorizontal;
    // Initialize display
    u8g2_InitDisplay(&canvas->fb);
    // Wake up display
    u8g2_SetPowerSave(&canvas->fb, 0);

    // Clear buffer and send to device
    canvas_clear(canvas);
    canvas_commit(canvas);

    return canvas;
}

void canvas_free(Canvas* canvas) {
    furi_check(canvas);
    compress_icon_free(canvas->compress_icon);
    CanvasCallbackPairArray_clear(canvas->canvas_callback_pair);
    furi_mutex_free(canvas->mutex);
    free(canvas);
}

static void canvas_lock(Canvas* canvas) {
    furi_assert(canvas);
    furi_check(furi_mutex_acquire(canvas->mutex, FuriWaitForever) == FuriStatusOk);
}

static void canvas_unlock(Canvas* canvas) {
    furi_assert(canvas);
    furi_check(furi_mutex_release(canvas->mutex) == FuriStatusOk);
}

void canvas_reset(Canvas* canvas) {
    furi_check(canvas);

    canvas_clear(canvas);

    canvas_set_color(canvas, ColorBlack);
    // canvas_set_font(canvas, FontSecondary);
    canvas_set_custom_u8g2_font(canvas, kalicyh);
    canvas_set_font_direction(canvas, CanvasDirectionLeftToRight);
}

void canvas_commit(Canvas* canvas) {
    furi_check(canvas);
    u8g2_SendBuffer(&canvas->fb);

    // Iterate over callbacks
    canvas_lock(canvas);
    for
        M_EACH(p, canvas->canvas_callback_pair, CanvasCallbackPairArray_t) {
            p->callback(
                canvas_get_buffer(canvas),
                canvas_get_buffer_size(canvas),
                canvas_get_orientation(canvas),
                p->context);
        }
    canvas_unlock(canvas);
}

uint8_t* canvas_get_buffer(Canvas* canvas) {
    furi_check(canvas);
    return u8g2_GetBufferPtr(&canvas->fb);
}

size_t canvas_get_buffer_size(const Canvas* canvas) {
    furi_check(canvas);
    return u8g2_GetBufferTileWidth(&canvas->fb) * u8g2_GetBufferTileHeight(&canvas->fb) * 8;
}

void canvas_frame_set(
    Canvas* canvas,
    int32_t offset_x,
    int32_t offset_y,
    size_t width,
    size_t height) {
    furi_check(canvas);
    canvas->offset_x = offset_x;
    canvas->offset_y = offset_y;
    canvas->width = width;
    canvas->height = height;
}

size_t canvas_width(const Canvas* canvas) {
    furi_check(canvas);
    return canvas->width;
}

size_t canvas_height(const Canvas* canvas) {
    furi_check(canvas);
    return canvas->height;
}

size_t canvas_current_font_height(const Canvas* canvas) {
    furi_check(canvas);
    size_t font_height = u8g2_GetMaxCharHeight(&canvas->fb);

    if(canvas->fb.font == u8g2_font_haxrcorp4089_tr) {
        font_height += 1;
    }

    return font_height;
}

size_t canvas_current_font_width(const Canvas* canvas) {
    furi_check(canvas);
    return u8g2_GetMaxCharWidth(&canvas->fb);
}

const CanvasFontParameters* canvas_get_font_params(const Canvas* canvas, Font font) {
    furi_check(canvas);
    furi_check(font < FontTotalNumber);
    if(asset_packs && asset_packs->font_params[font]) {
        return asset_packs->font_params[font];
    }
    return &canvas_font_params[font];
}

void canvas_clear(Canvas* canvas) {
    furi_check(canvas);
    if(momentum_settings.dark_mode) {
        u8g2_FillBuffer(&canvas->fb);
    } else {
        u8g2_ClearBuffer(&canvas->fb);
    }
}

void canvas_set_color(Canvas* canvas, Color color) {
    furi_check(canvas);
    if(momentum_settings.dark_mode) {
        if(color == ColorBlack) {
            color = ColorWhite;
        } else if(color == ColorWhite) {
            color = ColorBlack;
        }
    }
    u8g2_SetDrawColor(&canvas->fb, color);
}

void canvas_set_font_direction(Canvas* canvas, CanvasDirection dir) {
    furi_check(canvas);
    u8g2_SetFontDirection(&canvas->fb, dir);
}

void canvas_invert_color(Canvas* canvas) {
    if(canvas->fb.draw_color == ColorXOR && momentum_settings.dark_mode) {
        // XOR is 0x02, invert changes it to 0x00 which is White
        // Basically like resetting to background color
        // In Dark Mode, background color is Black instead
        canvas->fb.draw_color = ColorBlack;
    } else {
        canvas->fb.draw_color = !canvas->fb.draw_color;
    }
}

void canvas_set_font(Canvas* canvas, Font font) {
    furi_check(canvas);
    u8g2_SetFontMode(&canvas->fb, 1);
    if(asset_packs && asset_packs->fonts[font]) {
        u8g2_SetFont(&canvas->fb, asset_packs->fonts[font]);
        return;
    }
    switch(font) {
    case FontPrimary:
        u8g2_SetFont(&canvas->fb, u8g2_font_helvB08_tr);
        break;
    case FontSecondary:
        u8g2_SetFont(&canvas->fb, u8g2_font_haxrcorp4089_tr);
        break;
    case FontKeyboard:
        u8g2_SetFont(&canvas->fb, u8g2_font_profont11_mr);
        break;
    case FontBigNumbers:
        u8g2_SetFont(&canvas->fb, u8g2_font_profont22_tn);
        break;
    case FontBatteryPercent:
        u8g2_SetFont(&canvas->fb, u8g2_font_5x7_tr); //u8g2_font_micro_tr);
        break;
    default:
        furi_crash();
        break;
    }
}

void canvas_set_custom_u8g2_font(Canvas* canvas, const uint8_t* font) {
    furi_check(canvas);
    u8g2_SetFontMode(&canvas->fb, 1);
    u8g2_SetFont(&canvas->fb, font);
}

void canvas_draw_str(Canvas* canvas, int32_t x, int32_t y, const char* str) {
    furi_check(canvas);
    if(!str) return;
    x += canvas->offset_x;
    y += canvas->offset_y;
    u8g2_DrawUTF8(&canvas->fb, x, y, str);
}

void canvas_draw_str_aligned(
    Canvas* canvas,
    int32_t x,
    int32_t y,
    Align horizontal,
    Align vertical,
    const char* str) {
    furi_check(canvas);
    if(!str) return;
    x += canvas->offset_x;
    y += canvas->offset_y;

    switch(horizontal) {
    case AlignLeft:
        break;
    case AlignRight:
        x -= u8g2_GetUTF8Width(&canvas->fb, str);
        break;
    case AlignCenter:
        x -= (u8g2_GetUTF8Width(&canvas->fb, str) / 2);
        break;
    default:
        furi_crash();
        break;
    }

    switch(vertical) {
    case AlignTop:
        y += u8g2_GetAscent(&canvas->fb);
        break;
    case AlignBottom:
        break;
    case AlignCenter:
        y += (u8g2_GetAscent(&canvas->fb) / 2);
        break;
    default:
        furi_crash();
        break;
    }

    u8g2_DrawUTF8(&canvas->fb, x, y, str);
}

uint16_t canvas_string_width(Canvas* canvas, const char* str) {
    furi_check(canvas);
    if(!str) return 0;
    return u8g2_GetUTF8Width(&canvas->fb, str);
}

size_t canvas_glyph_width(Canvas* canvas, uint16_t symbol) {
    furi_check(canvas);
    return u8g2_GetGlyphWidth(&canvas->fb, symbol);
}

void canvas_draw_bitmap(
    Canvas* canvas,
    int32_t x,
    int32_t y,
    size_t width,
    size_t height,
    const uint8_t* compressed_bitmap_data) {
    furi_check(canvas);

    x += canvas->offset_x;
    y += canvas->offset_y;
    uint8_t* bitmap_data = NULL;
    compress_icon_decode(canvas->compress_icon, compressed_bitmap_data, &bitmap_data);
    canvas_draw_u8g2_bitmap(&canvas->fb, x, y, width, height, bitmap_data, IconRotation0);
}

void canvas_draw_icon_animation(
    Canvas* canvas,
    int32_t x,
    int32_t y,
    IconAnimation* icon_animation) {
    furi_check(canvas);
    furi_check(icon_animation);

    x += canvas->offset_x;
    y += canvas->offset_y;
    uint8_t* icon_data = NULL;
    compress_icon_decode(
        canvas->compress_icon, icon_animation_get_data(icon_animation), &icon_data);
    canvas_draw_u8g2_bitmap(
        &canvas->fb,
        x,
        y,
        icon_animation_get_width(icon_animation),
        icon_animation_get_height(icon_animation),
        icon_data,
        IconRotation0);
}

static void canvas_draw_u8g2_bitmap_int(
    u8g2_t* u8g2,
    u8g2_uint_t x,
    u8g2_uint_t y,
    u8g2_uint_t w,
    u8g2_uint_t h,
    bool mirror,
    bool rotation,
    const uint8_t* bitmap) {
    u8g2_uint_t blen;
    blen = w;
    blen += 7;
    blen >>= 3;

    if(rotation && !mirror) {
        x += w + 1;
    } else if(mirror && !rotation) {
        y += h - 1;
    }

    while(h > 0) {
        const uint8_t* b = bitmap;
        uint16_t len = w;
        uint16_t x0 = x;
        uint16_t y0 = y;
        uint8_t mask;
        uint8_t color = u8g2->draw_color;
        uint8_t ncolor = (color == 0 ? 1 : 0);
        mask = 1;

        while(len > 0) {
            if(u8x8_pgm_read(b) & mask) {
                u8g2->draw_color = color;
                u8g2_DrawHVLine(u8g2, x0, y0, 1, 0);
            } else if(u8g2->bitmap_transparency == 0) {
                u8g2->draw_color = ncolor;
                u8g2_DrawHVLine(u8g2, x0, y0, 1, 0);
            }

            if(rotation) {
                y0++;
            } else {
                x0++;
            }

            mask <<= 1;
            if(mask == 0) {
                mask = 1;
                b++;
            }
            len--;
        }

        u8g2->draw_color = color;
        bitmap += blen;

        if(mirror) {
            if(rotation) {
                x++;
            } else {
                y--;
            }
        } else {
            if(rotation) {
                x--;
            } else {
                y++;
            }
        }
        h--;
    }
}

void canvas_draw_u8g2_bitmap(
    u8g2_t* u8g2,
    int32_t x,
    int32_t y,
    size_t width,
    size_t height,
    const uint8_t* bitmap,
    IconRotation rotation) {
#ifdef U8G2_WITH_INTERSECTION
    if(u8g2_IsIntersection(u8g2, x, y, x + width, y + height) == 0) return;
#endif /* U8G2_WITH_INTERSECTION */

    switch(rotation) {
    case IconRotation0:
        canvas_draw_u8g2_bitmap_int(u8g2, x, y, width, height, 0, 0, bitmap);
        break;
    case IconRotation90:
        canvas_draw_u8g2_bitmap_int(u8g2, x, y, width, height, 0, 1, bitmap);
        break;
    case IconRotation180:
        canvas_draw_u8g2_bitmap_int(u8g2, x, y, width, height, 1, 0, bitmap);
        break;
    case IconRotation270:
        canvas_draw_u8g2_bitmap_int(u8g2, x, y, width, height, 1, 1, bitmap);
        break;
    default:
        break;
    }
}

void canvas_draw_icon_ex(
    Canvas* canvas,
    int32_t x,
    int32_t y,
    const Icon* icon,
    IconRotation rotation) {
    furi_check(canvas);
    furi_check(icon);

    x += canvas->offset_x;
    y += canvas->offset_y;
    uint8_t* icon_data = NULL;
    icon = asset_packs_swap_icon(icon);
    compress_icon_decode(canvas->compress_icon, icon_get_frame_data(icon, 0), &icon_data);
    canvas_draw_u8g2_bitmap(
        &canvas->fb, x, y, icon_get_width(icon), icon_get_height(icon), icon_data, rotation);
}

void canvas_draw_icon(Canvas* canvas, int32_t x, int32_t y, const Icon* icon) {
    furi_check(canvas);
    furi_check(icon);

    x += canvas->offset_x;
    y += canvas->offset_y;
    uint8_t* icon_data = NULL;
    icon = asset_packs_swap_icon(icon);
    compress_icon_decode(canvas->compress_icon, icon_get_frame_data(icon, 0), &icon_data);
    canvas_draw_u8g2_bitmap(
        &canvas->fb, x, y, icon_get_width(icon), icon_get_height(icon), icon_data, IconRotation0);
}

void canvas_draw_dot(Canvas* canvas, int32_t x, int32_t y) {
    furi_check(canvas);
    x += canvas->offset_x;
    y += canvas->offset_y;
    u8g2_DrawPixel(&canvas->fb, x, y);
}

void canvas_draw_box(Canvas* canvas, int32_t x, int32_t y, size_t width, size_t height) {
    furi_check(canvas);
    x += canvas->offset_x;
    y += canvas->offset_y;
    u8g2_DrawBox(&canvas->fb, x, y, width, height);
}

void canvas_draw_rbox(
    Canvas* canvas,
    int32_t x,
    int32_t y,
    size_t width,
    size_t height,
    size_t radius) {
    furi_check(canvas);
    x += canvas->offset_x;
    y += canvas->offset_y;
    u8g2_DrawRBox(&canvas->fb, x, y, width, height, radius);
}

void canvas_draw_frame(Canvas* canvas, int32_t x, int32_t y, size_t width, size_t height) {
    furi_check(canvas);
    x += canvas->offset_x;
    y += canvas->offset_y;
    u8g2_DrawFrame(&canvas->fb, x, y, width, height);
}

void canvas_draw_rframe(
    Canvas* canvas,
    int32_t x,
    int32_t y,
    size_t width,
    size_t height,
    size_t radius) {
    furi_check(canvas);
    x += canvas->offset_x;
    y += canvas->offset_y;
    u8g2_DrawRFrame(&canvas->fb, x, y, width, height, radius);
}

void canvas_draw_line(Canvas* canvas, int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
    furi_check(canvas);
    x1 += canvas->offset_x;
    y1 += canvas->offset_y;
    x2 += canvas->offset_x;
    y2 += canvas->offset_y;
    u8g2_DrawLine(&canvas->fb, x1, y1, x2, y2);
}

void canvas_draw_circle(Canvas* canvas, int32_t x, int32_t y, size_t radius) {
    furi_check(canvas);
    x += canvas->offset_x;
    y += canvas->offset_y;
    u8g2_DrawCircle(&canvas->fb, x, y, radius, U8G2_DRAW_ALL);
}

void canvas_draw_disc(Canvas* canvas, int32_t x, int32_t y, size_t radius) {
    furi_check(canvas);
    x += canvas->offset_x;
    y += canvas->offset_y;
    u8g2_DrawDisc(&canvas->fb, x, y, radius, U8G2_DRAW_ALL);
}

void canvas_draw_triangle(
    Canvas* canvas,
    int32_t x,
    int32_t y,
    size_t base,
    size_t height,
    CanvasDirection dir) {
    furi_check(canvas);
    if(dir == CanvasDirectionBottomToTop) {
        canvas_draw_line(canvas, x - base / 2, y, x + base / 2, y);
        canvas_draw_line(canvas, x - base / 2, y, x, y - height + 1);
        canvas_draw_line(canvas, x, y - height + 1, x + base / 2, y);
    } else if(dir == CanvasDirectionTopToBottom) {
        canvas_draw_line(canvas, x - base / 2, y, x + base / 2, y);
        canvas_draw_line(canvas, x - base / 2, y, x, y + height - 1);
        canvas_draw_line(canvas, x, y + height - 1, x + base / 2, y);
    } else if(dir == CanvasDirectionRightToLeft) {
        canvas_draw_line(canvas, x, y - base / 2, x, y + base / 2);
        canvas_draw_line(canvas, x, y - base / 2, x - height + 1, y);
        canvas_draw_line(canvas, x - height + 1, y, x, y + base / 2);
    } else if(dir == CanvasDirectionLeftToRight) {
        canvas_draw_line(canvas, x, y - base / 2, x, y + base / 2);
        canvas_draw_line(canvas, x, y - base / 2, x + height - 1, y);
        canvas_draw_line(canvas, x + height - 1, y, x, y + base / 2);
    }
}

void canvas_draw_xbm(
    Canvas* canvas,
    int32_t x,
    int32_t y,
    size_t width,
    size_t height,
    const uint8_t* bitmap) {
    furi_check(canvas);
    x += canvas->offset_x;
    y += canvas->offset_y;
    canvas_draw_u8g2_bitmap(&canvas->fb, x, y, width, height, bitmap, IconRotation0);
}

void canvas_draw_glyph(Canvas* canvas, int32_t x, int32_t y, uint16_t ch) {
    furi_check(canvas);
    x += canvas->offset_x;
    y += canvas->offset_y;
    u8g2_DrawGlyph(&canvas->fb, x, y, ch);
}

void canvas_set_bitmap_mode(Canvas* canvas, bool alpha) {
    u8g2_SetBitmapMode(&canvas->fb, alpha ? 1 : 0);
}

void canvas_set_orientation(Canvas* canvas, CanvasOrientation orientation) {
    furi_check(canvas);
    const u8g2_cb_t* rotate_cb = NULL;
    bool need_swap = false;
    if(canvas->orientation != orientation) {
        switch(orientation) {
        case CanvasOrientationHorizontal:
            need_swap = canvas->orientation == CanvasOrientationVertical ||
                        canvas->orientation == CanvasOrientationVerticalFlip;
            rotate_cb = U8G2_R0;
            break;
        case CanvasOrientationHorizontalFlip:
            need_swap = canvas->orientation == CanvasOrientationVertical ||
                        canvas->orientation == CanvasOrientationVerticalFlip;
            rotate_cb = U8G2_R2;
            break;
        case CanvasOrientationVertical:
            need_swap = canvas->orientation == CanvasOrientationHorizontal ||
                        canvas->orientation == CanvasOrientationHorizontalFlip;
            rotate_cb = U8G2_R3;
            break;
        case CanvasOrientationVerticalFlip:
            need_swap = canvas->orientation == CanvasOrientationHorizontal ||
                        canvas->orientation == CanvasOrientationHorizontalFlip;
            rotate_cb = U8G2_R1;
            break;
        default:
            furi_crash();
        }

        if(need_swap) FURI_SWAP(canvas->width, canvas->height);
        u8g2_SetDisplayRotation(&canvas->fb, rotate_cb);
        canvas->orientation = orientation;
    }
}

CanvasOrientation canvas_get_orientation(const Canvas* canvas) {
    return canvas->orientation;
}

void canvas_add_framebuffer_callback(Canvas* canvas, CanvasCommitCallback callback, void* context) {
    furi_check(canvas);

    const CanvasCallbackPair p = {callback, context};

    canvas_lock(canvas);
    furi_check(!CanvasCallbackPairArray_count(canvas->canvas_callback_pair, p));
    CanvasCallbackPairArray_push_back(canvas->canvas_callback_pair, p);
    canvas_unlock(canvas);
}

void canvas_remove_framebuffer_callback(
    Canvas* canvas,
    CanvasCommitCallback callback,
    void* context) {
    furi_check(canvas);

    const CanvasCallbackPair p = {callback, context};

    canvas_lock(canvas);
    furi_check(CanvasCallbackPairArray_count(canvas->canvas_callback_pair, p) == 1);
    CanvasCallbackPairArray_remove_val(canvas->canvas_callback_pair, p);
    canvas_unlock(canvas);
}
