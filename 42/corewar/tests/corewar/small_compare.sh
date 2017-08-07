#!/bin/sh
./corewar -d $1 games/justin_bee.cor games/live.cor games/meowluigi.cor games/dubo.cor | tail -n 64 > diff_1
./corenao -d $1 games/justin_bee.cor games/live.cor games/meowluigi.cor games/dubo.cor | tail -n 64 > diff_2
diff  diff_1 diff_2
exit 0
