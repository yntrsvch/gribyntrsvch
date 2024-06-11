#include <eccodes.h>
#include <iostream>
#include <fstream>

void print_grib_info(const char* file_path) {
    FILE* f = fopen(file_path, "rb");
    if (!f) {
        std::cerr << "Error opening file: " << file_path << std::endl;
        return;
    }

    codes_handle* h = nullptr;
    int err = 0;
    long edition, length, startPos, endPos, paramTableVersion, center, processId, gridId, indicatorType, level, year, month, day, hour, minute, unit, P1, P2, timeRange, century, subCenter, decimalScale;
    double lat, lon;
    size_t size = 1024;
    char centerName[1024];

    while ((h = codes_handle_new_from_file(nullptr, f, PRODUCT_GRIB, &err)) != nullptr) {
        codes_get_long(h, "editionNumber", &edition);
        codes_get_long(h, "totalLength", &length);
        codes_get_long(h, "offsetSection0", &startPos);
        codes_get_long(h, "offsetSection7", &endPos);
        codes_get_long(h, "parameterTableVersion", &paramTableVersion);
        codes_get_long(h, "centre", &center);
        codes_get_long(h, "generatingProcessIdentifier", &processId);
        codes_get_long(h, "gridDefinitionTemplateNumber", &gridId);
        codes_get_long(h, "indicatorOfTypeOfLevel", &indicatorType);
        codes_get_long(h, "level", &level);
        codes_get_long(h, "year", &year);
        codes_get_long(h, "month", &month);
        codes_get_long(h, "day", &day);
        codes_get_long(h, "hour", &hour);
        codes_get_long(h, "minute", &minute);
        codes_get_long(h, "unitOfTimeRange", &unit);
        codes_get_long(h, "P1", &P1);
        codes_get_long(h, "P2", &P2);
        codes_get_long(h, "timeRangeIndicator", &timeRange);
        codes_get_long(h, "centuryOfReferenceTimeOfData", &century);
        codes_get_long(h, "subCentre", &subCenter);
        codes_get_long(h, "decimalScaleFactor", &decimalScale);
        codes_get_string(h, "centreDescription", centerName, &size);

        std::cout << "Coding info: " << edition << "\n";
        std::cout << "==========================\n";
        std::cout << "== General Message Info ==\n";
        std::cout << "==========================\n";
        std::cout << "Grib Finda at pos: " << startPos << "\n";
        std::cout << "7777 Find at position: " << endPos << "\n";
        std::cout << "Distance bettwen end of grib and start of 7777: " << (endPos - startPos) << "\n";
        std::cout << "Whole Message length: " << length << "\n";

        std::cout << "======================\n";
        std::cout << "==  Section 1 Data  ==\n";
        std::cout << "======================\n";
        std::cout << "Parameter table Version: " << paramTableVersion << "\n";
        std::cout << "Identification of Centre: " << centerName << "\n";
        std::cout << "Process ID number: " << processId << "\n";
        std::cout << "Grid Identification: " << gridId << "\n";
        std::cout << "Indicator of type of level or layer: " << indicatorType << "\n";
        std::cout << "Height, pressure, etc. of the level or layer: " << level << "\n";
        std::cout << "YY/MM/DD|HH:MM  :  " << year << "/" << month << "/" << day << "|" << hour << ":" << minute << "\n";
        std::cout << "Time unit: " << unit << "\n";
        std::cout << "P1 - Period of time: " << P1 << "\n";
        std::cout << "P2 - Period of time: " << P2 << "\n";
        std::cout << "Time range indicator: " << timeRange << "\n";
        std::cout << "Reference century: " << century << "\n";
        std::cout << "Identification of sub Center: " << subCenter << "\n";
        std::cout << "Decimal Scale factor: " << decimalScale << "\n";

        // You can extract and print more sections similarly

        codes_handle_delete(h);
    }

    fclose(f);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <GRIB file path>" << std::endl;
        return 1;
    }

    print_grib_info(argv[1]);
    return 0;
}
