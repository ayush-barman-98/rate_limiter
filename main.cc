#include <drogon/drogon.h>
#include "services/logger/logger.hpp"

int main() {
    drogon::app().addListener("0.0.0.0", 5555);

    logger.debug("debug");
    logger.info("info");
    logger.warn("warn");
    logger.error("error");

    drogon::app().run();
    return 0;
}