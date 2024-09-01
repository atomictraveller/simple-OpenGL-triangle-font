#pragma once

	float fontx[42][24];				//	x and y for tri strips
	float fonty[42][24];
	char fpoints[42] = {				//	number of points in strip
		18, 7, 20, 24, 10, 20, 22, 7, 21, 22,		//	0 - 9     22, 8, 18, 22
		22, 16, 16, 16, 20, 14, 22, 12, 8, 14,		//	a - j
		12, 4, 24, 12, 18, 16, 16, 10, 24, 14,		//	k - t
		12, 8, 8, 16, 10, 8, 19, 4, 4, 6, 6, 0 };	//	u - z, top half of '8', period, dash, left, right (only declared to 41)
	bool fstrips[42] = {	//	1 = character is two strips not one
		0, 0, 0, 1, 1, 0, 0, 0, 1, 0,
		0, 0, 0, 0, 0, 1, 0, 1, 1, 1,
		1, 0, 1, 0, 0, 0, 0, 0, 0, 1,
		0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0 };	//	2nd half of 8 tagged but not
	char fstripindex[42] = {	//	index of second strip beginning
		0, 0, 0, 12, 4, 0, 0, 0, 18, 0,
		0, 0, 0, 0, 0, 10, 0, 4, 4, 4,
		4, 0, 12, 0, 0, 0, 0, 0, 0, 4,
		0, 4, 4, 8, 6, 0, 16, 0, 0, 0, 0, 0 };

	float finc[42];			//	x increment per character
	float fscale = 1.f;		//	for changing font size
	float fspacing;			//	spacing :)
	float fxdim, fydim;		//	width and height of character in scene units
	float frise;
	float fdrop;			//	descending and ascending
	float xwidth, ywidth;	//	thickness of stroke
	float xangle, yangle;	//	corner cut/'rounding' in units
	float crossy;			//	0-1 y position of crossbars
	unsigned char glyph[256];
	int glyphindex[256];
	unsigned char glyphs = 0;


void makefont() {

	fscale = 0.2f;
	fspacing = 0.2f;
	fxdim = 2.0f;		fydim = 1.2f;									//	character dimensions in scene units (all except crossy)
	frise = 0.5f;		fdrop = -0.4f;									//	descending (-) and ascending (+)
	xwidth = 0.34f;		xwidth = min(fxdim * 0.4f, xwidth);				//	stroke thickness
	ywidth = 0.24f;		ywidth = min(fydim * 0.28f, ywidth);//24
	xangle = 0.32f;		xangle = min(fxdim * 0.4f, xangle);				//	corner cut/rounding
	crossy = 0.6f;														//	y position of crossbars as 0.0 (bottom) to 1.0 (top) so .3-.7
	crossy = max(ywidth * 1.6f, min(fydim - ywidth * 1.6f, crossy));
	yangle = 0.22f;		//yangle = min(yangle, fydim * min(crossy, 1.f - crossy) * 0.8f);
	yangle = min(yangle, fydim * min(crossy, 1.f - crossy) * 0.8f);


	//	internal beariables
	float insideratio = (fxdim - xwidth - xwidth) / fxdim;
	float xinside = xangle * insideratio;				//	for inside corner cuts
	float yinside = yangle * insideratio;
	float xc0 = (fxdim - xwidth) * 0.5f;				//	left and right of middle stroke (eg. y center)
	float xc1 = (fxdim + xwidth) * 0.5f;
	float yc0 = (fydim * crossy) - ywidth * 0.5f;		//	bottom and top of crossbar (eg. "a", "e", "s")
	float yc1 = (fydim * crossy) + ywidth * 0.5f;
	float x1 = xangle;	float x2 = xwidth;	float x3 = xwidth + xinside;	//	these cover most of the points
	float y1 = yangle;	float y2 = ywidth;	float y3 = ywidth + yinside;
	float x4 = fxdim - x3;	float x5 = fxdim - xwidth;	float x6 = fxdim - xangle;
	float y4 = fydim - y3;	float y5 = fydim - ywidth;	float y6 = fydim - yangle;

	//	begin making characters
	float slope, slope2, t0;	//	variables for figuring out stuff
/*
fontx[][0] = ;	fonty[][0] = ;
fontx[][1] = ;	fonty[][1] = ;
fontx[][2] = ;	fonty[][2] = ;
fontx[][3] = ;	fonty[][3] = ;
fontx[][4] = ;	fonty[][4] = ;
fontx[][5] = ;	fonty[][5] = ;
fontx[][6] = ;	fonty[][6] = ;
fontx[][7] = ;	fonty[][7] = ;
fontx[][8] = ;	fonty[][8] = ;
fontx[][9] = ;	fonty[][9] = ;
fontx[][10] = ;	fonty[][10] = ;
fontx[][11] = ;	fonty[][11] = ;
fontx[][12] = ;	fonty[][12] = ;
fontx[][13] = ;	fonty[][13] = ;
fontx[][14] = ;	fonty[][14] = ;
fontx[][15] = ;	fonty[][15] = ;
fontx[][16] = ;	fonty[][16] = ;
fontx[][17] = ;	fonty[][17] = ;
fontx[][18] = ;	fonty[][18] = ;
fontx[][19] = ;	fonty[][19] = ;
fontx[][20] = ;	fonty[][20] = ;
fontx[][21] = ;	fonty[][21] = ;
fontx[][22] = ;	fonty[][22] = ;
fontx[][23] = ;	fonty[][23] = ;
fontx[][24] = ;	fonty[][24] = ;
fontx[][25] = ;	fonty[][25] = ;
*/
	t0 = y2 + (fydim - y2) * 0.5f;	//	y of point .. halfway between fydim and y2
	slope = (t0 - fydim) / (x5 - xangle);	slope = ywidth / slope;
	fontx[40][0] = fxdim - xangle - slope;	fonty[40][0] = fydim;	//	right arrow
	fontx[40][1] = x5 - xangle;		fonty[40][1] = fydim;
	fontx[40][2] = x2 - slope;		fonty[40][2] = t0;
	fontx[40][3] = 0.f;	fonty[40][3] = t0;
	fontx[40][4] = fxdim - xangle - slope;	fonty[40][4] = y2;
	fontx[40][5] = x5 - xangle;		fonty[40][5] = y2;

	fontx[39][0] = x2 + xangle;		fonty[39][0] = fydim;	//	left arrow
	fontx[39][1] = 0.f + xangle + slope;	fonty[39][1] = fydim;
	fontx[39][2] = fxdim;	fonty[39][2] = t0;
	fontx[39][3] = x5 + slope;		fonty[39][3] = t0;
	fontx[39][4] = x2 + xangle;		fonty[39][4] = y2;
	fontx[39][5] = 0.f + xangle + slope;	fonty[39][5] = y2;

	fontx[38][0] = 0.f + xinside;	fonty[38][0] = yc1;	//	dash
	fontx[38][1] = 0.f + xinside;	fonty[38][1] = yc0;
	fontx[38][2] = fxdim - xinside;	fonty[38][2] = yc1;
	fontx[38][3] = fxdim - xinside;	fonty[38][3] = yc0;

	fontx[37][0] = 0.f;		fonty[37][0] = y2;	//	period
	fontx[37][1] = 0.f;		fonty[37][1] = 0.f;
	fontx[37][2] = x2;		fonty[37][2] = y2;
	fontx[37][3] = x2;		fonty[37][3] = 0.f;

	slope = fydim / (fxdim - x2);	t0 = (fxdim - x2) * slope;
	fontx[35][0] = 0.f;	fonty[35][0] = fydim;	//	z - top to bottom
	fontx[35][1] = 0.f;	fonty[35][1] = y5;
	fontx[35][2] = fxdim;	fonty[35][2] = fydim;
	fontx[35][3] = fxdim - x2 - ywidth / slope;	fonty[35][3] = y5;
	fontx[35][4] = x2 + ywidth / slope;	fonty[35][4] = y2;
	fontx[35][5] = 0.f;	fonty[35][5] = 0.f;
	fontx[35][6] = fxdim;	fonty[35][6] = y2;
	fontx[35][7] = fxdim;	fonty[35][7] = 0.f;

	slope = fydim / (fxdim - x2);	t0 = (x5 - fxdim * 0.5f) * slope;
	fontx[33][0] = x2;		fonty[33][0] = fydim;	//	x - two strips of 12 vertices, middle quad has redundnt vertice :p = easy to do
	fontx[33][1] = 0.f;		fonty[33][1] = fydim;	//	top half left to right
	fontx[33][2] = fxdim * 0.5f;	fonty[33][2] = fydim - t0;
	fontx[33][3] = x5 * 0.5f;		fonty[33][3] = fydim  * 0.5f;
	fontx[33][4] = fxdim * 0.5f;	fonty[33][4] = fydim - t0;
	fontx[33][5] = fxdim - x5 * 0.5f;	fonty[33][5] = fydim * 0.5f;
	fontx[33][6] = x5;		fonty[33][6] = fydim;
	fontx[33][7] = fxdim;	fonty[33][7] = fydim;
	fontx[33][8] = 0.f;		fonty[33][8] = 0.f;		//	bottom half l-r
	fontx[33][9] = x2;		fonty[33][9] = 0.f;
	fontx[33][10] = x5 * 0.5f;			fonty[33][10] = fydim * 0.5f;
	fontx[33][11] = fxdim * 0.5f;		fonty[33][11] = t0;
	fontx[33][12] = fxdim - x5 * 0.5f;	fonty[33][12] = fydim * 0.5f;
	fontx[33][13] = fxdim * 0.5f;		fonty[33][13] = t0;
	fontx[33][14] = fxdim;	fonty[33][14] = 0.f;
	fontx[33][15] = x5;		fonty[33][15] = 0.f;

	fontx[31][0] = x2;		fonty[31][0] = fydim;	//	v - left, right
	fontx[31][1] = 0.f;		fonty[31][1] = fydim;
	fontx[31][2] = xc1;		fonty[31][2] = 0.f;
	fontx[31][3] = xc0;		fonty[31][3] = 0.f;
	fontx[31][4] = fxdim;	fonty[31][4] = fydim;
	fontx[31][5] = x5;		fonty[31][5] = fydim;
	fontx[31][6] = xc1;		fonty[31][6] = 0.f;
	slope2 = fxdim * 0.5f;
	slope = fydim / (fxdim - xc1);		t0 = (x5 - slope2) * slope;
	fontx[31][7] = slope2;	fonty[31][7] = fydim - t0;

	for (int i = 0; i < 8; i++) {
		fontx[32][i] = fontx[31][i] - fspacing - xwidth;	fonty[32][i] = fonty[31][i];	//	w - uses v as first half		
	}
	fontx[32][1] = xwidth * 0.5f - fspacing - xwidth;	fonty[32][1] = fydim - (xwidth * 0.5f) * slope;

	for (int i = 0; i < 4; i++) {
		fontx[34][i] = fontx[31][i];	fonty[34][i] = fonty[31][i];	//	y - also y derived
		fontx[34][i + 6] = fontx[31][i + 4];	fonty[34][i + 6] = fonty[31][i + 4];	//	y - also y derived
	}
	fontx[34][4] = xc1 + fdrop / slope;	fonty[34][4] = fdrop;	//	y tail
	fontx[34][5] = xc0 + fdrop / slope;	fonty[34][5] = fdrop;

	fontx[30][0] = x2;		fonty[30][0] = fydim;	//	u - left to right
	fontx[30][1] = 0.f;		fonty[30][1] = fydim;
	fontx[30][2] = x2;		fonty[30][2] = y3;
	fontx[30][3] = 0.f;		fonty[30][3] = y1;
	fontx[30][4] = x3;		fonty[30][4] = y2;
	fontx[30][5] = x1;		fonty[30][5] = 0.f;
	fontx[30][6] = x4;		fonty[30][6] = y2;
	fontx[30][7] = x6;		fonty[30][7] = 0.f;
	fontx[30][8] = x5;		fonty[30][8] = y3;
	fontx[30][9] = fxdim;	fonty[30][9] = y1;
	fontx[30][10] = x5;		fonty[30][10] = fydim;
	fontx[30][11] = fxdim;	fonty[30][11] = fydim;

	fontx[29][0] = x5;		fonty[29][0] = fydim;	//	t - top down
	fontx[29][1] = x2;		fonty[29][1] = fydim;
	fontx[29][2] = x5;		fonty[29][2] = y5;
	fontx[29][3] = x2;		fonty[29][3] = y5;
	fontx[29][4] = x2;		fonty[29][4] = fydim + frise;	//
	fontx[29][5] = 0.f;		fonty[29][5] = fydim + frise;
	fontx[29][6] = x2;		fonty[29][6] = y3;
	fontx[29][7] = 0.f;		fonty[29][7] = y1;
	fontx[29][8] = x3;		fonty[29][8] = y2;
	fontx[29][9] = x1;		fonty[29][9] = 0.f;
	fontx[29][10] = x4;		fonty[29][10] = y2;
	fontx[29][11] = x6;		fonty[29][11] = 0.f;
	fontx[29][12] = x5;		fonty[29][12] = y3;
	fontx[29][13] = fxdim;	fonty[29][13] = y1;

	fontx[28][0] = x2;		fonty[28][0] = y3;	//	s - bottom to top
	fontx[28][1] = 0.f;		fonty[28][1] = y1;
	fontx[28][2] = x3;		fonty[28][2] = y2;
	fontx[28][3] = x1;		fonty[28][3] = 0.f;
	fontx[28][4] = x4;		fonty[28][4] = y2;
	fontx[28][5] = x6;		fonty[28][5] = 0.f;
	fontx[28][6] = x5;		fonty[28][6] = y3;
	fontx[28][7] = fxdim;	fonty[28][7] = y1;
	fontx[28][8] = x5;		fonty[28][8] = yc0 - yinside - yinside;
	fontx[28][9] = fxdim;	fonty[28][9] = yc1 - yangle - yinside;
	fontx[28][10] = x4;		fonty[28][10] = yc0 - yinside;
	fontx[28][11] = x6;		fonty[28][11] = yc1 - yinside;
	fontx[28][12] = x1;		fonty[28][12] = yc0;
	fontx[28][13] = x3;		fonty[28][13] = yc1;
	fontx[28][14] = 0.f;	fonty[28][14] = yc0 + yangle;
	fontx[28][15] = x2;		fonty[28][15] = yc1 + yinside;
	fontx[28][16] = 0.f;	fonty[28][16] = y6;
	fontx[28][17] = x2;		fonty[28][17] = y4;
	fontx[28][18] = x1;		fonty[28][18] = fydim;
	fontx[28][19] = x3;		fonty[28][19] = y5;
	fontx[28][20] = x6;		fonty[28][20] = fydim;
	fontx[28][21] = x4;		fonty[28][21] = y5;
	fontx[28][22] = fxdim;	fonty[28][22] = y6;
	fontx[28][23] = x5;		fonty[28][23] = y4;

	fontx[27][0] = 0.f;		fonty[27][0] = 0.f;	//	r - bottom up
	fontx[27][1] = x2;		fonty[27][1] = 0.f;
	fontx[27][2] = 0.f;		fonty[27][2] = y6;
	fontx[27][3] = x2;		fonty[27][3] = y4;
	fontx[27][4] = x1;		fonty[27][4] = fydim;
	fontx[27][5] = x3;		fonty[27][5] = y5;
	fontx[27][6] = x6;		fonty[27][6] = fydim;
	fontx[27][7] = x4;		fonty[27][7] = y5;
	fontx[27][8] = fxdim;	fonty[27][8] = y6;
	fontx[27][9] = x5;		fonty[27][9] = y4;

	fontx[26][0] = x5;		fonty[26][0] = 0.f;	//	q - clockwise ending at tail
	fontx[26][1] = x5;		fonty[26][1] = y2;
	fontx[26][2] = x1;		fonty[26][2] = 0.f;
	fontx[26][3] = x3;		fonty[26][3] = y2;
	fontx[26][4] = 0.f;		fonty[26][4] = y1;
	fontx[26][5] = x2;		fonty[26][5] = y3;
	fontx[26][6] = 0.f;		fonty[26][6] = y6;
	fontx[26][7] = x2;		fonty[26][7] = y4;
	fontx[26][8] = x1;		fonty[26][8] = fydim;
	fontx[26][9] = x3;		fonty[26][9] = y5;
	fontx[26][10] = x6;		fonty[26][10] = fydim;
	fontx[26][11] = x4;		fonty[26][11] = y5;
	fontx[26][12] = fxdim;	fonty[26][12] = y6;
	fontx[26][13] = x5;		fonty[26][13] = y4;
	fontx[26][14] = fxdim;	fonty[26][14] = fdrop;
	fontx[26][15] = x5;		fonty[26][15] = fdrop;

	fontx[25][0] = 0.f;		fonty[25][0] = fdrop;	//	p - bottom clockwise
	fontx[25][1] = x2;		fonty[25][1] = fdrop;
	fontx[25][2] = 0.f;		fonty[25][2] = y6;
	fontx[25][3] = x2;		fonty[25][3] = y4;
	fontx[25][4] = x1;		fonty[25][4] = fydim;
	fontx[25][5] = x3;		fonty[25][5] = y5;
	fontx[25][6] = x6;		fonty[25][6] = fydim;
	fontx[25][7] = x4;		fonty[25][7] = y5;
	fontx[25][8] = fxdim;	fonty[25][8] = y6;
	fontx[25][9] = x5;		fonty[25][9] = y4;
	fontx[25][10] = fxdim;	fonty[25][10] = y1;
	fontx[25][11] = x5;		fonty[25][11] = y3;
	fontx[25][12] = x6;		fonty[25][12] = 0.f;
	fontx[25][13] = x4;		fonty[25][13] = y2;
	fontx[25][14] = x2;		fonty[25][14] = 0.f;
	fontx[25][15] = x2;		fonty[25][15] = y2;

	fontx[24][0] = 0.f;		fonty[24][0] = y6;		//	o - top left proceeding clockwise
	fontx[24][1] = x2;		fonty[24][1] = y4;
	fontx[24][2] = x1;		fonty[24][2] = fydim;
	fontx[24][3] = x3;		fonty[24][3] = y5;
	fontx[24][4] = x6;		fonty[24][4] = fydim;
	fontx[24][5] = x4;		fonty[24][5] = y5;
	fontx[24][6] = fxdim;	fonty[24][6] = y6;
	fontx[24][7] = x5;		fonty[24][7] = y4;
	fontx[24][8] = fxdim;	fonty[24][8] = y1;
	fontx[24][9] = x5;		fonty[24][9] = y3;
	fontx[24][10] = x6;		fonty[24][10] = 0.f;
	fontx[24][11] = x4;		fonty[24][11] = y2;
	fontx[24][12] = x1;		fonty[24][12] = 0.f;
	fontx[24][13] = x3;		fonty[24][13] = y2;
	fontx[24][14] = 0.f;	fonty[24][14] = y1;
	fontx[24][15] = x2;		fonty[24][15] = y3;
	fontx[24][16] = 0.f;	fonty[24][16] = y6;
	fontx[24][17] = x2;		fonty[24][17] = y4;

	fontx[23][0] = 0.f;		fonty[23][0] = 0.f;	//	n - bottom left clockwise
	fontx[23][1] = x2;		fonty[23][1] = 0.f;
	fontx[23][2] = 0.f;		fonty[23][2] = y6;
	fontx[23][3] = x2;		fonty[23][3] = y4;
	fontx[23][4] = x1;		fonty[23][4] = fydim;
	fontx[23][5] = x3;		fonty[23][5] = y5;
	fontx[23][6] = x6;		fonty[23][6] = fydim;
	fontx[23][7] = x4;		fonty[23][7] = y5;
	fontx[23][8] = fxdim;	fonty[23][8] = y6;
	fontx[23][9] = x5;		fonty[23][9] = y4;
	fontx[23][10] = fxdim;	fonty[23][10] = 0.f;
	fontx[23][11] = x5;		fonty[23][11] = 0.f;

	fontx[22][0] = 0.f;		fonty[22][0] = 0.f;	//	m - bottom left clockwise
	fontx[22][1] = x2;		fonty[22][1] = 0.f;	//	two arches, middle is dividec in center
	fontx[22][2] = 0.f;		fonty[22][2] = y6;
	fontx[22][3] = x2;		fonty[22][3] = y4;
	fontx[22][4] = x1;		fonty[22][4] = fydim;
	fontx[22][5] = x3;		fonty[22][5] = y5;
	fontx[22][6] = x6;		fonty[22][6] = fydim;
	fontx[22][7] = x4;		fonty[22][7] = y5;
	slope2 = fxdim - xwidth * 0.5f;	//	x middle of the middle
	t0 = fydim - yangle * (fxdim - slope2) / xangle;	//	y coordinate
	fontx[22][8] = slope2;	fonty[22][8] = t0;
	fontx[22][9] = x5;		fonty[22][9] = y4;
	fontx[22][10] = slope2;	fonty[22][10] = 0.f;
	fontx[22][11] = x5;		fonty[22][11] = 0.f;
	fontx[22][12] = slope2;	fonty[22][12] = 0.f;	//	2nd arch
	fontx[22][13] = fxdim;	fonty[22][13] = 0.f;
	fontx[22][14] = slope2;	fonty[22][14] = t0;
	fontx[22][15] = fxdim;	fonty[22][15] = y4;
	fontx[22][16] = x5 + x1;	fonty[22][16] = fydim;
	fontx[22][17] = x5 + x3;	fonty[22][17] = y5;
	fontx[22][18] = x5 + x6;	fonty[22][18] = fydim;
	fontx[22][19] = x5 + x4;	fonty[22][19] = y5;
	fontx[22][20] = x5 + fxdim;	fonty[22][20] = y6;
	fontx[22][21] = x5 + x5;	fonty[22][21] = y4;
	fontx[22][22] = x5 + fxdim;	fonty[22][22] = 0.f;
	fontx[22][23] = x5 + x5;	fonty[22][23] = 0.f;

	fontx[21][0] = 0.f;		fonty[21][0] = fydim + frise;	//	L 
	fontx[21][1] = 0.f;		fonty[21][1] = 0.f;
	fontx[21][2] = x2;		fonty[21][2] = fydim + frise;
	fontx[21][3] = x2;		fonty[21][3] = 0.f;

	fontx[20][0] = 0.f;		fonty[20][0] = fydim + frise;	//	k 
	fontx[20][1] = 0.f;		fonty[20][1] = 0.f;
	fontx[20][2] = x2;		fonty[20][2] = fydim + frise;
	fontx[20][3] = x2;		fonty[20][3] = 0.f;
	fontx[20][4] = fxdim;	fonty[20][4] = fydim;		//	top down
	fontx[20][5] = x5;		fonty[20][5] = fydim;
	slope2 = min(x4, x2 + xwidth * 0.99f);	//	temporarily used as max width
	fontx[20][6] = slope2;		fonty[20][6] = fydim * crossy;
	slope = ((fydim * crossy) - fydim) / (fxdim - slope2);		t0 = (x5 - x2) * slope;
	fontx[20][7] = x2;		fonty[20][7] = fydim + t0;
	fontx[20][8] = slope2;		fonty[20][8] = fydim * crossy;
	slope = (fydim * crossy) / (fxdim - slope2);		t0 = (x5 - x2) * slope;
	fontx[20][9] = x2;		fonty[20][9] = t0;
	fontx[20][10] = fxdim;	fonty[20][10] = 0.f;
	fontx[20][11] = x5;		fonty[20][11] = 0.f;

	fontx[19][0] = fxdim - fspacing;	fonty[19][0] = fydim + frise;	//	j - top down
	fontx[19][1] = x5 - fspacing;		fonty[19][1] = fydim + frise;
	fontx[19][2] = fxdim - fspacing;	fonty[19][2] = fydim + frise - ywidth;
	fontx[19][3] = x5 - fspacing;		fonty[19][3] = fydim + frise - ywidth;
	fontx[19][4] = fxdim - fspacing;	fonty[19][4] = fydim;
	fontx[19][5] = x5 - fspacing;		fonty[19][5] = fydim;
	fontx[19][6] = fxdim - fspacing;	fonty[19][6] = fdrop + yangle;
	fontx[19][7] = x5 - fspacing;		fonty[19][7] = fdrop + ywidth + yinside;
	fontx[19][8] = x6 - fspacing;		fonty[19][8] = fdrop;
	fontx[19][9] = x4 - fspacing;		fonty[19][9] = fdrop + ywidth;
	fontx[19][10] = x1 - fspacing;		fonty[19][10] = fdrop;
	fontx[19][11] = x3 - fspacing;		fonty[19][11] = fdrop + ywidth;
	fontx[19][12] = 0.f - fspacing;		fonty[19][12] = fdrop + yangle;
	fontx[19][13] = x2 - fspacing;		fonty[19][13] = fdrop + ywidth + yinside;

	fontx[18][0] = 0.f;	fonty[18][0] = fydim;	//	i
	fontx[18][1] = 0.f;	fonty[18][1] = 0.f;
	fontx[18][2] = x2;	fonty[18][2] = fydim;
	fontx[18][3] = x2;	fonty[18][3] = 0.f;
	fontx[18][4] = 0.f;	fonty[18][4] = fydim + frise;
	fontx[18][5] = 0.f;	fonty[18][5] = fydim + frise - ywidth;
	fontx[18][6] = x2;	fonty[18][6] = fydim + frise;
	fontx[18][7] = x2;	fonty[18][7] = fydim + frise - ywidth;

	fontx[17][0] = 0.f;		fonty[17][0] = fydim + frise;	//	h
	fontx[17][1] = 0.f;		fonty[17][1] = 0.f;
	fontx[17][2] = x2;		fonty[17][2] = fydim + frise;
	fontx[17][3] = x2;		fonty[17][3] = 0.f;
	fontx[17][4] = x2;		fonty[17][4] = fydim;	//	
	fontx[17][5] = x2;		fonty[17][5] = y5;
	fontx[17][6] = x6;		fonty[17][6] = fydim;
	fontx[17][7] = x4;		fonty[17][7] = y5;
	fontx[17][8] = fxdim;	fonty[17][8] = y6;
	fontx[17][9] = x5;		fonty[17][9] = y4;
	fontx[17][10] = fxdim;	fonty[17][10] = 0.f;
	fontx[17][11] = x5;		fonty[17][11] = 0.f;

	fontx[16][0] = x5;		fonty[16][0] = 0.f;	//	g - clockwise around to bottom
	fontx[16][1] = x5;		fonty[16][1] = y2;
	fontx[16][2] = x1;		fonty[16][2] = 0.f;
	fontx[16][3] = x3;		fonty[16][3] = y2;
	fontx[16][4] = 0.f;		fonty[16][4] = y1;
	fontx[16][5] = x2;		fonty[16][5] = y3;
	fontx[16][6] = 0.f;		fonty[16][6] = y6;
	fontx[16][7] = x2;		fonty[16][7] = y4;
	fontx[16][8] = x1;		fonty[16][8] = fydim;
	fontx[16][9] = x3;		fonty[16][9] = y5;
	fontx[16][10] = x6;		fonty[16][10] = fydim;
	fontx[16][11] = x4;		fonty[16][11] = y5;
	fontx[16][12] = fxdim;	fonty[16][12] = y6;
	fontx[16][13] = x5;		fonty[16][13] = y4;
	fontx[16][14] = fxdim;	fonty[16][14] =  fdrop + yangle;
	fontx[16][15] = x5;		fonty[16][15] = fdrop + ywidth + yinside;
	fontx[16][16] = x6;		fonty[16][16] = fdrop;
	fontx[16][17] = x4;		fonty[16][17] = fdrop + ywidth;
	fontx[16][18] = x1;		fonty[16][18] = fdrop;
	fontx[16][19] = x3;		fonty[16][19] = fdrop + ywidth;
	fontx[16][20] = 0.f;	fonty[16][20] = fdrop + yangle;
	fontx[16][21] = x2;		fonty[16][21] = fdrop + ywidth + yinside;

	fontx[15][0] = 0.f;		fonty[15][0] = 0.f;	//	f - bottom to top, then cross
	fontx[15][1] = x2;		fonty[15][1] = 0.f;
	fontx[15][2] = 0.f;		fonty[15][2] = fydim + frise - yangle;
	fontx[15][3] = x2;		fonty[15][3] = fydim + frise - ywidth - yinside;
	fontx[15][4] = x1;		fonty[15][4] = fydim + frise;
	fontx[15][5] = x3;		fonty[15][5] = fydim + frise - ywidth;
	fontx[15][6] = x6;		fonty[15][6] = fydim + frise;
	fontx[15][7] = x4;		fonty[15][7] = fydim + frise - ywidth;
	fontx[15][8] = fxdim;	fonty[15][8] = fydim + frise - yangle;
	fontx[15][9] = x5;		fonty[15][9] = fydim + frise - ywidth - yinside;
	fontx[15][10] = x2;		fonty[15][10] = fydim;
	fontx[15][11] = x2;		fonty[15][11] = y5;
	fontx[15][12] = x5;		fonty[15][12] = fydim;
	fontx[15][13] = x5;		fonty[15][13] = y5;

	fontx[14][0] = fxdim;	fonty[14][0] = y1;	//	e - clockwise	
	fontx[14][1] = x5;		fonty[14][1] = y3;
	fontx[14][2] = x6;		fonty[14][2] = 0.f;
	fontx[14][3] = x4;		fonty[14][3] = y2;
	fontx[14][4] = x1;		fonty[14][4] = 0.f;
	fontx[14][5] = x3;		fonty[14][5] = y2;
	fontx[14][6] = 0.f;		fonty[14][6] = y1;
	fontx[14][7] = x2;		fonty[14][7] = y3;
	fontx[14][8] = 0.f;		fonty[14][8] = y6;
	fontx[14][9] = x2;		fonty[14][9] = y4;
	fontx[14][10] = x1;		fonty[14][10] = fydim;
	fontx[14][11] = x3;		fonty[14][11] = y5;
	fontx[14][12] = x6;		fonty[14][12] = fydim;
	fontx[14][13] = x4;		fonty[14][13] = y5;
	fontx[14][14] = fxdim;	fonty[14][14] = y6;
	fontx[14][15] = x5;		fonty[14][15] = y4;
	fontx[14][16] = fxdim;	fonty[14][16] = yc0;
	fontx[14][17] = x5;		fonty[14][17] = yc1;
	fontx[14][18] = x2;		fonty[14][18] = yc0;
	fontx[14][19] = x2;		fonty[14][19] = yc1;

	fontx[13][0] = fxdim;	fonty[13][0] = fydim + frise;	//	d - from top, clockwise
	fontx[13][1] = x5;	fonty[13][1] = fydim + frise;
	fontx[13][2] = fxdim;	fonty[13][2] = y1;
	fontx[13][3] = x5;	fonty[13][3] = y3;
	fontx[13][4] = x6;	fonty[13][4] = 0.f;
	fontx[13][5] = x4;	fonty[13][5] = y2;
	fontx[13][6] = x1;	fonty[13][6] = 0.f;
	fontx[13][7] = x3;	fonty[13][7] = y2;
	fontx[13][8] = 0.f;	fonty[13][8] = y1;
	fontx[13][9] = x2;	fonty[13][9] = y3;
	fontx[13][10] = 0.f;	fonty[13][10] = y6;
	fontx[13][11] = x2;	fonty[13][11] = y4;
	fontx[13][12] = x1;	fonty[13][12] = fydim;
	fontx[13][13] = x3;	fonty[13][13] = y5;
	fontx[13][14] = x5;	fonty[13][14] = fydim;
	fontx[13][15] = x5;	fonty[13][15] = y5;

	fontx[12][0] = fxdim;	fonty[12][0] = y1;	//	c - clockwise	
	fontx[12][1] = x5;		fonty[12][1] = y3;
	fontx[12][2] = x6;		fonty[12][2] = 0.f;
	fontx[12][3] = x4;		fonty[12][3] = y2;
	fontx[12][4] = x1;		fonty[12][4] = 0.f;
	fontx[12][5] = x3;		fonty[12][5] = y2;
	fontx[12][6] = 0.f;		fonty[12][6] = y1;
	fontx[12][7] = x2;		fonty[12][7] = y3;
	fontx[12][8] = 0.f;		fonty[12][8] = y6;
	fontx[12][9] = x2;		fonty[12][9] = y4;
	fontx[12][10] = x1;		fonty[12][10] = fydim;
	fontx[12][11] = x3;		fonty[12][11] = y5;
	fontx[12][12] = x6;		fonty[12][12] = fydim;
	fontx[12][13] = x4;		fonty[12][13] = y5;
	fontx[12][14] = fxdim;	fonty[12][14] = y6;
	fontx[12][15] = x5;		fonty[12][15] = y4;

	fontx[11][0] = x2;		fonty[11][0] = fydim;	//	b	inside out clockwise
	fontx[11][1] = x2;		fonty[11][1] = y5;
	fontx[11][2] = x6;		fonty[11][2] = fydim;
	fontx[11][3] = x4;		fonty[11][3] = y5;
	fontx[11][4] = fxdim;	fonty[11][4] = y6;
	fontx[11][5] = x5;		fonty[11][5] = y4;
	fontx[11][6] = fxdim;	fonty[11][6] = y1;
	fontx[11][7] = x5;		fonty[11][7] = y3;
	fontx[11][8] = x6;		fonty[11][8] = 0.f;
	fontx[11][9] = x4;		fonty[11][9] = y2;
	fontx[11][10] = x1;		fonty[11][10] = 0.f;
	fontx[11][11] = x3;		fonty[11][11] = y2;
	fontx[11][12] = 0.f;	fonty[11][12] = y1;
	fontx[11][13] = x2;		fonty[11][13] = y3;
	fontx[11][14] = 0.f;	fonty[11][14] = fydim + frise;
	fontx[11][15] = x2;		fonty[11][15] = fydim + frise;

	fontx[10][0] = 0.f;		fonty[10][0] = y6;	//	a - outside in clockwise
	fontx[10][1] = x2;		fonty[10][1] = y4;
	fontx[10][2] = x1;		fonty[10][2] = fydim;
	fontx[10][3] = x3;		fonty[10][3] = y5;
	fontx[10][4] = x6;		fonty[10][4] = fydim;
	fontx[10][5] = x4;		fonty[10][5] = y5;
	fontx[10][6] = fxdim;	fonty[10][6] = y6;
	fontx[10][7] = x5;		fonty[10][7] = y4;
	fontx[10][8] = fxdim;	fonty[10][8] = y1;
	fontx[10][9] = x5;		fonty[10][9] = y3;
	fontx[10][10] = x6;		fonty[10][10] = 0.f;
	fontx[10][11] = x4;		fonty[10][11] = y2;
	fontx[10][12] = x1;		fonty[10][12] = 0.f;
	fontx[10][13] = x3;		fonty[10][13] = y2;
	fontx[10][14] = 0.f;	fonty[10][14] = y1;
	fontx[10][15] = x2;		fonty[10][15] = y3;
	fontx[10][16] = 0.f;	fonty[10][16] = yc1 - yangle;
	fontx[10][17] = x2;		fonty[10][17] = yc0 - yinside;
	fontx[10][18] = x1;		fonty[10][18] = yc1;
	fontx[10][19] = x3;		fonty[10][19] = yc0;
	fontx[10][20] = x5;		fonty[10][20] = yc1;
	fontx[10][21] = x5;		fonty[10][21] = yc0;

	fontx[9][0] = x5;		fonty[9][0] = yc0;	//	inside out clockwise
	fontx[9][1] = x5;		fonty[9][1] = yc1;
	fontx[9][2] = x1;		fonty[9][2] = yc0;
	fontx[9][3] = x3;		fonty[9][3] = yc1;
	fontx[9][4] = 0.f;		fonty[9][4] = yc0 + yangle;
	fontx[9][5] = x2;		fonty[9][5] = yc1 + yinside;
	fontx[9][6] = 0.f;		fonty[9][6] = fydim + frise - yangle;
	fontx[9][7] = x2;		fonty[9][7] = fydim + frise - ywidth - yinside;
	fontx[9][8] = x1;		fonty[9][8] = fydim + frise;
	fontx[9][9] = x3;		fonty[9][9] = fydim + frise - ywidth;
	fontx[9][10] = x6;		fonty[9][10] = fydim + frise;
	fontx[9][11] = x4;		fonty[9][11] = fydim + frise - ywidth;
	fontx[9][12] = fxdim;	fonty[9][12] = fydim + frise - yangle;
	fontx[9][13] = x5;		fonty[9][13] = fydim + frise - ywidth - yinside;
	fontx[9][14] = fxdim;	fonty[9][14] = y1;
	fontx[9][15] = x5;		fonty[9][15] = y3;
	fontx[9][16] = x6;		fonty[9][16] = 0.f;
	fontx[9][17] = x4;		fonty[9][17] = y2;
	fontx[9][18] = x1;		fonty[9][18] = 0.f;
	fontx[9][19] = x3;		fonty[9][19] = y2;
	fontx[9][20] = 0.f;		fonty[9][20] = y1;
	fontx[9][21] = x2;		fonty[9][21] = y3;

	fontx[36][0] = xangle * 0.5f;	fonty[36][0] = fydim * crossy;	//	upper loop of 8 ('part 2') left to right cw
	fontx[36][1] = x2;		fonty[36][1] = yc1;
	fontx[36][2] = 0.f;		fonty[36][2] = yc0 + yangle;
	fontx[36][3] = x2;		fonty[36][3] = yc1 + yinside;
	fontx[36][4] = 0.f;		fonty[36][4] = fydim + frise - yangle;
	fontx[36][5] = x2;		fonty[36][5] = fydim + frise - ywidth - yinside;
	fontx[36][6] = x1;		fonty[36][6] = fydim + frise;
	fontx[36][7] = x3;		fonty[36][7] = fydim + frise - ywidth;
	fontx[36][8] = x6;		fonty[36][8] = fydim + frise;
	fontx[36][9] = x4;		fonty[36][9] = fydim + frise - ywidth;
	fontx[36][10] = fxdim;	fonty[36][10] = fydim + frise - yangle;
	fontx[36][11] = x5;		fonty[36][11] = fydim + frise - ywidth - yinside;
	fontx[36][12] = fxdim;	fonty[36][12] = yc0 + yangle;
	fontx[36][13] = x5;		fonty[36][13] = yc1 + yinside;
	fontx[36][14] = fxdim - xangle * 0.5f;	fonty[36][14] = fydim * crossy;
	fontx[36][15] = x5;		fonty[36][15] = yc1;
	fontx[36][16] = x4;		fonty[36][16] = yc1;	//	inside lower right triangle
	fontx[36][17] = x5;		fonty[36][17] = yc1;
	fontx[36][18] = x5;		fonty[36][18] = yc1 + yinside;

	for (int i = 0; i < 19; i++) fontx[36][i] -= fxdim + fspacing;

	fontx[8][0] = 0.f;		fonty[8][0] = yc1 - yangle;				//	top left proceeding clockwise 8 part 1 (lower loop)
	fontx[8][1] = x2;		fonty[8][1] = yc0 - yinside;
	fontx[8][2] = x2;		fonty[8][2] = yc1;
	fontx[8][3] = x3;		fonty[8][3] = yc0;
	fontx[8][4] = x5;		fonty[8][4] = yc1;
	fontx[8][5] = x4;		fonty[8][5] = yc0;
	fontx[8][6] = fxdim;	fonty[8][6] = yc1 - yangle;
	fontx[8][7] = x5;		fonty[8][7] = yc0 - yinside;
	fontx[8][8] = fxdim;	fonty[8][8] = y1;
	fontx[8][9] = x5;		fonty[8][9] = y3;
	fontx[8][10] = x6;		fonty[8][10] = 0.f;
	fontx[8][11] = x4;		fonty[8][11] = y2;
	fontx[8][12] = x1;		fonty[8][12] = 0.f;
	fontx[8][13] = x3;		fonty[8][13] = y2;
	fontx[8][14] = 0.f;		fonty[8][14] = y1;
	fontx[8][15] = x2;		fonty[8][15] = y3;
	fontx[8][16] = 0.f;		fonty[8][16] = yc1 - yangle;
	fontx[8][17] = x2;		fonty[8][17] = yc0 - yinside;
	fontx[8][18] = x2;		fonty[8][18] = yc1 + yinside;	//	extra tri (inside lower left of upper loop) 
	fontx[8][19] = x2;		fonty[8][19] = yc1;
	fontx[8][20] = x3;		fonty[8][20] = yc1;

	fontx[7][0] = 0.f;		fonty[7][0] = fydim + frise;	//	top to bottom
	fontx[7][1] = 0.f;		fonty[7][1] = fydim + frise - ywidth;
	fontx[7][2] = fxdim;	fonty[7][2] = fydim + frise;
	fontx[7][3] = x5;		fonty[7][3] = fydim + frise - ywidth;
	fontx[7][4] = fxdim;	fonty[7][4] = fydim + frise - ywidth;
	fontx[7][5] = xc0;		fonty[7][5] = 0.f;
	fontx[7][6] = xc1;		fonty[7][6] = 0.f;

	fontx[6][0] = x2;		fonty[6][0] = yc1;	//	clockwise (center to top)
	fontx[6][1] = x2;		fonty[6][1] = yc0;
	fontx[6][2] = x6;		fonty[6][2] = yc1;
	fontx[6][3] = x4;		fonty[6][3] = yc0;
	fontx[6][4] = fxdim;	fonty[6][4] = yc1 - yangle;
	fontx[6][5] = x5;		fonty[6][5] = yc0 - yinside;
	fontx[6][6] = fxdim;	fonty[6][6] = y1;
	fontx[6][7] = x5;		fonty[6][7] = y3;
	fontx[6][8] = x6;		fonty[6][8] = 0.f;
	fontx[6][9] = x4;		fonty[6][9] = y2;
	fontx[6][10] = x1;		fonty[6][10] = 0.f;
	fontx[6][11] = x3;		fonty[6][11] = y2;
	fontx[6][12] = 0.f;		fonty[6][12] = y1;
	fontx[6][13] = x2;		fonty[6][13] = y3;
	fontx[6][14] = 0.f;		fonty[6][14] = fydim + frise - yangle;
	fontx[6][15] = x2;		fonty[6][15] = fydim + frise - ywidth - yinside;
	fontx[6][16] = x1;		fonty[6][16] = fydim + frise;
	fontx[6][17] = x3;		fonty[6][17] = fydim + frise - ywidth;
	fontx[6][18] = x6;		fonty[6][18] = fydim + frise;
	fontx[6][19] = x4;		fonty[6][19] = fydim + frise - ywidth;
	fontx[6][20] = fxdim;	fonty[6][20] = fydim + frise - yangle;
	fontx[6][21] = x6;		fonty[6][21] = fydim + frise - ywidth - yinside;

	fontx[5][0] = xwidth;	fonty[5][0] = y3;				//	lower to upper
	fontx[5][1] = 0.f;		fonty[5][1] = y1;
	fontx[5][2] = x3;		fonty[5][2] = y2;
	fontx[5][3] = x1;		fonty[5][3] = 0.f;
	fontx[5][4] = x4;		fonty[5][4] = y2;
	fontx[5][5] = x6;		fonty[5][5] = 0.f;
	fontx[5][6] = x5;		fonty[5][6] = y3;
	fontx[5][7] = fxdim;	fonty[5][7] = y1;
	fontx[5][8] = x5;		fonty[5][8] = yc0 - yinside;
	fontx[5][9] = fxdim;	fonty[5][9] = yc1 - yangle;
	fontx[5][10] = x4;		fonty[5][10] = yc0;
	fontx[5][11] = x6;		fonty[5][11] = yc1;
	fontx[5][12] = x1;		fonty[5][12] = yc0 + yinside;
	fontx[5][13] = x3;		fonty[5][13] = yc1 + yinside;
	fontx[5][14] = 0.f;		fonty[5][14] = yc0 + yangle + yinside;
	fontx[5][15] = x2;		fonty[5][15] = yc1 + yinside + yinside;
	fontx[5][16] = 0.f;		fonty[5][16] = fydim + frise;
	fontx[5][17] = xwidth;	fonty[5][17] = fydim + frise - ywidth;
	fontx[5][18] = fxdim;	fonty[5][18] = fydim + frise;
	fontx[5][19] = fxdim;	fonty[5][19] = fydim + frise - ywidth;

	fontx[4][0] = x5;		fonty[4][0] = fydim + frise;	//	vertical then L
	fontx[4][1] = x5;		fonty[4][1] = 0.f;
	fontx[4][2] = fxdim;	fonty[4][2] = fydim + frise;
	fontx[4][3] = fxdim;	fonty[4][3] = 0.f;
	fontx[4][4] = x2;		fonty[4][4] = fydim + frise;
	fontx[4][5] = 0.f;		fonty[4][5] = fydim + frise;
	fontx[4][6] = x2;		fonty[4][6] = yc1;
	fontx[4][7] = 0.f;		fonty[4][7] = yc0;
	fontx[4][8] = x5;		fonty[4][8] = yc1;
	fontx[4][9] = x5;		fonty[4][9] = yc0;

	fontx[3][0] = 0.f;		fonty[3][0] = fydim + frise - yangle;			//	top left proceeding clockwise
	fontx[3][1] = x2;		fonty[3][1] = fydim + frise - ywidth - yinside;
	fontx[3][2] = x1;		fonty[3][2] = fydim + frise;
	fontx[3][3] = x3;		fonty[3][3] = fydim + frise - ywidth;
	fontx[3][4] = x6;		fonty[3][4] = fydim + frise;
	fontx[3][5] = x4;		fonty[3][5] = fydim + frise - ywidth;
	fontx[3][6] = fxdim;	fonty[3][6] = fydim + frise - yangle;
	fontx[3][7] = x5;		fonty[3][7] = fydim + frise - ywidth - yinside;
	fontx[3][8] = fxdim;	fonty[3][8] = yc0 + yangle + yinside;
	fontx[3][9] = x5;		fonty[3][9] = yc1 + yinside + yinside;
	fontx[3][10] = x2 + xinside;		fonty[3][10] = yc0;// + yinside;
	fontx[3][11] = x2 + xinside;		fonty[3][11] = yc1;// + yinside;
	slope = (yc0 - (yc1 - (yc1 + yinside + yinside - yc0))) / (x5 - (x2 + xinside));	//	10 - 15, x inverted i guess
	slope2 = (yc0 - (yc0 + yangle + yinside)) / ((x2 + xinside) - fxdim);				//	10 - 8 upper slope
	t0 = slope / (slope + slope2);								//	ratio of slopes
	t0 *= (yc0 + yangle + yinside) - (yc1 - yangle - yinside);	//	really the y distance between 8 and 14
	fontx[3][12] = fxdim - t0 / slope;			fonty[3][12] = (yc1 - yangle - yinside) + t0;
	fontx[3][13] = x2 + xinside;		fonty[3][13] = yc0;
	fontx[3][14] = fxdim;	fonty[3][14] = yc1 - yangle - yinside;
	fontx[3][15] = x5;		fonty[3][15] = yc1 - (yc1 + yinside + yinside - yc0);
	fontx[3][16] = fxdim;	fonty[3][16] = y1;
	fontx[3][17] = x5;		fonty[3][17] = y3;
	fontx[3][18] = x6;		fonty[3][18] = 0.f;
	fontx[3][19] = x4;		fonty[3][19] = y2;
	fontx[3][20] = x1;		fonty[3][20] = 0.f;
	fontx[3][21] = x3;		fonty[3][21] = y2;
	fontx[3][22] = 0.f;		fonty[3][22] = y1;
	fontx[3][23] = x2;		fonty[3][23] = y3;

	fontx[2][0] = 0.f;		fonty[2][0] = fydim + frise - yangle;			//	top left proceeding clockwise
	fontx[2][1] = x2;		fonty[2][1] = fydim + frise - ywidth - yinside;
	fontx[2][2] = x1;		fonty[2][2] = fydim + frise;
	fontx[2][3] = x3;		fonty[2][3] = fydim + frise - ywidth;
	fontx[2][4] = x6;		fonty[2][4] = fydim + frise;
	fontx[2][5] = x4;		fonty[2][5] = fydim + frise - ywidth;
	fontx[2][6] = fxdim;	fonty[2][6] = fydim + frise - yangle;
	fontx[2][7] = x5;		fonty[2][7] = fydim + frise - ywidth - yinside;
	fontx[2][8] = fxdim;	fonty[2][8] = yc0 + yangle + yinside;
	fontx[2][9] = x5;		fonty[2][9] = yc1 + yinside + yinside;
	fontx[2][10] = x6;		fonty[2][10] = yc0 + yinside;
	fontx[2][11] = x4;		fonty[2][11] = yc1 + yinside;
	fontx[2][12] = x3;		fonty[2][12] = yc0;// - yinside;
	fontx[2][13] = x1;		fonty[2][13] = yc1;// - yinside;
	fontx[2][14] = x2;		fonty[2][14] = yc0 - yinside;// - yinside;// - yinside;
	fontx[2][15] = 0.f;		fonty[2][15] = yc1 - yangle;// - yinside;// - yinside;
	fontx[2][16] = x2;		fonty[2][16] = y2;
	fontx[2][17] = 0.f;		fonty[2][17] = 0.f;
	fontx[2][18] = fxdim;	fonty[2][18] = y2;
	fontx[2][19] = fxdim;	fonty[2][19] = 0.f;

	fontx[1][0] = 0.f;				fonty[1][0] = fydim + frise - yangle;
	fontx[1][1] = 0.f;				fonty[1][1] = fydim + frise - yangle - ywidth;
	fontx[1][2] = xangle;			fonty[1][2] = fydim + frise;
	fontx[1][3] = xangle;			fonty[1][3] = fydim + frise - ywidth;
	fontx[1][4] = xangle + xwidth;	fonty[1][4] = fydim + frise;
	fontx[1][5] = xangle;			fonty[1][5] = 0.f;
	fontx[1][6] = xangle + xwidth;	fonty[1][6] = 0.f;

	fontx[0][0] = 0.f;		fonty[0][0] = fydim + frise - yangle;			//	top left proceeding clockwise
	fontx[0][1] = x2;		fonty[0][1] = fydim + frise - ywidth - yinside;
	fontx[0][2] = x1;		fonty[0][2] = fydim + frise;
	fontx[0][3] = x3;		fonty[0][3] = fydim + frise - ywidth;
	fontx[0][4] = x6;		fonty[0][4] = fydim + frise;
	fontx[0][5] = x4;		fonty[0][5] = fydim + frise - ywidth;
	fontx[0][6] = fxdim;	fonty[0][6] = fydim + frise - yangle;
	fontx[0][7] = x5;		fonty[0][7] = fydim + frise - ywidth - yinside;
	fontx[0][8] = fxdim;	fonty[0][8] = y1;
	fontx[0][9] = x5;		fonty[0][9] = y3;
	fontx[0][10] = x6;		fonty[0][10] = 0.f;
	fontx[0][11] = x4;		fonty[0][11] = y2;
	fontx[0][12] = x1;		fonty[0][12] = 0.f;
	fontx[0][13] = x3;		fonty[0][13] = y2;
	fontx[0][14] = 0.f;		fonty[0][14] = y1;
	fontx[0][15] = x2;		fonty[0][15] = y3;
	fontx[0][16] = 0.f;		fonty[0][16] = fydim + frise - yangle;
	fontx[0][17] = x2;		fonty[0][17] = fydim + frise - ywidth - yinside;








	for (int i = 0; i < 42; i++) finc[i] = fxdim + fspacing;
//	finc[8] = 0;		//	first half of 8.. follow with [36]
	finc[15] = fxdim + fspacing * 0.2f;		//	f
	finc[18] = xwidth + fspacing;			//	i
	finc[19] = fxdim;						//	j
	finc[21] = xwidth + fspacing;			//	l
	finc[22] = fxdim + fxdim - xwidth + fspacing;	//	m
	finc[27] = fxdim + fspacing * 0.2f;		//	r

	finc[32] = fxdim - xwidth;				//	w - second half
	finc[36] = 0.f;							//	second half of 8 (top)
	finc[37] = xwidth + fspacing;			//	period

};











void textmesh() {	//	it's not really a mesh just naming convention :)
	//	0 - 9     22, 8, 18, 22
	//	10-19	a - j
	//	20-29	k - t
	//	30+		u - z, top half of '8', period, dash, left, right (only declared to 41)

	//glyphs = 4;	glyph[0] = 16;	glyph[1] = 10;	glyph[2] = 22;	glyph[3] = 14;	//	game
	//glyphs = 4;	glyph[0] = 22;	glyph[1] = 10;	glyph[2] = 35;	glyph[3] = 14;	//	maze
	//glyphs = 5;	glyph[0] = 31;	glyph[1] = 32;	glyph[2] = 14;	glyph[3] = 14;	glyph[4] = 13;	//	weed

	glyphs = 36;
	for (int i = 0; i < 36; i++) glyph[i] = ((testing >> 3) + i) % 36;
	testing < 288 ? testing++ : testing = 0;

	int glyphix = 0;	//	glyph mesh index accumulator
	float fxloc = -4.f;	//	line position accumulator
	float fyloc = 2.4f;
	for (int j = 0; j < glyphs; j++) {
		if (!(j % 12)) { fxloc = -4.f;	fyloc -= 0.4f; }
		for (int i = 0; i < fpoints[glyph[j]]; i++) {
			register int ix = (glyphix + i) * 6;
			pointvertices[ix] = fxloc + fontx[glyph[j]][i] * fscale;
			pointvertices[ix + 1] = fyloc + fonty[glyph[j]][i] * fscale;
			pointvertices[ix + 2] = 0;
			pointvertices[ix + 3] = -0.2f;// 0.9f;	
				pointvertices[ix + 4] = -0.2f;	pointvertices[ix + 5] = -0.2f;
		}
		fxloc += finc[glyph[j]] * fscale;	
		glyphindex[j] = glyphix;	glyphix += fpoints[glyph[j]];
	}

	glBindBuffer(GL_ARRAY_BUFFER, pointvbo);	//	this has to be after vao binding
	glBufferData(GL_ARRAY_BUFFER, sizeof(pointvertices), pointvertices, GL_DYNAMIC_DRAW);


};





//	you would do something like this in the display function

textmesh();	//	defined in minimesh	move to function around line 220
	material = 8;	glUniform1i(materialLocation, material);	//	TEXT DISPLAY	//	glPointSize(dispx * 0.02);
	glBindVertexArray(pointvao);	
	
	for (int i = 0; i < glyphs; i++) {
		if (fstripindex[glyph[i]]) {
			glDrawArrays(GL_TRIANGLE_STRIP, glyphindex[i], fstripindex[glyph[i]]);
			glDrawArrays(GL_TRIANGLE_STRIP, glyphindex[i] + fstripindex[glyph[i]], fpoints[glyph[i]] - fstripindex[glyph[i]]);
		}
		else glDrawArrays(GL_TRIANGLE_STRIP, glyphindex[i], fpoints[glyph[i]]);
	}


//	and this is stuff you should set up for yourself but for eg.
unsigned int pointvao, pointvbo;	//	point array

float pointvertices[9216];			// 144 = 24 point char - 64 chars

	glGenVertexArrays(1, &pointvao);	glBindVertexArray(pointvao);	//	vao/vbo for point array
	glGenBuffers(1, &pointvbo);	glBindBuffer(GL_ARRAY_BUFFER, pointvbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pointvertices), pointvertices, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);					glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);	glBindVertexArray(0);








