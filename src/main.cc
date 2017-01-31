#include <iostream>

#include "options.h"
#include "webserver.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Invalid number of arguments. Usage: webserver <config_file>\n";
        return 1;
    }

    Options opt;
    opt.loadOptionsFromFile(argv[1]);
    unsigned short port_num = opt.getPort();
    std::cout << "configured port: " << port_num << std::endl;

    Webserver ws(port_num);
    ws.run();

    return 0;
}
