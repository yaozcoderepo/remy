# Testing Environment Setup

-   To reproduce the results from our project report, first download [remy-reproduce-1.0.tar.gz](https://web.mit.edu/remy/remy-reproduce-1.0.tar.gz) to the root directory
-   Uncompress it by running `tar zxvf remy-reproduce-1.0.tar.gz`
-   Inside the root directory, build a docker image by running `docker build -t network .`
-   Start a container from this created image by running `docker run -it --name=project --net=host network bash`
-   Then,

    ```bash
    cd /app/remy-reproduce-1.0
    ./install

    # Then
    # move all remycc algorithm files from the provided `dna` directory
    # to `/app/remy-reproduce-1.0/ns-2.35/tcl/ex/congctrl` directory
    # inside the container using `docker cp` command

    # move all scripts from the provided `scripts` directory to
    # `/app/remy-reproduce-1.0/ns-2.35/tcp/remy/rats/new` directory
    # inside the container using `docker cp` command as well

    cd /app/remy-reproduce-1.0/ns-2.35/tcl/ex/congctrl
    chmod 700 run-figure-*

    # if you want to reproduce the memory modification experiment in our project
    ./run-figure-memory

    # after 5-10 min
    cd ../graphing-scripts
    # run the command below and you will get the graph showing the result
    ./graphmaker ../congctrl/results/
    ```
