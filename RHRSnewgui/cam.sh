raspivid -o - -t 0 -n  -w 1920 -h 1080 -fps 30| cvlc -vvv stream:///dev/stdin --sout '#rtp{sdp=rtsp://:8554/}' :demux=h264
