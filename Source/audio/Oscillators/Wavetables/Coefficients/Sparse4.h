#define WT_NR 91
	
m_wavetable_names_1D[WT_NR] = "Sparse4";
m_fourier_coeffs[WT_NR][0][0] = 1.f; //signals sine only
m_fourier_coeffs[WT_NR][1][0] = 0.539144; //Saw scalar (negative to invert for LFO)

m_fourier_coeffs[WT_NR][0][1] = 1.0;
m_fourier_coeffs[WT_NR][0][7] = 0.142857;
m_fourier_coeffs[WT_NR][0][13] = 0.0769231;
m_fourier_coeffs[WT_NR][0][19] = 0.0526316;
m_fourier_coeffs[WT_NR][0][25] = 0.04;
m_fourier_coeffs[WT_NR][0][31] = 0.0322581;
m_fourier_coeffs[WT_NR][0][37] = 0.027027;
m_fourier_coeffs[WT_NR][0][43] = 0.0232558;
m_fourier_coeffs[WT_NR][0][49] = 0.0204082;
#undef WT_NR
