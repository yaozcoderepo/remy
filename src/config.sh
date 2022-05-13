#!/bin/bash

./configuration of=testing \
                min_link_ppt=1 max_link_ppt=1 link_ppt_incr=0 \
                min_rtt=150 max_rtt=150 rtt_incr=0 \
                min_nsrc=8 max_nsrc=8 nsrc_incr=0 \
                min_on=5000 max_on=5000 on_incr=0 \
                min_off=5000 max_off=5000 off_incr=0 \
                min_sloss=0 max_sloss=0 sloss_incr=0 \
                ticks=200000 \
                min_buf_size=inf max_buf_size=inf buf_size_incr=0