#!/bin/bash

./configuration of=testing \
                min_link_ppt=10 max_link_ppt=10 link_ppt_incr=0 \
                min_rtt=100 max_rtt=200 rtt_incr=20 \
                min_nsrc=5 max_nsrc=5 nsrc_incr=0 \
                min_on=5 max_on=5 on_incr=0 \
                min_off=5 max_off=5 off_incr=0 \
                min_sloss=0.1 max_sloss=0.2 sloss_incr=0.1 \
                ticks=20 \
                min_buf_size=10000 max_buf_size=10000 buf_size_incr=0