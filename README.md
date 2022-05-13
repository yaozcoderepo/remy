# Remy

This code (`main branch`) is directly forked from [this](https://github.com/tcpexmachina/remy)

Then for our experiments, we modify the remy code in the following branch:

-   For memory modification, refer to `test-min-rtt`, `test-rtt-ewma`, `test-slow-rtt-ewma`, `test-slow-send-ewma` branches
-   For action modification, refer to `change-action` branch
-   For objective function experiment, refer to `remy-delta-*` branches
-   For design range experiment, you need to change `src/config.sh` file to different setting based on the report, and the other parts remain the same as the `main` branch

Basically, this code serve as a base case for our network project

To compile this code, navigate to the root directory of the repository

```bash
./autogen.sh
./configure
make

cd src
./config.sh
mkdir outputs
./remy cf="testing.cfg" of="outputs/remycc"
```

Then you would get trained RemyCC algorithm files in `outputs` folder.

For environment, we use VirtualBox together with Vagrant to set up VM. For more specific step, go to `train-vm` branch.

For testing, please refer to `test-ns` branch
