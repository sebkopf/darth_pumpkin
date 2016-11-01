// modified from pitches created by instructables user eserra
// http://www.instructables.com/id/How-to-easily-play-music-with-buzzer-on-arduino-Th/

// PAUSE
#define NP    0

// OTHER NOTES
#define	NC0  16.35
#define	NDb0	17.32
#define	ND0	18.35
#define	NEb0	19.45
#define	NE0	20.60
#define	NF0	21.83
#define	NGb0	23.12
#define	NG0	24.50
#define	NAb0	25.96
#define	NA0	27.50
#define	NBb0	29.14
#define	NB0	30.87
#define	NC1	32.70
#define	NDb1	34.65
#define	ND1	36.71
#define	NEb1	38.89
#define	NE1	41.20
#define	NF1	43.65
#define	NGb1	46.25
#define	NG1	49.00
#define	NAb1	51.91
#define	NA1	55.00
#define	NBb1	58.27
#define	NB1	61.74
#define	NC2	65.41
#define	NDb2	69.30
#define	ND2	73.42
#define	NEb2	77.78
#define	NE2	82.41
#define	NF2	87.31
#define	NGb2	92.50
#define	NG2	98.00
#define	NAb2	103.83
#define	NA2	110.00
#define	NBb2	116.54
#define	NB2	123.47
#define	NC3	130.81
#define	NDb3	138.59
#define	ND3	146.83
#define	NEb3	155.56
#define	NE3	164.81
#define	NF3	174.61
#define	NGb3	185.00
#define	NG3	196.00
#define	NAb3	207.65
#define	NA3	220.00
#define	NBb3	233.08
#define	NB3	246.94
#define	NC4	261.63
#define	NDb4	277.18
#define	ND4	293.66
#define	NEb4	311.13
#define	NE4	329.63
#define	NF4	349.23
#define	NGb4	369.99
#define	NG4	392.00
#define	NAb4	415.30
#define	NA4	440.00
#define	NBb4	466.16
#define	NB4	493.88
#define	NC5	523.25
#define	NDb5	554.37
#define	ND5	587.33
#define	NEb5	622.25
#define	NE5	659.26
#define	NF5	698.46
#define	NGb5	739.99
#define	NG5	783.99
#define	NAb5	830.61
#define	NA5	880.00
#define	NBb5	932.33
#define	NB5	987.77
#define	NC6	1046.50
#define	NDb6	1108.73
#define	ND6	1174.66
#define	NEb6	1244.51
#define	NE6	1318.51
#define	NF6	1396.91
#define	NGb6	1479.98
#define	NG6	1567.98
#define	NAb6	1661.22
#define	NA6	1760.00
#define	NBb6	1864.66
#define	NB6	1975.53
#define	NC7	2093.00
#define	NDb7	2217.46
#define	ND7	2349.32
#define	NEb7	2489.02
#define	NE7	2637.02
#define	NF7	2793.83
#define	NGb7	2959.96
#define	NG7	3135.96
#define	NAb7	3322.44
#define	NA7	3520.01
#define	NBb7	3729.31
#define	NB7	3951.07
#define	NC8	4186.01
#define	NDb8	4434.92
#define	ND8	4698.64
#define	NEb8	4978.03

// notes durations
const int BPM = 120;
const int Q = 60000/BPM; //quarter 1/4
const int H = 2*Q; //half 2/4
const int E = Q/2;   //eighth 1/8
const int S = Q/4; // sixteenth 1/16
const int W = 4*Q; // whole 4/4
const int GAP = BPM/5; // gap between notes
