#!/bin/bash

./configuration of=testing \
                min_link_ppt=15 max_link_ppt=15 link_ppt_incr=0 \
                min_rtt=150 max_rtt=150 rtt_incr=0 \
                min_nsrc=8 max_nsrc=8 nsrc_incr=0 \
                min_on=5 max_on=5 on_incr=0 \
                min_off=0.2 max_off=0.2 off_incr=0 \
                min_sloss=0.02 max_sloss=0.02 sloss_incr=0 \
                ticks=5000 \
                min_buf_size=1000 max_buf_size=3000 buf_size_incr=1000
