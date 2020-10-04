/*
** Odin 2 Synthesizer Plugin
** Copyright (C) 2020 TheWaveWarden
**
** Odin 2 is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Odin 2 is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
*/

#define WT_NR 150


m_wavetable_names_1D[WT_NR] = "PerlinReplace3";




//m_fourier_coeffs[WT_NR][1][0] = 0.256269f; // scalar

//m_fourier_coeffs[WT_NR][0][1] = 0.139490f;
//m_fourier_coeffs[WT_NR][0][2] = 0.179982f;
//m_fourier_coeffs[WT_NR][0][3] = 0.407049f;
//m_fourier_coeffs[WT_NR][0][4] = 0.331237f;
////m_fourier_coeffs[WT_NR][0][5] = 0.301097f;
////m_fourier_coeffs[WT_NR][0][6] = 0.471707f;
////m_fourier_coeffs[WT_NR][0][7] = 0.083341f;
////m_fourier_coeffs[WT_NR][0][8] = 0.176586f;
////m_fourier_coeffs[WT_NR][0][9] = 0.215134f;
////m_fourier_coeffs[WT_NR][0][10] = 0.189050f;
////m_fourier_coeffs[WT_NR][0][11] = 0.199470f;
////m_fourier_coeffs[WT_NR][0][12] = 0.120349f;
////m_fourier_coeffs[WT_NR][0][13] = 0.085019f;
//m_fourier_coeffs[WT_NR][0][14] = 0.409751f;
//m_fourier_coeffs[WT_NR][0][15] = 0.285732f;
//m_fourier_coeffs[WT_NR][0][16] = 0.383750f;
//m_fourier_coeffs[WT_NR][0][17] = 0.089324f;
//m_fourier_coeffs[WT_NR][0][18] = 0.329313f;
//m_fourier_coeffs[WT_NR][0][19] = 0.299783f;
//m_fourier_coeffs[WT_NR][0][20] = 0.097346f;
//m_fourier_coeffs[WT_NR][0][21] = 0.314697f;
//m_fourier_coeffs[WT_NR][0][22] = 0.242040f;
//m_fourier_coeffs[WT_NR][0][23] = 0.127561f;
//m_fourier_coeffs[WT_NR][0][24] = 0.272982f;
//m_fourier_coeffs[WT_NR][0][25] = 0.290082f;
//m_fourier_coeffs[WT_NR][0][26] = 0.279014f;
//m_fourier_coeffs[WT_NR][0][27] = 0.129492f;
//m_fourier_coeffs[WT_NR][0][28] = 0.176441f;
//m_fourier_coeffs[WT_NR][0][29] = 0.378934f;
//m_fourier_coeffs[WT_NR][0][30] = 0.230274f;
////m_fourier_coeffs[WT_NR][0][31] = 0.281815f;
////m_fourier_coeffs[WT_NR][0][32] = 0.249277f;
////m_fourier_coeffs[WT_NR][0][33] = 0.338941f;
////m_fourier_coeffs[WT_NR][0][34] = 0.146794f;
////m_fourier_coeffs[WT_NR][0][35] = 0.264411f;
////m_fourier_coeffs[WT_NR][0][36] = 0.120405f;
////m_fourier_coeffs[WT_NR][0][37] = 0.213280f;
////m_fourier_coeffs[WT_NR][0][38] = 0.092842f;
////m_fourier_coeffs[WT_NR][0][39] = 0.042926f;
////m_fourier_coeffs[WT_NR][0][40] = 0.242564f;
//m_fourier_coeffs[WT_NR][0][41] = 0.113490f;
//m_fourier_coeffs[WT_NR][0][42] = 0.187826f;
//m_fourier_coeffs[WT_NR][0][43] = 0.347496f;
//m_fourier_coeffs[WT_NR][0][44] = 0.255650f;
//m_fourier_coeffs[WT_NR][0][45] = 0.214076f;
//m_fourier_coeffs[WT_NR][0][46] = 0.262615f;
//m_fourier_coeffs[WT_NR][0][47] = 0.464100f;
//m_fourier_coeffs[WT_NR][0][48] = 0.265696f;
//m_fourier_coeffs[WT_NR][0][49] = 0.130566f;
//m_fourier_coeffs[WT_NR][0][50] = 0.151355f;
//m_fourier_coeffs[WT_NR][0][51] = 0.187988f;
//m_fourier_coeffs[WT_NR][0][52] = 0.128648f;
//m_fourier_coeffs[WT_NR][0][53] = 0.152970f;
//m_fourier_coeffs[WT_NR][0][54] = 0.109687f;
//m_fourier_coeffs[WT_NR][0][55] = 0.142452f;
//m_fourier_coeffs[WT_NR][0][56] = 0.232467f;
//m_fourier_coeffs[WT_NR][0][57] = 0.360428f;
//m_fourier_coeffs[WT_NR][0][58] = 0.193771f;
//m_fourier_coeffs[WT_NR][0][59] = 0.117458f;
//m_fourier_coeffs[WT_NR][0][60] = 0.069206f;
//m_fourier_coeffs[WT_NR][0][61] = 0.070257f;
//m_fourier_coeffs[WT_NR][0][62] = 0.162558f;
//m_fourier_coeffs[WT_NR][0][63] = 0.278406f;
//m_fourier_coeffs[WT_NR][0][64] = 0.041759f;
//m_fourier_coeffs[WT_NR][0][65] = 0.073072f;
//m_fourier_coeffs[WT_NR][0][66] = 0.135900f;
//m_fourier_coeffs[WT_NR][0][67] = 0.401420f;
//m_fourier_coeffs[WT_NR][0][68] = 0.239880f;
//m_fourier_coeffs[WT_NR][0][69] = 0.276713f;
//m_fourier_coeffs[WT_NR][0][70] = 0.160697f;
//m_fourier_coeffs[WT_NR][0][71] = 0.228080f;
//m_fourier_coeffs[WT_NR][0][72] = 0.118641f;
//m_fourier_coeffs[WT_NR][0][73] = 0.134231f;
//m_fourier_coeffs[WT_NR][0][74] = 0.126477f;
//m_fourier_coeffs[WT_NR][0][75] = 0.190543f;
//m_fourier_coeffs[WT_NR][0][76] = 0.066658f;
//m_fourier_coeffs[WT_NR][0][77] = 0.154928f;
//m_fourier_coeffs[WT_NR][0][78] = 0.110272f;
//m_fourier_coeffs[WT_NR][0][79] = 0.142632f;
//m_fourier_coeffs[WT_NR][0][80] = 0.164839f;
//m_fourier_coeffs[WT_NR][0][81] = 0.107298f;
//m_fourier_coeffs[WT_NR][0][82] = 0.031295f;
//m_fourier_coeffs[WT_NR][0][83] = 0.162101f;
//m_fourier_coeffs[WT_NR][0][84] = 0.092460f;
//m_fourier_coeffs[WT_NR][0][85] = 0.104884f;
//m_fourier_coeffs[WT_NR][0][86] = 0.022369f;
//m_fourier_coeffs[WT_NR][0][87] = 0.118369f;
//m_fourier_coeffs[WT_NR][0][88] = 0.036660f;
//m_fourier_coeffs[WT_NR][0][89] = 0.101071f;
//m_fourier_coeffs[WT_NR][0][90] = 0.062281f;
//m_fourier_coeffs[WT_NR][0][91] = 0.124313f;
//m_fourier_coeffs[WT_NR][0][92] = 0.054875f;
//m_fourier_coeffs[WT_NR][0][93] = 0.119781f;
//m_fourier_coeffs[WT_NR][0][94] = 0.197100f;
//m_fourier_coeffs[WT_NR][0][95] = 0.044598f;
//m_fourier_coeffs[WT_NR][0][96] = 0.165391f;
//m_fourier_coeffs[WT_NR][0][97] = 0.076200f;
//m_fourier_coeffs[WT_NR][0][98] = 0.036820f;
//m_fourier_coeffs[WT_NR][0][99] = 0.101545f;
//m_fourier_coeffs[WT_NR][0][100] = 0.073590f;
//m_fourier_coeffs[WT_NR][0][101] = 0.094966f;
//m_fourier_coeffs[WT_NR][0][102] = 0.058109f;
//m_fourier_coeffs[WT_NR][0][103] = 0.025136f;
//m_fourier_coeffs[WT_NR][0][104] = 0.124264f;
//m_fourier_coeffs[WT_NR][0][105] = 0.050576f;
//m_fourier_coeffs[WT_NR][0][106] = 0.041158f;
//m_fourier_coeffs[WT_NR][0][107] = 0.102190f;
//m_fourier_coeffs[WT_NR][0][108] = 0.076577f;
//m_fourier_coeffs[WT_NR][0][109] = 0.082883f;
//m_fourier_coeffs[WT_NR][0][110] = 0.077134f;
//m_fourier_coeffs[WT_NR][0][111] = 0.107532f;
//m_fourier_coeffs[WT_NR][0][112] = 0.085610f;
//m_fourier_coeffs[WT_NR][0][113] = 0.115214f;
//m_fourier_coeffs[WT_NR][0][114] = 0.058637f;
//m_fourier_coeffs[WT_NR][0][115] = 0.041375f;
//m_fourier_coeffs[WT_NR][0][116] = 0.059206f;
//m_fourier_coeffs[WT_NR][0][117] = 0.052967f;
//m_fourier_coeffs[WT_NR][0][118] = 0.074418f;
//m_fourier_coeffs[WT_NR][0][119] = 0.039759f;
//m_fourier_coeffs[WT_NR][0][120] = 0.085230f;
//m_fourier_coeffs[WT_NR][0][121] = 0.060855f;
//m_fourier_coeffs[WT_NR][0][122] = 0.063008f;
//m_fourier_coeffs[WT_NR][0][123] = 0.046590f;
//m_fourier_coeffs[WT_NR][0][124] = 0.025911f;
//m_fourier_coeffs[WT_NR][0][125] = 0.059585f;
//m_fourier_coeffs[WT_NR][0][126] = 0.043486f;
//m_fourier_coeffs[WT_NR][0][127] = 0.063094f;
//m_fourier_coeffs[WT_NR][0][128] = 0.010368f;
//m_fourier_coeffs[WT_NR][0][129] = 0.061063f;
//m_fourier_coeffs[WT_NR][0][130] = 0.077436f;
//m_fourier_coeffs[WT_NR][0][131] = 0.052389f;
//m_fourier_coeffs[WT_NR][0][132] = 0.041677f;
//m_fourier_coeffs[WT_NR][0][133] = 0.057618f;
//m_fourier_coeffs[WT_NR][0][134] = 0.040140f;
//m_fourier_coeffs[WT_NR][0][135] = 0.052787f;
//m_fourier_coeffs[WT_NR][0][136] = 0.048470f;
//m_fourier_coeffs[WT_NR][0][137] = 0.075254f;
//m_fourier_coeffs[WT_NR][0][138] = 0.025196f;
//m_fourier_coeffs[WT_NR][0][139] = 0.014127f;
//m_fourier_coeffs[WT_NR][0][140] = 0.043637f;
//m_fourier_coeffs[WT_NR][0][141] = 0.051907f;
//m_fourier_coeffs[WT_NR][0][142] = 0.006237f;
//m_fourier_coeffs[WT_NR][0][143] = 0.026146f;
//m_fourier_coeffs[WT_NR][0][144] = 0.031081f;
//m_fourier_coeffs[WT_NR][0][145] = 0.035750f;
//m_fourier_coeffs[WT_NR][0][146] = 0.016841f;
//m_fourier_coeffs[WT_NR][0][147] = 0.052440f;
//m_fourier_coeffs[WT_NR][0][148] = 0.046677f;
//m_fourier_coeffs[WT_NR][0][149] = 0.016831f;
//m_fourier_coeffs[WT_NR][0][150] = 0.033071f;
//m_fourier_coeffs[WT_NR][0][151] = 0.027007f;
//m_fourier_coeffs[WT_NR][0][152] = 0.051930f;
//m_fourier_coeffs[WT_NR][0][153] = 0.047425f;
//m_fourier_coeffs[WT_NR][0][154] = 0.057321f;
//m_fourier_coeffs[WT_NR][0][155] = 0.042574f;
//m_fourier_coeffs[WT_NR][0][156] = 0.082962f;
//m_fourier_coeffs[WT_NR][0][157] = 0.036640f;
//m_fourier_coeffs[WT_NR][0][158] = 0.015159f;
//m_fourier_coeffs[WT_NR][0][159] = 0.039398f;
//m_fourier_coeffs[WT_NR][0][160] = 0.045023f;
//m_fourier_coeffs[WT_NR][0][161] = 0.014357f;
//m_fourier_coeffs[WT_NR][0][162] = 0.020950f;
//m_fourier_coeffs[WT_NR][0][163] = 0.046802f;
//m_fourier_coeffs[WT_NR][0][164] = 0.039635f;
//m_fourier_coeffs[WT_NR][0][165] = 0.012503f;
//m_fourier_coeffs[WT_NR][0][166] = 0.009604f;
//m_fourier_coeffs[WT_NR][0][167] = 0.038039f;
//m_fourier_coeffs[WT_NR][0][168] = 0.002907f;
//m_fourier_coeffs[WT_NR][0][169] = 0.025134f;
//m_fourier_coeffs[WT_NR][0][170] = 0.008714f;
//m_fourier_coeffs[WT_NR][0][171] = 0.020801f;
//m_fourier_coeffs[WT_NR][0][172] = 0.026610f;
//m_fourier_coeffs[WT_NR][0][173] = 0.020638f;
//m_fourier_coeffs[WT_NR][0][174] = 0.050106f;
//m_fourier_coeffs[WT_NR][0][175] = 0.036952f;
//m_fourier_coeffs[WT_NR][0][176] = 0.016224f;
//m_fourier_coeffs[WT_NR][0][177] = 0.032916f;
//m_fourier_coeffs[WT_NR][0][178] = 0.023429f;
//m_fourier_coeffs[WT_NR][0][179] = 0.014246f;
//m_fourier_coeffs[WT_NR][0][180] = 0.014044f;
//m_fourier_coeffs[WT_NR][0][181] = 0.004170f;
//m_fourier_coeffs[WT_NR][0][182] = 0.036177f;
//m_fourier_coeffs[WT_NR][0][183] = 0.023346f;
//m_fourier_coeffs[WT_NR][0][184] = 0.024844f;
//m_fourier_coeffs[WT_NR][0][185] = 0.017188f;
//m_fourier_coeffs[WT_NR][0][186] = 0.007390f;
//m_fourier_coeffs[WT_NR][0][187] = 0.006461f;
//m_fourier_coeffs[WT_NR][0][188] = 0.014443f;
//m_fourier_coeffs[WT_NR][0][189] = 0.019621f;
//m_fourier_coeffs[WT_NR][0][190] = 0.012920f;
//m_fourier_coeffs[WT_NR][0][191] = 0.005078f;
//m_fourier_coeffs[WT_NR][0][192] = 0.009777f;
//m_fourier_coeffs[WT_NR][0][193] = 0.013433f;
//m_fourier_coeffs[WT_NR][0][194] = 0.001739f;
//m_fourier_coeffs[WT_NR][0][195] = 0.024266f;
//m_fourier_coeffs[WT_NR][0][196] = 0.019653f;
//m_fourier_coeffs[WT_NR][0][197] = 0.010839f;
//m_fourier_coeffs[WT_NR][0][198] = 0.009445f;
//m_fourier_coeffs[WT_NR][0][199] = 0.021346f;
//m_fourier_coeffs[WT_NR][0][200] = 0.022442f;
//m_fourier_coeffs[WT_NR][0][201] = 0.003869f;
//m_fourier_coeffs[WT_NR][0][202] = 0.013719f;
//m_fourier_coeffs[WT_NR][0][203] = 0.027205f;
//m_fourier_coeffs[WT_NR][0][204] = 0.007232f;
//m_fourier_coeffs[WT_NR][0][205] = 0.030979f;
//m_fourier_coeffs[WT_NR][0][206] = 0.012360f;
//m_fourier_coeffs[WT_NR][0][207] = 0.009421f;
//m_fourier_coeffs[WT_NR][0][208] = 0.010051f;
//m_fourier_coeffs[WT_NR][0][209] = 0.006450f;
//m_fourier_coeffs[WT_NR][0][210] = 0.011937f;
//m_fourier_coeffs[WT_NR][0][211] = 0.014904f;
//m_fourier_coeffs[WT_NR][0][212] = 0.007007f;
//m_fourier_coeffs[WT_NR][0][213] = 0.007748f;
//m_fourier_coeffs[WT_NR][0][214] = 0.009885f;
//m_fourier_coeffs[WT_NR][0][215] = 0.014583f;
//m_fourier_coeffs[WT_NR][0][216] = 0.027813f;
//m_fourier_coeffs[WT_NR][0][217] = 0.008189f;
//m_fourier_coeffs[WT_NR][0][218] = 0.015135f;
//m_fourier_coeffs[WT_NR][0][219] = 0.010157f;
//m_fourier_coeffs[WT_NR][0][220] = 0.013302f;
//m_fourier_coeffs[WT_NR][0][221] = 0.007433f;
//m_fourier_coeffs[WT_NR][0][222] = 0.015329f;
//m_fourier_coeffs[WT_NR][0][223] = 0.006096f;
//m_fourier_coeffs[WT_NR][0][224] = 0.013684f;
//m_fourier_coeffs[WT_NR][0][225] = 0.009968f;
//m_fourier_coeffs[WT_NR][0][226] = 0.012335f;
//m_fourier_coeffs[WT_NR][0][227] = 0.012598f;
//m_fourier_coeffs[WT_NR][0][228] = 0.006059f;
//m_fourier_coeffs[WT_NR][0][229] = 0.004801f;
//m_fourier_coeffs[WT_NR][0][230] = 0.004716f;
//m_fourier_coeffs[WT_NR][0][231] = 0.009335f;
//m_fourier_coeffs[WT_NR][0][232] = 0.008347f;
//m_fourier_coeffs[WT_NR][0][233] = 0.003635f;
//m_fourier_coeffs[WT_NR][0][234] = 0.017136f;
//m_fourier_coeffs[WT_NR][0][235] = 0.004831f;
//m_fourier_coeffs[WT_NR][0][236] = 0.002938f;
//m_fourier_coeffs[WT_NR][0][237] = 0.002207f;
//m_fourier_coeffs[WT_NR][0][238] = 0.008855f;
//m_fourier_coeffs[WT_NR][0][239] = 0.008529f;
//m_fourier_coeffs[WT_NR][0][240] = 0.002574f;
//m_fourier_coeffs[WT_NR][0][241] = 0.009801f;
//m_fourier_coeffs[WT_NR][0][242] = 0.010145f;
//m_fourier_coeffs[WT_NR][0][243] = 0.001547f;
//m_fourier_coeffs[WT_NR][0][244] = 0.018687f;
//m_fourier_coeffs[WT_NR][0][245] = 0.005093f;
//m_fourier_coeffs[WT_NR][0][246] = 0.003038f;
//m_fourier_coeffs[WT_NR][0][247] = 0.001319f;
//m_fourier_coeffs[WT_NR][0][248] = 0.013029f;
//m_fourier_coeffs[WT_NR][0][249] = 0.005639f;
//m_fourier_coeffs[WT_NR][0][250] = 0.001062f;
//m_fourier_coeffs[WT_NR][0][251] = 0.006997f;
//m_fourier_coeffs[WT_NR][0][252] = 0.006487f;
//m_fourier_coeffs[WT_NR][0][253] = 0.005676f;
//m_fourier_coeffs[WT_NR][0][254] = 0.008580f;
//m_fourier_coeffs[WT_NR][0][255] = 0.010007f;


#undef WT_NR
