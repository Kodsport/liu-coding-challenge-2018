#!/usr/bin/env python3
print(['dae ae ju traeligt va', 'haer talar vi rikssvenska'][(lambda W: sum(1 for w in W if 'ae' in w)*10 < len(W)*4)(input().split())])
