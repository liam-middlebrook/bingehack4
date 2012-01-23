/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/* NitroHack may be freely redistributed.  See license for details. */

#ifndef RM_H
#define RM_H

/*
 * The dungeon presentation graphics code and data structures were rewritten
 * and generalized for NetHack's release 2 by Eric S. Raymond (eric@snark)
 * building on Don G. Kneller's MS-DOS implementation.	See drawing.c for
 * the code that permits the user to set the contents of the symbol structure.
 *
 * The door representation was changed by Ari Huttunen(ahuttune@niksula.hut.fi)
 */

/*
 * TLCORNER	TDWALL		TRCORNER
 * +-		-+-		-+
 * |		 |		 |
 *
 * TRWALL	CROSSWALL	TLWALL		HWALL
 * |		 |		 |
 * +-		-+-		-+		---
 * |		 |		 |
 *
 * BLCORNER	TUWALL		BRCORNER	VWALL
 * |		 |		 |		|
 * +-		-+-		-+		|
 */

/* Level location types */
#define STONE		0
#define VWALL		1
#define HWALL		2
#define TLCORNER	3
#define TRCORNER	4
#define BLCORNER	5
#define BRCORNER	6
#define CROSSWALL	7	/* For pretty mazes and special levels */
#define TUWALL		8
#define TDWALL		9
#define TLWALL		10
#define TRWALL		11
#define DBWALL		12
#define TREE		13	/* KMH */
#define SDOOR		14
#define SCORR		15
#define POOL		16
#define MOAT		17	/* pool that doesn't boil, adjust messages */
#define WATER		18
#define DRAWBRIDGE_UP	19
#define LAVAPOOL	20
#define IRONBARS	21	/* KMH */
#define DOOR		22
#define CORR		23
#define ROOM		24
#define STAIRS		25
#define LADDER		26
#define FOUNTAIN	27
#define THRONE		28
#define SINK		29
#define GRAVE		30
#define ALTAR		31
#define ICE		32
#define DRAWBRIDGE_DOWN 33
#define AIR		34
#define CLOUD		35

#define MAX_TYPE	36
#define INVALID_TYPE	127

/*
 * Avoid using the level types in inequalities:
 * these types are subject to change.
 * Instead, use one of the macros below.
 */
#define IS_WALL(typ)	((typ) && (typ) <= DBWALL)
#define IS_STWALL(typ)	((typ) <= DBWALL)	/* STONE <= (typ) <= DBWALL */
#define IS_ROCK(typ)	((typ) < POOL)		/* absolutely nonaccessible */
#define IS_DOOR(typ)	((typ) == DOOR)
#define IS_TREE(typ)	((typ) == TREE || \
			(level->flags.arboreal && (typ) == STONE))
#define ACCESSIBLE(typ) ((typ) >= DOOR)		/* good position */
#define IS_ROOM(typ)	((typ) >= ROOM)		/* ROOM, STAIRS, furniture.. */
#define ZAP_POS(typ)	((typ) >= POOL)
#define SPACE_POS(typ)	((typ) > DOOR)
#define IS_POOL(typ)	((typ) >= POOL && (typ) <= DRAWBRIDGE_UP)
#define IS_THRONE(typ)	((typ) == THRONE)
#define IS_FOUNTAIN(typ) ((typ) == FOUNTAIN)
#define IS_SINK(typ)	((typ) == SINK)
#define IS_GRAVE(typ)	((typ) == GRAVE)
#define IS_ALTAR(typ)	((typ) == ALTAR)
#define IS_DRAWBRIDGE(typ) ((typ) == DRAWBRIDGE_UP || (typ) == DRAWBRIDGE_DOWN)
#define IS_FURNITURE(typ) ((typ) >= STAIRS && (typ) <= ALTAR)
#define IS_AIR(typ)	((typ) == AIR || (typ) == CLOUD)
#define IS_SOFT(typ)	((typ) == AIR || (typ) == CLOUD || IS_POOL(typ))

/*
 * The screen symbols may be the default or defined at game startup time.
 * See drawing.c for defaults.
 * Note: {ibm|dec}_graphics[] arrays (also in drawing.c) must be kept in synch.
 */

/* begin dungeon characters */

#define S_unexplored	0
#define S_stone		1
#define S_vwall		2
#define S_hwall		3
#define S_tlcorn	4
#define S_trcorn	5
#define S_blcorn	6
#define S_brcorn	7
#define S_crwall	8
#define S_tuwall	9
#define S_tdwall	10
#define S_tlwall	11
#define S_trwall	12
#define S_ndoor		13
#define S_vodoor	14
#define S_hodoor	15
#define S_vcdoor	16	/* closed door, vertical wall */
#define S_hcdoor	17	/* closed door, horizontal wall */
#define S_bars		18	/* KMH -- iron bars */
#define S_tree		19	/* KMH */
#define S_room		20
#define S_darkroom	21
#define S_corr		22
#define S_litcorr	23
#define S_upstair	24
#define S_dnstair	25
#define S_upladder	26
#define S_dnladder	27
#define S_upsstair      28
#define S_dnsstair      29
#define S_altar		30
#define S_grave		31
#define S_throne	32
#define S_sink		33
#define S_fountain	34
#define S_pool		35
#define S_ice		36
#define S_lava		37
#define S_vodbridge	38
#define S_hodbridge	39
#define S_vcdbridge	40	/* closed drawbridge, vertical wall */
#define S_hcdbridge	41	/* closed drawbridge, horizontal wall */
#define S_air		42
#define S_cloud		43
#define S_water		44

#define MAXPCHARS	45	/* maximum number of mapped characters */

/* end dungeon characters, begin special effects */

#define E_digbeam	0	/* dig beam symbol */
#define E_flashbeam	1	/* camera flash symbol */
#define E_boomleft	2	/* thrown boomerang, open left, e.g ')'    */
#define E_boomright	3	/* thrown boomerang, open right, e.g. '('  */
#define E_ss1		4	/* 4 magic shield glyphs */
#define E_ss2		5
#define E_ss3		6
#define E_ss4		7
#define E_gascloud	8

/* The 8 swallow symbols.  Do NOT separate.  To change order or add, see */
/* the function swallow_to_effect() in display.c.			 */
#define S_sw_tl		0	/* swallow top left [1]			*/
#define S_sw_tc		1	/* swallow top center [2]	Order:	*/
#define S_sw_tr		2	/* swallow top right [3]		*/
#define S_sw_ml		3	/* swallow middle left [4]	1 2 3	*/
#define S_sw_mr		4	/* swallow middle right [6]	4 5 6	*/
#define S_sw_bl		5	/* swallow bottom left [7]	7 8 9	*/
#define S_sw_bc		6	/* swallow bottom center [8]		*/
#define S_sw_br		7	/* swallow bottom right [9]		*/

#define E_explode1	0	/* explosion top left			*/
#define E_explode2	1	/* explosion top center			*/
#define E_explode3	2	/* explosion top right		 Ex.	*/
#define E_explode4	3	/* explosion middle left		*/
#define E_explode5	4	/* explosion middle center	 /-\	*/
#define E_explode6	5	/* explosion middle right	 |@|	*/
#define E_explode7	6	/* explosion bottom left	 \-/	*/
#define E_explode8	7	/* explosion bottom center		*/
#define E_explode9	8	/* explosion bottom right		*/

/* end effects */


struct symdef {
    uchar sym;
    const char	*explanation;
    uchar color;
};

extern const struct nh_symdef defsyms[];	/* defaults */

extern const char * const trapexplain[];
extern const char * const defexplain[];
extern const char * const warnexplain[];

/*
 * The 5 possible states of doors
 */

#define D_NODOOR	0
#define D_BROKEN	1
#define D_ISOPEN	2
#define D_CLOSED	4
#define D_LOCKED	8
#define D_TRAPPED	16

/*
 * Some altars are considered as shrines, so we need a flag.
 */
#define AM_SHRINE	8

/*
 * Thrones should only be looted once.
 */
#define T_LOOTED	1

/*
 * Trees have more than one kick result.
 */
#define TREE_LOOTED	1
#define TREE_SWARM	2

/*
 * Fountains have limits, and special warnings.
 */
#define F_LOOTED	1
#define F_WARNED	2
#define FOUNTAIN_IS_WARNED(x,y)		(level->locations[x][y].looted & F_WARNED)
#define FOUNTAIN_IS_LOOTED(x,y)		(level->locations[x][y].looted & F_LOOTED)
#define SET_FOUNTAIN_WARNED(x,y)	level->locations[x][y].looted |= F_WARNED;
#define SET_FOUNTAIN_LOOTED(x,y)	level->locations[x][y].looted |= F_LOOTED;
#define CLEAR_FOUNTAIN_WARNED(x,y)	level->locations[x][y].looted &= ~F_WARNED;
#define CLEAR_FOUNTAIN_LOOTED(x,y)	level->locations[x][y].looted &= ~F_LOOTED;

/*
 * Doors are even worse :-) The special warning has a side effect
 * of instantly trapping the door, and if it was defined as trapped,
 * the guards consider that you have already been warned!
 */
#define D_WARNED	16

/*
 * Sinks have 3 different types of loot that shouldn't be abused
 */
#define S_LPUDDING	1
#define S_LDWASHER	2
#define S_LRING		4

/*
 * The four directions for a DrawBridge.
 */
#define DB_NORTH	0
#define DB_SOUTH	1
#define DB_EAST		2
#define DB_WEST		3
#define DB_DIR		3	/* mask for direction */

/*
 * What's under a drawbridge.
 */
#define DB_MOAT		0
#define DB_LAVA		4
#define DB_ICE		8
#define DB_FLOOR	16
#define DB_UNDER	28	/* mask for underneath */

/*
 * Wall information.
 */
#define WM_MASK		0x07	/* wall mode (bottom three bits) */
#define W_NONDIGGABLE	0x08
#define W_NONPASSWALL	0x10

/*
 * Ladders (in Vlad's tower) may be up or down.
 */
#define LA_UP		1
#define LA_DOWN		2

/*
 * Room areas may be iced pools
 */
#define ICED_POOL	8
#define ICED_MOAT	16

/*
 * The structure describing a coordinate position.
 * Before adding fields, remember that this will significantly affect
 * the size of temporary files and save files.
 */
struct rm {
	unsigned mem_bg:6;	/* remembered background */
	unsigned mem_trap:5;	/* remembered trap */
	unsigned mem_obj:10;	/* remembered object */
	unsigned mem_obj_mn:9;	/* monnum of remembered corpses, statues, figurines */
	unsigned mem_invis:1;	/* remembered invisible monster encounter */
	
	schar typ;		/* what is really there */
	uchar seenv;		/* seen vector */
	unsigned flags:5;	/* extra information for typ */
	unsigned horizontal:1; /* wall/door/etc is horiz. (more typ info) */
	unsigned lit:1;	/* speed hack for lit rooms */
	unsigned waslit:1;	/* remember if a location was lit */
	unsigned roomno:6;	/* room # for special rooms */
	unsigned edge:1;	/* marks boundaries for special rooms*/
};

/*
 * Add wall angle viewing by defining "modes" for each wall type.  Each
 * mode describes which parts of a wall are finished (seen as as wall)
 * and which are unfinished (seen as rock).
 *
 * We use the bottom 3 bits of the flags field for the mode.  This comes
 * in conflict with secret doors, but we avoid problems because until
 * a secret door becomes discovered, we know what sdoor's bottom three
 * bits are.
 *
 * The following should cover all of the cases.
 *
 *	type	mode				Examples: R=rock, F=finished
 *	-----	----				----------------------------
 *	WALL:	0 none				hwall, mode 1
 *		1 left/top (1/2 rock)			RRR
 *		2 right/bottom (1/2 rock)		---
 *							FFF
 *
 *	CORNER: 0 none				trcorn, mode 2
 *		1 outer (3/4 rock)			FFF
 *		2 inner (1/4 rock)			F+-
 *							F|R
 *
 *	TWALL:	0 none				tlwall, mode 3
 *		1 long edge (1/2 rock)			F|F
 *		2 bottom left (on a tdwall)		-+F
 *		3 bottom right (on a tdwall)		R|F
 *
 *	CRWALL: 0 none				crwall, mode 5
 *		1 top left (1/4 rock)			R|F
 *		2 top right (1/4 rock)			-+-
 *		3 bottom left (1/4 rock)		F|R
 *		4 bottom right (1/4 rock)
 *		5 top left & bottom right (1/2 rock)
 *		6 bottom left & top right (1/2 rock)
 */

#define WM_W_LEFT 1			/* vertical or horizontal wall */
#define WM_W_RIGHT 2
#define WM_W_TOP WM_W_LEFT
#define WM_W_BOTTOM WM_W_RIGHT

#define WM_C_OUTER 1			/* corner wall */
#define WM_C_INNER 2

#define WM_T_LONG 1			/* T wall */
#define WM_T_BL   2
#define WM_T_BR   3

#define WM_X_TL   1			/* cross wall */
#define WM_X_TR   2
#define WM_X_BL   3
#define WM_X_BR   4
#define WM_X_TLBR 5
#define WM_X_BLTR 6

/*
 * Seen vector values.	The seen vector is an array of 8 bits, one for each
 * octant around a given center x:
 *
 *			0 1 2
 *			7 x 3
 *			6 5 4
 *
 * In the case of walls, a single wall square can be viewed from 8 possible
 * directions.	If we know the type of wall and the directions from which
 * it has been seen, then we can determine what it looks like to the hero.
 */
#define SV0 0x1
#define SV1 0x2
#define SV2 0x4
#define SV3 0x8
#define SV4 0x10
#define SV5 0x20
#define SV6 0x40
#define SV7 0x80
#define SVALL 0xFF



#define doormask	flags
#define altarmask	flags
#define wall_info	flags
#define ladder		flags
#define drawbridgemask	flags
#define looted		flags
#define icedpool	flags

#define blessedftn	horizontal  /* a fountain that grants attribs */
#define disturbed	horizontal  /* a grave that has been disturbed */

struct damage {
	struct damage *next;
	long when, cost;
	coord place;
	schar typ;
};

struct levelflags {
	uchar	nfountains;		/* number of fountains on level */
	uchar	nsinks;			/* number of sinks on the level */
	/* Several flags that give hints about what's on the level */
	unsigned has_shop:1;
	unsigned has_vault:1;
	unsigned has_zoo:1;
	unsigned has_court:1;
	unsigned has_morgue:1;
	unsigned has_beehive:1;
	unsigned has_barracks:1;
	unsigned has_temple:1;

	unsigned has_swamp:1;
	unsigned noteleport:1;
	unsigned hardfloor:1;
	unsigned nommap:1;
	unsigned hero_memory:1;		/* hero has memory */
	unsigned shortsighted:1;	/* monsters are shortsighted */
	unsigned graveyard:1;		/* has_morgue, but remains set */
	unsigned is_maze_lev:1;

	unsigned is_cavernous_lev:1;
	unsigned arboreal:1;		/* Trees replace rock */
	
	unsigned forgotten:1;	/* previously visited but forgotten (amnesia) */
};

/* worm segment structure */
struct wseg {
    struct wseg *nseg;
    xchar  wx, wy;	/* the segment's position */
};


struct ls_t;
struct level {
    char		levname[64]; /* as given by the player via donamelevel */
    struct rm		locations[COLNO][ROWNO];
    struct obj		*objects[COLNO][ROWNO];
    struct monst	*monsters[COLNO][ROWNO];
    struct obj		*objlist;
    struct obj		*buriedobjlist;
    struct obj		*billobjs; /* objects not yet paid for */
    struct monst	*monlist;
    struct damage	*damagelist;
    struct levelflags	flags;
    
    timer_element	*lev_timers;
    struct ls_t		*lev_lights;
    struct trap 	*lev_traps;
    struct engr		*lev_engr;
    struct region 	**regions;

    coord 		doors[DOORMAX];
    struct mkroom	rooms[(MAXNROFROOMS+1)*2];
    struct mkroom	*subrooms;
    struct mkroom	*upstairs_room, *dnstairs_room, *sstairs_room;
    stairway		upstair, dnstair;
    stairway		upladder, dnladder;
    stairway		sstairs;
    dest_area		updest;
    dest_area		dndest;

    struct wseg 	*wheads[MAX_NUM_WORMS], *wtails[MAX_NUM_WORMS];
    int			wgrowtime[MAX_NUM_WORMS];
    int			lastmoves; /* when the level was last visited */
    int 		nroom;
    int			nsubroom;
    int			doorindex;
    int			n_regions;
    int			max_regions;

    d_level		z;
};

extern struct level *levels[MAXLINFO]; /* structure describing all levels */
extern struct level *level;		/* pointer to an entry in levels */


#define OBJ_AT(x,y)	(level->objects[x][y] != NULL)
#define OBJ_AT_LEV(lev, x,y)	((lev)->objects[x][y] != NULL)

/*
 * Macros for encapsulation of level->monsters references.
 */
#define MON_AT(lev,x,y)	((lev)->monsters[x][y] != NULL && \
			 !(lev)->monsters[x][y]->mburied)
#define MON_BURIED_AT(x,y)	(level->monsters[x][y] != NULL && \
				level->monsters[x][y]->mburied)
#define place_worm_seg(m,x,y)	(m)->dlevel->monsters[x][y] = m
#define remove_monster(x,y)	level->monsters[x][y] = NULL
#define m_at(lev,x,y)		(MON_AT(lev,x,y) ? (lev)->monsters[x][y] : \
						NULL)
#define m_buried_at(x,y)	(MON_BURIED_AT(x,y) ? level->monsters[x][y] : \
						       NULL)

#endif /* RM_H */