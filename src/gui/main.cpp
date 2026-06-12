#include <QApplication>
#include <QDir>
#include <cstdlib>
#include "EGIAmpWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    std::string configPath;
    bool configSpecified = false;

    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];
        if ((arg == "--config" || arg == "-c") && i + 1 < argc) {
            configPath = argv[++i];
            configSpecified = true;
        } else if (arg.rfind("--config=", 0) == 0) {
            configPath = arg.substr(9);
            configSpecified = true;
        } else if (!arg.empty() && arg[0] != '-' && !configSpecified) {
            // Backward-compatible positional config path
            configPath = arg;
            configSpecified = true;
        } else if (arg == "--help" || arg == "-h") {
            return 0;
        }
    }

    if (!configSpecified) {
        if (const char* envPath = std::getenv("EGIAMP_CONFIG_FILE")) {
            configPath = envPath;
        } else {
            configPath = QDir(QCoreApplication::applicationDirPath())
                             .filePath("ampserver_config.cfg").toStdString();
        }
    }

    EGIAmpWindow window(nullptr, configPath);
    window.show();
    return app.exec();
}
