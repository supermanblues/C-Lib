/**
 * @author: waingxiaoqiang
 * @create-date: 2020-04-21
 * @modify-date: 2020-05-07
 * @version: 0.0.3
 * @description: Common Header File
 */
/* ========================== Common Start ========================= */
#ifndef __COMMON_H__
#define __COMMON_H__

typedef long long int ll;

#define rep(inc, frm, to) for (int inc = (frm); inc < (to); ++inc)
#define rep2(inc, frm, to) for (int inc = (frm); inc > (to); --inc)
#define for_(inc, frm, to) rep(inc, frm, to)
#define for_prev_(inc, frm, to) rep2(inc, frm, to)

#define setbit(x, y) x |= 1 << y
#define clrbit(x, y) x &= ~(1 << y)
#define getbit(x, y) x >> y & 1
#define flipbit(x, y) x ^= 1 << y
#define show_bin(x) { rep2(i, 31, ~0) printf("%d%c", getbit(x, i), i ? 0 : 10); }

#define r() fast_read()

int is_digit(const char);
ll fast_read(void);

#endif
/* ========================== Common End ========================= */
