/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrains Mono:size=10" };
static const char dmenufont[]       = "JetBrains Mono:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#98971a";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
    { "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODALT Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODALT,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODALT|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODALT|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODALT|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "alacritty", "-t", scratchpadname, NULL };

#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */

	{ MODALT|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
    { MODALT,                       XK_minus,  killclient,     {0} },

    { MODALT,                       XK_q,      setlayout,      {.v = &layouts[0]} },
    { MODALT,                       XK_w,      setlayout,      {.v = &layouts[1]} },
    { MODALT,                       XK_e,      setlayout,      {.v = &layouts[2]} },
    { MODALT,                       XK_a,      setlayout,      {0} },

    { MODALT,                       XK_space,  togglescratch,  {.v = scratchpadcmd } },
    { MODALT,                       XK_d,      togglebar,      {0} },

    { MODALT,                       XK_j,      focusstack,     {.i = +1 } },
    { MODALT,                       XK_k,      focusstack,     {.i = -1 } },
    { MODALT|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
    { MODALT|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODALT,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODALT,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODALT,                       XK_Return, zoom,           {0} },

	{ MODALT,                       XK_m,      view,           {0} },
	{ MODALT,                       XK_0,      view,           {.ui = ~0 } },

    { MODALT,                       XK_comma,  incnmaster,     {.i = +1 } },
    { MODALT,                       XK_period, incnmaster,     {.i = -1 } },

    //{ MODALT|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	//{ MODALT,                       XK_comma,  focusmon,       {.i = -1 } },
	//{ MODALT,                       XK_period, focusmon,       {.i = +1 } },
	//{ MODALT|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	//{ MODALT|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	TAGKEYS(                        XK_u,                      0)
	TAGKEYS(                        XK_i,                      1)
	TAGKEYS(                        XK_o,                      2)
	TAGKEYS(                        XK_p,                      3)
	TAGKEYS(                        XK_7,                      4)
	TAGKEYS(                        XK_8,                      5)
	TAGKEYS(                        XK_9,                      6)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODALT,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODALT,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODALT,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODALT,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODALT,         Button3,        toggletag,      {0} },
};

