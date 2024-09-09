/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 30;       /* snap pixel */
static const unsigned int gappih    = 9;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 9;       /* vert inner gap between windows */
static const unsigned int gappoh    = 9;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 9;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const char *fonts[]          = { "Iosevka Nerd Font Mono:size=10" };
static const char col_debkg[]       = "#1a1b26";
static const char col_acbkg[]       = "#414868";
static const char col_acfor[]       = "#c0caf5";
static const char col_defor[]       = "#a9b1d6";
static const char col_debor[]       = "#24283b";
static const char col_acbor[]       = "#2ac3de";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_defor, col_debkg,  col_debor },
	[SchemeSel]  = { col_acfor, col_acbkg,  col_acbor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firrfox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.52; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "  ",      tile },    /* first entry is default */
	{ "  ",      monocle },
	{ "  ",     dwindle },
	{ "  ",      bstack },
	{ "  ",      bstackhoriz },
	{ " 󱗼 ",      grid },
	{ " 󱇚 ",      horizgrid },
        { "  ",      centeredmaster },
	{ "  ",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "rofi", "-show", "drun" , NULL };
static const char *termcmd[]  = { "alacritty", NULL };

#include "movestack.c"
#include "unfloat.c"


static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
        { MODKEY,                   XK_equal,      incnmaster,     {.i = +1 } },
	{ MODKEY,                   XK_minus,      incnmaster,     {.i = -1 } },
	{ MODKEY,                XK_bracketleft,   shiftview,      {.i = -1 } },
	{ MODKEY,                XK_bracketright,  shiftview,      {.i = +1 } },
	{ MODKEY|ShiftMask,      XK_bracketleft,   shifttag,       {.i = -1 } },
	{ MODKEY|ShiftMask,      XK_bracketright,  shifttag,       {.i = +1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
        { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
        { MODKEY,                       XK_h,      setcfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setcfact,       {.f = +0.05} },
        { MODKEY,                       XK_i,      setcfact,       {.f = +0.00} },
        { MODKEY|ShiftMask,             XK_k,      movestack,      {.i = +1 } },
        { MODKEY|ShiftMask,             XK_j,      movestack,      {.i = -1 } },
        { MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
        { MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
        { MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
        { MODKEY|Mod1Mask,              XK_h,      incrgaps,       {.i = +1 } },
        { MODKEY|Mod1Mask,              XK_l,      incrgaps,       {.i = -1 } },
        { MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
        { MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|Mod1Mask,              XK_minus,  cyclelayout,    {.i = -1 } },
        { MODKEY|Mod1Mask,              XK_equal,  cyclelayout,    {.i = +1 } },
        { MODKEY,                       XK_s,      togglefloating, {0} },
	{ MODKEY,                       XK_S,      unfloatvisible, {0} },
	{ MODKEY|ShiftMask,             XK_t,      unfloatvisible, {.v = &layouts[0]} },
        { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
        { MODKEY|Mod1Mask,              XK_q,      quit,           {0} },
        { MODKEY|Mod1Mask,              XK_r,      quit,           {1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

