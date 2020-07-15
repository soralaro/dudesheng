#ffmpeg -f image2 -i ./d2to1_png/%d.png -keyint_min 0 -g 10 -preset veryslow -qp 0 -vcodec libx264 -r 25  d1.h264
ffmpeg -f image2 -i ./d2to1_png/%d.png -keyint_min 0 -g 10  -vcodec libx264 -r 25  d1.h264
