/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 15;        /* gaps between windows */
static const unsigned int snap      = 16;        /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const char *fonts[]          = { "Inconsolata Nerd Font Mono:size=12:style=Bold", "Material Design Icons:size=12" };
static const char dmenufont[]       = "Inconsolata Nerd Font Mono:size=12:style=Bold";
static const char col_gray1[]       = "#1d2021";
static const char col_gray2[]       = "#8ec07f";
static const char col_gray3[]       = "#a89984";
static const char col_gray4[]       = "#689d6a";
static const char col_cyan[]        = "#ebdbb2";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray4, col_gray1,  col_gray3 },
	[SchemeSel]  = { col_gray1, col_gray4,  col_gray4  },
	[SchemeStatus]  = { col_gray3, col_gray1,  "#000000"  },
	// Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { col_gray1, col_gray4,  "#000000"  },
	// Tagbar left selected {text,background,not used but cannot be empty}
	[SchemeTagsNorm]  = { col_gray3, col_gray1,  "#000000"  },
	// Tagbar left unselected {text,background,not used but cannot be empty}
	[SchemeInfoSel]  = { col_gray1, col_gray4,  "#000000"  },
	// infobar middle  selected {text,background,not used but cannot be empty}
	[SchemeInfoNorm]  = { col_gray3, col_gray1,  "#000000"  },
	// infobar middle  unselected {text,background,not used but cannot be empty}
};

/* tagging */
static const char *tags[] = { "󰈹", "󰞷", "󰣞", "󰋹", "󰣇", "󰊗", "󰋋", "󰐌"};
			     /*1 ,  2,   3,   4,   5,	7,   8,   9*/

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class    	    instance   title   tags mask switchtag isfloating monitor */
	{ "Gimp",   	 	NULL,  NULL,   1 << 3,    1,	    0,	         0 },
	{ "firefox",	  	NULL,  NULL,   1 << 0,    1,	    0,	         0 },
	{ "MuPDF",   		NULL,  NULL,   1 << 2,    1,	    0,	         0 },
	{ "Soffice",		NULL,  NULL,   1 << 2,    1,	    0,	         0 },
	{ "Filezilla",		NULL,  NULL,   1 << 2,    1,	    0,	         0 },
	{ "mpv",		NULL,  NULL,   1 << 7,    1,	    0,	         0 },
	{ "TelegramDesktop",	NULL,  NULL,   1 << 4,	  1,	    0,	         0 }
                                                                                                 
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "clu",      tile },    /* first entry is default */
	{ "clu",      NULL },    /* no layout function means floating behavior */
	{ "clu",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,               KEY,   view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,   KEY,   toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,     KEY,   tag,            {.ui = 1 << TAG} }, \
	{ Mod1Mask|ShiftMask,   KEY,   toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_gray4, "-sf", col_gray1, NULL};
static const char *termcmd[]  = { "urxvtc", NULL };
static const char *lock[]  = { "slock", NULL };
static const char *webbrowser1[] = { "firefox", NULL };
static const char *webbrowser2[] = { "qutebrowser", NULL };

#include "movestack.c"

static Key keys[] = {
	/* modifier             key        function        argument */
	{ MODKEY,               XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,     XK_x,      spawn,          {.v = lock } },
	{ MODKEY,               XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,		XK_w,	   spawn,	   {.v = webbrowser1 } },
	{ MODKEY,		XK_q,	   spawn,	   {.v = webbrowser2 } },
	{ MODKEY,		XK_e,	   spawn,	   SHCMD("urxvtc -e fff") },
	{ MODKEY|ShiftMask,	XK_u,	   spawn,	   SHCMD("setxkbmap us -option caps:escape") },
	{ MODKEY|ShiftMask,	XK_d,	   spawn,	   SHCMD("setxkbmap us -variant dvp -option caps:escape") },
//	{ MODKEY,               XK_b,      togglebar,      {0} },
	{ MODKEY,               XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,               XK_k,      focusstack,     {.i = -1 } },
//	{ MODKEY,               XK_i,      incnmaster,     {.i = +1 } },
//	{ MODKEY,               XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,               XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,               XK_l,      setmfact,       {.f = +0.05} },
    	{ MODKEY|ShiftMask,	XK_j,	   movestack,	   {.i = +1} },
    	{ MODKEY|ShiftMask,	XK_k,	   movestack,	   {.i = -1} },


//	{ MODKEY|ShiftMask,     XK_Return, zoom,           {0} },
	{ MODKEY,               XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,     XK_q,      killclient,     {0} },
	{ MODKEY,		XK_s,	   togglesticky,   {0} },
//	{ MODKEY,               XK_t,      setlayout,      {.v = &layouts[0]} },
//	{ MODKEY,               XK_f,      setlayout,      {.v = &layouts[1]} },
//	{ MODKEY,               XK_m,      setlayout,      {.v = &layouts[2]} },
//	{ MODKEY,               XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,     XK_space,  togglefloating, {0} },
//	{ MODKEY,               XK_0,      view,           {.ui = ~0 } },
//	{ MODKEY,               XK_comma,  focusmon,       {.i = -1 } },
//	{ MODKEY,               XK_period, focusmon,       {.i = +1 } },
//	{ MODKEY|ShiftMask,     XK_comma,  tagmon,         {.i = -1 } },
//	{ MODKEY|ShiftMask,     XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_minus,  spawn,	   SHCMD("amixer set Master 5%- ; kill -44 $(pidof ~/sources/blocks/dwmblocks)") },
	{ MODKEY|ShiftMask,     XK_equal,  spawn,	   SHCMD("amixer set Master 5%+ ; kill -44 $(pidof ~/sources/blocks/dwmblocks)") },
	
	/* { MODKEY|ShiftMask,     XK_minus,  spawn,	   SHCMD("amixer set Speaker 5%- ; kill -44 $(pidof ~/sources/blocks/dwmblocks)") }, */
	/* { MODKEY|ShiftMask,     XK_equal,  spawn,	   SHCMD("amixer set Speaker 5%+ ; kill -44 $(pidof ~/sources/blocks/dwmblocks)") }, */
	
	{ MODKEY|ShiftMask,	XK_m, 	   spawn, 	   SHCMD("~/Documents/scripts/wal2.sh") },
	{ MODKEY|ShiftMask,	XK_p, 	   spawn, 	   SHCMD("maim -m 1 ~/Pictures/artix/$(date +%F_%T).png") },

	TAGKEYS(                XK_1,                      0)
	TAGKEYS(                XK_2,                      1)
	TAGKEYS(                XK_3,                      2)
	TAGKEYS(                XK_4,                      3)
	TAGKEYS(                XK_5,                      4)
	TAGKEYS(                XK_7,                      5)
	TAGKEYS(                XK_8,                      6)
	TAGKEYS(                XK_9,                      7)
	{ MODKEY|ShiftMask,     XK_c,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
//	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
//	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
//	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
//	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
//	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

