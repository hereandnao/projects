#!/usr/bin/python
# coding: utf8

import os, sys

command = "./corewar";

if (len(sys.argv) != 2):
	print("script must take one numeric argument like:\n%s 5" %(sys.argv[0]));
	exit (1);

i = (int)(sys.argv[1]);

loc = \
[[50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 555, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1200, 1400, 1600, 1800, 2000, 2500, 3000, 3500, 4000, 4500, 5000,
6500, 7000, 7500, 8000, 8500, 9000, 9500, 10000, 11000, 12000, 13000, 14000, 15000, 16000, 17000, 18000, 19000, 20000, 21000, 22000, 23000, 24000, 25000, 25700, 25800, 25900,
26000, 26100, 26200, 26226],
\
[50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 555, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1200, 1400, 1600, 1800, 2000, 2500, 3000, 3500, 4000, 4500, 5000,
6500, 7000, 7500, 8000, 8500, 9000, 9500, 10000, 11000, 12000, 13000, 14000, 15000, 16000, 17000, 18000, 19000, 20000, 21000, 22000, 23000, 24000, 24100, 24200, 24250, 24300, 24366],
\
[50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 555, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1200, 1400, 1600, 1800, 2000, 2500, 3000, 3500, 4000, 4500, 5000,
6500, 7000, 7500, 8000, 8500, 9000, 9500, 10000, 11000, 12000, 13000, 14000, 15000, 16000, 17000, 18000, 19000, 20000, 21000, 22000, 23000, 24000, 25000, 25100, 25200, 25400, 25600, 25902],
\
[50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 555, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1200, 1400, 1600, 1800, 2000, 2500, 3000, 3500, 4000, 4500, 5000,
6500, 7000, 7500, 8000, 8500, 9000, 9500, 10000, 11000, 12000, 13000, 14000, 15000, 16000, 17000, 18000, 19000, 20000, 21000, 22000, 23000, 24000, 25000, 25100, 25200, 25400, 25600, 26000,
27000, 28000, 29000, 30000, 31000, 32000, 32500, 32700, 32900, 33000, 33060],
\
[50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 555, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1200, 1400, 1600, 1800, 2000, 2500, 3000, 3500, 4000, 4500, 5000,
6500, 7000, 7500, 8000, 8500, 9000, 9500, 10000, 11000, 12000, 13000, 14000, 15000, 16000, 17000, 18000, 19000, 20000, 21000, 22000, 23000, 24000, 24100, 24200, 24250, 24300, 24366],
\
[50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 555, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1200, 1400, 1600, 1800, 2000, 2500, 3000, 3500, 4000, 4500, 5000,
6500, 7000, 7500, 8000, 8500, 9000, 9500, 10000, 11000, 12000, 13000, 14000, 15000, 16000, 17000, 18000, 19000, 20000, 21000, 22000, 23000, 24000, 24100, 24200, 24250, 24300, 24366],
\
[50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 555, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1200, 1400, 1600, 1800, 2000, 2500, 3000, 3500, 4000, 4500, 5000,
5200, 5300, 5600, 5700, 5800, 5843],
\
[50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 555, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1200, 1400, 1600, 1800, 2000, 2500, 3000, 3500, 4000, 4500, 5000,
6500, 7000, 7500, 8000, 8500, 9000, 9500, 10000, 11000, 12000, 13000, 14000, 15000, 16000, 17000, 18000, 19000, 20000, 21000, 22000, 23000, 24000, 25000, 26000, 27000, 28000, 28050, 28100, 28150, 28200, 28224],
\
[50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 555, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1200, 1400, 1600, 1800, 2000, 2500, 3000, 3500, 4000, 4500, 5000,
6500, 7000, 7500, 8000, 8500, 9000, 9500, 10000, 11000, 12000, 13000, 14000, 15000, 16000, 17000, 18000, 19000, 20000, 21000, 22000, 23000, 24000, 25000, 25700, 25800, 25900,
26000, 26100, 26200, 26226],
\
[50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 555, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1200, 1400, 1600, 1800, 2000, 2500, 3000, 3500, 4000, 4500, 5000,
6500, 7000, 7500, 8000, 8500, 9000, 9500, 10000, 11000, 12000, 13000, 14000, 15000, 16000, 17000, 18000, 19000, 20000, 21000, 22000, 23000, 24000, 24100, 24200, 24250, 24300, 24366],
\
[50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 555, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1200, 1400, 1600, 1800, 2000, 2500, 3000, 3500, 4000, 4500, 5000,
6500, 7000, 7500, 8000, 8500, 9000, 9500, 10000, 11000, 12000, 13000, 14000, 15000, 16000, 17000, 18000, 19000, 20000, 21000, 22000, 23000, 24000, 24100, 24200, 24250, 24300, 24366]];

fight = \
["games/Misaka_Mikoto.cor games/skynet2.cor games/Machine-gun.cor games/casimir.cor",
"games/sam_2.0.cor games/doge.cor games/Rainbow_dash.cor games/youforkmytralala.cor",
"games/big_feet.cor games/loose.cor games/mandragore.cor games/gedeon.cor",
"games/terminator.cor games/ultimate-surrender.cor games/salamahenagalabadoun.cor games/corelol.cor",
\
"games/MarineKing.cor games/Kappa.cor games/Wall.cor games/Varimathras.cor",
"games/justin_bee.cor games/live.cor games/meowluigi.cor games/dubo.cor",
"games/jinx.cor games/THUNDER.cor games/Asombra.cor games/littlepuppy.cor",
"games/champ.cor games/darksasuke.cor",
\
"games/Misaka_Mikoto.cor games/skynet2.cor games/Machine-gun.cor",
"games/bee_gees.cor games/turtle.cor games/helltrain.cor games/bigzork.cor",
"games/darksasuke.cor games/Kappa.cor games/mandragore.cor games/Rainbow_dash.cor"];

f_dump = "-d"

f_filename_linux = "txt"
f_filename_macos = "_txt"

f_filename = f_filename_linux;

if ((i > len(loc)) or i == 0):
	print("arg value is FALSE.");
	exit (1);
i-=1;

j = 0;
while (j < len(loc[i])):
	string = "%s %s %i %s | tail -n 64 > %s%i" %(command, f_dump, loc[i][j], fight[i], f_filename, loc[i][j]);
	print("%s %s %i %s | tail -n 64 > %s%i" %(command, f_dump, loc[i][j], fight[i], f_filename, loc[i][j]));
	os.system(string);
	j+=1;

exit (0);
