# Remy

This code (`main branch`) is directly forked from [this](https://github.com/tcpexmachina/remy)

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
