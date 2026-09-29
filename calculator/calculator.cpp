#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iomanip>

const double PI = 3.14159265358979323846;

void printHelp(const char* prog) {
    std::cout << "Калькулятор (вариант 11): тригонометрический\n"
              << "Поддерживаемые операции: arctg, arcctg\n"
              << "Количество операндов: 1\n\n"
              << "Использование:\n"
              << "  " << prog << " -o <operation> -m <mode> <operand>\n\n"
              << "Параметры:\n"
              << "  -o, --operation <op>   Операция: arctg | arcctg\n"
              << "  -m, --mode <mode>      Режим углов: rad | deg\n"
              << "  -h, --help             Показать эту справку\n\n"
              << "Примеры:\n"
              << "  " << prog << " -o arctg  -m rad 1\n"
              << "  " << prog << " -o arcctg -m deg 1\n";
}

int main(int argc, char* argv[]) {
    std::string operation;
    std::string mode = "rad";
    bool hasOperand = false;
    double operand = 0.0;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            printHelp(argv[0]);
            return 0;
        }
        else if (arg == "-o" || arg == "--operation") {
            if (i + 1 >= argc) {
                std::cerr << "Ошибка: не указано значение для " << arg << "\n";
                return 1;
            }
            operation = argv[++i];
        }
        else if (arg == "-m" || arg == "--mode") {
            if (i + 1 >= argc) {
                std::cerr << "Ошибка: не указано значение для " << arg << "\n";
                return 1;
            }
            mode = argv[++i];
        }
        else if (!arg.empty() && arg[0] == '-') {
            std::cerr << "Ошибка: неизвестный параметр " << arg << "\n";
            printHelp(argv[0]);
            return 1;
        }
        else {
            if (hasOperand) {
                std::cerr << "Ошибка: операнд уже задан\n";
                return 1;
            }
            char* endptr = nullptr;
            operand = std::strtod(arg.c_str(), &endptr);
            if (endptr == arg.c_str() || *endptr != '\0') {
                std::cerr << "Ошибка: операнд не является числом: " << arg << "\n";
                return 1;
            }
            hasOperand = true;
        }
    }

    if (argc == 1) {
        printHelp(argv[0]);
        return 0;
    }

    if (operation.empty()) {
        std::cerr << "Ошибка: не задана операция (-o arctg|arcctg)\n";
        return 1;
    }
    if (!hasOperand) {
        std::cerr << "Ошибка: не задан операнд\n";
        return 1;
    }
    if (mode != "rad" && mode != "deg") {
        std::cerr << "Ошибка: режим должен быть rad или deg\n";
        return 1;
    }

    bool toDegrees = (mode == "deg");
    double result = 0.0;

    if (operation == "arctg") {
        result = std::atan(operand);
        if (toDegrees) result = result * 180.0 / PI;
    }
    else if (operation == "arcctg") {
        if (operand == 0.0) {
            std::cerr << "Ошибка: arcctg не определён при x = 0\n";
            return 1;
        }
        result = PI / 2.0 - std::atan(operand);
        if (toDegrees) result = result * 180.0 / PI;
    }
    else {
        std::cerr << "Ошибка: неизвестная операция '" << operation
                  << "'. Доступно: arctg, arcctg\n";
        return 1;
    }

    std::cout << std::fixed << std::setprecision(10)
              << "Результат: " << result
              << (toDegrees ? " (градусы)" : " (радианы)") << "\n";

    return 0;
}
