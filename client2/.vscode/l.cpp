#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/stream.hpp>
#include <fcntl.h>

namespace io = boost::iostreams;

void readLineByLineBoost() {
    int fdr = open("me.txt", O_RDONLY);
    if (fdr >= 0) {
        io::file_descriptor_source fdDevice(fdr, io::file_descriptor_flags::close_handle);
        io::stream <io::file_descriptor_source> in(fdDevice);
        if (fdDevice.is_open()) {
            std::string line;
            while (std::getline(in, line)) {
                // using printf() in all tests for consistency
                printf("%s", line.c_str());
            }
            fdDevice.close();
        }
    }
}