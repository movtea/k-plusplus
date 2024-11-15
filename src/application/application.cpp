#include "application.h"

#include <iostream>
#include <string>
#include <vector>
#include <future>

#include "../nsrlRepository/nsrlRepository.h"
#include "../getFileFromDir/getFileFromDir.h"
#include "../OutputDB/outputDB.h"
#include "../calculateShaHash/calculateShaHash.h"
#include "../../models/fileSchema.h"

using namespace std;

/**
 * Конструктор приложения
 * @param [in] argc количество отправленных параметров
 * @param [in] argv отправленные параметры
 */
Application::Application(int argc, const char **argv)
{
    // Добавляем пункты меню
    m_desc.add_options()("help,h", "Print the help")("nsrl-db-path,r", po::value<filesystem::path>(&m_inputDBPath)->composing(), "set the path to the nsrl database")("scan-dir,s", po::value<filesystem::path>(&m_scanDirPath)->composing(), "set the folder to scan")("output-db-path,o", po::value<filesystem::path>(&m_outputDBPath)->composing(), "set the path to the response base")("output-db-name,n", po::value<filesystem::path>(&m_outputDBPath)->composing(), "set a name for the response database");
    po::store(po::parse_command_line(argc, argv, m_desc), m_vm); // парсим переданные аргументы
    po::notify(m_vm);                                            // записываем аргументы в переменные в программе
}

/**
 * Запуск приложения
 */
int Application::exec()
{
    // Если есть запрос на справку
    if (m_vm.count("help"))
    {
        // То выводим описание меню
        cout << m_desc << endl;
        return 1;
    }

    if (!m_vm.count("scan-dir"))
    {
        // То выводим описание меню
        cout << "\033[93m" << "Enter the scan-dir parameter" << "\033[0m" << endl;
        return 1;
    }

    if (!m_vm.count("nsrl-db-path"))
    {
        cout << "\033[93m" << "nsrl-db-path parameter is not defined." << "\033[0m" << endl;
        return 1;
    }

    NSRLRepository* nsrlRepo;
    OutputDB* ourDatabase;
    vector<FilePtr> filename = getFileFromDir(m_scanDirPath);               // Рекурсивный обход указанной директории
    try {
        nsrlRepo = new NSRLRepository(m_inputDBPath);                // Инициализация NSRL репозитория
        ourDatabase = new OutputDB(m_outputDBPath.append(m_outputDBName)); // Создание выходных баз данных
    }
    catch (const NSRLRepository::NSRLDBException &ex)
    {
        cout << ex.messages << ex.error << endl;
        delete nsrlRepo;
        delete ourDatabase;
        return 1;
    }
    

    int j = 0;
    for (int i = 0; i < filename.size(); i++)
    {
        try {
            future<void> a1 = async([filename, i]                         // Анализ контрольной суммы файла
                                { CalculateSHA1Hash(filename[i]); }); // Подсчет хеша
            a1.wait();
            future<void> a2 = async([&nsrlRepo, filename, i]
                                    { nsrlRepo->IsHashInDB(filename[i]); });
            a2.wait();
            ourDatabase->FillTheDB(filename[i]); // Заполнение баз данных
        }catch (const NSRLRepository::NSRLDBException &ex)
        {
            cout << ex.messages << ex.error << endl;
            delete nsrlRepo;
            delete ourDatabase;
            return 1;
        }
    }

    filename.clear();
    delete nsrlRepo;
    delete ourDatabase;
    return 0;
}