#include <cstdio>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "ratbreeder.hh"
#include "dna.pb.h"
#include "configrange.hh"

using namespace std;

void print_range(const Range &range, const string &name)
{
    printf("Optimizing for %s over [%f : %f : %f]\n", name.c_str(),
           range.low, range.incr, range.high);
}

int main(int argc, char *argv[])
{
    // <Whisker> is Action
    WhiskerTree whiskers;
    string output_filename;
    BreederOptions options;
    WhiskerImproverOptions whisker_options;
    RemyBuffers::ConfigRange input_config;
    string config_filename;

    for (int i = 1; i < argc; i++)
    {
        string arg(argv[i]);
        if (arg.substr(0, 3) == "if=") // input file name if=
        {
            string filename(arg.substr(3));
            int fd = open(filename.c_str(), O_RDONLY);
            if (fd < 0)
            {
                perror("open");
                exit(1);
            }

            RemyBuffers::WhiskerTree tree;
            if (!tree.ParseFromFileDescriptor(fd))
            {
                fprintf(stderr, "Could not parse %s.\n", filename.c_str());
                exit(1);
            }
            whiskers = WhiskerTree(tree);

            if (close(fd) < 0)
            {
                perror("close");
                exit(1);
            }
        }
        else if (arg.substr(0, 3) == "of=") // output file name of=
        {
            output_filename = string(arg.substr(3));
        }
        else if (arg.substr(0, 4) == "opt=") // optimization options
        {
            // optimization options parsed from "opt=" are passed to `whisker_options`
            whisker_options.optimize_window_increment = false;
            whisker_options.optimize_window_multiple = false;
            whisker_options.optimize_intersend = false;
            for (char &c : arg.substr(4))
            {
                if (c == 'b')
                {
                    whisker_options.optimize_window_increment = true;
                }
                else if (c == 'm')
                {
                    whisker_options.optimize_window_multiple = true;
                }
                else if (c == 'r')
                {
                    whisker_options.optimize_intersend = true;
                }
                else
                {
                    fprintf(stderr, "Invalid optimize option: %c\n", c);
                    exit(1);
                }
            }
        }
        else if (arg.substr(0, 3) == "cf=") // configuration file
        {
            config_filename = string(arg.substr(3));
            int cfd = open(config_filename.c_str(), O_RDONLY);
            if (cfd < 0)
            {
                perror("open config file error");
                exit(1);
            }
            if (!input_config.ParseFromFileDescriptor(cfd))
            {
                fprintf(stderr, "Could not parse input config from file %s. \n", config_filename.c_str());
                exit(1);
            }
            if (close(cfd) < 0)
            {
                perror("close");
                exit(1);
            }
        }
    }

    // check if a configuration file is generated
    if (config_filename.empty())
    {
        fprintf(stderr, "An input configuration protobuf must be provided via the cf= option. \n");
        fprintf(stderr, "You can generate one using './configuration'. \n");
        exit(1);
    }

    // supply configurations from "cf=" file to options <BreederOptions>
    // Basically, options contains all design assumptions for a situation
    options.config_range = ConfigRange(input_config);

    RatBreeder breeder(options, whisker_options); // pass design assumptions and optimization options to breeder <RatBreeder>

    unsigned int run = 0; // epoch

    // print out input configurations
    printf("#######################\n");
    printf("Evaluator simulations will run for %d ticks\n",
           options.config_range.simulation_ticks);
    printf("Optimizing window increment: %d, window multiple: %d, intersend: %d\n",
           whisker_options.optimize_window_increment, whisker_options.optimize_window_multiple,
           whisker_options.optimize_intersend);
    print_range(options.config_range.link_ppt, "link packets_per_ms");
    print_range(options.config_range.rtt, "rtt_ms");
    print_range(options.config_range.num_senders, "num_senders");
    print_range(options.config_range.mean_on_duration, "mean_on_duration");
    print_range(options.config_range.mean_off_duration, "mean_off_duration");
    print_range(options.config_range.stochastic_loss_rate, "stochastic_loss_rate");
    // if the buffer size is not infinite, print the buffer size
    // else print `Optimizing for infinitely sized buffers.`
    if (options.config_range.buffer_size.low != numeric_limits<unsigned int>::max())
    {
        print_range(options.config_range.buffer_size, "buffer_size");
    }
    else
    {
        printf("Optimizing for infinitely sized buffers. \n");
    }

    // print out whiskertree structure
    printf("Initial rules (use if=FILENAME to read from disk): %s\n", whiskers.str().c_str());
    printf("#######################\n");

    // print out output file information
    if (!output_filename.empty())
    {
        printf("Writing to \"%s.N\".\n", output_filename.c_str());
    }
    else
    {
        printf("Not saving output. Use the of=FILENAME argument to save the results.\n");
    }

    // specify training configurations
    RemyBuffers::ConfigVector training_configs;
    bool written = false;

    while (1)
    {
        auto outcome = breeder.improve(whiskers); // greedy steps to build and improve rule table
        printf("run = %u, score = %f\n", run, outcome.score);

        printf("whiskers: %s\n", whiskers.str().c_str());

        for (auto &run : outcome.throughputs_delays)
        {
            if (!(written))
            {
                for (auto &run : outcome.throughputs_delays)
                {
                    // record the config to the protobuf
                    RemyBuffers::NetConfig *net_config = training_configs.add_config();
                    *net_config = run.first.DNA();
                    written = true;
                }
            }
            printf("===\nconfig: %s\n", run.first.str().c_str());
            // ex: config: mean_on=5.000000, mean_off=5.000000, nsrc=3.000000, link_ppt=10.000000, delay=100.000000, buffer_size=10000.000000, stochastic_loss_rate = 0.100000
            for (auto &x : run.second)
            {
                printf("sender: [tp=%f, del=%f]\n", x.first / run.first.link_ppt, x.second / run.first.delay);
            }
            // sender: [tp=0.038204, del=1.001007]
            // sender: [tp=0.040126, del=1.001032]
            // sender: [tp=0.046403, del=1.001029]
        }

        if (!output_filename.empty())
        {
            char of[128];
            snprintf(of, 128, "%s.%d", output_filename.c_str(), run);
            fprintf(stderr, "Writing to \"%s\"... ", of);
            int fd = open(of, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
            if (fd < 0)
            {
                perror("open");
                exit(1);
            }

            auto remycc = whiskers.DNA();
            remycc.mutable_config()->CopyFrom(options.config_range.DNA());
            remycc.mutable_optimizer()->CopyFrom(Whisker::get_optimizer().DNA());
            remycc.mutable_configvector()->CopyFrom(training_configs);
            if (not remycc.SerializeToFileDescriptor(fd))
            {
                fprintf(stderr, "Could not serialize RemyCC.\n");
                exit(1);
            }

            if (close(fd) < 0)
            {
                perror("close");
                exit(1);
            }

            fprintf(stderr, "done.\n");
        }

        fflush(NULL);
        run++;
    }

    return 0;
}
